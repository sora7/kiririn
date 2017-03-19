#include "gelbooruparser.h"

GelbooruParser::GelbooruParser()
{
    this->_http_prefix = "http://";
    this->_site_url = "gelbooru.com";

    this->_query_prefix = "/index.php?page=post&s=list&tags=";
    this->_query_tag_sep = "+";
    this->_query_suffix = "";
    this->_tags_max = 0;
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

//    <li><a href="//simg4.gelbooru.com//images/1b/f1/1bf1cf176c99ca7c534e84593ab70bf8.png" style="font-weight: bold;">Original image</a></li>
    QString orig = "<li><a href=\"//((?:simg[0-9]{1,}[.]){0,1}gelbooru.com//images/[a-z0-9]{2}/[a-z0-9]{2}/([a-z0-9]*[.]([a-z0-9]{3,4})))\".*>Original image</a></li>";
    this->_rxOrig = QRegExp(orig);
    this->_rxOrig.setMinimal(true);

//    <img data-original-width="1063" data-original-height="992" alt="1girl :d animal_hood artist_name ass ayakura_juu belt bike_shorts bike_shorts_under_shorts boots bra bunny_hood crop_top eyebrows eyebrows_visible_through_hair falling fingerless_gloves full_body gloves hair_ornament hairclip holding hood hood_down hoodie legs_up looking_at_viewer mask mask_removed midriff navel official_art open_mouth purple_bra purple_eyes purple_hair round_teeth short_hair_with_long_locks short_sleeves shorts sidelocks simple_background smile solo teeth underwear vocaloid voiceroid watermark white_background yuzuki_yukari" height="793" src="//simg4.gelbooru.com//samples/a8/3a/sample_a83a22a8fc3e55e584950c5e0db1a5be.jpg" id="image" width="850"/>
    QString resize = "<.*alt=\".*\".*src=\"//((?:simg[0-9]{1,}[.]){0,1}gelbooru.com//samples/[a-z0-9]{2}/[a-z0-9]{2}/(sample_[a-z0-9]*[.]([a-z0-9]{3,4})))\" id=\"image\".*/>";
//    QString resize = "<img.*id=\"image\".*src=\"(/data/sample/(.*[.]([a-z0-9]{3,4})))\" />";
    this->_rxResize = QRegExp(resize);
    this->_rxResize.setMinimal(true);
}

GelbooruParser::~GelbooruParser()
{

}

QString GelbooruParser::name()
{
    return gelbooru::fullname;
}

QString GelbooruParser::getNextPage(QString htmlText)
{
    QString nextPage;

    int pos = this->_rxNextPage.indexIn(htmlText);
    if (pos > -1) {
        QString nextFound = this->_rxNextPage.cap(1);
        nextFound.replace("&amp;", "&");
        nextPage = this->_http_prefix + this->_site_url + "/index.php" + nextFound;
    }

    return nextPage;
}

QStringList GelbooruParser::getPosts(QString htmlText)
{
    cout << "posts booru" << endl;
    QString prefix = this->_http_prefix + this->_site_url + "/";
    QStringList postsList = findall(htmlText, this->_rxPost, 0, prefix);

    return postsList;
}

QStringList GelbooruParser::findall(QString text, QRegExp rx, int pos_shift,
                                 QString prefix)
{
    QStringList result;

    int i = 0;

    int pos = pos_shift;
    while ((pos = rx.indexIn(text, pos)) != -1) {
        i++;
        //cout << "FOUND: #" << i << " " << rx.cap(1).toStdString() << endl;
        QString found = rx.cap(1);
        found.replace("&amp;", "&");
        result << prefix + found;
        pos += rx.matchedLength();
    }

    return result;
}
