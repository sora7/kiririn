#include "grabber.h"

Grabber::Grabber()
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

    Parser* parser;
    if (currJob.getSite() == "sankaku") {
        parser = new SankakuParser();
        cout << "Sankaku Channel" << endl;
    }
    if (currJob.getSite() == "idol") {
        parser = new IdolComplexParser();
        cout << "Idol Complex" << endl;
    }
    if (currJob.getSite() == "katawa") {
        parser = new MishimmieParser();
        cout << "Mishimmie" << endl;
    }
    if (currJob.getSite() == "4chan") {
        parser = new FourChanHouseParser();
        cout << "4chan House" << endl;
    }
    if (currJob.getSite() == "konachan") {
        parser = new KonachanParser();
        cout << "Konachan" << endl;
    }

    switch (currJob.getStatus()) {
    case READY: {
        QString initialUrl = parser->genQueryUrl(currJob.getTags());

        this->jobManager->updSearch(initialUrl, currJob.getId());
        this->jobManager->updStatus(SEARCH_START, currJob.getId());

        currJob.setLastSearchUrl(initialUrl);
        currJob.setStatus(SEARCH_START);
    }
    case SEARCH_START: {
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

void Grabber::searchProcess(QString searchUrl, Parser *parser, int jobID)
{
    cout << "SEARCH PROCESS\tURL: " << searchUrl.toStdString() << endl;
    Loader loader;
    QString htmlText = loader.loadHtml(searchUrl);

    SearchInfo searchInfo = parser->parseSearch(htmlText);

    this->jobManager->addPosts(searchInfo.getPosts(), jobID);

    if (searchInfo.hasNext()) {
        QString newSearchUrl = searchInfo.nextPage();

        this->jobManager->updSearch(newSearchUrl, jobID);

        this->searchProcess(newSearchUrl, parser, jobID);
    }
    else {
        this->jobManager->updStatus(SEARCH_DONE, jobID);
    }
}

void Grabber::postsProcess(Parser* parser, Job currJob)
{
    cout << "POSTS PROCESS" << endl;
    QList<PostInfo> postList = this->jobManager->readPosts(currJob.getId());

    Loader loader;
    for (int i = 0; i < postList.count(); i++) {
        QString postUrl = postList.at(i).getUrl();

        QString postHtml = loader.loadHtml(postUrl);
        PostInfo postInfo = parser->parsePost(postHtml);

//        cout << postInfo << endl;

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
            this->jobManager->addPics(okList, currJob.getId());
            this->jobManager->postDone(postList.at(i).getId());
        }
    }
    this->jobManager->updStatus(POSTS_DONE, currJob.getId());
    cout << "POSTS FINISH" << endl;
}

void Grabber::picsDownload(int jobID)
{
    cout << "PICS DOWNLOAD" << endl;
    QList<PicInfo> picList = this->jobManager->readPics(jobID);
    Loader loader;
    for (int i = 0; i < picList.count(); i++) {
        PicInfo picInfo = picList.at(i);

        cout << "LOAD #" << i+1 << endl;
        cout << picInfo.getName().toStdString() << endl;
        cout << picInfo.getName().toStdString() << endl;

        loader.loadFile(picInfo.getUrl(), picInfo.getName());
        this->jobManager->picDone(picInfo.getId());
    }
    this->jobManager->updStatus(PICS_DONE, jobID);
    cout << "DOWNLOAD COMPLETE" << endl;
}
