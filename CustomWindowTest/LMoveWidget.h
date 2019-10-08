#ifndef CLMOVEWIDGET_H
#define CLMOVEWIDGET_H
#include <QWidget>


enum E_DragAbsolutePosition
{
    ED_RemainUnchanged=0,
    ED_LockLeft,
    ED_LockTop=1,
    ED_LockRight,
    DR_LockBottom=2
};

class CLMoveWidget : public QWidget
{
    Q_OBJECT
public:
    //explicit CLMoveWidget(QWidget *parent = 0);
    explicit CLMoveWidget(QWidget* parent = 0, Qt::WindowFlags f = 0);
    ~CLMoveWidget();

signals:

public slots:
protected:
    //改写QWidget的函数，自己重新实现拖动操作
    void mouseMoveEvent ( QMouseEvent * event );
    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent(QMouseEvent * event);
    void resizeEvent(QResizeEvent *event);
//    void setRootWidget(QWidget* wgtRoot)
//    {
//        m_wgtRoot = wgtRoot;
//    }
    void setRectWidgetDrag(QWidget* pWgtDrag)
    {
        m_pWgtDrag = pWgtDrag;
    }

private:
    void initUI();

protected:
    // 鼠标按下的位置
    QPoint m_ptMousePress;
    // 是否可以拖动窗口
    bool m_bCanDrag;
    // 鼠标按在某个控件的区域上可以拖动窗口，默认指定整个窗口
    QWidget* m_pWgtDrag;
    //
    bool m_bCanResize;

    int m_nCanResizeBorder;

    QPoint m_ptResizeStart;

    E_DragAbsolutePosition m_emHorizontal;

    E_DragAbsolutePosition m_emVertical;
};

#endif // CLMOVEWIDGET_H
