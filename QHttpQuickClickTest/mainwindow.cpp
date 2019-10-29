#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "HttpClient.h"
#include "openssl/aes.h" //使用openssl的aes
#include <QDateTime>
#include <QCryptographicHash>
#include <QJsonObject>
#include <QJsonDocument>
#include <QtDebug>
#include <QTextCodec>
#include <assert.h>

#define BUFFSIZE 1024				//字符串缓存长度
#define ERR_TOO_LONG_PASSWORD 28
#define ERR_AES_KEY_SET 29

#define MDSV_VER    "1.0.1"
#define MDSV_CHINESE  "中文"
#define MDSV_ENGLISH  "ENGLISH"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_strName("ex_leisx")
    , m_strPasswd("Limeilian..1011")
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleDownloadCompleted(bool bOk, CHttpClient *pHttpQuery)
{
    if (!bOk)
    {
        return;
    }
    qDebug() << "handleDownloadCompleted";
    ULONG nQueryTag = pHttpQuery->e_QueryTag();
    QByteArray byteData = pHttpQuery->e_GetData();
    qDebug() << byteData << "\n";
    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson(byteData, &json_error);
    if (json_error.error == QJsonParseError::NoError)
    {
        QJsonObject objRoot;
        if (parse_doucment.isObject())
        {
            objRoot = parse_doucment.object();
        }
        //handleObjRoot(objRoot, nQueryTag);
        //qDebug() << objRoot << nQueryTag;
    }
}

void MainWindow::handReadyRead(CHttpClient *pHttpQuery)
{
    qDebug() << "handReadyRead";
}

//MainWindow::handleObjRoot(QJsonObject isonObj, ULONG tag)
//{

//}

void MainWindow::on_btnRequest_clicked()
{
    QJsonObject jsonObj;
    jsonObj["path"] = "/";
    jsonObj["index"] = 1;
    jsonObj["pageSize"] = 100;
    jsonObj["type"] = "1";
    jsonObj["sortFiled"] = 0;
    jsonObj["sortType"] = 2;
    jsonObj["token"] = ui->lineEdit->text();

    QJsonDocument document;
    document.setObject(jsonObj);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    QString json_str(byte_array);

    CHttpClient *pTempHttpClient = CHttpClient::e_GetTempObject(1);
    connect(pTempHttpClient, SIGNAL(readyRead(CHttpClient*)),this, SLOT(handReadyRead(CHttpClient*)));
    connect(pTempHttpClient, SIGNAL(downloadCompleted(bool,CHttpClient*)),
            this, SLOT(handleDownloadCompleted(bool,CHttpClient*)));


    QString strUrl = "https://yunpan-sit.midea.com:8443/v1/mideastore/service/eshare/file/list";
    qDebug() << json_str << "  length = " << json_str.length();
    pTempHttpClient->e_HttpPost(strUrl, json_str.toStdString().data(), json_str.length() + 4);

}


#define AES_BITS 128
//#undef AES_BLOCK_SIZE
//#define AES_BLOCK_SIZE 32
//#define AES_IV_SIZE 16
// 全局向量
unsigned char AES_IVEC[AES_BLOCK_SIZE] =
{
    0x30, 0x31, 0x30, 0x32, 0x30, 0x33, 0x30, 0x34,
    0x30, 0x35, 0x30, 0x36, 0x30, 0x37, 0x30, 0x38
};

//填充方式：
//NoPadding：
//不做任何填充，但是要求明文必须是16字节的整数倍。

//PKCS5Padding（默认）：
//如果明文块少于16个字节（128bit），在明文块末尾补足相应数量的字符，且每个字节的值等于缺少的字符数。

