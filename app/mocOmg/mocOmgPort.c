#include "brBoard.h"
#include "brVlan.h"
#include "brPort.h"
#include "mocOmg.h"
#include "mocOmgPort.h"
#include "uci_pub.h"

AC_STATUS omgInterfaceDisplay(DL_DUMP_HW_PORT * port, DL_ETH_TYPE ethType){
	AC_U32 m = 0, n = 0;
	if(port && ethType == port->ethType){
		printf(" %s %d, current state: %s\n", ethTypeToString(ethType), port->hwPort, commonStatsToString(port->linkStatusActual));
		printf(" Media mode is %s, actual media type is %s \n", mediaTypeToString(port->mediaType), mediaTypeToString(port->mediaTypeActual));
		printf(" Speed mode is %s, duplex mode is %s \n", speedToString(port->speed), duplexToString(port->duplex));
		printf(" Link speed type is %s, link duplex type is %s \n", speedToString(port->speedActual), duplexToString(port->duplexActual));
		printf(" Flow control mode is %s \n", commonModeToString(port->flowControl));
		printf(" Flow control actual type is %s \n", commonModeToString(port->flowControlActual));
		printf(" Jumbo frame is %s to pass \n", DL_COMMON_MODE_ENABLE == port->jumboFrame ? "allow":"not allow");
		printf(" PVID is %d \n", port->pvid);
		printf(" Port link type is %s \n", portLinkTypeToString(port->vlanPortMode));
		if(DL_VLAN_PORT_MODE_TRUNK == port->vlanPortMode){
			printf("  Vlan passing  : ");
			if(1<<(port->pvid%8) & port->unTagVlanList[(port->pvid/8)]){
				printf("%d\n", port->pvid);
			}else{
				printf("%s\n", "None");
			}
			printf("  Vlan permitted: ");
			for(m = 1, n = 0; m < 4096; m++){
				if((1<<(m%8) & port->unTagVlanList[(m/8)])
					|| (1<<(m%8) & port->tagVlanList[(m/8)])){
					printf("%d, ", m);
					n++;
				}
				printf("%s", n && !(n%8) ? "\n                  ":"");
			}
			printf("%s", n ? "\n":"None\n");
		}else{
			printf("  Tagged   Vlan : ");
			for(m = 1, n = 0; m < 4096; m++){
				if((1<<(m%8) & port->tagVlanList[(m/8)])){
					printf("%d, ", m);
					n++;
				}
				printf("%s", n && !(n%8) ? "\n                  ":"");
			}
			printf("%s", n ? "\n":"None\n");
			printf("  Untagged Vlan : ");
			for(m = 1, n = 0; m < 4096; m++){
				if((1<<(m%8) & port->unTagVlanList[(m/8)])){
					printf("%d, ", m);
					n++;
				}
				printf("%s", n && !(n%8) ? "\n                  ":"");
			}
			printf("%s", n ? "\n":"None\n");
		}
		return printf("\n");
	}else
		return printf(" %% The specified port does not exist.\n");
}

AC_STATUS omgDisplayGbitEthernetInterface(char * str){
	DL_DUMP_HW_PORT port;
	char * portStr = cmdTk(str, 4, ACCI_TK_CUT);
	port.hwPort = portStr && isAcU32(portStr) ? strToAcU32(portStr):0;
	return omgInterfaceDisplay(AC_OK == (brPortDump(&port))? &port : NULL, DL_ETH_TYPE_GIBITETHERNET);
}

AC_STATUS omgDisplayTenGbitEthernetInterface(char * str){
	DL_DUMP_HW_PORT port;
	char * portStr = cmdTk(str, 4, ACCI_TK_CUT);
	port.hwPort = portStr && isAcU32(portStr) ? strToAcU32(portStr):0;
	return omgInterfaceDisplay(AC_OK == (brPortDump(&port))? &port : NULL, DL_ETH_TYPE_TENGIBITETHERNET);
}

AC_STATUS omgDisplayEthernetInterface(char * str){
	DL_DUMP_HW_PORT port;
	char *  portStr = cmdTk(str, 4, ACCI_TK_CUT);
	port.hwPort = portStr && isAcU32(portStr) ? strToAcU32(portStr):0;
	return omgInterfaceDisplay(AC_OK == (brPortDump(&port)) ? &port : NULL, DL_ETH_TYPE_ETHERNET);
}

