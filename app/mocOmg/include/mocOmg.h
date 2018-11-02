#ifndef __MOC_OMG_H__
#define __MOC_OMG_H__
#include "brBoard.h"
#include "brVlan.h"
#include "brPort.h"
#include "acci.h"

typedef enum {
	VIEW_BASIC = 1,
	VIEW_SYSTEM,
	VIEW_CMDHIDE,
	VIEW_VLAN,
	VIEW_VLAN_INTERFACE,
	VIEW_PORT_INTERFACE,
	VIEW_PORT_GROUP,
	VIEW_ACL,
	VIEW_QOS_PROFILE,

	OMG_VIEW_BASIC,
	OMG_VIEW_SYSTEM,
	OMG_VIEW_VLAN,
	OMG_VIEW_VLAN_INTERFACE,
	OMG_VIEW_PORT_INTERFACE,
	OMG_VIEW_PORT_GROUP,
	OMG_VIEW_ACL,
	OMG_VIEW_QOS_PROFILE,
}MOC_VIEW_TYPE;

typedef struct {
    AC_U32 viewID;
    union{
    	AC_U32 content;
    	void * p;
    }content;
}MOC_VIEW_BAK;


void * backPGet(void);
AC_U32 backContentGet(void);
AC_STATUS omgAcciViewQuit(void);
AC_STATUS omgAcciViewEnter(MOC_VIEW_TYPE view, void * p);
#endif
