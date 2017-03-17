#ifndef GRABBER_H
#define GRABBER_H

#include <QObject>

#include <iostream>

using namespace std;

#include "loader.h"
#include "parsers/parser.h"
#include "parsers/sankakuparser.h"
#include "parsers/mishimmieparser.h"
#include "parsers/fourchanhouseparser.h"
#include "parsers/idolcomplexparser.h"
#include "parsers/konachanparser.h"

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
private:
    JobManager* jobManager;
    Job _currentJob;

//    GraberStage _stage;
//    int _progress_curr;
//    int _progress_total;

    void startJob(Job currJob);

    void searchProcess(QString searchUrl, Parser* parser, int jobID);
    void postsProcess(Parser *parser, Job currJob);
    void picsDownload(int jobID);
};

#endif // GRABBER_H
