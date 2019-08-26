#ifndef V_UTIL_BASE_TYPES_H_
 #define V_UTIL_BASE_TYPES_H_
 
 #include <stdint.h>
 
 namespace v {
 
 	typedef unsigned int uint;
 	typedef unsigned char uchar;
 
 #ifdef _MSC_VER
 	typedef __int8  int8;
 	typedef __int16 int16;
 	typedef __int32 int24;
 	typedef __int32 int32;
 	typedef __int64 int64;
 
 	typedef unsigned __int8  uint8;
 	typedef unsigned __int16 uint16;
 	typedef unsigned __int32 uint24;
 	typedef unsigned __int32 uint32;
 	typedef unsigned __int64 uint64;
 #else
 	typedef int8_t  int8;
 	typedef int16_t int16;
 	typedef int32_t int24;
 	typedef int32_t int32;
 	typedef int64_t int64;
 
 	typedef uint8_t  uint8;
 	typedef uint16_t uint16;
 	typedef uint32_t uint24;
 	typedef uint32_t uint32;
 	typedef uint64_t uint64;
 #endif
 
 } // namespace v
 
 #endif // V_UTIL_BASE_TYPES_H_