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
//tchar to string
std::string CNExcerpt(const wchar_t *src, unsigned int lenght);
//判断大端小端
bool isBigDebian();

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

#endif //__GFUNC_H__
