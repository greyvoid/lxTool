#include "LSearchEdit.h"
#include <QEvent>
#include <QApplication>
#include <QCompleter>
#include <QFocusEvent>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPainter>
#include <QStyle>
#include <QStyleOptionFrameV2>
#include <QDebug>

#define SPACE_WIDGET        10

CLSearchEditBase::CLSearchEditBase(QWidget *parent)
    : QWidget(parent)
    , m_wgtClear(NULL)
    , m_wgtShearch(NULL)
    , m_lineEdit(new QLineEdit(this))
{
    setFocusPolicy(m_lineEdit->focusPolicy());
    setAttribute(Qt::WA_InputMethodEnabled);
    setSizePolicy(m_lineEdit->sizePolicy());
    setBackgroundRole(m_lineEdit->backgroundRole());
    setMouseTracking(true);
    setAcceptDrops(true);
    setAttribute(Qt::WA_MacShowFocusRect, true);
    QPalette p = m_lineEdit->palette();
    setPalette(p);

    // line edit
    m_lineEdit->setFrame(false);
    m_lineEdit->setFocusProxy(this);
    m_lineEdit->setAttribute(Qt::WA_MacShowFocusRect, false);
    QPalette clearPalette = m_lineEdit->palette();
    clearPalette.setBrush(QPalette::Base, QBrush(Qt::transparent));
    m_lineEdit->setPalette(clearPalette);
}

void CLSearchEditBase::setClearWidget(QWidget *widget)
{
    m_wgtClear = widget;
}

QWidget *CLSearchEditBase::clearWidget() const
{
    return m_wgtClear;
}

void CLSearchEditBase::setShearchWidget(QWidget *widget)
{
    m_wgtShearch = widget;
}

QWidget *CLSearchEditBase::shearchWidget() const
{
    return m_wgtShearch;
}

void CLSearchEditBase::resizeEvent(QResizeEvent *event)
{
    Q_ASSERT(m_wgtClear);
    updateGeometries();
    QWidget::resizeEvent(event);
}

void CLSearchEditBase::updateGeometries()
{
    QStyleOptionFrameV2 panel;
    initStyleOption(&panel);
    QRect rectSub = style()->subElementRect(QStyle::SE_LineEditContents, &panel, this);

    int nSubHeight = rectSub.height();
    int nSubWidth = rectSub.width();

    int nSubFixWidth = nSubWidth - m_wgtClear->width() - m_wgtShearch->width() - SPACE_WIDGET * 3;
    m_lineEdit->setGeometry(rectSub.x()
                            , 0
                            , nSubFixWidth
                            , nSubHeight);

    m_wgtClear->setGeometry(  m_lineEdit->rect().right() + SPACE_WIDGET
                            , rectSub.y() + (nSubHeight - m_wgtClear->height())/2
                            , m_wgtClear->width()
                            , m_wgtClear->height());

    m_wgtShearch->setGeometry(m_lineEdit->rect().right() + m_wgtClear->width() + SPACE_WIDGET * 2
                            , rectSub.y() + (nSubHeight - m_wgtShearch->height())/2
                            , m_wgtShearch->width()
                            , m_wgtShearch->height());

}

void CLSearchEditBase::initStyleOption(QStyleOptionFrameV2 *option) const
{
    option->initFrom(this);
    option->rect = contentsRect();
    option->lineWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth, option, this);
    option->midLineWidth = 0;
    option->state |= QStyle::State_Sunken;
    if (m_lineEdit->isReadOnly())
        option->state |= QStyle::State_ReadOnly;
#ifdef QT_KEYPAD_NAVIGATION
    if (hasEditFocus())
        option->state |= QStyle::State_HasEditFocus;
#endif
    option->features = QStyleOptionFrameV2::None;
}

QSize CLSearchEditBase::sizeHint() const
{
    m_lineEdit->setFrame(true);
    QSize size = m_lineEdit->sizeHint();
    m_lineEdit->setFrame(false);
    return size;
}

