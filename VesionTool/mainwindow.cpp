#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Windows.h>
#include <QtDebug>
#include <QApplication>
#include <QFileDialog>
//#include <QDomDocument>
#include "LVersionXmlTool.h"
#include "LFileOperateUtil.h"


//在安全DLL搜索模式开启的情况下，搜索顺序是：
//           1、应用程序EXE所在的路径。
//           2、系统目录。
//           3、16位系统目录
//           4、Windows目录
//           5、当前目录
//           6、PATH环境变量指定的目录

///
/// \brief getFileVertion
/// \param fullName 注意如果这里只输入名字，会按上面的规则搜索，被小编坑在这里了，获取的老是别的路径下的同名文件。改为全路径ok
/// \return
///
QString getFileVertion(QString fullName)
{
    QString result = "";
    char* pData = nullptr;
    do
    {
        DWORD dwLen = GetFileVersionInfoSize(fullName.toStdWString().c_str(), 0);
        if (0 == dwLen)
        {
            break;
        }
        pData = new char[dwLen + 1];
        // 获取版本资源信息。这个函数会检查资源信息，并将需要的数据复制到一个缓冲区里。
        BOOL bSuccess = GetFileVersionInfo(fullName.toStdWString().c_str(), 0, dwLen, pData);
        if (!bSuccess)
        {
            break;
        }

        struct LANGANDCODEPAGE
        {
            WORD wLanguage;
            WORD wCodePage;
        } *lpTranslate;

        LPVOID lpBuffer = nullptr;
        UINT uLen = 0;
        //核心函数VerQueryValue 用于从版本资源中获取信息，调用这个函数前，必须先用GetFileVersionInfo函数
        bSuccess = VerQueryValue(pData, (TEXT("\\VarFileInfo\\Translation")), (LPVOID*)&lpTranslate, &uLen);
        if (!bSuccess)
        {
            break;
        }
        QString str1, str2;
        str1.setNum(lpTranslate->wLanguage, 16);
        str2.setNum(lpTranslate->wCodePage, 16);
        str1 = "000" + str1;
        str2 = "000" + str2;

        //ProductVersion：产品版本号 FileVersion：文件版本号
        //        QString verPath = "\\StringFileInfo\\" + str1.right(4) + str2.right(4) + "\\ProductVersion";
        //        bSuccess = VerQueryValue(pData, (verPath.toStdWString().c_str()), &lpBuffer, &uLen);
        //        if (!bSuccess)
        //        {
        //            break;
        //        }
        //        result = QString::fromUtf16((const unsigned short int*)lpBuffer);

        //获得文件版本信息：FileVersion
        QString verPath ="\\StringFileInfo\\" + str1.right(4) + str2.right(4) + "\\FileVersion";
        bSuccess = VerQueryValue(pData, (verPath.toStdWString().c_str()), &lpBuffer, &uLen);
        if (!bSuccess)
        {
            break;
        }
        result = QString::fromUtf16((const unsigned short int*)lpBuffer);
    }
    while (false);
    if (nullptr != pData)
    {
        delete pData;
    }
    return result;
}

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << getFileVertion(QCoreApplication::applicationDirPath() + "/" + "libeay32.dll");
}


////获得文件说明：FileDescription
//    //---------------------------------------------------------
//    code ="\\StringFileInfo\\"+ strTranslation +"\\FileDescription";
//    bSuccess = VerQueryValue(lpData,
//    (code.toStdWString().c_str()),
//    &lpBuffer,
//    &uLen);
//    if (!bSuccess)
//    {
//    qDebug()<<"Get file verstion error!";
//    }
//    else
//    {
//    str_value="文件说明：" + QString::fromUtf16((const unsigned short int *)lpBuffer)+"\n";
//    fileInfomation +=str_value;
//}
////    //获得文件版本信息：FileVersion
//    //-----------------------------------------------------
//     code ="\\StringFileInfo\\"+ strTranslation +"\\FileVersion";
//    bSuccess = VerQueryValue(lpData,
//    (code.toStdWString().c_str()),
//    &lpBuffer,
//    &uLen);
//    if (!bSuccess)
//    {
//    qDebug()<<"获取文件版本信息错误!";

//    }
//    else
//    {
//    str_value="文件版本信息：" + QString::fromUtf16((const unsigned short int *)lpBuffer)+"\n";
//    fileInfomation +=str_value;
//    }
////    //获得文件产品名称
//    //---------------------------------------------------------
//    code ="\\StringFileInfo\\"+ strTranslation +"\\ProductName";
//    bSuccess = VerQueryValue(lpData,
//    (code.toStdWString().c_str()),
//    &lpBuffer,
//    &uLen);
//    if (!bSuccess)
//    {
//    qDebug()<<"Get file ProductName error!";

