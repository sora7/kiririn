#include "loader.h"

Loader::Loader(QObject *parent) : QObject(parent)
{
    connect(&m_WebCtrl,
            SIGNAL(finished(QNetworkReply*)),
            this,
            SLOT(fileDownloaded(QNetworkReply*))
            );

    connect(&m_WebCtrl,
            SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)),
            this,
            SLOT(onSslErrors(QNetworkReply*,QList<QSslError>))
            );
}

Loader::~Loader()
{
}

void Loader::load(QString url)
{
    QUrl url2(url);
    QNetworkRequest request(url2);
    request.setRawHeader(QString("User-Agent").toAscii(), DEFAULT_UA.toAscii());

    QSslConfiguration sslConfig = QSslConfiguration::defaultConfiguration();

    sslConfig.setProtocol(QSsl::TlsV1);
    request.setSslConfiguration(sslConfig);

    m_WebCtrl.get(request);
}

QByteArray Loader::downloadedData() const
{
    return m_DownloadedData;
}

QString Loader::getHtml() const
{
//    const int UNICODE = 106;

    QString htmlText(m_DownloadedData);
//    QString htmlText = QString::fromAscii(m_DownloadedData);
//    htmlText = QTextCodec::codecForMib(106)->toUnicode(m_DownloadedData);
    return htmlText;
}

void Loader::fileDownloaded(QNetworkReply *pReply)
{
    m_DownloadedData = pReply->readAll();
    pReply->deleteLater();
    emit downloaded();
}

void Loader::onSslErrors(QNetworkReply *pReply, const QList<QSslError>& lst)
{
//    cout << "SSL ERROR" << endl;
    pReply->ignoreSslErrors(lst);
}
