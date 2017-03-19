#include "safebooruparser.h"

SafebooruParser::SafebooruParser()
{
    this->_http_prefix = "https://";
    this->_site_url = "safebooru.org";

    this->_query_prefix = "/index.php?page=post&s=list&tags=";
    this->_query_sep = "+";
    this->_query_suffix = "";
    this->_tags_max = 0;
//    <b>6</b> <a href="?page=post&amp;s=list&amp;tags=seifuku&amp;pid=240">
//    <b>1</b> <a href="?page=post&amp;s=list&amp;tags=ayakura_juu+1girl&amp;pid=42">
    this->_rxNextPage = QRegExp("<b>\\d{1,}</b> <a href=\"([?]page=post&amp;s=list&amp;tags=.*&amp;pid=\\d+)\">");
    this->_rxNextPage.setMinimal(true);
//    <span id="s3568555" class="thumb"><a id="p3568555" href="index.php?page=post&amp;s=view&amp;id=3568555" ><img
    this->_rxPost = QRegExp("<span id=\"s\\d+\" class=\"thumb\"><a id=\"p\\d+\" href=\"(index.php[?]page=post&amp;s=view&amp;id=\\d+)\" ><img");
    this->_rxPost.setMinimal(true);
//    <li>Rating: Safe</li>
//    <li>Rating: Questionable</li>
//    <li>Rating: Explicit</li>
    this->_rxRating   = QRegExp("<li>Rating: (Safe|Questionable|Explicit)</li>");

//    <li><a href="//safebooru.org//images/1361/1c1c2323bbfba4ebba9da18f5e8b048137384c12.png"
    QString orig = "<li><a href=\"//(safebooru.org//images/[0-9]*/([a-z0-9]*[.]([a-z0-9]{3,4})))\"";
    this->_rxOrig = QRegExp(orig);
    this->_rxOrig.setMinimal(true);

//    <img alt="1girl absurdres bangs black_eyes black_hair black_serafuku black_shirt black_skirt blunt_bangs bullet cartridge fingernails from_side gun handgun highres holding holding_gun holding_weapon jong_hyun_jeon lipstick long_sleeves makeup neckerchief nose open_mouth original pistol pleated_skirt red_lips red_lipstick sailor_collar school_uniform serafuku shirt short_hair simple_background skirt skirt_set smile solo teeth teeth_hold trigger_discipline upper_body weapon white_background" height="1032" src="//safebooru.org//samples/2084/sample_4d27b4a18795f8ccdf2efb3f8a90cbf7d65af3c6.jpg?2173464" id="image" onclick="Note.toggle();" width="850"/><br /><div style="margin-bottom: 1em;">
    QString resize = "<img alt=\".*\".*src=\"//(safebooru.org//samples/[0-9]+/(sample_[a-z0-9]*[.]([a-z0-9]{3,4}))[?][0-9]+)\" id=\"image\"";
    this->_rxResize = QRegExp(resize);
    this->_rxResize.setMinimal(true);
}

SafebooruParser::~SafebooruParser()
{

}

QString SafebooruParser::name()
{
    return safebooru::fullname;
}
