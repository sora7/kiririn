#ifndef LOADER_H
#define LOADER_H

#include <string>
#include <iostream>

#include <cstdio>
#include <cstdlib>
#include <time.h>

#include <QString>

// delay function using QCoreApplication::processEvents
#define DELAY_Q
// delay function using QThread
//#define DELAY_T

#ifdef DELAY_Q
#include <QTime>
#include <QCoreApplication>
#endif

#ifdef DELAY_T
#include <QThread>
#endif

#include <curl/curl.h>

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

#ifdef DELAY_T
class Sleeper : public QThread
{
public:
    static void msleep(unsigned long msec) { QThread::msleep(msec); }
};
#endif

void delay(int millisec);
int rand_gap(int from, int to);

#endif // LOADER_H
