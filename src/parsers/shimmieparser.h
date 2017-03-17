#ifndef SHIMMIEPARSER_H
#define SHIMMIEPARSER_H

#include "parsers/booruparser.h"

//mishimmie
//4chan house
class ShimmieParser : public BooruParser
{
public:
    ShimmieParser();
    ~ShimmieParser();
private:
    PostRating getRating(QString htmlText);
    QList<PicInfo> getPics(QString htmlText);
};

#endif // SHIMMIEPARSER_H
