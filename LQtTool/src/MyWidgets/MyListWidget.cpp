#include "MyListWidget.h"

QMyListWidget::QMyListWidget()
{
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setFocusPolicy(Qt::NoFocus);
    this->setFrameShape(QFrame::NoFrame);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

//border-radius: 10px  边框弧度
//border: 2px groove gray;
//border-style:outset; inset
//border-left
//border-left-color,border-left-style
//border-image
//selection-color

//    QPalette pa;
//    pa.setColor(QPalette::WindowText, Qt::white);
//    QLabel *label = new QLabel;
//           label->setText("hello Qt");
//           label->setPalette(pa);
//           label->setFont(QFont("Times", 12, QFont::Bold));
//          this->setCentralWidget(label);

//    QPixmap("d:/qt4logo.png").save(&buffer,"BMP");

//    QPixmap pix(100,100);
//    QPainter p(&pix);
//    p.drawText(0,10,"helloWorld");
//    p.end();
//    pix.save("a.png");

