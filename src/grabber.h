#ifndef GRABBER_H
#define GRABBER_H

#include <QObject>

#include <iostream>

using namespace std;

#include "loader.h"
#include "picnamer.h"

#include "parsers/booruparser.h"
#include "parsers/sankakuchannelparser.h"
#include "parsers/mishimmieparser.h"
#include "parsers/fourchanhouseparser.h"
#include "parsers/idolcomplexparser.h"
#include "parsers/konachanparser.h"
#include "parsers/yandereparser.h"
#include "parsers/danbooruparser.h"
#include "parsers/gelbooruparser.h"
#include "parsers/safebooruparser.h"

#include "jobmanager.h"

enum GrabberStage {
    SEARCH,
    POST,
    DOWNLOAD
};

class Grabber : public QObject
{
    Q_OBJECT
public:
    explicit Grabber(QObject *parent = 0);
    ~Grabber();

    void startNewJob(Job newJob);
    void contLastJob();

    QSqlTableModel* jobModel();
signals:
    void stageChange(GrabberStage stage);
    void progressChange(int current, int total);
    void logMessage(QString messageText);
private slots:
    void searchProcessStart(QString searchUrl);
    void searchProcessFinish();

    void postProcessStart();
    void postProcessFinish();

    void picDownloadStart();
    void picDownloadFinish();
private:
    JobManager* m_jobManager;
    BooruParser* m_parser;
    PicNamer m_picNamer;
    Loader* m_loader;

    Job m_currJob;
    PostInfo m_currPost;
    PicInfo m_currPic;

    QQueue<PostInfo> m_posts;
    QQueue<PicInfo> m_pics;

    void startJob(Job currJob);
    void selectParser(QString siteName);

    void searchProcess(QString searchUrl);
    void postsProcess();
    void picsDownload();
};

#endif // GRABBER_H
