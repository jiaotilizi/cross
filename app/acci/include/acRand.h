#ifndef __AC_RAND_H__
#define __AC_RAND_H__

#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <sys/time.h>

#include "acType.h"

/* RAND_MAX=0x7fffffff */

#define _RAND_MAX RAND_MAX

/*
 * 以秒级的当前时间作为随机种子，1s内突发随机数有可能重复
 * sRand：随机值0～RAND_MAX
 * sRandBool：随机true或者false
 * sRandInt：随机数0～_max,包含_max
 * sRandFloat：随机浮点数
 * sRandChar(str)：字符串中随机一个字母，不包含‘\0’
 * sRandObj(obj)：数组中一个随机对象
 *
 * */

#define S_SRAND	do{srand((unsigned)time(NULL));}while(0)

AC_U32		sRand(void);
AC_BOOL 	sRandBool(void);
AC_U32  	sRandInt(AC_U32 max);
float      sRandFloat(void);

#define sRandRange(min, max) (min+sRandInt(max-min))
#define sRandChar(str)   str[sRandInt(strlen(str)-1)]
#define sRandObj(obj)    obj[sRandInt(sizeof(obj)/sizeof(obj[0])-1)]

/*
 * 以毫秒级的当前时间作为随机种子，精度更高，突发随机数不重复
 * msRand：随机值0～RAND_MAX
 * msRandBool：随机true或者false
 * msRandInt：随机数0～_max,包含_max
 * msRandFloat：随机浮点数
 * msRandChar(str)：字符串中随机一个字母，不包含‘\0’
 * msRandObj(obj)：数组中一个随机对象
 * msRandRange(min, max)
 * */

#define MS_SRAND	do{struct timeval tv; gettimeofday(&tv, NULL); srand(tv.tv_usec + tv.tv_sec);}while(0)

AC_U32 	 msRand(void);
AC_BOOL msRandBool(void);
AC_U32 	 msRandInt(AC_U32 max);
float 	 msRandFloat(void);
char    msRandChar(char * str);

#define msRandRange(min, max) (min+msRandInt(max-min))
#define msRandObj(obj)   obj[msRandInt(sizeof(obj)/sizeof(obj[0])-1)]

/*
 * 生成整形数据
 * randLetter：大写字母，小写字母，数字，符号
 * randUpper：大写字母 A~Z
 * randLower：小写字母 a~z
 * randNumber：数字 0~9
 * randMac地址, 6字节长，0x000000000000~0xffffffffffff
 * randIpv4：ip4地址, 4字节长，0x00000000~0xffffffff
 *
 * */

char randLetter(void);
char randUpper(void);
char randLower(void);
char randNumber(void);
AC_MAC  randMac(void);
AC_IPV4  randIpv4(void);

/*
 * 生成整形数据
 * randAc8：  8位长， 有符号整数，-128～127
 * randAc16： 16位长，有符号整数，-32768～32767
 * randAc32： 32位长，有符号整数，-2147483648～2147483647
 * randAc64： 64位长，有符号整数，-9223372036854775808～9223372036854775807
 * randAcU8： 8位长， 无符号整数，0～255
 * randAcU16：16位长，无符号整数，0～65535
 * randAcU32：32位长，无符号整数，0～4294967295
 * randAcU64：64位长，无符号整数，0～18446744073709551615
 *
 * */

#define RANDFIXCHAR(__type)    do{char src[sizeof(__type)]; AC_U8 len = 0;\
                                    for(;len<sizeof(__type);len++)\
                                    src[len] = msRandInt(0xff);\
                                    return *(__type *)(src);}while(0)
#define RANDFIXTYPE(__type) __type rand##__type(void){RANDFIXCHAR(__type);}

AC_8    randAC_8(void);
AC_16   randAC_16(void);
AC_32   randAC_32(void);
AC_64   randAC_64(void);
AC_U8   randAC_U8(void);
AC_U16  randAC_U16(void);
AC_U32  randAC_U32(void);
AC_U64  randAC_U64(void);

#endif
