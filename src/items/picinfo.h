#ifndef PICINFO_H
#define PICINFO_H

#include <iostream>
#include <QString>

using namespace std;

namespace pic_type {
    const int ORIGINAL = 1;
    const int RESIZED = 2;

    const int FORMAT_JPG  = 1;
    const int FORMAT_PNG  = 2;
    const int FORMAT_GIF  = 3;
    const int FORMAT_WEBM = 4;
    const int FORMAT_MP4  = 5;
}

class PicInfo
{
public:
    PicInfo();
    ~PicInfo();

    friend ostream &operator<<(ostream &os, const PicInfo &picInfo);

    int id;

    QString type;   //orig, resize
    QString format; //jpg, png, webm, mp4
    QString url;
    QString name;

    QString res;    // 1024x768
    QString size;   // KB
    int done;
};

#endif // PICINFO_H
