#include "mishimmieparser.h"

MishimmieParser::MishimmieParser()
{
}

MishimmieParser::~MishimmieParser()
{
}

QString MishimmieParser::genQueryUrl(QStringList tags)
{
    QString queryUrl("https://shimmie.katawa-shoujo.com/post/list/");

//    const int TAGS_MAX = 4;
    const QString TAGS_SEP = " ";

//    QStringList slice = tags.mid(0, TAGS_MAX);
    queryUrl += tags.join(TAGS_SEP);

    queryUrl += "/1";
    return queryUrl;
}

QString MishimmieParser::getNextPage(QString htmlText)
{
    QString nextPage;
//    <div id='paginator'>   <b>1</b> <a href='/post/list/hanako/2'>2</a>

    QRegExp rxNextPage("<div id='paginator'>.+<b>\\d+</b>.+<a href='(/post/list/.+/\\d+)'>\\d+</a>");
    rxNextPage.setMinimal(true);
    int pos = rxNextPage.indexIn(htmlText);
    if (pos > -1) {
        nextPage = "https://shimmie.katawa-shoujo.com" + rxNextPage.cap(1);
    }

//    nextPage = "LOL";

    return nextPage;
}

QStringList MishimmieParser::getPosts(QString htmlText)
{
    QStringList postsList;

//    <a href='/post/view/4549?search=hanako'>

    QString post_regex = "<a href='(/post/view/\\d*[?]search=.+)'>";
    QString prefix = "https://shimmie.katawa-shoujo.com";

    postsList = findall(htmlText, post_regex, 0, prefix);



    return postsList;
}

QList<PicInfo> MishimmieParser::getPics(QString htmlText)
{
    QList<PicInfo> pics;
//    QRegExp rxExt = "";

    QRegExp rxOrig("<img id='main_image' src='(http://shimmie.katawa-shoujo.com"
                   "/image/([0-9]*.([a-z0-9]{3,4})))'></div>");
    rxOrig.setMinimal(true);//lazy quantifiers, qt you suck

    int pos = rxOrig.indexIn(htmlText);
    if (pos > -1) {
        QString origUrl  = rxOrig.cap(1);
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

PostRating MishimmieParser::getRating(QString htmlText)
{
    return RT_OTHER;
}
