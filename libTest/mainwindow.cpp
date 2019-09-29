#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //lstd::saveFileData("hello.txt", "1234443");
}

MainWindow::~MainWindow()
{
    delete ui;
}
