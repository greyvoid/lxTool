#include "MyLabels.h"
#include <QPainter>

QClickLabel::QClickLabel(QWidget *parent):QLabel(parent)
{
    QFont smallFont("Helvetica [Cronyx]", 8);
    QPalette pa;
    pa.setColor(QPalette::ButtonText,Qt::white);
    this->setFont(smallFont);
    this->setFixedHeight(50);
    //this->setFixedSize(buttonWidth,buttonHeight);
    this->setPalette(pa);
        this->setAlignment(Qt::AlignCenter);

//    setStyleSheet("QWidget{background-color:rgb(255,255,0);border-radius:3px;}");

//    this->setFrameStyle(QFrame::Box | QFrame::Plain);
//    this->setLineWidth(2);

//    setFixedSize(400,200);
//       setStyleSheet("border-image:url(d:/800.6002.PNG);");
//    setStyleSheet("QFrame{border-radius:12px;}");
//       setStyleSheet("QLabel{border-radius:12px;}");

//         setAutoFillBackground(true);
//         windowPixmap.load("d:/800.6002.PNG");
//        QPalette pa;
//        QPixmap pixmap("d:/800.6002.PNG");
//        setWindowIcon(pixmap);
//        pa.setBrush(QPalette::Background,QBrush(pixmap));
//        setPalette(pa);
}

//void CTest::paintEvent(QPaintEvent *event)
//{
//    QPainter painter(this);
//    painter.drawPixmap(0,0,width(),height(),QPixmap(":/3.jpg"));
//}

QClickLabel::QClickLabel(const QString &text, QWidget *parent,Qt::WindowFlags f):QLabel(text, parent, f)
{
    QFont smallFont("Helvetica [Cronyx]", 8);
    QPalette pa;
    pa.setColor(QPalette::ButtonText,Qt::white);
    this->setText(text);
    this->setFont(smallFont);
    this->setFixedHeight(50);
    this->setPalette(pa);
    this->setAlignment(Qt::AlignCenter);
}

void QClickLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev)
    emit clicked();

}





QWhiteTextLabel::QWhiteTextLabel(QWidget *parent):QLabel(parent)
{
    init();
}

QWhiteTextLabel::QWhiteTextLabel(const QString &text, QWidget *parent,Qt::WindowFlags f):QLabel(text, parent, f)
{
    init();
}

void QWhiteTextLabel::init()
{
    //QFont smallFont("Helvetica [Cronyx]", 8);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    //this->setFont(smallFont);
    //this->setFixedHeight(50);
    //this->setFixedSize(buttonWidth,buttonHeight);
    this->setPalette(pa);
    //    this->setAlignment(Qt::AlignCenter);

//    setStyleSheet("QWidget{background-color:rgb(255,255,0);border-radius:3px;}");

//    this->setFrameStyle(QFrame::Box | QFrame::Plain);
//    this->setLineWidth(2);

//    setFixedSize(400,200);
//       setStyleSheet("border-image:url(d:/800.6002.PNG);");
//    setStyleSheet("QFrame{border-radius:12px;}");
//       setStyleSheet("QLabel{border-radius:12px;}");

//         setAutoFillBackground(true);
//         windowPixmap.load("d:/800.6002.PNG");
//        QPalette pa;
//        QPixmap pixmap("d:/800.6002.PNG");
//        setWindowIcon(pixmap);
//        pa.setBrush(QPalette::Background,QBrush(pixmap));
//        setPalette(pa);
}




myLabel::myLabel(QWidget *parent) :
    QLabel(parent)
{
}

void myLabel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform|QPainter::Antialiasing);
    QLabel::paintEvent(event);
}