//文本加密
int aesCbcEncrypt(const char* pSource, const char* key, unsigned char* ivec, char* aesdata)
{
    char buffSrc[BUFFSIZE];
    char buffDest[BUFFSIZE];
    unsigned char keyTemp[AES_BLOCK_SIZE + 1];
    unsigned char ivecTmp[AES_BLOCK_SIZE]; //可读写的一块内存。长度必须是16字节。
    int nLengthSrc = 0;
    int nSetDataLen = 0; // 取16（AES_BLOCK_SIZE）的整数倍

    memset(buffSrc, 0x00, sizeof(buffSrc));
    strcpy(buffSrc, pSource);
    nLengthSrc = strlen(buffSrc);

    //memset(keyTemp, 0x00, sizeof(keyTemp));
    //memcpy(keyTemp, key, AES_BLOCK_SIZE);

    memcpy(ivecTmp, ivec, AES_BLOCK_SIZE);


    QString keyStr(key);
    QByteArray bytesKey = keyStr.toLatin1();
    QByteArray bytesKeyMD5 = QCryptographicHash::hash(bytesKey, QCryptographicHash::Md5);
    QByteArray bytesKeyMD5Hex = bytesKeyMD5.toHex().mid(8, 16);	//md5:mid(8, 16) 32位转16位,字符截断
    //QByteArray bytesKeyMD5Hex = bytesKeyMD5.mid(8).toHex();

    // test 不使用md5，自定义key
    //bytesKeyMD5Hex = "asdfwetyhjuytrfd";

    // 设置加密密钥
    AES_KEY AesKey;
    memset(&AesKey, 0x00, sizeof(AES_KEY));
    if (AES_set_encrypt_key((const uchar*)bytesKeyMD5Hex.toStdString().c_str(), 128, &AesKey) < 0)
    {
        return ERR_AES_KEY_SET;
    }

    //    if ((nLengthSrc % AES_BLOCK_SIZE) == 0)
    //    {
    //        nSetDataLen = nLengthSrc;
    //    }
    //    else
    //    {
    //        nSetDataLen = ((nLengthSrc / AES_BLOCK_SIZE) +  1) * AES_BLOCK_SIZE;
    //    }
    // 额外的长度, 用于补齐到（AES_BLOCK_SIZE）的整数倍

    // 去掉补位
        int nLengthExtra = (AES_BLOCK_SIZE - (nLengthSrc % AES_BLOCK_SIZE));
        if (nLengthSrc + nLengthExtra >= BUFFSIZE)
        {
            return ERR_TOO_LONG_PASSWORD;
        }

        for (int i = 0; i < nLengthExtra; ++i)
        {
            buffSrc[nLengthSrc + i] = nLengthExtra;
        }
        nSetDataLen = nLengthSrc + nLengthExtra;
        buffSrc[nSetDataLen] = '\0';

    // 不用补位
    //nSetDataLen = nLengthSrc;

    // 加密
    AES_cbc_encrypt((const unsigned char*)buffSrc
                    , (unsigned char*)buffDest
                    , nSetDataLen
                    , &AesKey
                    , (unsigned char*)ivecTmp
                    , AES_ENCRYPT);
    // 不用strcpy(aesdata, buffDest);，防止里面有'\0'，得到16字节密文
    for (int i = 0; i < nSetDataLen; ++i)
    {
        *(aesdata + i) = buffDest[i];
    }
    *(aesdata + nSetDataLen) = '\0';


    return 0;
}

