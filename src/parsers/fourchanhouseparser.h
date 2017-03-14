#ifndef FOURCHANHOUSEPARSER_H
#define FOURCHANHOUSEPARSER_H

#include "parsers/shimmieparser.h"

class FourChanHouseParser : public ShimmieParser
{
public:
    FourChanHouseParser();
    ~FourChanHouseParser();

    QString genQueryUrl(QStringList tags);
private:
    QString getNextPage(QString htmlText);
    QStringList getPosts(QString htmlText);

    QList<PicInfo> getPics(QString htmlText);
};

#endif // FOURCHANHOUSEPARSER_H
