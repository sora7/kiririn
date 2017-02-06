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
    Parser* parser;
    cout << "PARSER" << endl;
    if (currJob.site == "sankaku") {
        parser = new SankakuParser();
    }
    if (!currJob.search_done) {
        if (currJob.lastSearchUrl == job::INIT_URL) {
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
        this->jobManager->searchDone(jobID);
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
        PostInfo parseInfo = parser->parsePost(postHtml);

        cout << parseInfo << endl;


        if (currJob.rating.contains(parseInfo.rating)) {
            QList<PicInfo> okList;
            for (int j = 0; j < parseInfo.pics.count(); j++) {
                PicInfo picInfo = parseInfo.pics.at(j);
                if (
                        (currJob.pic_types.contains(picInfo.type)) &&
                        (currJob.file_types.contains(picInfo.format))
                    ) {
                    //name?
                    okList << picInfo;
                }
            }
            this->jobManager->addPics(okList, currJob.id);
            this->jobManager->postDone(postList.at(i).id);
        }

    }
    this->jobManager->postsDone(currJob.id);
    cout << "POSTS FINISH" << endl;
}

void Grabber::picsDownload(int jobID)
{
    QList<PicInfo> picList = this->jobManager->readPics(jobID);
    Loader loader;
    for (int i = 0; i < picList.count(); i++) {
        PicInfo picInfo = picList.at(i);
        loader.loadFile(picInfo.url, picInfo.name);
        this->jobManager->picDone(picInfo.id);
    }
    this->jobManager->picsDone(jobID);
}
