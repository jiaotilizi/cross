#include <termios.h>
#include <stdbool.h>
#include <setjmp.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <sys/time.h>
#include <stdio.h>
#include <time.h>

#include "acci.h"

#define CLEAR()             printf("\033[2J")                       // 清除屏幕
#define CLEAR_ROW()         printf("\033[K")                        // 清除行
#define MOVEUP(x)           printf("\033[%dA", (x))                 // 上移光标
#define MOVEDOWN(x)         printf("\033[%dB", (x))                 // 下移光标
#define MOVELEFT(y)         printf("\033[%dD", (y))                 // 左移光标
#define MOVERIGHT(y)        printf("\033[%dC", (y))                 // 右移光标
#define MOVETO(x,y)         printf("\033[%d;%dH", (x), (y))         // 定位光标
#define RESET_CURSOR()      printf("\033[H")                        // 光标复位
#define HIDE_CURSOR()       printf("\033[?25l")                     // 隐藏光标
#define SHOW_CURSOR()       printf("\033[?25h")                     // 显示光标
#define HIGHT_LIGHT()       printf("\033[1m")                       // 反显
#define UN_HIGHT_LIGHT()    printf("\033[0m")                       // 反显

char inBuf[INPUTBUFLEN];
static jmp_buf acciEnv;
static ACCI_VIEW acciView;
static ACCI_HISTORY acciHistory;
static struct  termios termios;

static AC_U32 lineMax;
static AC_U32 acciTimeOut = 3000000;

AC_STATUS nCharPrint(AC_U32 n, char letter){
    char * tmp = (char *)malloc(sizeof(char) * n + sizeof('\0'));
    memset(tmp, letter, sizeof(char)*n);
    tmp[n] = '\0';
    printf("%s\n", tmp);
    free(tmp);
    tmp=NULL;
    return AC_OK;
}

AC_STATUS errPoint(AC_U32 len){
    if(len <= INPUTBUFLEN){
        char * tmp = (char *)malloc(sizeof(char) * len + sizeof('^') + sizeof('\0'));
        memset(tmp, ' ', sizeof(char)*len);
        tmp[len++] = '^';
        tmp[len] = '\0';
        printf("%s\n", tmp);
        free(tmp);
        tmp=NULL;
        return AC_OK;
    }
    return AC_FAIL;
}

AC_STATUS morePrint(const char * str){
    const char * head = str;
    for(lineMax=0; *head; head++){
        if('\n' == *head){
            if(_LINE_MAX <= lineMax){
                MOVELEFT(strlen("--more--"));
                CLEAR();
                printf("%s--more--", str);
            }else{
                printf("%s", str);
            }
            fflush(stdout);
            lineMax++;
        }
    }
    return AC_OK;
}

static char sGetc(){
    SHOW_CURSOR();
    char c = getchar();
    alarm(acciTimeOut);
    return c;
}

static void _loop_init(AC_U32 __signal){
    if(__signal==SIGINT){
        alarm(acciTimeOut);
        printf("\n");
        siglongjmp(acciEnv, 1);
    }
}

AC_STATUS acciExit(char * argv){
    char *extra;
    if(!(extra = strtok(argv, " ")))
        return _EXIT_CLI;
    errPoint(strlen(acciView.head) + (extra-(char*)&inBuf)/sizeof(char));
    return printf(" %% Too many parameters!\n");
}

AC_STATUS historyInit(void){
    ACCI_RECORD * tmp = (ACCI_RECORD *)malloc(sizeof(ACCI_RECORD));
    memset(tmp, 0, sizeof(ACCI_RECORD));
    tmp->cmd = (char *)malloc(strlen("") + sizeof('\0'));
    //memset(tmp->cmd, 0, sizeof(strlen("") + sizeof('\0')));
    strcpy(tmp->cmd, "");
    tmp->next = NULL;
    tmp->prev = tmp;
    acciHistory.Num = 0;
    acciHistory.NumMax = 100;
    acciHistory.tail = NULL;
    acciHistory.head = tmp;
    acciHistory.currentCmd = NULL;
    return AC_OK;
}

AC_STATUS historySetMax(AC_U32 max){
    if(max<3 || max>100)
        return AC_FAIL;
    acciHistory.NumMax = max;
    while(acciHistory.Num > acciHistory.NumMax){
        acciHistory.tail = acciHistory.tail->prev;
        FREE(acciHistory.tail->next->cmd);
        acciHistory.tail->next->cmd  = NULL;
        acciHistory.tail->next->prev = NULL;
        acciHistory.tail->next->next = NULL;
        FREE(acciHistory.tail->next);
        acciHistory.tail->next = NULL;
        acciHistory.Num--;
    }
    return AC_OK;
}

AC_STATUS displayHistoryCmd(void){
    AC_U32 i;
    ACCI_RECORD * tmp = acciHistory.tail;
    printf("\033[1m%60s\033[0m\n", "command history:");
    nCharPrint(61, '-');
    for(i=0; tmp!=tmp->prev; tmp=tmp->prev, i++)
        printf(" %8d:    %s\n", i, tmp->cmd);
    nCharPrint(61, '-');
    printf(" %% Total command count: %d. Max command count:%d.\n", acciHistory.Num, acciHistory.NumMax);
    nCharPrint(61, '-');
    return fflush(stdout);
}

