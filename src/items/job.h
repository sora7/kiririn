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

    bool okRating(const PostInfo postInfo) const;
    bool picMatch(const PicInfo picInfo) const;

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
    int m_id;
    QString m_site;
    QStringList m_tags;
    QString m_savePath;

    QSet<PicType> m_pic_types;
    QSet<PostRating> m_rating;
    QSet<PicFormat> m_pic_formats;

    QString m_lastSearchUrl;

    QString m_filenameTemplate;
    int m_tryMax;

    JobStatus m_status;
};

#endif // JOB_H
