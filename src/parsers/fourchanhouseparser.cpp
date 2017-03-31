#include "fourchanhouseparser.h"

FourChanHouseParser::FourChanHouseParser()
{
//    https://shimmie.4chanhouse.org/index.php?q=/post/list/jp/1
//    4chanhouse owners, you are really bastrards
//    DO NOT USE WHITESPACE " " AS A SEPARATOR
    this->m_http_prefix  = "https://";
    this->m_site_url     = "shimmie.4chanhouse.org";
    this->m_query_prefix = "/index.php?q=/post/list/";
    this->m_query_tag_sep    = "+";
    this->m_query_suffix = "/1";
    this->m_tags_max     = 0;

//    <div id='paginator'>   <b>1</b> <a href='./index.php?q=/post/list/jp/2'>2</a>
    this->m_rxNextPage = QRegExp("<div id='paginator'>.+<b>\\d+</b>.+<a href='[.](/index[.]php[?]q=/post/list/.+/\\d+)'>\\d+</a>");
    this->m_rxNextPage.setMinimal(true);

//    <a href='./index.php?q=/post/view/6554&search=jp'>
//    <a href='./index.php?q=/post/view/2804&search=conrad%20jp'>
    this->m_rxPost     = QRegExp("<a href='[.](/index[.]php[?]q=/post/view/\\d+[&]search=[^ ]*)'>");
    this->m_rxPost.setMinimal(true);

//    <img id='main_image' src='./index.php?q=/image/5717.png'></div>
    QString orig = "<img id='main_image' src='[.](/index.php[?]q=/image/([0-9]*.([a-z0-9]{3,4})))'></div>";
    this->m_rxOrig = QRegExp(orig);
    this->m_rxOrig.setMinimal(true);
}

FourChanHouseParser::~FourChanHouseParser()
{
}

QString FourChanHouseParser::name()
{
    return fourchan::fullname;
}
