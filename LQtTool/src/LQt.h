#ifndef LQt_FUNC_H
#define LQt_FUNC_H

#include "LStd.h"
#include <QString>

class QWidget;

class CLQt : public CLStd
{

public:
    static void delayTime(int s);
    static QString strRecombine(const QString &strSrc, const QString &strSplit, int nSplitSize);

    static QString formatBytes(quint64 qu64Size, quint8 u8ValidDigit = 2);

    // 图片处理
    static void saveImgDataToFile(const QString &fromImgData, const QString &toFilePath, const QString &strFormat);
    static void dataToPic(const QString &fromFilePath, QString toPic, QString myformat);

    static void Sleep(int ms);

    //窗体相对桌面居中显示
    static void moveToDeskCenter(QWidget *widget);

    //判断是否是IP地址
    static bool isIP(QString strIP);

    //设置为开机启动
    static void autoRunWithSystem(bool bAutoRun, const QString & strAppName, const QString & strAppPath);


}; // end namespace Lx


#endif // end LQt_FUNC_H
