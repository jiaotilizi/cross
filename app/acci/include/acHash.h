#ifndef __AC_HASH_H__
#define __AC_HASH_H__
#include "acType.h"
typedef enum{
    DL_HASH_ARRAY,
    DL_HASH_LIST,
} AC_HASH_MODE;

typedef struct {
    AC_U32 elemKey;
    AC_U32 length;
    void *instance[];
} AC_HASH_ELEM;

typedef struct {
    AC_U32  count;
    AC_U32  length;
    AC_SIZE size;
    AC_BOOL (*ck)(void * ins, void * p);
    AC_U32  (*hash)(void * ins);
    void (*destroy)(void ** ins);
    void *(*new)(void * ins);
    AC_HASH_MODE mode;
    AC_HASH_ELEM *elem[];
} AC_HASH_TAB;

void * acHashTableGetInstance(AC_HASH_TAB ** brHashTable, void * ins);
void * acHashTableCreatInstance(AC_HASH_TAB ** brHashTable, void * ins);

AC_STATUS acHashTableDeleteInstance(AC_HASH_TAB ** brHashTable, void * ins);
AC_STATUS acHashTableInit(AC_HASH_TAB ** brHashTable, AC_HASH_TAB * templet);

typedef struct{
    AC_U32 id;
    char name[64];
} CASE_HASH;

AC_STATUS acHashTest(void);
#endif
