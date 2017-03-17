#ifndef YANDEREPARSER_H
#define YANDEREPARSER_H

#include "parsers/konachanparser.h"

namespace yandere {
    const QString fullname = "Yande.re";
    const QString shortname = "yandere";
}

class YandeReParser : public KonachanParser
{
public:
    YandeReParser();
    ~YandeReParser();

    QString name();
};

#endif // YANDEREPARSER_H
