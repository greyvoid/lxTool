#ifndef CMYBUTTON_H
#define CMYBUTTON_H

#include <QPushButton>
#include <QPaintEvent>
class QMediaPlayer;

//basPotBtn = new QPushButton(QIcon(tr(":/res/ctrl/BasicCtrl/choice.ico")), tr(""), this);
//basPotBtn->setToolTip(tr("指针")); 此函数可以显示提示

class QDoubleButton:public QPushButton
{
    Q_OBJECT
public:
    explicit QDoubleButton(QWidget *parent=0);
    explicit QDoubleButton(const QString &text, QWidget *parent=0);
protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *);
private:
signals:
    void douClick(void);
};

class QThereStatusButton:public QPushButton
{
    Q_OBJECT
public:
    explicit QThereStatusButton(QWidget *parent=0);
    explicit QThereStatusButton(const QString &text, QWidget *parent=0);

private:

};


class CLsxButton: public QWidget
{
    Q_OBJECT
public:
    CLsxButton(const QString text,QWidget *parent = 0);

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


class CLsxRadioButton: public QWidget
{
    Q_OBJECT
public:
    enum E_Btn_Status
    {
        EB_Normal,
        EB_Hover,
        EB_Press
    };

    CLsxRadioButton(const QString text,QWidget *parent = 0);

    void setBtnStatus(E_Btn_Status eBtnStatus);

    E_Btn_Status getBtnStatus()
    {
        return m_eBtnStatus;
    }

    void setPress(bool bPress);
    void initColor();
    void setTextColor(QColor colorNomal, QColor colorHover, QColor colorPress);
    void setBgColor(QColor colorNomal, QColor colorHover, QColor colorPress);
    void setBgImg(QString strImgNormal = "", QString strImgHover = "", QString strImgPress = "");

    QString text()
    {
        return m_text;
    }

signals:
    void emitStatus(E_Btn_Status);
    void clicked();
    void clicked(CLsxRadioButton*);

protected:
    void paintEvent(QPaintEvent *e);
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
    void mousePressEvent(QMouseEvent *e);
    //void mouseMoveEvent(QMouseEvent *e);//鼠标按下后移动
    void mouseReleaseEvent(QMouseEvent *e);
private:
    QRect m_rect;
    QString m_text;
    E_Btn_Status m_eBtnStatus;
    bool m_bMousePress;
    QColor m_colorTextNomal, m_colorTextHover, m_colorTextPress;
    QColor m_colorBgNomal, m_colorBgHover, m_colorBgPress;
    QString m_strImgNormal, m_strImgHover, m_strImgPress;
};



/**
 * 作者:feiyangqingyun(QQ:517216493) 2016-11-6
 * 1:可设置开关按钮的样式 圆角矩形/内圆形/外圆形/图片
 * 2:可设置选中和未选中时的背景颜色
 * 3:可设置选中和未选中时的滑块颜色
 * 4:可设置显示的文本
 * 5:可设置滑块离背景的间隔
 * 6:可设置圆角角度
 */

#include <QWidget>

class QTimer;

class SwitchButton: public QWidget
{
    Q_OBJECT
public:
    enum ButtonStyle {
        ButtonStyle_Rect = 0,     //圆角矩形
        ButtonStyle_CircleIn = 1, //内圆形
        ButtonStyle_CircleOut = 2,//外圆形
        ButtonStyle_Image = 3     //图片
    };

    SwitchButton(QWidget *parent = 0);
    ~SwitchButton();

protected:
    void mousePressEvent(QMouseEvent *);
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);
    void drawBg(QPainter *painter);
    void drawSlider(QPainter *painter);
    void drawText(QPainter *painter);
    void drawImage(QPainter *painter);

private:
    bool checked;               //是否选中
    ButtonStyle buttonStyle;    //开关按钮样式

    QColor bgColorOff;          //关闭时背景颜色
    QColor bgColorOn;           //打开时背景颜色

    QColor sliderColorOff;      //关闭时滑块颜色
    QColor sliderColorOn;       //打开时滑块颜色

    QColor textColorOff;        //关闭时文本颜色
    QColor textColorOn;         //打开时文本颜色

    QString textOff;            //关闭时显示的文字
    QString textOn;             //打开时显示的文字

    QString imageOff;           //关闭时显示的图片
    QString imageOn;            //打开时显示的图片

    int space;                  //滑块离背景间隔
    int rectRadius;             //圆角角度

    int step;                   //每次移动的步长
    int startX;                 //滑块开始X轴坐标
    int endX;                   //滑块结束X轴坐标
    QTimer *timer;              //定时器绘制

private slots:
    void updateValue();

public:
    bool getChecked()const
    {
        return checked;
    }
    ButtonStyle getButtonStyle()const
    {
        return buttonStyle;
    }

    QColor getBgColorOff()const
    {
        return bgColorOff;
    }
    QColor getBgColorOn()const
    {
        return bgColorOn;
    }

    QColor getSliderColorOff()const
    {
        return sliderColorOff;
    }
    QColor getSliderColorOn()const
    {
        return sliderColorOn;
    }

    QColor getTextColorOff()const
    {
        return textColorOff;
    }
    QColor getTextColorOn()const
    {
        return textColorOn;
    }

    QString getTextOff()const
    {
        return textOff;
    }
    QString getTextOn()const
    {
        return textOn;
    }

    QString getImageOff()const
    {
        return imageOff;
    }
    QString getImageOn()const
    {
        return imageOn;
    }

    int getSpace()const
    {
        return space;
    }
    int getRectRadius()const
    {
        return rectRadius;
    }

public slots:
    //设置是否选中
    void setChecked(bool checked);
    //设置风格样式
    void setButtonStyle(ButtonStyle buttonStyle);

    //设置背景颜色
    void setBgColor(QColor bgColorOff, QColor bgColorOn);
    //设置滑块颜色
    void setSliderColor(QColor sliderColorOff, QColor sliderColorOn);
    //设置文本颜色
    void setTextColor(QColor textColorOff, QColor textColorOn);

    //设置文本
    void setText(QString textOff, QString textOn);

    //设置背景图片
    void setImage(QString imageOff, QString imageOn);

    //设置间隔
    void setSpace(int space);
    //设置圆角角度
    void setRectRadius(int rectRadius);

signals:
    void checkedChanged(bool checked);
};



class PushButton:public QPushButton
{
    Q_OBJECT
public:
   explicit PushButton(QWidget *parent = 0);
   explicit PushButton(const QString text,QWidget *parent = 0);
   ~PushButton();

   void setBgImg(QString strImgNormal, QString strImgHover, QString strImgPress);
   void enterEvent(QEvent *);//进入事件
   void leaveEvent(QEvent *);//离开事件
   void mousePressEvent(QMouseEvent *event);  //鼠标按下事件
   void mouseReleaseEvent(QMouseEvent *event); //鼠标释放事件
   void paintEvent(QPaintEvent *);//按钮绘图事件

private:
   enum ButtonStatus{NORMAL, HOVER, PRESS};	//枚举按钮的几种状态
   ButtonStatus status;
   bool mouse_press; //按钮左键是否按下
   QString m_strImgNormal, m_strImgHover, m_strImgPress;
};



class myPushButton : public QPushButton
{
    Q_OBJECT
public:
    myPushButton(const QString &text,QWidget *parent);
    myPushButton(QWidget *parent=0);
    myPushButton(const QString &text);

signals:

public slots:

protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

private:
    void init();

private:
    QMediaPlayer *player;
    //QCursor *cursor;

};

#endif // CMYBUTTON_H
