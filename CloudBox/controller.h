#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QGraphicsObject>

#include "qmlapplicationviewer.h"
#include "helper.h"
#include "dropboxnetwork.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);

public slots:
    void qml_pathClicked(QString path);

signals:


private:
    DropboxNetwork *m_dropboxNetwork;
    QmlApplicationViewer *m_qmlViewer;
    Helper *m_helper;
};

#endif // CONTROLLER_H
