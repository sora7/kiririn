#ifndef PARSER_H
#define PARSER_H

#include <QFile>

#include <QRegExp>
#include <QStringList>

#include "items/postinfo.h"
#include "items/searchinfo.h"

using namespace std;

class Parser
{
public:
    Parser();
    ~Parser();

    static QString readFile(QString filename);

    virtual QString genQueryUrl(QStringList tags) = 0;
    SearchInfo parseSearch(QString htmlText);
    PostInfo parsePost(QString htmlText);

protected:
    QStringList findall(QString text, QString regex, int pos_shift=0, QString prefix="");
    PicFormat checkFormat(QString str);

    //search
    virtual QString getNextPage(QString htmlText) = 0;
    virtual QStringList getPosts(QString htmlText) = 0;
    //post
    virtual QList<PicInfo> getPics(QString htmlText) = 0;
    virtual PostRating getRating(QString htmlText) = 0;
};

#endif // PARSER_H

/*
    Liste:

    Danbooru-alike:
        SankakuChannel *
        Konachan
        Yande.re
        Safebooru
        Danbooru
        Gelbooru
    Shimmie-alike:
        Mishimmie      ?
        4chanhouse
    Other:
        favim.ru
*/
