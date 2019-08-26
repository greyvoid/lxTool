#ifndef MY_DATEEDIT_H
#define MY_DATEEDIT_H

#include <QDateEdit>

class CMyDateEdit:public QDateEdit
{
    Q_OBJECT
public:
    explicit CMyDateEdit(QWidget *parent=0);
    explicit CMyDateEdit(const QDate & date, QWidget * parent = 0);
private:
    void init();

};



#endif // MY_DATEEDIT_H
