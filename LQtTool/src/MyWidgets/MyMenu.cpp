#include "MyMenu.h"
#include <QtDebug>
///
/// \brief CustomIconStyle::CustomIconStyle
///
///

CustomIconStyle::CustomIconStyle()
{
    mSize = 20;
}

CustomIconStyle::~CustomIconStyle()
{

}


void CustomIconStyle::SetCustomSize( int nSize )
{
    mSize = nSize;
}

int CustomIconStyle::pixelMetric( PixelMetric metric, const QStyleOption * option, const QWidget * widget ) const
{
    int s = QCommonStyle::pixelMetric(metric, option, widget);
    if (metric == QStyle::PM_SmallIconSize) {
        s = mSize;
    }

    return s;
}



///
/// \brief CTabMenu::CTabMenu
/// \param parent
///
///
CTabMenu::CTabMenu(QWidget *parent)
{
    init();
}

CTabMenu::CTabMenu(CLsxRadioButton *btn, ...)
{
    va_list args;
    va_start(args, btn);
        while (btn)
        {
            qDebug() << "..........................";
            connect(btn, SIGNAL(clicked(CLsxRadioButton*)), this, SLOT(btnClick(CLsxRadioButton*)));
            m_vecBtn.push_back(btn);
            btn = va_arg(args, CLsxRadioButton *);
        }

    va_end(args);
    init();

}

CTabMenu::CTabMenu(const char *pText, ...)
{
    va_list args;
    va_start(args, pText);
        while (pText)
        {
            CLsxRadioButton* btn = new CLsxRadioButton(pText);
            connect(btn, SIGNAL(clicked(CLsxRadioButton*)), this, SLOT(btnClick(CLsxRadioButton*)));
            m_vecBtn.push_back(btn);
            pText = va_arg(args, const char *);
        }

    va_end(args);
    init();
}

CTabMenu::~CTabMenu()
{

}

void CTabMenu::btnClick(CLsxRadioButton *lsxRadioButton)
{
//    QVector<CLsxRadioButton*>::iterator iter;
//    for (iter = m_vecBtn.begin(); iter != m_vecBtn.end(); ++iter)
//    {
//        if((*iter) != lsxRadioButton)
//        {
//            (*iter)->setPress(false);
//        }
//    }
    for (int i = 0; i < m_vecBtn.size(); ++i)
    {
        if(m_vecBtn[i] != lsxRadioButton)
        {
            m_vecBtn[i]->setPress(false);
        }
        else
        {
            emit itemClick(i);
            emit itemClick(m_vecBtn[i]->text());
        }
    }
}

void CTabMenu::init()
{
    m_nIndex = -1;
    m_nLastSelectedIndex = 0;
    m_hLay = new QHBoxLayout;
    if(m_vecBtn.isEmpty())
    {
     return;
    }
    setBaseSize(m_vecBtn[0]->size().width() * m_vecBtn.size(), m_vecBtn[0]->size().height());
       for (int j=0; j<0; ++j)
       {
           qDebug()<< "jjjjjjjjjjjjjjj";
       }
    for (int i = 0; i < m_vecBtn.size(); ++i)
    {
        qDebug() << ".........................." << m_vecBtn[0]->size().width();
        m_hLay->addWidget(m_vecBtn[i]);
    }
    setLayout(m_hLay);
    m_vecBtn[0]->setPress(true);
    qDebug() << size().width() << size().height();
}



