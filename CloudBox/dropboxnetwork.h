#ifndef DROPBOXNETWORK_H
#define DROPBOXNETWORK_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QtKOAuth>
#include <QStringList>
#include <QSettings>
#include <QNetworkSession>
#include <QNetworkConfigurationManager>
#include <QNetworkConfiguration>


#include "json.h"

class DropboxNetwork : public QObject
{
    Q_OBJECT

public:
    DropboxNetwork();
    void listFiles(QString path);
    void accountInfo();
    bool isBusy();
    bool keysWork();

public slots:
    bool hasValidKeys();
    void oauthNetworkFinished(QNetworkReply *networkReply);

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

    QNetworkConfigurationManager *m_networkConfigurationManager;
    QNetworkSession *m_networkSession;
    QNetworkAccessManager *m_networkManager;
    QNetworkAccessManager *m_oauthNetworkManager;

    KQOAuthManager *m_oauthManager;
    KQOAuthRequest *m_oauthRequest;
    Json *m_json;
    QSettings m_settings;
    QString m_token;
    QString m_secret;
    bool m_busy;
};

#endif // DROPBOXNETWORK_H
