#ifndef __AC_TYPE_H__
#define __AC_TYPE_H__

#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <sys/types.h>
/*
 * 整形数据
 * AC_8：  8位长， 有符号整数，-128～127
 * AC_16： 16位长，有符号整数，-32768～32767
 * AC_32： 32位长，有符号整数，-2147483648～2147483647
 * AC_64： 64位长，有符号整数，-9223372036854775808～9223372036854775807
 * AC_U8： 8位长， 无符号整数，0～255
 * AC_U16：16位长，无符号整数，0～65535
 * AC_U32：32位长，无符号整数，0～4294967295
 * AC_U64：64位长，无符号整数，0～18446744073709551615
 *
 * */

typedef u_int8_t    AC_U8;
typedef u_int16_t   AC_U16;
typedef u_int32_t   AC_U32;
typedef u_int64_t   AC_U64;
typedef int8_t    AC_8;
typedef int16_t   AC_16;
typedef int32_t   AC_32;
typedef int64_t   AC_64;

typedef size_t      AC_SIZE;

typedef enum {
    AC_OK = 0,
    AC_FAIL = 1,
}AC_STATUS;

#define MAX_AC_8          (AC_8)((0xff-1)/2)
#define MAX_AC_16         (AC_16)((0xffff-1)/2)
#define MAX_AC_32         (AC_32)((0xffffffff-1)/2)
#define MAX_AC_64         (AC_64)((0xffffffffffffffff-1)/2)

#define MIN_AC_8          (AC_8)(0x00-MAX_AC_8-1)
#define MIN_AC_16         (AC_16)(0x0000-MAX_AC_16-1)
#define MIN_AC_32         (AC_32)(0x00000000-MAX_AC_32-1)
#define MIN_AC_64         (AC_64)(0x0000000000000000-MAX_AC_64-1)

#define MAX_AC_U8         0xff
#define MAX_AC_U16        0xffff
#define MAX_AC_U32        0xffffffff
#define MAX_AC_U64        0xffffffffffffffff

#define MIN_AC_U8         0x00
#define MIN_AC_U16        0x0000
#define MIN_AC_U32        0x00000000
#define MIN_AC_U64        0x0000000000000000

#define LEN_DEC_AC_8      strlen("-128")
#define LEN_DEC_AC_16     strlen("-32768")
#define LEN_DEC_AC_32     strlen("-2147483648")
#define LEN_DEC_AC_64     strlen("-9223372036854775808")

#define LEN_DEC_AC_U8     strlen("255")
#define LEN_DEC_AC_U16    strlen("65535")
#define LEN_DEC_AC_U32    strlen("4294967295")
#define LEN_DEC_AC_U64    strlen("18446744073709551615")

#define SIZE_DEC_AC_8     sizeof("-128")
#define SIZE_DEC_AC_16    sizeof("-32768")
#define SIZE_DEC_AC_32    sizeof("-2147483648")
#define SIZE_DEC_AC_64    sizeof("-9223372036854775808")

#define SIZE_DEC_AC_U8    sizeof("255")
#define SIZE_DEC_AC_U16   sizeof("65535")
#define SIZE_DEC_AC_U32   sizeof("4294967295")
#define SIZE_DEC_AC_U64   sizeof("18446744073709551615")

#define BASE02      "01"
#define BASE08      "01234567"
#define BASE10      "0123456789"
#define BASE16      "0123456789ABCDEFabcdef"
#define BASENUM     "0123456789"
#define BASEA2Z     "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define BASEa2z     "abcdefghijklmnopqrstuvwxyz"
#define BASE_       "!\"#$%&\'()*+,-./:;<=>\?@[\\]^_`{|}~"

typedef struct {
    char provider[3];
    char device_id[3];
} AC_MAC;

typedef struct {
    char ip[4];
} AC_IPV4;

typedef enum{
    AC_FALSE,
    AC_TRUE,
}AC_BOOL;

#define LETTER2NUM(__char) ((AC_8)(__char>='0' && __char<='9') ? (__char-'0')\
                :((__char>='a' && __char<='f') ? (__char-'a'+10)\
                :((__char>='A' && __char<='F') ? ((__char-'A'+10)):(0))))

/*
 * _BASE_MAC_2: ffff-ffff-ffff
 * _BASE_MAC_3: ff-ff-ff-ff-ff-ff
 * _BASE_MAC_4: ff:ff:ff:ff:ff:ff
 *
 * */

typedef enum {
    _BASE_BIN = 2,
    _BASE_OCT = 8,
    _BASE_DEC = 10,
    _BASE_HEX = 16,
    _BASE_MAC_2,
    _BASE_MAC_3,
    _BASE_MAC_4,
    _BASE_IPV4,
    _BASE_MAX,
}MAC_BASE;

/*
 * 字符有效性：
 * isLetter：字母，包括数字、大写字母、小写字母
 * isUpper：大写字母
 * isLower：小写字母
 * isBin：2进制字符
 * isOct：8进制字符
 * isDec：10进制字符
 * isHex：16进制字符
 * isSym：符号
 * inBase：检查字符是否在字符串中
 *
 * */

