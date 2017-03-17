#include "danbooruparser.h"

DanbooruParser::DanbooruParser()
{
    this->_http_prefix = "http://";
    this->_site_url = "danbooru.donmai.us";

    this->_query_prefix = "/posts?utf8=✓&tags=";
    this->_query_sep = "+";
    this->_query_suffix = "&ms=1";
    this->_tags_max = 2;
//    <li><a rel="next" href="/posts?ms=1&amp;page=2&amp;tags=megumin+thighhighs&amp;utf8=%E2%9C%93">&gt;&gt;</a></li>
//    <a rel="next" href="/posts?page=2&amp;tags=chomusuke">
//    <a rel="next" href="/posts?ms=1&amp;page=2&amp;tags=chomusuke&amp;utf8=%D0%B2%D1%9A%E2%80%9C">
    this->_rxNextPage = QRegExp("<a rel=\"next\" href=\"(/posts[?].{0,}page=\\d+&amp;tags=.*)\">");
    this->_rxNextPage.setMinimal(true);
//    <a href="/posts/2661171"><img itemprop="thumbnailUrl" src="
    this->_rxPost = QRegExp("<a href=\"(/posts/\\d+)\"><img itemprop=\"thumbnailUrl\" src=\"");
    this->_rxPost.setMinimal(true);
//    <li>Rating: Safe</li>
//    <li>Rating: Questionable</li>
//    <li>Rating: Explicit</li>
    this->_rxRating   = QRegExp("<li>Rating: (Safe|Questionable|Explicit)</li>");


//    Size: <a href="/data/__aqua_kono_subarashii_sekai_ni_shukufuku_wo_drawn_by_tomifumi__a4f83e79ecdcb7ef37883bc9dfaac025.jpg">635 KB</a>
    QString orig = "Size: <a href=\"(/data/(.*[.]([a-z0-9]{3,4})))\">.*</a>";
    this->_rxOrig = QRegExp(orig);
}

DanbooruParser::~DanbooruParser()
{

}

QString DanbooruParser::name()
{
    return danbooru::fullname;
}

QList<PicInfo> DanbooruParser::getPics(QString htmlText)
{
//    cout << "booru pics" << endl;
    QList<PicInfo> pics;

    this->_rxOrig.setMinimal(true);
    int pos = this->_rxOrig.indexIn(htmlText);
    if (pos > -1) {
        QString origUrl  = this->_rxOrig.cap(1);
        QString origName = this->_rxOrig.cap(2);
        QString origExt  = this->_rxOrig.cap(3);

        PicInfo picInfo;
        picInfo.setType(ORIGINAL);
        picInfo.setName(origName);
        picInfo.setFormat( checkFormat( origExt ) );
        picInfo.setUrl( this->_http_prefix + this->_site_url + origUrl );

        pics << picInfo;
    }
    return pics;
}
