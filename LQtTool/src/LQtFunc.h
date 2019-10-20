#ifndef LQt_FUNC_H
#define LQt_FUNC_H

#include <QString>
class QWidget;

namespace Lqt {

void delayTime(int s);
QString strRecombine(const QString &strSrc, const QString &strSplit, int nSplitSize);

QString formatBytes(quint64 qu64Size, quint8 u8ValidDigit);

// 图片处理
void saveImgDataToFile(const QString &fromImgData, const QString &toFilePath, const QString &strFormat);
void dataToPic(const QString &fromFilePath, QString toPic, QString myformat);


} // end namespace Lx


#endif // end LQt_FUNC_H
