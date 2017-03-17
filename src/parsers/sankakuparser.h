#ifndef SANKAKUPARSER_H
#define SANKAKUPARSER_H

#include "parsers/parser.h"

namespace sankaku {
    const QString fullname = "Sankaku Channel";
    const QString shortname = "sankaku";
}

class SankakuParser : public Parser
{
public:
    SankakuParser();
    ~SankakuParser();

    QString name();

    QString genQueryUrl(QStringList tags);

private:
    QString getNextPage(QString htmlText);
    QStringList getPosts(QString htmlText);

    QList<PicInfo> getPics(QString htmlText);
    PostRating getRating(QString htmlText);
};

#endif // SANKAKUPARSER_H
