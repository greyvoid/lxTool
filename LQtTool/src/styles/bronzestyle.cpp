#include <QtGui>

#include <QAbstractButton>
#include <QAbstractSpinBox>
#include <QDialogButtonBox>
#include <QStyleOptionComplex>
#include "bronzestyle.h"

//通用属性
void BronzeStyle::polish(QPalette &palette)
{
    //设置背景
    //QPixmap backgroundImage(":/images/background.png");
    //设置按钮颜色
    QColor bronze(207, 155, 95);
    //设置背景框颜色
    QColor veryLightBlue(239, 239, 247);
    //要加深的颜色
    QColor lightBlue(223, 223, 239);
    //选中后的颜色
    QColor darkBlue(95, 95, 191);

    //创建一个新的面板
    palette = QPalette(bronze);
    //设置背景
    palette.setBrush(QPalette::Window, QColor("white"));
    //设置背景框颜色
    palette.setBrush(QPalette::Base, veryLightBlue);
    //设置加深的颜色
    palette.setBrush(QPalette::AlternateBase, lightBlue);
    //设置选中的颜色
    palette.setBrush(QPalette::Highlight, darkBlue);
    //设置样式
    palette.setBrush(QPalette::Disabled, QPalette::Highlight,
                     Qt::darkGray);
}

//当样式应用到窗口部件时
// 这里，我们重新实现了 polish( QWidget 骨) ，以便在按钮和微调框中设置'Qt:: WA_Hover 属性。
//当这一属性被设置、鼠标进入或者离开窗口部件所在的区域时，会产生一个绘制事件。这给我们
//一个机会，可以根据鼠标是否位于窗口部件上把窗口部件绘制出不同的样子。
void BronzeStyle::polish(QWidget *widget)
{
    //设置Qt::WA-Hover属性,鼠标进入或者离开窗口部件所在区域
    //会产生一个绘制事件
    if (qobject_cast<QAbstractButton *>(widget)
            || qobject_cast<QAbstractSpinBox *>(widget))
        widget->setAttribute(Qt::WA_Hover, true);
}

//取消polish的作用
void BronzeStyle::unpolish(QWidget *widget)
{
    if (qobject_cast<QAbstractButton *>(widget)
            || qobject_cast<QAbstractSpinBox *>(widget))
        widget->setAttribute(Qt::WA_Hover, false);
}

//函数返回一些关于样式外观的提示
int BronzeStyle::styleHint(StyleHint which, const QStyleOption *option,
                           const QWidget *widget,
                           QStyleHintReturn *returnData) const
{
    switch (which) {
    case SH_DialogButtonLayout:
        return int(QDialogButtonBox::MacLayout);
    case SH_EtchDisabledText:
        return int(true);
    case SH_DialogButtonBox_ButtonsHaveIcons:
        return int(true);
    case SH_UnderlineShortcut:
        return int(false);
    default:
        return QCommonStyle::styleHint(which, option, widget,
                                        returnData);
    }
}

//返回一个像素值,用于用户界面元素中
int BronzeStyle::pixelMetric(PixelMetric which,
                             const QStyleOption *option,
                             const QWidget *widget) const
{
    switch (which) {
    //返回0是因为不希望在默认的按钮旁边保留额外的空间
    case PM_ButtonDefaultIndicator:
        return 0;
    //指示器大小是一个正方形
    case PM_IndicatorWidth:
    case PM_IndicatorHeight:
        return 16;
    //控制指示器和其右边的文字之间的距离
    case PM_CheckBoxLabelSpacing:
        return 8;
    //定义QFrame,QPushButton,QSpinBox以及其他的一些窗口部件的
    //线宽.
    case PM_DefaultFrameWidth:
        return 2;
    //对于其他的PM_xxx值,从基类中继承像素规格的值
    default:
        return QCommonStyle::pixelMetric(which, option, widget);
    }
}

//绘制基本的用户界面元素
void BronzeStyle::drawPrimitive(PrimitiveElement which,
                                const QStyleOption *option,
                                QPainter *painter,
                                const QWidget *widget) const
{
    switch (which) {
    //会被QCheckBox,QGroupBox和QItemDelegate用来绘制选择指示器
    case PE_IndicatorCheckBox:
        drawBronzeCheckBoxIndicator(option, painter);
        break;
    case PE_PanelButtonCommand:
        drawBronzeBevel(option, painter);
        break;
    case PE_Frame:
        drawBronzeFrame(option, painter);
        break;
        //对与PE_FrameDefaultButton什么都不做
        //避免在默认的按钮旁边另外再绘制一个多余的边框
    case PE_FrameDefaultButton:
        break;
    default:
        QCommonStyle::drawPrimitive(which, option, painter, widget);
    }
}