AC_STATUS terminalInit(void){
//    signal(SIGINT,  SIG_IGN);
//    signal(SIGTSTP, SIG_IGN);
//    signal(SIGQUIT, SIG_IGN);

    struct	termios	 termTmp;
    tcgetattr(fileno(stdin),	(void *)(&termios));
    memcpy(&termTmp,	&termios, sizeof(struct termios));
    termTmp.c_lflag &= ~(ICANON|ECHO|ECHONL);
    termTmp.c_cc[VTIME] = 0;
    termTmp.c_cc[VMIN] = 1;
    tcsetattr(fileno(stdin), TCSANOW, (void *)(&termTmp));
    return AC_OK;
}

AC_STATUS	displayTerminal(void){
    return printf("\n"
                  " *****************************************************\n"
			       " * JoyWare Industry Switch Terminal.                 *\n"
			       " * Build in %12s %8s.                   *\n"
			       " * Copyright(c) 2016 JoyWare Electronics Co., Ltd.   *\n"
			       " * All rights reserved.                              *\n"
			       " *****************************************************\n"
			       "\n",  __DATE__, __TIME__);
}

AC_STATUS timeOutSet(AC_U32 time){
    if (time>=10 && time<=3600) {
        acciTimeOut = time;
        return  AC_OK;
    }
    return AC_FAIL;
}

AC_STATUS viewInit(ACCI_VIEW * _acciView){
    if(!_acciView)
        return AC_FAIL;
    memcpy(&acciView, _acciView, sizeof(ACCI_VIEW));
    acciView.chan = AC_TRUE;
    return  AC_OK;
}

static AC_STATUS cmdRecord(const char * cmd){
    ACCI_RECORD * tmp;
    for(tmp=acciHistory.head; tmp; tmp = tmp->next){
        if(!strcmp(cmd, tmp->cmd)){
            tmp->prev->next = tmp->next;
            if(tmp->next)
                tmp->next->prev = tmp->prev;
            else
                acciHistory.tail = tmp->prev;
			break;
        }
    }
    if(!tmp){
		tmp = (ACCI_RECORD *)malloc(sizeof(ACCI_RECORD));
		memset(tmp, 0, sizeof(ACCI_RECORD));
		tmp->cmd = (char *)malloc(strlen(cmd)+sizeof('\0'));
		memset(tmp->cmd, 0, sizeof(strlen(cmd) + sizeof('\0')));
		strcpy(tmp->cmd, cmd);
		acciHistory.Num++;
	}
	tmp->next = acciHistory.head->next;
	tmp->prev = acciHistory.head;
	if(!acciHistory.head->next)
	    acciHistory.tail = tmp;
	else
	    acciHistory.head->next->prev = tmp;
	acciHistory.head->next = tmp;
	while(acciHistory.Num > acciHistory.NumMax){
	    acciHistory.tail = acciHistory.tail->prev;
	    FREE(acciHistory.tail->next->cmd);
		acciHistory.tail->next->cmd = NULL;
		acciHistory.tail->next->prev = NULL;
		acciHistory.tail->next->next = NULL;
		FREE(acciHistory.tail->next);
		acciHistory.tail->next = NULL;
		acciHistory.Num--;
	}
	return AC_OK;
}

static void handerInput(char c){
	if(INPUTBUFLEN - 1 == strlen(inBuf))
		return;
	AC_U32 i;
	for(i = strlen(inBuf); i > acciView.cursor; i--)
		inBuf[i] = inBuf[i-1];
	inBuf[acciView.cursor] = c;
	CLEAR_ROW();
	printf("%s", inBuf + acciView.cursor);
	acciView.cursor ++;
	acciView.chan = AC_TRUE;
	if(strlen(inBuf) - acciView.cursor)
		MOVELEFT(strlen(inBuf) - acciView.cursor);
	fflush(stdout);
}

static void handerBackspace(void){
	if('\0' == inBuf[0] || 0==acciView.cursor)
		return;
	AC_U32 i;
	for(i=acciView.cursor-1; i < strlen(inBuf); i++)
		inBuf[i] = inBuf[i+1];
	acciView.cursor--;
	acciView.chan = AC_TRUE;
	MOVELEFT(1);
	CLEAR_ROW();
	printf("%s", inBuf + acciView.cursor);
	if(strlen(inBuf) - acciView.cursor)
		MOVELEFT(strlen(inBuf) - acciView.cursor);
	fflush(stdout);
}

static void handerDelete(void){
	if(acciView.cursor == strlen(inBuf))
		return;
	AC_U32 i;
	for(i=acciView.cursor; i < strlen(inBuf); i++)
		inBuf[i] = inBuf[i+1];
	CLEAR_ROW();
	printf("%s", inBuf + acciView.cursor);
	acciView.chan = AC_TRUE;
	if(strlen(inBuf) - acciView.cursor)
		MOVELEFT(strlen(inBuf) - acciView.cursor);
	fflush(stdout);
}

static void handerUp(void){
	if(NULL == acciHistory.currentCmd)
	    acciHistory.currentCmd = acciHistory.head;
	if(NULL != acciHistory.currentCmd->next){
	    acciHistory.currentCmd = acciHistory.currentCmd->next;
		memset(inBuf, 0, sizeof(char)*INPUTBUFLEN);
		strcpy(inBuf, acciHistory.currentCmd->cmd);
		if(0 != acciView.cursor)
			MOVELEFT(acciView.cursor);
		CLEAR_ROW();
		printf("%s", inBuf);
		acciView.cursor = strlen(inBuf);
		fflush(stdout);
	}
	acciView.chan = AC_TRUE;
}

