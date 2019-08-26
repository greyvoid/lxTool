#ifndef __TOOL_GLOBAL__
#define __TOOL_GLOBAL__
#include "cocos2d.h"

using namespace cocos2d;

std::string gb23122utf8(const char* gb2312);
std::string FontToUTF8(const std::wstring& str);
void showQr(char* strContent, Node* parentNode);
std::string getCurTimeHMS();
std::string intToHMS(int sec);
bool isFileExist(const char* pstrFileName);

//Cocos2d专有的转换方法
//int index = 100; std::string str = Value(index).asString(); int index2 = Value(str).asInt();


#endif //__TOOL_GLOBAL__