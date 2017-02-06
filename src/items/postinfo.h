#ifndef POSTINFO_H
#define POSTINFO_H

#include <iostream>

#include <QString>
#include <QList>

#include "items/picinfo.h"

using namespace std;

namespace post_rating {
    const int SAFE = 1;
    const int QUESTIONABLE = 2;
    const int EXPLICIT = 3;
}

class PostInfo
{
public:
    PostInfo();
    ~PostInfo();

    friend ostream &operator<<(ostream &os, const PostInfo &postInfo);

    int id;
    QString url;


    QString rating;
//    QStringList tags;
    QList<PicInfo> pics;
};

#endif // POSTINFO_H
