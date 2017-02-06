#include "jobmanager.h"

JobManager::JobManager()
{
    this->job_db = QSqlDatabase::addDatabase("QSQLITE");
    this->job_db.setDatabaseName(DB_PATH);
    this->job_db.open();

    this->checkTables();

    this->_jobModel = new QSqlTableModel();
    this->_jobModel->setTable("jobs");
    this->_jobModel->select();
}

JobManager::~JobManager()
{
    delete this->_jobModel;

    this->job_db.close();
}

QSqlTableModel *JobManager::jobModel()
{
    return this->_jobModel;
}

void JobManager::checkTables()
{
    QSqlQuery checkQuery(QSqlDatabase::database());

    QString selectString = "SELECT * FROM sqlite_master WHERE name = 'jobs' "
                           "AND type = 'table';";
    checkQuery.exec(selectString);

    if (!checkQuery.next()) {
        QString jobsSql = "CREATE TABLE jobs ("
                        "`JobID` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
                        "`site` TEXT NOT NULL,"
                        "`tags` TEXT NOT NULL,"
                        "`save_path` TEXT NOT NULL,"
                        "`pic_types` TEXT NOT NULL,"
                        "`rating` TEXT NOT NULL,"
                        "`file_types` TEXT NOT NULL,"
                        "`filenames` TEXT NOT NULL,"
                        "`try_max` INTEGER NOT NULL,"
                        "`last_search_url` TEXT NOT NULL,"
                        "`done` INTEGER NOT NULL,"
                        "`search_done` INTEGER NOT NULL,"
                        "`posts_done` INTEGER NOT NULL);";
        checkQuery.exec(jobsSql);
    }

//    selectString = "SELECT * FROM sqlite_master WHERE name = 'search' "
//                   "AND type = 'table';";
//    checkQuery.exec(selectString);

//    if (!checkQuery.next()) {
//        QString jobsSql = "CREATE TABLE `search` ("
//                          "`SearchID` INTEGER NOT NULL PRIMARY KEY "
//                          "AUTOINCREMENT,"
//                          "`JobID` INTEGER NOT NULL,"
//                          "`url` TEXT NOT NULL,"
//                          "`done` INTEGER NOT NULL,"
//                          "`try` INTEGER NOT NULL);";
//        checkQuery.exec(jobsSql);
//    }

    selectString = "SELECT * FROM sqlite_master WHERE name = 'posts' "
                   "AND type = 'table';";
    checkQuery.exec(selectString);

    if (!checkQuery.next()) {
        QString jobsSql = "CREATE TABLE `posts` ("
                          "`PostID` INTEGER NOT NULL PRIMARY KEY "
                          "AUTOINCREMENT,"
                          "`JobID` INTEGER NOT NULL,"
                          "`url` TEXT NOT NULL,"
//                          "`rating` TEXT,"
                          "`done` INTEGER NOT NULL);";
        checkQuery.exec(jobsSql);
    }
    selectString = "SELECT * FROM sqlite_master WHERE name = 'pics' "
                   "AND type = 'table';";
    checkQuery.exec(selectString);

    if (!checkQuery.next()) {
        QString jobsSql = "CREATE TABLE `pics` ("
                          "`PicID` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
                          "`JobID` INTEGER NOT NULL,"
                          "`url` TEXT NOT NULL,"
                          "`done` INTEGER NOT NULL,"
                          "`filename` INTEGER NOT NULL);";
        checkQuery.exec(jobsSql);
    }
}

