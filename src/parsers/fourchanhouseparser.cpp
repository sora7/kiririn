#include "fourchanhouseparser.h"

FourChanHouseParser::FourChanHouseParser()
{

}

FourChanHouseParser::~FourChanHouseParser()
{

}

QString FourChanHouseParser::genQueryUrl(QStringList tags)
{
//    https://shimmie.4chanhouse.org/index.php?q=/post/list/jp/1
    QString queryUrl("https://shimmie.4chanhouse.org/index.php?q=/post/list/");

//    4chanhouse owners, you are really bastrards
    const QString TAGS_SEP = "+";
//    DO NOT USE WHITESPACE " "

    queryUrl += tags.join(TAGS_SEP);

    queryUrl += "/1";
    return queryUrl;
}

QString FourChanHouseParser::getNextPage(QString htmlText)
{
    QString nextPage;
//    <div id='paginator'>   <b>1</b> <a href='./index.php?q=/post/list/jp/2'>2</a>

    QRegExp rxNextPage("<div id='paginator'>.+<b>\\d+</b>.+<a href='[.](/index[.]php[?]q=/post/list/.+/\\d+)'>\\d+</a>");

//    QRegExp rxNextPage("<div id='paginator'>.+<b>\\d+</b>.+<a href='[.](/index[.]php[?]q=/post/list/.+/\\d+)'>\\d+</a>");
    rxNextPage.setMinimal(true);
    int pos = rxNextPage.indexIn(htmlText);
    if (pos > -1) {
        nextPage = "https://shimmie.4chanhouse.org" + rxNextPage.cap(1);
    }
    return nextPage;
}

QStringList FourChanHouseParser::getPosts(QString htmlText)
{
    QStringList postsList;

//    <a href='./index.php?q=/post/view/6554&search=jp'>
//    <a href='./index.php?q=/post/view/2804&search=conrad%20jp'>
//    QString post_regex = "<a href='[.](/index[.]php[?]q=/post/view/\\d+[&]search=.+)'>";
    QString post_regex = "<a href='[.](/index[.]php[?]q=/post/view/\\d+[&]search=[^ ]*)'>";
    QString prefix = "https://shimmie.4chanhouse.org";

    postsList = findall(htmlText, post_regex, 0, prefix);

    return postsList;
}

QList<PicInfo> FourChanHouseParser::getPics(QString htmlText)
{
    QList<PicInfo> pics;
//    <img id='main_image' src='./index.php?q=/image/5717.png'></div>
    QRegExp rxOrig("<img id='main_image' src='[.](/index.php[?]q=/image/([0-9]*.([a-z0-9]{3,4})))'></div>");
    rxOrig.setMinimal(true);

    int pos = rxOrig.indexIn(htmlText);
    if (pos > -1) {
        QString origUrl  = "https://shimmie.4chanhouse.org" + rxOrig.cap(1);
        QString origName = rxOrig.cap(2);
        QString origExt  = rxOrig.cap(3);
//        QString origRes  = rxOrig.cap(4);
//        QString origSize = rxOrig.cap(5);

        PicInfo picInfo;
        picInfo.setType(ORIGINAL);
        picInfo.setName(origName);
        picInfo.setFormat( checkFormat( origExt ) );
        picInfo.setUrl( origUrl );

//        picInfo.size   = origSize;
//        picInfo.res    = origRes;

        pics << picInfo;
//        cout << picInfo << endl;
    }

    return pics;
}
