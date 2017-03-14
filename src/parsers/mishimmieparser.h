#ifndef MISHIMMIEPARSER_H
#define MISHIMMIEPARSER_H

#include "parsers/parser.h"

class MishimmieParser : public Parser
{
public:
    MishimmieParser();
    ~MishimmieParser();

    QString genQueryUrl(QStringList tags);

private:
    QString getNextPage(QString htmlText);
    QStringList getPosts(QString htmlText);

    QList<PicInfo> getPics(QString htmlText);
    PostRating getRating(QString htmlText);
};

#endif // MISHIMMIEPARSER_H