void JobManager::addJob(Job job)
{
    QSqlQuery addQuery(QSqlDatabase::database());

    QString site = job.site;
    QString tags = job.tags.join(SEP);
    QString save_path = job.save_path;

    QString pic_types = pack_qset(job.pic_types);
    QString rating = pack_qset(job.rating);
    QString file_types = pack_qset(job.file_types);

    //defaults
    QString filenames = job.filenames;
    int try_max = job.try_max;

    //service
    QString last_search_url = job.lastSearchUrl;
    int done = job.done;
    int search_done = job.search_done;
    int posts_done = job.posts_done;

    QString insertString("INSERT INTO jobs(site, tags, save_path, pic_types, "
                         "rating, file_types, filenames, try_max, "
                         "last_search_url, done, search_done, posts_done) "
                         "VALUES ('%1', '%2', '%3', '%4', '%5', '%6', '%7', "
                         "%8, '%9', %10, %11, %12);");

    QString str = insertString.arg(site).arg(tags).arg(save_path);
    str = str.arg(pic_types).arg(rating).arg(file_types).arg(filenames);
    str = str.arg(try_max).arg(last_search_url).arg(done).arg(search_done).arg(posts_done);

    cout << str.toStdString() << endl;

    addQuery.exec(str);
}

Job JobManager::getJob(int jobID)
{
    QSqlQuery selectQuery(QSqlDatabase::database());
    QString selectString = "SELECT * FROM jobs WHERE JobID = %1";
    selectString = selectString.arg(jobID);

    selectQuery.exec(selectString);

    QSqlRecord rec = selectQuery.record();

    Job selectJob;
    while (selectQuery.next()) {
        selectJob.id = selectQuery.value(rec.indexOf("JobID")).toInt();
        selectJob.site = selectQuery.value(rec.indexOf("site")).toString();

        selectJob.tags = selectQuery.value(
                    rec.indexOf("tags")).toString().split(SEP);

        selectJob.save_path = selectQuery.value(
                    rec.indexOf("save_path")).toString();

        selectJob.pic_types = unpack_qset(
                    selectQuery.value(rec.indexOf("pic_types")).toString());
        selectJob.rating = unpack_qset(
                    selectQuery.value(rec.indexOf("rating")).toString());
        selectJob.file_types = unpack_qset(
                    selectQuery.value(rec.indexOf("file_types")).toString());
        selectJob.filenames = selectQuery.value(rec.indexOf("filenames")).toString();
        selectJob.try_max = selectQuery.value(rec.indexOf("try_max")).toInt();
        selectJob.lastSearchUrl = selectQuery.value(rec.indexOf("last_search_url")).toString();

        selectJob.done = selectQuery.value(rec.indexOf("done")).toBool();
        selectJob.search_done = selectQuery.value(rec.indexOf("search_done")).toBool();
        selectJob.posts_done = selectQuery.value(rec.indexOf("posts_done")).toBool();
    }

    return selectJob;
}

Job JobManager::getLastJob()
{
    QSqlQuery selectQuery(QSqlDatabase::database());
    QString selectString = "SELECT JobID FROM jobs WHERE done = 0 ORDER BY JobID"
                           " DESC LIMIT 1;";

    selectQuery.exec(selectString);
    QSqlRecord rec = selectQuery.record();

    int lastJobID = 0;
    while (selectQuery.next()) {
        lastJobID = selectQuery.value(rec.indexOf("JobID")).toInt();
    }

    return this->getJob(lastJobID);
}

void JobManager::updSearch(QString searchUrl, int jobID)
{
    QSqlQuery updateQuery(QSqlDatabase::database());
    QString updateString = "UPDATE jobs SET last_search_url = %1 "
                           "WHERE JobID = %2";
    updateString = updateString.arg(searchUrl).arg(jobID);
    cout << "UPD EXEC" << endl;
    updateQuery.exec(updateString);
}

void JobManager::addPosts(QStringList postUrls, int jobID)
{
    QSqlQuery insertQuery(QSqlDatabase::database());
    QString insertTemplate = "INSERT INTO posts (JobID, url, done) VALUES (%1, '%2', 0)";
    QString insertString;

    QString postUrl;
    for (int i = 0; i < postUrls.count(); i++) {
        postUrl = postUrls.at(i);
        insertString = insertTemplate.arg(jobID).arg(postUrl);
        insertQuery.exec(insertString);
    }
    cout << postUrls.count() << " POSTS ADDED" << endl;
}

