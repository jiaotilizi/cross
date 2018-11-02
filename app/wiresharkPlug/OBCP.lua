do

local enable = {
	[1] = "Enabled",
	[0] = "Disabled",}

OBCP = Proto ("OBCP","OBCP","OB Control Protocol--OBCP")
---字符倒转
function reverse(str)
	local swap_str = tostring(str)
	local new_str = ""
	for i = 0,str:len()-2,2
	do
		new_str = string.sub(swap_str,1+i,2+i) .. new_str
	end
	return new_str
end

---buffer倒转
function le_buffers(str)
	local new_str = ""
	for i = 0,str:len()-1,1
	do
		new_str = str(i,1) .. new_str
	end
	return new_str
end

---字符倒转，16进制转10进制
function str_rev_10(str)
	local new_str = ""
	new_str =string.format("%d",("0x" .. reverse(str)))
	return new_str
end

---buffer倒转，16进制转10进制
function to10_r(str)
	local new_str = ""
	new_str =string.format("%d",("0x" .. le_buffers(str)))
	return new_str
end


---ascii输出
function toascii(str)
	local swap_str = tostring(str)
	local new_str = ""
	for i = 0,str:len()-1,1
	do
		new_str = new_str .. string.char((str(i,1)):uint())
	end
	return new_str
end

---buffer倒转，ascii输出
function toascii_r(str)
	local new_str = ""
	for i = str:len()-1,0,-1
	do
		new_str = string.char((str(i,1)):uint()) .. new_str
	end
	return new_str
end



---转IP
function toip(str)
	local new_str = ""
	for i = 0,str:len()-1,1
	do
		if i == 0 then
			new_str = (str(i,1)):uint() .. new_str
		else
			new_str = (str(i,1)):uint() .. "." .. new_str
		end
	end
	return new_str
end


function uints(buffer)
	return buffer:uint()
end

function le_uints(buffer)
	return buffer:le_uint()
end

function uint64s(buffer)
	return buffer:uint64()
end

function le_uint64s(buffer)
	return buffer:le_uint64()
end

function strings(buffer)
	return buffer:string()
end

function le_strings(buffer)
	local new_str = ""
	for i = buffer:len()-1,0,-1
	do
		new_str = string.char((buffer(i,1)):uint()) .. new_str
	end
	return new_str
end

function stringszs(buffer)
	return buffer:stringsz()
end

function ints(buffer)
	return buffer:int()
end

function le_ints(buffer)
	return buffer:int()
end

function int64s(buffer)
	return buffer:int64()
end

function le_int64s(buffer)
	return buffer:le_int64()
end

function floats(buffer)
	return buffer:float()
end

function le_floats(buffer)
	return buffer:float()
end

function ipv4s(buffer)
	return tostring(buffer:ipv4())
end

function le_ipv4s(buffer)
	return tostring(buffer:le_ipv4())
end

function ethers(buffer)
	return tostring(buffer(2,6):ether())
end

function le_ethers(buffer)
	return tostring(buffer(2,6):ether())
end

function le_times(buffer)
	
end

function times(buffer)
	
end


function bits(buffer)
	local new_str = ''
	for i = 0,buffer:len()*8-1, 1 do
		new_str = new_str .. (buffer():bitfield(i,1))
	end
	return new_str	
end


function treeadd(tree,buffer,str,fun,usrtype)
	if fun == nil then
		if usrtype == nil then
			tree:add(buffer, str)
		else
			tree:add(buffer, str .. usrtype[buffer:uint()])
		end
	else
		if usrtype == nil then
			tree:add(buffer, str .. fun(buffer))
		else
			tree:add(buffer, str .. usrtype[fun(buffer)])
		end
	end
end


function treeadd_tab(tree,buffer,tab)
	offset = 0
	for i = 1,#(tab)
		do
		treeadd(tree,buffer(offset,tab[i][1]),tab[i][2],tab[i][3],tab[i][4])
		offset = offset + tab[i][1]
	end
end


--[[
================================================
                     握手协商
================================================
]]


function SystemHello_dissector(buffer,pinfo,tree)
	local tab = {
			{4,"Product:",tostring},
			{8,"MacID:",le_ethers},
			{1,"ObcpVersion:",tostring},
			{1,"ObcpCrypt:",tostring},
			{2,"ObcpPort:",le_uints},
			{4,"ObcpAddr:",le_ipv4s},}
	treeadd_tab(tree,buffer(0,20),tab)
end


--[[
================================================
                     系统状态
================================================
]]

local dnsmode = {
	[0] = "OFF",
	[1] = "PEANUT",}
	
	
local dataformat = {
	[0] = "UNKNOW",
	[1] = "YYYY-MM-DD",
	[2] = "MM-DD-YYYY",
	[3] = "DD-MM-YYYY",
	[4] = "YYYY/MM/DD",
	[5] = "MM/DD/YYYY",
	[6] = "DD/MM/YYYY",
	[7] = "YYYY&MM&DD",
	[8] = "MM&DD&YYYY",
	[9] = "DD&MM&YYYY",}
	
	
local timeformat = {
	[0] = "UNKNOW",
	[1] = "HH:mm:ss",
	[2] = "hh:mm:ss",
	[3] = "HH.mm.ss",
	[4] = "hh.mm.ss",}


local platform = {
	[1] = "HI3520(1)",
	[2] = "HI3531(2)",}
	
local camerastatus = {
	[0] = "UNKNOW",
	[1] = "Normal",
	[2] = "AbNormal",}


function SystemState_dissector(buffer,pinfo,tree)
	local tab = {
			{4,"Time:",le_times},
			{4,"Uptime:",le_times},
			{4,"Totalram:",le_uints},
			{4,"Freearam:",le_uints},
			{4,"Bufferram:",le_uints},
			{4,"Totalswap:",le_uints},
			{4,"Freeswap:",le_uints},
			{4,"Procs:",le_uints},
			{4,"Temperature:",le_uints},
			{4,"Res:",tostring},}
	treeadd_tab(tree,buffer(0,36),tab)
end


function SystemVersion_dissector(buffer,pinfo,tree)
	local tab = {
			{4,"Product:",tostring},
			{32,"Model:",strings},
			{32,"Version:",strings},
			{32,"Serial:",tostring},
			{8,"MacID:",le_ethers},}
	treeadd_tab(tree,buffer(0,108),tab)
end


function hwspec_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Chips:",le_uints},
			{1,"VideoInputs:",le_uints},
			{1,"VideoOutputs:",le_uints},
			{1,"AudioInputs:",le_uints},
			{1,"AudioOutputs:",le_uints},
			{1,"SpeechInputs:",le_uints},
			{1,"SpeechOutputs:",le_uints},
			{1,"AlarmInputs:",le_uints},
			{1,"AlarmOutputs:",le_uints},
			{1,"NetIface:",le_uints},
			{1,"Rs232:",le_uints},
			{1,"RS485:",le_uints},
			{1,"USB:",le_uints},
			{1,"Monitor:",le_uints},
			{1,"Shelfs:",le_uints},
			{1,"IOs:",le_uints},
			{16,"Res:",tostring},}
	treeadd_tab(tree,buffer(0,32),tab)
end


function swlimit_dissector(buffer,pinfo,tree)
	local tab = {
			{2,"Sessions:",le_uints},
			{2,"Streams:",le_uints},
			{2,"Netplays:",le_uints},
			{2,"Dumps:",le_uints},
			{2,"Speechs:",le_uints},
			{2,"ImageRotateSuport:",nil,enable},
			{2,"VideoOutSuport:",nil,enable},
			{18,"Res:",tostring},}
	treeadd_tab(tree,buffer(0,32),tab)
end


function itscap_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"IOFlashLightOututNum:",le_uints},
			{1,"IOInputNum:",le_uints},
			{30,"Res:",tostring},}
	treeadd_tab(tree,buffer(0,32),tab)
end


function SystemDescribe_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"PlatForm:",nil,platform},
			{3,"Res:",tostring},
			{4,"Features:",tostring},}
	treeadd_tab(tree,buffer(0,8),tab)
	local hwspectree = tree:add(OBCP,buffer(8,32),"Hwspec: " )
	hwspec_dissector(buffer(8,32),pinfo,hwspectree)
	local swlimittree = tree:add(OBCP,buffer(40,32),"Swlimit: ")
	swlimit_dissector(buffer(40,32),pinfo,swlimittree)
	local itscaptree = tree:add(OBCP,buffer(72,32),"ITScap: ")
	itscap_dissector(buffer(72,32),pinfo,itscaptree)
end


function modulessist_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Model:",tostring},
			{3,"Res:",tostring},
			{8,"Version:",strings},
			{4,"BuildTime:",le_times},}
	treeadd_tab(tree,buffer(0,16),tab)
end


function SystemGetModules_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Count:",le_uints},
			{3,"Res:",tostring},}
	treeadd_tab(tree,buffer(0,4),tab)
	modulessist_dissector(buffer(4,16),pinfo,tree)
end


function SystemGetIPCDVSStatus_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"CameraStatus:",nil,camerastatus},
			{1,"OnlinesUsers:",le_uints},
			{1,"VideoStreamCount:",le_uints},
			{1,"SDActive:",nil,yon},
			{8,"BitRates:",le_uints},
			{4,"EarlistRecordTime:",le_times},
			{8,"TotalSizeOnSD:",le_uint64s},
			{8,"LeftSizeOnSD:",le_uint64s},
			{8,"Res:",tostring},}
	treeadd_tab(tree,buffer(0,40),tab)
end


function SystemGetIdentity_dissector(buffer,pinfo,tree)
	local tab = {
			{4,"Code:",tostring},
			{32,"Name:",strings},
			{32,"Contact:",strings},
			{32,"Location:",strings},
			{32,"Memo:",strings},}
	treeadd_tab(tree,buffer(0,132),tab)
end


function SystemSetIdentity_dissector(buffer,pinfo,tree)
	local tab = {
			{4,"Code:",tostring},
			{32,"Name:",strings},
			{32,"Contact:",strings},
			{32,"Location:",strings},
			{32,"Memo:",strings},}
	treeadd_tab(tree,buffer(0,132),tab)
end


function SystemGetTime_dissector(buffer,pinfo,tree)
	local tab = {
			{4,"Time:",le_times,},}
	treeadd_tab(tree,buffer(0,4),tab)
end


function SystemSetTime_dissector(buffer,pinfo,tree)
	local tab = {
			{4,"Time:",le_times,},}
	treeadd_tab(tree,buffer(0,4),tab)
end


function SystemGetTimeStyle_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"DataFormat:",nil,dataformat},
			{1,"TimeFormat:",nil,timeformat},
			{1,"Week Display:",nil,enable},
			{5,"Res:",tostring},
			{2,"Timezone:",le_uints},
			{1,"Daylight:",tostring},
			{1,"NTPEnabled:",nil,enable},
			{32,"NTPName:",strings},
			{4,"NTPInterval:",le_uints},}
	treeadd_tab(tree,buffer(0,48),tab)
end


function SystemSetTimeStyle_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"DataFormat:",nil,dataformat},
			{1,"TimeFormat:",nil,timeformat},
			{1,"Week Display:",nil,enable},
			{5,"Res:",tostring},
			{2,"Timezone:",le_uints},
			{1,"Daylight:",tostring},
			{1,"NTPEnabled:",nil,enable},
			{32,"NTPName:",strings},
			{4,"NTPInterval:",tostring},}
	treeadd_tab(tree,buffer(0,48),tab)
end


function SystemGetStatus_dissector(buffer,pinfo,tree)
	local tab = {
			{4,"SysStatus:",tostring},}
	treeadd_tab(tree,buffer(0,4),tab)
end


function SystemGetSDCodeCapbility_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"DataFormat:",tostring},}
	treeadd_tab(tree,buffer(0,1),tab)
end


function SystemGetHDCodeCapbility_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"DataFormat:",tostring},}
	treeadd_tab(tree,buffer(0,1),tab)
end


--[[
================================================
                     系统维护
================================================
]]

	
	
local category = {
	[1] = "Safe",
	[2] = "Service",}
	
local stage = {
	[1] = "READY",
	[2] = "PRE_CHECK",
	[3] = "ERASE",
	[4] = "WRITE",
	[5] = "POST_CHECK",
	[100] = "DONE",}


function SystemPackageInstall_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Category:",nil,category},
			{3,"Res:",tostring},
			{16,"Name:",strings},
			{4,"Version:",strings},
			{128,"Path:",strings},}
	treeadd_tab(tree,buffer(0,152),tab)
end


function SystemPackageRemove_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Category:",nil,category},
			{3,"Res:",tostring},
			{16,"Name:",strings},}
	treeadd_tab(tree,buffer(0,20),tab)
end


function PackageList_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Category:",nil,category},
			{3,"Res:",tostring},
			{16,"Name:",strings},
			{4,"Version:",strings},}
	treeadd_tab(tree,buffer(0,24),tab)
end


function SystemPackageList_dissector(buffer,pinfo,tree)
	local tab = {
			{4,"Count:",le_uints},}
	treeadd_tab(tree,buffer(0,4),tab)
	for i = 0, buffer(0,4):le_uint()-1,1
		do
			local PackageListtree = tree:add(OBCP,buffer(4+24*i,24),"PackageList: " .. (i+1))
			PackageList_dissector(buffer(4+24*i,24),pinfo,PackageListtree)
	end
end


function SystemShell_dissector(buffer,pinfo,tree)
	if buffer:len() == 68 then
		local tab = {
				{64,"Cmd:",strings},
				{4,"Wait:",le_uints},}
		treeadd_tab(tree,buffer(0,68),tab)
	else
		local tab = {
				{4,"Return:",tostring},
				{buffer:len()-4,"Text:",strings},}
		treeadd_tab(tree,buffer(0,buffer:len()),tab)
	end
end


function SystemTop_dissector(buffer,pinfo,tree)
	local tab = {
			{buffer:len(),"Text:",strings},}
	treeadd_tab(tree,buffer(0,buffer:len()),tab)
end


function SystemReboot_dissector(buffer,pinfo,tree)
	local tab = {
			{4,"ConflictStatatus:",tostring},}
	treeadd_tab(tree,buffer(0,4),tab)
end


function SystemHalt_dissector(buffer,pinfo,tree)
	
end


function SystemExport_dissector(buffer,pinfo,tree)
	local tab = {
			{128,"Path:",strings},}
	treeadd_tab(tree,buffer(0,128),tab)
end


function SystemImport_dissector(buffer,pinfo,tree)
	local tab = {
			{128,"Path:",strings},}
	treeadd_tab(tree,buffer(0,128),tab)
end


function SystemRestore_dissector(buffer,pinfo,tree)
	if buffer:len() == 8 then
		local tab = {
				{4,"Mode:",tostring},
				{4,"Inclusions:",tostring},}
		treeadd_tab(tree,buffer(0,8),tab)
	else
		local tab = {
				{4,"InclusionsStatus:",tostring},}
		treeadd_tab(tree,buffer(0,4),tab)
	end
end


function SystemUpgrade_dissector(buffer,pinfo,tree)
	if buffer:len() == 128 then
		local tab = {
			{128,"Path:",strings},}
			treeadd_tab(tree,buffer(0,128),tab)
	else
		local tab = {
			{4,"InclusionsStatus:",tostring},}
			treeadd_tab(tree,buffer(0,4),tab)
	end
end


function SystemBurnState_dissector(buffer,pinfo,tree)
		local tab = {
			{4,"Stage:",le_uints,stage},
			{4,"Percent:",le_uints},}
			treeadd_tab(tree,buffer(0,8),tab)
end


function SystemUpgradeCheck_dissector(buffer,pinfo,tree)
	if buffer:len() == 128 then
		local tab = {
			{128,"Path:",strings},}
			treeadd_tab(tree,buffer(0,128),tab)
	else
		local tab = {
			{4,"Ret:",tostring},}
			treeadd_tab(tree,buffer(0,4),tab)
	end
end


--[[
================================================
                     系统日志
================================================
]]


function SystemLogOpen_dissector(buffer,pinfo,tree)
	if buffer:len() == 28 then
		local tab = {
			{4,"StartTime:",le_times},
			{4,"EndTime:",le_times},
			{1,"Type:",bits},
			{1,"Level:",bits},
			{1,"Disk:",bits},
			{1,"Res:",tostring},
			{16,"Usrs:",trings},}
			treeadd_tab(tree,buffer(0,28),tab)
	else
		local tab = {
			{4,"QueryID:",le_uints},
			{4,"Total:",le_uints},}
			treeadd_tab(tree,buffer(0,8),tab)
	end
end


function SystemLogClose_dissector(buffer,pinfo,tree)
		local tab = {
			{4,"QueryID:",le_uints},}
			treeadd_tab(tree,buffer(0,4),tab)
end


function SyslogList_dissector(buffer,pinfo,tree)
	local tab = {
			{4,"Time:",le_times},
			{1,"Type:",bits},
			{1,"Level:",bits},
			{1,"Action:",tostring},
			{1,"Result:",tostring},
			{4,"Target:",bits},
			{16,"User:",strings},
			{56,"Msg:",strings},}
	treeadd_tab(tree,buffer(0,84),tab)
end


function SystemLogFetch_dissector(buffer,pinfo,tree)
	if buffer:len() == 12 then
		local tab = {
			{4,"QueryID:",le_uints},
			{4,"RowID:",le_uints},
			{4,"RowCount:",le_uints},}
		treeadd_tab(tree,buffer(0,12),tab)
	else
		local tab = {
			{4,"Total:",le_uints},
			{4,"RowID:",le_uints},
			{4,"RowCount:",le_uints},}
		treeadd_tab(tree,buffer(0,12),tab)
		for i = 0, buffer(8,4):le_uint()-1,1 do
			local SyslogListtree = tree:add(OBCP,buffer(12+84*i,84),"SyslogList: " .. (i+1))
			SyslogList_dissector(buffer(4+84*i,84),pinfo,SyslogListtree)
		end		
	end
end


function SystemLogExport_dissector(buffer,pinfo,tree)
	if buffer:len() == 12 then
		local tab = {
			{4,"StartTime:",le_times},
			{4,"EndTime:",le_times},
			{1,"Type:",bits},
			{1,"Level:",bits},
			{1,"Disk:",bits},
			{1,"Resx:",tostring},}
			treeadd_tab(tree,buffer(0,12),tab)
	else
		local tab = {
			{32,"File:",strings},
			{4,"Length:",le_uints},}
			treeadd_tab(tree,buffer(0,36),tab)
	end
