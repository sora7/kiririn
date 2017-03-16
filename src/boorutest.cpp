#include "boorutest.h"

BooruTest::BooruTest(QString booru)
{
    this->_booru = booru;
    if (booru == "sankaku") {
        this->parser = new SankakuParser();
    }
    if (booru == "katawa") {
        this->parser = new MishimmieParser();
    }
    if (booru == "4chan") {
        this->parser = new FourChanHouseParser();
    }
    if (booru == "idol") {
        this->parser = new IdolComplexParser();
    }
    if (booru == "konachan") {
        this->parser = new KonachanParser();
    }
}

BooruTest::~BooruTest()
{
    delete this->parser;
}

void BooruTest::load(QString type, QString url)
{
    QString fname;
    int datasetCount = 1;
    while (QFile::exists(fname = datasetFilename(type, datasetCount))) {
        datasetCount++;
    }

    Loader loader;
    loader.loadFile(url, fname);
}

void BooruTest::test(QString type, int datasetN)
{
    if (datasetN == 0) {
        int count = 1;
        while (QFile::exists( datasetFilename(type, count) )) {
            this->test(type, count);
            count++;
        }
    }
    else {
        cout << "Dataset #" << datasetN << endl;
        QString fname = datasetFilename(type, datasetN);
        if (type == "search") {
            SearchInfo sinfo =  parser->parseSearch(Parser::readFile(fname));
            cout << sinfo << endl;
        }
        else {
            PostInfo pinfo =  parser->parsePost(Parser::readFile(fname));
            cout << pinfo << endl;
        }
    }
}

QString BooruTest::datasetFilename(QString type, int datasetN)
{
    //    filename template
    //    %booru%_%type%_%datasetN%.txt
    return this->_booru + "_" + type + "_" + QString::number(datasetN) + ".txt";
}
