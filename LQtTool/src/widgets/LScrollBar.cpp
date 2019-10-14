#include "LScrollBar.h"


CLScrollBar::CLScrollBar(QWidget *parent)
    : QScrollBar(parent)
{
    init();
}

CLScrollBar::CLScrollBar(Qt::Orientation, QWidget *parent)
    : QScrollBar(Qt::Orientation, parent)
{
    init();
}

void CLScrollBar::onValueChanged(int nValue)
{
    if (nValue == maximum())
    {
        emit reachedBottom();
    }
}

void CLScrollBar::init()
{
    connect(this, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged()));
    // 可以采用闭包函数
}
