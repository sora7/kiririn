#include "sankakuparser.h"

SankakuParser::SankakuParser()
{
    this->m_http_prefix = "https://";

    this->m_query_prefix = "/?tags=";
    this->m_query_tag_sep = "+";
    this->m_query_suffix = "&commit=Search";
    this->m_tags_max = 4;

    this->_rxPopular  = QRegExp("id=more-popular-link>");

    QString next = "next-page-url=\"([^ ]*)\"";
    this->setNext(next);
//    this->_rxNextPage = QRegExp(next);
//    this->_rxNextPage.setMinimal(true);
    QString post = "><a href=\"(/post/show/\\d*)\"";
    this->setPost(post);
//    this->_rxPost = QRegExp(post);
//    this->_rxPost.setMinimal(true);
//    <li>Rating: Safe</li>
//    <li>Rating: Questionable</li>
//    <li>Rating: Explicit</li>
    QString rating = "<li>Rating: (Safe|Questionable|Explicit)</li>";
//    this->_rxRating = QRegExp(rating);
    this->setRating(rating);
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

    QString prefix = this->m_http_prefix + this->m_site_url;
    QStringList postsList = findall(htmlText,
                                    this->m_rxPost,
                                    position_popular,
                                    prefix);

    return postsList;
}
