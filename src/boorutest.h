#ifndef BOORUTEST_H
#define BOORUTEST_H


#include "loader.h"
#include "parsers/sankakuparser.h"
#include "parsers/mishimmieparser.h"
#include "parsers/fourchanhouseparser.h"
#include "parsers/idolcomplexparser.h"
#include "parsers/konachanparser.h"

class BooruTest
{
public:
    BooruTest();
    ~BooruTest();

    void setBooru(QString shortname);
    void load(QString type, QString url);
//    dataset == 0: test all datasets
    void test(QString type, int datasetN=0);

    void testing();
private:
    QString _booru;
    Parser* parser;

    QString testFilename(QString type, int datasetN);
};

#endif // BOORUTEST_H
