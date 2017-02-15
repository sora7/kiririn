#ifndef JOB_H
#define JOB_H

#include <iostream>

#include <QString>
#include <QStringList>
#include <QSet>

#include "items/postinfo.h"

using namespace std;

enum JobStatus {
    READY,
    SEARCH_START,
    SEARCH_DONE,
    POSTS_DONE,
    PICS_DONE
};

class Job
{
public:
    Job();
    ~Job();

    friend ostream &operator<<(ostream &os, const Job &job);
    static string to_str(JobStatus jobStatus);

    int id;
    QString site;
    QStringList tags;
    QString save_path;

    QSet<PicType> pic_types;
    QSet<PostRating> rating;
    QSet<PicFormat> file_types;

    QString lastSearchUrl;

    QString filenames;
    int try_max;

    JobStatus status;

//    bool done;
//    bool search_done;
//    bool posts_done;

    int getId() const;
    void setId(const int value);

    void addRating(const PostRating postRating);
    void addType(const PicType picType);
    void addFormat(const PicFormat picFormat);

    bool okRating(const PostRating postRating) const;
    bool okType(const PicType picType)const;
    bool okFormat(const PicFormat picFormat) const;

//    bool picType(QString pictype) const;

    JobStatus getStatus() const;
    void setStatus(const JobStatus jobStatus);

private:
};

#endif // JOB_H
