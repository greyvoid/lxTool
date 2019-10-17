#ifndef BRONZESTYLE_H
#define BRONZESTYLE_H

#include <QCommonStyle>
#include <QProxyStyle>

// 青铜样式 --棕色、亮棕色、暗棕色等
class BronzeStyle : public QProxyStyle
{
    Q_OBJECT

public:
    BronzeStyle() {}

    // 以下三个函数在装载Style和卸载Style时调用,它可以是适当修改窗口部件和调色板
    //抛光 --改变调色板为样式指定的颜色调色板
    void polish(QPalette &palette);
    void polish(QWidget *widget);//初始化给定窗口部件的外观,窗口部件每一次创建后首次显示之前调用
    void unpolish(QWidget *widget);//取消polish()的作用

    //返回一些关于样式外观的提示 --分别设置各种部件的布局，比如checkbox的text在左边或者在右边 --查询函数类
    int styleHint(StyleHint which, const QStyleOption *option,
                  const QWidget *widget = 0,
                  QStyleHintReturn *returnData = 0) const;

    //像素值,像素指示 --设置各部件的线宽，大小等 --查询函数类
    int pixelMetric(PixelMetric which, const QStyleOption *option,
                    const QWidget *widget = 0) const;

    //画原子元素 --这个则是最重要的，在这里面可以实现对不同部件的原始元素的绘制，当然你也可以调用默认的方法.element这个参数就是我们需要重绘的部件的原始元素
    void drawPrimitive(PrimitiveElement which,
                       const QStyleOption *option, QPainter *painter,
                       const QWidget *widget = 0) const;

    // 画控件(窗口部件)
    // drawControl()函数被各种 QStyle 的子类重新实现，用于绘制 QPushButiön 和其他的一些简单的 窗口部件
//    void drawControl(ControlElement element, // 要绘制的窗口部件的类型
//                     const QStyleOption *option,
//                     QPainter *painter,
//                     const QWidget *widget) const;

    // 画复合控件
    void drawComplexControl(ComplexControl which,
                            const QStyleOptionComplex *option,
                            QPainter *painter,
                            const QWidget *widget = 0) const;

    // --查询函数类
    QRect subControlRect(ComplexControl whichControl,
                         const QStyleOptionComplex *option,
                         SubControl whichSubControl,
                         const QWidget *widget = 0) const;

public slots:
    // 获取用在用户界面上的标准图标。
    QIcon standardIconImplementation(StandardPixmap which,
                                     const QStyleOption *option,
                                     const QWidget *widget = 0) const;

private:
    void drawBronzeFrame(const QStyleOption *option,
                         QPainter *painter) const;
    void drawBronzeBevel(const QStyleOption *option,
                         QPainter *painter) const;
    void drawBronzeCheckBoxIndicator(const QStyleOption *option,
                                     QPainter *painter) const;
    void drawBronzeSpinBoxButton(SubControl which,
                                 const QStyleOptionComplex *option,
                                 QPainter *painter) const;
};

#endif
