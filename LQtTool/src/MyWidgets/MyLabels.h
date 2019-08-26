#ifndef CMYLABELS_H
#define CMYLABELS_H

#include <QLabel>

class QClickLabel:public QLabel
{
    Q_OBJECT
public:
    explicit QClickLabel(QWidget *parent=0);
    explicit QClickLabel(const QString &text, QWidget *parent=0, Qt::WindowFlags f=0);
private:
    signals:
    void clicked(void);
protected:
    virtual void mouseReleaseEvent(QMouseEvent *ev);


};

class QWhiteTextLabel:public QLabel
{
    Q_OBJECT
public:
    explicit QWhiteTextLabel(QWidget *parent=0);
    explicit QWhiteTextLabel(const QString &text, QWidget *parent=0, Qt::WindowFlags f=0);
private:
    void init();
};


class myLabel : public QLabel
{
    Q_OBJECT
public:
    explicit myLabel(QWidget *parent = 0);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *);

};

#endif // CMYLABELS_H