end


function SystemLogPurge_dissector(buffer,pinfo,tree)
	local tab = {
		{4,"StartTime:",le_times},
		{4,"EndTime:",le_times},
		{1,"Type:",bits},
		{1,"Level:",bits},
		{1,"Disk:",bits},
		{1,"Resx:",tostring},}
		treeadd_tab(tree,buffer(0,12),tab)
end


--[[
================================================
                     网络管理
================================================
]]


local iface = {
	[0] = "UNKNOW",
	[1] = "LAN",
	[2] = "WAN",
	[3] = "PPPOE",
	[4] = "LAN2",}
	
local up = {
	[0] = "DOWN",
	[1] = "UP",
	[2] = "DIALING",}
	
local netstatus = {
	[0] = "UNKNOW",
	[1] = "BUSY",
	[2] = "NA",
	[3] = "TIMEOUT",
	[4] = "AUTH",}
	
local netspeed = {
	[0] = "AUTO",
	[1] = "10M",
	[2] = "100M",
	[3] = "1000M",}
	
local duplex = {
	[0] = "AUTO",
	[1] = "HALF",
	[2] = "FULL",}
	
local multicast = {
	[0] = "OFF",
	[1] = "ON",}
	
local netmode = {
	[0] = "UNKNOW",
	[1] = "STATIC",
	[2] = "DHCP",
	[3] = "ADSL",}
	
local adsldial = {
	[0] = "UNKNOW",
	[1] = "AUTO",
	[2] = "MANUAL",}


function NetLinkState_dissector(buffer,pinfo,tree)
	if buffer:len() == 4 then
		local tab = {
			{4,"IFace:",le_uints,iface},}
		treeadd_tab(tree,buffer(0,4),tab)
	else
		local tab = {
			{4,"IFace:",le_uints,iface},
			{8,"PhyAddr:",le_ethers},
			{4,"UP:",le_uints,up},
			{4,"Status:",le_uints,netstatus},
			{4,"IpAddr:",le_ipv4s},
			{4,"NetMask:",le_ipv4s},
			{4,"GateWay:",le_ipv4s},
			{4,"RxPkts:",le_uint},
			{4,"TxPkts:",le_uint},
			{4,"RxOcts:",le_uint},
			{4,"TxOcts:",le_uint},}
		treeadd_tab(tree,buffer(0,48),tab)
	end
end


function NetLinkGetCfg_dissector(buffer,pinfo,tree)
	if buffer:len() == 4 then
		local tab = {
			{4,"IFace:",le_uints,iface},}
		treeadd_tab(tree,buffer(0,4),tab)
	else
		local tab = {
			{4,"IFace:",le_uints,iface},
			{8,"PhyAddr:",le_ethers},
			{1,"Speed:",le_uints,netspeed},
			{1,"Duplex:",le_uints,duplex},
			{1,"Multicast:",nil,multicast},
			{1,"Mode:",nil,netmode},
			{4,"MTU:",le_uints},
			{4,"IpAddr:",le_ipv4s},
			{4,"NetMask:",le_ipv4s},
			{4,"GateWay:",le_ipv4s},
			{3,"Res:",tostring},
			{1,"DNS:",nil,dnsmode},
			{4,"NameServer1:",le_ipv4s},
			{4,"NameServer2:",le_ipv4s},
			{4,"AdslDial:",le_uints,adsldial},
			{4,"AdslIdle:",le_uint},
			{32,"AdslServer:",strings},
			{32,"AdslUserName:",strings},
			{16,"AdslPassword:",strings},
			{32,"DnsDomain:",strings},
			{32,"DnsUserName:",strings},
			{16,"DnsPassword:",strings},}
		treeadd_tab(tree,buffer(0,212),tab)
	end
end


function NetLinkSetCfg_dissector(buffer,pinfo,tree)
	if buffer:len() == 4 then
		local tab = {
			{4,"IFace:",nil,iface},}
		treeadd_tab(tree,buffer(0,4),tab)
	else
		local tab = {
			{4,"IFace:",le_uints,iface},
			{8,"PhyAddr:",le_ethers},
			{1,"Speed:",le_uints,netspeed},
			{1,"Duplex:",le_uints,duplex},
			{1,"Multicast:",nil,multicast},
			{1,"Mode:",nil,netmode},
			{4,"MTU:",le_uints},
			{4,"IpAddr:",le_ipv4s},
			{4,"NetMask:",le_ipv4s},
			{4,"GateWay:",le_ipv4s},
			{3,"Res:",tostring},
			{1,"DNS:",nil,dnsmode},
			{4,"NameServer1:",le_ipv4s},
			{4,"NameServer2:",le_ipv4s},
			{4,"AdslDial:",le_uints,adsldial},
			{4,"AdslIdle:",le_uint},
			{32,"AdslServer:",strings},
			{32,"AdslUserName:",strings},
			{16,"AdslPassword:",strings},
			{32,"DnsDomain:",strings},
			{32,"DnsUserName:",strings},
			{16,"DnsPassword:",strings},}
		treeadd_tab(tree,buffer(0,212),tab)
	end
end


function NetLinkStartUp_dissector(buffer,pinfo,tree)
	local tab = {
			{4,"IFace:",le_uints,iface},}
	treeadd_tab(tree,buffer(0,4),tab)
end


function NetLinkShutDown_dissector(buffer,pinfo,tree)
	local tab = {
			{4,"IFace:",le_uints,iface},}
	treeadd_tab(tree,buffer(0,4),tab)
end


function NetLinkTest_dissector(buffer,pinfo,tree)
	if buffer:len() == 40 then
		local tab = {
				{4,"IFace:",le_uints,iface},
				{32,"Host:",strings},
				{4,"Wait:",le_uints},}
		treeadd_tab(tree,buffer(0,40),tab)
	else
		local tab = {
				{buffer:len(),"Text:",strings},}
		treeadd_tab(tree,buffer(0,buffer:len()),tab)
	end
end


--[[
================================================
                     网络应用
================================================
]]


local proto = {
	[0] = "UNKNOW",
	[1] = "UDP",
	[2] = "TCP",}
	
local workdir = {
	[1] = "USB",
	[0] = "SD",}
	
	
local anonenabled = {
	[1] = "Enabled",
	[0] = "Disabled",}
	


function NetServiceGetAddrs_dissector(buffer,pinfo,tree)
	local tab = {
			{2,"CmdPort:",le_uints},
			{2,"DataPort:",le_uints},
			{2,"HttpPort:",le_uints},
			{2,"McastPort:",le_uints},
			{4,"McastAddr:",le_ipv4s},
			{4,"LogServer:",le_ipv4s},}
	treeadd_tab(tree,buffer(0,16),tab)
end


function NetServiceSetAddrs_dissector(buffer,pinfo,tree)
	local tab = {
			{2,"CmdPort:",le_uints},
			{2,"DataPort:",le_uints},
			{2,"HttpPort:",le_uints},
			{2,"McastPort:",le_uints},
			{4,"McastAddr:",le_ipv4s},
			{4,"LogServer:",le_ipv4s},}
	treeadd_tab(tree,buffer(0,16),tab)
end


function AlertServerList_dissector(buffer,pinfo,tree)
	local tab = {
			{4,"Addr:",le_ipv4},
			{2,"Port:",le_uints},
			{1,"Proto:",nil,proto},
			{1,"Format:OB"},}
	treeadd_tab(tree,buffer(0,8),tab)
end


function NetServiceGetAlerts_dissector(buffer,pinfo,tree)
	for i = 0, 1,1 do
		local AlertServerListtree = tree:add(OBCP,buffer(8*i,8),"AlertServerList: " .. (i+1))
		AlertServerList_dissector(buffer(8*i,8),pinfo,AlertServerListtree)
	end
end


function NetServiceSetAlerts_dissector(buffer,pinfo,tree)
	for i = 0, 1,1 do
		local AlertServerListtree = tree:add(OBCP,buffer(8*i,8),"AlertServerList: " .. (i+1))
		AlertServerList_dissector(buffer(8*i,8),pinfo,AlertServerListtree)
	end
end


function NetServiceGetSmtp_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Enabled:",nil,enable},
			{3,"Res:",tostring},
			{32,"SmtpServer:",strings},
			{2,"SmtpPort:",le_uints},
			{1,"SmtpAuth:",le_ipv4s},
			{1,"Res:",tostring},
			{32,"SmtpUsername:",strings},
			{32,"SmtpPassword:",strings},
			{32,"Sender:",strings},
			{64,"Recipients:",strings},}
	treeadd_tab(tree,buffer(0,200),tab)
end


function NetServiceSetSmtp_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Enabled:",nil,enable},
			{3,"Res:",tostring},
			{32,"SmtpServer:",strings},
			{2,"SmtpPort:",le_uints},
			{1,"SmtpAuth:",le_ipv4s},
			{1,"Res:",tostring},
			{32,"SmtpUsername:",strings},
			{32,"SmtpPassword:",strings},
			{32,"Sender:",strings},
			{64,"Recipients:",strings},}
	treeadd_tab(tree,buffer(0,200),tab)
end


function NetServiceGetSnmp_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Enabled:",nil,enable},
			{3,"Res:",tostring},
			{16,"Community:",strings},}
	treeadd_tab(tree,buffer(0,20),tab)
end


function NetServiceSetSnmp_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Enabled:",nil,enable},
			{3,"Res:",tostring},
			{16,"Community:",strings},}
	treeadd_tab(tree,buffer(0,20),tab)
end


function CenterServerList_dissector(buffer,pinfo,tree)
	local tab = {
			{4,"Addr:",le_ipv4},
			{2,"Port:",le_uints},
			{2,"Res:",tostring},}
	treeadd_tab(tree,buffer(0,8),tab)
end


function NetServiceGetCenters_dissector(buffer,pinfo,tree)
	for i = 0, 1,1 do
		local CenterServerListtree = tree:add(OBCP,buffer(8*i,8),"CenterServerList: " .. (i+1))
		CenterServerList_dissector(buffer(8*i,8),pinfo,CenterServerListtree)
	end
end


function NetServiceSetCenters_dissector(buffer,pinfo,tree)
	for i = 0, 1,1 do
		local CenterServerListtree = tree:add(OBCP,buffer(8*i,8),"CenterServerList: " .. (i+1))
		CenterServerList_dissector(buffer(8*i,8),pinfo,CenterServerListtree)
	end
end


function NetServiceGetRtspCfg_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Enabled:",nil,enable},
			{1,"Res:",tostring},
			{2,"RtspPort:",le_uints},
			{2,"RtpBasePortVideo:",le_uints},
			{2,"RtpBasePortAudio:",le_uints},
			{4,"MulticastIp:",le_ipv4s},
			{2,"McastPortVideo:",le_uints},
			{2,"McastPortAudio:",le_uints},}
	treeadd_tab(tree,buffer(0,16),tab)
end


function NetServiceSetRtspCfg_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Enabled:",nil,enable},
			{1,"Res:",tostring},
			{2,"RtspPort:",le_uints},
			{2,"RtpBasePortVideo:",le_uints},
			{2,"RtpBasePortAudio:",le_uints},
			{4,"MulticastIp:",le_ipv4s},
			{2,"McastPortVideo:",le_uints},
			{2,"McastPortAudio:",le_uints},}
	treeadd_tab(tree,buffer(0,16),tab)
end


function FTPUser_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Flag:",nil,enable},
			{1,"ReadPermit:",nil,enable},
			{1,"WritePermit:",nil,enable},
			{1,"DeletePermit:",nil,enable},
			{32,"Name:",strings},
			{32,"PassWord:",strings},}
	treeadd_tab(tree,buffer(0,68),tab)
end


function NetServiceGetFtpCfg_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Enabled:",nil,enable},
			{2,"Port:",le_uints},
			{1,"AnonEnabled:",nil,anonenabled},
			{1,"WorkDir:",nil,workdir},
			{3,"Res:",tostring},
			{4,"UserNum:",le_uints},}
	treeadd_tab(tree,buffer(0,12),tab)
	for i = 0,15,1 do
		local FTPUsertree = tree:add(OBCP,buffer(12+68*i,68),"FTPUser: " .. (i+1))
		FTPUser_dissector(buffer(12+68*i,68),pinfo,FTPUsertree)
	end
end


function NetServiceSetFtpCfg_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Enabled:",nil,enable},
			{2,"Port:",le_uints},
			{1,"AnonEnabled:",nil,anonenabled},
			{1,"WorkDir:",nil,workdir},
			{3,"Res:",le_uints},
			{4,"UserNum:",le_uints},}
	treeadd_tab(tree,buffer(0,12),tab)
	for i = 0,15,1 do
		local FTPUsertree = tree:add(OBCP,buffer(12+68*i,68),"FTPUser: " .. (i+1))
		FTPUser_dissector(buffer(12+68*i,68),pinfo,FTPUsertree)
	end
end


function NetServiceGetOnvifCfg_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Enabled:",nil,enable},
			{3,"Res:",tostring},
			{2,"Port:",le_uints},
			{1,"SslEnabled:",tostring},
			{1,"AuthEnabled:",tostring},}
	treeadd_tab(tree,buffer(0,8),tab)
end


function NetServiceSetOnvifCfg_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Enabled:",nil,enable},
			{3,"Res:",tostring},
			{2,"Port:",le_uints},
			{1,"SslEnabled:",tostring},
			{1,"AuthEnabled:",tostring},}
	treeadd_tab(tree,buffer(0,8),tab)
end


function NetClientGetFtpCfg_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Enabled:",nil,enable},
			{3,"Res:",tostring},
			{4,"ServerIp:",le_ipv4s},
			{2,"ServerPort:",le_uints},
			{2,"Res:",tostring},
			{256,"Path:",strings},
			{32,"Name:",strings},
			{32,"PassWord:",strings},
			{1,"Anonenabled:",tostring},
			{1,"SubEnabled:",tostring},
			{2,"SubPathType:",tostring},}
	treeadd_tab(tree,buffer(0,336),tab)
end


function NetClientSetFtpCfg_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Enabled:",nil,enable},
			{3,"Res:",tostring},
			{4,"ServerIp:",le_ipv4s},
			{2,"ServerPort:",le_uints},
			{2,"Res:",tostring},
			{256,"Path:",strings},
			{32,"Name:",strings},
			{32,"PassWord:",strings},
			{1,"Anonenabled:",tostring},
			{1,"SubEnabled:",tostring},
			{2,"SubPathType:",tostring},}
	treeadd_tab(tree,buffer(0,336),tab)
end


function NetServiceGetSipCfg_dissector(buffer,pinfo,tree)
	local tab = {
			{32,"ServerID:",strings},
			{256,"ServerDomain:",strings},
			{4,"ServerIp:",le_ipv4s},
			{2,"ServerPort:",le_uints},
			{2,"LocalPort:",le_uints},
			{32,"UserName:",strings},
			{32,"PassWord:",strings},
			{4,"RegExpire:",le_uints},
			{4,"KeepAlivePeriod:",le_uints},
			{4,"KeepAliveTimeOut:",le_uints},
			{128,"Res:",tostring},}
	treeadd_tab(tree,buffer(0,500),tab)
end


function NetServiceSetSipCfg_dissector(buffer,pinfo,tree)
	local tab = {
			{32,"ServerID:",strings},
			{256,"ServerDomain:",strings},
			{4,"ServerIp:",le_ipv4s},
			{2,"ServerPort:",le_uints},
			{2,"LocalPort:",le_uints},
			{32,"UserName:",strings},
			{32,"PassWord:",strings},
			{4,"RegExpire:",le_uints},
			{4,"KeepAlivePeriod:",le_uints},
			{4,"KeepAliveTimeOut:",le_uints},
			{128,"Res:",tostring},}
	treeadd_tab(tree,buffer(0,500),tab)
end


--[[
================================================
                     状态上传
================================================
]]


function NetReportGetCfg_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Enabled:",nil,enable},
			{3,"Res:",tostring},}
	treeadd_tab(tree,buffer(0,4),tab)
end


function NetReportSetCfg_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Enabled:",nil,enable},
			{3,"Res:",tostring},}
	treeadd_tab(tree,buffer(0,4),tab)
end


function NetDiscoveryHello_dissector(buffer,pinfo,tree)
	local tab = {
			{4,"Product:",tostring},
			{8,"MacID:",le_ethers},
			{1,"OBCPVersion:",tostring},
			{1,"OBCPCrypt:",tostring},
			{2,"OBCPPort:",le_uints},
			{4,"OBCPAddr:",le_ipv4s},}
	treeadd_tab(tree,buffer(0,20),tab)
end


function NetDiscoveryState_dissector(buffer,pinfo,tree)
	local tab = {
			{4,"Time:",le_times},
			{4,"UpTime:",le_times},
			{4,"Loads:",le_uints},
			{4,"Totalram:",le_uints},
			{4,"Freearam:",le_uints},
			{4,"Bufferram:",le_uints},
			{4,"Totalswap:",le_uints},
			{4,"Freeswap:",le_uints},
			{4,"Procs:",le_uints},}
	treeadd_tab(tree,buffer(0,36),tab)
end


function NetDiscoverySetParam_dissector(buffer,pinfo,tree)
	local tab = {
			{8,"MAC:",le_ethers},
			{2,"DeviceType:",tostring},
			{2,"Settype:",tostring},}
	treeadd_tab(tree,buffer(0,12),tab)
end


--[[
================================================
                     安全管理
================================================
]]

local actortype = {
	[0] = "UNKNOW",
	[1] = "GUI",
	[2] = "CLI",
	[4] = "CLIENT",
	[8] = "WEBUI",}


function SecuritySessionLogin_dissector(buffer,pinfo,tree)
	if buffer:len() == 52 then
		local tab = {
				{16,"User:",strings},
				{32,"PassWord:",strings},
				{4,"Actor:",le_uints,actortype},}
		treeadd_tab(tree,buffer(0,52),tab)
	else
		local tab = {
				{4,"SessionID:",le_uints},
				{16,"Role:",strings},}
		treeadd_tab(tree,buffer(0,20),tab)		
	end
