#include "TextMovingWidget.h"

#include <QTimer>
#include <QPainter>

CLTextMovingWidget::CLTextMovingWidget(const QString str ,QWidget *parent)
    : QWidget(parent),m_strText(str),m_nDirection(1),m_nX(0)
{
    m_pTimer = new QTimer(this);
    connect(m_pTimer,SIGNAL(timeout()),this,SLOT(slot_updateTextGeometry()));
    m_pTimer->start(30);
}

CLTextMovingWidget::~CLTextMovingWidget()
{

}

void CLTextMovingWidget::setText(const QString &t)
{
    m_strText=t;
    m_nX=0;
    update();
}

void CLTextMovingWidget::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);
    QPainter p(this);
    p.setPen(Qt::white);
    QFontMetrics metric(font());
    int y=(height()- metric.height())/2;
    p.drawText(m_nX,y,metric.width(m_strText),metric.height(),Qt::AlignLeft,m_strText);
}

inline int CLTextMovingWidget::getDirection(const QString &text)
{
    QFontMetrics metrics(font());
    int tw=metrics.width(text);
    if(tw<=width())
    {
        if(m_nX+tw>width())
            return 0;
        else if(m_nX<=0)
        return 1;
        return m_nDirection;
    }
    else
    {
        if(m_nX==10)
          return 0;
        else if(m_nX<=width()-tw-10)
        return 1;
        return m_nDirection;
    }
}

void CLTextMovingWidget::slot_updateTextGeometry()
{
    QFontMetrics metric(font());
    int tw= metric.width(m_strText);
    if(tw>width()) //If the text width greater than widget width
    {
        if(m_nDirection) //right
            m_nX++;
        else          //left
            m_nX--;
    }
    else
    {
        if(m_nDirection) //right
            m_nX++;
        else          //left
            m_nX--;
    }
    m_nDirection=getDirection(m_strText);
    update();
}
