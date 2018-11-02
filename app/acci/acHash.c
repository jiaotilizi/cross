#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "acHash.h"

#define AC_HASH_MSG 

static void * acHashElemGetInstance(AC_HASH_TAB ** acHashTable, AC_HASH_ELEM ** elem, void * ins){
    AC_HASH_MSG("%s called. \n", __func__);
    AC_U32 i;
    void * p;
    if(!acHashTable || !(*acHashTable) || !elem || !(*elem) || !ins){
        AC_HASH_MSG("%s : param is invalid. \n", __func__);
        return NULL;
    }
    for(i = 0; i < (*elem)->length; i++){
        p = (*elem)->instance[i];
        if(p && (*acHashTable)->ck && (*acHashTable)->ck(ins, p)){
            AC_HASH_MSG("instance is exsit. \n");
            return ((*elem)->instance[i]);
        }
    }
    AC_HASH_MSG("%s : instance is not exsit. \n", __func__);
    return NULL;
}

static AC_HASH_ELEM ** acHashTableGetElem(AC_HASH_TAB ** acHashTable, void * ins){
    AC_HASH_MSG("%s called. \n", __func__);
    AC_U32 i;
    if(!acHashTable || !(*acHashTable) || !ins){
        AC_HASH_MSG("%s : acHashTable is invalid. \n", __func__);
        return NULL;
    }
    AC_U32 key = (*acHashTable)->hash(ins);
    for(i = 0; i < (*acHashTable)->length; i++){
        if((*acHashTable)->elem[i] && key == (*acHashTable)->elem[i]->elemKey){
            AC_HASH_MSG("Elem %d is exsit. \n", (*acHashTable)->elem[i]->elemKey);
            return &(*acHashTable)->elem[i];
        }
    }
    AC_HASH_MSG("elem is not exsit. \n");
    return NULL;
}

void * acHashTableGetInstance(AC_HASH_TAB ** acHashTable, void * ins){
    AC_HASH_MSG("%s called. \n", __func__);
    if(!acHashTable || !(*acHashTable) || !ins){
        AC_HASH_MSG("%s : param is invalid. \n", __func__);
        return NULL;
    }
    AC_HASH_ELEM ** elem = acHashTableGetElem(acHashTable, ins);
    if(!elem){
        AC_HASH_MSG("acHashTableCreatElem called failed. \n");
        return NULL;
    }
    void * p = acHashElemGetInstance(acHashTable, elem, ins);
    if(!p){
        AC_HASH_MSG("acHashElemGetInstance called failed. \n");
        return NULL;
    }
    AC_HASH_MSG("%s called successfully. \n", __func__);
    return p;
}

static AC_STATUS acHashElemDelInstance(AC_HASH_TAB ** acHashTable, AC_HASH_ELEM ** elem, void * ins){
    AC_HASH_MSG("%s called. \n", __func__);
    AC_U32 i;
    void * p;
    if(!acHashTable || !(*acHashTable) || !elem || !(*elem) || !ins){
        AC_HASH_MSG("%s : param is invalid. \n", __func__);
        return AC_FAIL;
    }
    for(i = 0; i < (*elem)->length; i++){
        p = (*elem)->instance[i];
        if(p && (*acHashTable)->ck && (*acHashTable)->ck(ins, p)){
            AC_HASH_MSG("instance is exsit. \n");
            if((*acHashTable)->destroy){
                (*acHashTable)->destroy(&((*elem)->instance[i]));
            }else{
                free((*elem)->instance[i]);
                (*elem)->instance[i] = NULL;
            }
            (*acHashTable)->count--;
            break;
        }
    }
    AC_HASH_MSG("%s : instance is not exsit. \n", __func__);
    return AC_OK;
}

AC_STATUS acHashTableDeleteInstance(AC_HASH_TAB ** acHashTable, void * ins){
    AC_HASH_MSG("%s called. \n", __func__);
    if(!acHashTable || !(*acHashTable) || !ins){
        AC_HASH_MSG("%s : param is invalid. \n", __func__);
        return AC_FAIL;
    }
    AC_HASH_ELEM ** elem = acHashTableGetElem(acHashTable, ins);
    if(!elem){
        AC_HASH_MSG("acHashTableGetElem called failed. \n");
        return AC_OK;
    }
    return acHashElemDelInstance(acHashTable, elem, ins);
}

