#include "LColorStyle.h"

CLColorStyle::CLColorStyle(QStyle *style)
    : QProxyStyle(style)
{

}

void CLColorStyle::polish(QPalette &palette)
{

}

void CLColorStyle::polish(QWidget *widget)
{

}

void CLColorStyle::unpolish(QWidget *widget)
{

}

int CLColorStyle::styleHint(QStyle::StyleHint which, const QStyleOption *option, const QWidget *widget
                            , QStyleHintReturn *returnData) const
{

}

int CLColorStyle::pixelMetric(QStyle::PixelMetric which, const QStyleOption *option, const QWidget *widget) const
{

}

void CLColorStyle::drawPrimitive(QStyle::PrimitiveElement which, const QStyleOption *option
                                 , QPainter *painter, const QWidget *widget) const
{

}

///
/// \brief CLColorStyle::drawControl// 画控件(窗口部件),用于绘制 QPushButiön 和其他的一些简单的 窗口部件
/// \param element
/// \param option
/// \param painter
/// \param widget
///
void CLColorStyle::drawControl(QStyle::ControlElement element, const QStyleOption *option
                               , QPainter *painter, const QWidget *widget) const
{

}

void CLColorStyle::drawComplexControl(QStyle::ComplexControl which, const QStyleOptionComplex *option
                                      , QPainter *painter, const QWidget *widget) const
{

}

QRect CLColorStyle::subControlRect(QStyle::ComplexControl whichControl, const QStyleOptionComplex *option
                                   , QStyle::SubControl whichSubControl, const QWidget *widget) const
{

}
