#include "fileitem.h"

FileItem::FileItem()
{
    m_isFolder = false;
    m_name = "";
    m_iconPath = "";

}

void FileItem::setIsFolder(bool isFolder)
{
    m_isFolder = isFolder;
}

bool FileItem::getIsFolder()
{
    return m_isFolder;
}

QString FileItem::getName()
{
    return m_name;
}

void FileItem::setName(QString name)
{
    m_name = name;
}

QString FileItem::getIconPath()
{
    return m_iconPath;
}

void FileItem::setIconPath(QString iconPath)
{
    m_iconPath = iconPath;
}