AC_STATUS omgDisplayInterface(char * str){
	DL_DUMP_HW_PORT port;
	for(port.hwPort = 1; AC_OK == brPortDump(&port); port.hwPort++)
		omgInterfaceDisplay(&port, port.ethType);
	return AC_OK;
}

AC_STATUS omgInterfacePortViewEnter(char * str){
	DL_DUMP_HW_PORT port;
	char *portStr = cmdTk(str, 3, ACCI_TK_CUT);
	port.hwPort = portStr && isAcU32(portStr) ? strToAcU32(portStr):0;
	return AC_OK == (brPortDump(&port))
	? omgAcciViewEnter(VIEW_PORT_INTERFACE, (void *)(&port))
	:printf(" The specified port does not exist.\n");;
}

AC_STATUS omgInterfacePortSpeedSet(char * str){
	DL_DUMP_HW_PORT port;
	AC_U32 speed;
	AC_U32 deplex;
	AC_STATUS retVal;
	char *speedStr = cmdTk(str, 2, ACCI_TK_CUT);
	char *duplexStr = cmdTk(NULL, 2, ACCI_TK_CUT);
	#if 0
	speed = stringToSpeed(speedStr) | stringToDuplex(duplexStr);
	return AC_OK == (retVal = brPortSetSpeed(backContentGet(), speed)) ? retVal
					:printf(" %% %s\n", errString(retVal));
	#else
	speed = stringToSpeed(speedStr);
	deplex = stringToDuplex(duplexStr);
	brPortSetSpeed(backContentGet(), speed);
	brPortSetDuplex(backContentGet(), deplex);
	return AC_OK;
	#endif
}

AC_STATUS omgPortFlowControlEnable(char * str){
	AC_STATUS retVal;
	return AC_OK == (retVal = brPortSetFlowControl(backContentGet(), DL_COMMON_MODE_ENABLE)) ? retVal
			:printf(" %% %s\n", errString(retVal));
}

AC_STATUS omgPortFlowControlDisable(char * str){
	AC_STATUS retVal;
	return AC_OK == (retVal = brPortSetFlowControl(backContentGet(), DL_COMMON_MODE_DISABLE)) ? retVal
			:printf(" %% %s\n", errString(retVal));
}

AC_STATUS omgPortJumboFrameEnable(char * str){
	AC_STATUS retVal;
	return AC_OK == (retVal = brPortSetJumboFrame(backContentGet(), DL_COMMON_MODE_ENABLE)) ? retVal
			:printf(" %% %s\n", errString(retVal));
}

AC_STATUS omgPortJumboFrameDisable(char * str){
	AC_STATUS retVal;
	return AC_OK == (retVal = brPortSetJumboFrame(backContentGet(), DL_COMMON_MODE_DISABLE)) ? retVal
			:printf(" %% %s\n", errString(retVal));
}

AC_STATUS omgPortLinkUp(char * str){
	AC_STATUS retVal;
	return AC_OK == (retVal = brPortSetLink(backContentGet(), DL_COMMON_STATUS_ON)) ? retVal
			:printf(" %% %s\n", errString(retVal));
}

AC_STATUS omgPortLinkDown(char * str){
	AC_STATUS retVal;
	return AC_OK == (retVal = brPortSetLink(backContentGet(), DL_COMMON_STATUS_OFF)) ? retVal
			:printf(" %% %s\n", errString(retVal));
}

AC_STATUS omgPortLinkTypeSet(char * str){
	AC_STATUS retVal;
	DL_VLAN_PORT_MODE linkType = stringToPortLinkType(cmdTk(str, 3, ACCI_TK_CUT));
	retVal = brVlanSetLinkType(backContentGet(), linkType);
	return AC_OK == retVal ? retVal : printf(" %% %s\n", errString(retVal));
}

AC_STATUS omgPortAccessVlanSet(char * str){
	AC_U32 vlanID;
	DL_VLAN vlan;
	AC_STATUS retVal;
	DL_DUMP_HW_PORT port;
	port.hwPort = backContentGet();
	if(AC_OK != brPortDump(&port) || DL_VLAN_PORT_MODE_ACCESS != port.vlanPortMode)
		return printf("This port is not a access port.\n");
	char *vlanStr = cmdTk(str, 4, ACCI_TK_CUT);
	vlanID = (vlanStr && isAcU32(vlanStr)) ? strToAcU32(vlanStr):0;
	vlan.vlanID = vlanID;
	if(AC_OK != brVlanGet(&vlan)){
		printf(" The specified port does not exist.\n");
		return AC_FAIL;
	}
	printf("%s: %d\n", __func__, vlanID);
	retVal = brVlanAddAccessPort(vlanID, backContentGet());
	return retVal;
}