end


function SecuritySessionLogout_dissector(buffer,pinfo,tree)
	local tab = {
		{4,"SessionID:",le_uints},}
	treeadd_tab(tree,buffer(0,4),tab)
end


function vostatus_dissector(buffer,pinfo,tree)
	local tab = {
			{4,"SessionID:",le_times},
			{16,"User:",strings},
			{16,"Role:",strings},
			{4,"Ctime:",le_times},
			{4,"Atime:",le_times},
			{4,"Actor:",le_uints,actortype},
			{4,"ClientAddr:",le_ipv4s},
			{4,"ServerAddr:",le_ipv4s},
			{2,"ClientPort:",le_uints},
			{2,"ServerPort:",le_uints},}
	treeadd_tab(tree,buffer(0,60),tab)
end


function SecuritySessionList_dissector(buffer,pinfo,tree)
	local tab = {
		{4,"Count:",le_uints},}
	treeadd_tab(tree,buffer(0,4),tab)
	for i = 0,buffer(0,4):le_uint()-1,1 do
		local Sessiontree = tree:add(OBCP,buffer(4+60*i,60),"SecuritySessionList: " .. (i+1))
		vostatus_dissector(buffer(4+60*i,60),pinfo,Sessiontree)
	end
end


function SecuritySessionGet_dissector(buffer,pinfo,tree)
	if buffer:len() == 4 then
		local tab = {
			{4,"Key:",le_uints},}
		treeadd_tab(tree,buffer(0,4),tab)
	else
		local tab = {
			{4,"Key:",le_uints},
			{4,"Value:",le_uints},}
		treeadd_tab(tree,buffer(0,8),tab)
	end
end


function SecuritySessionSet_dissector(buffer,pinfo,tree)
	local tab = {
		{4,"Key:",le_uints},
		{4,"Value:",le_uints},}
	treeadd_tab(tree,buffer(0,8),tab)
end


--[[
================================================
                     用户管理
================================================
]]


local perm = {
	[0] = "UNKNOW",
	[1] = "X",
	[2] = "W",
	[4] = "R",}
	
local tgttype = {
	[0] = "UNKNOW",
	[1] = "SYSTEM",
	[2] = "RECORD",
	[3] = "DOME",
	[4] = "PLAYBACK",}


function SecurityUserAdd_dissector(buffer,pinfo,tree)
	local tab = {
			{16,"User:",strings},
			{32,"PassWord:",strings},
			{16,"Role:",strings},
			{4,"Actor:",le_uints,actortype},
			{32,"Name:",strings},
			{32,"Email:",strings},
			{32,"Memo:",strings},}
	treeadd_tab(tree,buffer(0,164),tab)
end


function SecurityUserEdit_dissector(buffer,pinfo,tree)
	local tab = {
			{16,"User:",strings},
			{32,"PassWord:",strings},
			{16,"Role:",strings},
			{4,"Actor:",le_uints,actortype},
			{32,"Name:",strings},
			{32,"Email:",strings},
			{32,"Memo:",strings},}
	treeadd_tab(tree,buffer(0,164),tab)
end


function SecurityUserDel_dissector(buffer,pinfo,tree)
	local tab = {
			{16,"User:",strings},}
	treeadd_tab(tree,buffer(0,16),tab)
end


function userlist_dissector(buffer,pinfo,tree)
	local tab = {
			{16,"User:",strings},
			{32,"PassWord:",strings},
			{16,"Role:",strings},
			{4,"Actor:",le_uints,actortype},
			{32,"Name:",strings},
			{32,"Email:",strings},
			{32,"Memo:",strings},}
	treeadd_tab(tree,buffer(0,164),tab)
end


function SecurityUserList_dissector(buffer,pinfo,tree)
	local tab = {
			{4,"Count:",le_uints},}
	treeadd_tab(tree,buffer(0,4),tab)
	for i = 0,buffer(0,4):le_uint()-1,1 do
		local UserListtree = tree:add(OBCP,buffer(4+164*i,164),"UserList: " .. (i+1))
		userlist_dissector(buffer(4+164*i,164),pinfo,UserListtree)
	end	
end


function SecurityUserPasswd_dissector(buffer,pinfo,tree)
	local tab = {
			{16,"User:",strings},
			{32,"OldPassWord:",strings},
			{32,"OldPassWord:",strings},}
	treeadd_tab(tree,buffer(0,80),tab)
end


function PrivList_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Perms:",nil,perm},
			{2,"Res:",tostring},
			{1,"TgtType:",nil,tgttype},
			{4,"TgtIDS:",bits},}
	treeadd_tab(tree,buffer(0,8),tab)
end


function SecurityUserGetPrivilege_dissector(buffer,pinfo,tree)
	if buffer:len() ==  16 then
		local tab = {
				{16,"User:",strings},}
		treeadd_tab(tree,buffer(0,16),tab)
	else
		local tab = {
				{16,"User:",strings},
				{4,"Count:",le_units}}
		treeadd_tab(tree,buffer(0,20),tab)
		for i = 0,buffer(16,4):le_uint()-1,1 do
			local PrivListtree = tree:add(OBCP,buffer(20+8*i,8),"PrivList: " .. (i+1))
			PrivList_dissector(buffer(20+8*i,8),pinfo,PrivListtree)
		end	
	end
end


function SecurityUserSetPrivilege_dissector(buffer,pinfo,tree)
	if buffer:len() ==  16 then
		local tab = {
				{16,"User:",strings},}
		treeadd_tab(tree,buffer(0,16),tab)
	else
		local tab = {
				{16,"User:",strings},
				{4,"Count:",le_units}}
		treeadd_tab(tree,buffer(0,20),tab)
		for i = 0,buffer(16,4):le_uint()-1,1 do
			local PrivListtree = tree:add(OBCP,buffer(20+8*i,8),"PrivList: " .. (i+1))
			PrivList_dissector(buffer(20+8*i,8),pinfo,PrivListtree)
		end	
	end
end


function SecurityRoleAdd_dissector(buffer,pinfo,tree)
	local tab = {
			{16,"Role:",strings},
			{1,"Rank:",le_uints},
			{3,"Res:",tostring},
			{32,"Memo:",strings},}
	treeadd_tab(tree,buffer(0,52),tab)
end


function SecurityRoleEdit_dissector(buffer,pinfo,tree)
	local tab = {
			{16,"Role:",strings},
			{1,"Rank:",le_uints},
			{3,"Res:",tostring},
			{32,"Memo:",strings},}
	treeadd_tab(tree,buffer(0,52),tab)
end


function SecurityRoleDel_dissector(buffer,pinfo,tree)
	local tab = {
			{16,"Role:",strings},}
	treeadd_tab(tree,buffer(0,16),tab)
end


function RoleList_dissector(buffer,pinfo,tree)
	local tab = {
			{16,"Role:",strings},
			{1,"Rank:",le_uints},
			{3,"Res:",tostring},
			{32,"Memo:",strings},}
	treeadd_tab(tree,buffer(0,52),tab)
end


function SecurityRoleList_dissector(buffer,pinfo,tree)
	local tab = {
			{4,"Count:",le_uints},}
	treeadd_tab(tree,buffer(0,4),tab)
	for i = 0,buffer(0,4):le_uint()-1,1 do
		local RoleListtree = tree:add(OBCP,buffer(4+52*i,52),"RoleList: " .. (i+1))
		RoleList_dissector(buffer(4+52*i,52),pinfo,RoleListtree)
	end	
end


function SecurityRoleGetPrivilege_dissector(buffer,pinfo,tree)
	if buffer:len() ==  16 then
		local tab = {
				{16,"Role:",strings},}
		treeadd_tab(tree,buffer(0,16),tab)
	else
		local tab = {
				{16,"Role:",strings},
				{4,"Count:",le_units},}
		treeadd_tab(tree,buffer(0,20),tab)
		for i = 0,buffer(16,4):le_uint()-1,1 do
			local PrivListtree = tree:add(OBCP,buffer(20+8*i,8),"PrivList: " .. (i+1))
			PrivList_dissector(buffer(20+8*i,8),pinfo,PrivListtree)
		end	
	end
end


function SecurityRoleSetPrivilege_dissector(buffer,pinfo,tree)
	if buffer:len() ==  16 then
		local tab = {
				{16,"Role:",strings},}
		treeadd_tab(tree,buffer(0,16),tab)
	else
		local tab = {
				{16,"Role:",strings},
				{4,"Count:",le_units},}
		treeadd_tab(tree,buffer(0,20),tab)
		for i = 0,buffer(16,4):le_uint()-1,1 do
			local PrivListtree = tree:add(OBCP,buffer(20+8*i,8),"PrivList: " .. (i+1))
			PrivList_dissector(buffer(20+8*i,8),pinfo,PrivListtree)
		end	
	end
end


function OBCPRoleList_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"TgtType:",nil,tgttype},
			{1,"PrivIndex:",bits},
			{2,"Res:",tostring},
			{32,"TgtName:",strings},}
	treeadd_tab(tree,buffer(0,36),tab)
end


function SecurityRoleGetPrivilegeDesp_dissector(buffer,pinfo,tree)
	local tab = {
			{4,"Count:",le_uints},}
	treeadd_tab(tree,buffer(0,4),tab)
	for i = 0,buffer(0,4):le_uint()-1,1 do
		local OBCPPrivListtree = tree:add(OBCP,buffer(4+36*i,36),"OBCPRoleList: " .. (i+1))
		OBCPRoleList_dissector(buffer(4+36*i,36),pinfo,OBCPPrivListtree)
	end	
end


--[[
================================================
                     存储策略
================================================
]]


function StorageGetCfg_dissector(buffer,pinfo,tree)
	local tab = {
			{4,"Policies:",le_uints},}
	treeadd_tab(tree,buffer(0,4),tab)
end


function StorageSetCfg_dissector(buffer,pinfo,tree)
	local tab = {
			{4,"Policies:",le_uints},}
	treeadd_tab(tree,buffer(0,4),tab)
end


--[[
================================================
                     磁盘管理
================================================
]]
local storagetype = {
	[0] = "NAS",
	[1] = "SD Card",
	[2] = "USB",
	[3] = "LOCAL DISK",}
	
local storagelayout = {
	[0] = "NONE",
	[1] = "VMFS",
	[2] = "FDISK",}
	
local yon = {
	[0] = "No",
	[1] = "YES",}
	
local fstype = {
	[0] = "NONE",
	[1] = "VMFS",
	[2] = "FAT32",}


function disklist_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Usage:",tostring},
			{1,"Album:",tostring},
			{1,"Awake:",tostring},
			{1,"Active:",nil,yon},
			{1,"Type:",nil,storagetype},
			{1,"ImgPartitionPercents:",le_uints},
			{1,"Res:",tostring},
			{1,"Layout:",nil,storagelayout},
			{8,"TotalSpace:",le_uints},
			{8,"FreeSpace:",le_uints},
			{8,"ImgTotalSpace:",le_uints},
			{8,"ImgFreeSpace:",le_uints},}
	treeadd_tab(tree,buffer(0,40),tab)
end


function StorageDiskList_dissector(buffer,pinfo,tree)
	local tab = {
			{4,"Count:",le_uints},}
	treeadd_tab(tree,buffer(0,4),tab)
	for i = 0,buffer(0,4):le_uint()-1,1 do
		local disktree = tree:add(OBCP,buffer(4+40*i,40),"DiskList: " .. (i+1))
		disklist_dissector(buffer(4+40*i,40),pinfo,disktree)
	end	
end


function partitions_dissector(buffer,pinfo,tree)
		local tab = {
			{8,"TotalSpace:",le_uints},
			{8,"FreeSpace:",le_uints},
			{1,"Usage:",tostring},
			{2,"Res:",tostring,},
			{1,"FSType:",nil,fstype},}
		treeadd_tab(tree,buffer(0,20),tab)
end


function StorageDiskDescribe_dissector(buffer,pinfo,tree)
	if buffer:len() ==  4 then
		local tab = {
				{1,"Disk:",bits},
				{3,"Res:",tostring},}
		treeadd_tab(tree,buffer(0,4),tab)
	else
		local tab = {
			{8,"TotalSpace:",le_uints},
			{8,"FreeSpace:",le_uints},
			{8,"ImgTotalSpace:",le_uints},
			{8,"ImgFreeSpace:",le_uints},
			{2,"Res:",tostring},
			{1,"Layout:",nil,storagelayout},
			{1,"Partitions:",le_uints},}
		treeadd_tab(tree,buffer(0,36),tab)
		for i = 0,31,1 do
			local partitiontree = tree:add(OBCP,buffer(36+20*i,20),"Partitions: " .. (i+1))
			partitions_dissector(buffer(36+20*i,20),pinfo,partitiontree)
		end	
	end
end


--[[
================================================
                     盘组管理
================================================
]]





--[[
================================================
                     串口管理
================================================
]]


local ciphertype = {
	[0] = "UNKNOW",
	[1] = "Console",
	[2] = "Kb",
	[3] = "Agent",
	[4] = "Dome",
	[5] = "Snoop",}

	
local rxtx = {
	[0] = "Unknow",
	[1] = "RX",
	[2] = "TX",
	[3] = "BOTH",}
	
local parity = {
	[0] = "NONE",
	[1] = "EVEN",
	[2] = "ODD",
	[3] = "MARK",
	[4] = "SPACE",}
	
local flow = {
	[0] = "NONE",
	[1] = "XONOff",}
	
local uarttype = {
	[0] = "UNKNOW",
	[1] = "RS232",
	[2] = "RS485",
	[3] = "UNKNOW",
	[4] = "UNKNOW",}
	

function cipherlist_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Type:",nil,ciphertype},
			{1,"Rxtx:",nil,rxtx},
			{1,"Links:",bits},
			{1,"Capabilitys:",bits},
			{16,"Name:",strings},}
	treeadd_tab(tree,buffer(0,20),tab)
end


function serialcfg_dissector(buffer,pinfo,tree)
	local tab = {
			{4,"Baudrate:",le_uints},
			{1,"Databits:",le_uints},
			{1,"Stopbits:",le_uints},
			{1,"Parity:",nil,parity},
			{1,"Flow:",nil,flow},}
	treeadd_tab(tree,buffer(0,8),tab)
end


function uartcipher_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Enabled:",nil,enable},
			{1,"Res:",tostring},
			{1,"Addr:",tostring},
			{1,"User:",strings},}
	treeadd_tab(tree,buffer(0,4),tab)
	local cipherlisttree = tree:add(OBCP,buffer(4,20),"CipherList: ")
	cipherlist_dissector(buffer(4,20),pinfo,cipherlisttree)
	local serialcfgtree = tree:add(OBCP,buffer(24,8),"SerialCfg: ")
	serialcfg_dissector(buffer(24,8),pinfo,serialcfgtree)
end


function UartPortGetCfg_dissector(buffer,pinfo,tree)
	if buffer:len() == 4 then
		local tab = {
			{1,"Link:",nil,uarttype},
			{1,"Dock:",tostring},
			{2,"Res:",tostring},}
		treeadd_tab(tree,buffer(0,4),tab)
	else
		local tab = {
			{1,"Link:",nil,uarttype},
			{1,"Dock:",tostring},
			{1,"Res:",tostring},
			{1,"Count:",le_uints},}
		treeadd_tab(tree,buffer(0,4),tab)
		for i = 0,20,1 do
			local uartciphertree = tree:add(OBCP,buffer(4+32*i,32),"UartCipherList: " .. (i+1))
			uartcipher_dissector(buffer(4+32*i,32),pinfo,uartciphertree)
		end
	end
end


function UartPortSetCfg_dissector(buffer,pinfo,tree)
	if buffer:len() == 4 then
		local tab = {
			{1,"Link:",nil,uarttype},
			{1,"Dock:",tostring},
			{2,"Res:",tostring},}
		treeadd_tab(tree,buffer(0,4),tab)
	else
		local tab = {
			{1,"Link:",nil,uarttype},
			{1,"Dock:",tostring},
			{1,"Res:",tostring},
			{1,"Count:",le_uints},}
		treeadd_tab(tree,buffer(0,4),tab)
		for i = 0,(buffer(3,1):uint())-1,1 do
			local uartciphertree = tree:add(OBCP,buffer(4+32*i,32),"UartCipherList: " .. (i+1))
			uartcipher_dissector(buffer(4+32*i,32),pinfo,uartciphertree)
		end
	end
end


function UartCipherList_dissector(buffer,pinfo,tree)
	if buffer:len() == 4 then
		local tab = {
			{1,"Link:",nil,uarttype},
			{1,"Dock:",tostring},
			{2,"Res:",tostring},}
		treeadd_tab(tree,buffer(0,4),tab)
	else
		local tab = {
			{1,"Link:",nil,uarttype},
			{2,"Res:",tostring},
			{1,"Count:",tostring},}
		treeadd_tab(tree,buffer(0,4),tab)
		for i = 0,(buffer(3,1):uint())-1,1 do
			local uartciphertree = tree:add(OBCP,buffer(4+20*i,20),"UartCipherList: " .. (i+1))
			cipherlist_dissector(buffer(4+20*i,20),pinfo,uartciphertree)
		end
	end
end


function cipherlibrary_dissector(buffer,pinfo,tree)
	local tab = {
			{4,"Length:",le_uints},
			{buffer(0,4):le_uint(),"Data:",strings},}
	treeadd_tab(tree,buffer(0,buffer(0,4):le_uint()),tab)
end


function UartCipherInstall_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Mode:",tostring},
			{4,"Res:",tostring},}
	treeadd_tab(tree,buffer(0,5),tab)
	local cipherlisttree = tree:add(OBCP,buffer(5,20),"CipherList: ")
	cipherlist_dissector(buffer(5,20),pinfo,cipherlisttree)
	local cipherlibrarytree = tree:add(OBCP,buffer(25,buffer:len()-25),"cipherlibrary: ")
	cipherlibrary_dissector(buffer(25,buffer:len()-25),pinfo,cipherlibrarytree)
end


