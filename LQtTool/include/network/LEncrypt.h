#pragma once



class LEncrypt
{
public:
	LEncrypt();
	~LEncrypt();
};

void Makecode(char *pstr, int *pkey);
void Cutecode(char *pstr, int *pkey);

//void encrypt(); // 加密
//void decrypt(); // 解密
