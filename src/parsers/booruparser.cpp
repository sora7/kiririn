#include "booruparser.h"

BooruParser::BooruParser()
{
}

BooruParser::~BooruParser()
{
}

//string Parser::readFile(string filename)
//{
//    ifstream t(filename.c_str());
//    string html_text;

//    t.seekg(0, ios::end);
//    html_text.reserve(t.tellg());
//    t.seekg(0, ios::beg);

//    html_text.assign(istreambuf_iterator<char>(t),
//                     istreambuf_iterator<char>()
//                     );
//    return html_text;
//}

QString BooruParser::readFile(QString filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
       return NULL;
    }

    QByteArray total;
    QByteArray line;
    while (!file.atEnd()) {
       line = file.read(1024);
       total.append(line);
    }

    return QString(total);
}

QString BooruParser::genQueryUrl(QStringList tags)
{
    QString queryUrl = this->m_http_prefix + this->m_site_url + this->m_query_prefix;

    QStringList slice;
    if (this->m_tags_max > 0) {
        slice = tags.mid(0, this->m_tags_max);
    }
    else {
        slice = tags;
    }
    queryUrl += slice.join(this->m_query_tag_sep);

    queryUrl += this->m_query_suffix;

    return queryUrl;
}

void BooruParser::setNext(QString nextRegexStr)
{
    this->m_rxNextPage = QRegExp(nextRegexStr);
    this->m_rxNextPage.setMinimal(true);
}

void BooruParser::setPost(QString postRegexStr)
{
    this->m_rxPost = QRegExp(postRegexStr);
    this->m_rxPost.setMinimal(true);
}

void BooruParser::setOrig(QString origRegexStr)
{
    this->m_rxOrig = QRegExp(origRegexStr);
    this->m_rxOrig.setMinimal(true);
}

void BooruParser::setResize(QString resizeRegexStr)
{
    this->m_rxResize = QRegExp(resizeRegexStr);
    this->m_rxResize.setMinimal(true);
}

void BooruParser::setRating(QString ratingRegexStr)
{
    this->m_rxRating = QRegExp(ratingRegexStr);
    this->m_rxRating.setMinimal(true);
}

PicFormat BooruParser::checkFormat(QString str)
{
    if (str == "jpg") {
        return JPG;
    }
    if (str == "jpeg") {
        return JPG;
    }
    if (str == "png") {
        return PNG;
    }
    if (str == "gif") {
        return GIF;
    }
    if (str == "webm") {
        return WEBM;
    }
    if (str == "mp4") {
        return MP4;
    }
    return UNDEFINED;
}

QString BooruParser::getNextPage(QString htmlText)
{
    QString nextPage;

    int pos = this->m_rxNextPage.indexIn(htmlText);
    if (pos > -1) {
        QString nextFound = this->m_rxNextPage.cap(1);
        nextPage = this->m_http_prefix + this->m_site_url + nextFound;
    }

    return nextPage;
}

QStringList BooruParser::getPosts(QString htmlText)
{
    QString prefix = this->m_http_prefix + this->m_site_url;
    QStringList postsList = findall(htmlText, this->m_rxPost, 0, prefix);

    return postsList;
}

QList<PicInfo> BooruParser::getPics(QString htmlText)
{
    QList<PicInfo> pics;

    this->m_rxOrig.setMinimal(true);//lazy quantifiers, qt you suck
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

    this->m_rxResize.setMinimal(true);
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

PostRating BooruParser::getRating(QString htmlText)
{
//    <li>Rating: Safe</li>
//    <li>Rating: Questionable</li>
//    <li>Rating: Explicit</li>
    int pos = this->m_rxRating.indexIn(htmlText);
    if (pos > -1) {
        if (this->m_rxRating.cap(1) == "Safe"){
            return SAFE;
        }
        if (this->m_rxRating.cap(1) == "Questionable"){
            return QUESTIONABLE;
        }
        if (this->m_rxRating.cap(1) == "Explicit"){
            return EXPLICIT;
        }
    }
    return RT_OTHER;
}

SearchInfo BooruParser::parseSearch(QString htmlText)
{
    SearchInfo searchInfo;

    searchInfo.setNextPage(getNextPage(htmlText));
    searchInfo.setPosts(getPosts(htmlText));

    return searchInfo;
}

PostInfo BooruParser::parsePost(QString htmlText)
{
    PostInfo postInfo;

    postInfo.setRating( getRating(htmlText) );
    postInfo.setPics( getPics(htmlText) );

    return postInfo;
}

QStringList BooruParser::findall(QString text, QRegExp rx, int pos_shift, QString prefix)
{
    QStringList result;

    int i = 0;

    int pos = pos_shift;
    while ((pos = rx.indexIn(text, pos)) != -1) {
        i++;
        //cout << "FOUND: #" << i << " " << rx.cap(1).toStdString() << endl;
        result << prefix + rx.cap(1);
        pos += rx.matchedLength();
    }

    return result;
}

//QString Parser::getOriginal(QString htmlText)
//{
//    QString result;
////    //cs.sankakucomplex.com/data/a5/3b/a53b563b373665e84d300c701067c4f0.jpg?3595399

//    QRegExp rxOrig("Original: <a href=\"(//cs.sankakucomplex.com/data/[a-z0-9]{2}/[a-z0-9]{2}/[a-z0-9]{32}.[a-z0-9]{3,4}\\?[0-9]*)\".*");
//    int pos = rxOrig.indexIn(htmlText);
//    if (pos > -1) {
//        QString origUrl = rxOrig.cap(1);
//        result =  "https:" + origUrl;
//    }

//    return result;
//}

//QString Parser::getResized(QString htmlText)
//{
////    //cs.sankakucomplex.com/data/sample/a5/3b/sample-a53b563b373665e84d300c701067c4f0.jpg?3595399
//    QString result;
//    QRegExp rxResized("Resized: <a href=\"(//cs.sankakucomplex.com/data/sample/[a-z0-9]{2}/[a-z0-9]{2}/sample-[a-z0-9]{32}.[a-z0-9]{3,4}\\?[0-9]*)\".*");
//    int pos = rxResized.indexIn(htmlText);
//    if (pos > -1) {
//        QString resizeUrl = rxResized.cap(1);
//        result = "https:" + resizeUrl;
//    }

//    return result;
//}
