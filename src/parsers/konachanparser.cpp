#include "konachanparser.h"

KonachanParser::KonachanParser()
{

}

KonachanParser::~KonachanParser()
{

}

QString KonachanParser::genQueryUrl(QStringList tags)
{
    QString queryUrl("https://konachan.com/post?tags=");

//    const int TAGS_MAX = 4;
    const QString TAGS_SEP = "+";

//    QStringList slice = tags.mid(0, TAGS_MAX);
    queryUrl += tags.join(TAGS_SEP);

    return queryUrl;
}

QString KonachanParser::getNextPage(QString htmlText)
{
    QString nextPage;
//rel="next" href="/post?page=2&amp;tags=yuigahama_yui">
    QRegExp rxNextPage("rel=\"next\" href=\"(/post[?]page=\\d+&amp;tags=.*)\">");
    rxNextPage.setMinimal(true);
    int pos = rxNextPage.indexIn(htmlText);
    if (pos > -1) {
        nextPage = "https://konachan.com" + rxNextPage.cap(1);
    }

    return nextPage;
}

QStringList KonachanParser::getPosts(QString htmlText)
{
//<a class="thumb" href="/post/show/191270/black_eyes-black_hair-inanaki_shiki-long_hair-pant" ><img src=

    QString post_regex = "<a class=\"thumb\" href=\"(/post/show/\\d+/.*)\" ><img src=";
    QString prefix = "https://konachan.com";

    QStringList postsList = findall(htmlText, post_regex, 0, prefix);

    return postsList;
}

QList<PicInfo> KonachanParser::getPics(QString htmlText)
{
    QList<PicInfo> pics;

//    <li><a class="original-file-unchanged" href="//konachan.com/image/5f496e2abd1cd3277c832ddf040bd354/Konachan.com%20-%20234649%20blush%20close%20gradient%20hikigaya_komachi%20short_hair%20tagme_%28artist%29%20vector%20yahari_ore_no_seishun_love_come_wa_machigatteiru..png" id="png">Download PNG (3.16 MB)</a>
    QRegExp rxOrig("<li><a class=\"original-file-.{0,2}changed\" href=\"(//konachan.com/image/[a-z0-9]*/(.*[.]([a-z0-9]{3,4})))\" id=\".*\">.*</a>");
    rxOrig.setMinimal(true);

    int pos = rxOrig.indexIn(htmlText);
    if (pos > -1) {
        QString origUrl  = rxOrig.cap(1);
        QString origName = rxOrig.cap(2);
        QString origExt  = rxOrig.cap(3);

        PicInfo picInfo;
        picInfo.setType(ORIGINAL);
        picInfo.setName(origName);
        picInfo.setFormat( checkFormat( origExt ) );
        picInfo.setUrl( "https:" + origUrl );

        pics << picInfo;
    }
//<li><a class="original-file-changed" href="//konachan.com/jpeg/5f496e2abd1cd3277c832ddf040bd354/Konachan.com%20-%20234649%20blush%20close%20gradient%20hikigaya_komachi%20short_hair%20tagme_%28artist%29%20vector%20yahari_ore_no_seishun_love_come_wa_machigatteiru..jpg" id="highres">Download larger version (525 KB JPG)</a>

    QRegExp rxResize("<li><a class=\"original-file-changed\" href=\"(//konachan.com/jpeg/[a-z0-9]*/(.*[.]([a-z0-9]{3,4})))\".*</a>");
    rxResize.setMinimal(true);
    pos = rxResize.indexIn(htmlText);
    if (pos > -1) {
        QString resUrl  = rxResize.cap(1);
        QString resName = rxResize.cap(2);
        QString resExt  = rxResize.cap(3);


        PicInfo picInfo2;
        picInfo2.setType(RESIZED);
        picInfo2.setName(resName);
        picInfo2.setFormat( checkFormat( resExt ) );
        picInfo2.setUrl( "https:" + resUrl );

        pics << picInfo2;
    }
    return pics;
}

PostRating KonachanParser::getRating(QString htmlText)
{
    //    <li>Rating: Safe</li>
    //    <li>Rating: Questionable</li>
    //    <li>Rating: Explicit</li>
//<li>Rating: Safe
        QRegExp rxRating("<li>Rating: (Safe|Questionable|Explicit) ");
        int pos = rxRating.indexIn(htmlText);
        if (pos > -1) {
            if (rxRating.cap(1) == "Safe"){
                return SAFE;
            }
            if (rxRating.cap(1) == "Questionable"){
                return QUESTIONABLE;
            }
            if (rxRating.cap(1) == "Explicit"){
                return EXPLICIT;
            }
        }
        return RT_OTHER;
}