void JobManager::searchDone(int jobID)
{
    QSqlQuery updateQuery(QSqlDatabase::database());
    QString updateString = "UPDATE jobs SET search_done = 1 "
                           "WHERE JobID = %1";
    updateString = updateString.arg(jobID);

    updateQuery.exec(updateString);
}

QList<PostInfo> JobManager::readPosts(int jobID)
{
    QSqlQuery selectQuery(QSqlDatabase::database());
    QString selectString = "SELECT PostID, url FROM posts WHERE JobID = %1 AND done = 0";
    selectString = selectString.arg(jobID);

    selectQuery.exec(selectString);
    QSqlRecord rec = selectQuery.record();

    QList<PostInfo> postList;
    while (selectQuery.next()) {
        PostInfo postInfo;
        postInfo.id = selectQuery.value(rec.indexOf("PostID")).toInt();
        postInfo.url = selectQuery.value(rec.indexOf("url")).toString();

        postList << postInfo;
    }

    cout << "COUNT: " << postList.count() << endl;
    return postList;
}

void JobManager::postDone(int postID)
{
    QSqlQuery updateQuery(QSqlDatabase::database());
    QString updateString = "UPDATE posts SET done = 1 "
                           "WHERE PostID = %1";
    updateString = updateString.arg(postID);

    updateQuery.exec(updateString);
}

void JobManager::addPics(QList<PicInfo> picList, int jobID)
{
    QSqlQuery insertQuery(QSqlDatabase::database());
    QString insertTemplate = "INSERT INTO pics (JobID, url, done, filename) VALUES (%1, '%2', 0, '%3')";
    QString insertString;

    for (int i = 0; i < picList.count(); i++) {
        QString picUrl = picList.at(i).url;
        QString picName = picList.at(i).name;

        insertString = insertTemplate.arg(jobID).arg(picUrl).arg(picName);
        insertQuery.exec(insertString);
    }
    cout << picList.count() << " PICS ADDED" << endl;
}

void JobManager::postsDone(int jobID)
{
    QSqlQuery updateQuery(QSqlDatabase::database());
    QString updateString = "UPDATE jobs SET posts_done = 1 "
                           "WHERE JobID = %1";
    updateString = updateString.arg(jobID);

    updateQuery.exec(updateString);
}

QList<PicInfo> JobManager::readPics(int jobID)
{
    QSqlQuery selectQuery(QSqlDatabase::database());
    QString selectString = "SELECT PicID, url, filename FROM pics WHERE JobID = %1 AND done = 0";
    selectString = selectString.arg(jobID);
    cout << "PICS:" << selectString.toStdString() << endl;

    selectQuery.exec(selectString);
    QSqlRecord rec = selectQuery.record();

    QList<PicInfo> picList;
    while (selectQuery.next()) {
        PicInfo picInfo;
        picInfo.id = selectQuery.value(rec.indexOf("PicID")).toInt();
        picInfo.url = selectQuery.value(rec.indexOf("url")).toString();
        picInfo.name = selectQuery.value(rec.indexOf("filename")).toString();

        picList << picInfo;
    }

    cout << "COUNT: " << picList.count() << endl;
    return picList;
}

void JobManager::picDone(int picID)
{
    QSqlQuery updateQuery(QSqlDatabase::database());
    QString updateString = "UPDATE pics SET done = 1 "
                           "WHERE PicID = %1";
    updateString = updateString.arg(picID);

    updateQuery.exec(updateString);
}

void JobManager::picsDone(int jobID)
{
    QSqlQuery updateQuery(QSqlDatabase::database());
    QString updateString = "UPDATE jobs SET done = 1 "
                           "WHERE JobID = %1";
    updateString = updateString.arg(jobID);

    updateQuery.exec(updateString);
}

QString JobManager::pack_qset(QSet<QString> set)
{
    return QStringList(set.toList()).join(SEP);
}

QSet<QString> JobManager::unpack_qset(QString str)
{
    QSet<QString> set = QSet<QString>::fromList(str.split(SEP));
    return set;
}
