#ifndef __LSTD_FUNC_H__
#define __LSTD_FUNC_H__

#include <string>
#include <memory> // shared_ptr 
#include <vector>
#include <fstream>

#ifdef WIN32
#include <process.h>
#endif

using namespace std;

namespace lstd {


string format(const char *pszFmt, ...);
std::string cvtIntToStr(const int n);
int convertStrToInt(char *str, int sign);
string formatBytes(double dByteNum, unsigned char unValidDigit);

//判断是否全部为数字
bool isDigit(const std::string &src);

//判断大端小端
bool isBigDebian();

//用自己的方式实现strcat函数功能
char* strcat(char *dst,const char *src);

double random(double start, double end);


///
/// \brief printArray
/// \param aSrc //eg: int m_aConnCounters[20] = { 1, 2, 5, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 6, 5, 0, 0, 0, 0, 1 };
/// \return
///
std::string printArray(char aSrc[])
{

    char buf[256]={0};
    int ret = 0;

    for(int i = 0; i < 20; ++i)
    {
        //ret += sprintf(buf + ret, " %d", m_aConnCounters[i]);
        // 连接数组元素
        ret += sprintf(buf + ret, "%d", aSrc[i]);
    }
    return buf; // result 12511111101116500001
}


/**
* 说明：去除文件后缀 只留文件名
* 参数：文件名
* 返回：纯文件名称不带后缀
*/
string getFileName(string fileName)
{
    int pos = fileName.rfind(".");
    if (pos > 0)
        return fileName.substr(0, pos);
    else
        return fileName;
}


// 打印十六进制数据
void public_print_hex(unsigned char *buff, unsigned int buff_len);


/*
* 写入文件内容 不存在则创建  覆盖写入
* 参数一：文件路径
* 参数二：文件内容
* 返回：true成功/false失败
*/
static bool saveFileData(string filePath, char* fileData)
{
    ofstream outfile(filePath, ios::out);//ios::app表示在原文件末尾追加
    outfile.write(fileData, strlen(fileData));
    outfile.close();
    return true;
}

/**
* 说明：字符串替换（不循环重复替换）
* 参数：1总字符串 2要替换的字符 3替换成的字符
* 返回：替换后的字符串
*/
string& replace_all_distinct(string& str, const string& old_value, const string& new_value)
{
    for (string::size_type pos(0); pos != string::npos; pos += new_value.length()){
        if ((pos = str.find(old_value, pos)) != string::npos)
            str.replace(pos, old_value.length(), new_value);
        else  break;
    }
    return   str;
}

/**
* 说明：字符串替换（循环重复替换）
* 参数：1总字符串 2要替换的字符 3替换成的字符
* 返回：替换后的字符串
*/
string& replace_all(string& str, const string& old_value, const string& new_value)
{
    while (true) {
        string::size_type pos(0);
        if ((pos = str.find(old_value)) != string::npos)
            str.replace(pos, old_value.length(), new_value);
        else break;
    }
    return str;
}


/**
* 说明：判断是否包含子串（A中是否包含B）
* 参数：A总字符串  B子串
* 返回：true包含 /false不包含
*/
bool checkIsStr(string strA, string strB){
    string::size_type idx = strA.find(strB);
    if (idx != string::npos)
    {
        return true;
    }
    else {
        return false;
    }
}
/**
* 说明：截取字符串（从A到B中间的字符串）
* 参数：all总字符串  a开始字符串  b结束字符串
* 返回：处理后的字符串
*/
string subCString(std::string all, string a, string b){
    int ix = all.find(a);
    int iy = all.find(b);
    ix += strlen(a.c_str());
    iy = iy - ix;
    all = all.substr(ix, iy);
    return all;
}
/**
* 说明：多字符串替换（不循环重复替换）
* 参数：str总字符串  old_vlaue_Arr要替换的字符（string[]类型）num要替换字符串的个数  new_value替换成的字符
* 返回：替换后的字符串
*/
string& replace_all_distinct_list(string& str, string old_vlaue_Arr[], int num, const string& new_value)
{
    for (int i = 0; i < num; i++) {
        const string& old_value = old_vlaue_Arr[i];
        for (string::size_type pos(0); pos != string::npos; pos += new_value.length()){
            if ((pos = str.find(old_value, pos)) != string::npos)
                str.replace(pos, old_value.length(), new_value);
            else  break;
        }
    }
    return   str;
}
/**
* 说明：将字符串中的html标签转义
* 参数：需要转义的字符串
* 返回：处理后的字符串
*/
string replaceHTML(string str)
{
    string strAryy[4]{ "</div>", "<em>", "</em>", "</p>"};
    string replStr = replace_all_distinct_list(str, strAryy, 4, "");
    replStr = replace_all_distinct(replStr, "&nbsp;", " ");
    replStr = replace_all_distinct(replStr, "<br />", "\r\n");
    return replStr.c_str();
}
//字符串分割函数
std::vector<std::string> split(std::string str, std::string pattern)
{
    std::string::size_type pos;
    std::vector<std::string> result;
    str += pattern;//扩展字符串以方便操作
    int size = str.size();

    for (int i = 0; i<size; i++)
    {
        pos = str.find(pattern, i);
        if (pos<size)
        {
            std::string s = str.substr(i, pos - i);
            result.push_back(s);
            i = pos + pattern.size() - 1;
        }
    }
    return result;
}




unsigned char toHex(const unsigned char &x)
{
    return x > 9 ? x - 10 + 'A' : x + '0';
}

unsigned char fromHex(const unsigned char &x)
{
    return isdigit(x) ? x - '0' : x - 'A' + 10;
}
/**
* 说明：中文转为浏览器识别的特殊编码
* 参数：带转换字符串
* 返回：处理后的字符串
*/
string  URLEncode(const char *sIn)
{
    string sOut;
    for (size_t ix = 0; ix < strlen(sIn); ix++)
    {
        unsigned char buf[4];
        memset(buf, 0, 4);
        if (isalnum((unsigned char)sIn[ix]))
        {
            buf[0] = sIn[ix];
        }
        else
        {
            buf[0] = '%';
            buf[1] = toHex((unsigned char)sIn[ix] >> 4);
            buf[2] = toHex((unsigned char)sIn[ix] % 16);
        }
        sOut += (char *)buf;
    }
    return sOut;
};
/**
* 说明：浏览器识别的特殊编码转为中文
* 参数：带转换字符串
* 返回：处理后的字符串
*/
string URLDecode(const char *sIn)
{
    string sOut;
    for (size_t ix = 0; ix < strlen(sIn); ix++)
    {
        unsigned char ch = 0;
        if (sIn[ix] == '%')
        {
            ch = (fromHex(sIn[ix + 1]) << 4);
            ch |= fromHex(sIn[ix + 2]);
            ix += 2;
        }
        else if (sIn[ix] == '+')
        {
            ch = ' ';
        }
        else
        {
            ch = sIn[ix];
        }
        sOut += (char)ch;
    }

    return sOut;

}

} // end namespace lstd


#endif //__LSTD_FUNC_H__
