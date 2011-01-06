#include <QtGui/QApplication>
#include <QDeclarativeContext>
#include <QEventLoop>
#include <QDebug>

#include "qmlapplicationviewer.h"
#include "helper.h"
#include "dropboxnetwork.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("Cloudbox");
    QCoreApplication::setApplicationName("Cloudbox");


    QmlApplicationViewer viewer;
    Helper helper;
    DropboxNetwork dropbox(viewer.rootContext());

    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationLockPortrait);
    viewer.rootContext()->setContextProperty("Helper", &helper);
    viewer.rootContext()->setContextProperty("Dropbox", &dropbox);
    viewer.setMainQmlFile(QLatin1String("qml/CloudBox/main.qml"));

#if defined(Q_WS_S60) || defined(Q_WS_MAEMO)
    viewer.showFullScreen();
#else
    viewer.showExpanded();
#endif

    return app.exec();
}
