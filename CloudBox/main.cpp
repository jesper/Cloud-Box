#include <QtGui/QApplication>
#include <QDeclarativeContext>
#include <QEventLoop>
#include <QDebug>

#include "qmlapplicationviewer.h"
#include "helper.h"
#include "dropboxnetwork.h"
#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("Cloudbox");
    QCoreApplication::setApplicationName("Cloudbox");


    Controller controller;
    Q_UNUSED(controller);

    return app.exec();
}
