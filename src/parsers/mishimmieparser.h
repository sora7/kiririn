#ifndef MISHIMMIEPARSER_H
#define MISHIMMIEPARSER_H

#include "parsers/shimmieparser.h"

namespace katawa {
    const QString fullname = "Mishimmie";
    const QString shortname = "katawa";
}

class MishimmieParser : public ShimmieParser
{
public:
    MishimmieParser();
    ~MishimmieParser();

    QString name();

    static QString fullname();
    static QString shortname();

    QString genQueryUrl(QStringList tags);

private:
    QString getNextPage(QString htmlText);
    QStringList getPosts(QString htmlText);

    QList<PicInfo> getPics(QString htmlText);
};

#endif // MISHIMMIEPARSER_H
