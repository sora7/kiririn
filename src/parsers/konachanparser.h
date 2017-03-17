#ifndef KONACHANPARSER_H
#define KONACHANPARSER_H

#include "parsers/booruparser.h"

namespace konachan {
    const QString fullname = "Konachan";
    const QString shortname = "konachan";
}

class KonachanParser : public BooruParser
{
public:
    KonachanParser();
    ~KonachanParser();

    QString name();

    QList<PicInfo> getPics(QString htmlText);

protected:
    QRegExp _rxOrig2;
};

#endif // KONACHANPARSER_H
