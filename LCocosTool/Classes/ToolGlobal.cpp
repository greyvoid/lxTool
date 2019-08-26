#include "ToolGlobal.h"
#include "QR_Encode.h"
using namespace cocos2d;


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
// 利用Windows的库 但有的不行比如"福宝"， 可能是gbk有而不gb2312没有
/*
std::string gb23122utf8(const char* gb2312)
{
std::string strRet;
int len = MultiByteToWideChar(0, 0, gb2312, -1, NULL, 0);
wchar_t* wstr = new wchar_t[len + 1];
memset(wstr, 0, len + 1);
MultiByteToWideChar(0, 0, gb2312, -1, wstr, len);
len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
char* str = new char[len + 1];
memset(str, 0, len + 1);
WideCharToMultiByte(65001, 0, wstr, -1, str, len, NULL, NULL);
if (wstr) delete[] wstr;
if (str) delete[] str;
strRet = str;
return strRet;
}
*/
#endif 

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)  
#include "iconv.h"
#endif  

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
#include "win32-specific\icon\include\iconv.h"  
#endif  

int code_convert(const char *from_charset, const char *to_charset, const char *inbuf, size_t inlen, char *outbuf, size_t outlen)
{
	iconv_t cd;
	const char *temp = inbuf;
	const char **pin = &temp;
	char  **pout = &outbuf;
	memset(outbuf, 0, outlen);
	cd = iconv_open(to_charset, from_charset);
	if (cd == 0) return -1;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	if (iconv(cd, pin, &inlen, pout, &outlen) == -1) return -1;
#else
	if (iconv(cd, (char **)pin, &inlen, pout, &outlen) == -1) return -1;
#endif
	iconv_close(cd);
	return 0;
}

std::string u2a(const char *inbuf)
{
	size_t inlen = strlen(inbuf);
	char * outbuf = new char[inlen * 2 + 2];
	std::string strRet;
	if (code_convert("utf-8", "gb2312", inbuf, inlen, outbuf, inlen * 2 + 2) == 0)
	{
		strRet = outbuf;
	}
	delete[] outbuf;
	return strRet;
}

std::string gb23122utf8(const char *inbuf)
{
	size_t inlen = strlen(inbuf);
	char * outbuf = new char[inlen * 2 + 2];
	std::string strRet;
	if (code_convert("gb2312", "utf-8", inbuf, inlen, outbuf, inlen * 2 + 2) == 0)
	{
		strRet = outbuf;
	}
	delete[] outbuf;
	return strRet;
}


bool IsTextUTF8(const char* str, int length)
{
	int i;
	int nBytes = 0;//UFT8可用1-6个字节编码,ASCII用一个字节  
	char chr;
	bool bAllAscii = true; //如果全部都是ASCII, 说明不是UTF-8  
	for (i = 0; i < length; i++)
	{
		chr = *(str + i);
		if ((chr & 0x80) != 0) // 判断是否ASCII编码,如果不是,说明有可能是UTF-8,ASCII用7位编码,但用一个字节存,最高位标记为0,o0xxxxxxx  
			bAllAscii = false;
		if (nBytes == 0) //如果不是ASCII码,应该是多字节符,计算字节数  
		{
			if (chr >= 0x80)
			{
				if (chr >= 0xFC && chr <= 0xFD)
					nBytes = 6;
				else if (chr >= 0xF8)
					nBytes = 5;
				else if (chr >= 0xF0)
					nBytes = 4;
				else if (chr >= 0xE0)
					nBytes = 3;
				else if (chr >= 0xC0)
					nBytes = 2;
				else
				{
					return false;
				}
				nBytes--;
			}
		}
		else //多字节符的非首字节,应为 10xxxxxx  
		{
			if ((chr & 0xC0) != 0x80)
			{
				return false;
			}
			nBytes--;
		}
	}
	if (nBytes > 0) //违返规则  
	{
		return false;
	}
	if (bAllAscii) //如果全部都是ASCII, 说明不是UTF-8  
	{
		return false;
	}
	return true;
}


void WStrToUTF8(std::string& dest, const std::wstring& src)
{
	dest.clear();
	for (size_t i = 0; i < src.size(); i++){
		wchar_t w = src[i];
		if (w <= 0x7f){
			dest.push_back((char)w);
		}
		else if (w <= 0x7ff){
			dest.push_back(0xc0 | ((w >> 6) & 0x1f));
			dest.push_back(0x80 | (w & 0x3f));
		}
		else if (w <= 0xffff){
			dest.push_back(0xe0 | ((w >> 12) & 0x0f));
			dest.push_back(0x80 | ((w >> 6) & 0x3f));
			dest.push_back(0x80 | (w & 0x3f));
		}
		else if (sizeof(wchar_t) > 2 && w <= 0x10ffff){
			dest.push_back(0xf0 | ((w >> 18) & 0x07)); // wchar_t 4-bytes situation
			dest.push_back(0x80 | ((w >> 12) & 0x3f));
			dest.push_back(0x80 | ((w >> 6) & 0x3f));
			dest.push_back(0x80 | (w & 0x3f));
		}
		else{
			dest.push_back('?');
		}
	}
}

std::string FontToUTF8(const std::wstring& str)
{
	std:: string result;
	WStrToUTF8(result, str);
	return result;
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
#endif  
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)  
//const char *gb23122utf8(const char * gb2312)
//{
//	return gb2312;
//}
//#endif 

