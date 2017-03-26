#ifndef BOORUTEST_H
#define BOORUTEST_H

#include <QObject>
#include <QQueue>

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

class BooruTest : public QObject
{
    Q_OBJECT
public:
    explicit BooruTest(QObject *parent = 0);
    ~BooruTest();

    void setBooru(QString shortname);
    void setType(QString type);
    void load(QStringList urlList);

//    dataset == 0: test all datasets
    void test(int datasetN=0);

    void testing();
public slots:
    void load_finish();
private:
    QString _booru;
    QString m_type;
    BooruParser* parser;

    Loader* m_loader;
    QQueue<QString> m_urlList;

    void load_start(QString url);

    QString testFilename(int datasetN);
};

#endif // BOORUTEST_H
