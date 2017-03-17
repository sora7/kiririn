#ifndef DANBOORUPARSER_H
#define DANBOORUPARSER_H

#include "parsers/booruparser.h"

namespace danbooru {
    const QString fullname = "Danbooru";
    const QString shortname = "danbooru";
}

class DanbooruParser : public BooruParser
{
public:
    DanbooruParser();
    ~DanbooruParser();

    QList<PicInfo> getPics(QString htmlText);

    QString name();
};

#endif // DANBOORUPARSER_H
