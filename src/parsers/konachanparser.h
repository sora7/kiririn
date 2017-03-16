#ifndef KONACHANPARSER_H
#define KONACHANPARSER_H

#include "parsers/parser.h"

class KonachanParser : public Parser
{
public:
    KonachanParser();
    ~KonachanParser();

    QString genQueryUrl(QStringList tags);

private:
    QString getNextPage(QString htmlText);
    QStringList getPosts(QString htmlText);

    QList<PicInfo> getPics(QString htmlText);
    PostRating getRating(QString htmlText);
};

#endif // KONACHANPARSER_H
