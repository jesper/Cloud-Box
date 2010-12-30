#include <QDebug>
#include <QCoreApplication>
#include <QFile>
#include <QScriptEngine>
#include <QList>
#include <QVariantMap>

#include "dropboxnetwork.h"
#include "json.h"
#include "assets.h"

DropboxNetwork::DropboxNetwork(QDeclarativeContext *declarativeContext)
    : m_declarativeContext(declarativeContext)
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
    m_fileListModel = new QStandardItemModel(this);
    m_fileListModel->appendRow(new QStandardItem("Foo"));

    m_declarativeContext->setContextProperty("FileListModel", m_fileListModel);

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

    if (m_settings.value("token").toString().isEmpty() || m_settings.value("secret").toString().isEmpty())
    {

    //    reportErrorMessage("Dropbox Authentication Error: Could not find user token/secret");
        return false;
    }

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

    handleAccountInfo("{\"referral_link\": \"https://www.dropbox.com/referrals/NTE2OTk2Njk4OQ\", \"display_name\": \"Jesper Thomschutz\", \"uid\": 16996698, \"country\": \"SE\", \"quota_info\": {\"shared\": 0, \"quota\": 2147483648, \"normal\": 1304283}, \"email\": \"jesper@jespersaur.com\"}");
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

    handleListFiles("{\"hash\": \"e18874dce26d5f89bdd22b1f42eec7a1\", \"thumb_exists\": false, \"bytes\": 0, \"path\": \"\", \"is_dir\": true, \"size\": \"0 bytes\", \"root\": \"dropbox\", \"contents\": [{\"revision\": 9, \"thumb_exists\": false, \"bytes\": 127748, \"modified\": \"Fri, 17 Dec 2010 16:44:20 +0000\", \"path\": \"/Getting Started.pdf\", \"is_dir\": false, \"icon\": \"page_white_acrobat\", \"mime_type\": \"application/pdf\", \"size\": \"124.8KB\"}, {\"revision\": 1, \"thumb_exists\": false, \"bytes\": 0, \"modified\": \"Fri, 17 Dec 2010 16:44:20 +0000\", \"path\": \"/Photos\", \"is_dir\": true, \"icon\": \"folder_photos\", \"size\": \"0.0 bytes\"}, {\"revision\": 2, \"thumb_exists\": false, \"bytes\": 0, \"modified\": \"Fri, 17 Dec 2010 16:44:20 +0000\", \"path\": \"/Public\", \"is_dir\": true, \"icon\": \"folder_public\", \"size\": \"0.0 bytes\"}], \"icon\": \"folder\"}");
}

void DropboxNetwork::handleAccountInfo(QByteArray response)
{
    qDebug() << "\nAccount info response:" << response;
    m_busy = false;
    QVariantMap json = m_json->parse(QString(response));

    if (m_json->errorExists())
        return reportErrorMessage("Network JSON: " + m_json->getErrorString());

    if (json["display_name"].toString().isEmpty())
        return reportErrorMessage("Dropbox Account Info: Name is invalid.");

    if (json["email"].toString().isEmpty())
        return reportErrorMessage("Dropbox Account Info: Email is invalid.");

    if (json["quota_info"].toMap()["shared"].toString().isEmpty())
        return reportErrorMessage("Dropbox Account Info: quota_shared is invalid.");

    if (json["quota_info"].toMap()["quota"].toString().isEmpty())
        return reportErrorMessage("Dropbox Account Info: quota_info is invalid.");

    if (json["quota_info"].toMap()["normal"].toString().isEmpty())
        return reportErrorMessage("Dropbox Account Info: quota_normal is invalid.");

    m_accountName = json["display_name"].toString();
    m_accountEmail = json["email"].toString();

    //TBD Store quota
}

QString DropboxNetwork::getAccountName() {
    return m_accountName;
}


QString DropboxNetwork::getAccountEmail() {
    return m_accountEmail;
}

bool DropboxNetwork::isBusy()
{
    return m_busy;
}

void DropboxNetwork::handleListFiles(QByteArray response) {
    qDebug() << "\nList files response:" << response;
    QVariantMap json = m_json->parse(QString(response));

    if (m_json->errorExists())
        return reportErrorMessage("Network JSON: " + m_json->getErrorString());


    QList<QVariant> contents = json["contents"].toList();

    if (!contents.empty())
    {
        m_fileListModel->clear();
        for (int i=0; i < contents.length(); ++i)
        {
            qDebug() << "Contents:" << contents.at(i).toMap()["path"];
            QStandardItem *file = new QStandardItem(contents.at(i).toMap()["path"].toString());
            //Have to set the data value manually instead of setIcon so that qml can use it as a source property.
            file->setData("qrc:/icons/"+contents.at(i).toMap()["icon"].toString()+"48.gif", Qt::DecorationRole);
            m_fileListModel->appendRow(file);
        }
    }

    m_busy = false;
}
