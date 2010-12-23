#include <QDebug>

#include "json.h"

Json::Json(QObject *parent) :
    QScriptEngine(parent), m_error(false)
{
}

QVariantMap Json::parse(QString json)
{
    m_error = false;

    m_sc = evaluate(("(" + QString(json) + ")"));

    if (hasUncaughtException()) {
        qDebug() << "JSon uncaught exception at line" << uncaughtExceptionLineNumber() << ":" << m_sc.toString();
        m_error = true;
        return QVariantMap();
    }

    return m_sc.toVariant().toMap();
}

bool Json::error()
{
    return m_error;
}
