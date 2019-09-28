#include "NoTitleMenuMainWidget.h"
#include<QMouseEvent>
#include <QToolButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStyle>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QLabel>
#include <QToolBar>
#include "widgets.h"
#define TITLE_ICON_HEIGHT 40
#define TITLE_BAR_HEIGHT 50
#define DEFULT_WINDWO_WIDTH 1300

using namespace std;

//标题栏的长度
const static int pos_min_x = 0;
const static int pos_max_x = DEFULT_WINDWO_WIDTH - 120;  //为最小化和关闭按钮留空间
const static int pos_min_y = 0;
const static int pos_max_y = TITLE_BAR_HEIGHT;

CNoTitleMenuMainWidget::CNoTitleMenuMainWidget(QWidget *parent)
    : QWidget(parent)
    , m_vLayMain( new QVBoxLayout())
    , m_menuBar(new QMenuBar)
    , m_toolBar(new QToolBar)
    , m_centralWidget(new QWidget)
{

    setWindowFlags(Qt::FramelessWindowHint);//去掉窗口标题栏

    resize(1300,739);
    initTitleBar();
    initMenuBar();
    //initToolBar();
    initCentralWidget();

    m_vLayMain->addStretch();
    m_vLayMain->setMargin(0);
    m_vLayMain->setContentsMargins(QMargins(0,0,0,0));
    setLayout(m_vLayMain);
}

CNoTitleMenuMainWidget::~CNoTitleMenuMainWidget()
{

}

void CNoTitleMenuMainWidget::setTitleOperateIcon(QString strImgClose, QString strImgNormal, QString strImgMin)
{
    //    m_strImgClose = strImgClose;
    //    m_strImgNormal = strImgNormal;
    //    m_strImgMin = strImgMin;
    //    m_tBtnMin->setIcon(QPixmap(m_strImgMin));
    //    m_tBtnClose->setIcon(QPixmap(m_strImgClose));
    //    m_tBtnNormal->setIcon(QPixmap(m_strImgMin));
}

void CNoTitleMenuMainWidget::setTitleIcon(QString strIcon)
{
    m_labelTitleIcon->setPixmap(QPixmap(strIcon).scaled(m_labelTitleIcon->size()));
}

void CNoTitleMenuMainWidget::setTitle(QString strTitle)
{
    labelTitleText->setText(strTitle);
}


//自己实现的窗口拖动操作
void CNoTitleMenuMainWidget::mousePressEvent(QMouseEvent *event)
{
    //当鼠标单击窗体准备拖动时，初始化鼠标在窗体中的相对位置
    mousePosition = event->pos();
    //只对标题栏范围内的鼠标事件进行处理
    if (mousePosition.x()<=pos_min_x)
        return;
    if ( mousePosition.x()>=pos_max_x)
        return;
    if (mousePosition.y()<=pos_min_y )
        return;
    if (mousePosition.y()>=pos_max_y)
        return;
    isMousePressed = true;
}

void CNoTitleMenuMainWidget::mouseMoveEvent(QMouseEvent *event)
{
    if ( isMousePressed==true )
    {
        QPoint movePot = event->globalPos() - mousePosition;
        //move是移动的位置是相对于全局而言(即屏幕)
        move(movePot);
    }
}
void CNoTitleMenuMainWidget::mouseReleaseEvent(QMouseEvent *event)
{
    isMousePressed=false;
}

