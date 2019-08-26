#include "MyButtons.h"
#include <QPainter>
#include <QtDebug>
#include <QtMultimedia/QMediaPlayer>

QDoubleButton::QDoubleButton(QWidget *parent):QPushButton(parent)
{
    QPalette pa;
    pa.setColor(QPalette::ButtonText,Qt::white);
    this->setFont(QFont ("Times",20,QFont::Bold));
    this->setStyleSheet("QPushButton{background-color:rgb(56,121,255)}");
    this->setFocusPolicy(Qt::NoFocus);
    this->setFixedHeight(50);
    this->setPalette(pa);

    //    button = new QPushButton;
    //    //button->setText("Hello");
    //    button->setFixedSize(200,80);
    //    button->setFocusPolicy(Qt::NoFocus);
    //    button->setAutoFillBackground(true);
    //    QPixmap pix1("d:/callEnd.png");
    //    QPixmap pix2 = pix1.scaled(180,70,Qt::KeepAspectRatio);
    //    button->setIcon(pix2);
    //    button->setIconSize(button->size() * 0.7);
    //    button->setAutoRepeat(true);
    //    button->setAutoRepeatDelay(1000);
}
QDoubleButton::QDoubleButton(const QString &text, QWidget *parent):QPushButton(text, parent)
{
    QPalette pa;
    pa.setColor(QPalette::ButtonText,Qt::white);
    this->setText(text);
    this->setFont(QFont ("Times",20,QFont::Bold));
    this->setStyleSheet("QPushButton{background-color:rgb(56,121,255)}");
    this->setFocusPolicy(Qt::NoFocus);
    this->setFixedHeight(50);
    this->setPalette(pa);
}

void QDoubleButton::mouseDoubleClickEvent(QMouseEvent *e)
{
    //    if(e->buttons()==Qt::LeftButton)
    //    {
    //        emit douClick();
    //    }
}



QThereStatusButton::QThereStatusButton(QWidget *parent):QPushButton(parent)
{

}

QThereStatusButton::QThereStatusButton(const QString &text, QWidget *parent):QPushButton(text, parent)
{
    setStyleSheet("QPushButton{border-image: url(:/img/btn_style_normal.png);}"
                  "QPushButton:hover{border-image: url(:/img/btn_style_v.png);color: rgb(0, 255, 127);}"
                  "QPushButton:pressed{border-image: url(:/img/btn_style_down.png);}");
}


/******************************************************
 *
 * class CLsxButton
 *
 */

CLsxButton::CLsxButton(const QString text, QWidget *parent)
    : QWidget(parent)
    , m_text(text)
    , m_rect(QRect(0, 0, 90, 25))
    , m_bPress(false)
{

}

void CLsxButton::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    if(m_bPress)
    {
        p.setBrush(Qt::darkYellow);        //用画刷来画自己喜欢的颜色
    }
    else
    {
        p.setBrush(Qt::darkGreen);
    }
    p.drawEllipse(m_rect);                    //  有4个参数，分别是位置和长宽，如果长和宽相等就是一个标准的圆了
    p.drawText(m_rect,m_text,QTextOption(Qt::AlignCenter)); //设置文本有三个参数，分别是 对象，文本，文本位置

}

void CLsxButton::mousePressEvent(QMouseEvent *e)
{
    m_bPress = false;

    this->update();             //点击一下更新一下，调用painEvent
}

void CLsxButton::mouseReleaseEvent(QMouseEvent *e)
{
    m_bPress = true;

    this->update();             //点击一下更新一下，调用painEvent
}



/******************************************************
 *
 * class CLsxRadioButton
 *
 */

CLsxRadioButton::CLsxRadioButton(const QString text, QWidget *parent)
    : QWidget(parent)
    , m_text(text)
    , m_rect(QRect(0, 0, 120, 25))
    , m_bMousePress(false)
    , m_eBtnStatus(EB_Normal)
{
    //, m_rect(QRect(0, 0, 90, 25))
    setFixedSize(m_rect.size());
    initColor();
}

