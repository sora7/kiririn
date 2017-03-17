#ifndef KONACHANPARSER_H
#define KONACHANPARSER_H

#include "parsers/parser.h"

namespace konachan {
    const QString fullname = "Konachan";
    const QString shortname = "konachan";
}

class KonachanParser : public Parser
{
public:
    KonachanParser();
    ~KonachanParser();

    QString name();

    QString genQueryUrl(QStringList tags);

private:
    QString getNextPage(QString htmlText);
    QStringList getPosts(QString htmlText);

    QList<PicInfo> getPics(QString htmlText);
    PostRating getRating(QString htmlText);
};

#endif // KONACHANPARSER_H
