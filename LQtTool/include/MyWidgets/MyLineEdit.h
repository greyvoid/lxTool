#ifndef CMYLINEEDIT_H
#define CMYLINEEDIT_H

#include <QLineEdit>

class QMyLineEdit : public QLineEdit
{
public:
    explicit QMyLineEdit(QWidget *parent=0);

protected:
    virtual void focusInEvent(QFocusEvent *e);
           virtual void focusOutEvent(QFocusEvent *e);
    //bool eventFilter(QObject *,QEvent *);
};

class MyStyleLineEdit : public QLineEdit
{
public:
    explicit MyStyleLineEdit(QWidget *parent=0);

protected:
};

#endif // CMYLINEEDIT_H
