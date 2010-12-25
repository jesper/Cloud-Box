#include <QDebug>

#include "json.h"

Json::Json(QObject *parent) :
    QScriptEngine(parent), m_error(false), m_errorString("")
{
}

QVariantMap Json::parse(QString json)
{
    m_error = false;

    m_sc = evaluate(("(" + QString(json) + ")"));

    if (hasUncaughtException()) {
        qDebug() << "JSon uncaught exception at line" << uncaughtExceptionLineNumber() << ":" << m_sc.toString();
        m_errorString = uncaughtExceptionLineNumber() + ":" + m_sc.toString();
        m_error = true;
        return QVariantMap();
    }

    return m_sc.toVariant().toMap();
}

QString Json::getErrorString()
{
    return m_errorString;
}

bool Json::errorExists()
{
    return m_error;
}
