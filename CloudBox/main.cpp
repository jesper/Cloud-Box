#include <QtGui/QApplication>
#include <QDeclarativeContext>

#include "qmlapplicationviewer.h"
#include "helper.h"
#include "dropboxnetwork.h"
#include <QEventLoop>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("CloudBox");
    QCoreApplication::setApplicationName("CloudBox");

    Helper helper;


    /*

    // For testing the Dropbox network until the GUI is up to speed...
    DropboxNetwork dropbox;

    while (dropbox.isBusy())
        app.processEvents(QEventLoop::WaitForMoreEvents | QEventLoop::ExcludeUserInputEvents);

    dropbox.accountInfo();
    viewer.rootContext()->setContextProperty("Dropbox", &dropbox);

*/

    QmlApplicationViewer viewer;
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationLockPortrait);
    viewer.rootContext()->setContextProperty("Helper", &helper);


    viewer.setMainQmlFile(QLatin1String("qml/CloudBox/main.qml"));

#ifdef Q_OS_SYMBIAN
    viewer.showFullScreen();
#else
    viewer.showExpanded();
#endif

    return app.exec();
}
