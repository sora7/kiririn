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
    return m_name;
}

void PicInfo::setName(const QString &value)
{
    m_name = value;
}

QString PicInfo::getUrl() const
{
    return m_url;
}

void PicInfo::setUrl(const QString &value)
{
    m_url = value;
}

PicFormat PicInfo::getFormat() const
{
    return m_format;
}

void PicInfo::setFormat(const PicFormat &value)
{
    m_format = value;
}

PicType PicInfo::getType() const
{
    return m_type;
}

void PicInfo::setType(const PicType &value)
{
    m_type = value;
}

int PicInfo::getId() const
{
    return m_id;
}

void PicInfo::setId(int value)
{
    m_id = value;
}

ostream& operator <<(ostream &os, const PicInfo &picInfo)
{
    os << "url: " << picInfo.m_url.toStdString() << endl;
    os << "name: " << picInfo.m_name.toStdString() << endl;
    os << "type: " << PicInfo::to_str(picInfo.m_type);
    os << "\tformat: " << PicInfo::to_str(picInfo.m_format) << endl;
//    os << "\tresolution: " << picInfo.res.toStdString();
//    os << "\tsize: " << picInfo.size.toStdString() << endl;
    return os;
}
