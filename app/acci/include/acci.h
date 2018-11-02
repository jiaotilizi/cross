#ifndef __ACCI_H__
#define __ACCI_H__
#include "acType.h"
#define _EXIT_CLI       0x135246
#define _PWD_LEN        16
#define INPUTBUFLEN     256
#define KEY_HELP        0x3F    //0x3F
#define KEY_BACKSPACE   0x08
#define KEY_TAB         0x09
#define KEY_DELETE      0x7F
#define KEY_SPACE       0x20
#define KEY_UP          0x41
#define KEY_DOWN        0x42
#define KEY_RIGHT       0x43
#define KEY_LEFT        0x44

#define TEXT_LEN        0x32
#define _LINE_MAX       0x10

#define CALLINFO do{printf("%s %d called.\n", __func__, __LINE__);}while(0)

typedef AC_STATUS AC_NOD_FUN(char * str);
typedef AC_STATUS AC_CMD_FUN(char * cmd);

typedef enum {
    ACCI_TEXT_POSITION_END = 1,
    ACCI_TEXT_POSITION_MID,
    ACCI_TEXT_POSITION_MAX,
} ACCI_TEXT_POSITION;

typedef enum {
#if 1
    ACCI_NODE_TYPE_INTEGER = 1<<4,
    ACCI_NODE_TYPE_LETTER = 2<<4,
    ACCI_NODE_TYPE_NAME = 3<<4,
    ACCI_NODE_TYPE_DESCIRPITON = 4<<4,
    ACCI_NODE_TYPE_IPV4 = 5<<4,
    ACCI_NODE_TYPE_MAC = 6<<4,
    ACCI_NODE_TYPE_STR = 7<<4,
#endif
    ACCI_NODE_TYPE_END = 1<<8,
    ACCI_NODE_TYPE_CMD = 2<<8,
    ACCI_NODE_TYPE_PAR = 3<<8,
    ACCI_NODE_TYPE_OPT = 4<<8,
    ACCI_NODE_TYPE_ON1 = 1<<12,
    ACCI_NODE_TYPE_0T1 = 2<<12,
    ACCI_NODE_TYPE_1TN = 3<<12,
    ACCI_NODE_TYPE_0TN = 4<<12,
    ACCI_NODE_TYPE_0C1 = 5<<12,
    ACCI_NODE_TYPE_1CN = 6<<12,
    ACCI_NODE_TYPE_0CN = 7<<12,
} ACCI_NODE_TYPE;

#define ACCI_NODE_TYPE_NUM(type) ((type) & (0x000f))
#define ACCI_NODE_TYPE_PAR(type) ((type) & (0x00f0))
#define ACCI_NODE_TYPE_CMD(type) ((type) & (0x0f00))
#define ACCI_NODE_TYPE_OPT(type) ((type) & (0xf000))

typedef enum {
    ACCI_MATCH_OK = 1<<4,
    ACCI_MATCH_FAIL = 2<<4,
    ACCI_MATCH_END = ACCI_TEXT_POSITION_END<<8,
    ACCI_MATCH_MID = ACCI_TEXT_POSITION_MID<<8,
} ACCI_MATCH_MODE;

#define ACCI_NODE_MATCH_NUM(ret) ((ret)  & (0x000f))
#define ACCI_NODE_MATCH_RET(ret) ((ret)  & (0x00f0))
#define ACCI_NODE_MATCH_SET(ret) ((ret)  & (0x0f00))
#define ACCI_NODE_MATCH_OPT(ret) ((ret)  & (0xf000))

typedef enum {
    ACCI_TK_CUT = 1,
    ACCI_TK_RES,
} ACCI_TK;

typedef struct {
    AC_U16   node;
    AC_U16  type;
    char *  name;
    char *  help;
    AC_NOD_FUN *   func;
} ACCI_NODE;

typedef struct {
    AC_U32  nodeNum;
    ACCI_NODE * acciNode;
} ACCI_CMD;

typedef struct {
    AC_U32  cmdNum;
    ACCI_CMD *    acciCmd;
} ACCI_LIST;

typedef struct {
    char    head[64];
    AC_U32  cursor;
    AC_BOOL chan;
    ACCI_LIST   * acciList;
} ACCI_VIEW;

typedef struct acciRecord{
    char * cmd;
    struct acciRecord *   next;
    struct acciRecord *   prev;
} ACCI_RECORD;

typedef struct	 {
    AC_U32  Num;
    AC_U32  NumMax;
    ACCI_RECORD *   head;
    ACCI_RECORD *   tail;
    ACCI_RECORD *   currentCmd;
} ACCI_HISTORY;

char * cmdTk(char * str, AC_U32 node, ACCI_TK tk);
AC_STATUS _lo_input(char * buf, AC_U32 len, char mask);
AC_STATUS acciExit(char * argv);
AC_STATUS acciLoop(void);

AC_STATUS terminalInit(void);
AC_STATUS displayTerminal(void);
AC_STATUS timeOutSet(AC_U32 time);
AC_STATUS viewInit(ACCI_VIEW * acciView);

AC_STATUS errPoint(AC_U32 len);
AC_STATUS morePrint(const char * str);
AC_STATUS nCharPrint(AC_U32 n, char letter);

AC_STATUS historyInit(void);
AC_STATUS displayHistoryCmd(void);
AC_STATUS historySetMax(AC_U32 max);

#define ACCINODEADD(_node, _name, _help, _func, _type) {.node = _node, .name = _name, .help = _help, \
                                                                        .func = _func, .type = _type}
#define ACCICMDSADD(_node) {.acciNode = _node, .nodeNum = ARRY_LEN(_node)}
#define ACCILISTADD(_cmds) {.acciCmd = _cmds, .cmdNum = ARRY_LEN(_cmds)}

#define ARRY_LEN(__array) (sizeof(__array)/sizeof(__array[0]))
#define FREE(__p)         do{if(NULL != (__p)){free(__p); (__p) = NULL;}}while(0)
#endif
