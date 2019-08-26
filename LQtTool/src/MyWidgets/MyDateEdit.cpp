#include "MyDateEdit.h"

CMyDateEdit::CMyDateEdit(QWidget *parent)
    : QDateEdit(parent)
{
    init();
}

CMyDateEdit::CMyDateEdit(const QDate &date, QWidget *parent)
    : QDateEdit(date, parent)
{
    init();
}

void CMyDateEdit::init()
{
    QPalette pa;
    pa.setColor(QPalette::Text,Qt::white);
    setPalette(pa);
}