static void handerDown(void){
	if(NULL == acciHistory.currentCmd)
	    acciHistory.currentCmd = acciHistory.head;
	if(NULL != acciHistory.currentCmd->prev){
	    acciHistory.currentCmd = acciHistory.currentCmd->prev;
		memset(inBuf,  0,  sizeof(char)*INPUTBUFLEN);
		strcpy(inBuf,  acciHistory.currentCmd->cmd);
		if(0 != acciView.cursor)
			MOVELEFT(acciView.cursor);
		CLEAR_ROW();
		printf("%s", inBuf);
		acciView.cursor = strlen(inBuf);
		fflush(stdout);
	}
	acciView.chan = AC_TRUE;
}

static	void handerRight(void){
	if(acciView.cursor < strlen(inBuf)){
	    acciView.cursor++;
		MOVERIGHT(1);
		fflush(stdout);
	}
	acciView.chan = AC_TRUE;
}

static	void handerLeft(void){
    if(acciView.cursor > 0){
        acciView.cursor--;
        MOVELEFT(1);
        fflush(stdout);
	}
    acciView.chan = AC_TRUE;
}

static AC_U32 strCmp(const char *str_1, const char *str_2){
    AC_U32 i, len;
    for(i=0, len = strlen(str_1)<strlen(str_2) ? strlen(str_1):strlen(str_2);i<len && str_1[i] ==  str_2[i];i++){}
    return i;
}

static AC_STATUS matchNode(char * cmdText, ACCI_NODE * acciNode){
    switch(ACCI_NODE_TYPE_CMD(acciNode->type)){
        case ACCI_NODE_TYPE_END:
            if(!strlen(cmdText)){
               printf("\t %-16s \t %s\n", acciNode->name, acciNode->help);
               return AC_OK;
            }
               break;
        case ACCI_NODE_TYPE_PAR:
            if(acciNode->func && AC_FAIL == acciNode->func(cmdText))
            	return AC_FAIL;
            printf("\t %-16s \t %s\n", acciNode->name, acciNode->help);
            return AC_OK;
            break;
        case ACCI_NODE_TYPE_CMD:
        case ACCI_NODE_TYPE_OPT:
            if(strlen(cmdText)<= strlen(acciNode->name)
                    && !strncmp(cmdText, acciNode->name, strlen(cmdText))){
                printf("\t %-16s \t %s\n", acciNode->name, acciNode->help);
                return AC_OK;
            }
            break;
        default:
            return AC_FAIL;
            break;
        }
    return AC_FAIL;
}

static AC_STATUS varNode(char * cmdText, ACCI_NODE * acciNode){
    switch(ACCI_NODE_TYPE_CMD(acciNode->type)){
        case ACCI_NODE_TYPE_END:
            if(!strlen(cmdText))
               return AC_OK;
               break;
        case ACCI_NODE_TYPE_PAR:
            switch(ACCI_NODE_TYPE_PAR(acciNode->type)){
                case ACCI_NODE_TYPE_INTEGER:
                case ACCI_NODE_TYPE_IPV4:
                case ACCI_NODE_TYPE_MAC:
                    return AC_OK;
                    break;
                case ACCI_NODE_TYPE_DESCIRPITON:
                    return AC_OK;
                    break;
                case ACCI_NODE_TYPE_NAME:
                    return AC_OK;
                    break;
                default:
                    return acciNode->func ? acciNode->func(cmdText) : AC_OK;
                    break;
            }
            break;
        case ACCI_NODE_TYPE_CMD:
        case ACCI_NODE_TYPE_OPT:
            if(strlen(cmdText)== strlen(acciNode->name)
                    && !strcmp(cmdText, acciNode->name))
                return AC_OK;
            break;
        default:
            return AC_FAIL;
            break;
        }
    return AC_FAIL;
}

