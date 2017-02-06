#ifndef SANKAKUPARSER_H
#define SANKAKUPARSER_H

#include <QRegExp>
#include <QStringList>

#include "parsers/parser.h"

class SankakuParser : public Parser
{
public:
    SankakuParser();
    ~SankakuParser();

    QString genQueryUrl(QStringList tags);

private:
    QString getNextPage(QString htmlText);
    QStringList getPosts(QString htmlText);

    QList<PicInfo> getPics(QString htmlText);
    QString getRating(QString htmlText);
};

#endif // SANKAKUPARSER_H
