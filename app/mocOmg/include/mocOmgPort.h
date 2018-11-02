#ifndef __MOC_OMG_PORT_H__
#define __MOC_OMG_PORT_H__
#include "brBoard.h"
#include "brVlan.h"
#include "brPort.h"
#include "acci.h"
AC_STATUS omgDisplayTenGbitEthernetInterface(char * str);
AC_STATUS omgDisplayGbitEthernetInterface(char * str);
AC_STATUS omgDisplayEthernetInterface(char * str);
AC_STATUS omgInterfacePortViewEnter(char * str);
AC_STATUS omgInterfacePortSpeedSet(char * str);
AC_STATUS omgDisplayInterface(char * str);

AC_STATUS omgPortFlowControlEnable(char * str);
AC_STATUS omgPortFlowControlDisable(char * str);
AC_STATUS omgPortJumboFrameEnable(char * str);
AC_STATUS omgPortJumboFrameDisable(char * str);
AC_STATUS omgPortLinkDown(char * str);
AC_STATUS omgPortLinkUp(char * str);

AC_STATUS omgPortAccessVlanSet(char * str);
AC_STATUS omgPortTrunkVlanSet(char * str);
AC_STATUS omgPortHybridVlanSet(char * str);
AC_STATUS omgPortLinkTypeSet(char * str);
AC_STATUS omgPortPvidSet(char * str);

AC_STATUS omgAccessPortVlanUndo(char * str);
AC_STATUS omgTrunkPortVlanUndo(char * str);
AC_STATUS omgHybridPortVlanUndo(char * str);

AC_STATUS omgDebugPortPhyRegOp(char * str);
AC_STATUS omgDebugMacShowAll(char * str);
AC_STATUS omgDebugAclShow(char * str);

#endif
