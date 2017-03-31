#ifndef POSTINFO_H
#define POSTINFO_H

#include <iostream>

#include <QString>
#include <QList>

#include "items/picinfo.h"

using namespace std;

enum PostRating {
    SAFE,
    QUESTIONABLE,
    EXPLICIT,
    RT_OTHER
};

class PostInfo
{
public:
    PostInfo();
    ~PostInfo();

    friend ostream &operator<<(ostream &os, const PostInfo &postInfo);

    static string to_str(PostRating postRating);

    PostRating getRating() const;
    void setRating(const PostRating &value);
    QList<PicInfo> getPics() const;
    void setPics(const QList<PicInfo> &value);
    QString getUrl() const;
    void setUrl(const QString &value);
    int getId() const;
    void setId(int value);

private:
    int m_id;
    QString m_url;

    PostRating m_rating;
    QList<PicInfo> m_pics;
};

#endif // POSTINFO_H