void CLSearchEditBase::focusInEvent(QFocusEvent *event)
{
    m_lineEdit->event(event);
    QWidget::focusInEvent(event);
}

void CLSearchEditBase::focusOutEvent(QFocusEvent *event)
{
    m_lineEdit->event(event);

    if (m_lineEdit->completer())
    {
        connect(m_lineEdit->completer(), SIGNAL(activated(QString)),
                         m_lineEdit, SLOT(setText(QString)));
        connect(m_lineEdit->completer(), SIGNAL(highlighted(QString)),
                         m_lineEdit, SLOT(_q_completionHighlighted(QString)));
    }
    QWidget::focusOutEvent(event);
}

void CLSearchEditBase::keyPressEvent(QKeyEvent *event)
{
    m_lineEdit->event(event);
}

bool CLSearchEditBase::event(QEvent *event)
{
    if (event->type() == QEvent::ShortcutOverride)
        return m_lineEdit->event(event);
    return QWidget::event(event);
}

void CLSearchEditBase::paintEvent(QPaintEvent *)
{
    //如果从QWidget子类化一个Widget，为了能够使用样式表则需要为自定义Widget提供paintEvent事件。
    QPainter p(this);
    QStyleOptionFrameV2 panel;
    initStyleOption(&panel);
    style()->drawPrimitive(QStyle::PE_PanelLineEdit, &panel, &p, this);
}

QVariant CLSearchEditBase::inputMethodQuery(Qt::InputMethodQuery property) const
{
    return m_lineEdit->inputMethodQuery(property);
}

void CLSearchEditBase::inputMethodEvent(QInputMethodEvent *e)
{
    m_lineEdit->event(e);
}



///
/// \brief CLSearchEdit::CLSearchEdit
/// \param parent
///
/// \class
///

#define ICON_CLEAR_PATH             ":/image/main/ico_close.png"
#define ICON_SEARCH_PATH            ":/image/main/ic-search.png"


CLSearchEdit::CLSearchEdit(QWidget *parent)
    : CLSearchEditBase(parent)
    , m_btnClear(new QPushButton(this))
    , m_btnSearch(new QPushButton(this))
{

    m_btnClear->resize(16, 16);
    m_btnClear->setIcon(QIcon(ICON_CLEAR_PATH));
    m_btnClear->setFlat(true);
    setClearWidget(m_btnClear);

    m_btnSearch->resize(16, 16);
    m_btnSearch->setIcon(QIcon(ICON_SEARCH_PATH));
    m_btnSearch->setFlat(true);
    setShearchWidget(m_btnSearch);

    m_defaultBaseColor = palette().color(QPalette::Base);

    connect(m_lineEdit, SIGNAL(textChanged(QString)), this, SLOT(textChanged()));
}

QLinearGradient CLSearchEdit::generateGradient(const QColor &color) const
{
    QLinearGradient gradient(0, 0, 0, height());
    gradient.setColorAt(0, m_defaultBaseColor);
    gradient.setColorAt(0.15, color.lighter(120));
    gradient.setColorAt(0.5, color);
    gradient.setColorAt(0.85, color.lighter(120));
    gradient.setColorAt(1, m_defaultBaseColor);
    return gradient;
}

void CLSearchEdit::paintEvent(QPaintEvent *event)
{
    QPalette p = palette();
    if (!m_lineEdit->text().isEmpty())
    {
        QColor lightYellow(248, 248, 210);
        p.setBrush(QPalette::Base, generateGradient(lightYellow));
    }
    else
    {
        p.setBrush(QPalette::Base, m_defaultBaseColor);
    }
    setPalette(p);
    CLSearchEditBase::paintEvent(event);
}

void CLSearchEdit::textChanged()
{
    QString text = m_lineEdit->text();
    emit search(text);
}
