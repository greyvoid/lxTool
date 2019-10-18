#ifndef CLICONTEXTBUTTON_H
#define CLICONTEXTBUTTON_H

#include <QWidget>
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
class CLIconTextButton : public QWidget
{
    Q_OBJECT
public:
    explicit CLIconTextButton(QWidget *parent = 0);

    enum E_IconOrientation
    {
        EI_Left,
        EI_Right,
        EI_Top,
        EI_Bottom
    };

signals:

public slots:

private:
    bool m_bEnabled;
    QColor m_colorDisabled;
    QColor m_colorNormal;
    QColor m_colorHover;
    QIcon m_iconNormal;
    QIcon m_iconHover;
};

#endif // CLICONTEXTBUTTON_H
