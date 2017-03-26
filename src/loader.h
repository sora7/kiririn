#ifndef LOADER_H
#define LOADER_H

#include <iostream>

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSslConfiguration>
#include <QTextCodec>

using namespace std;

const QString DEFAULT_UA = "Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:42.0) "
                           "Gecko/20100101 Firefox/42.0";

class Loader : public QObject
{
    Q_OBJECT
public:
    explicit Loader(QString url, QObject *parent = 0);
    virtual ~Loader();
    QByteArray downloadedData() const;
    QString getHtml() const;
signals:
    void downloaded();

private slots:
    void fileDownloaded(QNetworkReply* pReply);

private:
    QNetworkAccessManager m_WebCtrl;
    QByteArray m_DownloadedData;
};

#endif // LOADER_H

