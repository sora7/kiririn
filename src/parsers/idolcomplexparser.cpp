#include "idolcomplexparser.h"

IdolComplexParser::IdolComplexParser()
{
    this->_site_url = "idol.sankakucomplex.com";
//    <li>Original: <a href="//is.sankakucomplex.com/data/e3/b5/e3b5e792cfdb1de24f7ec1b9f37d3f08.jpg?663736" id=highres itemprop=contentUrl title="1,801,410 bytes">3404x5100 (1.7 MB)</a></li>
    QString orig = "Original: <a href=\"//(is.sankakucomplex.com/data/"
                   "[a-z0-9]{2}/[a-z0-9]{2}/([a-z0-9]{32}."
                   "([a-z0-9]{3,4}))\\?[0-9]+)\".+>";
    this->_rxOrig = QRegExp(orig);
//    <li>Resized: <a href="//is.sankakucomplex.com/data/sample/e3/b5/sample-e3b5e792cfdb1de24f7ec1b9f37d3f08.jpg?663736" id=lowres>667x1000</a></li>
    QString resize = "Resized: <a href=\"//(is.sankakucomplex.com/data/sample/"
                     "[a-z0-9]{2}/[a-z0-9]{2}/(sample-[a-z0-9]{32}."
                     "([a-z0-9]{3,4}))\\?[0-9]+)\".+>";
    this->_rxResize = QRegExp(resize);
}

IdolComplexParser::~IdolComplexParser()
{

}

QString IdolComplexParser::name()
{
    return idol::fullname;
}
