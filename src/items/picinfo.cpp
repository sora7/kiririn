#include "picinfo.h"

PicInfo::PicInfo()
{
    this->done = 0;
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
    }
}

ostream& operator <<(ostream &os, const PicInfo &picInfo)
{
    os << "url: " << picInfo.url.toStdString() << endl;
    os << "name: " << picInfo.name.toStdString() << endl;
    os << "type: " << PicInfo::to_str(picInfo.type);
    os << "\tformat: " << PicInfo::to_str(picInfo.format);
    os << "\tresolution: " << picInfo.res.toStdString();
    os << "\tsize: " << picInfo.size.toStdString() << endl;
    return os;
}
