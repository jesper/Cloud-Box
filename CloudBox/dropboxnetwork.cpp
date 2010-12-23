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
    m_busy = false;
    m_oauthManager = new KQOAuthManager(this);
    m_json = new Json(this);
    m_oauthRequest = new KQOAuthRequest(this);

    m_networkManager = new QNetworkAccessManager(this);
    connect(m_networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(networkFinished(QNetworkReply *)));

    if (!hasValidKeys())
        getKeys();

    m_token = m_settings.value("token").toString();
    m_secret = m_settings.value("secret").toString();
}

bool DropboxNetwork::hasValidKeys()
{
    //TBD Check that they actually work as well!
    return !(m_settings.value("token").toString().isEmpty() || m_settings.value("secret").toString().isEmpty());
}

void DropboxNetwork::getKeys()
{
    m_busy = true;

    QString url = QString("https://api.dropbox.com/0/token?email=%1&password=%2&oauth_consumer_key=%3") \
            .arg(TEST_EMAIL).arg(TEST_PASSWORD).arg(APPLICATION_KEY);

    m_networkManager->get(QNetworkRequest(QUrl(url)));
}

void DropboxNetwork::networkFinished(QNetworkReply *networkReply)
{
    //TBD alert user incase of errors below

    if (networkReply->error() != 0)
    {
        qDebug("Some error occured in replyFinished in regards to networkReply");
        return;
    }

    QVariantMap response = m_json->parse(networkReply->readAll());

    if (m_json->error())
    {
        qDebug("JSON response was invalid");
        return;
    }

    if (!response["token"].toString().isEmpty())
        qDebug() << "!Token:" << response["token"].toString();
    else
    {
        qDebug() << "Token invalid";
        return;
    }

    if (!response["secret"].toString().isEmpty())
        qDebug() << "!Secret:" << response["secret"].toString();
    else
    {
        qDebug() << "Secret invalid";
        return;
    }

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
