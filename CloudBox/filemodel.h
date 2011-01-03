#ifndef FILEMODEL_H
#define FILEMODEL_H

#include <QAbstractListModel>
#include <QStandardItemModel>

#include "assets.h"

class FileModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit FileModel(QObject *parent = 0);
};

#endif // FILEMODEL_H
