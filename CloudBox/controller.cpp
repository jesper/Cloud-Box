#include "controller.h"

Controller::Controller(QObject *parent) :
    QObject(parent)
{
    m_qmlViewer = new QmlApplicationViewer();
    m_helper = new Helper();
    m_dropboxNetwork = new DropboxNetwork(m_qmlViewer->rootContext());

    m_qmlViewer->setOrientation(QmlApplicationViewer::ScreenOrientationLockPortrait);
    m_qmlViewer->rootContext()->setContextProperty("Helper", m_helper);
    m_qmlViewer->rootContext()->setContextProperty("Dropbox", m_dropboxNetwork);
    m_qmlViewer->setMainQmlFile(QLatin1String("qml/CloudBox/main.qml"));

    QObject *rootObject = dynamic_cast<QObject*>(m_qmlViewer->rootObject());
    QObject::connect(rootObject, SIGNAL(signal_pathClicked(QString)), this, SLOT(qml_pathClicked(QString)));

#if defined(Q_WS_S60) || defined(Q_WS_MAEMO)
    m_qmlViewer->showFullScreen();
#else
    m_qmlViewer->showExpanded();
#endif

}

void Controller::qml_pathClicked(QString path)
{
    qDebug() << "C++ Path is:" << path;
}
