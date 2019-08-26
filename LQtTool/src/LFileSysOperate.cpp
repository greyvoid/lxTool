#include "LFileSysOperate.h"
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <QtDebug>

LFileSysOperate::LFileSysOperate(QObject *parent) : QObject(parent)
{

}

LFileSysOperate::~LFileSysOperate()
{

}

QString LFileSysOperate::getExpandedName(QString strFilePath)
{
    //    //method1
    //    int first = strFilePath.lastIndexOf (".");
    //    return strFilePath.right (strFilePath.length () - first - 1);


    //method2
    return strFilePath.section('.', -1);
}


QString LFileSysOperate::getFileNameByFilePath(QString strFilePath)
{
    //    //method1
    //    QFileInfo fInfo(strFilePath);
    //    return fInfo.fileName();  //fInfo.absolutePath();
    //    return fInfo.completeBaseName(); //完整基础文件名
    //    fInfo.suffix(); //扩展名
    //    fInfo.size();
    //    fInfo.isDir();

    //method2
    int first = strFilePath.lastIndexOf ("/");
    QString fileName = strFilePath.right (strFilePath.length () - first - 1);
    return fileName;

    //method3
    // return strFilePath.section('/', -1);
}

QString LFileSysOperate::getFileBaseName(QString strFilePath)
{
    QString strFileName = getFileNameByFilePath(strFilePath);
    int index = strFileName.lastIndexOf(".");
    strFileName.truncate(index);
    return strFileName;
}

bool LFileSysOperate::s_copyFileToPath(const QString &strFileName, const QString &strDirDest, bool bCover)
{
    return QFile::copy(strFileName, strDirDest);
}

bool LFileSysOperate::s_copyDirFiles(const QString &strDirSrc, const QString &strDirDest, bool bCover)
{
    //strDirDest.replace("\\","/");
    QDir dirSrc(strDirSrc);
    QDir dirDest(strDirDest);
    if (!dirSrc.exists() || !dirDest.exists())
    {
        qDebug() << "不存在目录";
        return false;
    }
    // 如果目标目录不存在，则进行创建
    if(!dirDest.exists())
    {
        if(!dirDest.mkdir(strDirDest))
        {
            return false;
        }
    }
    return s_copyRecursionNoSignal(strDirSrc, strDirDest, bCover);
}




//
bool LFileSysOperate::copyDirFiles(const QString &strDirSrc, const QString &strDirDest, bool bCover)
{
    QDir dirSrc(strDirSrc);
    QDir dirDest(strDirDest);
    if (!dirSrc.exists() || !dirDest.exists())
    {
        qDebug() << "不存在目录";
        return false;
    }
    // 如果目标目录不存在，则进行创建
    if(!dirDest.exists())
    {
        if(!dirDest.mkdir(strDirDest))
        {
            return false;
        }
    }
    QFileInfoList fileInfoListSrc = dirSrc.entryInfoList();
    int nFile = 0;
    foreach(QFileInfo fileInfoSrc, fileInfoListSrc)
    {
        if(fileInfoSrc.isFile())
        {
            ++nFile;
        }
    }
    m_dirTotal = fileInfoListSrc.count() - 2 - nFile; // 2为.和.. 不计入,次级目录的.和.. 计入
    m_dirAreadyCopy = 0;

    qDebug() << "a copyDirectoryFiles:" << fileInfoListSrc.count() << m_dirTotal << nFile;
    emit sigCopyDirStation(m_dirAreadyCopy / m_dirTotal);
    if(m_dirAreadyCopy == m_dirTotal)
    {
        emit sigCopyDirStation(1);
        emit sigCopyDirOver();
    }
    return copyRecursion(strDirSrc, strDirDest, bCover);

}

// 递归创建目录拷贝文件
bool LFileSysOperate::s_copyRecursionNoSignal(const QString &strDirSrc, const QString &strDirDest, bool bCover)
{
    QDir dirSrc(strDirSrc);
    QDir dirDest(strDirDest);
    // 如果目标目录不存在，则进行创建
    if(!dirDest.exists())
    {
        if(!dirDest.mkdir(strDirDest))
        {
            return false;
        }
    }

    QFileInfoList fileInfoListSrc = dirSrc.entryInfoList();
    foreach(QFileInfo fileInfoSrc, fileInfoListSrc)
    {
        if(fileInfoSrc.fileName() == "." || fileInfoSrc.fileName() == "..")
        {
            continue;
        }
        if(fileInfoSrc.isDir())
        {
            // 当为目录时，递归的进行copy
            if(!s_copyRecursionNoSignal(fileInfoSrc.filePath(), dirDest.filePath(fileInfoSrc.fileName()), bCover))
            {
                return false;
            }
        }
        else
        {
            // 当允许覆盖操作时，将旧文件进行删除操作
            if(bCover && dirDest.exists(fileInfoSrc.fileName()))
            {
                dirDest.remove(fileInfoSrc.fileName());
            }
            // 进行文件copy
            if(!QFile::copy(fileInfoSrc.filePath(), dirDest.filePath(fileInfoSrc.fileName())))
            {
                return false;
            }
        }
    }
    return true;
}


bool LFileSysOperate::copyRecursion(const QString &strDirSrc, const QString &strDirDest, bool bCover)
{
    // 拷贝进度
    m_dirAreadyCopy++;
    qDebug() << "a copyDirectoryFiles:" << m_dirAreadyCopy << m_dirTotal;
    emit sigCopyDirStation(m_dirAreadyCopy / m_dirTotal);
    if((m_dirAreadyCopy / m_dirTotal == 1) || (m_dirAreadyCopy > m_dirTotal) || (m_dirAreadyCopy == m_dirTotal))
    {
        emit sigCopyDirOver();
    }
    return s_copyRecursionNoSignal(strDirSrc, strDirDest, bCover);
}

