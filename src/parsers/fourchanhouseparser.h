#ifndef FOURCHANHOUSEPARSER_H
#define FOURCHANHOUSEPARSER_H

#include "parsers/shimmieparser.h"

namespace fourchan {
    const QString fullname = "4chan House";
    const QString shortname = "4chan";
}

class FourChanHouseParser : public ShimmieParser
{
public:
    FourChanHouseParser();
    ~FourChanHouseParser();

    QString name();
    static QString fullname();
    static QString shortname();

    QString genQueryUrl(QStringList tags);
private:
    QString getNextPage(QString htmlText);
    QStringList getPosts(QString htmlText);

    QList<PicInfo> getPics(QString htmlText);
};

#endif // FOURCHANHOUSEPARSER_H
