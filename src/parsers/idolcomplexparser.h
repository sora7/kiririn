#ifndef IDOLCOMPLEXPARSER_H
#define IDOLCOMPLEXPARSER_H

#include "parsers/parser.h"

class IdolComplexParser : public Parser
{
public:
    IdolComplexParser();
    ~IdolComplexParser();

    QString genQueryUrl(QStringList tags);

private:
    QString getNextPage(QString htmlText);
    QStringList getPosts(QString htmlText);

    QList<PicInfo> getPics(QString htmlText);
    PostRating getRating(QString htmlText);
};

#endif // IDOLCOMPLEXPARSER_H
