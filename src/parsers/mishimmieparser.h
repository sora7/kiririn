#ifndef MISHIMMIEPARSER_H
#define MISHIMMIEPARSER_H

#include "parsers/shimmieparser.h"

class MishimmieParser : public ShimmieParser
{
public:
    MishimmieParser();
    ~MishimmieParser();

    QString genQueryUrl(QStringList tags);

private:
    QString getNextPage(QString htmlText);
    QStringList getPosts(QString htmlText);

    QList<PicInfo> getPics(QString htmlText);
};

#endif // MISHIMMIEPARSER_H
