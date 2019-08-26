﻿#ifndef WIN32
#include "regex.h"
#else
#include <regex>
#endif // !WIN32

#pragma warning (disable:4996)

#include <assert.h>
#include "gfunc.h"

std::string cvtIntToStr(const int n)
{
	char ch[32];
	sprintf(ch, "%d", n);

	std::string szResult = ch;
	return szResult;
}

int convertInt(char *str, int sign)
{
	int total, j;
	total = 0;
	j = 0;
	int strLength = strlen(str);
	for (int i = 0; i < strLength; i++)
	{
		int iAScill = str[i];
		if (iAScill >= '0' && iAScill <= '9')
		{
			total = total*sign + iAScill - '0';
		}
		if ((iAScill >= 'A' && iAScill <= 'Z'))
		{
			total = total*sign + iAScill - 'A' + 10;
		}
		if (iAScill >= 'a' && iAScill <= 'z')
		{
			total = total*sign + iAScill - 'a' + 10;
		}
	}
	return total;
}

int wstrlen(const wchar_t *pStr)
{
	if (!pStr) return 0;
	const wchar_t *pOffset = pStr;
	while (*pOffset++);
	return (pOffset - pStr - 1);
}

// 生成一个随机数
double random(double start, double end)
{
	return start + (end - start)*rand() / (RAND_MAX + 1.0);
}

/***********过滤字母数字，128-256******/
char * print16(char *str)
{
	int strLength = strlen(str);
	char buf16[16] = { 0 };
	char *str16;
	int j = 0;

	for (int i = 0; i < strLength; i++)
	{
		if ((str[i] >= 48 && str[i] <= 57) || (str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122))
		{
			buf16[j] = str[i];
			j++;
		}
	}
	str16 = new char[strlen(buf16) + 1];
	strcpy(str16, buf16);
	return str16;

}

/************************************************************************/
/*把十六进制字符串ptr 转换成十进制数                                     */
/************************************************************************/
//function 1
int ChangeNum1(char *str, int length)
{
	char  revstr[16] = { 0 };  //根据十六进制字符串的长度，这里注意数组不要越界
	int   num[16] = { 0 };
	int   count = 1;
	int   iResult = 0;
	strcpy(revstr, str);
	for (int i = length - 1; i >= 0; i--)
	{
		if ((revstr[i] >= '0') && (revstr[i] <= '9'))
			num[i] = revstr[i] - 48;//字符0的ASCII值为48
		else if ((revstr[i] >= 'a') && (revstr[i] <= 'f'))
			num[i] = revstr[i] - 'a' + 10;
		else if ((revstr[i] >= 'A') && (revstr[i] <= 'F'))
			num[i] = revstr[i] - 'A' + 10;
		else
			num[i] = 0;
		iResult = iResult + num[i] * count;
		count = count * 16;//十六进制(如果是八进制就在这里乘以8)    
	}
	return iResult;

}

// 字符串转换方法
void CTools::WStrToUTF8(string& dest, const wstring& src){
	dest.clear();
	for (size_t i = 0; i < src.size(); i++){
		wchar_t w = src[i];
		if (w <= 0x7f){
			dest.push_back((char)w);
			// log("CTools::WStrToUTF8:%d",1);
		}
		else if (w <= 0x7ff){
			dest.push_back(0xc0 | ((w >> 6)& 0x1f));
			dest.push_back(0x80| (w & 0x3f));
			// log("CTools::WStrToUTF8:%d",2);
		}else if (w <= 0xffff){
			dest.push_back(0xe0 | ((w >> 12)& 0x0f));
			dest.push_back(0x80| ((w >> 6) & 0x3f));
			dest.push_back(0x80| (w & 0x3f));
			// log("CTools::WStrToUTF8:%d",3);
		}else if (sizeof(wchar_t) > 2 && w <= 0x10ffff){
			//dest.push_back(0xf0 | ((w >> 18)& 0x07)); // wchar_t 4-bytes situation
			//dest.push_back(0x80| ((w >> 12) & 0x3f));
			//dest.push_back(0x80| ((w >> 6) & 0x3f));
			//dest.push_back(0x80| (w & 0x3f));
			//log("CTools::WStrToUTF8:%d",4);
		}else
			dest.push_back('?');
	}
}

string CTools::WStrToUTF8(const wstring& str){
	string result;
	WStrToUTF8(result, str);
	return result;
}



