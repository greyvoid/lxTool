﻿
#include "string.h"
#include "LAes.h"

///
/// \brief CLAes::CLAes 参考书籍<<密码编码学与网络安全>>
///
CLAes::CLAes()
{

}

CLAes::CLAes(unsigned char* key)
{
    // 定义了一个S盒，它是由16×16个字节组成是矩阵，包含了8位所能表示的256个数的一个置换
    // AES的S盒的原理是运用了GF(28)的乘法逆和矩阵的可逆运算来保证加密与解密过程的可逆性
	unsigned char sBox[] =
	{ /*  0    1    2    3    4    5    6    7    8    9    a    b    c    d    e    f */ 
		0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76, /*0*/  
		0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0, /*1*/
		0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15, /*2*/ 
		0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75, /*3*/ 
		0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84, /*4*/ 
		0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf, /*5*/
		0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8, /*6*/  
		0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2, /*7*/ 
		0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73, /*8*/ 
		0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb, /*9*/ 
		0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79, /*a*/
		0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08, /*b*/
		0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a, /*c*/ 
		0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e, /*d*/
		0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf, /*e*/ 
		0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16  /*f*/
	};
    // 逆S盒的构造
	unsigned char invsBox[256] = 
	{ /*  0    1    2    3    4    5    6    7    8    9    a    b    c    d    e    f  */  
		0x52,0x09,0x6a,0xd5,0x30,0x36,0xa5,0x38,0xbf,0x40,0xa3,0x9e,0x81,0xf3,0xd7,0xfb, /*0*/ 
		0x7c,0xe3,0x39,0x82,0x9b,0x2f,0xff,0x87,0x34,0x8e,0x43,0x44,0xc4,0xde,0xe9,0xcb, /*1*/
		0x54,0x7b,0x94,0x32,0xa6,0xc2,0x23,0x3d,0xee,0x4c,0x95,0x0b,0x42,0xfa,0xc3,0x4e, /*2*/ 
		0x08,0x2e,0xa1,0x66,0x28,0xd9,0x24,0xb2,0x76,0x5b,0xa2,0x49,0x6d,0x8b,0xd1,0x25, /*3*/ 
		0x72,0xf8,0xf6,0x64,0x86,0x68,0x98,0x16,0xd4,0xa4,0x5c,0xcc,0x5d,0x65,0xb6,0x92, /*4*/ 
		0x6c,0x70,0x48,0x50,0xfd,0xed,0xb9,0xda,0x5e,0x15,0x46,0x57,0xa7,0x8d,0x9d,0x84, /*5*/ 
		0x90,0xd8,0xab,0x00,0x8c,0xbc,0xd3,0x0a,0xf7,0xe4,0x58,0x05,0xb8,0xb3,0x45,0x06, /*6*/ 
		0xd0,0x2c,0x1e,0x8f,0xca,0x3f,0x0f,0x02,0xc1,0xaf,0xbd,0x03,0x01,0x13,0x8a,0x6b, /*7*/
		0x3a,0x91,0x11,0x41,0x4f,0x67,0xdc,0xea,0x97,0xf2,0xcf,0xce,0xf0,0xb4,0xe6,0x73, /*8*/ 
		0x96,0xac,0x74,0x22,0xe7,0xad,0x35,0x85,0xe2,0xf9,0x37,0xe8,0x1c,0x75,0xdf,0x6e, /*9*/
		0x47,0xf1,0x1a,0x71,0x1d,0x29,0xc5,0x89,0x6f,0xb7,0x62,0x0e,0xaa,0x18,0xbe,0x1b, /*a*/
		0xfc,0x56,0x3e,0x4b,0xc6,0xd2,0x79,0x20,0x9a,0xdb,0xc0,0xfe,0x78,0xcd,0x5a,0xf4, /*b*/ 
		0x1f,0xdd,0xa8,0x33,0x88,0x07,0xc7,0x31,0xb1,0x12,0x10,0x59,0x27,0x80,0xec,0x5f, /*c*/ 
		0x60,0x51,0x7f,0xa9,0x19,0xb5,0x4a,0x0d,0x2d,0xe5,0x7a,0x9f,0x93,0xc9,0x9c,0xef, /*d*/ 
		0xa0,0xe0,0x3b,0x4d,0xae,0x2a,0xf5,0xb0,0xc8,0xeb,0xbb,0x3c,0x83,0x53,0x99,0x61, /*e*/ 
		0x17,0x2b,0x04,0x7e,0xba,0x77,0xd6,0x26,0xe1,0x69,0x14,0x63,0x55,0x21,0x0c,0x7d  /*f*/
    };
    // 映射关系是sBox数组的sBox[0][0]的值是invsBox的行下标列下标，sBox数组的行下标列下标则存放invsBox的值
    // State中每个字节按照如下方式映射为一个新的字节：把该字节的高4位作为行值，低4位作为列值
    memcpy(m_aSbox, sBox, 256);
	memcpy(InvSbox, invsBox, 256);
	KeyExpansion(key, w);
}