static void * acHashElemCreatInstance(AC_HASH_TAB ** acHashTable, AC_HASH_ELEM ** elem, void * ins){
    AC_HASH_MSG("%s called : %d. \n", __func__, (*elem)->elemKey);
    AC_U32 i;
    void * p;
    if(!acHashTable || !(*acHashTable) || !elem || !(*elem) || !ins){
        AC_HASH_MSG("%s : param is invalid. \n", __func__);
        return NULL;
    }
    for(i = 0; i < (*elem)->length; i++){
        p = (*elem)->instance[i];
        if(p && (*acHashTable)->ck && (*acHashTable)->ck(ins, p)){
            AC_HASH_MSG("instance is exsit. \n");
            return &((*elem)->instance[i]);
        }
    }
    AC_HASH_MSG("instance is not exsit. \n");
    for(i = 0; i < (*elem)->length; i++){
        p = (*elem)->instance[i];
        if(!p)
            break;
    }
    if(p && i == (*elem)->length){
        AC_HASH_MSG("elem %d is full. \n", (*elem)->length);
        (*elem) = (AC_HASH_ELEM *)realloc((*elem), sizeof(AC_HASH_ELEM)
                        + sizeof(void *)*(*elem)->length*2);
        if(!(*elem)){
            AC_HASH_MSG("%s called failed : %d. \n", __func__, __LINE__);
            return NULL;
        }
        (*elem)->length *= 2;
        memset(&((*elem)->instance[i]), 0, sizeof(void *)*((*elem)->length-i));
    }else{
        AC_HASH_MSG("elem is not full: %d. \n", (*elem)->length);
    }
    if((*acHashTable)->new){
        p = (*acHashTable)->new(ins);
        if(!p){
            AC_HASH_MSG("%s called failed: %d. \n", __func__, __LINE__);
            return NULL;
        }
    }else{
        p = (void *)malloc((*acHashTable)->size);
        if(!p){
            AC_HASH_MSG("%s called failed: %d. \n", __func__, __LINE__);
            return NULL;
        }
        memset(p, 0, (*acHashTable)->size);
    }
    (*elem)->instance[i] = p;
    (*acHashTable)->count++;
    AC_HASH_MSG("%s called successfully. \n", __func__);
    return ((*elem)->instance[i]);
}

static AC_HASH_ELEM ** acHashTableCreatElem(AC_HASH_TAB ** acHashTable, void * ins){
    AC_HASH_MSG("%s called. \n", __func__);
    AC_U32 i;
    AC_HASH_ELEM *elem;
    AC_U32 key = (*acHashTable)->hash(ins);
    if(!acHashTable || !(*acHashTable) || !ins){
        AC_HASH_MSG("%s : acHashTable is invalid. \n", __func__);
        return NULL;
    }
    for(i=0; i < (*acHashTable)->length; i++){
        elem = (*acHashTable)->elem[i];
        if(elem && elem->elemKey == key){
            AC_HASH_MSG("Key %d is exsit. \n", key);
            return (&(*acHashTable)->elem[i]);
        }
    }
    AC_HASH_MSG("Key %d is not exsit. \n", key);
    for(i=0; i < (*acHashTable)->length; i++){
        elem = (*acHashTable)->elem[i];
        if(!elem)
            break;
    }
    if(elem && i == (*acHashTable)->length){
        AC_HASH_MSG("Hash table is full : %d. \n", (*acHashTable)->length);
        (*acHashTable) = (AC_HASH_TAB *)realloc((*acHashTable), sizeof(AC_HASH_TAB)
                        + sizeof(AC_HASH_ELEM *)*2*(*acHashTable)->length);
        if(!(*acHashTable)){
            AC_HASH_MSG("%s called failed : %d. \n", __func__, __LINE__);
            return NULL;
        }
        (*acHashTable)->length *= 2;
        memset(&((*acHashTable)->elem[i]), 0, sizeof(AC_HASH_ELEM *)*((*acHashTable)->length-i));
    }else{
        AC_HASH_MSG("Hash table is not full : %d. \n", (*acHashTable)->length);
    }
    elem = (AC_HASH_ELEM *)malloc(sizeof(AC_HASH_ELEM)+sizeof(void *));
    if(!(elem)){
        AC_HASH_MSG("%s called failed : %d. \n", __func__, __LINE__);
        return NULL;
    }
    memset(elem, 0, sizeof(AC_HASH_ELEM)+sizeof(void *));
    elem->length = 1;
    elem->elemKey = key;
    (*acHashTable)->elem[i] = elem;
    AC_HASH_MSG("%s called successfully. \n", __func__);
    return &((*acHashTable)->elem[i]);
}

