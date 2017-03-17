#include "konachanparser.h"

KonachanParser::KonachanParser()
{
    this->_site_url = "konachan.com";

    this->_http_prefix = "https://";

    this->_query_prefix = "/post?tags=";
    this->_query_sep = "+";
    this->_query_suffix = "";
    this->_tags_max = 0;
//    rel="next" href="/post?page=2&amp;tags=yuigahama_yui">
    this->_rxNextPage = QRegExp("rel=\"next\" href=\"(/post[?]page=\\d+&amp;tags=.*)\">");
    this->_rxNextPage.setMinimal(true);
//    <a class="thumb" href="/post/show/191270/black_eyes-black_hair-inanaki_shiki-long_hair-pant" ><img src=
    this->_rxPost     = QRegExp("<a class=\"thumb\" href=\"(/post/show/\\d+/.*)\" ><img src=");
    this->_rxPost.setMinimal(true);

//    <li>Rating: Safe
//    <li>Rating: Questionable
//    <li>Rating: Explicit
    this->_rxRating   = QRegExp("<li>Rating: (Safe|Questionable|Explicit) ");
    this->_rxRating.setMinimal(true);

//    <li><a class="original-file-unchanged" href="//konachan.com/image/5f496e2abd1cd3277c832ddf040bd354/Konachan.com%20-%20234649%20blush%20close%20gradient%20hikigaya_komachi%20short_hair%20tagme_%28artist%29%20vector%20yahari_ore_no_seishun_love_come_wa_machigatteiru..png" id="png">Download PNG (3.16 MB)</a>
    QString orig = "<li><a class=\"original-file-.{0,2}changed\" href=\"//(konachan.com/image/[a-z0-9]*/(.*[.]([a-z0-9]{3,4})))\" id=\".*\">.*</a>";
    this->_rxOrig = QRegExp(orig);
//    <li><a class="original-file-changed" href="//konachan.com/jpeg/5f496e2abd1cd3277c832ddf040bd354/Konachan.com%20-%20234649%20blush%20close%20gradient%20hikigaya_komachi%20short_hair%20tagme_%28artist%29%20vector%20yahari_ore_no_seishun_love_come_wa_machigatteiru..jpg" id="highres">Download larger version (525 KB JPG)</a>
    QString resize = "<li><a class=\"original-file-changed\" href=\"//(konachan.com/jpeg/[a-z0-9]*/(.*[.]([a-z0-9]{3,4})))\".*</a>";
    this->_rxResize = QRegExp(resize);
}

KonachanParser::~KonachanParser()
{

}

QString KonachanParser::name()
{
    return konachan::fullname;
}
