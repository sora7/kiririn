#ifndef PICINFO_H
#define PICINFO_H

#include <iostream>
#include <QString>

using namespace std;

enum PicType {
    ORIGINAL,
    RESIZED
};

enum PicFormat {
    JPG,
    PNG,
    GIF,
    WEBM,
    MP4,
    UNDEFINED
};

class PicInfo
{
public:
    PicInfo();
    ~PicInfo();

    friend ostream &operator<<(ostream &os, const PicInfo &picInfo);

    static string to_str(PicType picType);
    static string to_str(PicFormat picFormat);

    int id;

    PicType type;   //orig, resize
    PicFormat format; //jpg, png, webm, mp4
    QString url;
    QString name;

    QString res;    // 1024x768
    QString size;   // KB
    int done;
};

#endif // PICINFO_H
