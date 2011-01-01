#ifndef FILEMODEL_H
#define FILEMODEL_H

#include <QAbstractListModel>
#include <QStandardItemModel>

#include "fileitem.h"

class FileModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit FileModel(QObject *parent = 0);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &index = QModelIndex()) const;
    void clear();
    void appendRow(FileItem *fileItem);

    enum FileRoles {
        NameRole = Qt::UserRole + 1,
        IsFolderRole,
        IconPathRole,
        PathRole
    };

private:
    QList<FileItem *> m_fileItems;
};

#endif // FILEMODEL_H
