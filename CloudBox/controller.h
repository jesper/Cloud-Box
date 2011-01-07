#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QGraphicsObject>
#include <QStandardItem>

#include "qmlapplicationviewer.h"
#include "helper.h"
#include "dropboxnetwork.h"
#include "filemodel.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);

public slots:
    void qml_fileClicked(QString path);
    void dropbox_fileListing(QList<QStandardItem *> files);

signals:
    void slideInFiles(QVariant model);

private:
    DropboxNetwork *m_dropboxNetwork;
    QmlApplicationViewer *m_qmlViewer;
    Helper *m_helper;
    FileModel *m_fileListModel_A;
    FileModel *m_fileListModel_B;
    bool m_modelABusy;
};

#endif // CONTROLLER_H