static ACCI_TEXT_POSITION acciCmdSplit(char ** cmdText,  char * buff, ACCI_NODE *acciNodeVar){
    ACCI_TEXT_POSITION position;
    static char *textNext, *textStart;
    char mask = ACCI_NODE_TYPE_DESCIRPITON == ACCI_NODE_TYPE_PAR(acciNodeVar->type) ? '\0':' ';
    for(textStart = buff ? buff : textNext; *textStart && *textStart == ' '; textStart++){}
    for(*cmdText = textStart; *textStart && *textStart != mask; textStart++){}
    textNext = *textStart == '\0' ? textStart:textStart+1;
    position = *textStart == '\0' ? ACCI_TEXT_POSITION_END:ACCI_TEXT_POSITION_MID;
    *textStart = *textStart == mask ? '\0' : *textStart;
    for(++textStart; position == ACCI_TEXT_POSITION_MID && *textStart; textStart++)
        position = ' ' != *textStart ? ACCI_TEXT_POSITION_MID:position;
#if 0
    printf(" %% Text : %-16s \t position : %s\n", *cmdText, ACCI_TEXT_POSITION_END == position ? "END":"MID");
#endif
    return position;
}
static AC_STATUS cmdTextRest(char *cmdText, char ** cmdTextTmp){
	for(;*cmdText;cmdText++){}
	for(;!(*cmdText);cmdText++){}
	for(;(*cmdTextTmp) > cmdText;(*cmdTextTmp)--)
		**cmdTextTmp = **cmdTextTmp ? **cmdTextTmp:' ';
	return AC_OK;
}
static AC_U32 varCmd(char **cmdTextTmp, ACCI_NODE *acciNodeVar, ACCI_NODE *acciNodeEnd,  ACCI_NODE **acciNodeTarget){
    AC_U32 retVar, retTmp, nodeVar, nodeTmp, n;
    ACCI_NODE *acciNodeTmp = acciNodeVar;
    ACCI_TEXT_POSITION position = 0;
    char * cmdText;
    for(retVar = 0, retTmp = 0, nodeVar = 0, nodeTmp=0; acciNodeTmp < acciNodeEnd;){
    	cmdText = *cmdTextTmp;
    	acciNodeVar = (AC_OK == (retVar = varNode(cmdText, acciNodeTmp))) ? acciNodeTmp:acciNodeVar;
#if 0
    	printf(" %% %8s type: 0x%04x node: %d , name:%16s, retVal: %04s, position : %s\n", cmdText,
    					ACCI_NODE_TYPE_CMD(acciNodeTmp->type), acciNodeTmp->node, acciNodeTmp->name, AC_OK == retVar
    					? "OK":"FAIL", position == ACCI_TEXT_POSITION_END ? "END":"MID");
#endif
        for(acciNodeTmp++; acciNodeTmp < acciNodeEnd && acciNodeTmp->node >= acciNodeVar->node; acciNodeTmp++){
            n = acciNodeTmp->node - acciNodeVar->node;
            switch(ACCI_NODE_TYPE_OPT(acciNodeVar->type)){
                case ACCI_NODE_TYPE_ON1:
						if(AC_OK == retVar){
							if(1 == n){
								position = position ? position : acciCmdSplit(cmdTextTmp, NULL, acciNodeVar);
								if(ACCI_TEXT_POSITION_END == position){
									(*acciNodeTarget) = acciNodeTmp;
									nodeVar ++;
									return acciNodeVar->node << 12 | ACCI_MATCH_OK | nodeVar;
								}else{
									retTmp = varCmd(cmdTextTmp, acciNodeTmp, acciNodeEnd, acciNodeTarget);
									if(ACCI_MATCH_OK == ACCI_NODE_MATCH_RET(retTmp)){
										nodeTmp ++;
										nodeVar ++;
										return acciNodeVar->node << 12 | ACCI_MATCH_OK | nodeVar;
									}else{
										cmdTextRest(cmdText, cmdTextTmp);
										*cmdTextTmp = cmdText;
										continue;
									}
								}
							}else{
								continue;
							}
						}else{
							if(0 == n){
								break;
							}else{
								continue;
							}
						}
                    break;
                case ACCI_NODE_TYPE_0T1:
						if(AC_OK == retVar){
							if(1 == n){
								position = position ? position : acciCmdSplit(cmdTextTmp, NULL, acciNodeVar);
								if(ACCI_TEXT_POSITION_END == position){
									(*acciNodeTarget) = acciNodeTmp;
									nodeVar ++;
									return acciNodeVar->node << 12 | ACCI_MATCH_OK | nodeVar;
								}else{
									retTmp = varCmd(cmdTextTmp, acciNodeTmp, acciNodeEnd, acciNodeTarget);
									if(ACCI_MATCH_OK == ACCI_NODE_MATCH_RET(retTmp)){
										nodeTmp ++;
										nodeVar ++;
										return acciNodeVar->node << 12 | ACCI_MATCH_OK | nodeVar;
									}else{
										cmdTextRest(cmdText, cmdTextTmp);
										*cmdTextTmp = cmdText;
										continue;
									}
								}
							}else{
								continue;
							}
						}else{
							if(0 == n || 1 == n){
								break;
							}else{
								continue;
							}
						}
                    break;
                case ACCI_NODE_TYPE_1TN:
						if(AC_OK == retVar){
							if(ACCI_NODE_TYPE_NUM(acciNodeVar->type)){
								if(nodeVar >= ACCI_NODE_TYPE_NUM(acciNodeVar->type)){
									if(1 == n){
										position = position ? position : acciCmdSplit(cmdTextTmp, NULL, acciNodeVar);
										if(ACCI_TEXT_POSITION_END == position){
											(*acciNodeTarget) = acciNodeTmp;
											nodeVar ++;
											return acciNodeVar->node << 12 | ACCI_MATCH_OK | nodeVar;
										}else{
											retTmp = varCmd(cmdTextTmp, acciNodeTmp, acciNodeEnd, acciNodeTarget);
											if(ACCI_MATCH_OK == ACCI_NODE_MATCH_RET(retTmp)){
												nodeTmp ++;
												nodeVar ++;
												return acciNodeVar->node << 12 | ACCI_MATCH_OK | nodeVar;
											}else{
												cmdTextRest(cmdText, cmdTextTmp);
												*cmdTextTmp = cmdText;
												continue;
											}
										}
									}else{
										continue;
									}
								}else if(nodeVar > 0){
									if(0 == n || 1 == n){
										position = position ? position : acciCmdSplit(cmdTextTmp, NULL, acciNodeVar);
										if(ACCI_TEXT_POSITION_END == position){
											(*acciNodeTarget) = acciNodeTmp;
											nodeVar ++;
											return acciNodeVar->node << 12 | ACCI_MATCH_OK | nodeVar;
										}else{
											retTmp = varCmd(cmdTextTmp, acciNodeTmp, acciNodeEnd, acciNodeTarget);
											if(ACCI_MATCH_OK == ACCI_NODE_MATCH_RET(retTmp)){
												nodeTmp ++;
												nodeVar ++;
												return acciNodeVar->node << 12 | ACCI_MATCH_OK | nodeVar;
											}else{
												cmdTextRest(cmdText, cmdTextTmp);
												*cmdTextTmp = cmdText;
												continue;
											}
										}
									}else{
										continue;
									}
								}else{
									if(1 == n){
										position = position ? position : acciCmdSplit(cmdTextTmp, NULL, acciNodeVar);
										if(ACCI_TEXT_POSITION_END == position){
											(*acciNodeTarget) = acciNodeTmp;
											nodeVar ++;
											return acciNodeVar->node << 12 | ACCI_MATCH_OK | nodeVar;
										}else{
											retTmp = varCmd(cmdTextTmp, acciNodeTmp, acciNodeEnd, acciNodeTarget);
											if(ACCI_MATCH_OK == ACCI_NODE_MATCH_RET(retTmp)){
												nodeTmp ++;
												nodeVar ++;
												return acciNodeVar->node << 12 | ACCI_MATCH_OK | nodeVar;
											}else{
												cmdTextRest(cmdText, cmdTextTmp);
												*cmdTextTmp = cmdText;
												continue;
											}
										}
									}else{
										continue;
									}
								}
							}else{
								if(nodeVar > 0){
									if(0 == n || 1 == n){
										position = position ? position : acciCmdSplit(cmdTextTmp, NULL, acciNodeVar);
										if(ACCI_TEXT_POSITION_END == position){
											(*acciNodeTarget) = acciNodeTmp;
											nodeVar ++;
											return acciNodeVar->node << 12 | ACCI_MATCH_OK | nodeVar;
										}else{
											retTmp = varCmd(cmdTextTmp, acciNodeTmp, acciNodeEnd, acciNodeTarget);
											if(ACCI_MATCH_OK == ACCI_NODE_MATCH_RET(retTmp)){
												nodeTmp ++;
												nodeVar ++;
												return acciNodeVar->node << 12 | ACCI_MATCH_OK | nodeVar;
											}else{
												cmdTextRest(cmdText, cmdTextTmp);
												*cmdTextTmp = cmdText;
												continue;
											}
										}
									}else{
										continue;
									}
								}else{
									if(1 == n){
										position = position ? position : acciCmdSplit(cmdTextTmp, NULL, acciNodeVar);
										if(ACCI_TEXT_POSITION_END == position){
											(*acciNodeTarget) = acciNodeTmp;
											nodeVar ++;
											return acciNodeVar->node << 12 | ACCI_MATCH_OK | nodeVar;
										}else{
											retTmp = varCmd(cmdTextTmp, acciNodeTmp, acciNodeEnd, acciNodeTarget);
											if(ACCI_MATCH_OK == ACCI_NODE_MATCH_RET(retTmp)){
												nodeTmp ++;
												nodeVar ++;
												return acciNodeVar->node << 12 | ACCI_MATCH_OK | nodeVar;
											}else{
												cmdTextRest(cmdText, cmdTextTmp);
												*cmdTextTmp = cmdText;
												continue;
											}
										}
									}else{
										continue;
									}
								}
							}
						}else{
							if(0 == n){
								break;
							}else{
								continue;
							}
						}
                    break;
                case ACCI_NODE_TYPE_0TN:
						if(AC_OK == retVar){
							if(ACCI_NODE_TYPE_NUM(acciNodeVar->type)){
								if(nodeVar >= ACCI_NODE_TYPE_NUM(acciNodeVar->type)){
									if(1 == n){
										position = position ? position : acciCmdSplit(cmdTextTmp, NULL, acciNodeVar);
										if(ACCI_TEXT_POSITION_END == position){
											(*acciNodeTarget) = acciNodeTmp;
											nodeVar ++;
											return acciNodeVar->node << 12 | ACCI_MATCH_OK | nodeVar;
										}else{
											retTmp = varCmd(cmdTextTmp, acciNodeTmp, acciNodeEnd, acciNodeTarget);
											if(ACCI_MATCH_OK == ACCI_NODE_MATCH_RET(retTmp)){
												nodeTmp ++;
												nodeVar ++;
												return acciNodeVar->node << 12 | ACCI_MATCH_OK | nodeVar;
											}else{
												cmdTextRest(cmdText, cmdTextTmp);
												*cmdTextTmp = cmdText;
												continue;
											}
										}
									}else{
										continue;
									}
								}else if(nodeVar > 0){
									if(0 == n || 1 == n){
										position = position ? position : acciCmdSplit(cmdTextTmp, NULL, acciNodeVar);
										if(ACCI_TEXT_POSITION_END == position){
											(*acciNodeTarget) = acciNodeTmp;
											nodeVar ++;
											return acciNodeVar->node << 12 | ACCI_MATCH_OK | nodeVar;
										}else{
											retTmp = varCmd(cmdTextTmp, acciNodeTmp, acciNodeEnd, acciNodeTarget);
											if(ACCI_MATCH_OK == ACCI_NODE_MATCH_RET(retTmp)){
												nodeTmp ++;
												nodeVar ++;
												return acciNodeVar->node << 12 | ACCI_MATCH_OK | nodeVar;
											}else{
												cmdTextRest(cmdText, cmdTextTmp);
												*cmdTextTmp = cmdText;
												continue;
											}
										}
									}else{
										continue;
									}
								}else{
									if(1 == n){
										position = position ? position : acciCmdSplit(cmdTextTmp, NULL, acciNodeVar);
										if(ACCI_TEXT_POSITION_END == position){
											(*acciNodeTarget) = acciNodeTmp;
											nodeVar ++;
											return acciNodeVar->node << 12 | ACCI_MATCH_OK | nodeVar;
										}else{
											retTmp = varCmd(cmdTextTmp, acciNodeTmp, acciNodeEnd, acciNodeTarget);
											if(ACCI_MATCH_OK == ACCI_NODE_MATCH_RET(retTmp)){
												nodeTmp ++;
												nodeVar ++;
												return acciNodeVar->node << 12 | ACCI_MATCH_OK | nodeVar;
											}else{
												cmdTextRest(cmdText, cmdTextTmp);
												*cmdTextTmp = cmdText;
												continue;
											}
										}
									}else{
										continue;
									}
								}
							}else{
								if(nodeVar > 0){
									if(0 == n || 1 == n){
										position = position ? position : acciCmdSplit(cmdTextTmp, NULL, acciNodeVar);
										if(ACCI_TEXT_POSITION_END == position){
											(*acciNodeTarget) = acciNodeTmp;
											nodeVar ++;
											return acciNodeVar->node << 12 | ACCI_MATCH_OK | nodeVar;
										}else{
											retTmp = varCmd(cmdTextTmp, acciNodeTmp, acciNodeEnd, acciNodeTarget);
											if(ACCI_MATCH_OK == ACCI_NODE_MATCH_RET(retTmp)){
												nodeTmp ++;
												nodeVar ++;
												return acciNodeVar->node << 12 | ACCI_MATCH_OK | nodeVar;
											}else{
												cmdTextRest(cmdText, cmdTextTmp);
												*cmdTextTmp = cmdText;
												continue;
											}
										}
									}else{
										continue;
									}
								}else{
									if(1 == n){
										position = position ? position : acciCmdSplit(cmdTextTmp, NULL, acciNodeVar);
										if(ACCI_TEXT_POSITION_END == position){
											(*acciNodeTarget) = acciNodeTmp;
											nodeVar ++;
											return acciNodeVar->node << 12 | ACCI_MATCH_OK | nodeVar;
										}else{
											retTmp = varCmd(cmdTextTmp, acciNodeTmp, acciNodeEnd, acciNodeTarget);
											if(ACCI_MATCH_OK == ACCI_NODE_MATCH_RET(retTmp)){
												nodeTmp ++;
												nodeVar ++;
												return acciNodeVar->node << 12 | ACCI_MATCH_OK | nodeVar;
											}else{
												cmdTextRest(cmdText, cmdTextTmp);
												*cmdTextTmp = cmdText;
												continue;
											}
										}
									}else{
										continue;
									}
								}
							}
						}else{
							if(0 == n){
								break;
							}else{
								continue;
							}
						}
					break;
                default:
                    break;
            }
            break;
        }
    }
    *acciNodeTarget = NULL;
    return acciNodeVar->node << 12 | ACCI_MATCH_FAIL | nodeVar;
}

