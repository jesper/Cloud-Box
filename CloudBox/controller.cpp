#include "controller.h"

Controller::Controller(QObject *parent) :
    QObject(parent)
{
    m_qmlViewer = new QmlApplicationViewer();
    m_helper = new Helper();
    m_dropboxNetwork = new DropboxNetwork(m_qmlViewer->rootContext());
    m_fileListModel_A = new FileModel(this);
    m_fileListModel_B = new FileModel(this);

    m_modelABusy = false;

    m_qmlViewer->setOrientation(QmlApplicationViewer::ScreenOrientationLockPortrait);
    m_qmlViewer->rootContext()->setContextProperty("FileListModel_A", m_fileListModel_A);
    m_qmlViewer->rootContext()->setContextProperty("FileListModel_B", m_fileListModel_B);
    m_qmlViewer->rootContext()->setContextProperty("Helper", m_helper);
    m_qmlViewer->rootContext()->setContextProperty("Dropbox", m_dropboxNetwork);
    m_qmlViewer->setMainQmlFile(QLatin1String("qml/CloudBox/main.qml"));

    QObject *rootObject = dynamic_cast<QObject*>(m_qmlViewer->rootObject());

    connect(rootObject, SIGNAL(signal_fileClicked(QString)), this, SLOT(qml_fileClicked(QString)));
    QObject::connect(this, SIGNAL(slideInFiles(QVariant)), rootObject, SLOT(slideInFiles(QVariant)));

    connect(m_dropboxNetwork, SIGNAL(fileListing(QList<QStandardItem*>)), this, \
            SLOT(dropbox_fileListing(QList<QStandardItem*>)));

#if defined(Q_WS_S60) || defined(Q_WS_MAEMO)
    m_qmlViewer->showFullScreen();
#else
    m_qmlViewer->showExpanded();
#endif

}

void Controller::dropbox_fileListing(QList<QStandardItem *> files)
{
    qDebug() << "Length is:" << files.length();

    FileModel *model;

    if (m_modelABusy)
        model = m_fileListModel_B;
    else
        model = m_fileListModel_A;

    model->clear();

    for (int i=0; i < files.length(); ++i)
        model->appendRow(files.at(i));

    emit slideInFiles(m_modelABusy ? "FileListModel_B" : "FileListModel_A");

    m_modelABusy = !m_modelABusy;
}

void Controller::qml_fileClicked(QString path)
{
    m_dropboxNetwork->listFiles(path);
}