/*
#include <dlfcn.h>
void(*ucnv_convert)(const char *, const char *, char *, int32_t, const char *, int32_t, int32_t*) = 0;
bool openIcuuc()
{
void* libFile = dlopen(/ system / lib / libicuuc.so, RTLD_LAZY);
if (libFile)
{
ucnv_convert = (void(*)(const char *, const char *, char *, int32_t, const char *, int32_t, int32_t*))dlsym(libFile, ucnv_convert_3_8);

int index = 0;
char fun_name[64];
while (ucnv_convert == NULL)
{
sprintf(fun_name, ucnv_convert_4%d, index++);
ucnv_convert = (void(*)(const char *, const char *, char *, int32_t, const char *, int32_t, int32_t*))dlsym(libFile, fun_name);
if (ucnv_convert)
return true;
if (++index > 11)
break;
}
dlclose(libFile);
}
return false;
}

const char* gb23122utf8(const char * gb2312)
{
if (ucnv_convert == NULL)
{
openIcuuc();
}
if (ucnv_convert)
{
int err_code = 0;
int len = strlen(gb2312);
char* str = new char[len * 2 + 10];
memset(str, 0, len * 2 + 10);
ucnv_convert(utf - 8, gb2312, str, len * 2 + 10, gb2312, len, &err_code);
if (err_code == 0)
{
return str;
}
}
char test[256] = gb23122utf8 error;
char* str = new char[30];
strcpy(str, test);
return str;
}
*/


void showQr(char* strContent, Node* parentNode)
{
	CQR_Encode m_QREncode;
	bool bRet = m_QREncode.EncodeData(0, 0, 1, -1, strContent);

	if (bRet)
	{
		int nSize = 5;  // 定义好像素点的大小
		int originalSize = m_QREncode.m_nSymbleSize + (QR_MARGIN * 2);
		DrawNode *pQRNode = DrawNode::create();

		Point pt[6];
		Color4F color;

		// 先绘制一下地板
		pt[0] = ccp(0, 0);
		pt[1] = ccp((m_QREncode.m_nSymbleSize + QR_MARGIN * 2)*nSize, (m_QREncode.m_nSymbleSize + QR_MARGIN * 2)*nSize);
		pt[2] = ccp((m_QREncode.m_nSymbleSize + QR_MARGIN * 2)*nSize, 0);
		pt[3] = pt[0];
		pt[4] = ccp(0, (m_QREncode.m_nSymbleSize + QR_MARGIN * 2)*nSize);
		pt[5] = pt[1];
		color = ccc4f(1, 1, 1, 1);
		pQRNode->drawPolygon(pt, 6, color, 0, color);
		// 绘制里面的黑白点
		for (int i = 0; i < m_QREncode.m_nSymbleSize; ++i)
		{
			for (int j = 0; j < m_QREncode.m_nSymbleSize; ++j)
			{
				pt[0] = ccp((i + QR_MARGIN)*nSize, (j + QR_MARGIN)*nSize);
				pt[1] = ccp(((i + QR_MARGIN) + 1)*nSize, ((j + QR_MARGIN) + 1)*nSize);
				pt[2] = ccp(((i + QR_MARGIN) + 1)*nSize, ((j + QR_MARGIN) + 0)*nSize);
				pt[3] = pt[0];
				pt[4] = ccp(((i + QR_MARGIN) + 0)*nSize, ((j + QR_MARGIN) + 1)*nSize);
				pt[5] = pt[1];
				if (m_QREncode.m_byModuleData[i][j] == 1)
				{
					color = ccc4f(0, 0, 0, 1);
				}
				else
				{
					color = ccc4f(1, 1, 1, 1);
				}
				pQRNode->drawPolygon(pt, 6, color, 0, color);
			}
		}
		Size parentSize = parentNode->getContentSize();
		pQRNode->setPosition(ccp((parentSize.width - nSize*m_QREncode.m_nSymbleSize) / 2, parentSize.height - (parentSize.height - nSize*m_QREncode.m_nSymbleSize) / 2));
		pQRNode->setScaleY(-1);
		parentNode->addChild(pQRNode);
	}
}

std::string getCurTimeHMS()
{
	unsigned long long timestamp = time(NULL);
	struct tm *ptm = localtime((time_t*)&timestamp);
	char cur_time[32];
	sprintf(cur_time, "%02d:%02d:%02d", ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
	return cur_time;
}

std::string intToHMS(int sec)
{
	int h = 0;
	int m = 0;
	int s = 0;

	if (sec > 60 * 60 * 24)
	{
		h = 24;
	}
	else
	{
		s = sec % 60;
		int min = sec / 60;
		m = min % 60;
		h = min / 60;
	}

	char totaltime[32];
	sprintf(totaltime, "%02d:%02d:%02d", h, m, s);
	return totaltime;
}

bool isFileExist(const char* pstrFileName)
{
	bool bIsExist = false;
	if (NULL == pstrFileName) return bIsExist;

	std::string strFilePath = FileUtils::getInstance()->getWritablePath();
	strFilePath.append(pstrFileName);
	FILE *pFp = fopen(strFilePath.c_str(), "r");
	if (pFp)
	{
		fclose(pFp);
		bIsExist = true;
	}

	return bIsExist;
}
