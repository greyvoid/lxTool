#ifndef SEARCH_EDIT_H
#define SEARCH_EDIT_H

#include <QWidget>
#include <QStyleOptionFrame>
#include <QPushButton>
#include <QLineEdit>
#include <QLinearGradient>

QT_BEGIN_NAMESPACE
class QLineEdit;
QT_END_NAMESPACE


class CLSearchEditBase : public QWidget
{
    Q_OBJECT

public:
    CLSearchEditBase(QWidget *parent = 0);

    inline QLineEdit *lineEdit() const { return m_lineEdit; }

    void setClearWidget(QWidget *widget);
    QWidget *clearWidget() const;

    void setShearchWidget(QWidget *widget);
    QWidget *shearchWidget() const;

    QSize sizeHint() const;

    QVariant inputMethodQuery(Qt::InputMethodQuery property) const;
protected:
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void inputMethodEvent(QInputMethodEvent *e);
    bool event(QEvent *event);

protected:
    void updateGeometries();
    void initStyleOption(QStyleOptionFrameV2 *option) const;

    QWidget *m_wgtClear;
    QWidget *m_wgtShearch;
    QLineEdit *m_lineEdit;
};

class CLSearchEdit : public CLSearchEditBase
{
    Q_OBJECT

signals:
    void search(const QString text);

public:
    CLSearchEdit(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void textChanged();

private:
    QLinearGradient generateGradient(const QColor &color) const;
    QPushButton *m_btnClear;
    QPushButton *m_btnSearch;
    QColor m_defaultBaseColor;
};

#endif // SEARCH_EDIT_H