function UartSnoopGetCfg_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Link:",le_uints},
			{1,"Dock:",le_uints},
			{2,"Port:",le_uints},
			{4,"Addr:",le_ipv4s},}
	treeadd_tab(tree,buffer(0,8),tab)
	local cipherlisttree = tree:add(OBCP,buffer(8,20),"CipherList: ")
	cipherlist_dissector(buffer(8,20),pinfo,cipherlisttree)
	local tab = {
			{1,"Content:",tostring},
			{1,"Res:",tostring},
			{1,"Imprints:",bits},
			{1,"Subject:",bits},
			{2,"X:",le_uints},
			{2,"Y:",le_uints},}
	treeadd_tab(tree,buffer(28,8),tab)
end


function UartSnoopSetCfg_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Link:",le_uints},
			{1,"Dock:",le_uints},
			{2,"Port:",le_uints},
			{4,"Addr:",le_ipv4s},}
	treeadd_tab(tree,buffer(0,8),tab)
	local cipherlisttree = tree:add(OBCP,buffer(8,20),"CipherList: ")
	cipherlist_dissector(buffer(8,20),pinfo,cipherlisttree)
	local tab = {
			{1,"Content:",tostring},
			{1,"Res:",tostring},
			{1,"Imprints:",bits},
			{1,"Subject:",bits},
			{2,"X:",le_uints},
			{2,"Y:",le_uints},}
	treeadd_tab(tree,buffer(28,8),tab)
end


function UartAgentGetCfg_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Link:",le_uints},
			{1,"Dock:",le_uints},
			{1,"Addr:",le_uints},
			{1,"Res:",tostring},}
	treeadd_tab(tree,buffer(0,4),tab)
	local cipherlisttree = tree:add(OBCP,buffer(4,20),"CipherList: ")
	cipherlist_dissector(buffer(4,20),pinfo,cipherlisttree)
end


function UartAgentSetCfg_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Link:",le_uints},
			{1,"Dock:",le_uints},
			{1,"Addr:",le_uints},
			{1,"Res:",tostring},}
	treeadd_tab(tree,buffer(0,4),tab)
	local cipherlisttree = tree:add(OBCP,buffer(4,20),"CipherList: ")
	cipherlist_dissector(buffer(4,20),pinfo,cipherlisttree)
end


function UartFpgaGetCfg_dissector(buffer,pinfo,tree)
	if buffer:len() == 4 then
		local tab = {
			{1,"Link:",nil,uarttype},
			{1,"Dock:",tostring},
			{2,"Res:",tostring},}
		treeadd_tab(tree,buffer(0,4),tab)
	else
		local tab = {
			{1,"Link:",nil,uarttype},
			{1,"Dock:",tostring},
			{2,"Res:",tostring},}
		treeadd_tab(tree,buffer(0,4),tab)
		local serialcfgtree = tree:add(OBCP,buffer(4,8),"SerialCfg: ")
		serialcfg_dissector(buffer(4,8),pinfo,serialcfgtree)
	end
end


function UartFpgaSetCfg_dissector(buffer,pinfo,tree)
	if buffer:len() == 4 then
		local tab = {
			{1,"Link:",nil,uarttype},
			{1,"Dock:",tostring},
			{2,"Res:",tostring},}
		treeadd_tab(tree,buffer(0,4),tab)
	else
		local tab = {
			{1,"Link:",nil,uarttype},
			{1,"Dock:",tostring},
			{2,"Res:",tostring},}
		treeadd_tab(tree,buffer(0,4),tab)
		local serialcfgtree = tree:add(OBCP,buffer(4,8),"SerialCfg: ")
		serialcfg_dissector(buffer(4,8),pinfo,serialcfgtree)
	end
end


--[[
================================================
                     报警主机管理
================================================
]]


--[[
================================================
                     报警端子输入
================================================
]]


--[[
================================================
                     报警端子输出
================================================
]]


--[[
================================================
                     报警联动
================================================
]]





--[[
================================================
                     音视频总体
================================================
]]




function AVDescribe_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Vcodes:",bits},
			{1,"Systems:",bits},
			{1,"Bitstreams:",le_uints},
			{1,"Res:",tostring},
			{16,"Acodes:",tostring},}
	treeadd_tab(tree,buffer(0,20),tab)
end


function AVGetCfg_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Systems:",bits},
			{3,"Res:",tostring},}
	treeadd_tab(tree,buffer(0,4),tab)
end


function AVSetCfg_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Systems:",bits},
			{3,"Res:",tostring},}
	treeadd_tab(tree,buffer(0,4),tab)
end


--[[
================================================
                     音视频输入
================================================
]]


function inputcfglist_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Disabled:",nil,enable},
			{3,"Res:",tostring},
			{64,"Name:",strings},}
	treeadd_tab(tree,buffer(0,68),tab)
end


function AVInputGetCfg_dissector(buffer,pinfo,tree)
	if buffer:len() == 4 then
		local tab = {
				{4,"Channels:",le_uints,bits},}
		treeadd_tab(tree,buffer(0,4),tab)
	else
		local tab = {
				{4,"Channels:",le_uints,bits},}
		treeadd_tab(tree,buffer(0,4),tab)
		for i = 0,15,1 do
			local inputcfglisttree = tree:add(OBCP,buffer(4+i*68,68),"InputCfgList: ")
			inputcfglist_dissector(buffer(4+i*68,68),pinfo,inputcfglisttree)
		end
	end
end


function AVInputSetCfg_dissector(buffer,pinfo,tree)
	if buffer:len() == 4 then
		local tab = {
				{4,"Channels:",le_uints,bits},}
		treeadd_tab(tree,buffer(0,4),tab)
	else
		local tab = {
				{4,"Channels:",le_uints,bits},}
		treeadd_tab(tree,buffer(0,4),tab)
		for i = 0,15,1 do
			local inputcfglisttree = tree:add(OBCP,buffer(4+i*68,68),"InputCfgList: ")
			inputcfglist_dissector(buffer(4+i*68,68),pinfo,inputcfglisttree)
		end
	end
end


function inputcfglistv2_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Disabled:",nil,enable},
			{3,"Res:",tostring},
			{128,"Name:",strings},}
	treeadd_tab(tree,buffer(0,132),tab)
end


function AVInputGetCfg_dissector(buffer,pinfo,tree)
	if buffer:len() == 4 then
		local tab = {
				{4,"Channels:",le_uints,bits},}
		treeadd_tab(tree,buffer(0,4),tab)
	else
		local tab = {
				{4,"Channels:",le_uints,bits},}
		treeadd_tab(tree,buffer(0,4),tab)
		for i = 0,15,1 do
			local inputcfglisttree = tree:add(OBCP,buffer(4+i*132,132),"InputCfgListv2: ")
			inputcfglistv2_dissector(buffer(4+i*132,132),pinfo,inputcfglisttree)
		end
	end
end


function AVInputSetCfg_dissector(buffer,pinfo,tree)
	if buffer:len() == 4 then
		local tab = {
				{4,"Channels:",le_uints,bits},}
		treeadd_tab(tree,buffer(0,4),tab)
	else
		local tab = {
				{4,"Channels:",le_uints,bits},}
		treeadd_tab(tree,buffer(0,4),tab)
		for i = 0,15,1 do
			local inputcfglisttree = tree:add(OBCP,buffer(4+i*132,132),"InputCfgListv2: ")
			inputcfglistv2_dissector(buffer(4+i*132,132),pinfo,inputcfglisttree)
		end
	end
end


function picturecfglist_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Brightness:",le_uints},
			{1,"Contrast:",le_uints},
			{1,"Saturation:",le_uints},
			{1,"Hue:",le_uints},
			{1,"Sharpness:",le_uints},
			{3,"Res:",tostring},
			{1,"StartHour:",le_uints},
			{1,"StartMinute:",le_uints},
			{1,"EndHour:",le_uints},
			{1,"EndMinute:",le_uints},
			{1,"Endabled:",nil,enable},
			{3,"Res:",tostring},}
	treeadd_tab(tree,buffer(0,16),tab)
end


function AVInputGetPictureCfg_dissector(buffer,pinfo,tree)
	if buffer:len() == 4 then
		local tab = {
				{4,"Channels:",le_uints,bits},}
		treeadd_tab(tree,buffer(0,4),tab)
	else
		local tab = {
				{4,"Channels:",le_uints,bits},
				{1,"Enabled:",nil,enable},
				{1,"Impromptu:",nil,yon},
				{2,"Res:",tostring},}
		treeadd_tab(tree,buffer(0,8),tab)
		for i = 0,15,1 do
			local picturecfglisttree = tree:add(OBCP,buffer(8+i*16,16),"Picturecfglist: ")
			picturecfglist_dissector(buffer(8+i*16,16),pinfo,picturecfglisttree)
		end
	end
end


function AVInputSetPictureCfg_dissector(buffer,pinfo,tree)
	if buffer:len() == 4 then
		local tab = {
				{4,"Channels:",le_uints,bits},}
		treeadd_tab(tree,buffer(0,4),tab)
	else
		local tab = {
				{4,"Channels:",le_uints,bits},
				{1,"Enabled:",nil,enable},
				{1,"Impromptu:",le_uints},
				{2,"Res:",tostring},}
		treeadd_tab(tree,buffer(0,8),tab)
		for i = 0,15,1 do
			local picturecfglisttree = tree:add(OBCP,buffer(8+i*16,16),"Picturecfglist: ")
			picturecfglist_dissector(buffer(8+i*16,16),pinfo,picturecfglisttree)
		end
	end
end


function imprintscfglist_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Brightness:",le_uints},
			{1,"Contrast:",le_uints},
			{1,"Saturation:",le_uints},
			{1,"Hue:",le_uints},
			{1,"Sharpness:",le_uints},
			{3,"Res:",tostring},
			{1,"StartHour:",le_uints},
			{1,"StartMinute:",le_uints},
			{1,"EndHour:",le_uints},
			{1,"EndMinute:",le_uints},
			{1,"Endabled:",nil,enable},
			{3,"Res:",tostring},}
	treeadd_tab(tree,buffer(0,16),tab)
end


function AVInputGetImprintCfg_dissector(buffer,pinfo,tree)
	if buffer:len() == 4 then
		local tab = {
				{4,"Channels:",le_uints,bits},}
		treeadd_tab(tree,buffer(0,4),tab)
	else
		local tab = {
				{4,"Channels:",le_uints,bits},
				{1,"Enabled:",nil,enable},
				{3,"Res:",tostring},}
		treeadd_tab(tree,buffer(0,8),tab)
		for i = 0,15,1 do
			local imprintcfglisttree = tree:add(OBCP,buffer(8+i*16,16),"Imprintscfglist: ")
			imprintscfglist_dissector(buffer(8+i*16,16),pinfo,imprintcfglisttree)
		end
	end
end


function AVInputSetImprintCfg_dissector(buffer,pinfo,tree)
	if buffer:len() == 4 then
		local tab = {
				{4,"Channels:",le_uints,bits},}
		treeadd_tab(tree,buffer(0,4),tab)
	else
		local tab = {
				{4,"Channels:",le_uints,bits},
				{1,"Enabled:",nil,enable},
				{3,"Res:",tostring},}
		treeadd_tab(tree,buffer(0,8),tab)
		for i = 0,15,1 do
			local imprintcfglisttree = tree:add(OBCP,buffer(8+i*16,16),"Imprintscfglist: ")
			imprintscfglist_dissector(buffer(8+i*16,16),pinfo,imprintcfglisttree)
		end
	end
end


function imprintstextlist_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Brightness:",},
			{1,"Contrast:",tostring},
			{1,"Saturation:",strings},
			{1,"Hue:",tostring},
			{1,"Sharpness:",tostring},
			{3,"Res:",tostring},
			{1,"StartHour:",tostring},
			{1,"StartMinute:",tostring},
			{1,"EndHour:",tostring},
			{1,"EndMinute:",tostring},
			{1,"Endabled:",tostring},
			{3,"Res:",tostring},}
	treeadd_tab(tree,buffer(0,16),tab)
end


function AVInputGetImprintText_dissector(buffer,pinfo,tree)
	if buffer:len() == 4 then
		local tab = {
				{4,"Channels:",le_uints,bits},}
		treeadd_tab(tree,buffer(0,4),tab)
	else
		local tab = {
				{4,"Channels:",le_uints,bits},
				{1,"Enabled:",nil,enable},
				{3,"Res:",tostring},}
		treeadd_tab(tree,buffer(0,8),tab)
		for i = 0,15,1 do
			local imprinttextlisttree = tree:add(OBCP,buffer(8+i*16,16),"Imprintstextlist: ")
			imprintstextlist_dissector(buffer(8+i*16,16),pinfo,imprinttextlisttree)
		end
	end
end


--[[
================================================
                     环通编码器
================================================
]]


--[[
================================================
                     音视频输出
================================================
]]


--[[
================================================
                     音视频编码
================================================
]]


--[[
================================================
                     音视频检测
================================================
]]


--[[
================================================
                     IP通道管理
================================================
]]


local channeltype = {
	[0] = "IP",
	[1] = "DOMAIN",
	[2] = "URL",}


function AVDigitalChannelSearch_dissector(buffer,pinfo,tree)
	
end


function deviceinfo_dissector(buffer,pinfo,tree)
	tree:add(buffer(0,4),"ChannelType:" .. channeltype[buffer(0,4):le_uint()])
	if buffer(0,4):le_uint() == 0 then
		treeadd(tree,buffer(4,4),"IP:",le_ipv4s)
	elseif buffer(0,4):le_uint() == 1 then
		treeadd(tree,buffer(4,256),"DomainName:",strings)
	else
		treeadd(tree,buffer(4,256),"Url:",strings)
	end
	local tab = {
			{4,"RemoteChannel:",le_uints},
			{2,"CmdPort:",le_uints},
			{2,"StreamPort:",le_uints},
			{64,"Brand:",strings},
			{64,"User:",strings},
			{64,"Passwd:",strings},
			{4,"Protocol:",le_uints},
			{1,"Coder:",},
			{3,"Res:",tostring},}
	treeadd_tab(tree,buffer(260,208),tab)
end


function channelinfo_dissector(buffer,pinfo,tree)
	local tab = {
			{4,"Channel:",le_uints},}
	treeadd_tab(tree,buffer(0,4),tab)
	deviceinfo_dissector(buffer(4,468),pinfo,tree)
end


function AVDigitalChannelAdd_dissector(buffer,pinfo,tree)
	local deviceinfotree = tree:add(OBCP,buffer(4,468),"Channel: " .. buffer(0,4):le_uint())
	deviceinfo_dissector(buffer(4,468),pinfo,deviceinfotree)
end


function AVDigitalChannelModifyProp_dissector(buffer,pinfo,tree)
	local deviceinfotree = tree:add(OBCP,buffer(4,468),"Channel: " .. buffer(0,4):le_uint())
	deviceinfo_dissector(buffer(4,468),pinfo,deviceinfotree)
end


function AVDigitalChannelGetProp_dissector(buffer,pinfo,tree)
	if buffer:len() == 4 then
		treeadd(tree,buffer(0,4),"Channel:",le_units)
	else
		local deviceinfotree = tree:add(OBCP,buffer(4,468),"Channel: " .. buffer(0,4):le_uint())
		deviceinfo_dissector(buffer(4,468),pinfo,deviceinfotree)
	end
end


function AVDigitalChannelDel_dissector(buffer,pinfo,tree)
	treeadd(tree,buffer(0,4),"Channel:",le_uints)
end


function AVDigitalChannelGetDevList_dissector(buffer,pinfo,tree)
	local tab = {
			{4,"Count:",le_uints},}
	treeadd_tab(tree,buffer(0,4),tab)
	for i = 0,63,1 do
		local deviceinfotree = tree:add(OBCP,buffer(4+468*i,468),"Device: " .. (i + 1))
		deviceinfo_dissector(buffer(4+468*i,468),pinfo,deviceinfotree)
	end
end


function AVDigitalChannelGetChannelList_dissector(buffer,pinfo,tree)
	local tab = {
			{4,"Count:",le_uints},
			{64,"InUsr:",},}
	treeadd_tab(tree,buffer(0,68),tab)
	for i = 0,63,1 do
		local channelinfotree = tree:add(OBCP,buffer(68+472*i,472),"Channel: " .. (i + 1))
		channelinfo_dissector(buffer(68+472*i,472),pinfo,channelinfotree)
	end
end


--[[
================================================
                     轮巡通道管理
================================================
]]

codeformat = {
	[0] = "NONE",
	[1] = "MPEG4",
	[2] = "M-JPEG",
	[4] = "H264",}
	
	
function tourchannelstate_dissector(buffer,pinfo,tree)
	local tab = {
			{4,"Channel:",le_uints},
			{4,"Index:",le_uints},
			{1,"Decoding:",nil,enable},
			{1,"Format:",nil,codeformat},
			{1,"Muxing:",},
			{1,"Transport:",},
			{4,"Loads:",le_uints},
			{4,"Width:",le_uints},
			{4,"Heigth:",le_uints},
			{1,"Mode:",le_uints},
			{3,"Res:",tostring},
			{4,"VideoFrameRate:",le_uints},
			{4,"AudioFrameRate:",le_uints},
			{4,"DecodedVideoFrame:",le_uints},
			{4,"DecodedAudioFrame:",le_uints},}
		treeadd_tab(tree,buffer(0,44),tab)
end


function AVTourChannelAdd_dissector(buffer,pinfo,tree)
	local tab = {
			{4,"Channel:",le_uints},
			{4,"Index:",le_uints},}
	treeadd_tab(tree,buffer(0,8),tab)
	deviceinfo_dissector(buffer(8,468),pinfo,tree)
end


function AVTourChannelModifyProp_dissector(buffer,pinfo,tree)
	local tab = {
			{4,"Channel:",le_uints},
			{4,"Index:",le_uints},}
	treeadd_tab(tree,buffer(0,8),tab)
	deviceinfo_dissector(buffer(8,468),pinfo,tree)
end


function AVTourChannelGetProp_dissector(buffer,pinfo,tree)
	if buffer:len() == 8 then
		local tab = {
				{4,"Channel:",le_uints},
				{4,"Index:",le_uints},}
		treeadd_tab(tree,buffer(0,8),tab)	
	else
		local tab = {
				{4,"Channel:",le_uints},
				{4,"Index:",le_uints},}
		treeadd_tab(tree,buffer(0,8),tab)
		deviceinfo_dissector(buffer(8,468),pinfo,tree)
	end
end


