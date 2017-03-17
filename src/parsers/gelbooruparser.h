#ifndef GELBOORUPARSER_H
#define GELBOORUPARSER_H

#include "parsers/booruparser.h"

namespace gelbooru {
    const QString fullname = "Gelbooru";
    const QString shortname = "gelbooru";
}

class GelbooruParser : public BooruParser
{
public:
    GelbooruParser();
    ~GelbooruParser();

    QString name();

    QString getNextPage(QString htmlText);
    QStringList getPosts(QString htmlText);
    QStringList findall(QString text, QRegExp rx, int pos_shift=0, QString prefix="");
};

#endif // GELBOORUPARSER_H
