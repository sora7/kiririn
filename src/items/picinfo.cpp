#include "picinfo.h"

PicInfo::PicInfo()
{
//    this->done = 0;
}

PicInfo::~PicInfo()
{
}

string PicInfo::to_str(PicType picType)
{
    switch (picType) {
        case ORIGINAL: {
            return "original";
        }
        case RESIZED: {
            return "resized";
        }
    }
    return "";
}

string PicInfo::to_str(PicFormat picFormat)
{
    switch (picFormat) {
    case JPG: {
        return "JPG";
    }
    case PNG: {
        return "PNG";
    }
    case GIF: {
        return "GIF";
    }
    case WEBM: {
        return "WEBM";
    }
    case MP4: {
        return "MP4";
    }
    case UNDEFINED: {
        return "UNDEFINED";
    }
    }
    return "";
}

QString PicInfo::getName() const
{
    return _name;
}

void PicInfo::setName(const QString &value)
{
    _name = value;
}

QString PicInfo::getUrl() const
{
    return _url;
}

void PicInfo::setUrl(const QString &value)
{
    _url = value;
}

PicFormat PicInfo::getFormat() const
{
    return _format;
}

void PicInfo::setFormat(const PicFormat &value)
{
    _format = value;
}

PicType PicInfo::getType() const
{
    return _type;
}

void PicInfo::setType(const PicType &value)
{
    _type = value;
}

int PicInfo::getId() const
{
    return _id;
}

void PicInfo::setId(int value)
{
    _id = value;
}

ostream& operator <<(ostream &os, const PicInfo &picInfo)
{
    os << "url: " << picInfo._url.toStdString() << endl;
    os << "name: " << picInfo._name.toStdString() << endl;
    os << "type: " << PicInfo::to_str(picInfo._type);
    os << "\tformat: " << PicInfo::to_str(picInfo._format) << endl;
//    os << "\tresolution: " << picInfo.res.toStdString();
//    os << "\tsize: " << picInfo.size.toStdString() << endl;
    return os;
}
