#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class CHttpClient;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    void handleDownloadCompleted(bool bOk, CHttpClient* pHttpQuery);

    void handReadyRead(CHttpClient* pHttpQuery);

    //handleObjRoot(QJsonObject isonObj, ULONG tag);

private slots:
    void on_btnRequest_clicked();

    void on_btnLogin_clicked();

private:
    void autoLogin();

    void aTest();

private:
    Ui::MainWindow *ui;
    QString m_strName;
    QString m_strPasswd;

};

#endif // MAINWINDOW_H
