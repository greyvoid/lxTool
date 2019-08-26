
#include "MyAction.h"




CMyAction::CMyAction(QObject *parent)
    : QAction(parent)
{

}

CMyAction::CMyAction(const QString &text, QObject *parent)
    : QAction(text,parent)
{

}

CMyAction::CMyAction(const QIcon &icon, const QString &text, QObject *parent)
    : QAction(icon, text, parent)
{
//    QPalette pa;
//    pa.setColor(QPalette::Text,Qt::white);
//    setPalette(pa);
}
