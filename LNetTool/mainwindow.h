#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

class LTcpServer;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void saveFile(QString strFileName, QByteArray bytesFile);
    void clientConnected(qintptr handle, QString ip, quint16 port, int connectNum);
    void clientDisconnected(qintptr handle);
    void onRecv(qintptr socket, unsigned int unCmd, const char* data);
    void onRecvFile(qintptr socket,uint unCmd, QString strFileName, QByteArray bytesFile);

signals:
    void doDisConnectClient(qintptr handle); //主动断开连接信号
    void sendData(unsigned int cmd, char* data, unsigned int unSize);
    void sendData(qintptr handle, unsigned int cmd, char* data, unsigned int unSize);

private slots:


private:


private:
    Ui::MainWindow *ui;
    LTcpServer* m_pLTcpServer;
    QThread m_thread;
};

#endif // MAINWINDOW_H
