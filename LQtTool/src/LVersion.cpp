#include "LVersion.h"
#include <QStringList>
#include <QtDebug>

LVersion::LVersion(QString strVersion, QObject *parent)
    : QObject(parent)
    , m_strVersion(strVersion)
    , m_nMajor(0)
    , m_nMinor(0)
    , m_nRevision(0)
{
    QStringList strlstVersion = m_strVersion.split('.');
    if (strlstVersion.size() > 4)
    {
        qDebug() << "版本号格式错误";
        return;
    }
    if (strlstVersion.size() < 2)
    {
        qDebug() << "主版本和子版本号不能省略";
        return;
    }
    bool bMajor = false;
    bool bMinor = false;
    bool bRevision = false;

    m_nMajor = strlstVersion.at(0).toInt(&bMajor);
    m_nMinor = strlstVersion.at(1).toInt(&bMinor);
    if (bMajor || bMinor)
    {
        qDebug() << "主版本和子版本号不能省略";
        return;
    }
    if (strlstVersion.size() > 2)
    {
        m_nRevision = strlstVersion.at(2).toInt(&bRevision);
    }

}

LVersion::~LVersion()
{

}

bool LVersion::operator >(const LVersion &rhs)
{
    // 比较主版本号
    if (m_nMajor > rhs.m_nMajor)
    {
        return true;
    }
    if (m_nMajor < rhs.m_nMajor)
    {
        return false;
    }
    // 比较子版本号
    if (m_nMinor > rhs.m_nMinor)
    {
        return true;
    }
    if (m_nMinor < rhs.m_nMinor)
    {
        return false;
    }
    //
    if (m_nRevision > rhs.m_nRevision)
    {
        return true;
    }
    if (m_nRevision < rhs.m_nRevision)
    {
        return false;
    }
    return false;

}

int CompareVersion(QString strVer1, QString strVer2)
{
    if ( !strVer1.compare( strVer2 ) )
    {
        return 0; // 相等
    }

    QStringList list1 = strVer1.split( "." );
    QStringList list2 = strVer2.split( "." );

    int iTotal1 = list1.count();
    int iTotal2 = list2.count();

    int iTotal = iTotal1 > iTotal2 ? iTotal2 : iTotal1;

    int iValue1 = 0, iValue2 = 0;
    bool ibOK1 = false, ibOK2 = false;
    for ( int iNum = 0; iNum < iTotal; ++iNum )
    {
        iValue1 = list1[iNum].toInt( &ibOK1 );
        if (!ibOK1)
        {
            iValue1=0;
        }

        iValue2 = list2[iNum].toInt( &ibOK2 );
        if (!ibOK2)
        {
            iValue2 = 0;
        }

        if (iValue1 == iValue2)
        {
            continue;
        }
        else if ( iValue1 < iValue2 )
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }

    return iTotal1 < iTotal2 ? -1 : 1;
}
