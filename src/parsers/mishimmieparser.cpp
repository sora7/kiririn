#include "mishimmieparser.h"

MishimmieParser::MishimmieParser()
{
    this->_http_prefix  = "https://";
    this->_site_url     = "shimmie.katawa-shoujo.com";
    this->_query_prefix = "/post/list/";
    this->_query_tag_sep    = " ";
    this->_query_suffix = "/1";
    this->_tags_max     = 0;

//    <div id='paginator'>   <b>1</b> <a href='/post/list/hanako/2'>2</a>
    this->_rxNextPage = QRegExp("<div id='paginator'>.+<b>\\d+</b>.+<a href='(/post/list/.+/\\d+)'>\\d+</a>");
    this->_rxNextPage.setMinimal(true);
//    <a href='/post/view/4549?search=hanako'>
    this->_rxPost     = QRegExp("<a href='(/post/view/\\d*[?]search=.+)'>");
    this->_rxPost.setMinimal(true);

    QString orig = "<img id='main_image' src='http://shimmie.katawa-shoujo.com"
                   "(/image/([0-9]*.([a-z0-9]{3,4})))'></div>";
    this->_rxOrig = QRegExp(orig);
}

MishimmieParser::~MishimmieParser()
{
}

QString MishimmieParser::name()
{
    return katawa::fullname;
}
