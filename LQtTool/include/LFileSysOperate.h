/*********************************************************************************
 * 一些常用的文件操作
 *
 * *******************************************************************************/
#ifndef LFILESYSOPERATE_H
#define LFILESYSOPERATE_H

#include <QObject>

// 目录 dir
// 路径 path
// 文件 file
// 后缀名 suffix
// 基础文件名 BaseName
// 完整基础文件名 completeBaseName
// qt常用文件系统操作类有QFile、QFileInfo、QDir

class LFileSysOperate : public QObject
{
    Q_OBJECT
public:
    explicit LFileSysOperate(QObject *parent = 0);
    ~LFileSysOperate();

signals:

    void sigCopyDirStation(int percent);
    void sigCopyDirOver();
public slots:

public:
    static QString getExpandedName(QString strFilePath);
    static QString getFileNameByFilePath(QString strFilePath);
    static QString getFileBaseName(QString strFilePath);
    static bool s_copyFileToPath(const QString &strFileName, const QString &strDirDest, bool bCover = false);
    static bool s_copyDirFiles(const QString &strDirSrc, const QString &strDirDest, bool bCover = false);
    static bool s_copyRecursionNoSignal(const QString &strDirSrc, const QString &strDirDest, bool bCover = false);

public:
    bool copyDirFiles(const QString &strDirSrc, const QString &strDirDest, bool bCover = false);

private:

    bool copyRecursion(const QString &strDirSrc, const QString &strDirDest, bool bCover = false);

private:
    // 记录拷贝进度
    float m_dirTotal = 0;
    float m_dirAreadyCopy = 0;

};

#endif // LFILESYSOPERATE_H
