#include "grabber.h"

Grabber::Grabber(QObject *parent) :
    QObject(parent)
{
    this->m_jobManager = new JobManager();
    m_parser = NULL;

    m_loader = new Loader();

    m_currPic_i = 0;
}

Grabber::~Grabber()
{
    delete this->m_jobManager;

    m_loader->deleteLater();

    if (m_parser) {
        delete m_parser;
    }
}

void Grabber::startNewJob(Job newJob)
{
    this->m_jobManager->addJob(newJob);
    this->contLastJob();
}

void Grabber::contLastJob()
{
    m_currJob = this->m_jobManager->getLastJob();
    this->startJob();
}

QSqlTableModel *Grabber::jobModel()
{
    return this->m_jobManager->jobModel();
}

void Grabber::startJob()
{
    emit logMessage("Job start");

    selectParser(m_currJob.getSite());

    this->m_picNamer.setPattern(m_currJob.getFilenameTemplate());
    this->m_picNamer.setPicsPath(m_currJob.getSavePath());

    switch (m_currJob.getStatus()) {
    case READY: {
        QString initialUrl = m_parser->genQueryUrl(m_currJob.getTags());

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
        break;
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
    cout << "Site: " << m_parser->name().toStdString() << endl;
    emit logMessage("Site: " + m_parser->name());
}

void Grabber::searchProcess(QString searchUrl)
{
    cout << "SEARCH PROCESS\tURL: " << searchUrl.toStdString() << endl;
    emit logMessage("Search url: " + searchUrl);
    emit stageChange(SEARCH);

    connect(m_loader,
            SIGNAL(downloaded()),
            this,
            SLOT(searchProcessFinish())
            );

    searchProcessStart(searchUrl);
}

void Grabber::searchProcessStart(QString searchUrl)
{
    m_loader->load(searchUrl);
}

void Grabber::searchProcessFinish()
{
    QString htmlText = m_loader->getHtml();

    SearchInfo searchInfo = m_parser->parseSearch(htmlText);

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
        m_loader->disconnect(SIGNAL(downloaded()));
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
    emit progressMax(m_posts.length());

    connect(m_loader,
            SIGNAL(downloaded()),
            this,
            SLOT(postProcessFinish())
            );

    if (!m_posts.isEmpty()) {
        m_currPost = m_posts.dequeue();
        postProcessStart();
    }
}

void Grabber::postProcessStart()
{
    QString postUrl = m_currPost.getUrl();

    emit logMessage("post url: " + postUrl);
    m_loader->load(postUrl);
}

void Grabber::postProcessFinish()
{
    QString postHtml = m_loader->getHtml();
    PostInfo postInfo = m_parser->parsePost(postHtml);
    if ( m_currJob.okRating(postInfo) )
    {
        QList<PicInfo> picList = postInfo.getPics();
        QList<PicInfo> okList;
        for (int j = 0; j < picList.count(); j++) {
            PicInfo picInfo = picList.at(j);
            if ( m_currJob.picMatch(picInfo) )
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
    emit progress();

    if (m_posts.isEmpty()) {
        this->m_jobManager->updStatus(POSTS_DONE, m_currJob.getId());
        m_loader->disconnect(SIGNAL(downloaded()));
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
    emit progressMax(m_pics.length());

    connect(m_loader,
            SIGNAL(downloaded()),
            this,
            SLOT(picDownloadFinish())
            );

    if (!m_pics.isEmpty()) {
        m_currPic = m_pics.dequeue();
        picDownloadStart();
    }
}

void Grabber::picDownloadStart()
{
    QString picUrl = m_currPic.getUrl();

    m_currPic_i++;
    QString msgText = "Download pic #%1, url: %2";
    emit logMessage(msgText.arg(m_currPic_i).arg(picUrl));

    m_loader->load(picUrl);
}

void Grabber::picDownloadFinish()
{
    QFile file(m_currPic.getName());
    file.open(QIODevice::WriteOnly);
    file.write(m_loader->downloadedData());
    file.close();

    emit progress();
    this->m_jobManager->picDone(m_currPic.getId());

    if (!m_pics.isEmpty()) {
        m_currPic = m_pics.dequeue();
        picDownloadStart();
    }
    else {
        this->m_jobManager->updStatus(PICS_DONE, m_currJob.getId());
        m_loader->disconnect(SIGNAL(downloaded()));
        emit progress();
        emit logMessage("Pic download complete");
        cout << "DOWNLOAD COMPLETE" << endl;
    }
}
