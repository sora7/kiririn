#ifndef BOORUPARSER_H
#define BOORUPARSER_H

#include <QFile>

#include <QRegExp>
#include <QStringList>

#include "items/postinfo.h"
#include "items/searchinfo.h"

using namespace std;

class BooruParser
{
public:
    BooruParser();
    ~BooruParser();

    virtual QString name() = 0;

    static QString readFile(QString filename);
    SearchInfo parseSearch(QString htmlText);
    PostInfo parsePost(QString htmlText);
    //============================================//
    virtual QString genQueryUrl(QStringList tags);
    //============================================//
protected:
    QString _http_prefix;
    QString _site_url;
    QString _query_prefix;
    QString _query_sep;
    QString _query_suffix;
    int _tags_max;

    QRegExp _rxNextPage;
    QRegExp _rxPost;

    QRegExp _rxOrig;
    QRegExp _rxResize;

    QRegExp _rxRating;

    QStringList findall(QString text, QRegExp rx, int pos_shift=0, QString prefix="");
    PicFormat checkFormat(QString str);
    //============================================//
    //search
    virtual QString getNextPage(QString htmlText);
    virtual QStringList getPosts(QString htmlText);
    //post
    virtual QList<PicInfo> getPics(QString htmlText);
    virtual PostRating getRating(QString htmlText);
    //============================================//
};

#endif // BOORUPARSER_H

/*
    Liste:

    Danbooru-alike:
        SankakuChannel  *
        IdolComplex     *
        Konachan        *
        Yande.re
        Safebooru
        Danbooru
        Gelbooru
    Shimmie-alike:
        Mishimmie       *
        4chanhouse      *
    Other:
        favim.ru
*/
