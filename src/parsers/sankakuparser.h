#ifndef SANKAKUPARSER_H
#define SANKAKUPARSER_H

#include "parsers/booruparser.h"

//sankaku channel
//idol complex
class SankakuParser : public BooruParser
{
public:
    SankakuParser();
    ~SankakuParser();

private:
    QStringList getPosts(QString htmlText);

    QRegExp _rxPopular;
};

#endif // SANKAKUPARSER_H
