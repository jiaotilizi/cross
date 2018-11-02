#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "stdarg.h"
#include "mocOmg.h"
#include "brBoard.h"
#include "brVlan.h"
#include "brPort.h"
#include "acci.h"

#include "mocOmg.h"
#include "mocOmgVlan.h"
#include "mocOmgPort.h"

static AC_STATUS omgSystemViewEnter(char * str){
	return omgAcciViewEnter(VIEW_SYSTEM, NULL);
}

static AC_STATUS omgCmdHideViewEnter(char * str){
	return omgAcciViewEnter(VIEW_CMDHIDE, NULL);
}

static AC_STATUS omgAnyViewQuit(char * str){
	return omgAcciViewQuit();
}

static AC_STATUS displayCmd(char * str){
    return printf("%s \n", str);
}

static AC_STATUS omgDisplayTerminal(char * str){
	return displayTerminal();
}

static AC_STATUS ckPortID(char * cmd){
    return cmd && strlen(cmd)>0 && AC_TRUE != isAcU16(cmd) ? AC_FAIL : AC_OK;
}

static AC_STATUS ckVlanID(char * cmd){
    return cmd && strlen(cmd)>0 && AC_TRUE != isAcU16(cmd) ? AC_FAIL : AC_OK;
}

static AC_STATUS ckVlanList(char * cmd){
	char * cmdBuf = (char *)malloc((((strlen(cmd)/4) + 1) * 4));
	memset(cmdBuf, 0, (((strlen(cmd)/4) + 1) * 4));
	strcpy(cmdBuf, cmd);
	//AC_U32 i, vlan;
	char * vlanStr;
	for(vlanStr = cmdTk(cmdBuf, 1, ACCI_TK_CUT); vlanStr; vlanStr = cmdTk(NULL, 1, ACCI_TK_CUT)){
		if(AC_FAIL == ckVlanID(vlanStr)){
			free(cmdBuf);
			return AC_FAIL;
		}
	}
	free(cmdBuf);
	return AC_OK;
}