void CTools::UnicodeToUTF8(wchar_t* WStr,unsigned short wStrlen,const char *Utf8Char){

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	/*int  nLen=(lstrlen(WStr)+1) << 1;  
	memset(Utf8Char,0,sizeof(char)*wStrlen*3);
	WideCharToMultiByte(CP_UTF8,  0,  WStr,  wStrlen,  Utf8Char,  wStrlen*3,  NULL,  NULL);  */
//#else

	assert(WStr != NULL || Utf8Char !=NULL);
	string tempEncoderText;

	//转换汉字
	for (int i = 0; i <wStrlen; i++) {
		//结束符
		if (WStr[i] == 0)
		{
			break;
		}
		//数字与字母
		if (WStr[i] <= 0x7f){
			tempEncoderText.push_back((char)WStr[i]);
			continue;
		}
		//汉字
		if (WStr[i] <= 0x7ff){
			tempEncoderText.push_back(0xc0 | ((WStr[i] >> 6)& 0x1f));
			tempEncoderText.push_back(0x80| (WStr[i] & 0x3f));
			continue;
		}
		//汉字
		if (WStr[i] <= 0xffff){
			tempEncoderText.push_back(0xe0 | ((WStr[i] >> 12)& 0x0f));
			tempEncoderText.push_back(0x80 | ((WStr[i] >> 6)& 0x3f));
			tempEncoderText.push_back(0x80 | ((WStr[i])& 0x3f));
			continue;
		}		
	}	
	
	//返回参数
	memset((void *)Utf8Char,0,tempEncoderText.length()+1);
	memcpy((void *)Utf8Char,(void *)(tempEncoderText.c_str()),tempEncoderText.length());
	//清除数据
	tempEncoderText.clear();

	return;

//#endif
}

//utf_8转换为unicode
void CTools::UTF8ToUnicode(const char* _nickName, int wdatalength,wchar_t* &pUnicodeStr){

	pUnicodeStr=new wchar_t[(wdatalength+1)];
	memset(pUnicodeStr, 0, sizeof(wchar_t)*(wdatalength+1));
	int _CharCount =0;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

	for (int i = 0; i< wdatalength && _CharCount< wdatalength; i++) {


		if (_nickName[_CharCount]>=0x00 && _nickName[_CharCount]<=0x7F ) //0x00-0x7F
		{
			pUnicodeStr[i] = 0;
			pUnicodeStr[i] = (unsigned char)_nickName[_CharCount];
			_CharCount +=1;
			// log("_nickName[_CharCount]>=0x00 && _nickName[_CharCount]<=0x7F" );
			continue;
		}
		//0x0080 - 0x7FF  => 110x xxxx 10xx xxxx
		if((unsigned short)(_nickName[_CharCount])>=0x0080 && (unsigned short)(_nickName[_CharCount])<=0x07FF)
		{
			pUnicodeStr[i] = (_nickName[0+_CharCount] & 0x1F) << 6;		
			pUnicodeStr[i] |= (_nickName[1+_CharCount] & 0x3F);
			_CharCount += 2;
			// log("_nickName[_CharCount])>=0x0080 && (unsigned short)(_nickName[_CharCount])<=0x07FF %d ", wdatalength);
			continue;
		} 

		//0x0800 -0x07FF => 1110 xxxx 10xx xxxx 10xx xxxx
		if((unsigned short)(_nickName[_CharCount])>=0x0800)
		{
			pUnicodeStr[i] = (_nickName[0+_CharCount] & 0x0F) << 12;		
			pUnicodeStr[i] |= (_nickName[1+_CharCount] & 0x3F) << 6;
			pUnicodeStr[i] |= (_nickName[2+_CharCount] & 0x3F);
			_CharCount +=3;
			// log("_nickName[_CharCount])>=0x0800 %d ", wdatalength);
			continue;
		}
	}    
#else

	for (int i = 0; i< wdatalength && _CharCount< wdatalength; i++) {

		if (_nickName[_CharCount]>=0x00 && _nickName[_CharCount]<=0x7F ) //0x00-0x7F
		{
			pUnicodeStr[i] = 0;
			pUnicodeStr[i] = (unsigned char)_nickName[_CharCount];
			_CharCount +=1;
			// log("_nickName[_CharCount]>=0x00 && _nickName[_CharCount]<=0x7F" );
			continue;
		}

		//0x0080 - 0x7FF  => 110x xxxx 10xx xxxx
		if(*(unsigned short*)(&_nickName[_CharCount+1])>=0x0080 && *(unsigned short*)(&_nickName[_CharCount+1])<=0x07FF)
		{
			pUnicodeStr[i] = (_nickName[0+_CharCount] & 0x1F) << 6;		
			pUnicodeStr[i] |= (_nickName[1+_CharCount] & 0x3F);
			_CharCount += 2;
			// log("_nickName[_CharCount])>=0x0080 && (unsigned short)(_nickName[_CharCount])<=0x07FF %d ", wdatalength);
			continue;
		} 

		//0x0800 -0x07FF => 1110 xxxx 10xx xxxx 10xx xxxx
		if(*(unsigned short*)(&_nickName[_CharCount+1])>=0x0800)
		{
			pUnicodeStr[i] = (_nickName[0+_CharCount] & 0x0F) << 12;		
			pUnicodeStr[i] |= (_nickName[1+_CharCount] & 0x3F) << 6;
			pUnicodeStr[i] |= (_nickName[2+_CharCount] & 0x3F);
			_CharCount +=3;
			// log("_nickName[_CharCount])>=0x0800 %d ", wdatalength);
			continue;
		}	

	}    
#endif
}




