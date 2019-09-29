#include "LQtFunc.h"

#include <QTime>
#include <QCoreApplication>
#include <QWidget>
#include <QFile>
#include <QBuffer>

// 延迟时间-秒
void Lqt::delayTime(int s)
{
    QTime t=QTime::currentTime().addMSecs(s);
    while(QTime::currentTime()<t)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }
}

///
/// \brief Lx::strRecombine 对传入的字符串进行重排，每超过nSplitSize个字节就插入分割字符串strSplit,多用于文本分行显示
/// \param strSrc
/// \param strSplit
/// \param nSplitSize
/// \return
///
QString Lqt::strRecombine(const QString & strSrc, const QString & strSplit, int nSplitSize)
{
    if (strSrc.size() <= nSplitSize)
    {
        return strSrc;
    }
    QString strTemp = strSrc;
    QString strResult = "";
    while (true)
    {
        QString strSub = strTemp.left(nSplitSize);
        strResult = strResult + strSub + strSplit;
        strTemp = strTemp.right(strTemp.size() - nSplitSize);
        if (strTemp.size() <= nSplitSize)
        {
            strResult = strResult + strTemp;
            break;
        }
    }
    return strResult;
}

///
/// \brief Lx::strRecombineLine 对传入的文本strSrc根据控件pWidget的宽度自动换行
/// \param strSrc
/// \param pWidget
/// \return
///
QString Lqt::strRecombineLine(const QString & strSrc, const QWidget* pWidget)
{
    QString strResult;
    QFontMetrics fm(pWidget->fontMetrics());
    int nTextTotalWidthInPxs = fm.width(strSrc);
    if (nTextTotalWidthInPxs <= pWidget->width())
    {
        strResult = strSrc;
        return strResult;
    }
    // CharNum <==> bytes
    const int nTotalCharNum = strSrc.length();
    int nPickUpStartPos = 0;
    int nOffset = 1;
    QString strPickUp;
    unsigned int nPickUpCharNum = 0;
    unsigned int unPickUpWidthPxs = 0;
    while (nOffset <= nTotalCharNum)
    {
        nPickUpCharNum = nOffset - nPickUpStartPos;
        strPickUp = strSrc.mid(nPickUpStartPos, nPickUpCharNum);
        unPickUpWidthPxs = fm.width(strPickUp);
        if (unPickUpWidthPxs >= pWidget->width())
        {
            // 换行
            strResult += strPickUp + "\n";
            nPickUpStartPos = nOffset;
            unPickUpWidthPxs = 0;
        }
        ++nOffset;
    }

    // 加上最后一段
    if (!strPickUp.isEmpty())
    {
        strResult += strPickUp;
    }

    return strResult;
}

QString Lqt::formatBytes(quint64 qu64Size, quint8 u8ValidDigit)
{
    QString strUnit = "B";
    double dNumber = qu64Size;
    double dDivisor = 1024;
    if (dNumber >= dDivisor)
    {
        strUnit = "KB";
        dNumber = dNumber / dDivisor;
    }
    if (dNumber >= dDivisor)
    {
        strUnit = "MB";
        dNumber = dNumber / dDivisor;
    }
    if (dNumber >= dDivisor)
    {
        strUnit = "GB";
        dNumber = dNumber / dDivisor;
    }
    if (dNumber >= dDivisor)
    {
        strUnit = "TB";
        dNumber = dNumber / dDivisor;
    }
    return QString::number(dNumber, 'f', u8ValidDigit) + strUnit;
}

void Lqt::saveImgDataToFile(const QString &fromImgData, const QString &toFilePath, const QString &strFormat)
{
    QImage img(fromImgData);
    QByteArray ba;
    QBuffer buf(&ba);
    img.save(&buf,"JPG");//按照JPG解码保存数据
    QByteArray cc=qCompress(ba,1);
    QByteArray hh;
    if (strFormat=="Hex")
    {
        hh=cc.toHex();//16进制数据
    }
    else
    {
        hh=cc.toBase64();//base64数据
    }
    QString str(hh);
    QFile file(toFilePath);
    if (file.open(QFile::WriteOnly))
    {
        file.write(str.toLatin1());
        file.close();
    }
}

void Lqt::dataToPic(const QString &fromFilePath, QString toPic, QString myformat)
{
    QFile file(fromFilePath);
    if (file.open(QFile::ReadOnly))
    {
        QByteArray read=file.readAll();
        file.close();
        QString ss=QString::fromLatin1(read.data(),read.size());
        QByteArray rc;
        if (myformat=="Hex")
        {
            rc=QByteArray::fromHex(ss.toLatin1());
        }
        else
        {
            rc=QByteArray::fromBase64(ss.toLatin1());
        }
        QByteArray rdc=qUncompress(rc);

        QImage img;
        img.loadFromData(rdc);
        img.save(toPic);
    }
}
