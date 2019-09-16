
/*********************************************************************************
 * 一些常用的xml操作
 *
 * *******************************************************************************/

// 通过QXmlStreamReader解析mxl
// 通过DOM方式 -- 本类使用此方法
// 通过QXmlSimpleReader

#ifndef MY_XML_OPERATE_H
#define MY_XML_OPERATE_H


#include <QObject>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>

class LXmlOperate : public QObject
{
    Q_OBJECT

public:
    LXmlOperate(QObject *parent = 0);
    LXmlOperate(const QString strXmlFile, QObject *parent = 0);
    ~LXmlOperate();

    // 静态方法


public:
    // 公共成员方法
    bool loadXmlFile(const QString strXmlFile);
    bool saveXmlFile(const QString strXmlFile);
    QString getFirstElementTextByTagName(const QString &tagName);
    void setFirstElementTextByTagName(const QString &tagName, const QString &text);
    void clearAllChildNodes();

private:
    QDomDocument m_doc;         //xml doc
    QDomNode m_nodeRoot;
    QDomElement m_elementRoot;  //根节点
};

#endif

