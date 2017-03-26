#include "grabber.h"

Grabber::Grabber(QObject *parent) :
    QObject(parent)
{
    this->m_jobManager = new JobManager();
}

Grabber::~Grabber()
{
    delete this->m_jobManager;
//    delete m_loader;
    delete m_parser;
}

void Grabber::startNewJob(Job newJob)
{
    this->m_jobManager->addJob(newJob);
    this->contLastJob();
}

void Grabber::contLastJob()
{
    Job last = this->m_jobManager->getLastJob();
    this->startJob(last);
}

QSqlTableModel *Grabber::jobModel()
{
    return this->m_jobManager->jobModel();
}

void Grabber::startJob(Job currJob)
{
    cout << currJob << endl;
    emit logMessage("Job start");

    m_currJob = currJob;

    selectParser(m_currJob.getSite());

    this->m_picNamer.setPattern(m_currJob.getFilenameTemplate());
    this->m_picNamer.setPicsPath(m_currJob.getSavePath());

    switch (m_currJob.getStatus()) {
    case READY: {
        QString initialUrl = m_parser->genQueryUrl(m_currJob.getTags());
        cout << "QUERY: " << initialUrl.toStdString() << endl;

        this->m_jobManager->updSearch(initialUrl, m_currJob.getId());
        this->m_jobManager->updStatus(SEARCH_START, m_currJob.getId());

        m_currJob.setLastSearchUrl(initialUrl);
        m_currJob.setStatus(SEARCH_START);

        this->searchProcess(m_currJob.getLastSearchUrl());
        break;
    }
    case SEARCH_START: {
        emit logMessage("Search processing start");
        this->searchProcess(m_currJob.getLastSearchUrl());
        break;
    }
    case SEARCH_DONE: {
        this->postsProcess();
        break;
    }
    case POSTS_DONE: {
        this->picsDownload();
        break;
    }
    case PICS_DONE: {
        cout << "ALL DONE!" << endl;
        emit logMessage("Job finish");
    }
    }
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

void Grabber::selectParser(QString siteName)
{
    //    BooruParser* parser;
    if (siteName == sankaku::shortname) {
        m_parser = new SankakuChannelParser();
    }
    if (siteName == idol::shortname) {
        m_parser = new IdolComplexParser();
    }
    if (siteName == katawa::shortname) {
        m_parser = new MishimmieParser();
    }
    if (siteName == fourchan::shortname) {
        m_parser = new FourChanHouseParser();
    }
    if (siteName == konachan::shortname) {
        m_parser = new KonachanParser();
    }
    if (siteName == yandere::shortname) {
        m_parser = new YandeReParser();
    }
    if (siteName == danbooru::shortname) {
        m_parser = new DanbooruParser();
    }
    if (siteName == gelbooru::shortname) {
        m_parser = new GelbooruParser();
    }
    if (siteName == safebooru::shortname) {
        m_parser = new SafebooruParser();
    }
    cout << m_parser->name().toStdString() << endl;
    emit logMessage("Site: " + m_parser->name());
}

void Grabber::searchProcess(QString searchUrl)
{
    cout << "SEARCH PROCESS\tURL: " << searchUrl.toStdString() << endl;
    emit logMessage("Search url: " + searchUrl);
    emit stageChange(SEARCH);

    searchProcessStart(searchUrl);
}

void Grabber::searchProcessStart(QString searchUrl)
{
    m_loader = new Loader(searchUrl);
    cout << "LOADER" << endl;
    connect(m_loader,
            SIGNAL(downloaded()),
            this, SLOT(searchProcessFinish())
            );
}

void Grabber::searchProcessFinish()
{
    cout << "Search Finish" << endl;
    QString htmlText = m_loader->getHtml();
//    delete m_loader;
//    cout << htmlText.toStdString().substr(0, 500) << endl;

    SearchInfo searchInfo = m_parser->parseSearch(htmlText);
//    cout << searchInfo << endl;
    emit logMessage(QString::number(searchInfo.getPosts().length())
                    + " posts found");
    this->m_jobManager->addPosts(searchInfo.getPosts(), m_currJob.getId());

    if (searchInfo.hasNext()) {
        QString newSearchUrl = searchInfo.nextPage();

        this->m_jobManager->updSearch(newSearchUrl, m_currJob.getId());

        this->searchProcessStart(newSearchUrl);
    }
    else {
        this->m_jobManager->updStatus(SEARCH_DONE, m_currJob.getId());
        emit logMessage("Search processing finish");
        postsProcess();
    }
}

void Grabber::postsProcess()
{
    cout << "POSTS PROCESS" << endl;
    emit logMessage("Post processing start");
    emit stageChange(POST);

    m_posts.append(this->m_jobManager->readPosts(m_currJob.getId()));
    emit logMessage("Count: " + QString::number(m_posts.length()));

    if (!m_posts.isEmpty()) {
        m_currPost = m_posts.dequeue();
        postProcessStart();
    }
}

void Grabber::postProcessStart()
{
    QString postUrl = m_currPost.getUrl();

    emit logMessage("post url: " + postUrl);
    m_loader = new Loader(postUrl);
    connect(m_loader,
            SIGNAL(downloaded()),
            this, SLOT(postProcessFinish())
            );
}

void Grabber::postProcessFinish()
{
//    Job currJob = m_jobManager->getJob(m_jobID);

    QString postHtml = m_loader->getHtml();
    PostInfo postInfo = m_parser->parsePost(postHtml);
    if (
            (m_currJob.okRating(postInfo.getRating())) ||
            (m_currJob.okRating(RT_OTHER))
            )
    {
        QList<PicInfo> picList = postInfo.getPics();
        QList<PicInfo> okList;
        for (int j = 0; j < picList.count(); j++) {
            PicInfo picInfo = picList.at(j);
            if (
                    ( m_currJob.okType(picInfo.getType()) ) &&
                    ( m_currJob.okFormat(picInfo.getFormat()) )
                    )
            {
                //name?
                picInfo.setName(
                            this->m_picNamer.checkName(picInfo.getName())
                            );
                okList << picInfo;
            }
        }
        emit logMessage(QString::number(okList.length()) + " pics added");
        this->m_jobManager->addPics(okList, m_currJob.getId());
        this->m_jobManager->postDone(m_currPost.getId());
    }
//    emit progressChange(i+1, postList.count());

    if (m_posts.isEmpty()) {
        this->m_jobManager->updStatus(POSTS_DONE, m_currJob.getId());
        cout << "POSTS FINISH" << endl;
        emit logMessage("Post processing finish");
        picsDownload();
    }
    else {
        m_currPost = m_posts.dequeue();
        postProcessStart();
    }
}

void Grabber::picsDownload()
{
    cout << "PICS DOWNLOAD" << endl;
    emit logMessage("Pics download start");
    emit stageChange(DOWNLOAD);

    m_pics.append(this->m_jobManager->readPics(m_currJob.getId()));
    emit logMessage("Count: " + QString::number(m_pics.length()));

    if (!m_pics.isEmpty()) {
        m_currPic = m_pics.dequeue();
        picDownloadStart();
    }
}

void Grabber::picDownloadStart()
{
    QString picUrl = m_currPic.getUrl();

    emit logMessage("pic url: " + picUrl);
//    emit logMessage("Download pic #" + QString::number(i+1));
    m_loader = new Loader(picUrl);
    connect(m_loader,
            SIGNAL(downloaded()),
            this, SLOT(picDownloadFinish())
            );
}

void Grabber::picDownloadFinish()
{
    QFile file(m_currPic.getName());
    file.open(QIODevice::WriteOnly);
    file.write(m_loader->downloadedData());
    file.close();

    this->m_jobManager->picDone(m_currPic.getId());

    if (!m_pics.isEmpty()) {
        m_currPic = m_pics.dequeue();
        picDownloadStart();
    }
    else {
        this->m_jobManager->updStatus(PICS_DONE, m_currJob.getId());
        cout << "DOWNLOAD COMPLETE" << endl;
        emit logMessage("Pic download complete");
    }
}
