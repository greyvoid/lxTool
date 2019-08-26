#pragma once

#define CountArray(ary)		(sizeof(ary)/sizeof(ary[0]))
#define zeromemory(x, size)	memset(x, 0, size)
#define SAFE_DELETE(p)           do { delete (p); (p) = nullptr; } while(0)
#define SAFE_DELETE_ARRAY(p)     do { if(p) { delete[] (p); (p) = nullptr; } } while(0)
#define SAFE_FREE(p)             do { if(p) { free(p); (p) = nullptr; } } while(0)
#define BREAK_IF(cond)           if(cond) break

#ifdef _WIN32
#define	SLEEP(longTime) Sleep(longTime)
#else
#include <unistd.h>
#define	SLEEP(longTime) usleep(longTime*1000)
#endif

// 数字转字符
#define NUM_TO_CHAR(x)      ((x)+0x30)

// 检查入参是否为空指针
// 没返回值
#define NOT_NULL_PTR(x)        \
{ \
    if (NULL == (x)) \
        return ; \
}
// 有返回值
#define NOT_NULL_PTR_RET(x, ret)    \
{ \
    if (NULL == (x)) \
        return (ret); \
}

