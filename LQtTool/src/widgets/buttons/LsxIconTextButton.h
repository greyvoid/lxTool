#ifndef CLSXICONTEXTBUTTON_H
#define CLSXICONTEXTBUTTON_H

#include "LsxButton.h"
#include <QIcon>
/*****************************************************************
 * 控件使用率： 80%
 *
 *
 */

///
/// \brief The CLIconTextButton class 自定义图片文本按钮，由于QPushButton的图片位置很固定，很难用
/// 所以自定义，其效果为：
/// 1、禁用状态，按钮的图片和文本都为灰色（可配置），不可点击
/// 2、非禁用状态，鼠标移上去为蓝色（可配置），离开为正常黑色（可配置）
///
class CLsxIconTextButton : public CLsxButton
{
    Q_OBJECT
    Q_PROPERTY(QColor colorDisabled READ setColorDisabled WRITE getColorDisabled)
    Q_PROPERTY(QColor colorNormal READ setColorNormal WRITE getColorNormal)
    Q_PROPERTY(QColor colorHover READ setColorHover WRITE getColorHover)
    Q_PROPERTY(QIcon iconNormal READ getIconNormal WRITE setIconNormal)
    Q_PROPERTY(QIcon iconHover READ getIconHover WRITE setIconHover)
public:
    explicit CLsxIconTextButton(QWidget *parent = 0);

    enum E_IconOrientation
    {
        EI_Left,
        EI_Right,
        EI_Top,
        EI_Bottom
    };





signals:

public slots:
    void setEnabled(bool bEnabled);

protected:
    virtual void paintEvent(QPaintEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

private:
    void init();

private:
    //bool m_bEnabled;
    QColor m_colorDisabled;
    QColor m_colorNormal;
    QColor m_colorHover;
    QIcon m_iconNormal;
    QIcon m_iconHover;
};

#endif // CLSXICONTEXTBUTTON_H
