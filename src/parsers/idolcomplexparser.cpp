#include "idolcomplexparser.h"

IdolComplexParser::IdolComplexParser()
{
}

IdolComplexParser::~IdolComplexParser()
{

}

QString IdolComplexParser::name()
{
    return idol::fullname;
}

QString IdolComplexParser::genQueryUrl(QStringList tags)
{
    QString queryUrl("https://idol.sankakucomplex.com/?tags=");

    const int TAGS_MAX = 4;
    const QString TAGS_SEP = "+";

    QStringList slice = tags.mid(0, TAGS_MAX);
    queryUrl += slice.join(TAGS_SEP);

    queryUrl += "&commit=Search";
    return queryUrl;
}

QString IdolComplexParser::getNextPage(QString htmlText)
{
    QString nextPage;

    QRegExp rxNextPage("next-page-url=\"([^ ]*)\"");
    int pos = rxNextPage.indexIn(htmlText);
    if (pos > -1) {
        nextPage = "https://idol.sankakucomplex.com" + rxNextPage.cap(1);
    }

    return nextPage;
}

QStringList IdolComplexParser::getPosts(QString htmlText)
{
    //    shift position below the popular section
        QRegExp rx2("id=more-popular-link>");
        int position_popular = rx2.indexIn(htmlText, 0);

        // if there are no popular section start from 0
        if (position_popular < 0) {
            position_popular = 0;
        }

        QString post_regex = "><a href=\"(/post/show/\\d*)\"";
        QString prefix = "https://idol.sankakucomplex.com";

        QStringList postsList = findall(htmlText, post_regex, position_popular, prefix);

        return postsList;
}

QList<PicInfo> IdolComplexParser::getPics(QString htmlText)
{
    QList<PicInfo> pics;

    //    //cs.sankakucomplex.com/data/a5/3b/a53b563b373665e84d300c701067c4f0.jpg?3595399
//<li>Original: <a href="//is.sankakucomplex.com/data/e3/b5/e3b5e792cfdb1de24f7ec1b9f37d3f08.jpg?663736" id=highres itemprop=contentUrl title="1,801,410 bytes">3404x5100 (1.7 MB)</a></li>

    QRegExp rxOrig("Original: <a href=\"(//is.sankakucomplex.com/data/"
                   "[a-z0-9]{2}/[a-z0-9]{2}/([a-z0-9]{32}."
                   "([a-z0-9]{3,4}))\\?[0-9]+)\".+>");
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
//    <li>Resized: <a href="//is.sankakucomplex.com/data/sample/e3/b5/sample-e3b5e792cfdb1de24f7ec1b9f37d3f08.jpg?663736" id=lowres>667x1000</a></li>

    QRegExp rxResize("Resized: <a href=\"(//is.sankakucomplex.com/data/sample/"
                     "[a-z0-9]{2}/[a-z0-9]{2}/(sample-[a-z0-9]{32}."
                     "([a-z0-9]{3,4}))\\?[0-9]+)\".+>");
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

PostRating IdolComplexParser::getRating(QString htmlText)
{
    //    <li>Rating: Safe</li>
    //    <li>Rating: Questionable</li>
    //    <li>Rating: Explicit</li>

        QRegExp rxRating("<li>Rating: (Safe|Questionable|Explicit)</li>");
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
