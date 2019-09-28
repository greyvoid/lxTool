#ifndef __GFUNC_H__
#define __GFUNC_H__

#include <string>
#include <memory> // shared_ptr 

#ifdef WIN32
#include <process.h>
#endif

using namespace std;
namespace lx
{

}

std::string cvtIntToStr(const int n);
int convertInt(char *str, int sign);
std::string cvtScoreToStr(const __int64 l);

//int转string
string intToString(int n){

    try{
        std::stringstream newstr;
        newstr << n;
        return newstr.str();
    }
    catch (...){
        return "";
    }

}
//string转int
//int stringToInt(string  instringn){
//    try{
//        int index = _ttoi(instringn.c_str());
//        return index;
//    }
//    catch (...){
//        return -1;
//    }

//}

//tchar to string
std::string CNExcerpt(const wchar_t *src, unsigned int lenght);
//判断大端小端
bool isBigDebian();

char *mystrcat(char *dst,const char *src) //用自己的方式实现strcat函数功能
{
char *p=dst;  //下面的操作会改变目的指针指向，先定义一个指针记录dst
while(*p!='\0')p++;
while(*src != '\0')*p++=*src++;
 *p='\0';
return dst;

//
}

std::string cddd(char aSrc[])
{
    char buf[256]={0};
    int ret = 0;
    int m_aConnCounters[20] = { 1, 2, 5, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 6, 5, 0, 0, 0, 0, 1 };
    for(int i = 0; i < 20; ++i)
    {
        //ret += sprintf(buf + ret, " %d", m_aConnCounters[i]);
        // 连接数组元素
        ret += sprintf(buf + ret, "%d", m_aConnCounters[i]);
    }
    return buf; // result 12511111101116500001
}

/**
* wchar_t 长度
*/
static int wstrlen(const wchar_t *pStr);

double random(double start, double end);

//判断
bool isdigit(const std::string &src);
bool isdigitW(const std::wstring &src);

//时间相关
long getCurDayCount();
__int64 getCurHourCount();

// 打印十六进制数据
void public_print_hex(unsigned char *buff, unsigned int buff_len);

// 工具类
class CTools
{
public:


    // wstring 转成 utf-8 的 string
    static string WStrToUTF8(const wstring &str);

    // Unicode 转换为 UTF-8
    static void UnicodeToUTF8(wchar_t *WStr, unsigned short wStrlen, const char *Utf8Char);
    static std::string UnicodeToUTF8(wchar_t *pWStr);

    // UTF-8 转换位 Unicode
    static void UTF8ToUnicode(const char*_nickName, int wdatalength, wchar_t *&pUnicodeStr);
    static std::shared_ptr<wchar_t> UTF8ToUnicode(const std::string &src);






private:
    // 字符串转换方法
    static void WStrToUTF8(string& dest, const wstring& src);
};

/**
* 说明：去除文件后缀 只留文件名
* 参数：文件名
* 返回：纯文件名称不带后缀
*/
string getFileName(string fileName){
    int pos = fileName.rfind(".");
    if (pos > 0)
        return fileName.substr(0, pos);
    else
        return fileName;
}

#endif //__GFUNC_H__