int aesEncrypt(const char* pSource, const char* key, unsigned char* ivec, char* aesdata)
{
    char buffSrc[BUFFSIZE];
    char buffDest[BUFFSIZE];
    unsigned char keyTemp[AES_BLOCK_SIZE + 1];
    unsigned char ivecTmp[AES_BLOCK_SIZE]; //可读写的一块内存。长度必须是16字节。
    int nLengthSrc = 0;
    int nSetDataLen = 0; // 取16（AES_BLOCK_SIZE）的整数倍

    memset(buffSrc, 0x00, sizeof(buffSrc));
    strcpy(buffSrc, pSource);
    nLengthSrc = strlen(buffSrc);

    memset(keyTemp, 0x00, sizeof(keyTemp));
    memcpy(keyTemp, key, AES_BLOCK_SIZE);

    memcpy(ivecTmp, ivec, AES_BLOCK_SIZE);


    QString keyStr(key);
    QByteArray bytesKey = keyStr.toLatin1();
    QByteArray bytesKeyMD5 = QCryptographicHash::hash(bytesKey, QCryptographicHash::Md5);
    QByteArray bytesKeyMD5Hex = bytesKeyMD5.toHex().mid(8, 16);	//md5:mid(8, 16) 32位转16位,字符截断
    //QByteArray bytesKeyMD5Hex = bytesKeyMD5.mid(8).toHex();

    // 设置加密密钥
    AES_KEY AesKey;
    memset(&AesKey, 0x00, sizeof(AES_KEY));
    if (AES_set_encrypt_key((const uchar*)bytesKeyMD5Hex.toStdString().c_str(), 128, &AesKey) < 0)
    {
        return ERR_AES_KEY_SET;
    }

    int nLengthExtra = (AES_BLOCK_SIZE - (nLengthSrc % AES_BLOCK_SIZE));
    if (nLengthSrc + nLengthExtra >= BUFFSIZE)
    {
        return ERR_TOO_LONG_PASSWORD;
    }

    for (int i = 0; i < nLengthExtra; ++i)
    {
        buffSrc[nLengthSrc + i] = nLengthExtra;
    }
    nSetDataLen = nLengthSrc + nLengthExtra;
    buffSrc[nSetDataLen] = '\0';

    unsigned int nBlockNum = nSetDataLen / AES_BLOCK_SIZE;
    std::string strSrc(buffSrc);
    std::string strRet;
    for(unsigned int i = 0; i < nBlockNum; ++i)
    {
        std::string str16 = strSrc.substr( i * AES_BLOCK_SIZE, AES_BLOCK_SIZE);
        unsigned char out[AES_BLOCK_SIZE];
        memset(out, 0, AES_BLOCK_SIZE);
        AES_encrypt((const unsigned char*)str16.c_str(), out, &AesKey);
        strRet += std::string((const char*)out, AES_BLOCK_SIZE);
    }

    for (int i = 0; i < nSetDataLen; ++i)
    {
        *(aesdata + i) = strRet[i];
    }
    *(aesdata + nSetDataLen) = '\0';
    return 0;
}



std::string EncodeAES( const std::string& password
                       , const std::string& data )
{
    AES_KEY aes_key;
    if(AES_set_encrypt_key((const unsigned char*)password.c_str()
                           , password.length() * 8, &aes_key) < 0)
    {
        assert(false);
        return "";
    }
    std::string strRet;
    std::string data_bak = data;
    unsigned int data_length = data_bak.length();
    int padding = 0;
    if (data_bak.length() % AES_BLOCK_SIZE > 0)
    {
        padding =  AES_BLOCK_SIZE - data_bak.length() % AES_BLOCK_SIZE;
    }
    data_length += padding;
    while (padding > 0)
    {
        data_bak += '\0';
        padding--;
    }
    for(unsigned int i = 0; i < data_length/AES_BLOCK_SIZE; i++)
    {
        std::string str16 = data_bak.substr(i*AES_BLOCK_SIZE, AES_BLOCK_SIZE);
        unsigned char out[AES_BLOCK_SIZE];
        memset(out, 0, AES_BLOCK_SIZE);
        AES_encrypt((const unsigned char*)str16.c_str(), out, &aes_key);
        strRet += std::string((const char*)out, AES_BLOCK_SIZE);
    }
    return strRet;
}