static AC_STATUS acciNodeMatch(char *cmdText, ACCI_NODE ** acciNodeTarget, ACCI_NODE * acciNodeEnd){
    ACCI_NODE   * acciNodeTmp;
    AC_STATUS retVal;
    AC_U32 varNode;
    for(varNode = 0, acciNodeTmp = (*acciNodeTarget);
    		acciNodeTmp && acciNodeTmp != acciNodeEnd && acciNodeTmp->node >= (*acciNodeTarget)->node;
    		acciNodeTmp++){
        AC_U32 n = acciNodeTmp->node - (*acciNodeTarget)->node;
        switch(ACCI_NODE_TYPE_OPT((*acciNodeTarget)->type)){
            case ACCI_NODE_TYPE_ON1:
            case ACCI_NODE_TYPE_1TN:
            case ACCI_NODE_TYPE_0TN:
                if(0 != n)
                    continue;
                break;
            case ACCI_NODE_TYPE_0T1:
                if(1 != n && 0 != n)
                    continue;
                break;
            default:
                break;
        }
        retVal = matchNode(cmdText, acciNodeTmp);
        varNode += AC_OK == retVal ? 1:0;
    }
    return varNode ? AC_OK:AC_FAIL;
}

static AC_STATUS handerHelp(void) {
	printf("?\n");
	AC_U32 i, retVal, varnode, psi;
	ACCI_CMD *acciCmd;
	ACCI_NODE *acciNode, *acciNodeEnd, *acciNodeVar, *acciNodeTmp, *acciNodeTarget = NULL;
	char * buff = (char *) malloc(((strlen(inBuf) + sizeof('\0')) / 4 + 1) * 4);
	strcpy(buff, inBuf);
	char * cmdText;
	char * cmdTextTmp;
	ACCI_TEXT_POSITION position;
	for (i = 0, varnode = 0, acciNodeTarget = NULL;
	                i < acciView.acciList->cmdNum; i++, acciNodeTarget = NULL) {

		acciCmd = &(acciView.acciList->acciCmd[i]);
		acciNode = acciNodeVar = &(acciCmd->acciNode[0]);
		acciNodeEnd = &(acciCmd->acciNode[acciCmd->nodeNum]);

		if (!i)
			position = acciCmdSplit(&cmdTextTmp, buff, acciNodeVar);
		cmdText = cmdTextTmp;
		if (ACCI_TEXT_POSITION_END == position) {
			acciNodeTarget = acciNode;
		} else {
			retVal = varCmd(&cmdTextTmp, acciNodeVar, acciNodeEnd, &acciNodeTarget);

			if (ACCI_MATCH_OK == ACCI_NODE_MATCH_RET(retVal)) {
				if (acciNodeTarget) {
					retVal = acciNodeMatch(cmdTextTmp, &acciNodeTarget, acciNodeEnd);
					psi = (cmdTextTmp - buff) / sizeof(char);
					varnode += AC_OK == retVal ? 1 : 0;
				}
				break;
			} else {
				cmdTextRest(cmdText, &cmdTextTmp);
				cmdTextTmp = cmdText;
				continue;
			}
		}
		if (acciNodeTarget) {
			retVal = acciNodeMatch(cmdText, &acciNodeTarget, acciNodeEnd);
			psi = (cmdTextTmp - buff) / sizeof(char);
			varnode += AC_OK == retVal ? 1 : 0;
		}
	}
err:
	if (!varnode) {
		errPoint(strlen(acciView.head) + psi);
		printf(" %% Unrecognized command at \'^\' position.\n");
	}
end:
	printf("\n%s%s", acciView.head, inBuf);
	fflush(stdout);
	free(buff);
	acciView.chan = AC_TRUE;
	return AC_OK;
}

