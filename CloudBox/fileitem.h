#ifndef FILEITEM_H
#define FILEITEM_H

#include <QStandardItem>
#include <QString>

class FileItem
{

public:
    explicit FileItem();
    bool getIsFolder();
    void setIsFolder(bool isFolder);
    QString getName();
    void setName(QString name);
    QString getIconPath();
    void setIconPath(QString iconPath);

    QString getPath();
    void setPath(QString path);

private:
    bool m_isFolder;
    QString m_name;
    QString m_iconPath;
    QString m_path;
};

#endif // FILEITEM_H
