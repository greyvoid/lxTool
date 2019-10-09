#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <vector>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //lstd::saveFileData("hello.txt", "1234443");

    ///
    ///
    /************
     *
     * 需要验证的功能
     *
     */
    //  加密功能
    // NoTitleMenuMainWidget优化
    // MessageBox 遮罩
    // mysliderbutton优化
    // Tomast控件


}

MainWindow::~MainWindow()
{
    delete ui;
}