void CLsxRadioButton::setBtnStatus(CLsxRadioButton::E_Btn_Status eBtnStatus)
{
    m_eBtnStatus = eBtnStatus;
    update();
}

void CLsxRadioButton::setPress(bool bPress)
{
    m_bMousePress = bPress;
    if (m_bMousePress)
    {
        m_eBtnStatus = EB_Press;
    }
    else
    {
        m_eBtnStatus = EB_Normal;
    }
    update();
}

void CLsxRadioButton::initColor()
{
    m_colorBgNomal = QColor(0,0,0);
    m_colorBgHover = QColor(0,0,0);
    m_colorBgPress = QColor(0,0,0);
    m_colorTextNomal = QColor(255,255,255);
    m_colorTextHover = QColor(6,164,166);
    m_colorTextPress = QColor(6,164,166);
    m_strImgNormal = ":/img/btn_style_normal.png";
    m_strImgHover = ":/img/btn_style_normal.png";
    m_strImgPress = ":/img/btn_style_down.png";
}

void CLsxRadioButton::setTextColor(QColor colorNomal, QColor colorHover, QColor colorPress)
{
    m_colorBgNomal = colorNomal;
    m_colorBgHover = colorHover;
    m_colorBgPress = colorPress;
}

void CLsxRadioButton::setBgColor(QColor colorNomal, QColor colorHover, QColor colorPress)
{
    m_colorTextNomal = colorNomal;
    m_colorTextHover = colorHover;
    m_colorTextPress = colorPress;
}

void CLsxRadioButton::setBgImg(QString strImgNormal, QString strImgHover, QString strImgPress)
{
    m_strImgNormal = strImgNormal;
    m_strImgHover = strImgHover;
    m_strImgPress = strImgPress;
}

void CLsxRadioButton::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    QPixmap pixmap;
    QString imgPath;
    switch (m_eBtnStatus) {
    case EB_Normal:
        //p.setBrush(Qt::darkYellow);        //用画刷来画自己喜欢的颜色
        p.setPen(m_colorTextNomal);
        imgPath = m_strImgNormal;
        //p.setPen(Qt::red);
        break;
    case EB_Hover:
        //p.setBrush(Qt::darkGreen);
        p.setPen(m_colorTextHover);
        imgPath = m_strImgHover;
        break;
    case EB_Press:
        //p.setBrush(Qt::red);
        p.setPen(m_colorTextPress);
        imgPath = m_strImgPress;
        break;
    default:
        break;
    }
    if (!imgPath.isEmpty())
    {
        pixmap.load(imgPath);
        p.drawPixmap(rect(), pixmap);
    }
    else
    {
        p.drawEllipse(m_rect); //  有4个参数，分别是位置和长宽，如果长和宽相等就是一个标准的圆了
    }
    p.drawText(m_rect,m_text,QTextOption(Qt::AlignCenter)); //设置文本有三个参数，分别是 对象，文本，文本位置
    qDebug() << "111111111" << rect().size().width() << rect().size().height();
}

void CLsxRadioButton::enterEvent(QEvent *e)
{
    if (m_bMousePress)
    {
        return;
    }
    m_eBtnStatus = EB_Hover;
    update();
}

void CLsxRadioButton::leaveEvent(QEvent *e)
{
    if (m_bMousePress)
    {
        return;
    }
    m_eBtnStatus = EB_Normal;
        update();
}

void CLsxRadioButton::mousePressEvent(QMouseEvent *e)
{
    //m_eBtnStatus = EB_Press;
    //update();             //点击一下更新一下，调用painEvent
    if(e->button() == Qt::LeftButton)
        {
            m_bMousePress = true;
            m_eBtnStatus = EB_Press;
            clicked();
            clicked(this);
            update();
        }
}

