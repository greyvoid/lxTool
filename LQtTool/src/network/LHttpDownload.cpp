#include "LHttpDownload.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QFileInfo>
#include <QTimer>
#include <QEventLoop>
#include <QDir>


#define B       1
#define KB      1024
#define MB      1024*1024
#define GB      1024*1024*1024

LHttpDownload::LHttpDownload(QObject *parent)
    : LHttpClient(parent)
{

}

LHttpDownload::~LHttpDownload()
{

}



void LHttpDownload::download(const QUrl &urlRequest, const QString &strFileName, QString strDir, int nTimeout)
{
    m_tTaskCur.reset();
    // 文件名
    if(strFileName.isEmpty())
    {
        QFileInfo fileInfo(urlRequest.path());
        m_tTaskCur.rename = fileInfo.fileName();
    }
    else
    {
        m_tTaskCur.rename = strFileName;
    }

    //文件夹为空则默认当前程序运行路径
    if(strDir.isEmpty())
    {
        m_tTaskCur.dirSaveTo = QDir::currentPath();
    }
    else
    {
        QDir dir(strDir);
        //没有此文件夹，则创建
        if( !dir.exists() )
        {
            dir.mkpath(strDir);
        }
        m_tTaskCur.dirSaveTo = strDir;
    }
    m_tTaskCur.taskInfoListId = m_listTaskDownloadInfo.size();
    m_tTaskCur.url = urlRequest;
    m_tTaskCur.size = getFileTotalSize(m_tTaskCur.url.url());
    m_listTaskDownloadInfo.append(m_tTaskCur);
    get(urlRequest, nTimeout);
}

void LHttpDownload::downloadList(const QStringList &urlsStringList)
{
    foreach(QString url, urlsStringList)
    {
        T_TaskDownloadInfo tTaskDownloadInfo;
        tTaskDownloadInfo.url = url;
        tTaskDownloadInfo.size = getFileTotalSize(url);
        m_listTaskDownloadInfo.append(tTaskDownloadInfo);
    }
    start();
}

// 获取要下载文件的大小
qint64 LHttpDownload::getFileTotalSize(QString url, int tryTimes)
{
    qint64 size = -1;

    if (tryTimes <= 0)
    {
        tryTimes = 1;
    }

    do
    {
        QEventLoop loop;
        QTimer timer;
        m_netReply = m_netAccessManager->head(QNetworkRequest(url)); //发出请求，获取文件地址的头部信息;
        if (!m_netReply)
        {
            continue;
        }
        connect(m_netReply, SIGNAL(finished()), &loop, SLOT(quit()));
        connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));

        timer.start(2000);
        loop.exec();

        if (m_netReply->error() != QNetworkReply::NoError)
        {
            qDebug() << m_netReply->errorString();
            continue;
        }
        else if (!timer.isActive())
        {
            // 请求超时超时,未获取到文件信息;
            qDebug() << "Request Timeout";
            continue;
        }
        timer.stop();

        QVariant varSize = m_netReply->header(QNetworkRequest::ContentLengthHeader);
        size = varSize.toLongLong();
        m_netReply->deleteLater();
        break;
    } while (tryTimes--);

    return size;
}

T_TaskDownloadInfo LHttpDownload::getTaskInfoById(int nTaskId)
{
    foreach (T_TaskDownloadInfo tTaskDownloadInfo, m_listTaskDownloadInfo)
    {
        if (tTaskDownloadInfo.taskInfoListId == nTaskId)
        {
            return tTaskDownloadInfo;
        }
    }
}

void LHttpDownload::start()
{
    if (m_listTaskDownloadInfo.empty())
    {
        return;
    }
    foreach (T_TaskDownloadInfo tTaskDownloadInfo, m_listTaskDownloadInfo)
    {
        if(tTaskDownloadInfo.eDowlLoadState == ED_Downloading)
        {
            return;
        }
    }
    foreach (T_TaskDownloadInfo tTaskDownloadInfo, m_listTaskDownloadInfo)
    {
        if(tTaskDownloadInfo.eDowlLoadState == ED_Ready)
        {
            download(tTaskDownloadInfo.url, tTaskDownloadInfo.rename, tTaskDownloadInfo.dirSaveTo);
            break;
        }
    }
}

