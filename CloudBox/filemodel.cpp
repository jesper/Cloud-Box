#include <QDebug>

#include "filemodel.h"

FileModel::FileModel(QObject *parent) :
    QStandardItemModel(parent)
{
    QHash<int, QByteArray> roles = roleNames();
    roles[NameRole] = "name";
    roles[IsFolderRole] = "isFolder";
    roles[IconPathRole] = "iconPath";
    roles[PathRole] = "path";


    setRoleNames(roles);
}

int FileModel::rowCount(const QModelIndex &index) const
{
    return m_fileItems.count();
}

void FileModel::appendRow(FileItem *fileItem)
{
    m_fileItems.append(fileItem);
    QStandardItemModel::appendRow(new QStandardItem());
}

void FileModel::clear()
{
    qDeleteAll(m_fileItems.begin(), m_fileItems.end());
    m_fileItems.clear();
    QStandardItemModel::clear();
}

QVariant FileModel::data(const QModelIndex &index, int role) const {
    qDebug() << "\n!!!data index" << index.row();

    if (index.row() < 0 || index.row() > m_fileItems.count())
        return QVariant();

    FileItem *fileItem = m_fileItems[index.row()];

    switch (role)
    {
    case IsFolderRole:
        return QVariant(fileItem->getIsFolder());
        break;
    case NameRole:
        return QVariant(fileItem->getName());
        break;
    case IconPathRole:
        return QVariant(fileItem->getIconPath());
        break;
    case PathRole:
        return QVariant(fileItem->getPath());
        break;

    }

}

