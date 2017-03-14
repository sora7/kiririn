#include "parser.h"

Parser::Parser()
{
}

Parser::~Parser()
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

QString Parser::readFile(QString filename)
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

PicFormat Parser::checkFormat(QString str)
{
    if (str == "jpg") {
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

SearchInfo Parser::parseSearch(QString htmlText)
{
    SearchInfo searchInfo;

    searchInfo.setNextPage(getNextPage(htmlText));
    searchInfo.setPosts(getPosts(htmlText));

    return searchInfo;
}

PostInfo Parser::parsePost(QString htmlText)
{
    PostInfo postInfo;

    postInfo.setRating( getRating(htmlText) );
    postInfo.setPics( getPics(htmlText) );

    return postInfo;
}

QStringList Parser::findall(QString text, QString regex, int pos_shift, QString prefix)
{
    QStringList result;
    QRegExp rx(regex);
    rx.setMinimal(true);

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