AC_STATUS omgPortTrunkVlanSet(char * str){
	AC_STATUS retVal;
	DL_DUMP_HW_PORT port;
	char * vlanListStr, *vlanStr;
	port.hwPort = backContentGet();
	if(AC_OK != brPortDump(&port) || DL_VLAN_PORT_MODE_TRUNK != port.vlanPortMode)
		return printf(" This port is not a trunk port.\n");
	vlanListStr = cmdTk(str, 5, ACCI_TK_RES);
	for(vlanStr = cmdTk(vlanListStr, 1, ACCI_TK_CUT); vlanStr && isAcU32(vlanStr); vlanStr = cmdTk(NULL, 1, ACCI_TK_CUT))
		retVal = brVlanAddTrunkPort(strToAcU32(vlanStr), backContentGet());
	return retVal;
}

AC_STATUS omgPortHybridVlanSet(char * str){
	AC_STATUS retVal;
	DL_DUMP_HW_PORT port;
	char * vlanListStr, *vlanStr;
	port.hwPort = backContentGet();
	if(AC_OK != brPortDump(&port) || DL_VLAN_PORT_MODE_HYBRID != port.vlanPortMode)
		return printf(" This port is not a hybrid port.\n");
	DL_VLAN_HYBRID_PORT_EGRESS_MODE mode = stringToVlanHybridPortEgressMode(cmdTk(str, 3, ACCI_TK_CUT));
	vlanListStr = (cmdTk(NULL, 2, ACCI_TK_RES));
	for(vlanStr = cmdTk(vlanListStr, 1, ACCI_TK_CUT); vlanStr && isAcU32(vlanStr); vlanStr = cmdTk(NULL, 1, ACCI_TK_CUT))
		retVal = brVlanAddHybridPort(strToAcU32(vlanStr), backContentGet(), mode);
	return retVal;
}

AC_STATUS omgPortPvidSet(char * str){
	AC_STATUS retVal;
	DL_DUMP_HW_PORT port;
	port.hwPort = backContentGet();
	if(AC_OK != brPortDump(&port) || DL_VLAN_PORT_MODE_ACCESS == port.vlanPortMode)
		printf(" This port is not a trunk port or hybrid port.\n");
	char *pvidStr = cmdTk(str, 4, ACCI_TK_CUT);
	AC_U32 pvid = (pvidStr && isAcU32(pvidStr)) ? strToAcU32(pvidStr):0;
	retVal = brVlanSetPvid(backContentGet(), pvid);
	return retVal;
}

AC_STATUS omgAccessPortVlanUndo(char * str){
	AC_STATUS retVal;
	AC_U32 vlanID;
	char *vlanStr;
	vlanStr = cmdTk(str, 5, ACCI_TK_CUT);
	vlanID = ((vlanStr && isAcU32(vlanStr)) ? strToAcU32(vlanStr) : 0);
	if(AC_OK != brVlanDelAccessPort(vlanID, backContentGet())){
		printf(" %% Delete vlan %s failed.\n", vlanStr);
		return AC_FAIL;
	}
	return AC_OK;
}

AC_STATUS omgTrunkPortVlanUndo(char * str){
	AC_STATUS retVal;
	AC_U32 vlanID;
	char *vlanListStr, *vlanStr;
	vlanListStr = cmdTk(str, 6, ACCI_TK_RES);
	for(vlanStr = cmdTk(vlanListStr, 1, ACCI_TK_CUT); vlanStr; vlanStr = cmdTk(NULL, 1, ACCI_TK_CUT)){
		vlanID = ((vlanStr && isAcU32(vlanStr)) ? strToAcU32(vlanStr) : 0);
		if(AC_OK != brVlanDelTrunkPort(vlanID, backContentGet())){
			printf(" %% Delete vlan %s failed.\n", vlanStr);
			return AC_FAIL;
		}
	}
	return AC_OK;
}

