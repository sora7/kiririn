#include "sankakuchannelparser.h"

SankakuChannelParser::SankakuChannelParser()
{
    this->m_site_url = "chan.sankakucomplex.com";
//    <li>Original: <a href="//cs.sankakucomplex.com/data/a5/3b/a53b563b373665e84d300c701067c4f0.jpg?3595399" id=highres itemprop=contentUrl title="300,906 bytes">1024x1483 (293.9 KB)</a></li>

    QString orig = "Original: <a href=\"//(cs.sankakucomplex.com/data/"
                   "[a-z0-9]{2}/[a-z0-9]{2}/([a-z0-9]{32}."
                   "([a-z0-9]{3,4}))\\?[0-9]+)\".+>";
    this->setOrig(orig);
//    this->_rxOrig = QRegExp(orig);
//    <li>Resized: <a href="//cs.sankakucomplex.com/data/sample/a5/3b/sample-a53b563b373665e84d300c701067c4f0.jpg?3595399" id=lowres>690x1000</a></li>
    QString resize = "Resized: <a href=\"//(cs.sankakucomplex.com/data/sample/"
                     "[a-z0-9]{2}/[a-z0-9]{2}/(sample-[a-z0-9]{32}."
                     "([a-z0-9]{3,4}))\\?[0-9]+)\".+>";
    this->setResize(resize);
//    this->_rxResize = QRegExp(resize);
}

SankakuChannelParser::~SankakuChannelParser()
{
}

QString SankakuChannelParser::name()
{
    return sankaku::fullname;
}
