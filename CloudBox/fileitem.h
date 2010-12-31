#ifndef FILEITEM_H
#define FILEITEM_H

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

private:
    bool m_isFolder;
    QString m_name;
    QString m_iconPath;


};

#endif // FILEITEM_H