function AVTourChannelDel_dissector(buffer,pinfo,tree)
	local tab = {
			{4,"Channel:",le_uints},
			{4,"Index:",le_uints},}
	treeadd_tab(tree,buffer(0,8),tab)	
end


function AVTourChannelGetState_dissector(buffer,pinfo,tree)
	if buffer:len() == 8 then
		local tab = {
				{4,"Channel:",le_uints},
				{4,"Index:",le_uints},}
		treeadd_tab(tree,buffer(0,8),tab)	
	else
		tourchannelstate_dissector(buffer,pinfo,tree)
	end
end


function AVTourChannelGetInterval_dissector(buffer,pinfo,tree)
	if buffer:len() == 8 then
		local tab = {
				{4,"Channel:",le_uints},
				{2,"Interval:",le_uints},
				{2,"Res:",tostring},}
		treeadd_tab(tree,buffer(0,8),tab)	
	else
		local tab = {
				{4,"Channel:",le_uints},}
		treeadd_tab(tree,buffer(0,4),tab)
	end
end


function AVTourChannelSetInterval_dissector(buffer,pinfo,tree)
	if buffer:len() == 8 then
		local tab = {
				{4,"Channel:",le_uints},
				{2,"Interval:",le_uints},
				{2,"Res:",tostring},}
		treeadd_tab(tree,buffer(0,8),tab)	
	else
		local tab = {
				{4,"Channel:",le_uints},}
		treeadd_tab(tree,buffer(0,4),tab)
	end
end


function AVTourChannelGetDevList_dissector(buffer,pinfo,tree)
	local tab = {
			{4,"Count:",le_uints},}
	treeadd_tab(tree,buffer(0,4),tab)
	for i = 0,63,1 do
		local deviceinfotree = tree:add(OBCP,buffer(4+468*i,468),"Device: " .. (i + 1))
		deviceinfo_dissector(buffer(4+468*i,468),pinfo,deviceinfotree)
	end
end


function AVTourChannelGetChannelList_dissector(buffer,pinfo,tree)
	local tab = {
			{4,"Count:",le_uints},
			{64,"InUsr:",},}
	treeadd_tab(tree,buffer(0,68),tab)
	for i = 0,63,1 do
		local channelinfotree = tree:add(OBCP,buffer(68+472*i,472),"Channel: " .. (i + 1))
		channelinfo_dissector(buffer(68+472*i,472),pinfo,channelinfotree)
	end
end


--[[
================================================
                     解码状态管理
================================================
]]


function channelstate_dissector(buffer,pinfo,tree)
	local tab = {
			{4,"Channel:",le_uints},
			{1,"Decoding:",nil,enable},
			{1,"Format:",nil,codeformat},
			{1,"Muxing:",},
			{1,"Transport:",},
			{4,"Loads:",le_uints},
			{4,"Width:",le_uints},
			{4,"Heigth:",le_uints},
			{1,"Mode:",le_uints},
			{3,"Res:",tostring},
			{4,"VideoFrameRate:",le_uints},
			{4,"AudioFrameRate:",le_uints},
			{4,"DecodedVideoFrame:",le_uints},
			{4,"DecodedAudioFrame:",le_uints},}
		treeadd_tab(tree,buffer(0,40),tab)
end


function AVTourChannelGetConnectionState_dissector(buffer,pinfo,tree)
	if buffer:len() == 4 then
		local tab = {
				{4,"Channel:",le_uints},}
		treeadd_tab(tree,buffer(0,4),tab)
	else
		local tab = {
				{4,"Channel:",le_uints},
				{1,"Decoding:",nil,enable},
				{3,"Res:",tostring},
				{4,"Bitrate:",le_uints},
				{4,"StreamMode:",},
				{4,"DecodingMode:",},}
		treeadd_tab(tree,buffer(0,20),tab)
		deviceinfo_dissector(buffer(20,468),pinfo,tree)
	end
end


function AVTourChannelGetDecodingChannelList_dissector(buffer,pinfo,tree)
	local tab = {
			{4,"Count:",le_uints},}
	treeadd_tab(tree,buffer(0,4),tab)
	for i = 0,63,1 do
		local channelstatetree = tree:add(OBCP,buffer(4+40*i,40),"Channel: " .. (i + 1))
		channelstate_dissector(buffer(4+40*i,40),pinfo,channelstatetree)
	end
end


--[[
================================================
                     录像控制
================================================
]]


--[[
================================================
                     云台控制
================================================
]]


--[[
================================================
                     资料检索
================================================
]]


--[[
================================================
                     资料备份
================================================
]]


--[[
================================================
                     显示控制
================================================
]]

displaystatus = {
	[1] = "YES",
	[0] = "NO",}
	
displaysystem = {
	[0] = "UNKNOWN",
	[1] = "PAL",
	[2] = "NTSC",}
	
screenmode = {
	[1] = "NORMAL",
	[0] = "BIG SCREEN",}
	
	
	
local monitortype = {
	[0] = "NONE",
	[1] = "VGA",
	[2] = "BNC",
	[3] = "HDMI",
	[4] = "DVI",
	[5] = "UNKNOWN",
	[8] = "UNKNOWN",}


function monitor_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Type:",nil,monitortype},
			{3,"Vo:",uints},}
	treeadd_tab(tree,buffer(0,4),tab)
end


function vostatus_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"DisplayStatus:",nil,displaystatus},
			{1,"System:",nil,displaysystem},
			{1,"Layout:",le_uints},
			{1,"ScreenMode:",nil,screenmode},
			{4,"Res:",tostring},}
	treeadd_tab(tree,buffer(0,8),tab)
end


function layoutstatus_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"Channel:",le_uints},
			{1,"FrameRate:",le_uints},
			{2,"Res:",tostring},}
	treeadd_tab(tree,buffer(0,4),tab)
end


function SceneMonitorGetCfg_dissector(buffer,pinfo,tree)
	if buffer:len() == 4 then
		monitor_dissector(buffer(0,4),pinfo,tree)
	else
		monitor_dissector(buffer(0,4),pinfo,tree)
		local tab = {
			{1,"Enabled:",nil,enable},
			{2,"Res:",tostring},
			{1,"Depth:",le_uints},
			{2,"Width:",le_uints},
			{2,"Heigth:",le_uints},
			{2,"HRefreshRate:",le_uints},
			{2,"VRefreshRate:",le_uints},}
		treeadd_tab(tree,buffer(4,12),tab)
	end
end


function SceneMonitorSetCfg_dissector(buffer,pinfo,tree)
	if buffer:len() == 4 then
		monitor_dissector(buffer(0,4),pinfo,tree)
	else
		monitor_dissector(buffer(0,4),pinfo,tree)
		local tab = {
			{1,"Enabled:",nil,enable},
			{2,"Res:",tostring},
			{1,"Depth:",le_uints},
			{2,"Width:",le_uints},
			{2,"Heigth:",le_uints},
			{2,"HRefreshRate:",le_uints},
			{2,"VRefreshRate:",le_uints},}
		treeadd_tab(tree,buffer(4,12),tab)
	end
end


function SceneMonitorGetPicture_dissector(buffer,pinfo,tree)
	if buffer:len() == 4 then
		monitor_dissector(buffer(0,4),pinfo,tree)
	else
		monitor_dissector(buffer(0,4),pinfo,tree)
		local tab = {
			{1,"Brightness:",le_uints},
			{1,"Contrast:",le_uints},
			{1,"Saturation:",le_uints},
			{1,"Hue:",le_uints},}
		treeadd_tab(tree,buffer(4,4),tab)
	end
end


function SceneMonitorSetPicture_dissector(buffer,pinfo,tree)
	if buffer:len() == 4 then
		monitor_dissector(buffer(0,4),pinfo,tree)
	else
		monitor_dissector(buffer(0,4),pinfo,tree)
		local tab = {
			{1,"Brightness:",le_uints},
			{1,"Contrast:",le_uints},
			{1,"Saturation:",le_uints},
			{1,"Hue:",le_uints},}
		treeadd_tab(tree,buffer(4,4),tab)
	end
end


function SceneMonitorGetMargin_dissector(buffer,pinfo,tree)
	if buffer:len() == 4 then
		monitor_dissector(buffer(0,4),pinfo,tree)
	else
		monitor_dissector(buffer(0,4),pinfo,tree)
		local tab = {
			{2,"Left:",uints},
			{2,"Right:",uints},
			{2,"Top:",uints},
			{2,"Bottom:",uints},}
		treeadd_tab(tree,buffer(4,8),tab)
	end
end


function SceneMonitorSetMargin_dissector(buffer,pinfo,tree)
	if buffer:len() == 4 then
		monitor_dissector(buffer(0,4),pinfo,tree)
	else
		monitor_dissector(buffer(0,4),pinfo,tree)
		local tab = {
			{2,"Left:",uints},
			{2,"Right:",uints},
			{2,"Top:",uints},
			{2,"Bottom:",uints},}
		treeadd_tab(tree,buffer(4,4),tab)
	end
end


function SceneMonitorGetLayout_dissector(buffer,pinfo,tree)
	if buffer:len() == 4 then
		monitor_dissector(buffer(0,4),pinfo,tree)
	else
		monitor_dissector(buffer(0,4),pinfo,tree)
		local tab = {
			{1,"Layout:",uints},
			{3,"Res:",tostring},}
		treeadd_tab(tree,buffer(4,4),tab)
	end
end


function SceneMonitorSetLayout_dissector(buffer,pinfo,tree)
	if buffer:len() == 4 then
		monitor_dissector(buffer(0,4),pinfo,tree)
	else
		monitor_dissector(buffer(0,4),pinfo,tree)
		local tab = {
			{1,"Layout:",uints},
			{3,"Res:",tostring},}
		treeadd_tab(tree,buffer(4,4),tab)
	end
end


function SceneMonitorGetStatus_dissector(buffer,pinfo,tree)
	if buffer:len() == 4 then
		monitor_dissector(buffer(0,4),pinfo,tree)
	else
		monitor_dissector(buffer(0,4),pinfo,tree)
		local tab = {
			{4,"Count:",uints},}
		treeadd_tab(tree,buffer(4,4),tab)
		for i = 0, 15,1 do
			local voStatusListtree = tree:add(OBCP,buffer(8+8*i,8),"voStatus: " .. (i+1))
			vostatus_dissector(buffer(8+8*i,8),pinfo,voStatusListtree)
		end
	end
end


function SceneMonitorGetLayoutStatus_dissector(buffer,pinfo,tree)
	if buffer:len() == 4 then
		monitor_dissector(buffer(0,4),pinfo,tree)
	else
		monitor_dissector(buffer(0,4),pinfo,tree)
		local tab = {
			{4,"Layout:",le_uints},}
		treeadd_tab(tree,buffer(4,4),tab)
		for i = 0, 15,1 do
			local LayoutStatustree = tree:add(OBCP,buffer(8+4*i,4),"voStatus: " .. (i+1))
			layoutstatus_dissector(buffer(8+4*i,4),pinfo,LayoutStatustree)
		end
	end
end


--[[
================================================
                     窗格操作
================================================
]]

panestatus = {
	[0] = "IDLE",
	[1] = "PREVIEW",
	[2] = "PLAYBACK",}


function panestatus_dissector(buffer,pinfo,tree)
	local tab = {
			{2,"X1:",uints},
			{2,"Y1:",uints},
			{2,"X2:",uints},
			{2,"Y2:",uints},}
	treeadd_tab(tree,buffer(0,8),tab)
end


function rect_dissector(buffer,pinfo,tree)
	local tab = {
			{1,"PaneStatus:",nil,panestatus},
			{1,"Channel:",le_uints},
			{2,"Res:",tostring},}
	treeadd_tab(tree,buffer(0,4),tab)
end


function ScenePaneList_dissector(buffer,pinfo,tree)
	if buffer:len() == 8 then
		monitor_dissector(buffer(0,4),pinfo,tree)
		local tab = {
			{4,"Panes:",le_uints},}
		treeadd_tab(tree,buffer(4,4),tab)
	else
		monitor_dissector(buffer(0,4),pinfo,tree)
		local tab = {
			{4,"Layout:",le_uints},}
		treeadd_tab(tree,buffer(4,4),tab)
		for i = 0, 15,1 do
			local panestatusstree = tree:add(OBCP,buffer(8+4*i,4),"PaneStatus: " .. (i+1))
			panestatus_dissector(buffer(8+4*i,4),pinfo,panestatusstree)
		end
	end
end


function ScenePaneStart_dissector(buffer,pinfo,tree)
	monitor_dissector(buffer(0,4),pinfo,tree)
	local tab = {
		{4,"Panes:",le_uints},}
	treeadd_tab(tree,buffer(4,4),tab)
end


function ScenePaneStop_dissector(buffer,pinfo,tree)
	monitor_dissector(buffer(0,4),pinfo,tree)
	local tab = {
		{4,"Panes:",le_uints},}
	treeadd_tab(tree,buffer(4,4),tab)
end


function ScenePaneShift_dissector(buffer,pinfo,tree)
	if buffer:len() == 4 then
		monitor_dissector(buffer(0,4),pinfo,tree)
	else
		monitor_dissector(buffer(0,4),pinfo,tree)
		local tab = {
			{1,"Pane:",le_uints},
			{3,"Res:",tostring},}
		treeadd_tab(tree,buffer(4,4),tab)
	end
end


function ScenePaneSwap_dissector(buffer,pinfo,tree)
	if buffer:len() == 4 then
		monitor_dissector(buffer(0,4),pinfo,tree)
	else
		monitor_dissector(buffer(0,4),pinfo,tree)
		local tab = {
			{1,"Pane:",le_uints},
			{1,"XPane:",le_uints},
			{2,"Res:",tostring},}
		treeadd_tab(tree,buffer(4,4),tab)
	end
end


function ScenePaneSend_dissector(buffer,pinfo,tree)
	if buffer:len() == 4 then
		monitor_dissector(buffer(0,4),pinfo,tree)
	else
		monitor_dissector(buffer(0,4),pinfo,tree)
		local tab = {
			{1,"Pane:",le_uints},
			{1,"DstPane:",le_uints},
			{1,"DstMonitor:",le_uints},
			{1,"Res:",tostring},}
		treeadd_tab(tree,buffer(4,4),tab)
	end
end


function ScenePaneZoom_dissector(buffer,pinfo,tree)
	if buffer:len() == 8 then
		monitor_dissector(buffer(0,4),pinfo,tree)
		local tab = {
			{1,"Pane:",le_uints},
			{1,"Ratio:",le_uints},
			{2,"Res:",tostring},}
		treeadd_tab(tree,buffer(4,4),tab)
	else
		monitor_dissector(buffer(0,4),pinfo,tree)
		local tab = {
			{1,"Pane:",le_uints},
			{1,"Ratio:",le_uints},
			{2,"Res:",tostring},}
		treeadd_tab(tree,buffer(4,4),tab)
		rect_dissector(buffer(8,8),pinfo,tree)
	end
end


function ScenePaneMute_dissector(buffer,pinfo,tree)
	monitor_dissector(buffer(0,4),pinfo,tree)
	local tab = {
		{4,"Panes:",le_uints},}
	treeadd_tab(tree,buffer(4,4),tab)
end


--[[
================================================
                     现场预览
================================================
]]


function ScenePreviewGetCfg_dissector(buffer,pinfo,tree)
	if buffer:len() == 8 then
		monitor_dissector(buffer(0,4),pinfo,tree)
		local tab = {
			{4,"Series:",uints},}
		treeadd_tab(tree,buffer(4,4),tab)
	else
		monitor_dissector(buffer(0,4),pinfo,tree)
		local tab = {
			{4,"Series:",uints},
			{1,"Layout:",uints},
			{1,"Enabled:",uints},
			{1,"Res:",tostring},
			{1,"StartIndex:",uints},}
		treeadd_tab(tree,buffer(4,8),tab)
		for i = 0,15,1 do
			local deviceinfotree = tree:add(OBCP,buffer(12+1*i,1),"Channel	" .. (i + 1) .. ":" .. buffer(12+1*i,1))
		end
	end
end


function ScenePreviewSetCfg_dissector(buffer,pinfo,tree)
	if buffer:len() == 8 then
		monitor_dissector(buffer(0,4),pinfo,tree)
		local tab = {
			{4,"Series:",uints},}
		treeadd_tab(tree,buffer(4,4),tab)
	else
		monitor_dissector(buffer(0,4),pinfo,tree)
		local tab = {
			{4,"Series:",uints},
			{1,"Layout:",uints},
			{1,"Enabled:",uints},
			{1,"Res:",tostring},
			{1,"StartIndex:",uints},}
		treeadd_tab(tree,buffer(4,8),tab)
		for i = 0,15,1 do
			local deviceinfotree = tree:add(OBCP,buffer(12+1*i,1),"Channel	" .. (i + 1) .. ":" .. buffer(12+1*i,1))
		end
	end
end


function ScenePreviewRotate_dissector(buffer,pinfo,tree)
	if buffer:len() == 4 then
		monitor_dissector(buffer(0,4),pinfo,tree)
	else
		monitor_dissector(buffer(0,4),pinfo,tree)
		local tab = {
			{4,"Series:",le_uints},
			{1,"Index:",le_uints},
			{1,"Layout:",le_uints},
			{1,"Direction:",},
			{1,"Res:",tostring},}
		treeadd_tab(tree,buffer(4,8),tab)
	end
end


function ScenePreviewGetTour_dissector(buffer,pinfo,tree)
	if buffer:len() == 8 then
		monitor_dissector(buffer(0,4),pinfo,tree)
		local tab = {
			{4,"Series:",le_uints},}
		treeadd_tab(tree,buffer(4,4),tab)
	else
		monitor_dissector(buffer(0,4),pinfo,tree)
		local tab = {
			{4,"Series:",le_uints},
			{1,"Enabled:",nil,enable},
			{1,"Layout:",le_uints},
			{2,"Interval:",le_uints},}
		treeadd_tab(tree,buffer(4,8),tab)
		for i = 0,15,1 do
			local deviceinfotree = tree:add(OBCP,buffer(12+472*i,468),"Channel: " .. (i + 1))
			deviceinfo_dissector(buffer(12+472*i,468),pinfo,deviceinfotree)
		end
	end
end


