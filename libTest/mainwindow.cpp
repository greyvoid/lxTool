#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <vector>

#include "CustomMainWidget.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    /************
     *
     * 需要验证的控件
     *
     */

    // test CLSliderButton
    ui->sliderButton->addItem("123123");
    ui->sliderButton->addItem("text");
    ui->sliderButton->addItem("dfdff");

    // test NoTitleMenuMainWidget
    //m_pCustomMainWidget = new CCustomMainWidget;
    //CCustomMainWidget.show();

    // test CLShadeWidget 遮罩

    // test CLSliderButton

    // test CCompleteLineEdit
    ui->completeLineEdit->setListWords({"hello", "about", "you", "youuuuu"});

    //
    ui->progressIndicator->startAnimation();

    ui->loadingWidget->start();

    // Tomast控件

}

MainWindow::~MainWindow()
{
    delete ui;
    //m_pCustomMainWidget->deleteLater();
}