//    }
//    else
//    {
//    str_value="产品名称：" + QString::fromUtf16((const unsigned short int *)lpBuffer)+"\n";
//    fileInfomation +=str_value;
//   }
////    //获得产品版本信息：ProductVersion
//    //-----------------------------------------------------
//     code ="\\StringFileInfo\\"+ strTranslation +"\\ProductVersion";
//    bSuccess = VerQueryValue(lpData,
//    (code.toStdWString().c_str()),
//    &lpBuffer,
//    &uLen);
//    if (!bSuccess)
//    {
//    qDebug()<<"获取产品版本信息错误!";

//    }
//    else
//    {
//    str_value="产品版本信息：" + QString::fromUtf16((const unsigned short int *)lpBuffer)+"\n";
//    fileInfomation +=str_value;
//    }
////    //获得文件内部名称 InternalName
//    //---------------------------------------------------------
//    code ="\\StringFileInfo\\"+ strTranslation +"\\InternalName";
//    bSuccess = VerQueryValue(lpData,
//    (code.toStdWString().c_str()),
//    &lpBuffer,
//    &uLen);
//    if (!bSuccess)
//    {
//    qDebug()<<"Get file InternalName error!";

//    }
//    else
//    {
//    str_value="内部名称：" + QString::fromUtf16((const unsigned short int *)lpBuffer)+"\n";
//    fileInfomation +=str_value;
//   }


////    //获得原始文件名 OriginalFileName
//    //---------------------------------------------------------
//    code ="\\StringFileInfo\\"+ strTranslation +"\\OriginalFileName";
//    bSuccess = VerQueryValue(lpData,
//    (code.toStdWString().c_str()),
//    &lpBuffer,
//    &uLen);
//    if (!bSuccess)
//    {
//    qDebug()<<"Get file OriginalFileName error!";

//    }
//    else
//    {
//    str_value="原始文件名：" + QString::fromUtf16((const unsigned short int *)lpBuffer)+"\n";
//    fileInfomation +=str_value;
////获得合法版权 LegalTradeMarks 【Q tea  原创】
//    //---------------------------------------------------------
//    code ="\\StringFileInfo\\"+ strTranslation +"\\Type";
//    bSuccess = VerQueryValue( lpData,
//    (code.toStdWString().c_str()),
//    &lpBuffer,
//    &uLen);
//    if (!bSuccess)
//    {
//    qDebug()<<"Get file LegalTradeMarks error!";


//    }
//    else
//    {
//    str_value="版权：" + QString::fromUtf16((const unsigned short int *)lpBuffer)+"\n";
//    fileInfomation +=str_value;
//   }



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnOpen_clicked()
{
    QString pathsDir = QFileDialog::getExistingDirectory(this, "打开目录", ".");
    if (pathsDir.isEmpty())
    {
        return;
    }

    strCurRootPath = pathsDir;
    QStringList allFileList = CLFileOperateUtil::getListFiles(strCurRootPath);
    //m_lstFlieInfo = dir.entryInfoList(QDir::Files);
    ui->listWidget->addItems(allFileList);
    m_lstFlie = allFileList;

}

void MainWindow::on_btnCreate_clicked()
{
    QList<T_BinFileNodeMsg> lstBinFileNodeMsg;
//    foreach (QFileInfo fileInfo, m_lstFlieInfo) {

//        T_BinFileNodeMsg tBinFileNodeMsg;
//        tBinFileNodeMsg.name = fileInfo.fileName();
//        tBinFileNodeMsg.dir = fileInfo.dir().dirName();
//        tBinFileNodeMsg.version = getFileVertion(fileInfo.fileName());
//        ui->textBrowser->append(tBinFileNodeMsg.version);
//        lstBinFileNodeMsg.append(tBinFileNodeMsg);
//    }
    foreach (QString strFilePath, m_lstFlie) {

        T_BinFileNodeMsg tBinFileNodeMsg;
        QFileInfo fileInfo(strFilePath);
        tBinFileNodeMsg.name = fileInfo.fileName();
        QString strDir = fileInfo.dir().absolutePath();
        int pos = strCurRootPath.length();
        tBinFileNodeMsg.dir = strDir.mid(pos + 1);
        //tBinFileNodeMsg.dir = fileInfo.dir().dirName();
        tBinFileNodeMsg.version = getFileVertion(fileInfo.filePath());
        ui->textBrowser->append(tBinFileNodeMsg.version);
        lstBinFileNodeMsg.append(tBinFileNodeMsg);
    }
    CLVersionXmlTool::createVersionXmlFile("version_msg.xml", lstBinFileNodeMsg);
}
