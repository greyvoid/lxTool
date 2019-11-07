#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <QTextCodec>
#include <QFile>
#include <QApplication>

/*
 * 1、基本的表情，这类表情的对应utf-8编码又分为两种，例如 哈哈 这个表情的编码是\ud83d\ude04 占了两个字节长度，心 这个表情的编码为\u2764 只占了一个字节长度，这是因为emoji在Unicode中的编码范围不同，有一定的规律可循。

2、组合表情，这类表情是通过连接符\u200d连接，可能是多个基本表情组成的一个，也可能是一个表情加上颜色等样式，这样就会出现接收到很长一个字符串，最后解析出来只有一个表情符号的情况。

3、特殊的数字表情，常见的就是0-9带一个框的，这种的编码又有所不同，例如 1 是1\ufe0f\u20e3,2 是 2\ufe0f\u20e3，规律相同，都是数字后跟\ufe0f\u20e3。

4、一些旗帜表情，多数以\ud83c开始，但是\ud83c在组合表情中又用来连接表情的样式的，由于我的程序需求只需要处理100多个基本表情，没有涉及到旗子这块，所以没有处理，直接用缺省表情表示了
————————————————
版权声明：本文为CSDN博主「小无心」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/muwuxin/article/details/88896188
*/
///
/// \brief isEmoji
/// \param value
/// \param count
/// \return
///
bool isEmoji(int value, int & count)
{
    //0x200d -- 连接符
    //0xd83c----好像是颜色分割符 或者是旗帜?
    //0xfe0f ---好像是表情结束符
    //0xfe0f0x20e3--特殊符号的表情
    if ((value >= 0xd800 && value <= 0xdbff))
    {
        count = 2;
        return true;
    }
    else if ((0x2100 <= value && value <= 0x27ff && value != 0x263b)
             || (0x2b05 <= value && value <= 0x2b07)
             || (0x2934 <= value && value <= 0x2935)
             || (0x3297 <= value && value <= 0x3299)
             || value == 0xa9 || value == 0xae || value == 0x303d || value == 0x3030
             || value == 0x2b55 || value == 0x2b1c || value == 0x2b1b || value == 0x2b50
             || value == 0x231a)
    {
        count = 1;
        return true;
    }
    return false;
}




bool isContainEmoji(const QString  & strUtf8)
{
    bool bContain = false;
    std::u16string ut16 = strUtf8.toStdU16String();

    if (ut16.empty())
    {
        return false;
    }

    size_t len = ut16.length();
    for (size_t i = 0; i < len; ++i)
    {
        char16_t hs = ut16[i];
        if (0xd800 <= hs && hs <= 0xdbff)
        {
            if (ut16.length() > (i + 1))
            {
                char16_t ls = ut16[i + 1];
                int uc = ((hs - 0xd800) * 0x400) + (ls - 0xdc00) + 0x10000;
                if (0x1d000 <= uc && uc <= 0x1f77f)
                {
                    bContain = true;
                    break;
                }
            }
        }
        else
        {
            if (0x2100 <= hs && hs <= 0x27ff)
            {
                bContain = true;
            }
            else if (0x2B05 <= hs && hs <= 0x2b07)
            {
                bContain = true;
            }
            else if (0x2934 <= hs && hs <= 0x2935)
            {
                bContain = true;
            }
            else if (0x3297 <= hs && hs <= 0x3299)
            {
                bContain = true;
            }
            else if (hs == 0xa9 || hs == 0xae || hs == 0x303d || hs == 0x3030 || hs == 0x2b55 || hs == 0x2b1c || hs == 0x2b1b || hs == 0x2b50)
            {
                bContain = true;
            }
            else if (hs >= 0x2600 && hs <= 0x27BF) // 杂项符号与符号字体
            {
                bContain = true;
            }
            else if (hs == 0x303D || hs == 0x2049 || hs == 0x203C || hs == 0x205F)
            {
                bContain = true;
            }
            else if (hs >= 0x2000 && hs <= 0x200F)//
            {
                bContain = true;
            }
            else if (hs >= 0x2028 && hs <= 0x202F)//
            {
                bContain = true;
            }
            else if (hs >= 0x2065 && hs <= 0x206F)
            {
                bContain = true;
            }
            /* 标点符号占用区域 */
            else if (hs >= 0x2100 && hs <= 0x214F)// 字母符号
            {
                bContain = true;
            }
            else if (hs >= 0x2300 && hs <= 0x23FF)// 各种技术符号
            {
                bContain = true;
            }
            else if (hs >= 0x2B00 && hs <= 0x2BFF)// 箭头A
            {
                bContain = true;
            }
            else if (hs >= 0x2900 && hs <= 0x297F)// 箭头B
            {
                bContain = true;
            }
            else if (hs >= 0x3200 && hs <= 0x32FF)// 中文符号
            {
                bContain = true;
            }
            else if (hs >= 0xD800 && hs <= 0xDFFF)// 高低位替代符保留区域
            {
                bContain = true;
            }
            else if (hs >= 0xE000 && hs <= 0xF8FF)// 私有保留区域
            {
                bContain = true;
            }
            else if (hs >= 0xFE00 && hs <= 0xFE0F)// 变异选择器
            {
                bContain = true;
            }
            else if (hs >= 0x10000)
            {
                bContain = true;
            }

        }
    }

    return bContain;
}



MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTextCodec *gbk = QTextCodec::codecForName("gb18030");
    QTextCodec *utf8 = QTextCodec::codecForName("utf-8");

    QString str = "👗"; // 失败，默认gbk, 但gbk存储不了绘文字
    QString strUnicode = gbk->toUnicode(str.toLocal8Bit());
    qDebug() << strUnicode.toUtf8();

    QString str2 = QString::fromUtf8("👗");
    QString strUnicode2 = utf8->toUnicode(str2.toUtf8());
    qDebug() << strUnicode2.toUtf8();

    QString strEmoji = ui->lineEdit->text(); // 此次获得的text为utf-8
    qDebug() << strEmoji.toUtf8();
    QString strEmojiUnicode = utf8->toUnicode(strEmoji.toUtf8());
    qDebug() << strEmojiUnicode.toUtf8();

    QString chinese = "汉"; //默认gbk, 存储汉字成功
    qDebug() << chinese.toLocal8Bit();

    // test
    QByteArray bytesChinese;
    bytesChinese.append(0xBA);
    bytesChinese.append(0xBA);
    QString str222 = QString::fromLocal8Bit(bytesChinese); // 赋予字节数组为一个gbk字符的意义
    qDebug() << str222;

    // test2
    QByteArray bytesEmoji;
    bytesEmoji.append(0xF0);
    bytesEmoji.append(0x9D);
    bytesEmoji.append(0x8C);
    bytesEmoji.append(0x86);
    qDebug() << bytesEmoji;
    QString strEmojiUnicode3333 = utf8->toUnicode(bytesEmoji);// 赋予字节数组为一个utf-8字符的意义
    qDebug() << strEmojiUnicode3333.toUtf8();
    ui->label_2->setText(strEmojiUnicode3333);

    // test3 从unicode文本中读取
    QFile file(QCoreApplication::applicationDirPath() + "/" + "Emoji.txt");
    if (!file.open(QIODevice::ReadOnly))
    {
        return;
    }
    QByteArray bytesAll = file.readAll();
    qDebug() << bytesAll;
    QString strEmojiUnicode4444 = utf8->toUnicode(bytesAll);
    qDebug() << strEmojiUnicode4444; // 打印调用的是ansi指定本系统默认的字符集gb2312，所以打印不出啊
    ui->label->setText(strEmojiUnicode4444);

    qDebug() << isContainEmoji(QString::fromUtf8("汉字"));    // false -ok
    qDebug() << isContainEmoji(QString(bytesAll));  // true -ok

}

MainWindow::~MainWindow()
{
    delete ui;
}
