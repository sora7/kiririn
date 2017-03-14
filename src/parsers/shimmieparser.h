#ifndef SHIMMIEPARSER_H
#define SHIMMIEPARSER_H

#include "parsers/parser.h"

class ShimmieParser : public Parser
{
public:
    ShimmieParser();
    ~ShimmieParser();
private:
    PostRating getRating(QString htmlText);
};

#endif // SHIMMIEPARSER_H
