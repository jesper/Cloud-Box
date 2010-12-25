#ifndef JSON_H
#define JSON_H

#include <QScriptEngine>

class Json : public QScriptEngine
{
    Q_OBJECT
public:
    explicit Json(QObject *parent = 0);
    QVariantMap parse(QString json);
    bool errorExists();
    QString getErrorString();

private:
    bool m_error;
    QString m_errorString;
    QScriptValue m_sc;
};

#endif // JSON_H
