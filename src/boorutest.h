#ifndef BOORUTEST_H
#define BOORUTEST_H


#include "loader.h"
#include "parsers/sankakuparser.h"
#include "parsers/mishimmieparser.h"

class BooruTest
{
public:
    BooruTest(QString booru);
    ~BooruTest();

    void load(QString type, QString url);

//    dataset == 0: test all datasets
    void test(QString type, int datasetN=0);
private:
    QString _booru;
    Parser* parser;

    QString datasetFilename(QString type, int datasetN);
};

#endif // BOORUTEST_H
