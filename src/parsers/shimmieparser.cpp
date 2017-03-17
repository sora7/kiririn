#include "shimmieparser.h"

ShimmieParser::ShimmieParser()
{

}

ShimmieParser::~ShimmieParser()
{

}

QList<PicInfo> ShimmieParser::getPics(QString htmlText)
{
    QList<PicInfo> pics;

    int pos = this->_rxOrig.indexIn(htmlText);
    if (pos > -1) {
        QString origUrl  = this->_rxOrig.cap(1);
        QString origName = this->_rxOrig.cap(2);
        QString origExt  = this->_rxOrig.cap(3);

        PicInfo picInfo;
        picInfo.setType(ORIGINAL);
        picInfo.setName(origName);
        picInfo.setFormat( checkFormat( origExt ) );
        picInfo.setUrl( this->_http_prefix + this->_site_url + origUrl );

        pics << picInfo;
    }

    return pics;
}

PostRating ShimmieParser::getRating(QString htmlText)
{
    return RT_OTHER;
}
