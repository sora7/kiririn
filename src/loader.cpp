#include "loader.h"

Loader::Loader(QUrl url, QObject *parent) : QObject(parent)
{
    connect(&m_WebCtrl,
            SIGNAL(finished(QNetworkReply*)),
            this,
            SLOT(fileDownloaded(QNetworkReply*))
            );

//    QList<QSslError> errIgnore;

//    errIgnore << QSslError(QSslError::HostNameMismatch);
//    errIgnore << QSslError(QSslError::SelfSignedCertificate);

//    m_WebCtrl.ignoreSslErrors(errIgnore);

    connect(&m_WebCtrl,
            SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)),
            this,
            SLOT(onSslErrors(QNetworkReply*,QList<QSslError>))
            );

    QNetworkRequest request(url);
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:45.9) Gecko/20100101 Goanna/3.2 Firefox/45.9 PaleMoon/27.2.0");

    QSslConfiguration sslConfig = QSslConfiguration::defaultConfiguration();
//    sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
    sslConfig.setProtocol(QSsl::TlsV1);
    request.setSslConfiguration(sslConfig);

    m_WebCtrl.get(request);
}

Loader::~Loader()
{
}

QByteArray Loader::downloadedData() const
{
//    cout << "SIZE: " << m_DownloadedData.length() << endl;
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
    cout << "SSL ERROR" << endl;
    pReply->ignoreSslErrors(lst);
//    QNetworkReply::ignoreSslErrors()
}