//void CLsxRadioButton::mouseMoveEvent(QMouseEvent *e)
//{
//    m_eBtnStatus = EB_Hover;
//    update();
//}

void CLsxRadioButton::mouseReleaseEvent(QMouseEvent *e)
{
//    //若点击鼠标左键响应
//        if(m_bMousePress && this->rect().contains(e->pos()))
//        {
//            m_bMousePress = false;
//            m_eBtnStatus = EB_Hover;
//            update();
//            emit clicked();
//        }
}


/************************************************************************
 *
 *
 *
 *
 */

#include "qpainter.h"
#include "qevent.h"
#include "qtimer.h"
#include "qdebug.h"

SwitchButton::SwitchButton(QWidget *parent): QWidget(parent)
{
    checked = false;
    buttonStyle    = ButtonStyle_Rect;

    bgColorOff = QColor(225, 225, 225);
    bgColorOn = QColor(250, 250, 250);

    sliderColorOff = QColor(100, 100, 100);
    sliderColorOn = QColor(100, 184, 255);

    textColorOff = QColor(255, 255, 255);
    textColorOn = QColor(10, 10, 10);

    textOff = "";
    textOn = "";

    imageOff = ":/image/btncheckoff1.png";
    imageOn = ":/image/btncheckon1.png";

    space = 2;
    rectRadius = 5;

    step = width() / 50;
    startX = 0;
    endX = 0;

    timer = new QTimer(this);
    timer->setInterval(5);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));

    setFont(QFont("Microsoft Yahei", 10));
}

SwitchButton::~SwitchButton()
{

}

void SwitchButton::mousePressEvent(QMouseEvent *)
{
    checked = !checked;
    emit checkedChanged(checked);

    //每次移动的步长为宽度的 50分之一
    step = width() / 50;

    //状态切换改变后自动计算终点坐标
    if (checked) {
        if (buttonStyle == ButtonStyle_Rect) {
            endX = width() - width() / 2;
            } else if (buttonStyle == ButtonStyle_CircleIn) {
            endX = width() - height();
            } else if (buttonStyle == ButtonStyle_CircleOut) {
            endX = width() - height() + space;
            }
        } else {
        endX = 0;
        }

    timer->start();
}

void SwitchButton::resizeEvent(QResizeEvent *)
{
    //每次移动的步长为宽度的 50分之一
    step = width() / 50;

    //尺寸大小改变后自动设置起点坐标为终点
    if (checked) {
        if (buttonStyle == ButtonStyle_Rect) {
            startX = width() - width() / 2;
            } else if (buttonStyle == ButtonStyle_CircleIn) {
            startX = width() - height();
            } else if (buttonStyle == ButtonStyle_CircleOut) {
            startX = width() - height() + space;
            }
        } else {
        startX = 0;
        }

    update();
}

void SwitchButton::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (buttonStyle == ButtonStyle_Image) {
        //绘制图片
        drawImage(&painter);
        } else {
        //绘制背景
        drawBg(&painter);
        //绘制滑块
        drawSlider(&painter);
        //绘制文字
        drawText(&painter);
        }
}

void SwitchButton::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    if (!checked) {
        painter->setBrush(bgColorOff);
        } else {
        painter->setBrush(bgColorOn);
        }

    if (buttonStyle == ButtonStyle_Rect) {
        painter->drawRoundedRect(rect(), rectRadius, rectRadius);
        } else if (buttonStyle == ButtonStyle_CircleIn) {
        QRect rect(0, 0, width(), height());
        //半径为高度的一半
        int radius = rect.height() / 2;
        //圆的宽度为高度
        int circleWidth = rect.height();

        QPainterPath path;
        path.moveTo(radius, rect.left());
        path.arcTo(QRectF(rect.left(), rect.top(), circleWidth, circleWidth), 90, 180);
        path.lineTo(rect.width() - radius, rect.height());
        path.arcTo(QRectF(rect.width() - rect.height(), rect.top(), circleWidth, circleWidth), 270, 180);
        path.lineTo(radius, rect.top());

        painter->drawPath(path);
        } else if (buttonStyle == ButtonStyle_CircleOut) {
        QRect rect(space, space, width() - space * 2, height() - space * 2);
        painter->drawRoundedRect(rect, rectRadius, rectRadius);
        }

    painter->restore();
}