CLAes::~CLAes()
{

}

//加密解密算法的输入是一个128位分组。这些分组被描述成4×4的字节方阵，这个分组被复制到state数组中，
//并在加密和解密的每一阶段都被修改。在字节方阵中，每一格都是一个字，包含了4字节。在矩阵中字是按列排序的。
/*
 *
 * S0 S4 S8  S12
 * S1 S5 S9  S13
 * S2 S6 S10 S14
 * S3 S7 S11 S15
 *
 */

unsigned char* CLAes::cipher(unsigned char* input)
{
	unsigned char state[4][4];
	int i,r,c;

//16字节依次赋值给state
	for(r=0; r<4; r++)
	{
		for(c=0; c<4 ;c++)
		{
			state[r][c] = input[c*4+r];
		}
	}

	AddRoundKey(state,w[0]);

	for(i=1; i<=10; i++)
	{
		SubBytes(state);
        shiftRows(state);
        if(i!=10)mixColumns(state);
		AddRoundKey(state,w[i]);
	}

	for(r=0; r<4; r++)
	{
		for(c=0; c<4 ;c++)
		{
			input[c*4+r] = state[r][c];
		}
	}

	return input;
}

unsigned char* CLAes::invCipher(unsigned char* input)
{
	unsigned char state[4][4];
	int i,r,c;

	for(r=0; r<4; r++)
	{
		for(c=0; c<4 ;c++)
		{
			state[r][c] = input[c*4+r];
		}
	}

	AddRoundKey(state, w[10]);
	for(i=9; i>=0; i--)
	{
		InvShiftRows(state);
		InvSubBytes(state);
		AddRoundKey(state, w[i]);
		if(i)
		{
			InvMixColumns(state);
		}
	}
	
	for(r=0; r<4; r++)
	{
		for(c=0; c<4 ;c++)
		{
			input[c*4+r] = state[r][c];
		}
	}

	return input;
}

// 加密过程
void* CLAes::cipher(void* input, int length)
{
	unsigned char* in = (unsigned char*) input;
	int i;

    // 如果length为0为字符串，则获取length的真实长度
	if(!length)
	{
        while(*(in + length++));
		in = (unsigned char*) input;
	}

    // 16字节一组分别加密
    for(i=0; i<length; i += 16)
	{
		cipher(in+i);
	}
	return input;
}

// 解密过程
void* CLAes::invCipher(void* input, int length)
{
	unsigned char* in = (unsigned char*) input;
	int i;
	for(i=0; i<length; i+=16)
	{
        invCipher(in+i);
	}
	return input;
}

// KeyExpansion（密钥扩展）
void CLAes::KeyExpansion(unsigned char* key, unsigned char w[][4][4])
{
	int i,j,r,c;
	unsigned char rc[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36};
	for(r=0; r<4; r++)
	{
		for(c=0; c<4; c++)
		{
			w[0][r][c] = key[r+c*4];
		}
	}
	for(i=1; i<=10; i++)
	{
		for(j=0; j<4; j++)
		{
			unsigned char t[4];
			for(r=0; r<4; r++)
			{
				t[r] = j ? w[i][r][j-1] : w[i-1][r][3];
			}
			if(j == 0)
			{
				unsigned char temp = t[0];
				for(r=0; r<3; r++)
				{
                    t[r] = m_aSbox[t[(r+1)%4]];
				}
                t[3] = m_aSbox[temp];
				t[0] ^= rc[i-1];
			}
			for(r=0; r<4; r++)
			{
				w[i][r][j] = w[i-1][r][j] ^ t[r];
			}
		}
	}
}

///
/// \brief CLAes::FFmul 大于不大于0x80其实指的最高位是不是1,因为小于1x80的数只要左移（乘2）就可以了,不涉及到进位,
/// 而大于或等于0x80的数,最高位是1,左移就会溢出了,而溢出后的数就不在有限域里了,为了实现进位溢出和仍然停留在有限域里的矛盾
/// 就要找个方法结果就是溢出的时候与0x1b异或,0x1b怎么来的呢,你肯定知道GF（28）的不可约多项式吧
/// ,m（x）=x8+x4+x3+x+1,它的二进制就是0x1b
/// \param multiple 倍数
/// \param b
/// \return
///
unsigned char CLAes::GF28Multi(unsigned char multiple, unsigned char b)
{
	unsigned char bw[4];
	unsigned char res=0;
	int i;
	bw[0] = b;
	for(i=1; i<4; i++)
	{
		bw[i] = bw[i-1]<<1;
		if(bw[i-1]&0x80)
		{
			bw[i]^=0x1b;
		}
	}
	for(i=0; i<4; i++)
	{
        if((multiple>>i)&0x01)
		{
			res ^= bw[i];
		}
	}
	return res;
}


