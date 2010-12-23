#ifndef JSON_H
#define JSON_H

#include <QScriptEngine>

class Json : public QScriptEngine
{
    Q_OBJECT
public:
    explicit Json(QObject *parent = 0);
    QVariantMap parse(QString json);
    bool error();

private:
    bool m_error;
    QScriptValue m_sc;
};

#endif // JSON_H