std::string CTools::UnicodeToUTF8(wchar_t *src)
{
	assert(src);

	string dest;
	int wStrlen = wstrlen(src);
	for (int i = 0; i < wStrlen; ++i)
	{
		if (src[i] == 0)
		{
			break;
		}

		if (src[i] <= 0x7f)
		{
			dest.push_back((char)src[i]);
			continue;
		}

		if (src[i] <= 0x7ff)
		{
			dest.push_back(0xc0 | ((src[i] >> 6) & 0x1f));
			dest.push_back(0x80 | (src[i] & 0x3f));
			continue;
		}

		if (src[i] <= 0xffff)
		{
			dest.push_back(0xe0 | ((src[i] >> 12) & 0x0f));
			dest.push_back(0x80 | ((src[i] >> 6) & 0x3f));
			dest.push_back(0x80 | ((src[i]) & 0x3f));
			continue;
		}
	}

	return std::move(dest);
}

std::shared_ptr<wchar_t> CTools::UTF8ToUnicode(const std::string &src)
{
	int charCount = 0;
	int len = src.size();
	std::shared_ptr<wchar_t> dest(new wchar_t[len + 1], std::default_delete<wchar_t[]>());
	wchar_t *pResources = dest.get();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	for (int i = 0; i < len && charCount < len; ++i)
	{
		if (src[charCount] >= 0x00 && src[charCount] <= 0x7F)
		{
			pResources[i] = (unsigned char)src[charCount++];
		}
		else if ((unsigned short)(src[charCount]) >= 0x0080 && (unsigned short)(src[charCount]) <= 0x07FF)
		{
			pResources[i] = (src[0 + charCount] & 0x1F) << 6;
			pResources[i] |= (src[1 + charCount] & 0x3F);
			charCount += 2;
		}
		else if ((unsigned short)(src[charCount]) >= 0x0800)
		{
			pResources[i] = (src[0 + charCount] & 0x0F) << 12;
			pResources[i] |= (src[1 + charCount] & 0x3F) << 6;
			pResources[i] |= (src[2 + charCount] & 0x3F);
			charCount += 3;
		}
	}    
#else
	for (int i = 0; i < len && charCount < len; ++i)
	{
		if (src[charCount] >= 0x00 && src[charCount] <= 0x7F )
		{
			pResources[i] = (unsigned char)src[charCount++];
		}
		else if (*(unsigned short*)(&src[charCount+1]) >= 0x0080 && *(unsigned short*)(&src[charCount+1]) <= 0x07FF)
		{
			pResources[i] = (src[0 + charCount] & 0x1F) << 6;		
			pResources[i] |= (src[1 + charCount] & 0x3F);
			charCount += 2;
		} 
		else if (*(unsigned short*)(&src[charCount+1])>=0x0800)
		{
			pResources[i] = (src[0+charCount] & 0x0F) << 12;		
			pResources[i] |= (src[1+charCount] & 0x3F) << 6;
			pResources[i] |= (src[2+charCount] & 0x3F);
			charCount +=3;
		}
	}
#endif

	return dest;
}

std::string CNExcerpt(const wchar_t *src, unsigned int lenght)
{
	assert(src && lenght);

	std::string des;
	unsigned int currentLenght = 0;
	unsigned int wcharLen = wstrlen(src);
	for (unsigned int i = 0; i < wcharLen; i++)
	{
		if (src[i] == 0)
		{
			break;
		}
		else if (src[i] <= 0x7f)
		{
			currentLenght += 1;
			if (currentLenght <= lenght)
			{
				if (src[i] != ' ')
				{
					des.push_back((char)src[i]);
				}
			}
			else
			{
				des.append("...");
				break;
			}
		}
		else if (src[i] <= 0x7ff)
		{
			currentLenght += 2;
			if (currentLenght <= lenght)
			{
				des.push_back(0xc0 | ((src[i] >> 6) & 0x1f));
				des.push_back(0x80 | (src[i] & 0x3f));
			}
			else
			{
				des.append("...");
				break;
			}
		}
		else if (src[i] <= 0xffff)
		{
			currentLenght += 3;
			if (currentLenght <= lenght)
			{
				des.push_back(0xe0 | ((src[i] >> 12) & 0x0f));
				des.push_back(0x80 | ((src[i] >> 6) & 0x3f));
				des.push_back(0x80 | ((src[i]) & 0x3f));
			}
			else
			{
				des.append("...");
				break;
			}
		}
	}
	return des;
}





