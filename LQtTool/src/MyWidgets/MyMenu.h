#ifndef CMYMENU_H
#define CMYMENU_H

#include <QWidget>
#include <QHBoxLayout>
#include "MyButtons.h"
#include <QMenu>
#include <QCommonStyle>


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


class CTabMenu: public QWidget
{
    Q_OBJECT
public:
    CTabMenu(QWidget *parent = 0);
    CTabMenu(CLsxRadioButton *btn, ...);
    CTabMenu(const char *pText, ...);
    ~CTabMenu();

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