AC_STATUS omgHybridPortVlanUndo(char * str){
	AC_STATUS retVal;
	AC_U32 vlanID;
	char *vlanListStr, *vlanStr;
	vlanListStr = cmdTk(str, 5, ACCI_TK_RES);
	for(vlanStr = cmdTk(vlanListStr, 1, ACCI_TK_CUT); vlanStr; vlanStr = cmdTk(NULL, 1, ACCI_TK_CUT)){
		vlanID = ((vlanStr && isAcU32(vlanStr)) ? strToAcU32(vlanStr) : 0);
		if(AC_OK != brVlanDelHybridPort(vlanID, backContentGet())){
			printf(" %% Delete vlan %s failed.\n", vlanStr);
			return AC_FAIL;
		}
	}
	return AC_OK;
}

AC_STATUS omgDebugPortPhyRegOp(char * str)
{
	CFG_PHY_REG_INFO_S stPhyOp;
	AC_U32 lport = 0;
	AC_U32 uiVal = 0;
	char *pcTmp = cmdTk(str, 5, ACCI_TK_CUT);

	memset(&stPhyOp, 0x0, sizeof(stPhyOp));
	if(!strcmp(pcTmp, "read"))
	{
		pcTmp = cmdTk(str, 4, ACCI_TK_CUT);
		if(!strcmp(pcTmp, "phyreg"))
		{
			stPhyOp.enOp = CFG_PHY_PAGE_REG_READ;
		}
		else
		{
			stPhyOp.enOp = CFG_PHY_SERDES_REG_READ;
		}
	}
	else if(!strcmp(pcTmp, "write"))
	{
		pcTmp = cmdTk(str, 4, ACCI_TK_CUT);
		if(!strcmp(pcTmp, "phyreg"))
		{
			stPhyOp.enOp = CFG_PHY_PAGE_REG_WRITE;
		}
		else
		{
			stPhyOp.enOp = CFG_PHY_SERDES_REG_WRITE;
		}
	}	
	else
	{
		return AC_FAIL;
	}
		
	pcTmp = cmdTk(str, 3, ACCI_TK_CUT);
	if(pcTmp && isAcU32(pcTmp))
	{
		lport = strToAcU32(pcTmp);
	}

	pcTmp = cmdTk(str, 7, ACCI_TK_CUT);
	if(pcTmp && isAcU32(pcTmp))
	{
		if(CFG_PHY_PAGE_REG_READ == stPhyOp.enOp ||
			CFG_PHY_PAGE_REG_WRITE == stPhyOp.enOp)
		{
			stPhyOp.uiPhyPage = strToAcU32(pcTmp);
		}
		else
		{
			stPhyOp.uiDevice= strToAcU32(pcTmp);
		}
	}

	pcTmp = cmdTk(str, 9, ACCI_TK_CUT);
	if(pcTmp && (pcTmp[0] == '0') && (pcTmp[1] == 'x' || pcTmp[1] == 'X'))
	{
		sscanf(pcTmp, "%x", &uiVal);
		stPhyOp.usRegAddr = uiVal;
	}
	else if(pcTmp && isAcU32(pcTmp))
	{
		stPhyOp.usRegAddr = strToAcU32(pcTmp);
	}	

	if(CFG_PHY_PAGE_REG_WRITE == stPhyOp.enOp ||
		CFG_PHY_SERDES_REG_WRITE == stPhyOp.enOp)
	{
		pcTmp = cmdTk(str, 11, ACCI_TK_CUT);
		if(pcTmp && (pcTmp[0] == '0') && (pcTmp[1] == 'x' || pcTmp[1] == 'X'))
		{
			sscanf(pcTmp, "%x", &uiVal);
			stPhyOp.usRegData = uiVal;
		}
		else if(pcTmp && isAcU32(pcTmp))
		{
			stPhyOp.usRegData = strToAcU32(pcTmp);
		}
		else
		{
			printf(" Invalid Command! \n");
			return AC_FAIL;
		}
	}

	Drv_DebugPortPhyRegOp(lport, &stPhyOp);
	
	return AC_OK;
}

AC_STATUS omgDebugMacShowAll(char * str)
{
	Drv_DebugShowMacAll();
	
	return AC_OK;
}

AC_STATUS omgDebugAclShow(char * str)
{
	AC_U32 aclDataPoint = 0;
	char *pcTmp = cmdTk(str, 4, ACCI_TK_CUT);

	if(pcTmp && isAcU32(pcTmp))
	{
		aclDataPoint = strToAcU32(pcTmp);
	}	
	else
	{
		printf("Invalid parameter!");
		return AC_FAIL;
	}

	Drv_DebugAclShow(aclDataPoint);
	
	return AC_OK;
}