function ScenePreviewSetTour_dissector(buffer,pinfo,tree)
	if buffer:len() == 8 then
		monitor_dissector(buffer(0,4),pinfo,tree)
		local tab = {
			{4,"Series:",le_uints},}
		treeadd_tab(tree,buffer(4,4),tab)
	else
		monitor_dissector(buffer(0,4),pinfo,tree)
		local tab = {
			{4,"Series:",le_uints},
			{1,"Enabled:",nil,enable},
			{1,"Layout:",le_uints},
			{2,"Interval:",le_uints},}
		treeadd_tab(tree,buffer(4,8),tab)
		for i = 0,15,1 do
			local deviceinfotree = tree:add(OBCP,buffer(12+472*i,468),"Channel: " .. (i + 1))
			deviceinfo_dissector(buffer(12+472*i,468),pinfo,deviceinfotree)
		end
	end
end


function ScenePreviewStartTour_dissector(buffer,pinfo,tree)
	if buffer:len() == 8 then
		monitor_dissector(buffer(0,4),pinfo,tree)
		local tab = {
			{4,"Channel:",le_uints},}
		treeadd_tab(tree,buffer(4,4),tab)
	else
		monitor_dissector(buffer(0,4),pinfo,tree)
	end
end


function ScenePreviewStopTour_dissector(buffer,pinfo,tree)
	if buffer:len() == 8 then
		monitor_dissector(buffer(0,4),pinfo,tree)
		local tab = {
			{4,"Channel:",le_uints},}
		treeadd_tab(tree,buffer(4,4),tab)
	else
		monitor_dissector(buffer(0,4),pinfo,tree)
	end
end


function SceneMonitorGetDecodeChnBindState_dissector(buffer,pinfo,tree)
	local tab = {
		{4,"Count:",le_uints},}
	treeadd_tab(tree,buffer(0,4),tab)
end


--[[
================================================
                     本地回放
================================================
]]


--[[
================================================
                     现场音效
================================================
]]


--[[
================================================
                     人机界面设备
================================================
]]


--[[
================================================
                     镜头管理
================================================
]]


--[[
================================================
                     文件读写
================================================
]]

local schema = {
	[1] = "NORMAL",
	[2] = "MEMORY",
	[3] = "SYSIMAGE",}


function FileOpen_dissector(buffer,pinfo,tree)
	if buffer:len() == 132 then
		local tab = {
			{4,"Schema:",le_uints,schema},
			{128,"Path:",strings},}
		treeadd_tab(tree,buffer,tab)
	else
		local tab = {
			{4,"FileID:",le_uints},
			{buffer:len() - 4,"Path:",strings},}
		treeadd_tab(tree,buffer,tab)
	end
end



function FileWrite_dissector(buffer,pinfo,tree)
	if buffer:len() == 8 then
		local tab = {
			{4,"FileID:",le_uints},
			{4,"Length:",le_uints},}
		treeadd_tab(tree,buffer,tab)
	else
		local tab = {
			{4,"FileID:",le_uints},
			{4,"Length:",le_uints},
			{buffer:len() - 8,"Data:",tostring},}
		treeadd_tab(tree,buffer,tab)
	end
end


--[[
================================================
                     现场预览
================================================
]]


--[[
================================================
                     双向语音
================================================
]]


--[[
================================================
                     录像下载
================================================
]]


--[[
================================================
                     远程回放
================================================
]]


--[[
================================================
                     串口隧道
================================================
]]


--[[
================================================
                     车道管理
================================================
]]


--[[
================================================
                     事件高级参数
================================================
]]


--[[
================================================
                     闪光灯参数
================================================
]]


--[[
================================================
                     信号灯参数
================================================
]]


--[[
================================================
                     红灯校正
================================================
]]


--[[
================================================
                     雷达参数
================================================
]]


--[[
================================================
                     线圈参数
================================================
]]


--[[
================================================
                     抓拍参数
================================================
]]


--[[
================================================
                     OSD参数
================================================
]]


--[[
================================================
                     智能算法管理
================================================
]]





local dissector = {
	["00000000"] = SystemHello_dissector,
	["00000001"] = SystemState_dissector,
	["00000002"] = SystemVersion_dissector,
	["00000003"] = SystemDescribe_dissector,
	["00000005"] = SystemGetModules_dissector,
	["00000007"] = SystemGetIPCDVSStatus_dissector,
	["00000011"] = SystemGetIdentity_dissector,
	["00000012"] = SystemSetIdentity_dissector,
	["00000013"] = SystemGetTime_dissector,
	["00000014"] = SystemSetTime_dissector,
	["00000015"] = SystemGetTimeStyle_dissector,
	["00000016"] = SystemSetTimeStyle_dissector,
	["00000017"] = SystemGetStatus_dissector,
	["00000019"] = SystemGetSDCodeCapbility_dissector,
	["0000001B"] = SystemGetHDCodeCapbility_dissector,
	["00000081"] = SystemPackageInstall_dissector,
	["00000082"] = SystemPackageRemove_dissector,
	["00000083"] = SystemPackageList_dissector,
	["00000091"] = SystemShell_dissector,
	["00000092"] = SystemTop_dissector,
	["00000093"] = SystemReboot_dissector,
	["00000094"] = SystemHalt_dissector,
	["00000095"] = SystemExport_dissector,
	["00000096"] = SystemImport_dissector,
	["00000097"] = SystemRestore_dissector,
	["00000098"] = SystemUpgrade_dissector,
	["00000099"] = SystemBurnState_dissector,
	["0000009b"] = SystemUpgradeCheck_dissector,
	["0000aa01"] = SystemLogOpen_dissector,
	["0000aa02"] = SystemLogClose_dissector,
	["0000aa03"] = SystemLogFetch_dissector,
	["0000aa04"] = SystemLogExport_dissector,
	["0000aa05"] = SystemLogPurge_dissector,
	["00010000"] = NetLinkState_dissector,
	["00010001"] = NetLinkGetCfg_dissector,
	["00010002"] = NetLinkSetCfg_dissector,
	["00010003"] = NetLinkStartUp_dissector,
	["00010004"] = NetLinkShutDown_dissector,
	["000100ff"] = NetLinkTest_dissector,
	["00010101"] = NetServiceGetAddrs_dissector,
	["00010102"] = NetServiceSetAddrs_dissector,
	["00010103"] = NetServiceGetAlerts_dissector,
	["00010104"] = NetServiceSetAlerts_dissector,
	["00010105"] = NetServiceGetSmtp_dissector,
	["00010106"] = NetServiceSetSmtp_dissector,
	["00010107"] = NetServiceGetSnmp_dissector,
	["00010108"] = NetServiceSetSnmp_dissector,
	["00010109"] = NetServiceGetCenters_dissector,
	["0001010a"] = NetServiceSetCenters_dissector,
	["00010121"] = NetServiceGetRtspCfg_dissector,
	["00010122"] = NetServiceSetRtspCfg_dissector,
	["00010123"] = NetServiceGetFtpCfg_dissector,
	["00010124"] = NetServiceSetFtpCfg_dissector,
	["00010125"] = NetServiceGetOnvifCfg_dissector,
	["00010126"] = NetServiceSetOnvifCfg_dissector,
	["00010127"] = NetClientGetFtpCfg_dissector,
	["00010128"] = NetClientSetFtpCfg_dissector,
	["00010129"] = NetServiceGetSipCfg_dissector,
	["00010130"] = NetServiceSetSipCfg_dissector,
	["000101ff"] = NetServiceTest_dissector,
	["0001aa01"] = NetReportGetCfg_dissector,
	["0001aa02"] = NetReportSetCfg_dissector,
	["0001dd00"] = NetDiscoveryHello_dissector,
	["0001dd01"] = NetDiscoveryState_dissector,
	["0001dd02"] = NetDiscoverySetParam_dissector,
	["0001ee00"] = NetRegistryState_dissector,
	["0001ee01"] = NetRegistryGetCfg_dissector,
	["0001ee02"] = NetRegistrySetCfg_dissector,
	["0001ee03"] = NetRegistryLogin_dissector,
	["0001ee04"] = NetRegistryLogoff_dissector,
	["00020001"] = SecuritySessionLogin_dissector,
	["00020002"] = SecuritySessionLogout_dissector,
	["00020003"] = SecuritySessionList_dissector,
	["00020005"] = SecuritySessionGet_dissector,
	["00020006"] = SecuritySessionSet_dissector,
	["00020101"] = SecurityUserAdd_dissector,
	["00020102"] = SecurityUserEdit_dissector,
	["00020103"] = SecurityUserDel_dissector,
	["00020104"] = SecurityUserList_dissector,
	["00020105"] = SecurityUserPasswd_dissector,
	["00020107"] = SecurityUserGetPrivilege_dissector,
	["00020108"] = SecurityUserSetPrivilege_dissector,
	["00020201"] = SecurityRoleAdd_dissector,
	["00020202"] = SecurityRoleEdit_dissector,
	["00020203"] = SecurityRoleDel_dissector,
	["00020204"] = SecurityRoleList_dissector,
	["00020205"] = SecurityRoleGetPrivilege_dissector,
	["00020206"] = SecurityRoleSetPrivilege_dissector,
	["00020207"] = SecurityRoleGetPrivilegeDesp_dissector,
	["00040001"] = StorageGetCfg_dissector,
	["00040002"] = StorageSetCfg_dissector,
	["00040101"] = StorageDiskList_dissector,
	["00040102"] = StorageDiskDescribe_dissector,
	["00040103"] = StorageDiskState_dissector,
	["00040104"] = StorageDiskWaken_dissector,
	["00040105"] = StorageDiskUse_dissector,
	["00040107"] = StorageDiskGetUsages_dissector,
	["00040108"] = StorageDiskSetUsages_dissector,
	["00040109"] = StorageDiskInfo_dissector,
	["0004010b"] = StorageDiskGetFormatStates_dissector,
	["0004010f"] = StorageDiskFormat_dissector,
	["00040110"] = StorageDiskMount_dissector,
	["00040121"] = StorageDiskGetAlbums_dissector,
	["00040122"] = StorageDiskSetAlbums_dissector,
	["00040123"] = StorageDiskGetSchemes_dissector,
	["00040124"] = StorageDiskSetSchemes_dissector,
	["00040201"] = StorageDiskGetNfs_dissector,
	["00040202"] = StorageDiskSetNfs_dissector,
	["00080001"] = UartPortGetCfg_dissector,
	["00080002"] = UartPortSetCfg_dissector,
	["00080003"] = UartCipherList_dissector,
	["00080004"] = UartCipherInstall_dissector,
	["00080005"] = UartSnoopGetCfg_dissector,
	["00080006"] = UartSnoopSetCfg_dissector,
	["00080007"] = UartAgentGetCfg_dissector,
	["00080008"] = UartAgentSetCfg_dissector,
	["00080009"] = UartFpgaGetCfg_dissector,
	["00080010"] = UartFpgaSetCfg_dissector,
	["00aa0000"] = AlertAlarmState_dissector,
	["00aa0001"] = AlertAlarmArm_dissector,
	["00aa0002"] = AlertAlarmDisarm_dissector,
	["00aa0003"] = AlertAlarmBypass_dissector,
	["00aa0004"] = AlertAlarmReset_dissector,
	["00aa0005"] = AlertAlarmPasswd_dissector,
	["00aa0007"] = AlertAlarmGetcfg_dissector,
	["00aa0008"] = AlertAlarmSetcfg_dissector,
	["00aa0009"] = AlertAlarmDefenceGetcfg_dissector,
	["00aa000a"] = AlertAlarmDefenceSetcfg_dissector,
	["00aa0100"] = AlertAlarmInputState_dissector,
	["00aa0101"] = AlertAlarmInputGetcfg_dissector,
	["00aa0102"] = AlertAlarmInputSetcfg_dissector,
	["00aa0200"] = AlertAlarmOutputState_dissector,
	["00aa0201"] = AlertAlarmOutputGetcfg_dissector,
	["00aa0202"] = AlertAlarmOutputSetcfg_dissector,
	["00aa0203"] = AlertAlarmOutputStart_dissector,
	["00aa0204"] = AlertAlarmOutputSop_dissector,
	["00aa0301"] = AlertActionGetcfg_dissector,
	["00aa0302"] = AlertActionSetcfg_dissector,
	["00aa0303"] = AlertActionAck_dissector,
	["00aa0304"] = AlertActionRaise_dissector,
	["00aa0305"] = EventActionGetcfg_dissector,
	["00aa0306"] = EventActionSetcfg_dissector,
	["00aa0308"] = EventActionRaiseAlertIn_dissector,
	["00aa030a"] = EventActionRaiseAlertOut_dissector,
	["00aa0351"] = EventCameraCapture_dissector,
	["00aa0352"] = EventCameraCaptureLocal_dissector,
	["00aa9000"] = EventSubScribe_dissector,
	["00aa9001"] = EventSubScribeStart_dissector,
	["00aa9002"] = EventSubScribeEnd_dissector,
	["00030000"] = AVDescribe_dissector,
	["00030001"] = AVGetCfg_dissector,
	["00030001"] = AVSetCfg_dissector,
	["00030101"] = AVInputGetCfg_dissector,
	["00030102"] = AVInputSetCfg_dissector,
	["00030901"] = AVInputGetCfgv2_dissector,
	["00030902"] = AVInputSetCfgv2_dissector,
	["00030103"] = AVInputGetPictureCfg_dissector,
	["00030104"] = AVInputSetPictureCfg_dissector,
	["00030105"] = AVInputGetImprintCfg_dissector,
	["00030106"] = AVInputSetImprintCfg_dissector,
	["00030115"] = AVInputGetImprintText_dissector,
	["00030116"] = AVInputSetImprintText_dissector,
	["00030107"] = AVInputGetMaskCfg_dissector,
	["00030108"] = AVInputSetMaskCfg_dissector,
	["00030109"] = AVInputGetImprintFontCfg_dissector,
	["0003010a"] = AVInputSetImprintFontCfg_dissector,
	["00030180"] = AVInputGetViState_dissector,
	["00030181"] = AVInputGetViType_dissector,
	["00030182"] = AVInputSetViType_dissector,
	["00030183"] = AVInputGetViResolution_dissector,
	["00030184"] = AVInputSetViResolution_dissector,
	["00030201"] = AVOutputGetMaskCfg_dissector,
	["00030202"] = AVOutputSetMaskCfg_dissector,
	["00030203"] = AVOutputGetImprintCfg_dissector,
	["00030204"] = AVOutputSetImprintCfg_dissector,
	["00030301"] = AVEncoderGetCfg_dissector,
	["00030302"] = AVEncoderSetCfg_dissector,
	["00030303"] = AVEncoderGetProfile_dissector,
	["00030304"] = AVEncoderSetProfile_dissector,
	["00030305"] = AVEncoderGetCurrentProfile_dissector,
	["00030306"] = AVEncoderSetCurrentProfile_dissector,
	["00030309"] = AVEncoderGetROICfg_dissector,
	["0003030a"] = AVEncoderSetROICfg_dissector,
	["00030501"] = AVDetectGetLossCfg_dissector,
	["00030502"] = AVDetectSetLossCfg_dissector,
	["00030503"] = AVDetectGetMotionCfg_dissector,
	["00030504"] = AVDetectSetMotionCfg_dissector,
	["00030505"] = AVDetectGetBlockCfg_dissector,
	["00030506"] = AVDetectSetBlockCfg_dissector,
	["00030507"] = AVLossGetTime_dissector,
	["00030508"] = AVLossSetTime_dissector,
	["00030701"] = AVDigitalChannelSearch_dissector,
	["00030702"] = AVDigitalChannelAdd_dissector,
	["00030703"] = AVDigitalChannelFetchSearchInfo_dissector,
	["00030704"] = AVDigitalChannelModifyProp_dissector,
	["00030705"] = AVDigitalChannelGetProp_dissector,
	["00030706"] = AVDigitalChannelDel_dissector,
	["00030707"] = AVDigitalChannelGetState_dissector,
	["00030708"] = AVDigitalChannelSync_dissector,
	["0003070b"] = AVDigitalChannelGetDevList_dissector,
	["0003070f"] = AVDigitalChannelGetChannelList_dissector,
	["00030802"] = AVTourChannelAdd_dissector,
	["00030804"] = AVTourChannelModifyProp_dissector,
	["00030805"] = AVTourChannelGetProp_dissector,
	["00030806"] = AVTourChannelDel_dissector,
	["00030807"] = AVTourChannelGetState_dissector,
	["00030809"] = AVTourChannelGetInterval_dissector,
	["0003080a"] = AVTourChannelSetInterval_dissector,
	["0003080b"] = AVTourChannelGetDevList_dissector,
	["0003080f"] = AVTourChannelGetChannelList_dissector,
	["00030880"] = AVTourChannelGetConnectionState_dissector,
	["00030881"] = AVTourChannelGetDecodingChannelList_dissector,
	["00031000"] = AVRecordState_dissector,
	["00031001"] = AVRecordGetProfile_dissector,
	["00031002"] = AVRecordSetProfile_dissector,
	["00031003"] = AVRecordGetCfg_dissector,
	["00031004"] = AVRecordSetCfg_dissector,
	["00031015"] = AVRecordGetCfgv2_dissector,
	["00031016"] = AVRecordSetCfgv2_dissector,
	["00031005"] = AVRecordGetSchdule_dissector,
	["00031006"] = AVRecordSetSchdule_dissector,
	["00031011"] = AVRecordStart_dissector,
	["00031012"] = AVRecordStop_dissector,
	["00032001"] = AVCaptureGetCfg_dissector,
	["00032002"] = AVCaptureSetCfg_dissector,
	["00032003"] = AVCaptureGetSchdule_dissector,
	["00032004"] = AVCaptureSetSchdule_dissector,
	["00031101"] = AVDemoGetCfg_dissector,
	["00031102"] = AVDemoSetCfg_dissector,
	["00031103"] = AVDemoControl_dissector,
	["00031105"] = AVDemoGetPresets_dissector,
	["00031106"] = AVDemoSetPresets_dissector,
	["00031107"] = AVDemoGetPatrol_dissector,
	["00031108"] = AVDemoSetPatrol_dissector,
	["00031111"] = AVDemoGetCfgEx_dissector,
	["00031112"] = AVDemoSetCfgEx_dissector,
	["000a0001"] = ArchiveEventQueryOpen_dissector,
	["000a0002"] = ArchiveEventQueryClose_dissector,
	["000a0003"] = ArchiveEventQueryFetch_dissector,
	["000a0004"] = ArchiveEventQuerySort_dissector,
	["000a0005"] = ArchiveATMEventQueryOpen_dissector,
	["000a0011"] = ArchiveSDEventQueryOpen_dissector,
	["000a0012"] = ArchiveSDEventQueryClose_dissector,
	["000a0013"] = ArchiveSDEventQueryFetch_dissector,
	["000a0021"] = ArchiveImageQueryOpen_dissector,
	["000a0022"] = ArchiveImageQueryClose_dissector,
	["000a0023"] = ArchiveImageQueryFetch_dissector,
	["000a0102"] = ArchiveEventPlot_dissector,
	["000a0103"] = ArchiveEventCalendar_dissector,
	["000a0104"] = ArchiveEventDescribe_dissector,
	["000a0105"] = ArchiveEventXlate_dissector,
	["000a0106"] = ArchiveATMEventPlot_dissector,
	["000a0200"] = ArchiveBackupState_dissector,
	["000a0201"] = ArchiveBackupStart_dissector,
	["000a0202"] = ArchiveBackupStop_dissector,
	["000a0203"] = ArchiveBackupGetSchdule_dissector,
	["000a0204"] = ArchiveBackupSetSchdule_dissector,
	["000d0001"] = SceneMonitorGetCfg_dissector,
	["000d0002"] = SceneMonitorSetCfg_dissector,
	["000d0003"] = SceneMonitorGetPicture_dissector,
	["000d0004"] = SceneMonitorSetPicture_dissector,
	["000d0005"] = SceneMonitorGetMargin_dissector,
	["000d0006"] = SceneMonitorSetMargin_dissector,
	["000d0007"] = SceneMonitorGetLayout_dissector,
	["000d0008"] = SceneMonitorSetLayout_dissector,
	["000d0009"] = SceneMonitorGetStatus_dissector,
	["000d000b"] = SceneMonitorGetLayoutStatus_dissector,
	["000d0101"] = ScenePaneList_dissector,
	["000d0102"] = ScenePaneStart_dissector,
	["000d0103"] = ScenePaneStop_dissector,
	["000d0104"] = ScenePaneShift_dissector,
	["000d0105"] = ScenePaneSwap_dissector,
	["000d0106"] = ScenePaneSend_dissector,
	["000d0121"] = ScenePaneZoom_dissector,
	["000d0122"] = ScenePaneMute_dissector,
	["000d0201"] = ScenePreviewGetCfg_dissector,
	["000d0202"] = ScenePreviewSetCfg_dissector,
	["000d0203"] = ScenePreviewRotate_dissector,
	["000d0211"] = ScenePreviewGetTour_dissector,
	["000d0212"] = ScenePreviewSetTour_dissector,
	["000d0213"] = ScenePreviewStartTour_dissector,
	["000d0214"] = ScenePreviewStopTour_dissector,
	["000d0215"] = SceneMonitorGetDecodeChnBindState_dissector,
	["000d0300"] = ScenePlaybackState_dissector,
	["000d0301"] = ScenePlaybackOpen_dissector,
	["000d0302"] = ScenePlaybackStart_dissector,
	["000d0303"] = ScenePlaybackStop_dissector,
	["000d0304"] = ScenePlaybackClose_dissector,
	["000d0305"] = ScenePlaybackGet_dissector,
	["000d0306"] = ScenePlaybackSet_dissector,
	["000d0307"] = ScenePlaybackList_dissector,
	["000d0309"] = ScenePlaybackSeek_dissector,
	["000d030a"] = ScenePlaybackPip_dissector,
	["000d0801"] = SceneSoundGetCfg_dissector,
	["000d0802"] = SceneSoundSetCfg_dissector,
	["000d0803"] = SceneSoundGetVolume_dissector,
	["000d0804"] = SceneSoundSetVolume_dissector,
	["000d0a02"] = SceneHidPresent_dissector,
	["000d0a03"] = SceneHidGetCfg_dissector,
	["000d0a04"] = SceneHidSetCfg_dissector,
	["000d0a05"] = SceneHidGetTimeBar_dissector,
	["000d0a06"] = SceneHidGetTimeBar_dissector,
	["000d0aff"] = SceneHidSend_dissector,
	["00c00001"] = CameraGetCfg_dissector,
	["00c00002"] = CameraSetCfg_dissector,
	["00c00003"] = CameraImageProcessGetCfg_dissector,
	["00c00004"] = CameraImageProcessSetCfg_dissector,
	["00c00005"] = CameraDayNightGetCfg_dissector,
	["00c00006"] = CameraDayNightSetCfg_dissector,
	["00c00007"] = CameraAntiFlickerGetCfg_dissector,
	["00c00008"] = CameraAntiFlickerSetCfg_dissector,
	["00c00009"] = CameraExtendGetCfg_dissector,
	["00c0000a"] = CameraExtendSetCfg_dissector,
	["00c01001"] = CameraLumaValGetCfg_dissector,
	["00c01002"] = CameraLumaValSetCfg_dissector,
	["00c01003"] = CameraContrValGetCfg_dissector,
	["00c01004"] = CameraContrValSetCfg_dissector,
	["00c01005"] = CameraSatuValGetCfg_dissector,
	["00c01006"] = CameraSatuValSetCfg_dissector,
	["00c01007"] = CameraSpenValGetCfg_dissector,
	["00c01008"] = CameraSpenValSetCfg_dissector,
	["00c01009"] = CameraAntiFlickerGetCfg_dissector,
	["00c0100a"] = CameraAntiFlickerSetCfg_dissector,
	["00c0100b"] = CameraExpoModeGetCfg_dissector,
	["00c0100c"] = CameraExpoModeSetCfg_dissector,
	["00c0100d"] = CameraIrisTypeGetCfg_dissector,
	["00c0100e"] = CameraIrisTypeSetCfg_dissector,
	["00c0100f"] = CameraAWBTypeGetCfg_dissector,
	["00c01010"] = CameraAWBTypeSetCfg_dissector,
	["00c01011"] = CameraDayNightGetCfg_dissector,
	["00c01012"] = CameraDayNightSetCfg_dissector,
	["00c01013"] = CameraBackLightGetCfg_dissector,
	["00c01014"] = CameraBackLightSetCfg_dissector,
	["00c01015"] = CameraDRCGetCfg_dissector,
	["00c01016"] = CameraDRCSetCfg_dissector,
	["00c01017"] = CameraMirrorGetCfg_dissector,
	["00c01018"] = CameraMirrorSetCfg_dissector,
	["0f000001"] = FileOpen_dissector,
	["0f000002"] = FileClose_dissector,
	["0f000003"] = FileRead_dissector,
	["0f000004"] = FileWrite_dissector,
	["0f000005"] = FileSeek_dissector,
	["0f000010"] = FileErase_dissector,
	["0f000020"] = FileList_dissector,
	["06000000"] = StreamState_dissector,
	["06000001"] = StreamOpen_dissector,
	["06000002"] = StreamStart_dissector,
	["06000003"] = StreamStop_dissector,
	["06000004"] = StreamClose_dissector,
	["06000005"] = StreamSet_dissector,
	["06000006"] = StreamGet_dissector,
	["06000007"] = StreamList_dissector,
	["06000008"] = StreamPurge_dissector,
	["07000000"] = SpeechState_dissector,
	["07000001"] = SpeechOpen_dissector,
	["07000002"] = SpeechStart_dissector,
	["07000003"] = SpeechStop_dissector,
	["07000004"] = SpeechClose_dissector,
	["07000005"] = SpeechSet_dissector,
	["07000006"] = SpeechGet_dissector,
	["07000007"] = SpeechList_dissector,
	["07000008"] = SpeechPurge_dissector,
	["08000000"] = DumpState_dissector,
	["08000001"] = DumpOpen_dissector,
	["08000002"] = DumpStart_dissector,
	["08000003"] = DumpStop_dissector,
	["08000004"] = DumpClose_dissector,
	["08000005"] = DumpSet_dissector,
	["08000006"] = DumpGet_dissector,
	["08000007"] = DumpList_dissector,
	["08000008"] = DumpPurge_dissector,
	["08001001"] = DumpImage_dissector,
	["09000000"] = NetPlayState_dissector,
	["09000001"] = NetPlayOpen_dissector,
	["09000002"] = NetPlayStart_dissector,
	["09000003"] = NetPlayStop_dissector,
	["09000004"] = NetPlayClose_dissector,
	["09000005"] = NetPlaySet_dissector,
	["09000006"] = NetPlayGet_dissector,
	["09000007"] = NetPlayList_dissector,
	["09000008"] = NetPlayPurge_dissector,
	["09000009"] = NetPlaySeek_dissector,
	["01000000"] = TunnelState_dissector,
	["01000001"] = TunnelOpen_dissector,
	["01000002"] = TunnelStart_dissector,
	["01000003"] = TunnelStop_dissector,
	["01000004"] = TunnelClose_dissector,
	["01000005"] = TunnelSet_dissector,
	["01000006"] = TunnelGet_dissector,
	["01000007"] = TunnelList_dissector,
	["01000008"] = TunnelPurge_dissector,
	["01000009"] = TunnelServiceGet_dissector,
	["0100000a"] = TunnelServiceSet_dissector,
	["0100000b"] = TunnelServiceList_dissector,
	["00d01001"] = ITSGetLaneParam_dissector,
	["00d01002"] = ITSSetLaneInfo_dissector,
	["00d01003"] = ITSGetEventParam_dissector,
	["00d01004"] = ITSSetEventParam_dissector,
	["00d01101"] = ITSGetFlashLightParam_dissector,
	["00d01102"] = ITSSetFlashLightParam_dissector,
	["00d01201"] = ITSGetTrafLightGroup_dissector,
	["00d01202"] = ITSSetTrafLightGroup_dissector,
	["00d01203"] = ITSGetTrafLightSim_dissector,
	["00d01204"] = ITSSetTrafLightSim_dissector,
	["00d01211"] = ITSGetRedLightRegion_dissector,
	["00d01212"] = ITSSetRedLightRegion_dissector,
	["00d01213"] = ITSGetRedLightRegionEx_dissector,
	["00d01214"] = ITSSetRedLightRegionEx_dissector,
	["00d01221"] = ITSGetRadarParam_dissector,
	["00d01222"] = ITSSetRadarParam_dissector,
	["00d01223"] = ITSGetCoilParam_dissector,
	["00d01224"] = ITSSetCoilParam_dissector,
	["00d01301"] = ITSGetCaptureParam_dissector,
	["00d01302"] = ITSSetCaptureParam_dissector,
	["00d01311"] = ITSGetOSDParam_dissector,
	["00d01312"] = ITSSetOSDParam_dissector,
	["00d01313"] = ITSCaptureAnalize_dissector,
	["00d02001"] = ITSGetWorkMode_dissector,
	["00d02002"] = ITSSetWorkMode_dissector,
	["00d02003"] = ITSGetTriggerMode_dissector,
	["00d02004"] = ITSSetTriggerMode_dissector,
	["00d02005"] = ITSGetAlgorithmParam_dissector,
	["00d02006"] = ITSSetAlgorithmParam_dissector,
	["00d02007"] = ITSGetCheckPointParam_dissector,
	["00d02008"] = ITSSetCheckPointParam_dissector,
	["00d02009"] = ITSGetPoliceParam_dissector,
	["00d0200a"] = ITSSetPoliceParam_dissector,
	["00d0200b"] = ITSGetStatUploadParam_dissector,
	["00d0200c"] = ITSSetStatUploadParam_dissector,
	["00d0200d"] = ITSClearStatData_dissector,
	["00d0200e"] = ITSQueryAlgStat_dissector,}



