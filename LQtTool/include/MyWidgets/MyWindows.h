#ifndef CMYWINDOWS_H
#define CMYWINDOWS_H

#include <QWidget>

class QToolButton;
class QVBoxLayout;
class QMenuBar;
class QToolBar;
class QLabel;
class QWhiteTextLabel;

class CMyMainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CMyMainWindow(QWidget *parent = 0);
    ~CMyMainWindow();

    void setTitleOperateIcon(QString strImgClose = "", QString strImgNormal = "", QString strImgMin = "");

    QMenuBar* menuBar()
    {
        return m_menuBar;
    }

    QToolBar* toolBar()
    {
        return m_toolBar;
    }

    QWidget* centralWidget()
    {
        return m_centralWidget;
    }

    void setTitleIcon(QString strIcon);

    void setTitle(QString strTitle);
private slots:


protected:
    //改写QWidget的函数，自己重新实现拖动操作
    void mouseMoveEvent ( QMouseEvent * event );
    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent(QMouseEvent * event);

    void initTitleBar();
    void initMenuBar();
    void initToolBar();
    void initCentralWidget();

private:

    //自己重新实现拖动操作
    QPoint mousePosition;
    bool isMousePressed;
    QVBoxLayout* m_vLayMain;
    QString m_strImgClose, m_strImgNormal, m_strImgMin;
    QToolButton* m_tBtnMin, *m_tBtnClose, *m_tBtnNormal;
    QMenuBar* m_menuBar;
    QToolBar* m_toolBar;
    QWidget* m_centralWidget;
    QLabel *m_labelTitleIcon;
    QWhiteTextLabel *labelTitleText;

};

#endif // CMYWINDOWS_H
