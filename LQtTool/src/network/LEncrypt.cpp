#include "LEncrypt.h"
#include <string.h>

LEncrypt::LEncrypt()
{
}


LEncrypt::~LEncrypt()
{
}


void Makecode(char *pstr, int *pkey);
void Cutecode(char *pstr, int *pkey);

//单个字符异或运算
char MakecodeChar(char c, int key){
	return c = c^key;
}
//单个字符解密
char CutcodeChar(char c, int key){
	return c^key;
}




//加密
void Makecode(char *pstr, int *pkey)
{
	int len = strlen(pstr);//获取长度
	for (int i = 0; i < len; i++)
		*(pstr + i) = MakecodeChar(*(pstr + i), pkey[i % 5]);
}


//解密
void Cutecode(char *pstr, int *pkey)
{
	int len = strlen(pstr);
	for (int i = 0; i < len; i++)
		*(pstr + i) = CutcodeChar(*(pstr + i), pkey[i % 5]);
}