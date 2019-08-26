#ifndef LHTTPDOWNLOAD_H
#define LHTTPDOWNLOAD_H

#include <QList>
#include "LHttpClient.h"

enum E_DowlLoadState
{
    ED_Ready,
    ED_Downloading,
    ED_Completed,
    ED_Error
};

struct T_TaskDownloadInfo
{
    int taskInfoListId;                     // 任务id
    int controlState;                       // 手动还是立即下载
    E_DowlLoadState eDowlLoadState;         // 下载状态
    QUrl url;                               // url地址
    QStringList urlsStringList;             // url列表
    bool bHaveProxy;                        // 是否有代理,没有代理就直接连接
    bool bSingleProxy;                      // 是否单个代理
    int singleProxyId;                      // 单个代理id
    bool mutipleProxyBool;                  // 是否多个代理
    QList <int> mutipleProxyIdsList;        // 多个代理列表,每个线程使用不同的代理服务器
    QString referrer;                       // url来源于
    QString dirSaveTo;                      // 保存当地目录
    QString rename;                         // 重命名，即保存的文件名
    QString comment;                        // 注释
    QString user;                           // 用户名
    QString password;                       // 密码
    int splite;                             // 分离成几个线程下载,最大5个
    int retry;                              // 重试次数
    qint64 size;                            // 文件大小
    qint64 completed;                       // 已完成大小
    qint64 lastCompleted;                   //
    qint64 startPosition;                   //
    qint64 speed;                           // 速度,如果需要速度可以通过QTime每隔0.3s
    qint64 elapsedTime;                     // 剩余时间
    QList <qint64> speedPointList;          //

    T_TaskDownloadInfo()
    {

    }

    QString filePath()
    {
        return dirSaveTo + "/" + rename;
    }

    void reset()
    {
        taskInfoListId = -1;
        eDowlLoadState = ED_Ready;
        completed = 0;
        size = 0;
    }

};

// 一个client同一时间只能存在一个任务
class LHttpDownload : public LHttpClient
{
    Q_OBJECT

public:
    LHttpDownload(QObject *parent = 0);
    virtual ~LHttpDownload();
    static const char* formatByte(double dByteNum);

public:
    void download(const QUrl& urlRequest, const QString & strFileName="", QString strDir="", int nTimeout = 6000);
    void downloadList(const QStringList & urlsStringList);
    qint64 getFileTotalSize(QString url, int tryTimes = 2);
    T_TaskDownloadInfo getTaskInfoById(int nTaskId);
    void start();
    void stop();

signals:
    // http单个下载完成事件保存完成信号
    void downloadCompleted(T_TaskDownloadInfo tTaskDownloadInfo);
    // 整个任务列表完成进度
    void downloadProgressAll(qint64 bytesReceived, qint64 bytesTotal);

    void finishedAllTask();

private slots:
    virtual void onDownloadProgress(qint64 bytesReceived,qint64 bytesTotal);
    void onFinished();

private:
    T_TaskDownloadInfo m_tTaskCur;
    QList<T_TaskDownloadInfo> m_listTaskDownloadInfo;
};

#endif // LHTTPDOWNLOAD_H