//绘制多重辅助控制器窗口部件
void BronzeStyle::drawComplexControl(ComplexControl which,
                                     const QStyleOptionComplex *option,
                                     QPainter *painter,
                                     const QWidget *widget) const
{
    //重新实现了drawComplexControl
    if (which == CC_SpinBox) {
        drawBronzeSpinBoxButton(SC_SpinBoxDown, option, painter);
        drawBronzeSpinBoxButton(SC_SpinBoxUp, option, painter);

        QRect rect = subControlRect(CC_SpinBox, option,
                                    SC_SpinBoxEditField)
                     .adjusted(-1, 0, +1, 0);
        //painter->setPen(QPen(option->palette.mid(), 1.0));
        painter->setPen(QPen(option->palette.mid(), 1.0));
        painter->drawLine(rect.topLeft(), rect.bottomLeft());
        painter->drawLine(rect.topRight(), rect.bottomRight());
    } else {
        return QCommonStyle::drawComplexControl(which, option, painter,
                                                 widget);
    }
}

//确认辅助控制器窗口部件的位置
QRect BronzeStyle::subControlRect(ComplexControl whichControl,
                                  const QStyleOptionComplex *option,
                                  SubControl whichSubControl,
                                  const QWidget *widget) const
{
    if (whichControl == CC_SpinBox) {
        int frameWidth = pixelMetric(PM_DefaultFrameWidth, option,
                                     widget);
        int buttonWidth = 16;

        switch (whichSubControl) {
        case SC_SpinBoxFrame:
            return option->rect;
        case SC_SpinBoxEditField:
            return option->rect.adjusted(+buttonWidth, +frameWidth,
                                         -buttonWidth, -frameWidth);
        //返回矩形区域
        case SC_SpinBoxDown:
            return visualRect(option->direction, option->rect,
                              QRect(option->rect.x(), option->rect.y(),
                                    buttonWidth,
                                    option->rect.height()));
        case SC_SpinBoxUp:
            return visualRect(option->direction, option->rect,
                              QRect(option->rect.right() - buttonWidth,
                                    option->rect.y(),
                                    buttonWidth,
                                    option->rect.height()));
        default:
            return QRect();
        }
    } else {
        return QCommonStyle::subControlRect(whichControl, option,
                                             whichSubControl, widget);
    }
}

//调用standardIconImplementation()槽获取用在用户界面上的标准图标.
QIcon BronzeStyle::standardIconImplementation(StandardPixmap which,
        const QStyleOption *option, const QWidget *widget) const
{
    //调用基类的standardPixmap()获取图标,并绘制浅蓝色
    QImage image = QCommonStyle::standardPixmap(which, option, widget)
                   .toImage();
    if (image.isNull())
        return QIcon();

    QPalette palette;
    if (option) {
        palette = option->palette;
    } else if (widget) {
        palette = widget->palette();
    }

    QPainter painter(&image);
    //着色可以通过在图标上绘制25%不透明的蓝色实现
    painter.setOpacity(0.25);
    //确保原来透明的部分依然透明
    painter.setCompositionMode(QPainter::CompositionMode_SourceAtop);
    painter.fillRect(image.rect(), palette.highlight());
    painter.end();

    return QIcon(QPixmap::fromImage(image));
}

//会被drawPrimitive调用,用来绘制一个PE_Frame私有元素
void BronzeStyle::drawBronzeFrame(const QStyleOption *option,
                                  QPainter *painter) const
{
    //为了保证QPainter保存原来的状态
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(QPen(option->palette.foreground(), 1.0));
    painter->drawRect(option->rect.adjusted(+1, +1, -1, -1));
    //最后恢复
    painter->restore();
}

