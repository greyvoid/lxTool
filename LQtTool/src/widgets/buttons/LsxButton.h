#ifndef CLSXBUTTON_H
#define CLSXBUTTON_H

#include <QWidget>

class CLsxButton: public QWidget
{
    Q_OBJECT
public:
    CLsxButton(const QString text, QWidget *parent = 0);

signals:
    void clicked();


protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    //void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
private:
    QRect m_rect;
    QString m_text;
    bool m_bPress;

};

#endif // CLSXBUTTON_H
