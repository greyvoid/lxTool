#include "LVersion.h"
#include <QStringList>
#include <QtDebug>

CLVersion::CLVersion(QString strVersion, QObject *parent)
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

CLVersion::~CLVersion()
{

}

bool CLVersion::operator =(const CLVersion &rhs)
{
    if (m_nMajor == rhs.m_nMajor && m_nMinor == rhs.m_nMinor && m_nRevision == rhs.m_nRevision)
    {
        return true;
    }
    return false;
}

bool CLVersion::operator >(const CLVersion &rhs)
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

bool CLVersion::operator <(const CLVersion &rhs)
{
    if (*this == rhs)
    {
        return false;
    }
    else if (*this > rhs)
    {
        return false;
    }

    return true;
}

int compareVersion(QString strVer1, QString strVer2)
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





#include <string>
#include <stdio.h>
#include <iostream>
#include <math.h>

typedef struct
{
    int n;
    int* pinfo;
}versioninfo;

int chartoint(const char str)
{
    char strcmp[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(int i=0;i<62;i++)
    {
        if (str == strcmp[i])
            return i > 35 ? i - 26 : i;
    }
    return -1;
}
int stringtoint(const char* str)
{
    const char* ptemp1 = str;
    for (; *ptemp1 != '\0'; ++ptemp1); // 指针指向'\0'的地址
    int n = ptemp1 - str; // 得指针偏移量，亦为字符串长度
    if (n <= 0)
        return -1;
    int res = 0;
    for (ptemp1 = str; *ptemp1 != '\0'; ++ptemp1)
        res += pow(36,--n) * chartoint(*ptemp1);
    return res;
}
versioninfo versioncal(const char* str)
{
    const char* ptemp1 = str;
    const char* ptemp2 = str;
    int n = 0;
    while (*ptemp2 != '\0')
    {
        for (ptemp1= ptemp2; chartoint(*ptemp1) < 0; ++ptemp1);
        for (ptemp2 = ptemp1; chartoint(*ptemp2) >= 0; ++ptemp2);

        ++n;
    }
    int* pint = nullptr;
    if (n > 0)
        pint = (int*)malloc(sizeof(int)*n);
    n = 0;
    ptemp1 = str;
    ptemp2 = str;
    while (*ptemp2 != '\0')
    {
        for (ptemp1 = ptemp2; chartoint(*ptemp1) < 0; ++ptemp1);
        for (ptemp2 = ptemp1; chartoint(*ptemp2) >= 0; ++ptemp2);
        int len = ptemp2 - ptemp1;
        char* ptemp3 = (char*)malloc(sizeof(char)*(len + 1));
        for (int i = 0; i < len; i++)
            ptemp3[i] = ptemp1[i];
        ptemp3[len] = '\0';
        pint[n++] = stringtoint(ptemp3);
        free(ptemp3);
    }
    return { n,pint };
}
int versioncmp(const char* str1, const char* str2)
{
    versioninfo cal1 = versioncal(str1);
    versioninfo cal2 = versioncal(str2);
    if (cal1.n != cal2.n)
        return -1;
    int num = cal1.n;
    for (int i = 0; i < num; i++)
    {
        if (cal1.pinfo[i] > cal2.pinfo[i])
        {
            free(cal1.pinfo);
            free(cal2.pinfo);
            return 0;
        }
        else if (cal1.pinfo[i] < cal2.pinfo[i])
        {
            free(cal1.pinfo);
            free(cal2.pinfo);
            return 1;
        }
        else
            continue;
    }
    free(cal1.pinfo);
    free(cal2.pinfo);
    return 2;
}
int main()
{
    const char* str1 = "51 .11.12A";
    const char* str2 = "111. 91 .12a";
    int res = versioncmp(str1, str2);
    switch (res)
    {
    case -1:
        std::cout << "格式不同，无法比较" << std::endl;
        break;
    case 0:
        std::cout << "版本1较新" << std::endl;
        break;
    case 1:
        std::cout << "版本2较新" << std::endl;
        break;
    case 2:
        std::cout << "版本相同" << std::endl;
        break;
    }
    return 0;
}
