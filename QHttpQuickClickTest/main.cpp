#include "mainwindow.h"
#include <QApplication>
#include <QNetworkProxy>

int main(int argc, char *argv[])
{
    QNetworkProxy xy;
    xy.setHostName("127.0.0.1");
    xy.setPort(8888);
    xy.setType(QNetworkProxy::HttpProxy);
    QNetworkProxy::setApplicationProxy(xy);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
