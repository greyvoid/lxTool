#include "LLoopLoading.h"
#include <QPainter>
#include <QTimer>
//WaitingSpinnerWidget::WaitingSpinnerWidget(QWidget* parent,
//        bool centerOnParent,
//        bool disableParentWhenSpinning)
//    : QWidget(parent),
//      _centerOnParent(centerOnParent),
//      _disableParentWhenSpinning(disableParentWhenSpinning)
//{
//    initialize();
//}

//WaitingSpinnerWidget::WaitingSpinnerWidget(Qt::WindowModality modality,
//        QWidget* parent,
//        bool centerOnParent,
//        bool disableParentWhenSpinning)
//    : QWidget(parent, Qt::Dialog | Qt::FramelessWindowHint),
//      _centerOnParent(centerOnParent),
//      _disableParentWhenSpinning(disableParentWhenSpinning)
//{
//    initialize();

//    // We need to set the window modality AFTER we've hidden the
//    // widget for the first time since changing this property while
//    // the widget is visible has no effect.
//    setWindowModality(modality);
//    setAttribute(Qt::WA_TranslucentBackground);
//}
CLLoopLoading::CLLoopLoading(QWidget* parent)
    : QWidget(parent)
    , m_unAngle(0)
{
    setFixedSize(120, 120);
    if(!parentWidget())
    {
        setWindowFlags(Qt::FramelessWindowHint
                       | Qt::WindowSystemMenuHint
                       | Qt::WindowMinMaxButtonsHint);
        setAttribute(Qt::WA_TranslucentBackground, true);
    }
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(rotate()));
    m_timer->setInterval(30);

    // 设置 模态
    //setWindowModality(modality);
}

void CLLoopLoading::start(const QString & strTip)
{
    m_strTip = strTip;
    if (parentWidget())
    {
        move(parentWidget()->width() / 2 - width() / 2,
             parentWidget()->height() / 2 - height() / 2);
    }
    show();
    m_timer->start();

}

void CLLoopLoading::stop()
{
    hide();
    m_timer->stop();
}

void CLLoopLoading::rotate()
{
    m_unAngle += 18;
    if (m_unAngle >= 360)
    {
        m_unAngle = 0;
    }
    update();
}

void CLLoopLoading::paintEvent(QPaintEvent* paintEvent)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 与qml一致
    QFont font("Microsoft YaHei");
    font.setPixelSize(18);
    painter.setFont(font);
    int nFontWidth = painter.fontMetrics().width(m_strTip);
    int nFontHeight = painter.fontMetrics().height();
    int nSpace = 30;
    if (nFontWidth > width())
    {
        resize(nFontWidth, height());
    }

    int side = width() < height() ? width() : height();
    int nDiameters = side -  nFontHeight - nSpace;
    int radius = nDiameters / 2;
    painter.save();
    painter.translate(side / 2, side / 2);
    --radius;

    /** 此方法最里面的区域无法透明
    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);
    painter.drawEllipse(QPoint(0, 0), radius, radius);

    --radius;
    painter.setPen(QColor(217, 221, 224));
    painter.setBrush(QColor(217, 221, 224));
    painter.drawEllipse(QPoint(0, 0), radius, radius);

    painter.setPen(QColor(55, 144, 206));
    painter.setBrush(QColor(55, 144, 206));
    int startAngle = m_unAngle * 16;
    int spanAngle = (m_unAngle + 45) * 16;
    painter.drawPie(-radius, -radius, radius * 2, radius * 2, startAngle, spanAngle);

    radius -= 5;
    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);
    painter.drawEllipse(QPoint(0, 0), radius, radius);

    --radius;
    //    painter.save();
    //    painter.setCompositionMode( QPainter::CompositionMode_Clear );
    //    painter.drawEllipse(QPoint(0, 0), radius, radius);
    //QRegion::Ellipse

    QPainterPath painterPath;
    painterPath.addEllipse(QPoint(0, 0), radius, radius);
    //    painter.fillPath(painterPath, Qt::transparent);
    painter.fillPath(painterPath, QColor(0, 0, 0, 100));
    //    painter.restore();
    */

    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);
    QRegion r1(-radius, -radius, radius * 2, radius * 2, QRegion::Ellipse);
    --radius;
    QRegion r2(-radius, -radius, radius * 2, radius * 2, QRegion::Ellipse);
    QRegion r = r1 - r2;
    painter.setClipRegion(r);
    painter.fillRect(r.boundingRect(), Qt::white);

    int radiusColor = radius - 5;
    painter.setPen(QColor(217, 221, 224));
    painter.setBrush(QColor(217, 221, 224));
    QRegion r3(-radiusColor, -radiusColor, radiusColor * 2, radiusColor * 2, QRegion::Ellipse);
    QRegion rr = r2 - r3;
    painter.setClipRegion(rr);
    painter.fillRect(rr.boundingRect(), QColor(217, 221, 224));

    painter.setPen(QColor(55, 144, 206));
    painter.setBrush(QColor(55, 144, 206));
    QPainterPath path;
    //path.arcMoveTo(-radius, -radius, radius * 2,radius * 2, m_unAngle);
    path.moveTo(0, 0);
    path.arcTo(-radius, -radius, radius * 2, radius * 2, 0, 45);

//     path.arcMoveTo(-radiusColor, -radiusColor, radiusColor * 2,radiusColor * 2, m_unAngle + 45);
//     path.arcTo(-radiusColor, -radiusColor, radiusColor * 2,radiusColor * 2, m_unAngle + 45, m_unAngle);
    painter.rotate(m_unAngle);    // 逆时针旋转 30 度
    painter.drawPath(path);

    radius = radiusColor - 1;
    QRegion r4(-radius, -radius, radius * 2, radius * 2, QRegion::Ellipse);
    QRegion rrr = r3 - r4;
    painter.setClipRegion(rrr);
    painter.fillRect(r.boundingRect(), Qt::white);

    painter.resetTransform();
    painter.restore();

    QTextOption option(Qt::AlignCenter);
    painter.drawText(QRect(0, height() - nFontHeight, width(), nFontHeight), m_strTip, option);

}
