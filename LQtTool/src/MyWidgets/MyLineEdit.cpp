#include "MyLineEdit.h"
#include <QPixmap>
#include <QHBoxLayout>

QMyLineEdit::QMyLineEdit(QWidget *parent) : QLineEdit(parent)
{
//    this->setFont(QFont ("Times",20,QFont::Bold));
//    this->setFixedHeight(50);
    this->setStyleSheet("QLineEdit{background-color:black}");


    QPalette pa;
    pa.setColor(QPalette::Text,Qt::white);
    setPalette(pa);

//    QBrush myBrush;
//    QPalette palette;
//    myBrush = QBrush(Qt::red,Qt::DiagCrossPattern);
//    palette.setBrush(QPalette::Text,  myBrush);
//    setPalette(palette);

    //    //row1 控制用户电话号码输入
    //    QRegExp regExp("[1][3,4,5,8][0-9]{9}");
    //    phoneNumberLineEdit = new QMyLineEdit;
    //    phoneNumberLineEdit->setPlaceholderText("请输入手机号码");
    //    phoneNumberLineEdit->setValidator(new QRegExpValidator(regExp,this ));

    //设置背景图片
//    QWidget *widget = new QWidget;
//    widget->setFixedSize(size());
//    widget->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
//    QPalette palette = widget->palette();
//    QPixmap pixmap;
//    pixmap.fill(QColor(76,76,76));
//    palette.setBrush(QPalette::Window,QBrush(pixmap.scaled(widget->size(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));             // 使用平滑的缩放方式
//    widget->setPalette(palette);                           // 给widget加上背景图
//    QHBoxLayout *hLay = new QHBoxLayout;
//    hLay->addWidget(widget);
//    setLayout(hLay);
}

void QMyLineEdit::focusInEvent(QFocusEvent *e)
{
//       QPalette p=QPalette();
//       p.setColor(QPalette::Base,Qt::green);    //QPalette::Base 对可编辑输入框有效，还有其他类型，具体的查看文档
//       setPalette(p);
}

void QMyLineEdit::focusOutEvent(QFocusEvent *e)
{
//       QPalette p1=QPalette();
//       p1.setColor(QPalette::Base,Qt::white);
//       setPalette(p1);
}

//bool w::eventFilter(QObject * watched, QEvent *event)
//{
//    if(watched == ui->lineEdit)
//{
//        if(event->type()==QEvent::FocusIn)
//        {
//            QPalette p=QPalette();
//            p.setColor(QPalette::Base,Qt::green);
//            ui->lineEdit->setPalette(p);
//        }
//        else if (event->type()==QEvent::FocusOut)
//        {
//             QPalette p=QPalette();
//             p.setColor(QPalette::Base,Qt::white);
//             ui->lineEdit->setPalette(p);
//        }
//    }
//     return QWidget::eventFilter(watched,event);
//}


///
/// \brief MyStyleLineEdit::MyStyleLineEdit
/// \param parent
///
///

MyStyleLineEdit::MyStyleLineEdit(QWidget *parent)
    : QLineEdit(parent)
{
    setMinimumHeight(30);
    setMaximumHeight(30);
    setStyleSheet("color:rgba(184,7,235,150);font-size:16px;font-weight:470;");
    setContextMenuPolicy(Qt::NoContextMenu);
}
