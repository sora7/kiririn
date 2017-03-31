#include "mishimmieparser.h"

MishimmieParser::MishimmieParser()
{
    this->m_http_prefix  = "https://";
    this->m_site_url     = "shimmie.katawa-shoujo.com";
    this->m_query_prefix = "/post/list/";
    this->m_query_tag_sep    = " ";
    this->m_query_suffix = "/1";
    this->m_tags_max     = 0;

//    <div id='paginator'>   <b>1</b> <a href='/post/list/hanako/2'>2</a>
    this->m_rxNextPage = QRegExp("<div id='paginator'>.+<b>\\d+</b>.+<a href='(/post/list/.+/\\d+)'>\\d+</a>");
    this->m_rxNextPage.setMinimal(true);
//    <a href='/post/view/4549?search=hanako'>
    this->m_rxPost     = QRegExp("<a href='(/post/view/\\d*[?]search=.+)'>");
    this->m_rxPost.setMinimal(true);

    QString orig = "<img id='main_image' src='http://shimmie.katawa-shoujo.com"
                   "(/image/([0-9]*.([a-z0-9]{3,4})))'></div>";
    this->m_rxOrig = QRegExp(orig);
}

MishimmieParser::~MishimmieParser()
{
}

QString MishimmieParser::name()
{
    return katawa::fullname;
}