static AC_STATUS handerTab(void) {
	printf("\n");
	static AC_U32 i, retVal, varnode;
	ACCI_CMD *acciCmd;
	static char textTab[1024];
	static ACCI_NODE *acciNode, *acciNodeEnd, *acciNodeVar, *acciNodeTarget;
	char * buff = (char *) malloc(((strlen(inBuf) + sizeof('\0')) / 4 + 1) * 4);
	strcpy(buff, inBuf);
	char * cmdText;
	char * cmdTextTmp;
	static AC_U32 psi;
	ACCI_TEXT_POSITION position = 0;
	if (AC_TRUE == acciView.chan) {
		acciView.chan = AC_FALSE;
		for (i = 0, varnode = 0, acciNodeTarget = NULL; i < acciView.acciList->cmdNum; i++) {

			acciCmd = &(acciView.acciList->acciCmd[i]);
			acciNode = acciNodeVar = &(acciCmd->acciNode[0]);
			acciNodeEnd = &(acciCmd->acciNode[acciCmd->nodeNum]);

			position = position ? position : acciCmdSplit(&cmdText, buff, acciNodeVar);
			cmdText = cmdTextTmp;

			if (ACCI_TEXT_POSITION_END == position)
				acciNodeTarget = acciNode;
			else
				retVal = varCmd(&cmdText, acciNodeVar, acciNodeEnd, &acciNodeTarget);
			memset(textTab, 0, sizeof(textTab));
			strcpy(textTab, cmdText);
			psi = (cmdText - buff) / sizeof(char);
			if (acciNodeTarget)
				break;

			acciCmd = &(acciView.acciList->acciCmd[i]);
			acciNode = acciNodeVar = &(acciCmd->acciNode[0]);
			acciNodeEnd = &(acciCmd->acciNode[acciCmd->nodeNum]);

			if (!i)
				position = acciCmdSplit(&cmdTextTmp, buff, acciNodeVar);
			cmdText = cmdTextTmp;
			if (ACCI_TEXT_POSITION_END == position) {
				acciNodeTarget = acciNode;
			} else {
				retVal = varCmd(&cmdTextTmp, acciNodeVar, acciNodeEnd, &acciNodeTarget);

				if (ACCI_MATCH_OK == ACCI_NODE_MATCH_RET(retVal)) {
					if (acciNodeTarget) {
						retVal = acciNodeMatch(cmdTextTmp, &acciNodeTarget, acciNodeEnd);
						psi = (cmdTextTmp - buff) / sizeof(char);
						varnode += AC_OK == retVal ? 1 : 0;
					}
					break;
				} else {
					cmdTextRest(cmdText, &cmdTextTmp);
					cmdTextTmp = cmdText;
					continue;
				}
			}
			if (acciNodeTarget) {
				retVal = acciNodeMatch(cmdText, &acciNodeTarget, acciNodeEnd);
				psi = (cmdTextTmp - buff) / sizeof(char);
				varnode += AC_OK == retVal ? 1 : 0;
			}
		}
	}
	if (!acciNodeTarget) {
		errPoint(strlen(acciView.head) + psi);
		printf(" %% Unrecognized command at \'^\' position.\n");
		goto end;
	}
	for (; i < acciView.acciList->cmdNum; i++) {
		acciCmd = &(acciView.acciList->acciCmd[i]);
		acciNode = acciNodeVar = &(acciCmd->acciNode[0]);
		acciNodeEnd = &(acciCmd->acciNode[acciCmd->nodeNum]);
		for (; acciNode < acciNodeEnd; acciNode++) {
			if (acciNode->node == acciNodeTarget->node
			                && 0
			                                == strncmp(textTab, acciNode->name,
			                                                strlen(textTab))
			                && (ACCI_NODE_TYPE_CMD
			                                == ACCI_NODE_TYPE_CMD(
			                                                acciNode->type)
			                                || ACCI_NODE_TYPE_OPT
			                                                == ACCI_NODE_TYPE_CMD(
			                                                                acciNode->type))) {
				strcpy(&(inBuf[psi]), acciNode->name);
				goto end;
			}
		}
	}

	end: printf("%s%s", acciView.head, inBuf);
	acciView.cursor = strlen(inBuf);
	fflush(stdout);
	free(buff);
	return AC_OK;
}