bool isdigit(const std::string &src)
{
	if (src.empty()) return false;

	for (int i = 0; i < (int)src.length(); i++)
	{
		char ch = src[i];
		if (ch < '0' || ch > '9')
			return false;
	}

	return true;
}

bool isdigitW(const std::wstring &src)
{
	if (src.empty()) return false;

	for (int i = 0; i < (int)src.length(); i++)
	{
		char ch = src[i];
		if (ch < '0' || ch > '9')
			return false;
	}

	return true;
}

/*
1. 什么是大端,什么是小端:

所谓的大端模式，是指数据的低位保存在内存的高地址中，而数据的高位，保存在内存的低地址中；

所谓的小端模式，是指数据的低位保存在内存的低地址中，而数据的高位保存在内存的高地址中。

2.为什么会有大小端:

为什么会有大小端模式之分呢？这是因为在计算机系统中，我们是以字节为单位的，每个地址单元都对应着一个字节，一个字节为8bit。但是在C语言中除了8bit的char之外，
还有16bit的short型，32bit的long型（要看具体的编译器），另外，对于位数大于8位的处理器，例如16位或者32位的处理器，由于寄存器宽度大于一个字节，
那么必然存在着一个如果将多个字节安排的问题。因此就导致了大端存储模式和小端存储模式。例如一个16bit的short型x，在内存中的地址为0x0010，x的值为0x1122，
那么0x11为高字节，0x22为低字节。对于大端模式，就将0x11放在低地址中，即0x0010中，0x22放在高地址中，即0x0011中。小端模式，刚好相反。
我们常用的X86结构是小端模式，而KEIL C51则为大端模式。很多的ARM，DSP都为小端模式。有些ARM处理器还可以由硬件来选择是大端模式还是小端模式。
*/

/*
ntel的80x86系列芯片是唯一还在坚持使用小端的芯片，ARM芯片默认采用小端，但可以切换为大端；而MIPS等芯片要么采用全部大端的方式储存，
要么提供选项支持大端——可以在大小端之间切换。另外，对于大小端的处理也和编译器的实现有关，
在C语言中，默认是小端（但在一些对于单片机的实现中却是基于大端，比如Keil 51C），Java是平台无关的，默认是大端。在网络上传输数据普遍采用的都是大端
*/

bool isBigDebian()
{
	short int x;
	char x0, x1;
	x = 0x1122;
	x0 = ((char *)&x)[0];  //低地址单元
	x1 = ((char *)&x)[1];  //高地址单元
	printf("x0=0x%x,x1=0x%x", x0, x1);// 若x0=0x11,则是大端; 若x0=0x22,则是小端......
	if (x0 == 0x11)
	{
		return true;
	}
	return false;

	/*
	int val = 1;
	char *ret = (char *)&val;
	if (*ret == 1)
	printf("小端存储");
	else
	printf("大端存储");
	return 0;
	*/

	/*
	union UN
	{
	int a;
	char c;
	};
	int main()
	{
	union UN un;
	un.a = 1;
	if (un.c == 1)
	printf("小端存储");
	else
	printf("大端存储");
	return 0;
	}
	*/

	/*
	union chufa{
	int n; //n中存放要进行分离高低字节的数据
	char a[2]; //在keil c中一个整形占两个字节，char占一个字节，所以n与数组a占的字节数相同
	}test;
	test.n=65535-200; //进行完这句后就一切ok了，下面通过访问test中数组a的数据来取出高低字节的数据
	TH1=test.a[0];
	*/
}


/*******************************************
 *	打印十六进制数据
 *	@buff: 存放十六进制数据的缓存
 *  @buff_len: 缓存大小
********************************************/
void public_print_hex(unsigned char *buff, unsigned int buff_len)
{
    unsigned int index = 0;
    unsigned char tmp = 0;

    printf("\nbuff_len is %d, buff is\n", buff_len);
    for (index=0; index<buff_len; index++)
    {
        // 高4位
        tmp = buff[index];
        tmp &= 0xf0;
        tmp >>= 4;
        printf(" %x", tmp);

        // 低4位
        tmp = buff[index];
        tmp &= 0x0f;
        printf("%x", tmp);
    }
    printf("\nbuff over\n");
}
