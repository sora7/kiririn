#ifndef FOURCHANHOUSEPARSER_H
#define FOURCHANHOUSEPARSER_H

#include "parsers/shimmieparser.h"

namespace fourchan {
    const QString fullname = "4chan House";
    const QString shortname = "4chan";
}

class FourChanHouseParser : public ShimmieParser
{
public:
    FourChanHouseParser();
    ~FourChanHouseParser();

    QString name();
};

#endif // FOURCHANHOUSEPARSER_H