void * acHashTableCreatInstance(AC_HASH_TAB ** acHashTable, void * ins){
    AC_HASH_MSG("%s called. \n", __func__);
    if(!acHashTable || !(*acHashTable) || !ins){
        AC_HASH_MSG("%s : param is invalid. \n", __func__);
        return NULL;
    }
    AC_HASH_ELEM ** elem = acHashTableCreatElem(acHashTable, ins);
    if(!elem){
        AC_HASH_MSG("acHashTableCreatElem called failed. \n");
        return NULL;
    }
    void * p = acHashElemCreatInstance(acHashTable, elem, ins);
    if(!p){
        AC_HASH_MSG("acHashTableVlanCreatVlan called failed. \n");
        return NULL;
    }
    AC_HASH_MSG("%s called successfully. \n", __func__);
    return p;
}

AC_STATUS acHashTableInit(AC_HASH_TAB ** acHashTable, AC_HASH_TAB * templet){
    AC_HASH_MSG("%s called. \n", __func__);
    if(!acHashTable || !templet){
        AC_HASH_MSG("Invalid param in %s: %d. \n", __func__, __LINE__);
        return AC_FAIL;
    }
    (*acHashTable) = (AC_HASH_TAB*)malloc(sizeof(AC_HASH_TAB)+sizeof(AC_HASH_ELEM*));
    if(!(*acHashTable)){
        AC_HASH_MSG("%s called failed : %d. \n", __func__, __LINE__);
        return AC_FAIL;
    }
    memset((*acHashTable), 0, sizeof(AC_HASH_TAB) + sizeof(AC_HASH_ELEM*));
    memcpy((*acHashTable), templet, sizeof(AC_HASH_TAB));
    (*acHashTable)->length = 1;
    AC_HASH_MSG("%s called successfully. \n", __func__);
    return AC_OK;
}


static AC_U32  caseHash(void * ins){
    return ((CASE_HASH *)(ins))->id%16;
}
static AC_BOOL caseCk(void * ins, void * p){
    return ((CASE_HASH *)(ins))->id == ((CASE_HASH *)(p))->id;
}

AC_STATUS acHashTest(void){
    CASE_HASH t;
    CASE_HASH * p;
    AC_HASH_TAB tmp;
    AC_HASH_TAB * table;
    tmp.ck = caseCk;
    tmp.hash = caseHash;
    tmp.new = NULL;
    tmp.destroy = NULL;
    tmp.size = sizeof(CASE_HASH);
	tmp.new = NULL;
	tmp.destroy = NULL;
    acHashTableInit(&table, &tmp);
    do{
        for(t.id = 1; t.id < 4096; t.id++){
            p = (CASE_HASH *)(acHashTableCreatInstance(&table, &t));
            sprintf(p->name, "test name is %d", t.id);
            p->id = t.id;
            printf("acHashTableCreatInstance index %d is %s. \n", p->id, p->name);
        }
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        for(t.id = 1; t.id < 4096; t.id++){
            p = (CASE_HASH *)(acHashTableGetInstance(&table, &t));
            if(p)
                printf("acHashTableGetInstance index %d is %s. \n", p->id, p->name);
            else
                printf("acHashTableGetInstance index %d is not exsit. \n", t.id);
        }
        for(t.id = 1; t.id < 4096; t.id++){
            acHashTableDeleteInstance(&table, &t);
        }
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        for(t.id = 1; t.id < 4096; t.id++){
            p = (CASE_HASH *)(acHashTableGetInstance(&table, &t));
            if(p)
                printf("After delete acHashTableGetInstance index %d is %s. \n", p->id, p->name);
            else
                printf("After delete acHashTableGetInstance index %d is not exsit. \n", t.id);
        }
    }while(1);

    return AC_OK;
}