void SwitchButton::drawSlider(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    if (!checked) {
        painter->setBrush(sliderColorOff);
        } else {
        painter->setBrush(sliderColorOn);
        }

    if (buttonStyle == ButtonStyle_Rect) {
        int sliderWidth = width() / 2 - space * 2;
        int sliderHeight = height() - space * 2;
        QRect sliderRect(startX + space, space, sliderWidth , sliderHeight);
        painter->drawRoundedRect(sliderRect, rectRadius, rectRadius);
        } else if (buttonStyle == ButtonStyle_CircleIn) {
        QRect rect(0, 0, width(), height());
        int sliderWidth = rect.height() - space * 2;
        QRect sliderRect(startX + space, space, sliderWidth, sliderWidth);
        painter->drawEllipse(sliderRect);
        } else if (buttonStyle == ButtonStyle_CircleOut) {
        QRect rect(0, 0, width() - space, height() - space);
        int sliderWidth = rect.height();
        QRect sliderRect(startX, space / 2, sliderWidth, sliderWidth);
        painter->drawEllipse(sliderRect);
        }

    painter->restore();
}

void SwitchButton::drawText(QPainter *painter)
{
    painter->save();

    if (!checked) {
        painter->setPen(textColorOff);
        painter->drawText(width() / 2, 0, width() / 2 - space, height(), Qt::AlignCenter, textOff);
        } else {
        painter->setPen(textColorOn);
        painter->drawText(0, 0, width() / 2 + space * 2, height(), Qt::AlignCenter, textOn);
        }

    painter->restore();
}