void CNoTitleMenuMainWidget::initTitleBar()
{
    QHBoxLayout *hLay = new QHBoxLayout;
    m_labelTitleIcon = new QLabel;
    m_labelTitleIcon->resize(TITLE_ICON_HEIGHT,TITLE_ICON_HEIGHT);
    labelTitleText = new QWhiteTextLabel();
    QFont font("Helvetica [Cronyx]", 20);
    labelTitleText->setFont(font);
    CMediaPushButton *smallBtn=new CMediaPushButton(tr("_"));
    CMediaPushButton *closeBtn=new CMediaPushButton(tr("X"));
    connect(smallBtn,SIGNAL(clicked()),this,SLOT(showMinimized()));
    connect(closeBtn,SIGNAL(clicked()),this,SLOT(close()));

    smallBtn->setFixedSize(30,30);
    closeBtn->setFixedSize(30,30);

    hLay->addWidget(m_labelTitleIcon);
    hLay->addWidget(labelTitleText);
    hLay->addStretch();
    hLay->addWidget(smallBtn);
    hLay->addWidget(closeBtn);

    QWidget *widget = new QWidget;
    widget->setFixedHeight(TITLE_BAR_HEIGHT);
    widget->setStyleSheet("background-color:rgb(40,40,40);");
    widget->setLayout(hLay);

    //m_vLayMain->addLayout(hLay);
    m_vLayMain->addWidget(widget);

    //    //int width = this->width();//获取界面的宽度
    //    m_tBtnMin = new QToolButton(this);   //最小按钮
    //    m_tBtnClose= new QToolButton(this);  //关闭按钮
    //    m_tBtnNormal = new QToolButton(this);


    //    connect(m_tBtnMin, SIGNAL(clicked()), this, SLOT(showMinimized()));
    //    connect(m_tBtnClose, SIGNAL(clicked()), this, SLOT(close()));
    //    connect(m_tBtnNormal, SIGNAL(clicked()), this, SLOT(showNormal()));

    //    //获取最小化、关闭按钮图标
    //    QPixmap minPix = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
    //    QPixmap closePix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    //    QPixmap normalPix = style()->standardPixmap(QStyle::SP_TitleBarNormalButton);

    //    //设置最小化、关闭按钮图标
    //    m_tBtnMin->setIcon(minPix);
    //    m_tBtnClose->setIcon(closePix);
    //    m_tBtnNormal->setIcon(normalPix);

    //    //设置最小化、关闭按钮在界面的位置
    ////    m_tBtnNormal->setGeometry(width-160, 0, 20, 20);
    ////    m_tBtnMin->setGeometry(width-120,0,20,20);
    ////    m_tBtnClose->setGeometry(width-100,0,20,20);


    //    //设置鼠标移至按钮上的提示信息
    //    m_tBtnMin->setToolTip("最小化");
    //    m_tBtnClose->setToolTip("关闭");
    //    m_tBtnNormal->setToolTip("还原");

    //    //设置最小化、关闭等按钮的样式
    //    m_tBtnMin->setStyleSheet("background-color:transparent;");
    //    m_tBtnClose->setStyleSheet("background-color:transparent;");
    //    m_tBtnNormal->setStyleSheet("background-color:transparent;");
}

void CNoTitleMenuMainWidget::initMenuBar()
{
//    QMenu *menuFile = new QMenu("文件");
//    //menuFile->setStyleSheet("background-color:transparent;");
//    menuFile->setIcon(QPixmap(":/img/btn_style_normal.png").scaled(menuFile->size()));
//    QMenu *menuEdit = new QMenu("编辑");
//    QMenu *menuHelp = new QMenu("帮助");
//    //QAction *actFile = new QAction("文件");
//    //QAction *actEdit = new QAction("编辑");
//    // QAction *actHelp = new QAction("帮助");
//    m_menuBar->addMenu(menuFile);
//        //actInput->setIcon(QIcon(":/img/btn_style_normal.png"));
//    //m_menuBar->addSeparator();
//    m_menuBar->addMenu(menuEdit);
//    //m_menuBar->addSeparator();
//    m_menuBar->addMenu(menuHelp);
//    m_menuBar->setStyleSheet("background-color:rgb(40,40,40);");
//    m_vLayMain->addWidget(m_menuBar);
}



void CNoTitleMenuMainWidget::initToolBar()
{
    QAction *actInput = new QAction("司机实名制信息输入", m_toolBar);
    QAction *actSherch = new QAction("信息查询", m_toolBar);
    QAction *actSend = new QAction("数据推送", m_toolBar);
    QAction *actUrgencyEvent = new QAction("紧急事件", m_toolBar);

    m_toolBar->addAction(actInput);
    m_toolBar->addSeparator();
    m_toolBar->addAction(actSherch);
    m_toolBar->addSeparator();
    m_toolBar->addAction(actSend);
    m_toolBar->addSeparator();
    m_toolBar->addAction(actUrgencyEvent);
    m_vLayMain->addWidget(m_toolBar);
}

void CNoTitleMenuMainWidget::initCentralWidget()
{
    m_centralWidget->resize(width(), height() - 30 - m_menuBar->height() - m_toolBar->height());
    m_vLayMain->addWidget(m_centralWidget);
}


