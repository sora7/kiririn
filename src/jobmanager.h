#ifndef JOBMANAGER_H
#define JOBMANAGER_H

#include <iostream>

#include <QtSql>

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

    static const QString DB_PATH;

    QSqlTableModel* jobModel();

    void addJob(Job job);
    Job getJob(int jobID);
    Job getLastJob();

    //search
    void updSearch(QString searchUrl, int jobID);
    void addPosts(QStringList postUrls, int jobID);
    void updStatus(JobStatus jobStatus, int jobID);

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
    QSqlDatabase m_job_db;
    QSqlTableModel *m_jobModel;

    void checkTables();

    template <class T>
    QString pack_qset(QSet<T> set);

    template <class T>
    QSet<T> unpack_qset(QString str);
};

#endif // JOBMANAGER_H
