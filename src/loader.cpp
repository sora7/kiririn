#include "loader.h"

Loader::Loader(QString url, QObject *parent) : QObject(parent)
{
    connect(&m_WebCtrl,
            SIGNAL(finished(QNetworkReply*)),
            this,
            SLOT(fileDownloaded(QNetworkReply*)));

    QUrl url1(url);
    QNetworkRequest request(url1);
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:45.9) Gecko/20100101 Goanna/3.2 Firefox/45.9 PaleMoon/27.2.0");
    QSslConfiguration sslConfig = QSslConfiguration::defaultConfiguration();
    sslConfig.setProtocol(QSsl::TlsV1);
    request.setSslConfiguration(sslConfig);
    m_WebCtrl.get(request);
}

Loader::~Loader()
{
}

QByteArray Loader::downloadedData() const
{
    return m_DownloadedData;
}

QString Loader::getHtml() const
{
    QString htmlText;
    htmlText = QTextCodec::codecForMib(106)->toUnicode(m_DownloadedData);
    return htmlText;
}

void Loader::fileDownloaded(QNetworkReply *pReply)
{
    m_DownloadedData = pReply->readAll();
    pReply->deleteLater();
    cout << "SIGNAL" << endl;
    emit downloaded();
    cout << "SIGNAL" << endl;
}