void SwitchButton::drawImage(QPainter *painter)
{
    painter->save();

    QPixmap pix;

    if (!checked) {
        pix = QPixmap(imageOff);
        } else {
        pix = QPixmap(imageOn);
        }

    //自动等比例平滑缩放居中显示
    int targetWidth = pix.width();
    int targetHeight = pix.height();
    pix = pix.scaled(targetWidth, targetHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    int pixX = rect().center().x() - targetWidth / 2;
    int pixY = rect().center().y() - targetHeight / 2;
    QPoint point(pixX, pixY);
    painter->drawPixmap(point, pix);

    painter->restore();
}

void SwitchButton::updateValue()
{
    if (checked) {
        if (startX < endX) {
            startX = startX + step;
            } else {
            startX = endX;
            timer->stop();
            }
        } else {
        if (startX > endX) {
            startX = startX - step;
            } else {
            startX = endX;
            timer->stop();
            }
        }

    update();
}

void SwitchButton::setChecked(bool checked)
{
    if (this->checked != checked) {
        this->checked = checked;
        emit checkedChanged(checked);
        update();
        }
}

void SwitchButton::setButtonStyle(SwitchButton::ButtonStyle buttonStyle)
{
    this->buttonStyle = buttonStyle;
    update();
}

void SwitchButton::setBgColor(QColor bgColorOff, QColor bgColorOn)
{
    this->bgColorOff = bgColorOff;
    this->bgColorOn = bgColorOn;
    update();
}

void SwitchButton::setSliderColor(QColor sliderColorOff, QColor sliderColorOn)
{
    this->sliderColorOff = sliderColorOff;
    this->sliderColorOn = sliderColorOn;
    update();
}

void SwitchButton::setTextColor(QColor textColorOff, QColor textColorOn)
{
    this->textColorOff = textColorOff;
    this->textColorOn = textColorOn;
    update();
}

void SwitchButton::setText(QString textOff, QString textOn)
{
    this->textOff = textOff;
    this->textOn = textOn;
    update();
}

void SwitchButton::setImage(QString imageOff, QString imageOn)
{
    this->imageOff = imageOff;
    this->imageOn = imageOn;
    update();
}

void SwitchButton::setSpace(int space)
{
    this->space = space;
    update();
}

void SwitchButton::setRectRadius(int rectRadius)
{
    this->rectRadius = rectRadius;
    update();
}





/**********************************************************
 *
 *
 */
PushButton::PushButton(QWidget *parent)
    :QPushButton(parent)
{
    status = NORMAL;
    mouse_press = false;
    resize(QSize(90,25));
    m_strImgNormal = ":/img/btn_style_normal.png";
    m_strImgHover = ":/img/btn_style_normal.png";
    m_strImgPress = ":/img/btn_style_down.png";
}

PushButton::PushButton(const QString text, QWidget *parent)
    : QPushButton(text, parent)
{
    setText(text);
    status = NORMAL;
    mouse_press = false;
    resize(QSize(90,25));
    m_strImgNormal = ":/img/btn_style_normal.png";
    m_strImgHover = ":/img/btn_style_normal.png";
    m_strImgPress = ":/img/btn_style_down.png";
}
PushButton::~PushButton()
{

}


void PushButton::setBgImg(QString strImgNormal, QString strImgHover, QString strImgPress)
{
    m_strImgNormal = strImgNormal;
    m_strImgHover = strImgHover;
    m_strImgPress = strImgPress;
    resize(QPixmap(m_strImgNormal).size());
}

void PushButton::enterEvent(QEvent *)
{
    status = HOVER;
    update();
}
void PushButton::mousePressEvent(QMouseEvent *event)
{
    //若点击鼠标左键
    if(event->button() == Qt::LeftButton)
    {
        mouse_press = true;
        status = PRESS;
        update();
    }
}
void PushButton::mouseReleaseEvent(QMouseEvent *event)
{
    //若点击鼠标左键响应
    if(mouse_press&&this->rect().contains(event->pos()))
    {
        mouse_press = false;
        status = HOVER;
        update();
        emit clicked();
    }
}
void PushButton::leaveEvent(QEvent *)
{
    status = NORMAL;
    update();
}
void PushButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pixmap;
    switch(status)
    {
    case NORMAL:
        {
            painter.setPen(QColor(255,255,255));
            pixmap.load(m_strImgNormal);
            break;
        }
    case HOVER:
        {
            painter.setPen(QColor(6,164,166));
            pixmap.load(m_strImgHover);
            break;
        }
    case PRESS:
        {
            pixmap.load(m_strImgPress);
            break;
        }
    default:
        pixmap.load(m_strImgNormal);
    }
    painter.drawPixmap(rect(), pixmap);
    painter.drawText(this->rect(), Qt::AlignCenter, this->text());
}



/*********************************************************************
 *
 *
 *
 */


myPushButton::myPushButton(const QString &text,QWidget *parent) :
    QPushButton(text,parent)
{
    init();
}

myPushButton::myPushButton(QWidget *parent) :
    QPushButton(parent)
{
    init();
}

myPushButton::myPushButton(const QString &text) :
    QPushButton(text,0)
{
    init();
}

void myPushButton::enterEvent(QEvent *)
{
    //鼠标进入按钮播放音效->(开始)
    player->setMedia(QUrl(":/voice/PICKUP.WAV"));
    player->setVolume(200);
    player->play();
    //鼠标进入按钮播放音效<-(结束)
}

void myPushButton::leaveEvent(QEvent *)
{
    player->stop();
}

void myPushButton::init()
{
    QPalette pa;
    pa.setColor(QPalette::ButtonText,Qt::white);
    this->setPalette(pa);
    player=new QMediaPlayer(this);
    //cursor=new QCursor(QPixmap(":/new/prefix1/test.png"));
    //setCursor(*cursor);
}
