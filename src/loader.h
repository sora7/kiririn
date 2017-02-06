#ifndef LOADER_H
#define LOADER_H

#include <string>
#include <iostream>

#include <cstdio>
#include <cstdlib>
#include <time.h>

#include <QString>
#include <QTime>
#include <QCoreApplication>

#include "curl/curl.h"

using namespace std;

const string DEFAULT_UA = "Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:42.0) Gecko/20100101 Firefox/42.0";

class Loader
{
public:
    Loader();

    QString loadHtml(QString url);

    void loadFile(QString url, QString filename);

private:

};

void delay(int millisec);
int rand_gap(int from, int to);

#endif // LOADER_H