static AC_STATUS handerEnter(void){
    printf("\n");
    AC_U32 i, retVal, varnode;
    ACCI_CMD    *acciCmd;
    ACCI_NODE   *acciNode, *acciNodeEnd, *acciNodeVar, *acciNodeTmp, *acciNodeTarget;
    char * buff = (char *)malloc(((strlen(inBuf) + sizeof('\0'))/4+1)*4);
    strcpy(buff, inBuf);
    char * cmdText;
    ACCI_TEXT_POSITION position;
    for(i=0, varnode = 0, acciNodeTarget=NULL; i<acciView.acciList->cmdNum; i++){

		acciCmd = &(acciView.acciList->acciCmd[i]);
		acciNode = acciNodeVar = &(acciCmd->acciNode[0]);
		acciNodeEnd = &(acciCmd->acciNode[acciCmd->nodeNum]);

        if(!i)
        	position = acciCmdSplit(&cmdText, buff, acciNodeVar);

		if(cmdText == &buff[strlen(buff)])
			return AC_OK;

		if(ACCI_TEXT_POSITION_END == position)
			acciNodeTarget = acciNode;
		else
			retVal = varCmd(&cmdText, acciNodeVar, acciNodeEnd, &acciNodeTarget);

		if(acciNodeTarget && ACCI_NODE_TYPE_END == ACCI_NODE_TYPE_CMD(acciNodeTarget->type))
			break;
    }
    if(!acciNodeTarget){
    	goto err;
    }else{
    	if(ACCI_NODE_TYPE_END == ACCI_NODE_TYPE_CMD(acciNodeTarget->type) && acciNodeTarget->func){
    		acciNodeTarget->func(inBuf);
    		goto end;
    	}else{
    		if(!strcmp(cmdText, acciNodeTarget->name) && &(acciNodeTarget[1]) < acciNodeEnd
    			&& ACCI_NODE_TYPE_END == ACCI_NODE_TYPE_CMD(acciNodeTarget[1].type) && acciNodeTarget[1].func){
    			acciNodeTarget[1].func(inBuf);
    			goto end;
    		}else{
    			goto err;
    		}
    	}
    }
err:
	errPoint(strlen(acciView.head) + (cmdText - buff)/sizeof(char));
	printf(" %% Unrecognized command at \'^\' position.\n");
end:
    fflush(stdout);
    cmdRecord(inBuf);
    acciView.chan = AC_TRUE;
    acciHistory.currentCmd = NULL;
    return AC_OK;
}

