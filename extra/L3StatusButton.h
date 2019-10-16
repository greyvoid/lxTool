#ifndef CL3STATUSBUTTON_H
#define CL3STATUSBUTTON_H

#include <QPushButton>
#include <QString>
#include <QWidget>

class CL3StatusButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(int curIndex READ getcurIndex WRITE setcurIndex)

public:
    CL3StatusButton( QString FileName, int xnum  = 1,  QWidget *parent = 0,
            int ynum = 1, QString bkGrnd = NULL);
    CL3StatusButton(QVector<QString> &list, QWidget *parent = 0, QString bkGrnd = NULL);

    QList<QPixmap> *getPixmapList(void){return &pixmatpList;}
    void setcurIndex(int index){curIndex = index; update();}
    int getcurIndex(void){return curIndex;}

private:
    void setPixmapList(QVector<QString> &list);
    QPixmap *background;

protected:
    QList<QPixmap> pixmatpList;
    int curIndex;

protected:
    virtual void paintEvent ( QPaintEvent * event);
    virtual void enterEvent(QEvent *event);
    virtual void leaveEvent ( QEvent * event );
    virtual void mousePressEvent ( QMouseEvent * event ) ;
    virtual void mouseReleaseEvent ( QMouseEvent * event );
    virtual  QSize sizeHint () const;

};

#endif // CL3STATUSBUTTON_H
