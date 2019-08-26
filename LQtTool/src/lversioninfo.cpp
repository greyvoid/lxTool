#include "lversioninfo.h"

LVersionInfo::LVersionInfo()
{

}

LVersionInfo::~LVersionInfo()
{

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


