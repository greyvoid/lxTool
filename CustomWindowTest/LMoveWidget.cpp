#include "LMoveWidget.h"
#include <QMouseEvent>
#include <QResizeEvent>
#include <QApplication>
#include <QtDebug>

//CLMoveWidget::CLMoveWidget(QWidget *parent)
//    : QWidget(parent)
//    //, m_wgtRoot(NULL)
//{

//}

CLMoveWidget::CLMoveWidget(QWidget *parent, Qt::WindowFlags f)
: QWidget(parent, f)
, m_bCanDrag(false)
, m_pWgtDrag(NULL)
, m_bCanResize(false)
, m_nCanResizeBorder(6)
{
    initUI();
}

CLMoveWidget::~CLMoveWidget()
{

}

void CLMoveWidget::initUI()
{
    setWindowFlags(Qt::FramelessWindowHint);
    setMouseTracking(true);
    // 要检测窗口是否可以拖动大小形状改变需要让控件在鼠标未按下都能响应鼠标应当事件mouseMoveEvent
    QList<QWidget*> widgetList = findChildren<QWidget*>();
    foreach(QWidget* widget, widgetList)
    {
        widget->setMouseTracking(true);
    }
}

void CLMoveWidget::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);

    // 优先考虑窗口大小改变
    if (Qt::LeftButton & event->buttons())
    {
        if (m_bCanResize)                    //如果左键按住移动且在拖拽状态
        {
            const QPoint point_offset = event->globalPos() - m_ptResizeStart;
            m_ptResizeStart = event->globalPos();
            int nOffsetX1 = ED_LockRight == m_emHorizontal ? point_offset.x() : 0;
            int nOffsetY1 = DR_LockBottom == m_emVertical ? point_offset.y() : 0;
            int nOffsetX2 = ED_LockLeft == m_emHorizontal ? point_offset.x() : 0;
            int nOffsetY2 = ED_LockTop == m_emVertical ? point_offset.y() : 0;
            setGeometry(geometry().adjusted(nOffsetX1, nOffsetY1, nOffsetX2, nOffsetY2));
        }
    }
    else if (Qt::NoButton == event->button())
    {
        //先判断是否光标在可拖拽大小的窗口位置
        const QPoint& pos = event->pos();
        bool bHorLeft = pos.x() < m_nCanResizeBorder;
        bool bHorRight = pos.x() > rect().right() - m_nCanResizeBorder;
        bool bVertTop = pos.y() < m_nCanResizeBorder;
        bool bVertBottom = pos.y() > rect().bottom() - m_nCanResizeBorder;
        if (bHorLeft || bHorRight || bVertTop || bVertBottom)
        {
            m_bCanResize = true;
            if (bHorLeft && bVertTop)        //左上角拖拽
            {
                setCursor(Qt::SizeFDiagCursor);
                m_emHorizontal = ED_LockRight;
                m_emVertical = DR_LockBottom;
            }
            else if (bHorLeft && bVertBottom)    //左下角拖拽
            {
                setCursor(Qt::SizeBDiagCursor);
                m_emHorizontal = ED_LockRight;
                m_emVertical = ED_LockTop;
            }
            else if (bHorRight && bVertTop)        //右上角拖拽
            {
                setCursor(Qt::SizeBDiagCursor);
                m_emHorizontal = ED_LockLeft;
                m_emVertical = DR_LockBottom;
            }
            else if (bHorRight && bVertBottom)    //右下角拖拽
            {
                setCursor(Qt::SizeFDiagCursor);
                m_emHorizontal = ED_LockLeft;
                m_emVertical = ED_LockTop;
            }
            else if (bHorLeft)                    //左边框拖拽
            {
                setCursor(Qt::SizeHorCursor);
                m_emHorizontal = ED_LockRight;
                m_emVertical = ED_RemainUnchanged;
            }
            else if (bHorRight)                    //右边框拖拽
            {
                setCursor(Qt::SizeHorCursor);
                m_emHorizontal = ED_LockLeft;
                m_emVertical = ED_RemainUnchanged;
            }
            else if (bVertTop)                    //上边框拖拽
            {
                setCursor(Qt::SizeVerCursor);
                m_emHorizontal = ED_RemainUnchanged;
                m_emVertical = DR_LockBottom;
            }
            else if (bVertBottom)                //下边框拖拽
            {
                setCursor(Qt::SizeVerCursor);
                m_emHorizontal = ED_RemainUnchanged;
                m_emVertical = ED_LockTop;
            }
        }
        else if (m_bCanResize)
        {
            m_bCanResize = false;
            setCursor(Qt::ArrowCursor);            //如果上一次判断修改了光标，不再是拖拽的状态把光标改回来
        }
    }
    if (m_bCanResize)
    {
        return;
    }

    // 考虑窗口移动
    if ( m_bCanDrag )
    {
        QPoint movePot = event->globalPos() - m_ptMousePress;

        // move是移动的位置是相对于全局而言(即屏幕)
        QApplication::activeWindow()->move(movePot);
        return;
    }
}

void CLMoveWidget::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    m_ptMousePress = event->pos();
    if (Qt::LeftButton == event->button() && m_bCanResize)
    {
        m_ptResizeStart = event->globalPos();
        return;
    }

    if (m_pWgtDrag == NULL)
    {
        m_pWgtDrag = this;
    }
    QRect rectDrag = m_pWgtDrag->rect();
    if (rectDrag.contains(m_ptMousePress))
    {
        m_bCanDrag = true;
    }
}

void CLMoveWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
    m_bCanDrag=false;
}

void CLMoveWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}



