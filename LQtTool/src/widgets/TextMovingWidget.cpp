#include "TextMovingWidget.h"

#include <QTimer>
#include <QPainter>

TextMovingWidget::TextMovingWidget(const QString str ,QWidget *parent)
    : QWidget(parent),_text(str),m_direction(1),m_x(0)
{
    _timer=new QTimer(this);
    connect(_timer,SIGNAL(timeout()),this,SLOT(slot_UpdateTextGeometry()));
    _timer->start(30);
}

TextMovingWidget::~TextMovingWidget(){}

void TextMovingWidget::setText(const QString &t)
{
    _text=t;
    m_x=0;
    update();
}

void TextMovingWidget::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);
    QPainter p(this);
    p.setPen(Qt::white);
    QFontMetrics metric(font());
    int y=(height()- metric.height())/2;
    p.drawText(m_x,y,metric.width(_text),metric.height(),Qt::AlignLeft,_text);
}

inline int TextMovingWidget::getDirection(const QString &text)
{
    QFontMetrics metrics(font());
    int tw=metrics.width(text);
    if(tw<=width())
    {
        if(m_x+tw>width())
            return 0;
        else if(m_x<=0)
        return 1;
        return m_direction;
    }
    else
    {
        if(m_x==10)
          return 0;
        else if(m_x<=width()-tw-10)
        return 1;
        return m_direction;
    }
}

void TextMovingWidget::slot_UpdateTextGeometry()
{
    QFontMetrics metric(font());
    int tw= metric.width(_text);
    if(tw>width()) //If the text width greater than widget width
    {
        if(m_direction) //right
            m_x++;
        else          //left
            m_x--;
    }
    else
    {
        if(m_direction) //right
            m_x++;
        else          //left
            m_x--;
    }
    m_direction=getDirection(_text);
    update();
}