local cmd = {
	["00000000"] = "SystemHello",
	["00000001"] = "SystemState",
	["00000002"] = "SystemVersion",
	["00000003"] = "SystemDescribe",
	["00000005"] = "SystemGetModules",
	["00000007"] = "SystemGetIPCDVSStatus",
	["00000011"] = "SystemGetIdentity",
	["00000012"] = "SystemSetIdentity",
	["00000013"] = "SystemGetTime",
	["00000014"] = "SystemSetTime",
	["00000015"] = "SystemGetTimeStyle",
	["00000016"] = "SystemSetTimeStyle",
	["00000017"] = "SystemGetStatus",
	["00000019"] = "SystemGetSDCodeCapbility",
	["0000001B"] = "SystemGetHDCodeCapbility",
	["00000081"] = "SystemPackageInstall",
	["00000082"] = "SystemPackageRemove",
	["00000083"] = "SystemPackageList",
	["00000091"] = "SystemShell",
	["00000092"] = "SystemTop",
	["00000093"] = "SystemReboot",
	["00000094"] = "SystemHalt",
	["00000095"] = "SystemExport",
	["00000096"] = "SystemImport",
	["00000097"] = "SystemRestore",
	["00000098"] = "SystemUpgrade",
	["00000099"] = "SystemBurnState",
	["0000009b"] = "SystemUpgradeCheck",
	["0000aa01"] = "SystemLogOpen",
	["0000aa02"] = "SystemLogClose",
	["0000aa03"] = "SystemLogFetch",
	["0000aa04"] = "SystemLogExport",
	["0000aa05"] = "SystemLogPurge",
	["00010000"] = "NetLinkState",
	["00010001"] = "NetLinkGetCfg",
	["00010002"] = "NetLinkSetCfg",
	["00010003"] = "NetLinkStartUp",
	["00010004"] = "NetLinkShutDown",
	["000100ff"] = "NetLinkTest",
	["00010101"] = "NetServiceGetAddrs",
	["00010102"] = "NetServiceSetAddrs",
	["00010103"] = "NetServiceGetAlerts",
	["00010104"] = "NetServiceSetAlerts",
	["00010105"] = "NetServiceGetSmtp",
	["00010106"] = "NetServiceSetSmtp",
	["00010107"] = "NetServiceGetSnmp",
	["00010108"] = "NetServiceSetSnmp",
	["00010109"] = "NetServiceGetCenters",
	["0001010a"] = "NetServiceSetCenters",
	["00010121"] = "NetServiceGetRtspCfg",
	["00010122"] = "NetServiceSetRtspCfg",
	["00010123"] = "NetServiceGetFtpCfg",
	["00010124"] = "NetServiceSetFtpCfg",
	["00010125"] = "NetServiceGetOnvifCfg",
	["00010126"] = "NetServiceSetOnvifCfg",
	["00010127"] = "NetClientGetFtpCfg",
	["00010128"] = "NetClientSetFtpCfg",
	["00010129"] = "NetServiceGetSipCfg",
	["00010130"] = "NetServiceSetSipCfg",
	["000101ff"] = "NetServiceTest",
	["0001aa01"] = "NetReportGetCfg",
	["0001aa02"] = "NetReportSetCfg",
	["0001dd00"] = "NetDiscoveryHello",
	["0001dd01"] = "NetDiscoveryState",
	["0001dd02"] = "NetDiscoverySetParam",
	["0001ee00"] = "NetRegistryState",
	["0001ee01"] = "NetRegistryGetCfg",
	["0001ee02"] = "NetRegistrySetCfg",
	["0001ee03"] = "NetRegistryLogin",
	["0001ee04"] = "NetRegistryLogoff",
	["00020001"] = "SecuritySessionLogin",
	["00020002"] = "SecuritySessionLogout",
	["00020003"] = "SecuritySessionList",
	["00020005"] = "SecuritySessionGet",
	["00020006"] = "SecuritySessionSet",
	["00020101"] = "SecurityUserAdd",
	["00020102"] = "SecurityUserEdit",
	["00020103"] = "SecurityUserDel",
	["00020104"] = "SecurityUserList",
	["00020105"] = "SecurityUserPasswd",
	["00020107"] = "SecurityUserGetPrivilege",
	["00020108"] = "SecurityUserSetPrivilege",
	["00020201"] = "SecurityRoleAdd",
	["00020202"] = "SecurityRoleEdit",
	["00020203"] = "SecurityRoleDel",
	["00020204"] = "SecurityRoleList",
	["00020205"] = "SecurityRoleGetPrivilege",
	["00020206"] = "SecurityRoleSetPrivilege",
	["00020207"] = "SecurityRoleGetPrivilegeDesp",
	["00040001"] = "StorageGetCfg",
	["00040002"] = "StorageSetCfg",
	["00040101"] = "StorageDiskList",
	["00040102"] = "StorageDiskDescribe",
	["00040103"] = "StorageDiskState",
	["00040104"] = "StorageDiskWaken",
	["00040105"] = "StorageDiskUse",
	["00040107"] = "StorageDiskGetUsages",
	["00040108"] = "StorageDiskSetUsages",
	["00040109"] = "StorageDiskInfo",
	["0004010b"] = "StorageDiskGetFormatStates",
	["0004010f"] = "StorageDiskFormat",
	["00040110"] = "StorageDiskMount",
	["00040121"] = "StorageDiskGetAlbums",
	["00040122"] = "StorageDiskSetAlbums",
	["00040123"] = "StorageDiskGetSchemes",
	["00040124"] = "StorageDiskSetSchemes",
	["00040201"] = "StorageDiskGetNfs",
	["00040202"] = "StorageDiskSetNfs",
	["00080001"] = "UartPortGetCfg",
	["00080002"] = "UartPortSetCfg",
	["00080003"] = "UartCipherList",
	["00080004"] = "UartCipherInstall",
	["00080005"] = "UartSnoopGetCfg",
	["00080006"] = "UartSnoopSetCfg",
	["00080007"] = "UartAgentGetCfg",
	["00080008"] = "UartAgentSetCfg",
	["00080009"] = "UartFpgaGetCfg",
	["00080010"] = "UartFpgaSetCfg",
	["00aa0000"] = "AlertAlarmState",
	["00aa0001"] = "AlertAlarmArm",
	["00aa0002"] = "AlertAlarmDisarm",
	["00aa0003"] = "AlertAlarmBypass",
	["00aa0004"] = "AlertAlarmReset",
	["00aa0005"] = "AlertAlarmPasswd",
	["00aa0007"] = "AlertAlarmGetcfg",
	["00aa0008"] = "AlertAlarmSetcfg",
	["00aa0009"] = "AlertAlarmDefenceGetcfg",
	["00aa000a"] = "AlertAlarmDefenceSetcfg",
	["00aa0100"] = "AlertAlarmInputState",
	["00aa0101"] = "AlertAlarmInputGetcfg",
	["00aa0102"] = "AlertAlarmInputSetcfg",
	["00aa0200"] = "AlertAlarmOutputState",
	["00aa0201"] = "AlertAlarmOutputGetcfg",
	["00aa0202"] = "AlertAlarmOutputSetcfg",
	["00aa0203"] = "AlertAlarmOutputStart",
	["00aa0204"] = "AlertAlarmOutputSop",
	["00aa0301"] = "AlertActionGetcfg",
	["00aa0302"] = "AlertActionSetcfg",
	["00aa0303"] = "AlertActionAck",
	["00aa0304"] = "AlertActionRaise",
	["00aa0305"] = "EventActionGetcfg",
	["00aa0306"] = "EventActionSetcfg",
	["00aa0308"] = "EventActionRaiseAlertIn",
	["00aa030a"] = "EventActionRaiseAlertOut",
	["00aa0351"] = "EventCameraCapture",
	["00aa0352"] = "EventCameraCaptureLocal",
	["00aa9000"] = "EventSubScribe",
	["00aa9001"] = "EventSubScribeStart",
	["00aa9002"] = "EventSubScribeEnd",
	["00030000"] = "AVDescribe",
	["00030001"] = "AVGetCfg",
	["00030001"] = "AVSetCfg",
	["00030101"] = "AVInputGetCfg",
	["00030102"] = "AVInputSetCfg",
	["00030901"] = "AVInputGetCfgv2",
	["00030902"] = "AVInputSetCfgv2",
	["00030103"] = "AVInputGetPictureCfg",
	["00030104"] = "AVInputSetPictureCfg",
	["00030105"] = "AVInputGetImprintCfg",
	["00030106"] = "AVInputSetImprintCfg",
	["00030115"] = "AVInputGetImprintText",
	["00030116"] = "AVInputSetImprintText",
	["00030107"] = "AVInputGetMaskCfg",
	["00030108"] = "AVInputSetMaskCfg",
	["00030109"] = "AVInputGetImprintFontCfg",
	["0003010a"] = "AVInputSetImprintFontCfg",
	["00030180"] = "AVInputGetViState",
	["00030181"] = "AVInputGetViType",
	["00030182"] = "AVInputSetViType",
	["00030183"] = "AVInputGetViResolution",
	["00030184"] = "AVInputSetViResolution",
	["00030201"] = "AVOutputGetMaskCfg",
	["00030202"] = "AVOutputSetMaskCfg",
	["00030203"] = "AVOutputGetImprintCfg",
	["00030204"] = "AVOutputSetImprintCfg",
	["00030301"] = "AVEncoderGetCfg",
	["00030302"] = "AVEncoderSetCfg",
	["00030303"] = "AVEncoderGetProfile",
	["00030304"] = "AVEncoderSetProfile",
	["00030305"] = "AVEncoderGetCurrentProfile",
	["00030306"] = "AVEncoderSetCurrentProfile",
	["00030309"] = "AVEncoderGetROICfg",
	["0003030a"] = "AVEncoderSetROICfg",
	["00030501"] = "AVDetectGetLossCfg",
	["00030502"] = "AVDetectSetLossCfg",
	["00030503"] = "AVDetectGetMotionCfg",
	["00030504"] = "AVDetectSetMotionCfg",
	["00030505"] = "AVDetectGetBlockCfg",
	["00030506"] = "AVDetectSetBlockCfg",
	["00030507"] = "AVLossGetTime",
	["00030508"] = "AVLossSetTime",
	["00030701"] = "AVDigitalChannelSearch",
	["00030702"] = "AVDigitalChannelAdd",
	["00030703"] = "AVDigitalChannelFetchSearchInfo",
	["00030704"] = "AVDigitalChannelModifyProp",
	["00030705"] = "AVDigitalChannelGetProp",
	["00030706"] = "AVDigitalChannelDel",
	["00030707"] = "AVDigitalChannelGetState",
	["00030708"] = "AVDigitalChannelSync",
	["0003070b"] = "AVDigitalChannelGetDevList",
	["0003070f"] = "AVDigitalChannelGetChannelList",
	["00030802"] = "AVTourChannelAdd",
	["00030804"] = "AVTourChannelModifyProp",
	["00030805"] = "AVTourChannelGetProp",
	["00030806"] = "AVTourChannelDel",
	["00030807"] = "AVTourChannelGetState",
	["00030809"] = "AVTourChannelGetInterval",
	["0003080a"] = "AVTourChannelSetInterval",
	["0003080b"] = "AVTourChannelGetDevList",
	["0003080f"] = "AVTourChannelGetChannelList",
	["00030880"] = "AVTourChannelGetConnectionState",
	["00030881"] = "AVTourChannelGetDecodingChannelList",
	["00031000"] = "AVRecordState",
	["00031001"] = "AVRecordGetProfile",
	["00031002"] = "AVRecordSetProfile",
	["00031003"] = "AVRecordGetCfg",
	["00031004"] = "AVRecordSetCfg",
	["00031015"] = "AVRecordGetCfgv2",
	["00031016"] = "AVRecordSetCfgv2",
	["00031005"] = "AVRecordGetSchdule",
	["00031006"] = "AVRecordSetSchdule",
	["00031011"] = "AVRecordStart",
	["00031012"] = "AVRecordStop",
	["00032001"] = "AVCaptureGetCfg",
	["00032002"] = "AVCaptureSetCfg",
	["00032003"] = "AVCaptureGetSchdule",
	["00032004"] = "AVCaptureSetSchdule",
	["00031101"] = "AVDemoGetCfg",
	["00031102"] = "AVDemoSetCfg",
	["00031103"] = "AVDemoControl",
	["00031105"] = "AVDemoGetPresets",
	["00031106"] = "AVDemoSetPresets",
	["00031107"] = "AVDemoGetPatrol",
	["00031108"] = "AVDemoSetPatrol",
	["00031111"] = "AVDemoGetCfgEx",
	["00031112"] = "AVDemoSetCfgEx",
	["000a0001"] = "ArchiveEventQueryOpen",
	["000a0002"] = "ArchiveEventQueryClose",
	["000a0003"] = "ArchiveEventQueryFetch",
	["000a0004"] = "ArchiveEventQuerySort",
	["000a0005"] = "ArchiveATMEventQueryOpen",
	["000a0011"] = "ArchiveSDEventQueryOpen",
	["000a0012"] = "ArchiveSDEventQueryClose",
	["000a0013"] = "ArchiveSDEventQueryFetch",
	["000a0021"] = "ArchiveImageQueryOpen",
	["000a0022"] = "ArchiveImageQueryClose",
	["000a0023"] = "ArchiveImageQueryFetch",
	["000a0102"] = "ArchiveEventPlot",
	["000a0103"] = "ArchiveEventCalendar",
	["000a0104"] = "ArchiveEventDescribe",
	["000a0105"] = "ArchiveEventXlate",
	["000a0106"] = "ArchiveATMEventPlot",
	["000a0200"] = "ArchiveBackupState",
	["000a0201"] = "ArchiveBackupStart",
	["000a0202"] = "ArchiveBackupStop",
	["000a0203"] = "ArchiveBackupGetSchdule",
	["000a0204"] = "ArchiveBackupSetSchdule",
	["000d0001"] = "SceneMonitorGetCfg",
	["000d0002"] = "SceneMonitorSetCfg",
	["000d0003"] = "SceneMonitorGetPicture",
	["000d0004"] = "SceneMonitorSetPicture",
	["000d0005"] = "SceneMonitorGetMargin",
	["000d0006"] = "SceneMonitorSetMargin",
	["000d0007"] = "SceneMonitorGetLayout",
	["000d0008"] = "SceneMonitorSetLayout",
	["000d0009"] = "SceneMonitorGetStatus",
	["000d000b"] = "SceneMonitorGetLayoutStatus",
	["000d0101"] = "ScenePaneList",
	["000d0102"] = "ScenePaneStart",
	["000d0103"] = "ScenePaneStop",
	["000d0104"] = "ScenePaneShift",
	["000d0105"] = "ScenePaneSwap",
	["000d0106"] = "ScenePaneSend",
	["000d0121"] = "ScenePaneZoom",
	["000d0122"] = "ScenePaneMute",
	["000d0201"] = "ScenePreviewGetCfg",
	["000d0202"] = "ScenePreviewSetCfg",
	["000d0203"] = "ScenePreviewRotate",
	["000d0211"] = "ScenePreviewGetTour",
	["000d0212"] = "ScenePreviewSetTour",
	["000d0213"] = "ScenePreviewStartTour",
	["000d0214"] = "ScenePreviewStopTour",
	["000d0215"] = "SceneMonitorGetDecodeChnBindState",
	["000d0300"] = "ScenePlaybackState",
	["000d0301"] = "ScenePlaybackOpen",
	["000d0302"] = "ScenePlaybackStart",
	["000d0303"] = "ScenePlaybackStop",
	["000d0304"] = "ScenePlaybackClose",
	["000d0305"] = "ScenePlaybackGet",
	["000d0306"] = "ScenePlaybackSet",
	["000d0307"] = "ScenePlaybackList",
	["000d0309"] = "ScenePlaybackSeek",
	["000d030a"] = "ScenePlaybackPip",
	["000d0801"] = "SceneSoundGetCfg",
	["000d0802"] = "SceneSoundSetCfg",
	["000d0803"] = "SceneSoundGetVolume",
	["000d0804"] = "SceneSoundSetVolume",
	["000d0a02"] = "SceneHidPresent",
	["000d0a03"] = "SceneHidGetCfg",
	["000d0a04"] = "SceneHidSetCfg",
	["000d0a05"] = "SceneHidGetTimeBar",
	["000d0a06"] = "SceneHidGetTimeBar",
	["000d0aff"] = "SceneHidSend",
	["00c00001"] = "CameraGetCfg",
	["00c00002"] = "CameraSetCfg",
	["00c00003"] = "CameraImageProcessGetCfg",
	["00c00004"] = "CameraImageProcessSetCfg",
	["00c00005"] = "CameraDayNightGetCfg",
	["00c00006"] = "CameraDayNightSetCfg",
	["00c00007"] = "CameraAntiFlickerGetCfg",
	["00c00008"] = "CameraAntiFlickerSetCfg",
	["00c00009"] = "CameraExtendGetCfg",
	["00c0000a"] = "CameraExtendSetCfg",
	["00c01001"] = "CameraLumaValGetCfg",
	["00c01002"] = "CameraLumaValSetCfg",
	["00c01003"] = "CameraContrValGetCfg",
	["00c01004"] = "CameraContrValSetCfg",
	["00c01005"] = "CameraSatuValGetCfg",
	["00c01006"] = "CameraSatuValSetCfg",
	["00c01007"] = "CameraSpenValGetCfg",
	["00c01008"] = "CameraSpenValSetCfg",
	["00c01009"] = "CameraAntiFlickerGetCfg",
	["00c0100a"] = "CameraAntiFlickerSetCfg",
	["00c0100b"] = "CameraExpoModeGetCfg",
	["00c0100c"] = "CameraExpoModeSetCfg",
	["00c0100d"] = "CameraIrisTypeGetCfg",
	["00c0100e"] = "CameraIrisTypeSetCfg",
	["00c0100f"] = "CameraAWBTypeGetCfg",
	["00c01010"] = "CameraAWBTypeSetCfg",
	["00c01011"] = "CameraDayNightGetCfg",
	["00c01012"] = "CameraDayNightSetCfg",
	["00c01013"] = "CameraBackLightGetCfg",
	["00c01014"] = "CameraBackLightSetCfg",
	["00c01015"] = "CameraDRCGetCfg",
	["00c01016"] = "CameraDRCSetCfg",
	["00c01017"] = "CameraMirrorGetCfg",
	["00c01018"] = "CameraMirrorSetCfg",
	["0f000001"] = "FileOpen",
	["0f000002"] = "FileClose",
	["0f000003"] = "FileRead",
	["0f000004"] = "FileWrite",
	["0f000005"] = "FileSeek",
	["0f000010"] = "FileErase",
	["0f000020"] = "FileList",
	["06000000"] = "StreamState",
	["06000001"] = "StreamOpen",
	["06000002"] = "StreamStart",
	["06000003"] = "StreamStop",
	["06000004"] = "StreamClose",
	["06000005"] = "StreamSet",
	["06000006"] = "StreamGet",
	["06000007"] = "StreamList",
	["06000008"] = "StreamPurge",
	["07000000"] = "SpeechState",
	["07000001"] = "SpeechOpen",
	["07000002"] = "SpeechStart",
	["07000003"] = "SpeechStop",
	["07000004"] = "SpeechClose",
	["07000005"] = "SpeechSet",
	["07000006"] = "SpeechGet",
	["07000007"] = "SpeechList",
	["07000008"] = "SpeechPurge",
	["08000000"] = "DumpState",
	["08000001"] = "DumpOpen",
	["08000002"] = "DumpStart",
	["08000003"] = "DumpStop",
	["08000004"] = "DumpClose",
	["08000005"] = "DumpSet",
	["08000006"] = "DumpGet",
	["08000007"] = "DumpList",
	["08000008"] = "DumpPurge",
	["08001001"] = "DumpImage",
	["09000000"] = "NetPlayState",
	["09000001"] = "NetPlayOpen",
	["09000002"] = "NetPlayStart",
	["09000003"] = "NetPlayStop",
	["09000004"] = "NetPlayClose",
	["09000005"] = "NetPlaySet",
	["09000006"] = "NetPlayGet",
	["09000007"] = "NetPlayList",
	["09000008"] = "NetPlayPurge",
	["09000009"] = "NetPlaySeek",
	["01000000"] = "TunnelState",
	["01000001"] = "TunnelOpen",
	["01000002"] = "TunnelStart",
	["01000003"] = "TunnelStop",
	["01000004"] = "TunnelClose",
	["01000005"] = "TunnelSet",
	["01000006"] = "TunnelGet",
	["01000007"] = "TunnelList",
	["01000008"] = "TunnelPurge",
	["01000009"] = "TunnelServiceGet",
	["0100000a"] = "TunnelServiceSet",
	["0100000b"] = "TunnelServiceList",
	["00d01001"] = "ITSGetLaneParam",
	["00d01002"] = "ITSSetLaneInfo",
	["00d01003"] = "ITSGetEventParam",
	["00d01004"] = "ITSSetEventParam",
	["00d01101"] = "ITSGetFlashLightParam",
	["00d01102"] = "ITSSetFlashLightParam",
	["00d01201"] = "ITSGetTrafLightGroup",
	["00d01202"] = "ITSSetTrafLightGroup",
	["00d01203"] = "ITSGetTrafLightSim",
	["00d01204"] = "ITSSetTrafLightSim",
	["00d01211"] = "ITSGetRedLightRegion",
	["00d01212"] = "ITSSetRedLightRegion",
	["00d01213"] = "ITSGetRedLightRegionEx",
	["00d01214"] = "ITSSetRedLightRegionEx",
	["00d01221"] = "ITSGetRadarParam",
	["00d01222"] = "ITSSetRadarParam",
	["00d01223"] = "ITSGetCoilParam",
	["00d01224"] = "ITSSetCoilParam",
	["00d01301"] = "ITSGetCaptureParam",
	["00d01302"] = "ITSSetCaptureParam",
	["00d01311"] = "ITSGetOSDParam",
	["00d01312"] = "ITSSetOSDParam",
	["00d01313"] = "ITSCaptureAnalize",
	["00d02001"] = "ITSGetWorkMode",
	["00d02002"] = "ITSSetWorkMode",
	["00d02003"] = "ITSGetTriggerMode",
	["00d02004"] = "ITSSetTriggerMode",
	["00d02005"] = "ITSGetAlgorithmParam",
	["00d02006"] = "ITSSetAlgorithmParam",
	["00d02007"] = "ITSGetCheckPointParam",
	["00d02008"] = "ITSSetCheckPointParam",
	["00d02009"] = "ITSGetPoliceParam",
	["00d0200a"] = "ITSSetPoliceParam",
	["00d0200b"] = "ITSGetStatUploadParam",
	["00d0200c"] = "ITSSetStatUploadParam",
	["00d0200d"] = "ITSClearStatData",
	["00d0200e"] = "ITSQueryAlgStat",}


