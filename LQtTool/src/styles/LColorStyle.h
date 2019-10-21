#ifndef CLCOLORSTYLE_H
#define CLCOLORSTYLE_H

#include <QProxyStyle>

class CLColorStyle : public QProxyStyle
{
    Q_OBJECT
public:
    explicit CLColorStyle(QStyle *style = Q_NULLPTR);

    void polish(QPalette &palette);
    void polish(QWidget *widget);
    void unpolish(QWidget *widget);


    int styleHint(StyleHint which, const QStyleOption *option,
                  const QWidget *widget = 0,
                  QStyleHintReturn *returnData = 0) const;

    int pixelMetric(PixelMetric which, const QStyleOption *option,
                    const QWidget *widget = 0) const;


    void drawPrimitive(PrimitiveElement which,
                       const QStyleOption *option, QPainter *painter,
                       const QWidget *widget = 0) const;


    void drawControl(ControlElement element,
                     const QStyleOption *option,
                     QPainter *painter,
                     const QWidget *widget) const;


    void drawComplexControl(ComplexControl which,
                            const QStyleOptionComplex *option,
                            QPainter *painter,
                            const QWidget *widget = 0) const;

    QRect subControlRect(ComplexControl whichControl,
                         const QStyleOptionComplex *option,
                         SubControl whichSubControl,
                         const QWidget *widget = 0) const;

signals:

public slots:

};

#endif // CLCOLORSTYLE_H
