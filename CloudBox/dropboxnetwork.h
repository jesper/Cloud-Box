#ifndef DROPBOXNETWORK_H
#define DROPBOXNETWORK_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QtKOAuth>
#include <QStringList>
#include <QSettings>

#include "json.h"

class DropboxNetwork : public QObject
{
    Q_OBJECT

public:
    DropboxNetwork();
    void listFiles(QString path);
    void accountInfo();
    bool isBusy();

private slots:
    void handleAccountInfo(QByteArray);
    void handleListFiles(QByteArray);

    void networkFinished(QNetworkReply *networkReply);

private:
    bool hasValidKeys();
    void getKeys();
    void recyleOauth();

    QNetworkAccessManager *m_networkManager;
    KQOAuthManager *m_oauthManager;
    KQOAuthRequest *m_oauthRequest;
    Json *m_json;
    QSettings m_settings;
    QString m_token;
    QString m_secret;
    bool m_busy;
};

#endif // DROPBOXNETWORK_H