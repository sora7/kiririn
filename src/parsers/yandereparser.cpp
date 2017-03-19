#include "yandereparser.h"

YandeReParser::YandeReParser()
{
    this->_site_url = "yande.re";
    this->_http_prefix = "https://";
    this->_query_prefix = "/post?tags=";
    this->_query_tag_sep = "+";
    this->_query_suffix = "";
    this->_tags_max = 6;
//    rel="next" href="/post?page=2&amp;tags=yuigahama_yui">
    this->_rxNextPage = QRegExp("rel=\"next\" href=\"(/post[?]page=\\d+&amp;tags=.*)\">");
    this->_rxNextPage.setMinimal(true);
//    <a class="thumb" href="/post/show/377779" ><img
    this->_rxPost     = QRegExp("<a class=\"thumb\" href=\"(/post/show/\\d+)\" ><img src=");
    this->_rxPost.setMinimal(true);

//    <li>Rating: Safe
//    <li>Rating: Questionable
//    <li>Rating: Explicit
    this->_rxRating   = QRegExp("<li>Rating: (Safe|Questionable|Explicit) ");
    this->_rxRating.setMinimal(true);

//    <a class="original-file-changed" id="highres" href="https://files.yande.re/jpeg/5019c744568e2c27d5278f48b2b12bf2/yande.re%20386461%20cheerleader%20cleavage%20executor%20headphones%20kunikida_hanamaru%20love_live%21_sunshine%21%21%20siva.%20tsushima_yoshiko.jpg">Download larger version (888 KB JPG)</a>
    QString orig = "<a class=\"original-file-changed\".*href=\"https://(files.yande.re/jpeg/[a-z0-9]*/(.*[.]([a-z0-9]{3,4})))\">.*</a>";
    this->_rxOrig = QRegExp(orig);
    this->_rxOrig.setMinimal(true);

//    <li><a class="original-file-unchanged" id="png" href="https://files.yande.re/image/5019c744568e2c27d5278f48b2b12bf2/yande.re%20386461%20cheerleader%20cleavage%20executor%20headphones%20kunikida_hanamaru%20love_live%21_sunshine%21%21%20siva.%20tsushima_yoshiko.png">Download PNG (4.42 MB)</a>
    QString orig2 = "<li><a class=\"original-file-unchanged\".*href=\"https://(files.yande.re/image/[a-z0-9]*/(.*[.]([a-z0-9]{3,4})))\">.*</a>";
    this->_rxOrig2 = QRegExp(orig2);
    this->_rxOrig2.setMinimal(true);

//  <link rel="image_src" href="https://files.yande.re/sample/a13c355e56ccd8f825fd5aedcc385a0b/yande.re%20386510%20sample%20bikini%20cleavage%20dress_shirt%20see_through%20shimamura_uzuki%20swimsuits%20the_idolm%40ster%20the_idolm%40ster_cinderella_girls%20wet_clothes%20yohan1754.jpg" />
    QString resize = "<link rel=\"image_src\" href=\"https://(files.yande.re/sample/[a-z0-9]*/(.*[.]([a-z0-9]{3,4})))\" />";
    this->_rxResize = QRegExp(resize);
    this->_rxResize.setMinimal(true);
}

YandeReParser::~YandeReParser()
{

}

QString YandeReParser::name()
{
    return yandere::fullname;
}
