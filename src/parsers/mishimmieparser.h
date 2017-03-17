#ifndef MISHIMMIEPARSER_H
#define MISHIMMIEPARSER_H

#include "parsers/shimmieparser.h"

namespace katawa {
    const QString fullname = "Mishimmie";
    const QString shortname = "katawa";
}

class MishimmieParser : public ShimmieParser
{
public:
    MishimmieParser();
    ~MishimmieParser();

    QString name();
};

#endif // MISHIMMIEPARSER_H
