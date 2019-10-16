#pragma once
#include <QObject>
#include <QProxyStyle>
#include <QStyleOption>

// 参考Qt源码, qfunsionstyle

/**@brief 定制菜单style
	@author  lwh 
*/
class CCustomStyle : public QProxyStyle
{
	Q_OBJECT

public:
	CCustomStyle(QStyle *style = 0); 

	void drawControl(ControlElement control, const QStyleOption *option,
		QPainter *painter, const QWidget *widget) const;

	void drawPrimitive(PrimitiveElement element, const QStyleOption *option,
		QPainter *painter, const QWidget *widget) const; 

	int pixelMetric ( PixelMetric pm, const QStyleOption * opt, const QWidget * widget) const; 

private:
	void _DrawMenuItem(const QStyleOption *option,
		QPainter *painter, const QWidget *widget) const; 
	QPixmap 	_pixShadow	 ; //阴影图片	
};