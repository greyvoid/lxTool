#include <QSettings>
#include <QDateTime>
#include <QTextBrowser>
//#include <QThread>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "network/LTcpThread.h"
#include "network/LTcpServer.h"
#include <QDir>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << QString("%1->%2,thread id:%3").arg(__FILE__).arg(__FUNCTION__).arg((int)QThread::currentThreadId());

    m_pLTcpServer = new LTcpServer();
    m_pLTcpServer->moveToThread(&m_thread);

    //QT 信号与槽不在同一个线程 connect
    //connect用于连接qt的信号和槽，在qt编程过程中不可或缺。它其实有第五个参数，只是一般使用默认值，在满足某些特殊需求的时候可能需要
    //        手动设置。
    // Qt::AutoConnection： 默认值，使用这个值则连接类型会在信号发送时决定。如果接收者和发送者在同一个线程，
    //则自动使用Qt::DirectConnection类型。如果接收者和发送者不在一个线程，则自动使用Qt::QueuedConnection类型。

    //Qt::DirectConnection：槽函数会在信号发送的时候直接被调用，槽函数运行于信号发送者所在线程。
    //效果看上去就像是直接在信号发送位置调用了槽函数。这个在多线程环境下比较危险，可能会造成奔溃。

    //Qt::QueuedConnection：槽函数在控制回到接收者所在线程的事件循环时被调用，槽函数运行于信号接收者所在线程。
    //发送信号之后，槽函数不会立刻被调用，等到接收者的当前函数执行完，进入事件循环之后，槽函数才会被调用。多线程环境下一般用这个。

    //Qt::BlockingQueuedConnection：槽函数的调用时机与Qt::QueuedConnection一致，不过发送完信号后发送者所在线程会阻塞，
    //直到槽函数运行完。接收者和发送者绝对不能在一个线程，否则程序会死锁。在多线程间需要同步的场合可能需要这个。

   // Qt::UniqueConnection：这个flag可以通过按位或（|）与以上四个结合在一起使用。当这个flag设置时，当某个信号和槽已经连接时，
    //再进行重复的连接就会失败。也就是避免了重复连接。

    qRegisterMetaType<qintptr>("qintptr");
    // ctpServer未继承至QThread，ctpServer与m_pBlessService处于同一线程，所以第五个参数默认为Qt::DirectConnection
    connect(m_pLTcpServer, SIGNAL(clientConnected(qintptr,QString,quint16,int)),
            this, SLOT(clientConnected(qintptr,QString,quint16,int)), Qt::QueuedConnection);
    connect(m_pLTcpServer, SIGNAL(clientDisconnected(qintptr)),
            this, SLOT(clientDisconnected(qintptr)), Qt::QueuedConnection);
    connect(m_pLTcpServer, SIGNAL(recv(qintptr,uint,const char*)),
            this, SLOT(onRecv(qintptr,uint,const char*)), Qt::QueuedConnection);
    connect(m_pLTcpServer, SIGNAL(recvFile(qintptr,uint,QString,QByteArray)),
            this, SLOT(onRecvFile(qintptr,uint,QString,QByteArray)), Qt::QueuedConnection);
    connect(this, SIGNAL(sendData(uint,char*,uint)),
            m_pLTcpServer, SLOT(sendData(uint,char*,uint)), Qt::QueuedConnection);
    connect(this, SIGNAL(sendData(qintptr,uint,char*,uint)),
            m_pLTcpServer, SLOT(sendData(qintptr,uint,char*,uint)), Qt::QueuedConnection);
    connect(this, SIGNAL(doDisConnectClient(qintptr)),
            m_pLTcpServer, SLOT(doDisConnectClient(qintptr)), Qt::QueuedConnection);

    m_thread.start();

}

MainWindow::~MainWindow()
{
    delete ui;
    //m_pBackgroundThread->deleteLater();
    m_thread.quit();
    m_thread.wait();//调用wait()来等待QThread子线程的结束,此时才可以delete

}

void MainWindow::saveFile(QString strFileName, QByteArray bytesFile)
{
    QString filePath = QDir::currentPath() + "/" + strFileName;
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug() << tr("open file %1 fail.").arg(filePath);
        return ;
    }
    // 写
    file.write(bytesFile);
    file.close();
}

void MainWindow::clientConnected(qintptr handle, QString ip, quint16 port, int connectNum)
{

}

void MainWindow::clientDisconnected(qintptr handle)
{

}

void MainWindow::onRecv(qintptr socket, unsigned int unCmd, const char *data)
{

}

void MainWindow::onRecvFile(qintptr socket, uint unCmd, QString strFileName, QByteArray bytesFile)
{
    qDebug() << "recv file" << strFileName;
    saveFile(strFileName, bytesFile);
}