void MainWindow::autoLogin()
{
    //数据块
    //unsigned char iv[17] = "0102030405060708";  //字符乱码导致登录失败，需使用QString优化
    //iv[16] = 0;
    qint64 time = QDateTime::currentDateTime().currentMSecsSinceEpoch();
    QString strMsTime = QString::number(time);
    std::string szPasswd = m_strPasswd.toStdString();

    //test--1
    //QString strMsTime = "1564364846159";
    //m_strName = "rentf1";
    //m_strPasswd = "ningning1231131,";

    //test--2
    //QString strMsTime = "1564478453454";
    //m_strPasswd = "@，130uuqrooqr,2"; //--1564478453454 --17b2a5f3b4f53757a764bca9d0f45812400475a35d002a61f69107e4c27796ad

    // test3
    //QString strMsTime = "1564478453454";
    //m_strPasswd = "ningning";

    //aTest();



//    int nCountEncrypt = szPasswd.length() / AES_BLOCK_SIZE + 1;
//    QByteArray bytesPasswdEncrypt;
//    for (int i = 0; i < nCountEncrypt; ++i)
//    {
//        std::string str16 = szPasswd.substr(i*AES_BLOCK_SIZE, AES_BLOCK_SIZE);
//    char aesPwd[BUFFSIZE];
//    memset(aesPwd, 0, sizeof(aesPwd));
//    int ret = aesCbcEncrypt(str16.c_str()
//                            , strMsTime.toStdString().c_str()
//                            , AES_IVEC
//                            , aesPwd);
//    if (ret != 0)
//    {
//        return;
//    }
//    bytesPasswdEncrypt += QByteArray(aesPwd, 16);
//    }

    int nCountEncrypt = szPasswd.length() / AES_BLOCK_SIZE + 1;
    int nEncryptPasswdLength = nCountEncrypt * AES_BLOCK_SIZE;
    char aesPwd[BUFFSIZE];
    memset(aesPwd, 0, sizeof(aesPwd));
    int ret = aesCbcEncrypt(szPasswd.c_str()
                            , strMsTime.toStdString().c_str()
                            , AES_IVEC
                            , aesPwd);
    if (ret != 0)
    {
        return;
    }
    QByteArray bytesPasswdEncrypt = QByteArray(aesPwd, nEncryptPasswdLength);

    QString fromType(2);	//防止web与PC互踢参数
    //QString strPassword = QByteArray(aesPwd, 16).toHex();	//16位长度
    QString strPassword = bytesPasswdEncrypt.toHex();	//16位长度
    //QString strPassword = "0180a3a1d7b654d90bc773e833c8595b0180a3a1d7b654d90bc773e833c8595b";
    qDebug() << "encrypt rusult" << bytesPasswdEncrypt.toBase64() << "  " << strPassword;

    QJsonObject jsonObj;
    jsonObj["userAccount"] = m_strName;
    jsonObj["password"] = strPassword;
    jsonObj["stamp"] = strMsTime;
    jsonObj["fromType"] = fromType;
    jsonObj["language"] = "中文";
    jsonObj["verifyCode"] = QString("");

    QJsonDocument document;
    document.setObject(jsonObj);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    QString json_str(byte_array);

    CHttpClient *pTempHttpClient = CHttpClient::e_GetTempObject(1);
    connect(pTempHttpClient, SIGNAL(readyRead(CHttpClient*)),this, SLOT(handReadyRead(CHttpClient*)));
    connect(pTempHttpClient, SIGNAL(downloadCompleted(bool,CHttpClient*)),
            this, SLOT(handleDownloadCompleted(bool,CHttpClient*)));

//    case 0:	//sit环境
//        return "https://yunpan-sit.midea.com:8443";
//        break;
//    case 1:	//生产环境
//        return "https://yunpan.midea.com:443";
//        break;
//    case 2:	//uat环境
//        return "https://yunpan-uat.midea.com:28443";
//        break;
//    case 3:	//李德文环境
//        return "http://CN01XIT00000554.cn.Midea.com:28062";
//        break;
//    case 4:	//PC测试专用环境
//        return "https://10.17.158.7:8443";
        //
       // QString strUrl = "https://yunpan.midea.com:443/v1/mideastore/service/login";
    QString strUrl = "https://yunpan-sit.midea.com:8443/v1/mideastore/service/login";
    qDebug() << json_str << "  length = " << json_str.length();
    pTempHttpClient->e_HttpPost(strUrl, json_str.toStdString().data(), json_str.length() + 4);

}

void MainWindow::aTest()
{
    //test debug
    QString strMSecsSinceEpoch = ui->leMSecsSinceEpoch->text();
    qlonglong llDateTime = strMSecsSinceEpoch.toLongLong();
    QString strCurDateTime = QDateTime::fromTime_t(llDateTime / 1000).toString("yyyy-MM-dd hh:mm:ss");
    qDebug() << "strCurDateTime" << strCurDateTime;
}

void MainWindow::on_btnLogin_clicked()
{
    autoLogin();
}
