#ifndef TEXTMOVINGWIDGET_H
#define TEXTMOVINGWIDGET_H
#include <QWidget>

class QTimer;


///
/// \brief The TextMovingWidget class 跑马灯（走马灯）horse race lamp
///
class TextMovingWidget : public QWidget
{
    Q_OBJECT

public:
    TextMovingWidget(const QString str="" ,QWidget *parent = 0);
    ~TextMovingWidget();
    void setText(const QString&);
protected:
    virtual void paintEvent(QPaintEvent*);
    inline int getDirection(const QString&);
private slots:
    void slot_UpdateTextGeometry();
private:
    QTimer *_timer;
    QString _text;
    int m_direction; //zero means left ,one means right;
    int m_x;
};

#endif // TEXTMOVINGWIDGET_H
