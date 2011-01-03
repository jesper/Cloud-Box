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
