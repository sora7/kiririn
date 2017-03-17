#include "sankakuparser.h"

SankakuParser::SankakuParser()
{
    this->_http_prefix = "https://";

    this->_query_prefix = "/?tags=";
    this->_query_sep = "+";
    this->_query_suffix = "&commit=Search";
    this->_tags_max = 4;

    this->_rxPopular  = QRegExp("id=more-popular-link>");

    this->_rxNextPage = QRegExp("next-page-url=\"([^ ]*)\"");
    this->_rxNextPage.setMinimal(true);
    this->_rxPost     = QRegExp("><a href=\"(/post/show/\\d*)\"");
    this->_rxPost.setMinimal(true);
//    <li>Rating: Safe</li>
//    <li>Rating: Questionable</li>
//    <li>Rating: Explicit</li>
    this->_rxRating   = QRegExp("<li>Rating: (Safe|Questionable|Explicit)</li>");
}

SankakuParser::~SankakuParser()
{
}

QStringList SankakuParser::getPosts(QString htmlText)
{
    cout << "sankaku" << endl;
    // shift position below the popular section
    int position_popular = this->_rxPopular.indexIn(htmlText, 0);

    // if there are no popular section start from 0
    if (position_popular < 0) {
        position_popular = 0;
    }

    QString prefix = this->_http_prefix + this->_site_url;
    QStringList postsList = findall(htmlText, this->_rxPost, position_popular, prefix);

    return postsList;
}
