#ifndef BOORUPARSER_H
#define BOORUPARSER_H

#include <QFile>

#include <QRegExp>
#include <QStringList>

#include "items/postinfo.h"
#include "items/searchinfo.h"

using namespace std;

//struct booru_data {
//    QString http_prefix;
//    QString site_url;
//    QString query_prefix;
//    QString query_tag_sep;
//    QString query_suffix;
//    int tags_max;

//    QString rx_next;
//    QString rx_post;

//    QString rx_orig;
//    QString rx_orig2;
//    QString rx_resize;

//    QString rx_rating;
//};

class BooruParser
{
public:
    BooruParser();
    virtual ~BooruParser();

    virtual QString name() = 0;

    static QString readFile(QString filename);
    //============================================//
    SearchInfo parseSearch(QString htmlText);
    PostInfo parsePost(QString htmlText);
    virtual QString genQueryUrl(QStringList tags);
    //============================================//
protected:
    QString _http_prefix;
    QString _site_url;
    QString _query_prefix;
    QString _query_tag_sep;
    QString _query_suffix;
    int _tags_max;

    void setNext(QString nextRegexStr);
    void setPost(QString postRegexStr);

    void setOrig(QString origRegexStr);
    void setResize(QString resizeRegexStr);

    void setRating(QString ratingRegexStr);

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
        SankakuChannel      *
        IdolComplex         *
        Konachan            *
        Yande.re            *
        Safebooru           *
        Danbooru            *
        Gelbooru            *
        Zerochan
        Minitokyo
        kpop.asiachan.com
    Shimmie-alike:
        Mishimmie           *   ' '
        4chanhouse          *   '+'
    Other:
        favim.ru                ',' as tag separator '+' as whitespace
*/
