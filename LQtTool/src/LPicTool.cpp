#include "LPicTool.h"
#include <QFile>
#include <QBuffer>
#include <QFileDialog>


LPicTool::LPicTool(QObject *parent) : QObject(parent)
{

}

LPicTool::~LPicTool()
{

}

void LPicTool::picToData(QString fromPic, QString toData, QString myformat)
{
    QImage img(fromPic);
    QByteArray ba;
    QBuffer buf(&ba);
    img.save(&buf,"JPG");//按照JPG解码保存数据
    QByteArray cc=qCompress(ba,1);
    QByteArray hh;
    if (myformat=="Hex")
    {
        hh=cc.toHex();//16进制数据
    }
    else
    {
        hh=cc.toBase64();//base64数据
    }
    QString str(hh);
    QFile file(toData);
    if (file.open(QFile::WriteOnly))
    {
        file.write(str.toLatin1());
        file.close();
    }
}

void LPicTool::dataToPic(QString fromData, QString toPic, QString myformat)
{
    QFile file(fromData);
    if (file.open(QFile::ReadOnly))
    {
        QByteArray read=file.readAll();
        file.close();
        QString ss=QString::fromLatin1(read.data(),read.size());
        QByteArray rc;
        if (myformat=="Hex")
        {
            rc=QByteArray::fromHex(ss.toLatin1());
        }
        else
        {
            rc=QByteArray::fromBase64(ss.toLatin1());
        }
        QByteArray rdc=qUncompress(rc);

        QImage img;
        img.loadFromData(rdc);
        img.save(toPic);
    }
}

