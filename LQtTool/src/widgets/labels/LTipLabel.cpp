#include "LTipLabel.h"

#include <QToolTip>
#include "LQtFunc.h"

CLTipLabel::CLTipLabel(QWidget *parent)
    :QLabel(parent)
{

}

CLTipLabel::CLTipLabel(const QString &text, QWidget *parent, Qt::WindowFlags f)
    :QLabel(text, parent, f)
{

}



void CLTipLabel::enterEvent(QEvent *event)
{
    QToolTip::showText(QCursor::pos(), Lqt::strRecombineLine(m_strReal, this));
}

void CLTipLabel::leaveEvent(QEvent *event)
{

}
