#ifndef SAFEBOORUPARSER_H
#define SAFEBOORUPARSER_H

#include "parsers/gelbooruparser.h"

namespace safebooru {
    const QString fullname = "Safebooru";
    const QString shortname = "safebooru";
}

class SafebooruParser : public GelbooruParser
{
public:
    SafebooruParser();
    ~SafebooruParser();

    QString name();
};

#endif // SAFEBOORUPARSER_H