function OBCPhead_dissector(buffer,pinfo,tree)
	local tab = {
		{2,"Mark:",strings},
		{1,"Version:",tostring},
		{1,"Crypt:",tostring},
		{4,"Length:",le_uints},
		{2,"Mode:",le_buffers},
		{2,"Error:",le_buffers},
		{4,"Product:",le_buffers},
		{4,"Sequence:",le_buffers},
		{4,"Command:",le_buffers},
		{40,"Res:",tostring},}
	 treeadd_tab(tree,buffer(0,64),tab)
end


function OBCP.dissector(buffer,pinfo,tree)

	local buffer_len = buffer:len()
	local length = buffer(4,4):le_int() + 8
	local Command = le_buffers(buffer(20,4))


	if length > buffer:len() then
		pinfo.desegment_len = DESEGMENT_ONE_MORE_SEGMENT
		pinfo.desegment_offset = 0
	end
	pinfo.cols.protocol = ("OBCP")
	pinfo.cols.info:set(cmd[Command])	

	
	local OBCP_tree = tree:add(OBCP,buffer(0,length),"OBCP")
		local msg_head_tree = OBCP_tree:add(OBCP,buffer(0,24+40),"Message Head")
		OBCPhead_dissector(buffer(0,64), pinfo, msg_head_tree)
	
		if  length > 64 then
			local msg_data_tree = OBCP_tree:add(OBCP,buffer(64,length-64),cmd[Command])
			dissector[Command](buffer(64,length-64), pinfo, msg_data_tree)
		end

	--pinfo.desegment_len = 0
    --pinfo.desegment_offset = length
end





local udp_port_table = DissectorTable.get("tcp.port")
local my_port = 3721
udp_port_table:add(my_port, OBCP)
end