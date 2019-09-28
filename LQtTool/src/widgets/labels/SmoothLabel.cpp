#include "SmoothLabel.h"

CSmoothLabel::CSmoothLabel(QWidget *parent) :
    QLabel(parent)
{
}

void CSmoothLabel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform|QPainter::Antialiasing);
    QLabel::paintEvent(event);
}
