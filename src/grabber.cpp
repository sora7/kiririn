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
    cout << "PARSER" << endl;
    if (currJob.site == "sankaku") {
        parser = new SankakuParser();
        cout << "Sankaku Channel" << endl;
    }

    switch (currJob.status) {
    case READY: {
        QString initialUrl = parser->genQueryUrl(currJob.tags);

        this->jobManager->updSearch(initialUrl, currJob.id);
        this->jobManager->updStatus(SEARCH_START, currJob.id);

        currJob.lastSearchUrl = initialUrl;
        currJob.status = SEARCH_START;
//        this->searchProcess(initialUrl, parser, currJob.id);
//        break;
    }
    case SEARCH_START: {
        this->searchProcess(currJob.lastSearchUrl, parser, currJob.id);
//        break;
    }
    case SEARCH_DONE: {
        this->postsProcess(parser, currJob);
//        break;
    }
    case POSTS_DONE: {
        this->picsDownload(currJob.id);
//        break;
    }
    case PICS_DONE: {
        cout << "ALL DONE!" << endl;
//        break;
    }
    }
    delete parser;

//    if (!currJob.search_done) {
//        if (currJob.lastSearchUrl == Job::INITIAL_URL) {
//            QString initialUrl = parser->genQueryUrl(currJob.tags);
//            this->jobManager->updSearch(initialUrl, currJob.id);
//            currJob.lastSearchUrl = initialUrl;
//        }
//        this->searchProcess(currJob.lastSearchUrl, parser, currJob.id);
//    }

//    if (!currJob.posts_done) {
//        this->postsProcess(parser, currJob);
//    }
//    delete parser;

//    this->picsDownload(currJob.id);
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
    QList<PostInfo> postList = this->jobManager->readPosts(currJob.id);

    Loader loader;
    for (int i = 0; i < postList.count(); i++) {
        QString postUrl = postList.at(i).url;

        QString postHtml = loader.loadHtml(postUrl);
        PostInfo postInfo = parser->parsePost(postHtml);

//        cout << postInfo << endl;

//        if (    (currJob.rating.contains(postInfo.rating))
//                || (currJob.rating.contains(RT_OTHER))
//            ) {
        if (
                (currJob.okRating(postInfo.rating)) ||
                (currJob.okRating(RT_OTHER))
            )
        {
            QList<PicInfo> picList = postInfo.pics;
            QList<PicInfo> okList;
            for (int j = 0; j < picList.count(); j++) {
                PicInfo picInfo = picList.at(j);
                if (
                        (currJob.okType(picInfo.type)) &&
                        (currJob.okFormat(picInfo.format))
                    )
                {
                    //name?
                    okList << picInfo;
                }
            }
            this->jobManager->addPics(okList, currJob.id);
            this->jobManager->postDone(postList.at(i).id);
        }
    }
    this->jobManager->updStatus(POSTS_DONE, currJob.id);
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
        cout << picInfo.name.toStdString() << endl;
        cout << picInfo.url.toStdString() << endl;

        loader.loadFile(picInfo.url, picInfo.name);
        this->jobManager->picDone(picInfo.id);
    }
    this->jobManager->updStatus(PICS_DONE, jobID);
    cout << "DOWNLOAD COMPLETE" << endl;
}