void LHttpDownload::stop()
{
    disconnect(m_netReply,SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    disconnect(m_netReply, SIGNAL(finished()), this, SLOT(onFinished()));
    disconnect(m_netReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
    disconnect(m_netReply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(onDownloadProgress(qint64,qint64)));
    m_netReply->abort();
    m_netReply->deleteLater();
}

void LHttpDownload::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    // 更新单个任务进度
    for (QList<T_TaskDownloadInfo>::iterator iter = m_listTaskDownloadInfo.begin() ; iter != m_listTaskDownloadInfo.end() ; ++iter)
    {
        if((*iter).taskInfoListId == m_tTaskCur.taskInfoListId)
        {
            (*iter).completed = bytesReceived;
            break;
        }
    }
    emit downloadProgress(bytesReceived, bytesTotal);

    // 更新总进度
    quint64 llSizeTotal = 0;
    quint64 llSizeAlready = 0;
    foreach(T_TaskDownloadInfo tTaskDownloadInfo, m_listTaskDownloadInfo)
    {
        llSizeAlready += tTaskDownloadInfo.completed;
        llSizeTotal += tTaskDownloadInfo.size;
    }
    emit downloadProgressAll(llSizeAlready, llSizeTotal);
}

void LHttpDownload::onFinished()
{
    //如果文件已经存在，那么删除
    qDebug() << "child LHttpDownload";
    if(QFile::exists(m_tTaskCur.filePath()))
    {
        QFile::remove(m_tTaskCur.filePath());
    }

    QFile file(m_tTaskCur.filePath());
    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug()<<"不能存储文件："<< m_tTaskCur.filePath();
        return;
    }
    file.write(m_httpDataBuffer.readAll());
    file.flush();//注意需要刷新
    file.close();
    for (QList<T_TaskDownloadInfo>::iterator iter = m_listTaskDownloadInfo.begin() ; iter != m_listTaskDownloadInfo.end() ; ++iter)
    {
        if((*iter).taskInfoListId == m_tTaskCur.taskInfoListId)
        {
            (*iter).eDowlLoadState = ED_Completed;
            break;
        }
    }
    // 单个任务下载完成
    emit downloadCompleted(m_tTaskCur);
    bool bCompletedAll = true;
    foreach(T_TaskDownloadInfo tTaskDownloadInfo, m_listTaskDownloadInfo)
    {
        if (tTaskDownloadInfo.eDowlLoadState != ED_Completed)
        {
            bCompletedAll = false;
            break;
        }
    }
    if (bCompletedAll)
    {
        emit finishedAllTask();
    }

    //        // 写文件-形式为追加
    //        QFile file(m_strBaseName + ".jpg");
    //        if (file.open(QIODevice::Append))
    //        {
    //            //if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    //                file.write(m_pReply->readAll());
    //            file.close();
    //        }
    //            QString strFileName = m_strBaseName + ".png";
    //               QImageWriter imageWriter;
    //               imageWriter.setFormat("png");
    //               imageWriter.setFileName(strFileName);
    //               if( imageWriter.canWrite() )
    //               {
    //                  imageWriter.write( QImage(m_strBaseName + ".jpg", "jpg") );
    //               }

}

const char *LHttpDownload::formatByte(double dByteNum)
{
    std::string unit = "B";
    double dByteNumFormat = dByteNum;
    char byteFormat[32];

    if (dByteNumFormat > GB)
    {
        unit = "G";
        dByteNumFormat /= GB;
    }
    else if (dByteNumFormat > MB)
    {
        unit = "M";
        dByteNumFormat /= MB;
    }
    else if (dByteNumFormat > KB)
    {
        unit = "kB";
        dByteNumFormat /= KB;
    }

    sprintf(byteFormat, "%d%s", dByteNumFormat, unit.c_str());
    return byteFormat;
}




