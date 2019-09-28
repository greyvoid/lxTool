#ifndef CMYMENU_H
#define CMYMENU_H

#include <QWidget>
#include <QHBoxLayout>
#include <QMenu>
#include <QCommonStyle>

#include "buttons/LsxRadioButton.h"

class CustomIconStyle : public QCommonStyle
{
    Q_OBJECT

public:
    CustomIconStyle();
    ~CustomIconStyle();

    void SetCustomSize(int);

    //protected:
    virtual int pixelMetric(PixelMetric metric, const QStyleOption * option, const QWidget * widget) const;

private:
    int mSize;
};


class CLsxTabMenu: public QWidget
{
    Q_OBJECT
public:
    CLsxTabMenu(QWidget *parent = 0);
    CLsxTabMenu(CLsxRadioButton *btn, ...);
    CLsxTabMenu(const char *pText, ...);
    ~CLsxTabMenu();

signals:
    void itemClick(int nIndex);
    void itemClick(QString text);

private slots:
    void btnClick(CLsxRadioButton* lsxRadioButton);

private:
    void init();

private:
    QHBoxLayout* m_hLay;
    QVector<CLsxRadioButton*> m_vecBtn;
    int m_nLastSelectedIndex; //last select
    int m_nIndex; //current select
};


///
/// \brief The Menu class
///





#endif // CMYMENU_H
