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
private:
    JobManager* jobManager;
    Job _currentJob;
    PicNamer _picNamer;

    void startJob(Job currJob);

    void searchProcess(QString searchUrl, BooruParser* parser, int jobID);
    void postsProcess(BooruParser *parser, Job currJob);
    void picsDownload(int jobID);
};

#endif // GRABBER_H
