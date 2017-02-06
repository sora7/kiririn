#ifndef JOBMANAGER_H
#define JOBMANAGER_H

#include <QtSql>

#include <iostream>

#include "items/job.h"
#include "items/searchinfo.h"
#include "items/postinfo.h"
#include "items/picinfo.h"

using namespace std;

const QString DB_PATH = "jobs.db";
const QString SEP = " ";

class JobManager
{
public:
    JobManager();
    ~JobManager();

    QSqlTableModel* jobModel();

    void checkTables();

    void addJob(Job job);
    Job getJob(int jobID);
    Job getLastJob();

    //search
    void updSearch(QString searchUrl, int jobID);
    void addPosts(QStringList postUrls, int jobID);
    void searchDone(int jobID);
    //posts
    QList<PostInfo> readPosts(int jobID);
    void postDone(int postID);
    void addPics(QList<PicInfo> picList, int jobID);
    void postsDone(int jobID);
    //pics
    QList<PicInfo> readPics(int jobID);
    void picDone(int picID);
    void picsDone(int jobID);

private:
    QSqlDatabase job_db;

    QSqlTableModel *_jobModel;

    QString pack_qset(QSet<QString> set);
    QSet<QString> unpack_qset(QString str);
};

#endif // JOBMANAGER_H
