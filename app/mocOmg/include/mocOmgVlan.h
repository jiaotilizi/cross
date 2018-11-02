#ifndef __MOC_OMG_VLAN_H__
#define __MOC_OMG_VLAN_H__
#include "brBoard.h"
#include "brVlan.h"
#include "brPort.h"
#include "acci.h"
#include "brAtu.h"
AC_STATUS omgVlanUndo(char * str);
AC_STATUS omgDisplayVlan(char * str);
AC_STATUS omgVlanViewEnter(char * str);
AC_STATUS omgDisplayInterfaceVlan(char * str);
AC_STATUS omgInterfaceVlanViewEnter(char * str);
AC_STATUS omgDebugVlanShow(char * str);
#endif
