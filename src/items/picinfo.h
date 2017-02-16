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



//    QString res;    // 1024x768
//    QString size;   // KB
//    int done;

    int getId() const;
    void setId(int value);
    PicType getType() const;
    void setType(const PicType &value);
    PicFormat getFormat() const;
    void setFormat(const PicFormat &value);
    QString getUrl() const;
    void setUrl(const QString &value);
    QString getName() const;
    void setName(const QString &value);
private:
    int _id;

    PicType _type;   //orig, resize
    PicFormat _format; //jpg, png, webm, mp4

    QString _url;
    QString _name;
};

#endif // PICINFO_H
