#include "picinfo.h"

PicInfo::PicInfo()
{
    this->done = 0;
}

PicInfo::~PicInfo()
{
}

ostream& operator <<(ostream &os, const PicInfo &picInfo)
{
    os << "url: " << picInfo.url.toStdString() << endl;
    os << "name: " << picInfo.name.toStdString() << endl;
    os << "type: " << picInfo.type.toStdString();
    os << "\tformat: " << picInfo.format.toStdString();
    os << "\tresolution: " << picInfo.res.toStdString();
    os << "\tsize: " << picInfo.size.toStdString() << endl;
    return os;
}
