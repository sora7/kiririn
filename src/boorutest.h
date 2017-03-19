#ifndef BOORUTEST_H
#define BOORUTEST_H


#include "loader.h"
#include "parsers/sankakuchannelparser.h"
#include "parsers/mishimmieparser.h"
#include "parsers/fourchanhouseparser.h"
#include "parsers/idolcomplexparser.h"
#include "parsers/konachanparser.h"
#include "parsers/yandereparser.h"
#include "parsers/danbooruparser.h"
#include "parsers/gelbooruparser.h"
#include "parsers/safebooruparser.h"

class BooruTest
{
public:
    BooruTest();
    ~BooruTest();

    void setBooru(QString shortname);
    void load(QString type, QString url);
    void load(QString type, QStringList urlList);
//    dataset == 0: test all datasets
    void test(QString type, int datasetN=0);

    void testing();
private:
    QString _booru;
    BooruParser* parser;

    QString testFilename(QString type, int datasetN);
};

#endif // BOORUTEST_H
