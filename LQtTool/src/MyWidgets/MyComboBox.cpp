#include "MyComboBox.h"

MyComboBox::MyComboBox(QWidget *parent)
{

    QPalette pa;
    pa.setColor(QPalette::Text,Qt::white);
    setPalette(pa);
}

MyComboBox::~MyComboBox()
{

}

void MyComboBox::setDownArrowImg(QString strImgPath)
{
    setStyleSheet("QComboBox{border:1px solid gray;}"
      "QComboBox QAbstractItemView::item{height:20px;}" //下拉选项高度
      "QComboBox::down-arrow{image:url("+strImgPath+");}" //下拉箭头
      "QComboBox::drop-down{border:0px;}"); //下拉按钮

}

