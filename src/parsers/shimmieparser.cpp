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

    int pos = this->m_rxOrig.indexIn(htmlText);
    if (pos > -1) {
        QString origUrl  = this->m_rxOrig.cap(1);
        QString origName = this->m_rxOrig.cap(2);
        QString origExt  = this->m_rxOrig.cap(3);

        PicInfo picInfo;
        picInfo.setType(ORIGINAL);
        picInfo.setName(origName);
        picInfo.setFormat( checkFormat( origExt ) );
        picInfo.setUrl( this->m_http_prefix + this->m_site_url + origUrl );

        pics << picInfo;
    }

    return pics;
}

PostRating ShimmieParser::getRating(QString htmlText)
{
    return RT_OTHER;
}
