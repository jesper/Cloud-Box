#include <QDebug>
#include <QCoreApplication>
#include <QFile>
#include <QScriptEngine>
#include <QList>
#include <QVariantList>

#include "dropboxnetwork.h"
#include "json.h"
#include "assets.h"

DropboxNetwork::DropboxNetwork()
{
    m_networkConfigurationManager = new QNetworkConfigurationManager(this);
    //Seems this is needed for symbian to initiate an initial network scan.
    m_networkConfigurationManager->isOnline();

    m_networkSession = new QNetworkSession(m_networkConfigurationManager->defaultConfiguration(), this);
    m_oauthManager = new KQOAuthManager(this);
    m_json = new Json(this);
    m_oauthRequest = new KQOAuthRequest(this);
    m_networkManager = new QNetworkAccessManager(this);
    m_oauthNetworkManager = new QNetworkAccessManager(this);
    m_oauthManager->setNetworkManager(m_oauthNetworkManager);

    m_token = m_settings.value("token").toString();
    m_secret = m_settings.value("secret").toString();

    m_busy = false;

    connect(m_networkManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(networkFinished(QNetworkReply *)));
    connect(m_oauthNetworkManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(oauthNetworkFinished(QNetworkReply *)));
}

void DropboxNetwork::oauthNetworkFinished(QNetworkReply *networkReply)
{
    if (networkReply->error() == QNetworkReply::NoError)
        return;

    reportErrorMessage("Authentication Network Error: " + networkReply->errorString());
    m_busy = false;
}

bool DropboxNetwork::isNetworkingAvailable()
{
    if (!m_networkSession->isOpen())
        m_networkSession->open();

    if (!m_networkSession->waitForOpened(30000))
    {
        reportErrorMessage("Network Connectivity: " + m_networkSession->errorString());
        return false;
    }

    if (!((m_networkSession->state() != QNetworkSession::Connected) || (m_networkSession->state() != QNetworkSession::Roaming)))
    {
        reportErrorMessage("Network Connectivity: Could not connect, state: " + m_networkSession->state());
        return false;
    }

    return true;

}


bool DropboxNetwork::hasValidKeys()
{
    if (!isNetworkingAvailable())
        return false;

    //TBD Check that they actually work as well!
    if (m_settings.value("token").toString().isEmpty() || m_settings.value("secret").toString().isEmpty())
        return false;

    return keysWork();
}

void DropboxNetwork::busyWait()
{
    while (isBusy())
    {
        qDebug() << "Spinning";
        QCoreApplication::instance()->processEvents(QEventLoop::WaitForMoreEvents | QEventLoop::ExcludeUserInputEvents);
    }
}

bool DropboxNetwork::keysWork()
{
    if (!isNetworkingAvailable())
        return false;

    accountInfo();

    busyWait();

    if (m_oauthManager->lastError() != KQOAuthManager::NoError)
    {
        reportErrorMessage("Dropbox Authentication Error: Could Not Connect");
        return false;
    }
    else
        return true;
}

void DropboxNetwork::getKeys()
{
    if (!isNetworkingAvailable())
        return;

    m_busy = true;

    QString url = QString("https://api.dropbox.com/0/token?email=%1&password=%2&oauth_consumer_key=%3") \
            .arg(TEST_EMAIL).arg(TEST_PASSWORD).arg(APPLICATION_KEY);

    m_networkManager->get(QNetworkRequest(QUrl(url)));
}

void DropboxNetwork::reportErrorMessage(const QString error)
{
    qDebug() << "Error in " + error;
    m_busy  = false;
}

void DropboxNetwork::networkFinished(QNetworkReply *networkReply)
{
    //TBD alert user incase of errors below

    if (networkReply->error() != QNetworkReply::NoError)
        return reportErrorMessage("Network Connection: " + networkReply->errorString());

    QVariantMap response = m_json->parse(networkReply->readAll());

    if (m_json->errorExists())
        return reportErrorMessage("Network JSON: " + m_json->getErrorString());

    if (response["token"].toString().isEmpty())
        return reportErrorMessage("Dropbox Authentication: Temp Token Invalid.");

    if (!response["secret"].toString().isEmpty())
        return reportErrorMessage("Dropbox Authentication: Temp Secret Invalid.");

    m_settings.setValue("token", response["token"].toString());
    m_settings.setValue("secret", response["secret"].toString());

    m_token = response["token"].toString();
    m_secret = response["secret"].toString();

    m_busy = false;
}

void DropboxNetwork::recyleOauth()
{
    Q_ASSERT(m_busy == false);
    m_busy = true;

    delete m_oauthManager;
    m_oauthManager = new KQOAuthManager(this);
    m_oauthManager->setNetworkManager(m_oauthNetworkManager);
}

void DropboxNetwork::accountInfo()
{
    recyleOauth();
    QObject::connect(m_oauthManager, SIGNAL(requestReady(QByteArray)), this, SLOT(handleAccountInfo(QByteArray)));

    m_oauthRequest->initRequest(KQOAuthRequest::AuthorizedRequest, QUrl("https://api.dropbox.com/0/account/info"));
    m_oauthRequest->setConsumerKey(APPLICATION_KEY);
    m_oauthRequest->setConsumerSecretKey(APPLICATION_SECRET);
    m_oauthRequest->setToken(m_token);
    m_oauthRequest->setTokenSecret(m_secret);
    m_oauthManager->executeRequest(m_oauthRequest);
}

void DropboxNetwork::listFiles(QString path)
{
    recyleOauth();
    QObject::connect(m_oauthManager, SIGNAL(requestReady(QByteArray)), this, SLOT(handleListFiles(QByteArray)));

    m_oauthRequest->initRequest(KQOAuthRequest::AuthorizedRequest, QUrl("https://api.dropbox.com/0/metadata/dropbox/"+path));
    m_oauthRequest->setConsumerKey(APPLICATION_KEY);
    m_oauthRequest->setConsumerSecretKey(APPLICATION_SECRET);
    m_oauthRequest->setToken(m_token);
    m_oauthRequest->setTokenSecret(m_secret);
    m_oauthManager->executeRequest(m_oauthRequest);
}

void DropboxNetwork::handleAccountInfo(QByteArray response)
{
    qDebug() << "\nAccount info response:" << response;
    m_busy = false;
}

bool DropboxNetwork::isBusy()
{
    return m_busy;
}

void DropboxNetwork::handleListFiles(QByteArray response) {
    qDebug() << "\nList files response:" << response;
    m_busy = false;
}
