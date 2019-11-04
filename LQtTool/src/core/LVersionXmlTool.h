#ifndef CLVERSIONXMLTOOL_H
#define CLVERSIONXMLTOOL_H

#include <QObject>

///
/// \brief The T_BinFileNodeMsg struct 序列化的xml节点为版本信息文件
///
struct T_BinFileNodeMsg
{
    QString name;       // 版本文件名
    QString dir;        // 版本文件所在的目录
    QString version;    // 版本号
    T_BinFileNodeMsg()
    {
        init();
    }

    void init()
    {
        name = "";
        dir = "";
        version = "";
    }
};


///
/// \brief The CLVersionXmlTool class 基于xml文件的处理工具类
///
class CLVersionXmlTool : public QObject
{
    Q_OBJECT
public:
    explicit CLVersionXmlTool(QObject *parent = 0);

    static void createVersionXmlFile(const QString & strXmlFileName, const QList<T_BinFileNodeMsg> & lstBinFileNodeMsg);
    QList<T_BinFileNodeMsg> getListVersion(const QString & strFileName);
    QList<T_BinFileNodeMsg> getListVersionDownload(const QList<T_BinFileNodeMsg> & lstBinFileNodeOld
                                                   , const QList<T_BinFileNodeMsg> & lstBinFileNodeNew
                                                   , bool bNeedDlelteOldFile = false);
    QList<T_BinFileNodeMsg> getListVersionDownload(const QString & strFileNameOld
                                                   , const QString & strFileNameNew
                                                   , bool bNeedDlelteOldFile = false);


signals:

public slots:
};

#endif // CLVERSIONXMLTOOL_H
