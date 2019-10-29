#ifndef TEXTMOVINGWIDGET_H
#define TEXTMOVINGWIDGET_H
#include <QWidget>

class QTimer;


///
/// \brief The TextMovingWidget class 跑马灯（走马灯）horse race lamp
///
class CLTextMovingWidget : public QWidget
{
    Q_OBJECT

public:
    CLTextMovingWidget(const QString str="" ,QWidget *parent = 0);
    ~CLTextMovingWidget();
    void setText(const QString&);
protected:
    virtual void paintEvent(QPaintEvent*);
    inline int getDirection(const QString&);

private slots:
    void slot_updateTextGeometry();

private:
    QTimer *m_pTimer;
    QString m_strText;
    int m_nDirection; //zero means left ,one means right;
    int m_nX;
};

#endif // TEXTMOVINGWIDGET_H