///
/// \brief CLAes::SubBytes ByteSubstitution（字节替代--常用加密手段
/// 字节代替变换是一个简单的查表操作
///
/// \param state
///
void CLAes::SubBytes(unsigned char state[][4])
{
	int r,c;
	for(r=0; r<4; r++)
	{
		for(c=0; c<4; c++)
		{
            state[r][c] = m_aSbox[state[r][c]];
		}
	}
}


///
/// \brief CLAes::shiftRows （行移位变换）--常用加密手段
/// 即行移位变换作用于行上，第0行不变，第1行循环左移1个字节，第2行循环左移2个字节，第3行循环左移3个字节。
///
/// \param state
///
void CLAes::shiftRows(unsigned char state[][4])
{
    unsigned char temp[4]; // 临时保存单行变换后的数据
    int row,c;
    for(row=1; row<4; row++)
	{
		for(c=0; c<4; c++)
		{
            temp[c] = state[row][(c+row)%4];
		}

		for(c=0; c<4; c++)
		{
            state[row][c] = temp[c];
		}
        // 注意两个循环不能合并哦，因为后面一行的可能用到前面行的数据，前面行的数据在变换前要保持原值
	}
}

// MixColumns（列混淆变换） --常用加密手段
// 逐列混合
///
/// \brief CLAes::mixColumns 在AES算法中，需要模多项式m(x)=x^8+x^4+x^3+x+1。
/// 列混合即是用一个常矩阵乘以第二步变换后的矩阵，以达到矩阵中每一个元素都是该元素原所在列所有元素的加权和。
/// 列混淆变换实际上是使用乘法矩阵（注意：其运算中涉及的加法和乘法都是定义在GF(28)上的加法和乘法，目的就是为了确保运算结果不会溢出定义域）
/// \param state
///
void CLAes::mixColumns(unsigned char state[][4])
{
    //常矩阵
    /*
     * 02 03 01 01
     * 01 02 03 01
     * 01 01 02 03
     * 03 01 01 02
     *
     */
	unsigned char t[4];
	int r,c;
	for(c=0; c< 4; c++)
	{
		for(r=0; r<4; r++)
		{
			t[r] = state[r][c];
		}
		for(r=0; r<4; r++)
		{
            state[r][c] = GF28Multi(0x02, t[r])
                        ^ GF28Multi(0x03, t[(r+1)%4])
                        ^ GF28Multi(0x01, t[(r+2)%4])
                        ^ GF28Multi(0x01, t[(r+3)%4]);
		}
	}
}

// AddRoundKey（轮密钥加变换）  --常用加密手段
void CLAes::AddRoundKey(unsigned char state[][4], unsigned char k[][4])
{
	int r,c;
	for(c=0; c<4; c++)
	{
		for(r=0; r<4; r++)
		{
			state[r][c] ^= k[r][c];
		}
	}
}

void CLAes::InvSubBytes(unsigned char state[][4])
{
	int r,c;
	for(r=0; r<4; r++)
	{
		for(c=0; c<4; c++)
		{
			state[r][c] = InvSbox[state[r][c]];
		}
	}
}

void CLAes::InvShiftRows(unsigned char state[][4])
{
	unsigned char t[4];
	int r,c;
	for(r=1; r<4; r++)
	{
		for(c=0; c<4; c++)
		{
			t[c] = state[r][(c-r+4)%4];
		}
		for(c=0; c<4; c++)
		{
			state[r][c] = t[c];
		}
	}
}

void CLAes::InvMixColumns(unsigned char state[][4])
{
	unsigned char t[4];
	int r,c;
	for(c=0; c< 4; c++)
	{
		for(r=0; r<4; r++)
		{
			t[r] = state[r][c];
		}
		for(r=0; r<4; r++)
		{
            state[r][c] = GF28Multi(0x0e, t[r])
                        ^ GF28Multi(0x0b, t[(r+1)%4])
                        ^ GF28Multi(0x0d, t[(r+2)%4])
                        ^ GF28Multi(0x09, t[(r+3)%4]);
		}
	}
}