AC_STATUS acciLoop(void){
    char c;
    while(1){
        //signal(SIGINT,  _loop_init);
        sigsetjmp(acciEnv, 1);
        acciView.cursor = 0;
        acciHistory.currentCmd = NULL;
        memset(inBuf, 0, sizeof(char)*INPUTBUFLEN);
        printf("%s", acciView.head);
        fflush(stdout);
        while ((c = sGetc()) != '\n') {
			if(0x1B == c){
				c = sGetc();
				if(0x5B == c || 79==c){
					c = sGetc();
					switch (c){
						case 0x33:
							c = sGetc();
							if(0x7e == c)
								handerDelete();
							continue;
							break;
						case KEY_UP:
							handerUp();
							continue;
							break;
						case KEY_DOWN:
							handerDown();
							continue;
							break;
						case KEY_RIGHT:
							handerRight();
							continue;
							break;
						case KEY_LEFT:
							handerLeft();
							continue;
							break;
					}
				}
				continue;
			}
			if(KEY_HELP == c){
			    handerHelp();
			    continue;
			}
			if(c >= 0x20 && c <= 0x7E){
				handerInput(c);
			}else if(KEY_BACKSPACE == c){
				handerBackspace();
			}else if(KEY_DELETE == c){
			    handerDelete();
			}else if(KEY_TAB == c){
				handerTab();
			}
		}
        HIDE_CURSOR();
        //signal(SIGINT,  SIG_IGN);
        if(_EXIT_CLI == handerEnter())
            goto _end;
        SHOW_CURSOR();
        fflush(stdout);
    }
_end:
    return 0;
}

AC_U32 _lo_input(char * buf, AC_U32 len, char mask){
    char c;
    int cursor=0;
    memset(buf, 0, len);
    while ((c = sGetc()) != '\n') {
        if(0x1B == c){
            c = sGetc();
            if(0x5B == c){
                c = sGetc();
                switch (c){
                    case 0x33:
                        c = sGetc();
                        if(0x7e == c){}
                        continue;
                        break;
                    case KEY_UP:
                        continue;
                        break;
                    case KEY_DOWN:
                        continue;
                        break;
                    case KEY_RIGHT:
                        continue;
                        break;
                    case KEY_LEFT:
                        continue;
                        break;
                }
            }
            continue;
        }
        if(c >= 0x20 && c <= 0x7E){
            if(cursor<len-1){
                buf[cursor] = c;
                cursor++;
                if(mask < 0x7f)
                    printf("%c", mask);
                else
                    printf("%c", c);
                fflush(stdout);
            }
        }else if(KEY_BACKSPACE == c){
            if(cursor>0){
                buf[cursor]='\0';
                cursor--;
                if(mask)
                    MOVELEFT(1);
                CLEAR_ROW();
                fflush(stdout);
            }
        }else if(KEY_DELETE == c){
            if(cursor>0){
                buf[cursor]='\0';
                cursor--;
                if(mask)
                    MOVELEFT(1);
                CLEAR_ROW();
                fflush(stdout);
            }
        }else if(KEY_TAB == c){
        }else if(KEY_HELP == c){
        }
    }
    printf("\n");
    return strlen(buf);
}
