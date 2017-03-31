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
    int m_id;

    PicType m_type;   //orig, resize
    PicFormat m_format; //jpg, png, webm, mp4

    QString m_url;
    QString m_name;
};

#endif // PICINFO_H