typedef AC_BOOL isType(char letter);

AC_BOOL isLetter(char letter);
AC_BOOL isUpper(char letter);
AC_BOOL isLower(char letter);
AC_BOOL isBin(char letter);
AC_BOOL isOct(char letter);
AC_BOOL isDec(char letter);
AC_BOOL isHex(char letter);
AC_BOOL isSym(char letter);
AC_BOOL inBase(char letter, char * baseSet, int baseLen);

/*
 * 有效的mac地址字符串，自动支持如下格式：
 * ff:ff:ff:ff:ff:ff
 * ff-ff-ff-ff-ff-ff
 * ffff-ffff-ffff
 *
 * */

AC_BOOL isMac(char * mac);

/*
 * 有效的ip4地址字符串，支持类似下面的地址：
 * 255.255.255.255
 * 255.100.10.0
 * 1.1.1.1
 *
 * */

AC_BOOL isIpv4(char * ip);

/*
 * 有效整形字符串：
 * isAcU8
 * isAcU16
 * isAcU32
 * isAcU64
 *
 * isAc8
 * isAc16
 * isAc32
 * isAc64
 *
 * */

AC_BOOL isAcU8(char * num);
AC_BOOL isAcU16(char * num);
AC_BOOL isAcU32(char * num);
AC_BOOL isAcU64(char * num);

AC_BOOL isAc8(char * num);
AC_BOOL isAc16(char * num);
AC_BOOL isAc32(char * num);
AC_BOOL isAc64(char * num);

/*
 * 字符串中字符有效性：
 * strIsType：字符串中字符是否符合type
 * strInBase：字符串中字符是否在字符序列中
 * arrayIsType：字符数组中字符是否符合type
 * arrayInBase：字符数组中字符是否在字符序列中
 *
 * */

AC_BOOL strIsType(char * str, isType * isType);
AC_BOOL strInBase(char * str, char * baseset, int baseLen);
AC_BOOL arrayIsType(char * array, int len, isType * isType);
AC_BOOL arrayInBase(char * array, int len, char * baseSet, int baseLen);

/*
 * 类型转化
 *
 * strToMac:字符串格式转AC_MAC
 * strToIpv4:字符串格式转AC_IPV4
 *
 * strToAc8
 * strToAc16
 * strToAc32
 * strToAc64
 *
 * strToAcU8
 * strToAcU16
 * strToAcU32
 * strToAcU64
 *
 * macToStr:     cs_mac转字符串格式，无需释放内存
 * ipv4ToStr:     cs_ip4转字符串格式，无需释放内存
 *
 * ac8ToStr:     AC_8转字符串格式，  无需释放内存
 * ac16ToStr:    AC_16转字符串格式， 无需释放内存
 * ac32ToStr:    AC_32转字符串格式， 无需释放内存
 * ac64ToStr:    AC_64转字符串格式， 无需释放内存
 * acU8ToStr:    AC_U8转字符串格式， 无需释放内存
 * acU16ToStr:   AC_U16转字符串格式，无需释放内存
 * acU32ToStr:   AC_U32转字符串格式，无需释放内存
 * acU64ToStr:   AC_U64转字符串格式，无需释放内存
 *
 * */
AC_MAC  strToMac(char * str);
AC_IPV4 strToIpv4(char * str);

AC_8   strToAc8(char * str);
AC_16  strToAc16(char * str);
AC_32  strToAc32(char * str);
AC_64  strToAc64(char * str);
AC_U8  strToAcU8(char * str);
AC_U16 strToAcU16(char * str);
AC_U32 strToAcU32(char * str);
AC_U64 strToAcU64(char * str);

char * ipv4ToStr(AC_IPV4 ipv4);
char * macToStr(AC_MAC mac, MAC_BASE base);

char * ac8ToStr(AC_8 num);
char * ac16ToStr(AC_16 num);
char * ac32ToStr(AC_32 num);
char * ac64ToStr(AC_64 num);
char * acU8ToStr(AC_U8 num);
char * acU16ToStr(AC_U16 num);
char * acU32ToStr(AC_U32 num);
char * acU64ToStr(AC_U64 num);

#define P_INDEX(__p, __index) (unsigned char)(((char *)(&__p))[__index])
#define MAC2STR(__str, __mac) do{sprintf(__str, "%02x:%02x:%02x:%02x:%02x:%02x", \
        P_INDEX(__mac, 0), P_INDEX(__mac, 1), P_INDEX(__mac, 2),\
        P_INDEX(__mac, 3), P_INDEX(__mac, 4), P_INDEX(__mac, 5));}while(0)
#define IPV42STR(__str, __ip4) do{sprintf(__str, "%d.%d.%d.%d", \
        P_INDEX(__ip4, 0), P_INDEX(__ip4, 1), P_INDEX(__ip4, 2), P_INDEX(__ip4, 3));}while(0)

#endif
