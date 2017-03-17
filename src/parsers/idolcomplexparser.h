#ifndef IDOLCOMPLEXPARSER_H
#define IDOLCOMPLEXPARSER_H

#include "parsers/sankakuparser.h"

namespace idol {
    const QString fullname = "Idol Complex";
    const QString shortname = "idol";
}

class IdolComplexParser : public SankakuParser
{
public:
    IdolComplexParser();
    ~IdolComplexParser();

    QString name();
};

#endif // IDOLCOMPLEXPARSER_H
