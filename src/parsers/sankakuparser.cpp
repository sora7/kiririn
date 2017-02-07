#include "sankakuparser.h"

SankakuParser::SankakuParser()
{
}

SankakuParser::~SankakuParser()
{
}

QString SankakuParser::genQueryUrl(QStringList tags)
{
    QString queryUrl("https://chan.sankakucomplex.com/?tags=");

    const int TAGS_MAX = 4;
    const QString TAGS_SEP = "+";

    QStringList slice = tags.mid(0, TAGS_MAX);
    queryUrl += slice.join(TAGS_SEP);

    queryUrl += "&commit=Search";
    return queryUrl;
}

QString SankakuParser::getNextPage(QString htmlText)
{
    QString nextPage;

    QRegExp rxNextPage("next-page-url=\"([^ ]*)\"");
    int pos = rxNextPage.indexIn(htmlText);
    if (pos > -1) {
        nextPage = "https://chan.sankakucomplex.com" + rxNextPage.cap(1);
    }

    return nextPage;
}

QStringList SankakuParser::getPosts(QString htmlText)
{
//    shift position below the popular section
    QRegExp rx2("id=more-popular-link>");
    int position_popular = rx2.indexIn(htmlText, 0);

    // if there are no popular section start from 0
    if (position_popular < 0) {
        position_popular = 0;
    }

    QString post_regex = "><a href=\"(/post/show/\\d*)\"";
    QString prefix = "https://chan.sankakucomplex.com";

    QStringList postsList = findall(htmlText, post_regex, position_popular, prefix);

    return postsList;
}

QList<PicInfo> SankakuParser::getPics(QString htmlText)
{
    QList<PicInfo> pics;

    //    //cs.sankakucomplex.com/data/a5/3b/a53b563b373665e84d300c701067c4f0.jpg?3595399
//<li>Original: <a href="//cs.sankakucomplex.com/data/a5/3b/a53b563b373665e84d300c701067c4f0.jpg?3595399" id=highres itemprop=contentUrl title="300,906 bytes">1024x1483 (293.9 KB)</a></li>

    QRegExp rxOrig("Original: <a href=\"(//cs.sankakucomplex.com/data/"
                   "[a-z0-9]{2}/[a-z0-9]{2}/([a-z0-9]{32}."
                   "([a-z0-9]{3,4}))\\?[0-9]+)\".+>"
                   "([0-9]{1,}x[0-9]{1,}) [(](.+)[)].+</a></li>");
    rxOrig.setMinimal(true);//lazy quantifiers, qt you suck

    int pos = rxOrig.indexIn(htmlText);
    if (pos > -1) {
        QString origUrl  = rxOrig.cap(1);
        QString origName = rxOrig.cap(2);
        QString origExt  = rxOrig.cap(3);
        QString origRes  = rxOrig.cap(4);
        QString origSize = rxOrig.cap(5);

        PicInfo picInfo;
        picInfo.type   = ORIGINAL;
        picInfo.name   = origName;
        picInfo.format = checkFormat( origExt );
        picInfo.url    = "https:" + origUrl;
        picInfo.size   = origSize;
        picInfo.res    = origRes;

        pics << picInfo;
//        cout << picInfo << endl;;
    }
//    <li>Resized: <a href="//cs.sankakucomplex.com/data/sample/a5/3b/sample-a53b563b373665e84d300c701067c4f0.jpg?3595399" id=lowres>690x1000</a></li>

    QRegExp rxResize("Resized: <a href=\"(//cs.sankakucomplex.com/data/sample/"
                     "[a-z0-9]{2}/[a-z0-9]{2}/(sample-[a-z0-9]{32}."
                     "([a-z0-9]{3,4}))\\?[0-9]+)\".+>([0-9]{1,}x[0-9]{1,})"
                     ".+</a></li>");
    rxResize.setMinimal(true);
    pos = rxResize.indexIn(htmlText);
    if (pos > -1) {
        QString resUrl  = rxResize.cap(1);
        QString resName = rxResize.cap(2);
        QString resExt  = rxResize.cap(3);
        QString resRes  = rxResize.cap(4);

        PicInfo picInfo2;
        picInfo2.type   = RESIZED;
        picInfo2.name   = resName;
        picInfo2.format = checkFormat( resExt );
        picInfo2.url    = "https:" + resUrl;
        picInfo2.res    = resRes;

        pics << picInfo2;
    }
    return pics;
}

PostRating SankakuParser::getRating(QString htmlText)
{
    PostRating rating;

//    <li>Rating: Safe</li>
//    <li>Rating: Questionable</li>
//    <li>Rating: Explicit</li>

    QRegExp rxRating("<li>Rating: (Safe|Questionable|Explicit)</li>");
    int pos = rxRating.indexIn(htmlText);
    if (pos > -1) {
        if (rxRating.cap(1) == "Safe"){
            rating = SAFE;
        }
        if (rxRating.cap(1) == "Questionable"){
            rating = QUESTIONABLE;
        }
        if (rxRating.cap(1) == "Explicit"){
            rating = EXPLICIT;
        }
    }
    return rating;
}