//用来绘制QPushButton背景
void BronzeStyle::drawBronzeBevel(const QStyleOption *option,
                                  QPainter *painter) const
{
    QColor buttonColor = option->palette.button().color();
    //coeff使按钮有弹起效果
    int coeff = (option->state & State_MouseOver) ? 115 : 105;

    //上方是亮色,下方是暗色,其间是渐变的棕色
    QLinearGradient gradient(0, 0, 0, option->rect.height());
    gradient.setColorAt(0.0, option->palette.light().color());
    gradient.setColorAt(0.2, buttonColor.lighter(coeff));
    gradient.setColorAt(0.8, buttonColor.darker(coeff));
    gradient.setColorAt(1.0, option->palette.dark().color());

    //Bronze样式默认按钮使用2像素宽的边框,否则使用1像素宽的边框
    double penWidth = 1.0;
    //把option强转为const   QStyleOptionButton*类型,检测其features成员变量
    if (const QStyleOptionButton *buttonOpt =
            qstyleoption_cast<const QStyleOptionButton *>(option)) {
        if (buttonOpt->features & QStyleOptionButton::DefaultButton)
            penWidth = 2.0;
    }


    QRect roundRect = option->rect.adjusted(+1, +1, -1, -1);
    if (!roundRect.isValid())
        return;

    int diameter = 12;
    //指定按钮的圆角程度,根据diameter计算
    int cx = 100 * diameter / roundRect.width();
    int cy = 100 * diameter / roundRect.height();

    //执行绘图
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(gradient);
    painter->drawRoundRect(roundRect, cx, cy);

    if (option->state & (State_On | State_Sunken)) {
        QColor slightlyOpaqueBlack(0, 0, 0, 63);
        painter->setBrush(slightlyOpaqueBlack);
        painter->drawRoundRect(roundRect, cx, cy);
    }

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(QPen(option->palette.foreground(), penWidth));
    painter->setBrush(Qt::NoBrush);
    painter->drawRoundRect(roundRect, cx, cy);
    painter->restore();
}

//绘制复选框
void BronzeStyle::drawBronzeCheckBoxIndicator(
        const QStyleOption *option, QPainter *painter) const
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);

    if (option->state & State_MouseOver) {
        painter->setBrush(option->palette.alternateBase());
    } else {
        painter->setBrush(option->palette.base());
    }
    painter->drawRoundRect(option->rect.adjusted(+1, +1, -1, -1));

    if (option->state & (State_On | State_NoChange)) {
        QPixmap pixmap;
        if (!(option->state & State_Enabled)) {
            pixmap.load(":/images/checkmark-disabled.png");
        } else if (option->state & State_NoChange) {
            pixmap.load(":/images/checkmark-partial.png");
        } else {
            pixmap.load(":/images/checkmark.png");
        }

        QRect pixmapRect = pixmap.rect()
                                 .translated(option->rect.topLeft())
                                 .translated(+2, -6);
        QRect painterRect = visualRect(option->direction, option->rect,
                                       pixmapRect);
        if (option->direction == Qt::RightToLeft) {
            painter->scale(-1.0, +1.0);
            painterRect.moveLeft(-painterRect.right() - 1);
        }
        painter->drawPixmap(painterRect, pixmap);
    }
    painter->restore();
}

//绘制微调框向上向下按钮
void BronzeStyle::drawBronzeSpinBoxButton(SubControl which,
        const QStyleOptionComplex *option, QPainter *painter) const
{
    PrimitiveElement arrow = PE_IndicatorArrowLeft;
    QRect buttonRect = option->rect;
    if ((which == SC_SpinBoxUp)
            != (option->direction == Qt::RightToLeft)) {
        arrow = PE_IndicatorArrowRight;
        buttonRect.translate(buttonRect.width() / 2, 0);
    }
    buttonRect.setWidth((buttonRect.width() + 1) / 2);

    QStyleOption buttonOpt(*option);

    painter->save();
    painter->setClipRect(buttonRect, Qt::IntersectClip);
    if (!(option->activeSubControls & which))
        buttonOpt.state &= ~(State_MouseOver | State_On | State_Sunken);
    drawBronzeBevel(&buttonOpt, painter);

    QStyleOption arrowOpt(buttonOpt);
    arrowOpt.rect = subControlRect(CC_SpinBox, option, which)
                    .adjusted(+3, +3, -3, -3);
    if (arrowOpt.rect.isValid())
        drawPrimitive(arrow, &arrowOpt, painter);
    painter->restore();
}
