#include "brBoard.h"
#include "brVlan.h"
#include "brPort.h"
#include "mocOmg.h"
#include "mocOmgVlan.h"
#include "uci_pub.h"

AC_STATUS omgPortListDisplay(AC_U32 portLsit){
	AC_U32 port, n;
	DL_DUMP_HW_PORT hwPort;
	hwPort.hwPort = 1;
	for(port = 1, n = 0; portLsit >>= 1; port++){
		if(1 & portLsit){
			hwPort.hwPort = port;
			brPortDump(&hwPort);
			//printf("     %d%s", hwPort.hwPort, (++n)%3 ? "":"\n");
			printf("    %s %d%s", ethTypeToString(hwPort.ethType), hwPort.hwPort, (++n)%3 ? "":"\n");
		}
	}
	return printf(n ? "\n":"    None\n");
}

AC_STATUS omgVlanDisplay(DL_VLAN * vlan){
	if(vlan){
		printf(" %s %d\n %s %s\n %s %s\n", "VLAN ID:", vlan->vlanID, "Name:", vlan->name.name,
						"Description:",	vlan->description.description);
		printf(" %s\n", "Untagged Ports:");
		omgPortListDisplay(vlan->unTaggedPortList);
		printf(" %s\n", "Tagged Ports:");
		omgPortListDisplay(vlan->taggedPortList);
		printf("\n");
	}else
		printf(" %% The specified VLAN does not exist.\n");
	return AC_OK;
}

AC_STATUS omgDisplayVlan(char * str){
	DL_VLAN vlan;
	DL_STATUS retVal;
	char * vlanIDstr = cmdTk(str, 3, ACCI_TK_CUT);
	vlan.vlanID = vlanIDstr && isAcU32(vlanIDstr) ? strToAcU32(vlanIDstr):0;
	if(vlan.vlanID)
		return omgVlanDisplay(AC_OK == (retVal = brVlanGet(&vlan)) ? &vlan : NULL);
	else
		for(vlan.vlanID = 1; vlan.vlanID<4096; vlan.vlanID++)
			if(AC_OK == brVlanGet(&vlan))
				omgVlanDisplay(&vlan);
	return AC_OK;
}

AC_STATUS omgDisplayInterfaceVlan(char * str){
	DL_VLAN vlan;
	DL_STATUS retVal;
	char * vlanIDstr = cmdTk(str, 4, ACCI_TK_CUT);
	vlan.vlanID = vlanIDstr && isAcU32(vlanIDstr) ? strToAcU32(vlanIDstr):0;
	return omgVlanDisplay(AC_OK == (retVal = brVlanGet(&vlan)) ? &vlan : NULL);
}

AC_STATUS omgVlanViewEnter(char * str){
	AC_U32 vlan, n;
	AC_STATUS retVal;
	char *vlanListStr, *vlanStr;
	vlanListStr = cmdTk(str, 2, ACCI_TK_RES);
	for(n = 0, vlanStr = cmdTk(vlanListStr, 1, ACCI_TK_CUT); vlanStr; vlanStr = cmdTk(NULL, 1, ACCI_TK_CUT), n++){
		vlan = (vlanStr && isAcU32(vlanStr)) ? strToAcU32(vlanStr) : 0;
		if(1 == vlan){
			printf(" %% Can`t config the default vlan.\n");
			return AC_FAIL;
		}
		if(AC_OK != brVlanCreat(vlan)){
			printf(" %% Creat VLAN %s failed.\n", vlanStr);
			return AC_FAIL;
		}
	}
	if(1 == n)
		omgAcciViewEnter(VIEW_VLAN, (void *)(&vlan));
	return AC_OK;
}

AC_STATUS omgInterfaceVlanViewEnter(char * str){
	AC_U32 vlan;
	AC_STATUS retVal;
	char * vlanIDstr = cmdTk(str, 3, ACCI_TK_CUT);
	vlan = vlanIDstr && isAcU32(vlanIDstr) ? strToAcU32(vlanIDstr):0;
	if(1 == vlan){
		printf(" %% Can`t config the default vlan.\n");
		return AC_FAIL;
	}
	return AC_OK == (retVal = brVlanCreat(vlan))
			? omgAcciViewEnter(VIEW_VLAN_INTERFACE, (void *)(&vlan))
			:printf(" %% Creat VLAN %d failed.\n", vlan);
}

AC_STATUS omgVlanUndo(char * str){
	AC_STATUS retVal;
	AC_U32 vlanID;
	char *vlanListStr, *vlanStr;
	vlanListStr = cmdTk(str, 3, ACCI_TK_RES);
	for(vlanStr = cmdTk(vlanListStr, 1, ACCI_TK_CUT); vlanStr; vlanStr = cmdTk(NULL, 1, ACCI_TK_CUT)){
		vlanID = ((vlanStr && isAcU32(vlanStr)) ? strToAcU32(vlanStr) : 0);
		if(1 == vlanID){
			printf(" %% Can`t delete the default vlan.\n");
			return AC_FAIL;
		}
		if(AC_OK != brVlanDelete(vlanID)){
			printf(" %% Delete VLAN %s failed.\n", vlanStr);
			return AC_FAIL;
		}
	}
	return AC_OK;
}

AC_STATUS omgDebugVlanShow(char * str)
{
	AC_U32 vlanId = 0;
	char *pcTmp = cmdTk(str, 4, ACCI_TK_CUT);

	if(pcTmp && isAcU32(pcTmp))
	{
		vlanId = strToAcU32(pcTmp);
	}	
	else
	{
		printf("Invalid parameter!");
		return AC_FAIL;
	}

	Drv_DebugVlanShow(vlanId);
	
	return AC_OK;
}

