#ifndef GRABBER_H
#define GRABBER_H

#include <iostream>

using namespace std;

#include "loader.h"
#include "parsers/parser.h"
#include "parsers/sankakuparser.h"
#include "jobmanager.h"

class Grabber
{
public:
    Grabber();
    ~Grabber();

    void startNewJob(Job newJob);
    void contLastJob();

    QSqlTableModel* jobModel();

private:
    JobManager* jobManager;

    Job _currentJob;

    void startJob(Job currJob);

    void searchProcess(QString searchUrl, Parser* parser, int jobID);
    void postsProcess(Parser *parser, Job currJob);
    void picsDownload(int jobID);
};

#endif // GRABBER_H
