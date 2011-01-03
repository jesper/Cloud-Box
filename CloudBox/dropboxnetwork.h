#ifndef DROPBOXNETWORK_H
#define DROPBOXNETWORK_H

#include <QStandardItemModel>
#include <QDeclarativeContext>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QtKOAuth>
#include <QStringList>
#include <QSettings>
#include <QNetworkSession>
#include <QNetworkConfigurationManager>
#include <QNetworkConfiguration>

#include "filemodel.h"
#include "json.h"

class DropboxNetwork : public QObject
{
    Q_OBJECT

public:
    DropboxNetwork(QDeclarativeContext *declarativeContext);
    void accountInfo();
    bool isBusy();
    bool keysWork();

public slots:
    QString getAccountName();
    QString getAccountEmail();
    bool hasValidKeys();
    void oauthNetworkFinished(QNetworkReply *networkReply);
    void listFiles(QString path);


private slots:
    void handleAccountInfo(QByteArray);
    void handleListFiles(QByteArray);
    void networkFinished(QNetworkReply *networkReply);

private:
    bool isNetworkingAvailable();
    void busyWait();
    void getKeys();
    void recyleOauth();
    void reportErrorMessage(const QString error);

    FileModel *m_fileListModel;
    QNetworkConfigurationManager *m_networkConfigurationManager;
    QNetworkSession *m_networkSession;
    QNetworkAccessManager *m_networkManager;
    QNetworkAccessManager *m_oauthNetworkManager;
    QDeclarativeContext *m_declarativeContext;
    KQOAuthManager *m_oauthManager;
    KQOAuthRequest *m_oauthRequest;
    Json *m_json;
    QSettings m_settings;
    QString m_token;
    QString m_secret;
    bool m_busy;
    QString m_accountName;
    QString m_accountEmail;
};

#endif // DROPBOXNETWORK_H
