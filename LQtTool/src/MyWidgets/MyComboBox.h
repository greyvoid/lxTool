#ifndef MYCOMBOBOX_H
#define MYCOMBOBOX_H

#include <QComboBox>

class MyComboBox : public QComboBox
{
    Q_OBJECT
public:
    MyComboBox(QWidget* parent = 0);
    ~MyComboBox();

    void setDownArrowImg(QString strImgPath);
};

#endif // MYCOMBOBOX_H