#if 0
static ACCI_NODE omgAcciNodesDisplay[] = {
				ACCINODEADD(1, "display",  "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(2, "terminal", "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(3, "<cr1>",     "", omgDisplayTerminal, ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),

				ACCINODEADD(2, "interface", "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),

				ACCINODEADD(3, "GibitEthernet", "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_0C1),
				ACCINODEADD(4, "<port>", "display terminal configuration", ckPortID, ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_0T1),
				ACCINODEADD(4, "<cr2>",     "", omgDisplayGbitEthernetInterface, ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),

				ACCINODEADD(3, "vlan", "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_0C1),
				ACCINODEADD(4, "<vlan-id>", "display terminal configuration", ckPortID, ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_0T1),
				ACCINODEADD(4, "<cr3>",     "", omgDisplayInterfaceVlan, ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(3, "<cr4>",     "", omgDisplayInterfaceVlan, ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),

				ACCINODEADD(2, "vlan", "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_0C1),
				ACCINODEADD(3, "<vlan-id>", "display terminal configuration", ckPortID, ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_0T1),

				ACCINODEADD(3, "<cr5>",     "", omgDisplayVlan, ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
};
static ACCI_NODE omgAcciNodesPortLinkType [] = {
				ACCINODEADD(1, "link-type",     "", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(2, "access",     "", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(3, "vlan",     "", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(4, "<vlan-id>",     "", NULL, ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_0T1),
				ACCINODEADD(4, "<cr4>",    "",                 displayCmd,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(3, "<cr3>",    "",                 displayCmd,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),

				ACCINODEADD(2, "trunk",     "", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(3, "pvid_t",     "", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(4, "<vlan-id_t>",     "", NULL, ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(3, "permit_t",     "", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(4, "vlan_t",     "", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(5, "to_t",     "", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(3, "<cr>",    "",                 displayCmd,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),

				ACCINODEADD(2, "hybrid",     "", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(3, "<cr>",    "",                 displayCmd,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
};
#else

static ACCI_NODE omgAcciNodesDisplay[] = {
				ACCINODEADD(1, "display",  "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
              ACCINODEADD(2, "terminal", "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
              ACCINODEADD(3, "<cr>",     "", omgDisplayTerminal, ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
              ACCINODEADD(2, "interface", "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
              ACCINODEADD(3, "all", "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
              ACCINODEADD(4, "<cr>",     "", omgDisplayInterface, ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
              ACCINODEADD(3, "GibitEthernet", "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
              ACCINODEADD(4, "<port>", "display terminal configuration", ckPortID, ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
              ACCINODEADD(5, "<cr>",     "", omgDisplayGbitEthernetInterface, ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
              ACCINODEADD(2, "vlan", "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
              ACCINODEADD(3, "<vlan-id>", "display terminal configuration", ckPortID, ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
              ACCINODEADD(3, "all", "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
              ACCINODEADD(4, "<cr>",     "", omgDisplayVlan, ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
              ACCINODEADD(2, "mac-adress", "display mac adress tables", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
              ACCINODEADD(3, "<cr>",     "", omgDebugMacShowAll, ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
};

static ACCI_NODE omgAcciNodesDebugPortPhyRegCmd [] = {
	  ACCINODEADD(1, "debugport",  "debug port command", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
	  ACCINODEADD(2, "port", "port command", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
	  ACCINODEADD(3, "<port>", "port num", ckPortID, ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
	  ACCINODEADD(4, "phyreg", "phy register", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
	  ACCINODEADD(4, "serdes-phyreg", "serdes phy register", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
	  ACCINODEADD(5, "read", "read phy reg", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
	  ACCINODEADD(5, "write", "write phy reg", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
	  ACCINODEADD(6, "page", "read phy reg page num", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
	  ACCINODEADD(6, "device", "read serdes phy device", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
	  ACCINODEADD(7, "<page_num>", "page num", NULL, ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
	  ACCINODEADD(7, "<device_num>", "device num", NULL, ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
	  ACCINODEADD(8, "reg", "register", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
	  ACCINODEADD(9, "<register_addr>", "register addr", NULL, ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
	  ACCINODEADD(10, "<cr>",	 "", omgDebugPortPhyRegOp, ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
	  ACCINODEADD(10, "data", "register data", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
	  ACCINODEADD(11, "<reg_data>", "register data to be set", NULL, ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
	  ACCINODEADD(12, "<cr>",	 "", omgDebugPortPhyRegOp, ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),	  
};

static ACCI_NODE omgAcciNodesDebugVlanShowCmd [] = {
	  ACCINODEADD(1, "debugvlan",  "debug vlan command", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
   	  ACCINODEADD(2, "show",  "debug show infomation", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
	  ACCINODEADD(3, "vlan", "specify vlan", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
	  ACCINODEADD(4, "<vlan_id>", "vlan index", ckVlanID, ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
	  ACCINODEADD(5, "<cr>",	 "", omgDebugVlanShow, ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),	  
};

static ACCI_NODE omgAcciNodesDebugAclShowCmd [] = {
	  ACCINODEADD(1, "debugacl",  "debug acl command", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
   	  ACCINODEADD(2, "show",  "debug show infomation", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
	  ACCINODEADD(3, "datapoint", "specify acl datapoint", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
	  ACCINODEADD(4, "<acl_index>", "acl datapoint index", ckVlanID, ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
	  ACCINODEADD(5, "<cr>",	 "", omgDebugAclShow, ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),	  
};

static ACCI_NODE omgAcciNodesPortLinkType [] = {
				ACCINODEADD(1, "port",     "", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(2, "link-type",     "", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(3, "access",     "", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(3, "trunk",     "", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(3, "hybrid",     "", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(4, "<cr>",    "",     omgPortLinkTypeSet,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
};

static ACCI_NODE omgAcciNodesPvidSet [] = {
				ACCINODEADD(1, "pvid",     "", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(2, "<vlan-id>",     "", ckVlanID, ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(3, "<cr>",    "",   omgPortPvidSet,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
};

static ACCI_NODE omgAcciNodesPortVlanMode [] = {
				ACCINODEADD(1, "port",     "", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),

				ACCINODEADD(2, "link-type",     "", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(3, "access",     "", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(3, "trunk",     "", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(3, "hybrid",     "", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(4, "<cr>",    "",     omgPortLinkTypeSet,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),

				ACCINODEADD(2, "access",     "", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(3, "vlan",     "", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(4, "<vlan>",     "", ckVlanID, ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(5, "<cr>",    "",                 omgPortAccessVlanSet,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),

				ACCINODEADD(2, "trunk",     "", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(3, "pvid",     "", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(4, "<vlan-id>",     "", ckVlanID, ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(5, "<cr>",    "",   omgPortPvidSet,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(3, "permit",     "", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(4, "vlan",     "", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1 | ACCI_NODE_TYPE_DESCIRPITON),
				ACCINODEADD(5, "<vlan>",     "", ckVlanList, ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(6, "<cr>",    "",                 omgPortTrunkVlanSet,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),

				ACCINODEADD(2, "hybrid",     "", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(3, "pvid",     "", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(4, "<vlan-id>",     "", ckVlanID, ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(5, "<cr>",    "",   omgPortPvidSet,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(3, "tagged",     "", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(3, "unTagged",     "", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(4, "vlan",     "", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1 | ACCI_NODE_TYPE_DESCIRPITON),
				ACCINODEADD(5, "<vlan>",     "", ckVlanList, ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(6, "<cr>",    "",                 omgPortHybridVlanSet,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
};

#endif

static ACCI_NODE omgAcciNodesSystemView [] = {
				ACCINODEADD(1, "system-view",  "enter system view to continue", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(2, "<cr>",     "", omgSystemViewEnter, ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
};

static ACCI_NODE omgAcciNodesCmdHideView [] = {
				ACCINODEADD(1, "_hide",  "enter hide command line mode", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(2, "<cr>",     "", omgCmdHideViewEnter, ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
};

static ACCI_NODE omgAcciNodesViewQuit [] = {
				ACCINODEADD(1, "quit",  "enter system view to continue", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(2, "<cr>",     "", omgAnyViewQuit, ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
};

static ACCI_NODE omgAcciNodesInterface[] = {
				ACCINODEADD(1, "interface",  "enter a interface view", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(2, "GibitEthernet", "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(3, "<port>", "display terminal configuration", ckPortID, ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(4, "<cr>",     "", omgInterfacePortViewEnter, ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(2, "vlan", "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(3, "<vlan-id>", "display terminal configuration", ckPortID, ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(4, "<cr>",     "", omgInterfaceVlanViewEnter, ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
};

static ACCI_NODE omgAcciNodesVlan[] = {
				ACCINODEADD(1, "vlan", "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1 | ACCI_NODE_TYPE_DESCIRPITON),
				ACCINODEADD(2, "<vlan-id>", "display terminal configuration", ckVlanList, ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
				//ACCINODEADD(2, "all", "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(3, "<cr>",     "", omgVlanViewEnter, ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
};

static ACCI_NODE omgAcciNodesRule[] = {
				ACCINODEADD(1, "rule",                 "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "<rule-id>",            "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "permit",               "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "deny",                 "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "source",               "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "<source-addr>",        "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "<source-wildcard>",    "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "any",                  "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "time-range",           "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "<time-name>",          "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "fragment",             "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "logging",              "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "<cr>",                 "", displayCmd, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
};

static ACCI_NODE omgAcciNodeslldp[] = {
				ACCINODEADD(1, "lldp",                 "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "tlv-enable",           "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "basic-tlv",            "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "all",                  "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "port-description",     "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "system-capability",    "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "system-description",   "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "system-name",          "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "dot1-tlv",             "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "all",                  "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "port-vlan-id",         "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "protocol-vlan-id",     "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "<vlan-id>",            "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "vlan-name",            "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "<vlan-id>",            "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "dot3-tlv",             "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "all",                  "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "link-aggregation",     "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "mac-physic",           "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "max-frame-size",       "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "power",                "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "med-tlv",              "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "all",                  "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "capability",           "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "inventory",            "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "location-id",          "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "civic-address",        "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "<device-type>",        "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "<country-code>",       "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "<ca-type>",            "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "<ca-value>",           "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "elin-address",         "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "<tel-number>",         "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "network-policy",       "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "power-over-ethernet",  "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "<cr>",                 "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
};


static ACCI_NODE omgAcciNodesRedirect[] = {
				ACCINODEADD(1, "redirect",             "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "cpu",                  "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "<cr>",                 "", displayCmd, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "interface",            "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "<interface-type>",     "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "<interface-number>",   "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "<cr>",                 "", displayCmd, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "link-aggregation",     "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "group",                "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "<group-id>",           "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "<cr>",                 "", displayCmd, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "next-hop",             "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "<ipv4-add>",           "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "<cr>",                 "", displayCmd, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "<ipv4-add>",           "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "<cr>",                 "", displayCmd, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "<ipv6-add>",           "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "<cr>",                 "", displayCmd, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "<interface-type>",     "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "<interface-number>",   "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "<cr>",                 "", displayCmd, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "<ipv6-add>",           "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "<cr>",                 "", displayCmd, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "<interface-type>",     "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "<interface-number>",   "display terminal configuration", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(1, "<cr>",                 "", displayCmd, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
};

static AC_STATUS ckRuleId(char * cmd){
    return(!cmd || (strlen(cmd)>0 && AC_TRUE != isAcU16(cmd))) ? AC_FAIL:AC_OK;
}
static AC_STATUS ckProtocol(char * cmd){
    return(!cmd || (strlen(cmd)>0 && AC_TRUE != isAcU16(cmd))) ? AC_FAIL:AC_OK;
}

static ACCI_NODE omgAcciNodesAdvanceRule[] = {
				ACCINODEADD(1, "rule",                 "display terminal configuration", NULL,          ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(2, "INTEGER<0-65535>",     "display terminal configuration", ckRuleId,      ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_0T1),
				ACCINODEADD(3, "permit",               "display terminal configuration", NULL,          ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(3, "deny",                 "display terminal configuration", NULL,          ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(4, "INTEGER<1-255>",       "display terminal configuration", ckProtocol,    ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(4, "icmp",                 "display terminal configuration", NULL,          ACCI_NODE_TYPE_OPT | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(4, "igmp",                 "display terminal configuration", NULL,          ACCI_NODE_TYPE_OPT | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(4, "gre",                  "display terminal configuration", NULL,          ACCI_NODE_TYPE_OPT | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(4, "ip",                   "display terminal configuration", NULL,          ACCI_NODE_TYPE_OPT | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(4, "ipinip",               "display terminal configuration", NULL,          ACCI_NODE_TYPE_OPT | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(4, "tcp",                  "display terminal configuration", NULL,          ACCI_NODE_TYPE_OPT | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(4, "udp",                  "display terminal configuration", NULL,          ACCI_NODE_TYPE_OPT | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(4, "ospf",                 "display terminal configuration", NULL,          ACCI_NODE_TYPE_OPT | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(5, "destnation",           "display terminal configuration", NULL,          ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_0TN),
				ACCINODEADD(6, "<dest-addr>",          "display terminal configuration", NULL,          ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(7, "<dest-wildcard>",      "display terminal configuration", NULL,          ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
				//ACCINODEADD(8, "<cr>",                 "",                               displayCmd,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(6, "any",                  "display terminal configuration", NULL,          ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				//ACCINODEADD(7, "<cr>",                 "",                               displayCmd,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(5, "destnation-port",      "display terminal configuration", NULL,          ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_0TN),
				ACCINODEADD(6, "<operator>",           "display terminal configuration", NULL,          ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(7, "<port1>",              "display terminal configuration", NULL,          ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
				//ACCINODEADD(8, "<cr>",                 "",                               displayCmd,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(8, "<port2>",              "display terminal configuration", NULL,          ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_0T1),
				//ACCINODEADD(9, "<cr>",                 "",                               displayCmd,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(5, "dscp",                 "display terminal configuration", NULL,          ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_0TN),
				ACCINODEADD(6, "<dscp>",               "display terminal configuration", NULL,          ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
				//ACCINODEADD(7, "<cr>",                 "",                               displayCmd,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(5, "established",          "display terminal configuration", NULL,          ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_0TN),
				//ACCINODEADD(6, "<cr>",                 "",                               displayCmd,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(5, "fragment",             "display terminal configuration", NULL,          ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_0TN),
				//ACCINODEADD(6, "<cr>",                 "",                               displayCmd,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(5, "icmp-type",            "display terminal configuration", NULL,          ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_0TN),
				ACCINODEADD(6, "<icmp-type>",          "display terminal configuration", NULL,          ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(7, "<icmp-code>",          "display terminal configuration", NULL,          ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
				//ACCINODEADD(8, "<cr>",                 "",                               displayCmd,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(6, "<icmp-message>",       "display terminal configuration", NULL,          ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
				//ACCINODEADD(7, "<cr>",                 "",                               displayCmd,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(5, "logging",              "display terminal configuration", NULL,          ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_0TN),
				//ACCINODEADD(6, "<cr>",                 "",                               displayCmd,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(5, "precedence",           "display terminal configuration", NULL,          ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_0TN),
				ACCINODEADD(6, "<precedence>",         "display terminal configuration", NULL,          ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
				//ACCINODEADD(7, "<cr>",                 "",                               displayCmd,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(5, "reflective",           "display terminal configuration", NULL,          ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_0TN),
				//ACCINODEADD(6, "<cr>",                 "",                               displayCmd,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(5, "source",               "display terminal configuration", NULL,          ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_0TN),
				ACCINODEADD(6, "<source-addr>",        "display terminal configuration", NULL,          ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(7, "<source-wildcard>",    "display terminal configuration", NULL,          ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
				//ACCINODEADD(8, "<cr>",                 "",                               displayCmd,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(6, "any",                  "display terminal configuration", NULL,          ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				//ACCINODEADD(7, "<cr>",                 "",                               displayCmd,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(5, "source-port",          "display terminal configuration", NULL,          ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_0TN),
				ACCINODEADD(6, "<operator>",           "display terminal configuration", NULL,          ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(7, "<port1>",              "display terminal configuration", NULL,          ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
				//ACCINODEADD(8, "<cr>",                 "",                               displayCmd,    ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(8, "<port2>",              "display terminal configuration", NULL,          ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_0T1),
				//ACCINODEADD(9, "<cr>",                 "",                               displayCmd,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(5, "time-range",           "display terminal configuration", NULL,          ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_0TN),
				ACCINODEADD(6, "<time-name>",          "display terminal configuration", NULL,          ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
				//ACCINODEADD(7, "<cr>",                 "",                               displayCmd,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(5, "tos",                  "display terminal configuration", NULL,          ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_0TN),
				ACCINODEADD(6, "<tos>",                "display terminal configuration", NULL,          ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(5, "<cr>",                 "",                               displayCmd,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_0TN),
};

static ACCI_NODE omgAcciNodesInterfacePortUndo [] = {
				ACCINODEADD(1, "undo", "enter system view to continue", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(2, "jumboframe",  "enter system view to continue", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(3, "<cr>",    "",                 omgPortJumboFrameDisable,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(2, "flow-control",  "enter system view to continue", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(3, "<cr>",    "",                 omgPortFlowControlDisable,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(2, "port",  "enter system view to continue", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(3, "access",  "enter system view to continue", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(4, "vlan",  "enter system view to continue", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(5, "<vlan-id>",    "",                 ckVlanID,    ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(6, "<cr>",    "",                 omgAccessPortVlanUndo,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(3, "trunk",  "enter system view to continue", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1 ),
				ACCINODEADD(4, "permit",  "enter system view to continue", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(5, "vlan",  "enter system view to continue", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1 | ACCI_NODE_TYPE_DESCIRPITON),
				ACCINODEADD(6, "<vlan-id>",    "",                 ckVlanList,    ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(7, "<cr>",    "",                 omgTrunkPortVlanUndo,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(3, "hybrid",  "enter system view to continue", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(4, "vlan",  "enter system view to continue", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1 | ACCI_NODE_TYPE_DESCIRPITON),
				ACCINODEADD(5, "<vlan-id>",    "",                 ckVlanList,    ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(6, "<cr>",    "",                 omgHybridPortVlanUndo,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
};

static ACCI_NODE omgAcciNodesGibitPortSpeed [] = {
				ACCINODEADD(1, "speed", "enter system view to continue", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(2, "auto", "", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(2, "1000Mbps",     "", NULL, ACCI_NODE_TYPE_OPT | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(3, "<cr>",                 "",                               omgInterfacePortSpeedSet,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(2, "100Mbps",     "", NULL, ACCI_NODE_TYPE_OPT | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(2, "10Mbps",     "", NULL, ACCI_NODE_TYPE_OPT | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(3, "duplex",                 "",                               NULL,    ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(4, "full-duplex",     "", NULL, ACCI_NODE_TYPE_OPT | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(4, "half-duplex",     "", NULL, ACCI_NODE_TYPE_OPT | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(5, "<cr>",                 "",                               omgInterfacePortSpeedSet,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
};

static ACCI_NODE omgAcciNodesPortJumboFrameEnable [] = {
				ACCINODEADD(1, "jumboframe",  "enter system view to continue", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(2, "enable",     "", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(3, "<cr>",    "",                 omgPortJumboFrameEnable,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
};

static ACCI_NODE omgAcciNodesFlowControlEnable [] = {
				ACCINODEADD(1, "flow-control",  "enter system view to continue", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(2, "enable",     "", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(3, "<cr>",    "",                 omgPortFlowControlEnable,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
};

static ACCI_NODE omgAcciNodesSystemViewUndo [] = {
				ACCINODEADD(1, "undo", "enter system view to continue", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(2, "vlan",  "enter system view to continue", NULL, ACCI_NODE_TYPE_CMD | ACCI_NODE_TYPE_ON1 | ACCI_NODE_TYPE_DESCIRPITON),
				ACCINODEADD(3, "<vlan-id>",    "",                 ckVlanList,    ACCI_NODE_TYPE_PAR | ACCI_NODE_TYPE_ON1),
				ACCINODEADD(4, "<cr>",    "",                 omgVlanUndo,    ACCI_NODE_TYPE_END | ACCI_NODE_TYPE_ON1),
};

static ACCI_CMD omgAcciCmdsBasicView[] = {
        ACCICMDSADD(omgAcciNodesDisplay),
        ACCICMDSADD(omgAcciNodesViewQuit),
        ACCICMDSADD(omgAcciNodesSystemView),
};
static ACCI_LIST omgAcciViewBasic []= {ACCILISTADD(omgAcciCmdsBasicView),};

static ACCI_CMD omgAcciCmdsSystemView[] = {
        ACCICMDSADD(omgAcciNodesDisplay),
        ACCICMDSADD(omgAcciNodesViewQuit),
        ACCICMDSADD(omgAcciNodesInterface),
        ACCICMDSADD(omgAcciNodesVlan),
        ACCICMDSADD(omgAcciNodesSystemViewUndo),
        ACCICMDSADD(omgAcciNodesCmdHideView),
};
static ACCI_LIST omgAcciViewSystem []= {ACCILISTADD(omgAcciCmdsSystemView),};

static ACCI_CMD omgAcciCmdsCmdHide[] = {
        ACCICMDSADD(omgAcciNodesDebugPortPhyRegCmd),
		ACCICMDSADD(omgAcciNodesDebugVlanShowCmd),
		ACCICMDSADD(omgAcciNodesDebugAclShowCmd),
		ACCICMDSADD(omgAcciNodesViewQuit),
};
static ACCI_LIST omgAcciViewCmdHide []= {ACCILISTADD(omgAcciCmdsCmdHide),};

static ACCI_CMD omgAcciCmdsInterfacePortView[] = {
        ACCICMDSADD(omgAcciNodesDisplay),
        ACCICMDSADD(omgAcciNodesGibitPortSpeed),
        //ACCICMDSADD(omgAcciNodesPortLinkType),
        ACCICMDSADD(omgAcciNodesPortVlanMode),
        //ACCICMDSADD(omgAcciNodesPvidSet),
        ACCICMDSADD(omgAcciNodesPortJumboFrameEnable),
        ACCICMDSADD(omgAcciNodesFlowControlEnable),
        ACCICMDSADD(omgAcciNodesInterfacePortUndo),
        ACCICMDSADD(omgAcciNodesViewQuit),
};
static ACCI_LIST omgAcciViewInterfacePort []= {ACCILISTADD(omgAcciCmdsInterfacePortView),};

static ACCI_CMD omgAcciCmdsVlanView[] = {
        ACCICMDSADD(omgAcciNodesDisplay),
        ACCICMDSADD(omgAcciNodesViewQuit),
};
static ACCI_LIST omgAcciViewVlan []= {ACCILISTADD(omgAcciCmdsVlanView),};

static ACCI_CMD omgAcciCmdsInterfaceVlanView[] = {
        ACCICMDSADD(omgAcciNodesDisplay),
        ACCICMDSADD(omgAcciNodesViewQuit),
};
static ACCI_LIST omgAcciViewInterfaceVlan []= {ACCILISTADD(omgAcciCmdsInterfaceVlanView),};

static ACCI_CMD omgAcciCmdsPortGroupView[] = {
        ACCICMDSADD(omgAcciNodesDisplay),
        ACCICMDSADD(omgAcciNodesViewQuit),
};
static ACCI_LIST omgAcciViewPortGroup []= {ACCILISTADD(omgAcciCmdsPortGroupView),};

static ACCI_CMD omgAcciCmdsAclView[] = {
        ACCICMDSADD(omgAcciNodesDisplay),
        ACCICMDSADD(omgAcciNodesViewQuit),
        ACCICMDSADD(omgAcciNodesAdvanceRule),
};
static ACCI_LIST omgAcciViewAcl []= {ACCILISTADD(omgAcciCmdsAclView),};

static ACCI_CMD omgAcciCmdsQosProfileView[] = {
        ACCICMDSADD(omgAcciNodesDisplay),
        ACCICMDSADD(omgAcciNodesViewQuit),
};
static ACCI_LIST omgAcciViewQosProfile []= {ACCILISTADD(omgAcciCmdsQosProfileView),};

static ACCI_VIEW acciViewTable [] = {
#define VIEW_DEF(_view, _acciview) [_view] = {.acciList = _acciview, .chan = AC_TRUE, .cursor = 0, }
				VIEW_DEF(VIEW_BASIC, omgAcciViewBasic),
				VIEW_DEF(VIEW_SYSTEM, omgAcciViewSystem),
				VIEW_DEF(VIEW_CMDHIDE, omgAcciViewCmdHide),
				VIEW_DEF(VIEW_VLAN, omgAcciViewVlan),
				VIEW_DEF(VIEW_VLAN_INTERFACE, omgAcciViewInterfaceVlan),
				VIEW_DEF(VIEW_PORT_INTERFACE, omgAcciViewInterfacePort),
				VIEW_DEF(VIEW_PORT_GROUP, omgAcciViewPortGroup),
				VIEW_DEF(VIEW_ACL, omgAcciViewAcl),
				VIEW_DEF(VIEW_QOS_PROFILE, omgAcciViewQosProfile),

				VIEW_DEF(OMG_VIEW_BASIC, omgAcciViewBasic),
				VIEW_DEF(OMG_VIEW_SYSTEM, omgAcciViewSystem),
				VIEW_DEF(OMG_VIEW_VLAN, omgAcciViewVlan),
				VIEW_DEF(OMG_VIEW_VLAN_INTERFACE, omgAcciViewInterfaceVlan),
				VIEW_DEF(OMG_VIEW_PORT_INTERFACE, omgAcciViewInterfacePort),
				VIEW_DEF(OMG_VIEW_PORT_GROUP, omgAcciViewPortGroup),
				VIEW_DEF(OMG_VIEW_ACL, omgAcciViewAcl),
				VIEW_DEF(OMG_VIEW_QOS_PROFILE, omgAcciViewQosProfile),
};

static MOC_VIEW_BAK back;

AC_STATUS omgAcciViewEnter(MOC_VIEW_TYPE view, void * p){
	switch(view){
		case VIEW_BASIC:
			sprintf(acciViewTable[view].head, "%s", p ? (char *)(p):"<Switch> ");
			break;
		case VIEW_SYSTEM:
			sprintf(acciViewTable[view].head, "%s", p ? (char *)(p):"[Switch] ");
			break;
		case VIEW_CMDHIDE:
			sprintf(acciViewTable[view].head, "%s", p ? (char *)(p):"[Switch_hidecmd] ");
			break;			
		case VIEW_VLAN:
			sprintf(acciViewTable[view].head, "[Switch-vlan %d] ", *((AC_U32 *)(p)));
			back.content.content = *((AC_U32 *)(p));
			break;
		case VIEW_VLAN_INTERFACE:
			sprintf(acciViewTable[view].head, "[Switch-vlan-interface %d] ", *(AC_U32 *)(p));
			back.content.content = *((AC_U32 *)(p));
			break;
		case VIEW_PORT_INTERFACE:
			sprintf(acciViewTable[view].head, "[Switch-%s/%d] ",
			ethTypeToString(((DL_DUMP_HW_PORT *)(p))->ethType), ((DL_DUMP_HW_PORT *)(p))->hwPort);
			back.content.content = ((DL_DUMP_HW_PORT *)(p))->hwPort;
			break;
		case VIEW_PORT_GROUP:
			sprintf(acciViewTable[view].head, "[Switch-PortGroup %d] ", *(AC_U32 *)(p));
			back.content.content = *((AC_U32 *)(p));
			break;
		case VIEW_ACL:
			sprintf(acciViewTable[view].head, "[Switch] ");
			break;
		case VIEW_QOS_PROFILE:
			sprintf(acciViewTable[view].head, "[Switch] ");
			break;
		case OMG_VIEW_SYSTEM:
			sprintf(acciViewTable[view].head, "[OMG] ");
			break;
		case OMG_VIEW_VLAN:
			sprintf(acciViewTable[view].head, "[OMG-vlan %d] ", *(AC_U32 *)(p));
			back.content.content = *((AC_U32 *)(p));
			break;
		case OMG_VIEW_VLAN_INTERFACE:
			sprintf(acciViewTable[view].head, "[OMG-vlan-interface %d] ", *(AC_U32 *)(p));
			back.content.content = *((AC_U32 *)(p));
			break;
		case OMG_VIEW_PORT_INTERFACE:
			sprintf(acciViewTable[view].head, "[OMG-%s/%d] ",
			ethTypeToString(((DL_DUMP_HW_PORT *)(p))->ethType), ((DL_DUMP_HW_PORT *)(p))->hwPort);
			back.content.content = ((DL_DUMP_HW_PORT *)(p))->hwPort;
			break;
		case OMG_VIEW_PORT_GROUP:
			sprintf(acciViewTable[view].head, "[OMG-PortGroup %d] ", *(AC_U32 *)(p));
			back.content.content = *((AC_U32 *)(p));
			break;
		case OMG_VIEW_ACL:
			sprintf(acciViewTable[view].head, "[OMG] ");
			break;
		case OMG_VIEW_QOS_PROFILE:
			sprintf(acciViewTable[view].head, "[OMG] ");
			break;
		case OMG_VIEW_BASIC:
		default:
			sprintf(acciViewTable[OMG_VIEW_BASIC].head, "<OMG> ");
			back.viewID = OMG_VIEW_BASIC;
			return viewInit(&(acciViewTable[OMG_VIEW_BASIC]));
			break;
	}
	back.viewID = view;
	return viewInit(&(acciViewTable[view]));
}

AC_STATUS omgAcciViewQuit(void){
	switch(back.viewID){
		case VIEW_BASIC:
		case VIEW_SYSTEM:
			return omgAcciViewEnter(VIEW_BASIC, NULL);
		case VIEW_VLAN:
		case VIEW_VLAN_INTERFACE:
		case VIEW_PORT_INTERFACE:
		case VIEW_PORT_GROUP:
		case VIEW_ACL:
		case VIEW_QOS_PROFILE:
		case VIEW_CMDHIDE:
			return omgAcciViewEnter(VIEW_SYSTEM, NULL);
		case OMG_VIEW_SYSTEM:
		case OMG_VIEW_BASIC:
		default:
			return omgAcciViewEnter(OMG_VIEW_BASIC, NULL);
	}
}

AC_U32 backContentGet(void){
	return back.content.content;
}

void * backPGet(void){
	return back.content.p;
}
