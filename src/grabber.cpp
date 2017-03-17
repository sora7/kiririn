#include "grabber.h"

Grabber::Grabber(QObject *parent) :
    QObject(parent)
{
    this->jobManager = new JobManager();
}

Grabber::~Grabber()
{
    delete this->jobManager;
}

void Grabber::startNewJob(Job newJob)
{
    this->jobManager->addJob(newJob);
    this->contLastJob();
}

void Grabber::contLastJob()
{
    Job last = this->jobManager->getLastJob();
    this->startJob(last);
}

QSqlTableModel *Grabber::jobModel()
{
    return this->jobManager->jobModel();
}

void Grabber::startJob(Job currJob)
{
    cout << currJob << endl;
    emit logMessage("Job start");
    BooruParser* parser;
    if (currJob.getSite() == sankaku::shortname) {
        parser = new SankakuChannelParser();
    }
    if (currJob.getSite() == idol::shortname) {
        parser = new IdolComplexParser();
    }
    if (currJob.getSite() == katawa::shortname) {
        parser = new MishimmieParser();
    }
    if (currJob.getSite() == fourchan::shortname) {
        parser = new FourChanHouseParser();
    }
    if (currJob.getSite() == konachan::shortname) {
        parser = new KonachanParser();
    }
    cout << parser->name().toStdString() << endl;
    emit logMessage("Site: " + parser->name());

    switch (currJob.getStatus()) {
    case READY: {
        QString initialUrl = parser->genQueryUrl(currJob.getTags());

        this->jobManager->updSearch(initialUrl, currJob.getId());
        this->jobManager->updStatus(SEARCH_START, currJob.getId());

        currJob.setLastSearchUrl(initialUrl);
        currJob.setStatus(SEARCH_START);
    }
    case SEARCH_START: {
        emit logMessage("Search processing start");
        this->searchProcess(currJob.getLastSearchUrl(), parser, currJob.getId());
    }
    case SEARCH_DONE: {
        this->postsProcess(parser, currJob);
    }
    case POSTS_DONE: {
        this->picsDownload(currJob.getId());
    }
    case PICS_DONE: {
        cout << "ALL DONE!" << endl;
        emit logMessage("Job finish");
    }
    }
    delete parser;
/*
    if (!currJob.search_done) {
        if (currJob.lastSearchUrl == Job::INITIAL_URL) {
            QString initialUrl = parser->genQueryUrl(currJob.tags);
            this->jobManager->updSearch(initialUrl, currJob.id);
            currJob.lastSearchUrl = initialUrl;
        }
        this->searchProcess(currJob.lastSearchUrl, parser, currJob.id);
    }

    if (!currJob.posts_done) {
        this->postsProcess(parser, currJob);
    }
    delete parser;

    this->picsDownload(currJob.id);
*/
}

void Grabber::searchProcess(QString searchUrl, BooruParser *parser, int jobID)
{
    cout << "SEARCH PROCESS\tURL: " << searchUrl.toStdString() << endl;
    emit logMessage("Search url: " + searchUrl);
    emit stageChange(SEARCH);

    Loader loader;
    QString htmlText = loader.loadHtml(searchUrl);

    SearchInfo searchInfo = parser->parseSearch(htmlText);
    emit logMessage(QString::number(searchInfo.getPosts().length())
                    + " posts found");
    this->jobManager->addPosts(searchInfo.getPosts(), jobID);

    if (searchInfo.hasNext()) {
        QString newSearchUrl = searchInfo.nextPage();

        this->jobManager->updSearch(newSearchUrl, jobID);

        this->searchProcess(newSearchUrl, parser, jobID);
    }
    else {
        this->jobManager->updStatus(SEARCH_DONE, jobID);
        emit logMessage("Search processing finish");
    }
}

void Grabber::postsProcess(BooruParser* parser, Job currJob)
{
    cout << "POSTS PROCESS" << endl;
    emit logMessage("Post processing start");
    emit stageChange(POST);

    QList<PostInfo> postList = this->jobManager->readPosts(currJob.getId());
    emit logMessage("Count: " + QString::number(postList.length()));

    Loader loader;
    for (int i = 0; i < postList.count(); i++) {
        QString postUrl = postList.at(i).getUrl();
        emit logMessage("post url: " + postUrl);

        QString postHtml = loader.loadHtml(postUrl);
        PostInfo postInfo = parser->parsePost(postHtml);
        cout << postInfo << endl;
        if (
                (currJob.okRating(postInfo.getRating())) ||
                (currJob.okRating(RT_OTHER))
            )
        {
            QList<PicInfo> picList = postInfo.getPics();
            QList<PicInfo> okList;
            for (int j = 0; j < picList.count(); j++) {
                PicInfo picInfo = picList.at(j);
                if (
                        ( currJob.okType(picInfo.getType()) ) &&
                        ( currJob.okFormat(picInfo.getFormat()) )
                    )
                {
                    //name?
                    okList << picInfo;
                }
            }
            emit logMessage(QString::number(okList.length()) + " pics added");
            this->jobManager->addPics(okList, currJob.getId());
            this->jobManager->postDone(postList.at(i).getId());
        }
        emit progressChange(i+1, postList.count());
    }
    this->jobManager->updStatus(POSTS_DONE, currJob.getId());
    cout << "POSTS FINISH" << endl;
    emit logMessage("Post processing finish");
}

void Grabber::picsDownload(int jobID)
{
    cout << "PICS DOWNLOAD" << endl;
    emit logMessage("Pics download start");
    emit stageChange(DOWNLOAD);

    QList<PicInfo> picList = this->jobManager->readPics(jobID);
    Loader loader;
    for (int i = 0; i < picList.count(); i++) {
        PicInfo picInfo = picList.at(i);

        cout << "LOAD #" << i+1 << endl;
        emit logMessage("Download pic #" + QString::number(i+1));

        cout << picInfo.getName().toStdString() << endl;
        cout << picInfo.getUrl().toStdString() << endl;

        loader.loadFile(picInfo.getUrl(), picInfo.getName());
        this->jobManager->picDone(picInfo.getId());

        emit progressChange(i+1, picList.count());
    }
    this->jobManager->updStatus(PICS_DONE, jobID);
    cout << "DOWNLOAD COMPLETE" << endl;
    emit logMessage("Pic download complete");
}
