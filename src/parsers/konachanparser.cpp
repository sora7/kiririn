#include "konachanparser.h"

KonachanParser::KonachanParser()
{
    this->m_site_url = "konachan.com";
    this->m_http_prefix = "https://";
    this->m_query_prefix = "/post?tags=";
    this->m_query_tag_sep = "+";
    this->m_query_suffix = "";
    this->m_tags_max = 6;
//    rel="next" href="/post?page=2&amp;tags=yuigahama_yui">
    this->m_rxNextPage = QRegExp("rel=\"next\" href=\"(/post[?]page=\\d+&amp;tags=.*)\">");
    this->m_rxNextPage.setMinimal(true);
//    <a class="thumb" href="/post/show/191270/black_eyes-black_hair-inanaki_shiki-long_hair-pant" ><img src=
    this->m_rxPost     = QRegExp("<a class=\"thumb\" href=\"(/post/show/\\d+/.*)\" ><img src=");
    this->m_rxPost.setMinimal(true);

//    <li>Rating: Safe
//    <li>Rating: Questionable
//    <li>Rating: Explicit
    this->m_rxRating   = QRegExp("<li>Rating: (Safe|Questionable|Explicit) ");
    this->m_rxRating.setMinimal(true);

//    <li><a class="original-file-changed" href="//konachan.com/jpeg/5f496e2abd1cd3277c832ddf040bd354/Konachan.com%20-%20234649%20blush%20close%20gradient%20hikigaya_komachi%20short_hair%20tagme_%28artist%29%20vector%20yahari_ore_no_seishun_love_come_wa_machigatteiru..jpg" id="highres">Download larger version (525 KB JPG)</a>
    QString orig = "<li><a class=\"original-file-changed\" href=\"//(konachan.com/jpeg/[a-z0-9]*/(.*[.]([a-z0-9]{3,4})))\".*</a>";
    this->m_rxOrig = QRegExp(orig);
    this->m_rxOrig.setMinimal(true);

//    <li><a class="original-file-unchanged" href="//konachan.com/image/5f496e2abd1cd3277c832ddf040bd354/Konachan.com%20-%20234649%20blush%20close%20gradient%20hikigaya_komachi%20short_hair%20tagme_%28artist%29%20vector%20yahari_ore_no_seishun_love_come_wa_machigatteiru..png" id="png">Download PNG (3.16 MB)</a>
    QString orig2 = "<li><a class=\"original-file-.{0,2}changed\" href=\"//(konachan.com/image/[a-z0-9]*/(.*[.]([a-z0-9]{3,4})))\" id=\".*\">.*</a>";
    this->_rxOrig2 = QRegExp(orig2);
    this->_rxOrig2.setMinimal(true);

//    <img alt="heirou saikyougui_no_dark_hero tagme_(character)" class="image" height="1072" id="image" large_height="2048" large_width="2866" src="//konachan.com/sample/3e2e2edde836a807c7d6ab0b059d7cd7/Konachan.com%20-%20238379%20sample.jpg" width="1500" />
    QString resize = "<img.*src=\"//(konachan.com/sample/[a-z0-9]*/(.*sample[.]([a-z0-9]{3,4})))\".* />";
    this->m_rxResize = QRegExp(resize);
    this->m_rxResize.setMinimal(true);
}

KonachanParser::~KonachanParser()
{

}

QString KonachanParser::name()
{
    return konachan::fullname;
}

QList<PicInfo> KonachanParser::getPics(QString htmlText)
{
//    cout << "booru pics" << endl;
    QList<PicInfo> pics;

    int pos = this->m_rxOrig.indexIn(htmlText);
    if (pos > -1) {
        QString origUrl  = this->m_rxOrig.cap(1);
        QString origName = this->m_rxOrig.cap(2);
        QString origExt  = this->m_rxOrig.cap(3);

        PicInfo picInfo;
        picInfo.setType(ORIGINAL);
        picInfo.setName(origName);
        picInfo.setFormat( checkFormat( origExt ) );
        picInfo.setUrl( this->m_http_prefix + origUrl );

        pics << picInfo;
    }

    pos = this->_rxOrig2.indexIn(htmlText);
    if (pos > -1) {
        QString origUrl  = this->_rxOrig2.cap(1);
        QString origName = this->_rxOrig2.cap(2);
        QString origExt  = this->_rxOrig2.cap(3);

        PicInfo picInfo3;
        picInfo3.setType(ORIGINAL);
        picInfo3.setName(origName);
        picInfo3.setFormat( checkFormat( origExt ) );
        picInfo3.setUrl( this->m_http_prefix + origUrl );

        pics << picInfo3;
    }

    pos = this->m_rxResize.indexIn(htmlText);
    if (pos > -1) {
        QString resUrl  = this->m_rxResize.cap(1);
        QString resName = this->m_rxResize.cap(2);
        QString resExt  = this->m_rxResize.cap(3);

        PicInfo picInfo2;
        picInfo2.setType(RESIZED);
        picInfo2.setName(resName);
        picInfo2.setFormat( checkFormat( resExt ) );
        picInfo2.setUrl( this->m_http_prefix + resUrl );

        pics << picInfo2;
    }
    return pics;
}
