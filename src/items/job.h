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

    int getId() const;
    void setId(const int value);

    void addRating(const PostRating postRating);
    void addType(const PicType picType);
    void addFormat(const PicFormat picFormat);

    bool okRating(const PostRating postRating) const;
    bool okType(const PicType picType)const;
    bool okFormat(const PicFormat picFormat) const;

    JobStatus getStatus() const;
    void setStatus(const JobStatus jobStatus);

    QSet<PicType> getPicTypes() const;
    void setPicTypes(const QSet<PicType> picTypes);

    QSet<PostRating> getRating() const;
    void setRating(const QSet<PostRating> postRating);

    QSet<PicFormat> getPicFormats() const;
    void setPicFormats(const QSet<PicFormat> picFormats);

    QString getLastSearchUrl() const;
    void setLastSearchUrl(const QString &value);

    QString getSite() const;
    void setSite(const QString &value);

    QStringList getTags() const;
    void setTags(const QStringList &value);

    QString getSavePath() const;
    void setSavePath(const QString &value);

    QString getFilenameTemplate() const;
    void setFilenameTemplate(const QString &value);

    int getTryMax() const;
    void setTryMax(int value);

private:
    int _id;
    QString _site;
    QStringList _tags;
    QString _savePath;

    QSet<PicType> _pic_types;
    QSet<PostRating> _rating;
    QSet<PicFormat> _file_types;

    QString _lastSearchUrl;

    QString _filenameTemplate;
    int _tryMax;

    JobStatus _status;
};

#endif // JOB_H
