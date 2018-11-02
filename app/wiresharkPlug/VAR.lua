

do
  protocol = {
    [128] = "Control",
    [129] = "Transmission",
    [130] = "Matrix",
    [131] = "Other",
    [132] = "Other",
  }
	
  message = {
    [1] = "Req",
    [2] = "Set",
    [3] = "Send",
    [4] = "Ack",
    [7] = "Other",}
	
	
Var = Proto ("Var","Var","My Self-defined Protocol")

  set = {
    [0] = "Date",
    [1] = "Reset",
    [2] = "Char CLear",
    [3] = "Screen Clear",}
	
  display = {
    [0] = "Don't Display",
    [1] = "Display",}
	
  datetype = {
    [0] = "YYYY-MM-DD",
    [1] = "YYYY/MM/DD",
    [2] = "YY-MM-DD",
    [3] = "YY/MM/DD",
    [4] = "MM-DD",
    [5] = "MM/DD",
    [6] = "MMDD",} 
	
  second = {
    [0] = "hh:mm",
    [1] = "hh:mm:ss",
    [2] = "hhmm",
    [3] = "/hhmm",}
	
  updatetype = {
    [1] = "uImage",
    [2] = "Ramdisk",
    [3] = "jffs2.img",
    [4] = "u-boot",}
	
  Operationtype = {
    [0] = "Stop",
    [1] = "Start",
    [2] = "Pause",}
	
  devicetype = {
      [0] = "CPU",
	   [1] = "Encode",
	   [2] = "Decode",}
  
  pi = {
    [1] = "800x600",
    [2] = "1024x768",
    [3] = "1280x1024",
    [4] = "1280x720",
    [5] = "1366x768",
    [6] = "1440x900",
    [7] = "1280x1024",
    [8] = "1600x1200",
    [9] = "1920x1080",
    [10] = "1920x1200",}
	
   ref = {
    [1] = "60p",
    [2] = "50p",
    [3] = "30p",
    [4] = "25p",
    [5] = "75p",
    [6] = "85p",
    [7] = "100p",
    [11] = "60i",
    [12] = "50i",}
	
  pro = {
    [0] = "Pelco-D",
    [1] = "Pelco-P",}
	
   bps = {
    [0] = "1200",
    [1] = "2400",
    [2] = "4800",
    [3] = "9600",}




function REQ_SET_HEARTJUMP_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[REQ_SET_HEARTJUMP]")
  tree:add(buffer(0,buffer:len()),"[REQ_SET_HEARTJUMP]")
end


function RET_SET_HEARTJUMP_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[RET_SET_HEARTJUMP]")
  tree:add(buffer(0,buffer:len()),"[RET_SET_HEARTJUMP]")
end

	
function Snd_Matrix_PowerOn_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Snd_Matrix_PowerOn]")
  return true
end



function Snd_Matrix_CpuLog_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Snd_Matrix_CpuLog]" .. " Log: " .. tostring(buffer(0,buffer:len())))
  tree:add(buffer(0,buffer:len()),"Log: " .. tostring(buffer(0,buffer:len())))
end


function Req_Set_MatrixIP_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Set_MatrixIP]" .. "  Device: " .. devicetype[buffer(0,1)] .. " IP Address: " .. buffer(1,1) .. "." ..buffer(2,1) .. "." .. buffer(3,1) .. "." ..buffer(4,1))
  tree:add(buffer(0,1), "Device: " .. devicetype[buffer(0,1)])
  tree:add(buffer(1,4), "IP Address: " .. buffer(1,1) .. "." ..buffer(2,1) .. "." .. buffer(3,1) .. "." ..buffer(4,1))
  tree:add(buffer(5,4), "Subnet Mask: " .. buffer(5,1) .. "." ..buffer(6,1) .. "." .. buffer(7,1) .. "." ..buffer(8,1))
  tree:add(buffer(9,4), "Getway: " .. buffer(9,1) .. "." ..buffer(10,1) .. "." .. buffer(11,1) .. "." ..buffer(12,1))
  tree:add(buffer(13,2), "Port: " .. buffer(13,2))
  tree:add(buffer(15,4), "Index: " .. tostring(buffer(15,4)))
end


function Ret_Set_MatrixIP_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
  pinfo.cols.info = ("[Ret_Set_MatrixIP]" .. "  Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
  pinfo.cols.info = ("[Ret_Set_MatrixIP]" .. "  Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Get_EquInfo_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Get_EquInfo]" .. " EquInfo: " .. tostring(buffer(0,6)))
  tree:add(buffer(0,6), "EquInfo: " .. tostring(buffer(0,6)))
end


function Ret_Get_EquInfo_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  pinfo.cols.info = ("[Ret_Get_EquInfo]" .. " Configration Version: " .. tostring(buffer(0,6)) .. " Matrix: " .. tostring(buffer(7,4)))
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  pinfo.cols.info = ("[Ret_Get_EquInfo]" .. " Ack: Fail")
  end
  tree:add(buffer(1,6), "Configration Version: " .. tostring(buffer(0,6)))
  tree:add(buffer(7,4), "Matrix: " .. tostring(buffer(7,4)))
  local n = buffer(11,1):uint()
  local m = buffer(12+10*n,1):uint()
  local l = buffer(12+10*n+3*m,1):uint()
  for i = 0, (n-1) do
    local Sub_tree = tree:add(Var,buffer(i*10+12,10),"Equipment " .. (i+1) .. "Info: ")
      Sub_tree:add(buffer(i*10+12,2), "Protocol: " .. buffer(i*10+12,2))
      Sub_tree:add(buffer(i*10+14,8), "Protocol: " .. buffer(i*10+14,8))
  end
  for i = 0, (m-1) do
    local Sub_tree = tree:add(Var,buffer(12+n*10+1,3),"Equipment " .. (i+1) .. "Info: ")
      Sub_tree:add(buffer(12+n*10+1,1), "Protocol: " .. buffer(12+n*10+1,1))
      Sub_tree:add(buffer(12+n*10+2,2), "Protocol: " .. buffer(12+n*10+2,2))
  end
  for i = 0, (m-1) do
    local Sub_tree = tree:add(Var,buffer(12+n*10+1+3*m+1,8),"Equipment " .. (i+1) .. "Info: ")
      Sub_tree:add(buffer(12+n*10+1+3*m+1+i*8,4), "Card: " .. buffer(12+n*10+1+3*m+1+i*8,4))
      Sub_tree:add(buffer(12+n*10+1+3*m+1+i*8+4,1), "Box: " .. buffer(12+n*10+1+3*m+1+i*8+4,1))
      Sub_tree:add(buffer(12+n*10+1+3*m+1+i*8+5,1), "Solt ID: " .. buffer(12+n*10+1+3*m+1+i*8+5,1))
      Sub_tree:add(buffer(12+n*10+1+3*m+1+i*8+6,1), "Card Type ID: " .. buffer(12+n*10+1+3*m+1+i*8+6,1))
      Sub_tree:add(buffer(12+n*10+1+3*m+1+i*8+7,1), "Card Software Version: " .. buffer(12+n*10+1+3*m+1+i*8+7,1))
  end
end


function Req_Set_ChannelInfo_dissector(buffer,pinfo,tree)
  local n = buffer(3,2):uint()
  --local m = buffer(3+10*n,2):uint()
  pinfo.cols.info = ("[eq_Set_ChannelInfo]" .. "  Datagram Index: " .. tostring(buffer(0,2)))
  tree:add(buffer(0,2), "Datagram Index: " .. tostring(buffer(0,2)))
end


function Ret_Set_ChannelInfo_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
  pinfo.cols.info = ("[Ret_Set_ChannelInfo]" .. " Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
  pinfo.cols.info = ("[Ret_Set_ChannelInfo]" .. " Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end



function Req_Set_RouteInfo_dissector(buffer,pinfo,tree)
  local n = buffer(0,2):uint()
  local m = buffer(2+16*n,2):uint()
  pinfo.cols.info = ("[Req_Set_RouteInfo]" .. " Route Input" .. buffer(0,2):uint() .. " Route Output" .. buffer(2+16*n,2):uint())
  for i = 0, (n-1) do
    local Sub_tree = tree:add(Var,buffer(2+i*16,16),"Route Input" .. (i+1) .. " Info: ")
      Sub_tree:add(buffer(2+i*16,4), "Input Card: " .. tostring(buffer(2+16*i,4)))
      Sub_tree:add(buffer(2+i*16+4,1), "Input Port: " .. buffer(2+i*16+4,1))
      Sub_tree:add(buffer(2+i*16+5,1), "Input Channel: " .. buffer(2+i*16+5,1))
      Sub_tree:add(buffer(2+i*16+6,4), "Matrix ID: " .. tostring(buffer(2+i*16+6,4)))
      Sub_tree:add(buffer(2+i*16+10,4), "Output Card: " .. tostring(buffer(2+i*16+10,4)))
      Sub_tree:add(buffer(2+i*16+14,1), "Output Port: " .. buffer(2+i*16+14,1))
      Sub_tree:add(buffer(2+i*16+15,1), "Output Channel: " .. buffer(2+i*16+15,1))
  end
  for i = 0, (m-1) do
    local Sub_tree = tree:add(Var,buffer(2+n*16+2+16*i,16),"Route Output" .. (i+1) .. " Info: ")
      Sub_tree:add(buffer(2+n*16+2+16*i,4), "Output Card: " .. tostring(buffer(2+n*16+2+16*i,4)))
      Sub_tree:add(buffer(2+n*16+2+16*i+4,1), "Output Port: " .. buffer(2+n*16+2+16*i+4,1))
      Sub_tree:add(buffer(2+n*16+2+16*i+5,1), "Output Channel: " .. buffer(2+n*16+2+16*i+5,1))
      Sub_tree:add(buffer(2+n*16+2+16*i+6,4), "Matrix ID: " .. tostring(buffer(2+n*16+2+16*i+6,4)))
      Sub_tree:add(buffer(2+n*16+2+16*i+10,4), "Input Card: " .. tostring(buffer(2+n*16+2+16*i+10,4)))
      Sub_tree:add(buffer(2+n*16+2+16*i+14,1), "Input Port: " .. buffer(2+n*16+2+16*i+14,1))
      Sub_tree:add(buffer(2+n*16+2+16*i+15,1), "Input Channel: " .. buffer(2+n*16+2+16*i+15,1))
  end
end


function Ret_Set_RouteInfo_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
  pinfo.cols.info = ("[Ret_Set_RouteInfo]" .. " Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
  pinfo.cols.info = ("[Ret_Set_RouteInfo]" .. " Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Get_RouteInfo_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  pinfo.cols.info = ("[Req_Get_RouteInfo]" .. " Ack: Success")
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  pinfo.cols.info = ("[Req_Get_RouteInfo]" .. " Ack: Fail")
  end
end


function Ret_Get_RouteInfo_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  pinfo.cols.info = ("[Ret_Get_RouteInfo]" .. " Route Input Number: " .. buffer(1,2))
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  pinfo.cols.info = ("[Ret_Get_RouteInfo]" .. " Ack: Fail")
  end
  tree:add(buffer(1,2),"Route Input Number: " .. buffer(1,2):uint())
  local n = buffer(1,2):uint()
  local m = buffer(n*16+3,2):uint()
  for i = 0, (n-1) do
    local Sub_tree = tree:add(Var,buffer(i*16+3,16),"Input Channel " .. (i+1) .. "Info: ")
      Sub_tree:add(buffer(i*16+3,4), "Input Card: " .. buffer(i*16+3,4))
      Sub_tree:add(buffer(i*16+7,1), "Input Port ID: " .. buffer(i*16+7,1))
      Sub_tree:add(buffer(i*16+8,1), "Input Channel: " .. buffer(i*16+8,1))
      Sub_tree:add(buffer(i*16+9,4), "Matrix ID: "  .. buffer(i*16+9,4))
      Sub_tree:add(buffer(i*16+13,4), "Output Card: " .. buffer(i*16+13,4))
      Sub_tree:add(buffer(i*16+17,1), "Output Port ID: " .. buffer(i*16+17,1))
      Sub_tree:add(buffer(i*16+18,1), "Output Channel: " .. buffer(i*16+18,1))
  end
  for i = 0, (m-1) do
    local Sub_tree = tree:add(Var,buffer(n*16+i*16+3,16),"Output Channel " .. (i+1) .. "Info: ")
      Sub_tree:add(buffer(n*16+i*16+3,4), "Input Card: " .. buffer(n*16+i*16+3,4))
      Sub_tree:add(buffer(n*16+i*16+7,1), "Input Port ID: " .. buffer(n*16+i*16+7,1))
      Sub_tree:add(buffer(n*16+i*16+8,1), "Input Channel: " .. buffer(n*16+i*16+8,1))
      Sub_tree:add(buffer(n*16+i*16+9,4), "Matrix ID: "  .. buffer(n*16+i*16+9,4))
      Sub_tree:add(buffer(n*16+i*16+13,4), "Output Card: " .. buffer(n*16+i*16+13,4))
      Sub_tree:add(buffer(n*16+i*16+17,1), "Output Port ID: " .. buffer(n*16+i*16+17,1))
      Sub_tree:add(buffer(n*16+i*16+18,1), "Output Channel: " .. buffer(n*16+i*16+18,1))  
  end
end


function Req_Set_ReportMode_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
  pinfo.cols.info = ("[Req_Set_ReportMode]" .. "  Report Server IP: " .. buffer(1,1) .. "." ..buffer(2,1) .. "." .. buffer(3,1) .. "." ..buffer(4,1))
    tree:add(buffer(0,1), "Active Report (" .. tostring(buffer(0,1)) .. ")")
  else
    tree:add(buffer(0,1), "Passive Report (" .. tostring(buffer(0,1)) .. ")")
  end
  tree:add(buffer(1,4), "Report Server IP: " .. buffer(1,1) .. "." ..buffer(2,1) .. "." .. buffer(3,1) .. "." ..buffer(4,1))
  tree:add(buffer(5,2), "Report Poert: " .. buffer(5,2))
  tree:add(buffer(7,4), "Time Server IP: " .. buffer(7,1) .. "." ..buffer(8,1) .. "." .. buffer(9,1) .. "." ..buffer(10,1))
  tree:add(buffer(11,4), "Alarm Server IP: " .. buffer(11,1) .. "." ..buffer(12,1) .. "." .. buffer(13,1) .. "." ..buffer(14,1))
  tree:add(buffer(15,2), "Alarm Poert: " .. buffer(15,2))
end


function Ret_Set_ReportMode_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
  pinfo.cols.info = ("[Ret_Set_ReportMode]" .. "  Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
  pinfo.cols.info = ("[Ret_Set_ReportMode]" .. "  Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Get_WorkStatus_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Get_WorkStatus]" .. "  Channel Work Status: " .. buffer(0,buffer:len()))
  tree:add(buffer(0,buffer:len()),"Channel Work Status: " .. buffer(0,buffer:len())) 
end


function Ret_Get_WorkStatus_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  pinfo.cols.info = ("[Ret_Get_WorkStatus]" .. "  Matrix Version: " .. buffer(1,1))
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  pinfo.cols.info = ("[Ret_Get_WorkStatus]" .. "  Ack: Fail")
  end
  tree:add(buffer(1,3), "Matrix Version: " .. tostring(buffer(1,3)))
  ---???
end


function Req_Set_DeviceStatus_dissector(buffer,pinfo,tree)
  local type = {
    [0] = "Matrix",
    [1] = "Card",
    [2] = "Port",
    [3] = "Channel",}
   local state = {
    [0] = "Start",
    [1] = "Stop",
    [2] = "Restart",}
   pinfo.cols.info = ("[Req_Set_DeviceStatus]" .. " Device Type: " .. type[buffer(0,1)] .. "  Card: " .. buffer(1,4) .. " Port: " .. buffer(5,1) .. " Device State: " .. state[buffer(7,1)])
   tree:add(buffer(0,1), "Device Type: " .. type[buffer(0,1)])
   tree:add(buffer(1,4), "Card: " .. buffer(1,4))
   tree:add(buffer(5,1), "Port: " .. buffer(5,1))
   tree:add(buffer(6,1), "Channel: " .. buffer(6,1))
   tree:add(buffer(7,1), "Device State: " .. state[buffer(7,1)])
end


function Ret_Set_DeviceStatus_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
  pinfo.cols.info = ("[Ret_Set_DeviceStatus]" .. "  Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
  pinfo.cols.info = ("[Ret_Set_DeviceStatus]" .. "  Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Snd_Report_WorkStatus_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Snd_Report_WorkStatus]")
  ---???
end


function Req_Set_SwitchInfo_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Set_SwitchInfo]")
end


function Ret_Set_SwitchInfo_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
  pinfo.cols.info = ("[Ret_Set_SwitchInfo]" .. "  Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
  pinfo.cols.info = ("[Ret_Set_SwitchInfo]" .. "  Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end



function Req_Get_SwitchInfo_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Get_SwitchInfo]")
  tree:add(nil)
end


function Ret_Get_SwitchInfo_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    pinfo.cols.info = ("[Ret_Get_SwitchInfo]" .. "Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
    pinfo.cols.info = ("[Ret_Get_SwitchInfo]" .. "Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
  ---???
end



function Req_Set_MonitorInfo_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Set_MonitorInfo]")
  ---???
end


function Ret_Set_MonitorInfo_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
  pinfo.cols.info = ("[Ret_Set_MonitorInfo]" .. " Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
  pinfo.cols.info = ("[Ret_Set_MonitorInfo]" .. " Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Get_MonitorInfo_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Get_MonitorInfo]")
  tree:add(nil)
end


function Ret_Get_MonitorInfo_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Ret_Get_MonitorInfo]")
  ---???
end


function Req_Set_TextDotInfo_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Set_TextDotInfo]" .. " Box Number: " .. buffer(0,1) .. " Card: " .. buffer(1,3) .. " Remote Card: " .. tostring(buffer(5,4)))
  tree:add(buffer(0,1), "Box Number: " .. buffer(0,1))
  tree:add(buffer(1,4), "Card: " .. buffer(1,3))
  tree:add(buffer(5,4), "Remote Card: " .. tostring(buffer(5,4)))
  tree:add(buffer(9,1), "Solt: " .. buffer(9,1))
  tree:add(buffer(10,1), "Port: " .. buffer(10,1))
  tree:add(buffer(11,1), "Channel: " .. buffer(11,1))
  tree:add(buffer(12,1), "Char Numner: " .. buffer(12,1))
  tree:add(buffer(13,1), "Char Start Address: " .. buffer(13,1))
  ---???
end


function Ret_Set_TextDotInfo_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
  pinfo.cols.info = ("[Ret_Set_TextDotInfo]" .. " Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
  pinfo.cols.info = ("[Ret_Set_TextDotInfo]" .. " Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Active_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Active]" .. "  Type: " .. tostring((buffer(0,1))) .. " CpuID: " .. tostring(buffer(1,4)))
  tree:add(buffer(0,1), "Type: " .. tostring((buffer(0,1))))
  tree:add(buffer(1,4), "CpuID: " .. tostring(buffer(1,4)))
  tree:add(buffer(5,4), "Valid Time: " .. tostring(buffer(5,4)))
end


function Ret_Active_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
  pinfo.cols.info = ("[Ret_Active]" .. "  Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
    pinfo.cols.info = ("[Ret_Active]" .. "  Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Set_MaskInfo_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Set_MaskInfo]" .. "  Remote Card: " .. tostring(buffer(0,4)) .. "  Box: " .. tostring(buffer(4,1)) .. "  Card: " .. tostring(buffer(5,4)))
  tree:add(buffer(0,4), "Remote Card: " .. tostring(buffer(0,4)))
  tree:add(buffer(4,1), "Box: " .. tostring(buffer(4,1)))
  tree:add(buffer(5,4), "Card: " .. tostring(buffer(5,4)))
  tree:add(buffer(9,1), "Card Solt: " .. buffer(9,1))
  tree:add(buffer(10,1), "Port ID: " .. buffer(10,1))
  tree:add(buffer(11,1), "Channel: " .. buffer(11,1))
  tree:add(buffer(12,1), "Set: " .. set[buffer(12,1)] .. "(" .. tostring(buffer(12,1)) .. ")")
  tree:add(buffer(13,1), "Date: " .. display[buffer(13,1)] .. "(" .. tostring(buffer(13,1)) .. ")")
  tree:add(buffer(14,2), "Display_X: " .. buffer(14,2))
  tree:add(buffer(16,2), "Display_Y: " .. buffer(16,2))
  tree:add(buffer(18,1), "Date Type: " .. datetype[buffer(18,1)] .. "(" .. tostring(buffer(18,1)) .. ")")
  tree:add(buffer(19,1), "Time: " .. display[buffer(19,1)] .. "(" .. tostring(buffer(19,1)) .. ")")
  tree:add(buffer(20,2), "Display_X: " .. buffer(20,2))
  tree:add(buffer(22,2), "Display_Y: " .. buffer(22,2))
  tree:add(buffer(24,1), "Time: " .. second[buffer(24,1)] .. "(" .. tostring(buffer(24,1)) .. ")")
end


function Ret_Set_MaskInfo_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
  pinfo.cols.info = ("[Ret_Set_MaskInfo]" .. "  Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
  pinfo.cols.info = ("[Ret_Set_MaskInfo]" .. "  Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Set_TextMask_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Set_TextMask]" .. "  Remote Card: " .. tostring(buffer(0,4)) .. "  Box: " .. buffer(4,1) ..  " Card: " .. buffer(5,4) .. " Solt: " .. buffer(9,1))
  tree:add(buffer(0,4), "Remote Card: " .. tostring(buffer(0,4)))
  tree:add(buffer(4,1), "Box: " .. buffer(4,1))
  tree:add(buffer(5,4), "Card: " .. buffer(5,4))
  tree:add(buffer(9,1), "Solt: " .. buffer(9,1))
  tree:add(buffer(10,1), "Port: " .. buffer(10,1))
  tree:add(buffer(11,1), "Channel: " .. buffer(11,1))
  
end


function Ret_Set_TextMask_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
  pinfo.cols.info = ("[Ret_Set_TextMask]" .. "  Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
  pinfo.cols.info = ("[Ret_Set_TextMask]" .. "  Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Set_Shield_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Set_Shield]" .. "  Remote Card: " .. tostring(buffer(0,4) .. " Box: " .. buffer(4,1) .. "  Card: " .. buffer(5,4)) .. "  Solt: " .. buffer(9,1))
  tree:add(buffer(0,4), "Remote Card: " .. tostring(buffer(0,4)))
  tree:add(buffer(4,1), "Box: " .. buffer(4,1))
  tree:add(buffer(5,4), "Card: " .. buffer(5,4))
  tree:add(buffer(9,1), "Solt: " .. buffer(9,1))
  tree:add(buffer(10,1), "Port: " .. buffer(10,1))
  tree:add(buffer(11,1), "Channel: " .. buffer(11,1))
  if buffer(12,1):uint() == 0 then
    tree:add(buffer(12,1), "None (" .. tostring(buffer(12,1)) .. ")")
  else
    local n = buffer(12,1):uint()
      for i = 0, (n-1) do
      local Sub_tree = tree:add(Var,buffer(13+8*i,8),"Shield" .. (i+1) .. " Info: ")
        Sub_tree:add(buffer(13+8*i,2), "X1: " .. tostring(buffer(13+8*i,2)))
        Sub_tree:add(buffer(13+8*i+2,2), "Y1: " .. tostring(buffer(13+8*i+2,2)))
        Sub_tree:add(buffer(13+8*i+4,2), "X2: " .. tostring(buffer(13+8*i+4,2)))
        Sub_tree:add(buffer(13+8*i+6,2), "Y2: " .. tostring(buffer(13+8*i+6,2)))
      end
  end
end


function Ret_Set_Shield_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
  pinfo.cols.info = ("[Ret_Set_Shield]" .. "  Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
  pinfo.cols.info = ("[Ret_Set_Shield]" .. "  Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Set_ChannelRoute_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
  pinfo.cols.info = ("[Req_Set_ChannelRoute]" .. "  Ack: Clear")
    tree:add(buffer(0,1), "Ack: Clear (" .. tostring(buffer(0,1)) .. ")")
  else
  pinfo.cols.info = ("[Req_Set_ChannelRoute]" .. "  Ack: Set")
    tree:add(buffer(0,1), "Ack: Set (" .. tostring(buffer(0,1)) .. ")")
  end
  tree:add(buffer(1,1), "Input Box: " .. buffer(1,1))
  tree:add(buffer(2,4), "Input Card: " .. tostring(buffer(2,4)))
  tree:add(buffer(6,1), "Input Solt: " .. buffer(6,1))
  tree:add(buffer(7,1), "Input Port: " .. buffer(7,1))
  tree:add(buffer(8,1), "Input Channel: " .. buffer(8,1))
  tree:add(buffer(9,2), "Input Channel Card: " .. tostring(buffer(9,2)))
  tree:add(buffer(11,1), "Output Box: " .. buffer(11,1))
  tree:add(buffer(12,4), "Output Card: " .. tostring(buffer(12,4)))
  tree:add(buffer(16,1), "Output Solt: " .. buffer(16,1))
  tree:add(buffer(17,1), "Output Port: " .. buffer(17,1))
  tree:add(buffer(18,1), "Output Channel: " .. buffer(18,1))
  tree:add(buffer(19,2), "Output Channel Card: " .. tostring(buffer(19,2)))
end


function Ret_Set_ChannelRoute_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
  pinfo.cols.info = ("[Ret_Set_ChannelRoute]" .. "  Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
  pinfo.cols.info = ("[Ret_Set_ChannelRoute]" .. "  Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_PT_PanTilt_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_PT_PanTilt]" .. "  User: " .. buffer(1,2):uint() .." Scene: " .. tostring(buffer(3,3)) .. "  Monitot: " .. tostring(buffer(6,3)) .. "  Camera: " .. tostring(buffer(9,4)))
  tree:add(buffer(0,1), "Start Bit: " .. tostring(buffer(0,1)))
  tree:add(buffer(1,2), "User: " .. buffer(1,2):uint())
  tree:add(buffer(3,3), "Scene: " .. tostring(buffer(3,3)))
  tree:add(buffer(6,3), "Monitot: " .. tostring(buffer(6,3)))
  tree:add(buffer(9,4), "Camera: " .. tostring(buffer(9,4)))
  tree:add(buffer(13,3), "Command: " .. tostring(buffer(13,3)))
  tree:add(buffer(16,3), "Command1: " .. tostring(buffer(16,3)))
  tree:add(buffer(19,3), "Command2: " .. tostring(buffer(19,3)))
  tree:add(buffer(22,1), "End Bit: " .. tostring(buffer(22,1)))
end


function Ret_PT_PanTilt_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
  pinfo.cols.info = ("[Ret_PT_PanTilt]" .. "  Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
  pinfo.cols.info = ("[Ret_PT_PanTilt]" .. "  Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Cpu_Update_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Cpu_Update]" .. "  Update Type: " .. buffer(0,1) .. "  Update:" .. updatetype[buffer(1,1):uint()] .. " Tftp Server IP: " .. tostring(buffer(4,4)))
  tree:add(buffer(0,1), "Update Type: " .. buffer(0,1))
  tree:add(buffer(1,1), "Update:" .. updatetype[buffer(1,1):uint()])
  tree:add(buffer(2,2), "Version: " .. tostring(buffer(2,2)))
  tree:add(buffer(4,4), "Tftp Server IP: " .. tostring(buffer(4,4)))
  tree:add(buffer(8,64), "Die: " .. tostring(buffer(8,64)))
end


function Ret_Cpu_Update_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    pinfo.cols.info = ("[Ret_Cpu_Update]" .. "  Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
    pinfo.cols.info = ("[Ret_Cpu_Update]" .. "  Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Get_ChannelWorkStatus_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Get_ChannelWorkStatus]" .. " Channel Work Status: " .. tostring(buffer(0,3)))
  tree:add(buffer(0,3), "Channel WorkStatus: " .. tostring(buffer(0,3)))
end


function Ret_Get_ChannelWorkStatus_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    pinfo.cols.info = ("[Ret_Get_ChannelWorkStatus]" .. " Work Status Version: " .. tostring(buffer(1,3)) .. "  Channel Status: " .. buffer(4,2))
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
  pinfo.cols.info = ("[Ret_Get_ChannelWorkStatus]" .. " Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
  tree:add(buffer(1,3), "Work Status Version: " .. tostring(buffer(1,3)))
  tree:add(buffer(4,2), "Channel Status: " .. buffer(4,2))
  tree:add(buffer(6,2), "Channel Number: " .. buffer(6,2))
  tree:add(buffer(8,4), "Channel Card: " .. tostring(buffer(8,4)))
  tree:add(buffer(12,1), "Channel Port ID: " .. buffer(12,1))
  tree:add(buffer(13,1), "Channel ID: " .. buffer(13,1))
  tree:add(buffer(14,4), "InRoute Card: " .. tostring(buffer(14,4)))
  tree:add(buffer(18,1), "InRoute Port ID: " .. buffer(18,1))
  tree:add(buffer(19,1), "InRoute ID: " .. buffer(19,1))
  ---???
end


function Snd_Report_ChannelWorkStatus_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Snd_Report_ChannelWorkStatus]" .. "  Work Status version: " .. tostring(buffer(0,3)))
  tree:add(buffer(0,3), "Work Status version: " .. tostring(buffer(0,3)))
  for i = 0, (buffer(3,1):uint()-1) do
    local Sub_tree = tree:add(Var,buffer(i*17+5,10),"Work Status " .. (i+1) .. " Info: ")
      Sub_tree:add(buffer(i*17+5,4), "Output Card: " .. tostring(buffer(i*17+5,4)))
      Sub_tree:add(buffer(i*17+9,1), "Output Port ID: " .. tostring(buffer(i*17+9,1)))
      Sub_tree:add(buffer(i*17+10,1), "Output Port ID: " .. tostring(buffer(i*17+10,1)))
      Sub_tree:add(buffer(i*17+11,4), "Input Connectiong Card: " .. tostring(buffer(i*17+11,4)))
      Sub_tree:add(buffer(i*17+15,1), "Input Connectiong Port ID: " .. tostring(buffer(i*17+15,1)))
      Sub_tree:add(buffer(i*17+16,1), "Input Connectiong Channel ID: " .. tostring(buffer(i*17+16,1)))
  end
end


function Req_SwitchUser_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_SwitchUser]")
  tree:add(buffer(0,4), "Matrix Number: " ..  buffer(0,4))
  tree:add(buffer(4,2), "Last User ID: " .. buffer(4,2))
  tree:add(buffer(6,2), "New User ID: " .. buffer(6,2))
end



function Ret_SwitchUser_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
  pinfo.cols.info = ("[Ret_SwitchUser]" .. "  Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
  pinfo.cols.info = ("[Ret_Set_Fixed_ChannelRoute]" .. "  Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end

function Snd_Report_SwitchUser_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Snd_Report_SwitchUser]")
  tree:add(buffer(0,4), "Matrix Number: " ..  buffer(0,4))
  tree:add(buffer(4,2), "Last User ID: " .. buffer(4,2))
  tree:add(buffer(6,2), "New User ID: " .. buffer(6,2))
end


function Req_Set_Fixed_ChannelRoute_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Set_Fixed_ChannelRoute]" ..  " Set Number: " ..  buffer(0,2) .. "  In Box Number: " .. buffer(2,1) .. "  Out Box Number: " .. buffer(6,1))
  tree:add(buffer(0,2), "Set Number: " ..  buffer(0,2))
  tree:add(buffer(2,1), "In Box Number: " .. buffer(2,1))
  tree:add(buffer(3,1), "In Solt: " .. buffer(3,1))
  tree:add(buffer(4,1), "In Port Number: " .. buffer(4,1))
  tree:add(buffer(5,1), "In Channel Number: " .. buffer(5,1))
  tree:add(buffer(6,1), "Out Box Number: " .. buffer(6,1))
  tree:add(buffer(7,1), "Out Solt: " .. buffer(7,1))
  tree:add(buffer(8,1), "Out Port Number: " .. buffer(8,1))
  tree:add(buffer(9,1), "Out Channel Number: " .. buffer(9,1))
end


function Ret_Set_Fixed_ChannelRoute_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
  pinfo.cols.info = ("[Ret_Set_Fixed_ChannelRoute]" .. "  Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
  pinfo.cols.info = ("[Ret_Set_Fixed_ChannelRoute]" .. "  Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Set_Remote_InConn_ChannelRoute_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Set_Remote_InConn_ChannelRoute]" .. "  Total Set: " .. buffer(0,2) .. "  Box: " .. buffer(2,1) .. "  Solt: " .. buffer(3,1) .. " Port: " .. buffer(4,1))
  tree:add(buffer(0,2), "Total Set: " .. buffer(0,2))
  tree:add(buffer(2,1), "Box: " .. buffer(2,1))
  tree:add(buffer(3,1), "Solt: " .. buffer(3,1))
  tree:add(buffer(4,1), "Port: " .. buffer(4,1))
  
end


function Ret_Set_Remote_InConn_ChannelRoute_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
  pinfo.cols.info = ("[Ret_Set_Remote_InConn_ChannelRoute]" .. "  Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
  pinfo.cols.info = ("[Ret_Set_Remote_InConn_ChannelRoute]" .. "  Failed Card: " .. tostring(buffer(1,4)))
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
  tree:add(buffer(1,4), "Failed Card: " .. tostring(buffer(1,4)))
end


function Req_Save_Fixed_Channel_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Save_Fixed_Channel]" .. "  Set Number: " ..  buffer(0,2))
  tree:add(buffer(0,2), "Set Number: " ..  buffer(0,2))
  tree:add(buffer(2,1), "Input Box: " .. buffer(2,1))
  tree:add(buffer(3,1), "Input Solt: " .. buffer(3,1))
  tree:add(buffer(4,1), "Input Port: " .. buffer(4,1))
  tree:add(buffer(5,1), "Input Channel: " .. buffer(5,1))
  tree:add(buffer(6,1), "Output Box: " .. buffer(6,1))
  tree:add(buffer(7,1), "Output Solt: " .. buffer(7,1))
  tree:add(buffer(8,1), "Output Port: " .. buffer(8,1))
  tree:add(buffer(9,1), "Output Channel: " .. buffer(9,1))
end


function Rsp_Save_Fixed_Channel_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
  pinfo.cols.info = ("[Rsp_Save_Fixed_Channel]" .. "  Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
  pinfo.cols.info = ("[Rsp_Save_Fixed_Channel]" .. "  Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Query_Fixed_Channel_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Query_Fixed_Channel]")
  tree:add("Null")
end


function Rsp_Query_Fixed_Channel_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  pinfo.cols.info = ("[Rsp_Query_Fixed_Channel]" .. " Set Number: " ..  buffer(1,2))
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  pinfo.cols.info = ("[Rsp_Query_Fixed_Channel]" .. " Ack: Fail")
  end
  tree:add(buffer(0,2), "Set Number: " ..  buffer(1,2))
  for i = 0, (buffer(1,2):uint()-1) do
    local Fix_Channel_tree = tree:add(Var,buffer(i*8+3,8), "Channel " .. i .. ":")
      Fix_Channel_tree:add(buffer(i*8+3,1), "In Box Number: " .. buffer(i*8+3,1))
      Fix_Channel_tree:add(buffer(i*8+4,1), "In Solt: " .. buffer(i*8+4,1))
      Fix_Channel_tree:add(buffer(i*8+5,1), "In Port Number: " .. buffer(i*8+5,1))
      Fix_Channel_tree:add(buffer(i*8+6,1), "In Channel Number: " .. buffer(i*8+6,1))
      Fix_Channel_tree:add(buffer(i*8+7,1), "Out Box Number: " .. buffer(i*8+7,1))
      Fix_Channel_tree:add(buffer(i*8+8,1), "Out Solt: " .. buffer(i*8+8,1))
      Fix_Channel_tree:add(buffer(i*8+9,1), "Out Port Number: " .. buffer(i*8+9,1))
      Fix_Channel_tree:add(buffer(i*8+10,1), "Out Channel Number: " .. buffer(i*8+10,1))
  end
end


function Req_Qry_Record_Channel_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Qry_Record_Channel]")
  tree:add("Null")
end


function Rsp_Qry_Record_Channel_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  pinfo.cols.info = ("[Rsp_Qry_Record_Channel]" .. "  Ack: Success" .. "  Available Channle: " .. buffer(1,4))
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  pinfo.cols.info = ("[Rsp_Qry_Record_Channel]" .. "  Ack: Fail" .. " Available Channle: " .. buffer(1,4))
  end
  tree:add(buffer(1,4), "Available Channle: " .. buffer(1,4):uint())
end


function Req_Start_Record_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Start_Record]" .. "  Operation: " .. Operationtype[buffer(0,1)] .. " Camera Number: " .. buffer(1,2) .. "  Camera ID: " .. tostring(buffer(3,2)))
  tree:add(buffer(0,1), "Operation: " .. Operationtype[buffer(0,1)])
  tree:add(buffer(1,2), "Camera Number: " .. buffer(1,2))
  tree:add(buffer(3,2), "Camera ID: " .. tostring(buffer(3,2)))
end


function Rsp_Start_Record_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  pinfo.cols.info = ("[Rsp_Start_Record]" .. "  Operation Fail Number: " .. buffer(1,2) .. "  Camera ID: " .. buffer(3,2))
  else
  pinfo.cols.info = ("[Rsp_Start_Record]" .. "  Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
  tree:add(buffer(1,2), "Operation Fail Number: " .. buffer(1,2))
  tree:add(buffer(3,2), "Camera ID: " .. buffer(3,2))
end



function Req_Stop_Record_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Stop_Record]" .. " Operation: " .. Operationtype[buffer(0,1):uint()] .. "  Camera Number: " .. buffer(1,2) .. "  Camera ID: " .. buffer(3,2))
  tree:add(buffer(0,1), "Operation: " .. Operationtype[buffer(0,1):uint()])
  tree:add(buffer(1,2), "Camera Number: " .. buffer(1,2))
  tree:add(buffer(3,2), "Camera ID: " .. buffer(3,2))
end


function Rsp_Stop_Record_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  pinfo.cols.info = ("[Rsp_Stop_Record]" .. " Operation Fail Number: " .. buffer(1,2) .. "  Camera ID: " .. buffer(3,2))
  else
  pinfo.cols.info = ("[Rsp_Stop_Record]" .. " Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
  tree:add(buffer(1,2), "Operation Fail Number: " .. buffer(1,2))
  tree:add(buffer(3,2), "Camera ID: " .. buffer(3,2))
end


function Req_OnOff_Alarm_dissector(buffer,pinfo,tree)
  local type = {
    [0] = "Up Rise",
    [1] = "Down Rise",}
  pinfo.cols.info = ("[Req_OnOff_Alarm]" .. " Alarm: " .. buffer(0,2) .. "  Type: " .. type[buffer(2,1)])
  tree:add(buffer(0,2), "Alarm: " .. buffer(0,2))
  tree:add(buffer(2,1), "Type: " .. type[buffer(2,1)])
end


function Ret_OnOff_Alarm_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  pinfo.cols.info = ("[Ret_OnOff_Alarm]" .. " Ack: Success")
  else
    pinfo.cols.info = ("[Ret_OnOff_Alarm]" .. " Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end



function Req_General_Alarm_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_General_Alarm]" .. " Alarm Type Code: " .. buffer(0,4) .. "  Alarm Device Type: " .. buffer(4,2) .. "  Alarm Device ID: " .. buffer(6,4))
  tree:add(buffer(0,4), "Alarm Type Code: " .. buffer(0,4))
  tree:add(buffer(4,2), "Alarm Device Type: " .. buffer(4,2))
  tree:add(buffer(6,4), "Alarm Device ID: " .. buffer(6,4))
end


function Ret_General_Alarm_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
  pinfo.cols.info = ("[Ret_General_Alarm]" .. " Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
  pinfo.cols.info = ("[Ret_General_Alarm]" .. " Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Get_CardVersion_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Get_CardVersion]" .. " RomteCardID: " .. tostring(buffer(0,4)) ..  " BoxID: "  .. tostring(buffer(4,1)) .. " CardID: " .. tostring(buffer(5,4)) .. " CardSlot:  " .. tostring(buffer(9,1)))
  tree:add(buffer(0,4), "RomteCardID: " .. tostring(buffer(0,4)))
  tree:add(buffer(4,1), "BoxID: "  .. tostring(buffer(4,1)))
  tree:add(buffer(5,4), "CardID: " .. tostring(buffer(5,4)))
  tree:add(buffer(9,1), "CardSlot:  " .. tostring(buffer(9,1)))
end


function Ret_Get_CardVersion_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    pinfo.cols.info = ("[Ret_Get_CardVersion]" .. " CardNumber: " .. buffer(1,1))
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
  pinfo.cols.info = ("[Ret_Get_CardVersion]" .. " CardNumber: " .. buffer(1,1))
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
  tree:add(buffer(1,1), "CardNumber: " .. buffer(1,1):uint() .. " (" .. tostring(buffer(1,1)) .. ")")
  --tree:add(buffer(2,1), "CardID:" .. )
end



function Req_CpuDebug_Info_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_CpuDebug_Info]")
  tree:add("Null")
end


function Ret_CpuDebug_Info_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  pinfo.cols.info = ("[Ret_CpuDebug_Info]" .. " Card Number: " .. buffer(1,2) .. "  Card: " .. tostring(buffer(3,4)) .. " Version: " .. tostring(buffer(7,3)))
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  pinfo.cols.info = ("[Ret_CpuDebug_Info]" .. " Ack: Fail")
  end
  tree:add(buffer(1,2), "Card Number: " .. buffer(1,2):uint())
  tree:add(buffer(3,4), "Card: " .. tostring(buffer(3,4)))
  tree:add(buffer(7,3), "Version: " .. tostring(buffer(7,3)))
end


function Snd_DisconnectOpt_Info_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Snd_DisconnectOpt_Info]" .. "  Number: " .. buffer(0,2) .. " Card Number: " .. buffer(2,4))
  tree:add(buffer(0,2), "Number: " .. buffer(0,2))
  tree:add(buffer(2,4), "Card Number: " .. buffer(2,4))
  tree:add(buffer(6,1), "OPT2 Disconnect: " .. buffer(6,1))
  tree:add(buffer(7,1), "OPT3 Disconnect：" .. buffer(7,1))
  tree:add(buffer(8,1), "Disconnect Vedio Number: " .. buffer(8,1))
  tree:add(buffer(9,1), "OPT2 State: " ..  buffer(9,1))
end


function Ret_DisconnectOpt_Info_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
  pinfo.cols.info = ("[Ret_DisconnectOpt_Info]" .. "  Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
  pinfo.cols.info = ("[Ret_DisconnectOpt_Info]" .. "  Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Search_CPUCard_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Search_CPUCard]")
  return ture
end


function Ret_Search_CPUCard_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Ret_Search_CPUCard]" .. "  Device: " .. devicetype[buffer(0,1)] .. " IP Address: " .. buffer(1,1) .. "." ..buffer(2,1) .. "." .. buffer(3,1) .. "." ..buffer(4,1))
  tree:add(buffer(0,1), "Device: " .. type[buffer(0,1)])
  tree:add(buffer(1,4), "IP Address: " .. buffer(1,1) .. "." ..buffer(2,1) .. "." .. buffer(3,1) .. "." ..buffer(4,1))
  tree:add(buffer(5,4), "Subnet Mask: " .. buffer(5,1) .. "." ..buffer(6,1) .. "." .. buffer(7,1) .. "." ..buffer(8,1))
  tree:add(buffer(9,4), "Getway: " .. buffer(9,1) .. "." ..buffer(10,1) .. "." .. buffer(11,1) .. "." ..buffer(12,1))
  tree:add(buffer(13,6), "Mac: " .. buffer(13,1) .. "." ..buffer(14,1) .. "." .. buffer(15,1) .. "." ..buffer(16,1) "." ..buffer(17,1) "." ..buffer(18,1))
  tree:add(buffer(19,16), "Index: " .. tostring(buffer(19,16)))
  tree:add(buffer(35,8), "Version: " .. tostring(buffer(35,8)))   
end


function Req_Get_Boxinfo_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Get_Boxinfo]")
  tree:add("Null")
end


function Ret_Get_Boxinfo_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Ret_Get_Boxinfo]" .. " Box Number: " .. buffer(0,2) .. " Box Type: " .. buffer(2,1) .. " Cpu Slot: " .. buffer(3,1))
  tree:add(buffer(0,2), "Box Number: " .. buffer(0,2):uint() .. "(" .. tostring(buffer(0,2)) .. ")")
  tree:add(buffer(2,1), "Box Type: " .. buffer(2,1):uint() .. "(" .. tostring(buffer(2,1)) .. ")")
  tree:add(buffer(3,1),  "Cpu Slot: " .. buffer(3,1):uint() .. "(" .. tostring(buffer(3,1)) .. ")")
end



function Req_Get_CenterCardinfo_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Get_CenterCardinfo]")
  tree:add("Null")
end


function Ret_Get_CenterCardinfo_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Ret_Get_CenterCardinfo]" .. "  Card Number: " .. buffer(0,2) .. "  Card Type: " .. buffer(2,1) .. "  Card Solt: " .. buffer(3,1))
  tree:add(buffer(0,2), "Card Number: " .. buffer(0,2):uint())
  tree:add(buffer(2,1), "Card Type: " .. buffer(2,1):uint())
  tree:add(buffer(3,1), "Card Solt: " .. buffer(3,1):uint())
end



function Req_Get_FrontCardinfo_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Get_FrontCardinfo]")
  tree:add("Null")
end


function Ret_Get_FrontCardinfo_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Ret_Get_FrontCardinfo]" .. " Matrix Card Number: " .. buffer(0,2))
  tree:add(buffer(0,2), "Matrix Card Number: " .. buffer(0,2):uint())
  local Matrix_Card_Info_tree = tree:add(Var, buffer(2,15),"Matrix Card Info")
    Matrix_Card_Info_tree:add(buffer(2,1), "Systerm ID: " .. buffer(2,1):uint())
    Matrix_Card_Info_tree:add(buffer(3,1), "Matrix ID: " .. buffer(3,1):uint())
    Matrix_Card_Info_tree:add(buffer(4,1), "Box: " .. buffer(4,1):uint())
    Matrix_Card_Info_tree:add(buffer(5,1), "Solt ID: " .. buffer(5,1):uint())
    Matrix_Card_Info_tree:add(buffer(6,1), "Port ID: " .. buffer(6,1):uint())
    Matrix_Card_Info_tree:add(buffer(7,2), "Remote Card Number: " .. buffer(7,2):uint())
    Matrix_Card_Info_tree:add(buffer(9,1), "Remote Card Type: " .. buffer(9,1):uint())
    Matrix_Card_Info_tree:add(buffer(10,4), "Remote Card: " .. buffer(10,4):uint())
    Matrix_Card_Info_tree:add(buffer(14,1), "Remote Card Turn: " .. buffer(14,1):uint())
    Matrix_Card_Info_tree:add(buffer(15,1), "Remote Card Start: " .. buffer(15,1):uint())
    Matrix_Card_Info_tree:add(buffer(16,1), "Vedio Number: " .. buffer(16,1):uint())
end



function Req_Set_TextMask_HD_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Set_TextMask_HD]" .. " Remote Card: " .. tostring(buffer(0,4)) .. "  Box: " .. tostring(buffer(4,1)) .. "  Card: " .. tostring(buffer(5,4)) .. " Card Solt: " .. buffer(9,1))
  tree:add(buffer(0,4), "Remote Card: " .. tostring(buffer(0,4)))
  tree:add(buffer(4,1), "Box: " .. tostring(buffer(4,1)))
  tree:add(buffer(5,4), "Card: " .. tostring(buffer(5,4)))
  tree:add(buffer(9,1), "Card Solt: " .. buffer(9,1))
  tree:add(buffer(10,1), "Port ID: " .. buffer(10,1))
  tree:add(buffer(11,1), "Channel: " .. buffer(11,1))
  tree:add(buffer(12,1), "Set: " .. set[buffer(12,1)] .. "(" .. tostring(buffer(12,1)) .. ")")
  tree:add(buffer(13,1), "Date: " .. display[buffer(13,1)] .. "(" .. tostring(buffer(13,1)) .. ")")
  tree:add(buffer(14,2), "Display_X: " .. buffer(14,2))
  tree:add(buffer(16,2), "Display_Y: " .. buffer(16,2))
  tree:add(buffer(18,1), "Date Type: " .. datetype[buffer(18,1)] .. "(" .. tostring(buffer(18,1)) .. ")")
  tree:add(buffer(19,1), "Time: " .. display[buffer(19,1)] .. "(" .. tostring(buffer(19,1)) .. ")")
  tree:add(buffer(20,2), "Display_X: " .. buffer(20,2))
  tree:add(buffer(22,2), "Display_Y: " .. buffer(22,2))
  tree:add(buffer(24,1), "Time: " .. second[buffer(24,1)] .. "(" .. tostring(buffer(24,1)) .. ")")
end


function Ret_Set_TextMask_HD_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  pinfo.cols.info = ("[Ret_Set_TextMask_HD]" .. " Ack: Success")
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  pinfo.cols.info = ("[Ret_Set_TextMask_HD]" .. " Ack: Fail")
  end
end



function Req_Set_TimeMask_HD_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Set_TimeMask_HD]")
end


function Ret_Set_TimeMask_HD_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  pinfo.cols.info = ("[Ret_Set_TimeMask_HD]" .. " Ack: Success")
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  pinfo.cols.info = ("[Ret_Set_TimeMask_HD]" .. " Ack: Fail")
  end
end



function Req_Query_VideoMapping_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Query_VideoMapping]" .. "  Monitor ID: " .. buffer(0,4))
  tree:add(buffer(0,4), "Monitor ID: " .. buffer(0,4):uint())
end


function Ret_Query_VideoMapping_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  pinfo.cols.info = ("[Ret_Query_VideoMapping]" .. "  Camera ID: " .. buffer(1,4))
  else
  pinfo.cols.info = ("[Ret_Query_VideoMapping]" .. "  Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
  tree:add(buffer(1,4), "Camera ID: " .. buffer(1,4):uint())
end


function Ret_SetOutputMode_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
  pinfo.cols.info = ("[Ret_SetOutputMode]" .. " Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
  pinfo.cols.info = ("[Ret_SetOutputMode]" .. " Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_SetOutputMode_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_SetOutputMode]")
  ---???
end


function Req_Reset_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Reset]" .. " User ID: " .. buffer(0,1) .. "  Box: " .. buffer(1,1) .. "  Card: " .. buffer(2,8) .. " Solt: " .. buffer(10,1))
  tree:add(buffer(0,1), "User ID: " .. buffer(0,1):uint())
  tree:add(buffer(1,1), "Box: " .. buffer(1,1):uint())
  tree:add(buffer(2,8), "Card: " .. buffer(2,8):uint())
  tree:add(buffer(10,1), "Solt: " .. buffer(10,1):uint())
end


function Ret_Reset_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  pinfo.cols.info = ("[Ret_Reset]" .. " Ack: Success")
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  pinfo.cols.info = ("[Ret_Reset]" .. " Ack: Fail")
  end
end



function Req_SetPool_Channel_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Ret_Set_TextDotInfo]" .. " Input Set Total: " .. buffer(0,2))
  tree:add(buffer(0,2), "Input Set Total: " .. buffer(0,2))
  tree:add(buffer(2,1), "Input Box: " .. buffer(2,1))
  tree:add(buffer(3,1), "Input Solt: " .. buffer(3,1))
  tree:add(buffer(4,1), "Input Port: " .. buffer(4,1))
  tree:add(buffer(5,1), "Input Channel: " .. buffer(5,1))
  tree:add(buffer(6,1), "Output Box: " .. buffer(6,1))
  tree:add(buffer(7,1), "Output Solt: " .. buffer(7,1))
  tree:add(buffer(8,1), "Output Port: " .. buffer(8,1))
  tree:add(buffer(9,1), "Output Channel: " .. buffer(9,1))
end


function Ret_SetPool_Channel_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
  pinfo.cols.info = ("[Ret_SetPool_Channel]" .. " Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
  pinfo.cols.info = ("[Ret_SetPool_Channel]" .. " Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Set_Update_dissector(buffer,pinfo,tree)
    local device = {
    [0] = "MCU",
    [1] = "FPGA",}
  pinfo.cols.info = ("[Req_Set_Update]" .. buffer(0,4))
  tree:add(buffer(0,4), "Remote Card ID: " .. buffer(0,4))
  tree:add(buffer(4,1), "Center Box NO: " .. buffer(4,1))
  tree:add(buffer(5,4), "Center Card ID: " .. buffer(5,4))
  tree:add(buffer(9,1), "Center Card Solt: " .. buffer(9,1))
  tree:add(buffer(10,1), "Port NO: " .. buffer(10,1))
  tree:add(buffer(11,1), "Channel NO: " .. buffer(11,1))
  tree:add(buffer(12,1), "Update Type: " .. device[buffer(12,1)] .. "(" .. tostring(buffer(12,1)) .. ")")
  tree:add(buffer(13,1), "Device ID: " .. buffer(13,1))
end


function Ret_Set_Update_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
  pinfo.cols.info = ("[Ret_Set_Update]" .. " Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
  pinfo.cols.info = ("[Ret_Set_Update]" .. " Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Set_MulChannelRoute_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Set_MulChannelRoute]")
  tree:add(buffer(0,2), "Count: " .. buffer(0,2))
  if buffer(2,1):uint() == 0 then
      tree:add(buffer(2,1), "Operation Mark: Rmove")
  else
      tree:add(buffer(2,1), "Operation Mark: Build")
  end
  tree:add(buffer(3,1), "Input Card Box: " .. buffer(3,1))
  tree:add(buffer(4,4), "Input Card ID: " .. buffer(4,4))
  tree:add(buffer(8,1), "Input Card Solt: " .. buffer(8,1))
  tree:add(buffer(9,1), "Input Card Port: " .. buffer(9,1))
  tree:add(buffer(10,1), "Input Card Channel: " .. buffer(10,1))
  tree:add(buffer(11,2), "Input Channel Card ID: " .. buffer(11,2))
  tree:add(buffer(13,1), "Output Card Box: " .. buffer(13,1))
  tree:add(buffer(14,4), "Output Card ID: " .. buffer(14,4))
  tree:add(buffer(18,1), "Output Card Solt: " .. buffer(18,1))
  tree:add(buffer(19,1), "Output Card Port: " .. buffer(19,1))
  tree:add(buffer(20,1), "Output Card Channel: " .. buffer(20,1))
  tree:add(buffer(21,2), "Output Channel Card ID: " .. buffer(21,2))
end


function Ret_Set_MulChannelRoute_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
  pinfo.cols.info = ("[Ret_Set_MulChannelRoute]" .. " Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
  pinfo.cols.info = ("[Ret_Set_MulChannelRoute]" .. " Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Set_MulCamSwi_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Set_MulCamSwi]")
  tree:add(buffer(0,2), "Count: " .. buffer(0,2))
  tree:add(buffer(2,1), "Sub Window ID: " .. buffer(2,1))
  tree:add(buffer(3,1), "User ID: " .. buffer(3,1))
  tree:add(buffer(4,2), "Site ID: " .. buffer(4,2))
  tree:add(buffer(6,2), "Monitor ID: " .. buffer(6,2))
  tree:add(buffer(8,4), "Camera ID: " .. buffer(8,4))
end


function Ret_Set_MulCamSwi_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
  pinfo.cols.info = ("[Ret_Set_MulCamSwi]" .. " Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
  pinfo.cols.info = ("[Ret_Set_MulCamSwi]" .. " Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Set_MonitorRoute_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Break (" .. tostring(buffer(0,1)) .. ")")
  pinfo.cols.info = ("[Req_Set_MonitorRoute]" .. "  Break" .. "Camera ID: " .. tostring(buffer(2,4)))
  else
    tree:add(buffer(0,1), "Set (" .. tostring(buffer(0,1)) .. ")")
  pinfo.cols.info = ("[Req_Set_MonitorRoute]" .. "  Set" .. "Camera ID: " .. tostring(buffer(2,4)))
  end
  tree:add(buffer(1,1), "Input Box: " .. buffer(1,1))
  tree:add(buffer(2,4), "Camera ID: " .. tostring(buffer(2,4)))
  tree:add(buffer(6,1), "Input Solt: " .. buffer(6,1))
  tree:add(buffer(7,1), "Input Port: " .. buffer(7,1))
  tree:add(buffer(8,1), "Input Channel: " .. buffer(8,1))
  tree:add(buffer(9,2), "Combine: " .. tostring(buffer(9,2)))
  tree:add(buffer(11,1), "TVWall: " .. buffer(11,1))
  tree:add(buffer(12,2), "Screen ID: " .. buffer(12,2))
end


function Ret_Set_MonitorRoute_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  pinfo.cols.info = ("[Ret_Set_MonitorRoute]" .. "  Ack: Success")
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  pinfo.cols.info = ("[Ret_Set_MonitorRoute]" .. "  Ack: Fail")
  end
end



function Req_Set_MulMonitorRoute_dissector(buffer,pinfo,tree)
  tree:add(buffer(0,2), "Count: " .. buffer(0,2))
  if buffer(2,1):uint() == 0 then
    tree:add(buffer(2,1), "Break (" .. tostring(buffer(2,1)) .. ")")
  pinfo.cols.info = ("[Req_Set_MulMonitorRoute]" .. "  Break")
  else
    tree:add(buffer(2,1), "Set (" .. tostring(buffer(2,1)) .. ")")
  pinfo.cols.info = ("[Req_Set_MulMonitorRoute]" .. "  Set")
  end
  tree:add(buffer(3,1), "Input Box: " .. buffer(3,1))
  tree:add(buffer(4,4), "Camera ID: " .. tostring(buffer(4,4)))
  tree:add(buffer(8,1), "Input Solt: " .. buffer(8,1))
  tree:add(buffer(9,1), "Input Port: " .. buffer(9,1))
  tree:add(buffer(10,1), "Input Channel: " .. buffer(10,1))
  tree:add(buffer(11,2), "Combine: " .. tostring(buffer(11,2)))
  tree:add(buffer(13,1), "TVWall: " .. buffer(13,1))
  tree:add(buffer(14,2), "Screen ID: " .. buffer(14,2))
end


function Ret_Set_MulMonitorRoute_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  pinfo.cols.info = ("[Ret_Set_MulMonitorRoute]" .. "  Ack: Success")
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  pinfo.cols.info = ("[Ret_Set_MulMonitorRoute]" .. "  Ack: Fail")
  end
end


function Req_Set_AlarmMask_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Set_AlarmMask]")
  tree:add(buffer(0,1), "Mask Type: " .. buffer(0,1))
  tree:add(buffer(1,4), "Camera ID: " .. tostring(buffer(1,4)))
  tree:add(buffer(5,2), "User ID: " .. buffer(5,2))
  tree:add(buffer(7,1), "Input Information: " .. tostring(buffer(7,1)))
  tree:add(buffer(8,4), "Remote Card ID: " .. buffer(8,4))
  tree:add(buffer(12,1), "Box ID: " .. buffer(12,1))
  tree:add(buffer(13,4), "Center Card ID: " .. buffer(13,4))
  tree:add(buffer(17,1), "Center Card Solt: " .. tostring(buffer(17,1)))
  tree:add(buffer(18,1), "Center Card Port: " .. buffer(18,1))
  tree:add(buffer(19,1), "Center Card Channel: " .. buffer(19,1))
  tree:add(buffer(20,1), "Mask Mark: " .. buffer(20,1))
end


function Ret_Set_AlarmMask_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
    pinfo.cols.info = ("[Ret_Set_AlarmMask]" .. "  Ack: Success")
  elseif buffer(0,1):uint() == 1 then
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
    pinfo.cols.info = ("[Ret_Set_AlarmMask]" .. "  Ack: Fail")
  elseif buffer(0,1):uint() == 2 then
    tree:add(buffer(0,1), "Ack: Locked (" .. tostring(buffer(0,1)) .. ")")
    pinfo.cols.info = ("[Ret_Set_AlarmMask]" .. "  Ack: Locked")
  end
end


function Req_Set_CardReset_dissector(buffer,pinfo,tree)
    local resettype = {
    [0] = "MCU",
    [1] = "FPGA",
    [2] = "MCU And FPGA",
    [3] = "Card Reset",
    [4] = "MCU Restore settings",
    [5] = "FPGA Restore settings",
    [6] = "Card Restore settings",}
  pinfo.cols.info = ("[Req_Set_CardReset]" .. buffer(0,4))
  tree:add(buffer(0,4), "Remote Card ID: " .. buffer(0,4))
  tree:add(buffer(4,1), "Center Box NO: " .. buffer(4,1))
  tree:add(buffer(5,4), "Center Card ID: " .. buffer(5,4))
  tree:add(buffer(9,1), "Center Card Solt: " .. buffer(9,1))
  tree:add(buffer(10,1), "Port NO: " .. buffer(10,1))
  tree:add(buffer(11,1), "Channel NO: " .. buffer(11,1))
  tree:add(buffer(12,1), "Reset Type: " .. resettype[buffer(12,1):uint()] .. "(" .. tostring(buffer(12,1)) .. ")")
  tree:add(buffer(13,1), "Device ID: " .. buffer(13,1))
end

function Ret_Set_CardReset_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
  pinfo.cols.info = ("[Ret_Set_CardReset]" .. " Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
  pinfo.cols.info = ("[Ret_Set_CardReset]" .. " Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Set_FlowStatis_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Set_FlowStatis]")
  tree:add(buffer(0,6), "Remote Card ID: " .. tostring(buffer(0,6)))
  tree:add(buffer(6,1), "Remote Port: " .. buffer(6,1))
  tree:add(buffer(7,1), "Remote Channel: " .. buffer(7,1))
  tree:add(buffer(8,1), "Center Box NO: " .. buffer(8,1))
  tree:add(buffer(9,6), "Center Card ID: " .. tostring(buffer(9,6)))
  tree:add(buffer(15,1), "Center Card Solt: " .. buffer(15,1))
  tree:add(buffer(16,1), "Port NO: " .. buffer(16,1))
  tree:add(buffer(17,1), "Channel NO: " .. buffer(17,1))
  tree:add(buffer(18,6), "MAC Address: " .. tostring(buffer(18,6)))
  tree:add(buffer(24,1), "Get Code: " .. buffer(24,1))
  tree:add(buffer(25,1), "Result Status: " .. buffer(25,1))
  tree:add(buffer(26,1), "Port Num: " .. buffer(26,1))
  if buffer(27,1):uint() == 0 then
  	  tree:add(buffer(27,1), "OpCode: Refresh(" .. buffer(27,1) .. ")")
  else
      tree:add(buffer(27,1), "OpCode: Reset(" .. buffer(27,1) .. ")")
  end
  tree:add(buffer(28,8), "Port Map: " .. tostring(buffer(28,8)),2)
end

function Ret_Set_FlowStatis_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
  		pinfo.cols.info = ("[Ret_Set_FlowStatis]" .. " Ack: Success")
    	tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
      tree:add(buffer(1,1), "Port Num: " .. buffer(1,1):uint())
	    tree:add(buffer(2,8), "Port Map: " .. buffer(2,8))
      tree:add(buffer(10,2), "Valid Items Mask: " .. buffer(10,2))
      local portnum = buffer(1,1):uint()
      for i = 0 ,portnum-1 do
        local portflowstatis_tree = tree:add(Var,buffer(12,i*48),"Port Flow Statis:")    	  
    	  portflowstatis_tree:add(buffer(12+i*48,8), "RxGoodOctets: " .. buffer(12+i*48,8))
    	  portflowstatis_tree:add(buffer(20+i*48,4), "RxUnicastPkts: " .. buffer(20+i*48,4):uint())
    	  portflowstatis_tree:add(buffer(24+i*48,4), "RxBroadcastPkts: " .. buffer(24+i*48,4):uint())
    	  portflowstatis_tree:add(buffer(28+i*48,4), "RxMulticastPkts: " .. buffer(28+i*48,4):uint())
    	  portflowstatis_tree:add(buffer(32+i*48,4), "RxPausePkts: " .. buffer(32+i*48,4):uint())
    	  portflowstatis_tree:add(buffer(36+i*48,8), "TxOctets: " .. buffer(36+i*48,8))
    	  portflowstatis_tree:add(buffer(44+i*48,4), "TxUnicastPkts: " .. buffer(44+i*48,4):uint())
    	  portflowstatis_tree:add(buffer(48+i*48,4), "TxBroadcastPkts: " .. buffer(48+i*48,4):uint())
    	  portflowstatis_tree:add(buffer(52+i*48,4), "TxMulticastPkts: " .. buffer(52+i*48,4):uint())
    	  portflowstatis_tree:add(buffer(56+i*48,4), "TxPausePkts: " .. buffer(56+i*48,4):uint())
      end
    	tree:add(buffer(60,16), "Reserved[4]: " .. buffer(12+portnum*48,16))
  else
  	pinfo.cols.info = ("[Ret_Set_FlowStatis]" .. " Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end

end


function Req_Trap_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Trap]")
  tree:add(buffer(0,4), "Device ID: " .. tostring(buffer(0,4)))
  tree:add(buffer(4,6), "MAC Address: " .. tostring(buffer(4,6)))
end

function Ret_Trap_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
  pinfo.cols.info = ("[Ret_Trap]" .. " Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
  pinfo.cols.info = ("[Ret_Trap]" .. " Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end



function Req_Set_SwitchInfoV1_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Set_SwitchInfoV1]")
  tree:add(buffer(0,1), "Patrol Queue ID: " .. tostring(buffer(0,1)))
  tree:add(buffer(1,1), "Patrol Queue Step: " .. tostring(buffer(1,1)))
  tree:add(buffer(2,1), "Group switching ID: " .. tostring(buffer(2,1)))
  tree:add(buffer(3,1), "Group switching Step: " .. tostring(buffer(3,1)))
  tree:add(buffer(4,4), "Camera ID: " .. tostring(buffer(4,4)))
  tree:add(buffer(8,1), "Delay: " .. tostring(buffer(8,1)))
  tree:add(buffer(9,1), "Set: " .. tostring(buffer(9,1)))
  tree:add(buffer(10,1), "Assistant: " .. tostring(buffer(10,1)))
  tree:add(buffer(11,1), "Linkage: " .. tostring(buffer(11,1)))
end

function Ret_Set_SwitchInfoV1_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    pinfo.cols.info = ("[Ret_Set_SwitchInfoV1]" .. " Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
    pinfo.cols.info = ("[Ret_Set_SwitchInfoV1]" .. " Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Get_SwitchInfoV1_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Get_SwitchInfoV1]")
  tree:add("Req_Get_SwitchInfoV1")
end



function Ret_Get_SwitchInfoV1_dissector(buffer,pinfo,tree)
    if buffer(0,1):uint() == 0 then
      pinfo.cols.info = ("[Ret_Set_SwitchInfoV1]" .. " Ack: Success")
      tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
      tree:add(buffer(0+1,1), "Patrol Queue ID: " .. tostring(buffer(0+1,1)))
      tree:add(buffer(1+1,1), "Patrol Queue Step: " .. tostring(buffer(1+1,1)))
      tree:add(buffer(2+1,1), "Group switching ID: " .. tostring(buffer(2+1,1)))
      tree:add(buffer(3+1,1), "Group switching Step: " .. tostring(buffer(3+1,1)))
      tree:add(buffer(4+1,4), "Camera ID: " .. tostring(buffer(4+1,4)))
      tree:add(buffer(8+1,1), "Delay: " .. tostring(buffer(8+1,1)))
      tree:add(buffer(9+1,1), "Set: " .. tostring(buffer(9+1,1)))
      tree:add(buffer(10+1,1), "Assistant: " .. tostring(buffer(10+1,1)))
      tree:add(buffer(11+1,1), "Linkage: " .. tostring(buffer(11+1,1)))
  else
    pinfo.cols.info = ("[Ret_Set_SwitchInfoV1]" .. " Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Set_MonitorInfoV1_dissector(buffer,pinfo,tree)
      pinfo.cols.info = ("[Req_Set_MonitorInfoV1]")
end


function Ret_Set_MonitorInfoV1_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    pinfo.cols.info = ("[Ret_Set_MonitorInfoV1]" .. " Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
    pinfo.cols.info = ("[Ret_Set_MonitorInfoV1]" .. " Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Get_MonitorInfoV1_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Get_SwitchInfoV1]")
  tree:add("Req_Get_SwitchInfoV1")
end



function Ret_Get_MonitorInfoV1_dissector(buffer,pinfo,tree)
    if buffer(0,1):uint() == 0 then
      pinfo.cols.info = ("[Ret_Set_SwitchInfoV1]" .. " Ack: Success")
  else
    pinfo.cols.info = ("[Ret_Set_SwitchInfoV1]" .. " Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end



function Req_Set_SiteNo_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Set_SiteNo]")
  tree:add(buffer(0,2), "Camera Site: " .. tostring(buffer(2,2)))
  tree:add(buffer(2,2), "Monitor Site: " .. tostring(buffer(2,2)))
end

function Ret_Set_SiteNo_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    pinfo.cols.info = ("[Ret_Set_SiteNo]" .. " Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
    pinfo.cols.info = ("[Ret_Set_SiteNo]" .. " Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Get_WorkStatus_New_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Get_WorkStatus_New]")
  tree:add(buffer(0,3), "Version: " .. tostring(buffer(0,1)))
end



function Ret_Get_WorkStatus_New_dissector(buffer,pinfo,tree)
	local powerstatus = {
    	[0] = "Normal",
    	[1] = "Fault",
    	[2] = "Overload",
    	[3] = "Low",
    }
  if buffer(0,1):uint() == 0 then
    pinfo.cols.info = ("[Ret_Get_WorkStatus_New]" .. " Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
    tree:add(buffer(1,3), "Version: " .. tostring(buffer(1,3)))
    tree:add(buffer(4,1), "Power Count: " .. buffer(4,1))
    local powernum = buffer(4,1):uint()
    local powerstatus_tree = tree:add(Var,buffer(5,1+powernum*1),"Power Info:")
    	for i = 0, (powernum-1) do	
        	powerstatus_tree:add(buffer(5+1*i,1), "Power" .. (i+1) .. " Info: " .. powerstatus[buffer(5+1*i,1):uint()] .. "(" .. buffer(5+1*i,1) .. ")")
  		end
  	tree:add(buffer(5+1*powernum,2), "Card Count: " .. buffer(5+1*powernum,2))
  	local cardnum = buffer(5+1*powernum,2):uint()
  	local statusbytes = 0
  		for i = 0, (cardnum-1) do	
           	if buffer(5+1*powernum+2+statusbytes+ 6,1):uint() < 128 then 
        		local portnum = buffer(5+1*powernum+2+statusbytes+7,1):uint()
        		local portnumbytes = math.ceil(portnum/2)
        		local cardstatus_tree = tree:add(Var,buffer(5+1*powernum+2+statusbytes,6+portnumbytes), "Card " .. tostring(buffer(5+1*powernum+2+statusbytes,6)) .. " Status")
        		cardstatus_tree:add(buffer(5+1*powernum+2+statusbytes,6), "Card ID: " .. tostring(buffer(5+1*powernum+2+statusbytes,6)))
        		cardstatus_tree:add(buffer(5+1*powernum+2+statusbytes+6,1), "Port Status: Up")
        		cardstatus_tree:add(buffer(5+1*powernum+2+statusbytes+7,1), "Port Number: " .. portnum)
        		cardstatus_tree:add(buffer(5+1*powernum+2+statusbytes+8,portnumbytes), "Port Status: " .. tostring(buffer(5+1*powernum+2+statusbytes+8,portnumbytes)))
        		statusbytes = statusbytes+6+1+1+portnumbytes
        	else
        		local cardstatus_tree = tree:add(Var,buffer(5+1*powernum+2+statusbytes,6+1), "Card " .. tostring(buffer(5+1*powernum+2+statusbytes,6)) .. " Status")
        		cardstatus_tree:add(buffer(5+1*powernum+2+statusbytes,6), "Card ID: " .. tostring(buffer(5+1*powernum+2+statusbytes,6)))
        		cardstatus_tree:add(buffer(5+1*powernum+2+statusbytes+6,1), "Port Status: Down")
        		statusbytes = statusbytes + 7  		
        	end
  		end
  else
    pinfo.cols.info = ("[Ret_Get_WorkStatus_New]" .. " Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Snd_Win_Input_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Snd_Win_Input]")
  tree:add(buffer(0,1), "Large Screen ID: " .. tostring(buffer(0,1)))
  tree:add(buffer(1,2), "Monitor Site: " .. tostring(buffer(1,2)))
  tree:add(buffer(3,2), "Window Count: " .. tostring(buffer(3,2)))
end


function Ret_Snd_Win_Input_New_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    pinfo.cols.info = ("[Ret_Snd_Win_Input]" .. " Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
    pinfo.cols.info = ("[Ret_Snd_Win_Input]" .. " Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Set_UpdateV1_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Set_Update]" .. buffer(0,6))
  tree:add(buffer(0,6), "Remote Card ID: " .. buffer(0,6))
  tree:add(buffer(6,1), "Center Box NO: " .. buffer(6,1))
  tree:add(buffer(7,6), "Center Card ID: " .. buffer(7,6))
  tree:add(buffer(13,1), "Center Card Solt: " .. buffer(13,1))
  tree:add(buffer(14,1), "Port NO: " .. buffer(14,1))
  tree:add(buffer(15,1), "Channel NO: " .. buffer(15,1))
  tree:add(buffer(16,1), "Update Type: " .. device[buffer(16,1)] .. "(" .. tostring(buffer(16,1)) .. ")")
  tree:add(buffer(17,1), "Device ID: " .. buffer(17,1))
end


function Ret_Set_UpdateV1_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
  pinfo.cols.info = ("[Ret_Set_Update]" .. " Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
  pinfo.cols.info = ("[Ret_Set_Update]" .. " Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Set_CardResetV1_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Set_CardReset]" .. buffer(0,6))
  tree:add(buffer(0,6), "Remote Card ID: " .. buffer(0,6))
  tree:add(buffer(6,1), "Center Box NO: " .. buffer(6,1))
  tree:add(buffer(7,6), "Center Card ID: " .. buffer(7,6))
  tree:add(buffer(13,1), "Center Card Solt: " .. buffer(13,1))
  tree:add(buffer(14,1), "Port NO: " .. buffer(14,1))
  tree:add(buffer(15,1), "Channel NO: " .. buffer(15,1))
  tree:add(buffer(16,1), "Reset Type: " .. resettype[buffer(16,1):uint()] .. "(" .. tostring(buffer(16,1)) .. ")")
  tree:add(buffer(17,1), "Device ID: " .. buffer(17,1))
end


function Ret_Set_CardResetV1_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
  pinfo.cols.info = ("[Ret_Set_CardReset]" .. " Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
  pinfo.cols.info = ("[Ret_Set_CardReset]" .. " Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end

function Req_Get_CardVersionV1_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Get_CardVersionV1]" .. buffer(0,6))
  tree:add(buffer(0,6), "Remote Card ID: " .. buffer(0,6))
  tree:add(buffer(6,1), "Center Box NO: " .. buffer(6,1))
  tree:add(buffer(7,6), "Center Card ID: " .. buffer(7,6))
  tree:add(buffer(13,1), "Center Card Solt: " .. buffer(13,1))
  tree:add(buffer(14,1), "Port NO: " .. buffer(14,1))
  tree:add(buffer(15,1), "Channel NO: " .. buffer(15,1))
  tree:add(buffer(16,1), "Reset Type: " .. resettype[buffer(16,1):uint()] .. "(" .. tostring(buffer(16,1)) .. ")")
  tree:add(buffer(17,1), "Device ID: " .. buffer(17,1))
end


function Ret_Get_CardVersionV1_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    pinfo.cols.info = ("[Ret_Get_CardVersionV1]" .. " Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
    tree:add(buffer(1,2), "Card Count:" .. tostring(buffer(1,2)) .. ")")
  else
    pinfo.cols.info = ("[Ret_Get_CardVersionV1]" .. " Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end















--[[Large screen Protocol
















]]--


function Req_Del_MonitorInfo_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Del_MonitorInfo]" .. "TVWall: " .. buffer(0,1))
  tree:add(buffer(0,1), "TVWall: " .. buffer(0,1))
end


function Ret_Del_MonitorInfo_dissector(buffer,pinfo,tree)

  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Del_MonitorInfo]" .. "Ack: Success")
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Del_MonitorInfo]" .. "Ack: Fail")
  end
end


function Req_Set_WinInfo_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Set_WinInfo]" .. "	TVWall: " .. buffer(0,1) .. "	Scene: " .. buffer(1,2))
  tree:add(buffer(0,1), "TVWall: " .. buffer(0,1))
  tree:add(buffer(1,2), "Scene: " .. buffer(1,2))
  tree:add(buffer(3,4), "Start Y: " .. buffer(3,4))
  tree:add(buffer(7,4), "Start X: " .. buffer(7,4))
  tree:add(buffer(11,4), "End Y: " .. buffer(11,4))
  tree:add(buffer(15,4), "End X: " .. buffer(15,4))
end


function Ret_Set_WinInfo_dissector(buffer,pinfo,tree)

  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Set_WinInfo]" .. "Ack: Success" .. "	TVWall: " .. buffer(1,1) .. "	Scene: " .. buffer(2,2))
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Set_WinInfo]" .. "Ack: Fail" .. "	TVWall: " .. buffer(1,1) .. "	Scene: " .. buffer(2,2))
  end
  tree:add(buffer(1,1), "TVWall: " .. buffer(1,1))
  tree:add(buffer(2,2), "Scene: " .. buffer(2,2))
  tree:add(buffer(4,2), "Windows: " .. buffer(4,2))
end


function Req_Modify_WinInfo_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Modify_WinInfo]" .. "	TVWall: " .. buffer(0,1) .. "	Scene: " .. buffer(1,2) .. "	Window: " .. buffer(21,2))
  tree:add(buffer(0,1), "TVWall: " .. buffer(0,1))
  tree:add(buffer(1,2), "Scene: " .. buffer(1,2))
  tree:add(buffer(3,18), "Window Info: " .. tostring(buffer(3,18)))
  tree:add(buffer(21,2), "Window ID: " .. buffer(21,2))
  tree:add(buffer(23,4), "Start Y: " .. buffer(23,4))
  tree:add(buffer(27,4), "Start X: " .. buffer(27,4))
  tree:add(buffer(31,4), "End Y: " .. buffer(31,4))
  tree:add(buffer(35,4), "End X: " .. buffer(35,4)) 
end

function Ret_Modify_WinInfo_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Modify_WinInfo]" .. "Ack: Success")
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Modify_WinInfo]" .. "Ack: Fail")
  end
end


function Req_Del_WinInfo_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Del_WinInfo]" .. "	TVWall: " .. buffer(0,1) .. "	Scene: " .. buffer(1,2) .. "	Windows: " .. buffer(3,2))
  tree:add(buffer(0,1), "TVWall: " .. buffer(0,1))
  tree:add(buffer(1,2), "Scene: " .. buffer(1,2))
  tree:add(buffer(3,2), "Windows: " .. buffer(3,2))
end


function Ret_Del_WinInfo_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Del_WinInfo]" .. "Ack: Success")
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Del_WinInfo]" .. "Ack: Fail")
  end
end


function Req_Get_SceneInfo_dissector(buffer,pinfo,tree)
  if buffer(0,1) == 256 then
    tree:add(buffer(0,1), "Get All TVWall")
  else
    tree:add(buffer(0,1), "Get TVWall " .. buffer(0,1))
  end
  if buffer(1,2) == 65535 then
    tree:add(buffer(0,2), "Get All Scene")
	pinfo.cols.info = ("[Req_Get_SceneInfo]" .. "Get All Scene")	
  elseif buffer(1,2) == 65534 then
    tree:add(buffer(1,2), "Get The Current Scene" .. buffer(1,2))
	pinfo.cols.info = ("[Req_Get_SceneInfo]" .. "Get The Current Scene")	
  else
    tree:add(buffer(1,2), "Get The" .. buffer(1,2):uint() .. "Scene")
	pinfo.cols.info = ("[Req_Get_SceneInfo]" .. "Get The" .. buffer(1,2):uint() .. "Scene")
  end
end


function Ret_Get_SceneInfo_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Ret_Get_SceneInfo]" .. "TVWall: " .. buffer(0,1) .. "	Scene: " .. buffer(1,2) .. "	Windows Number: " .. buffer(4,1))
  tree:add(buffer(0,1), "TVWall: " .. buffer(0,1))
  tree:add(buffer(1,2), "Scene: " .. buffer(1,2))
  if buffer(3,1):uint() == 1 then
    tree:add(buffer(3,1), "Current Scene (" .. tostring(buffer(3,1)) .. ")")
  else
    tree:add(buffer(3,1), "Not Current Scene (" .. tostring(buffer(3,1)) .. ")")
  end
  tree:add(buffer(4,1), "Windows Number: " .. buffer(4,1))
  local n = buffer(4,1):uint()
  for i = 0, (n-1) do
      local Sub_tree = tree:add(Var,buffer(6+18*i,18),"Window" .. (i+1) .. " Info: ")
        Sub_tree:add(buffer(6+18*i,2), "Windows: " .. tostring(buffer(6+18*i,2)))
        Sub_tree:add(buffer(6+18*i+2,4), "X1: " .. tostring(buffer(6+18*i+2,4)))
        Sub_tree:add(buffer(6+18*i+6,4), "Y1: " .. tostring(buffer(6+18*i+6,4)))
        Sub_tree:add(buffer(6+18*i+10,4), "X2: " .. tostring(buffer(6+18*i+10,4)))
        Sub_tree:add(buffer(6+18*i+14,4), "Y2: " .. tostring(buffer(6+18*i+14,4)))
  end
end


function Req_Call_Scene_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Call_Scene]" .. "TVWall: " .. buffer(0,1) .. "	Scene: " .. buffer(1,2) .. "	User ID: " .. buffer(3,2))
  tree:add(buffer(0,1), "TVWall: " .. buffer(0,1))
  tree:add(buffer(1,2), "Scene: " .. buffer(1,2))
  tree:add(buffer(3,2), "User ID: " .. buffer(3,2))
end


function Ret_Call_Scene_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Call_Scene]" .. "Ack: Success")
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Call_Scene]" .. "Ack: Fail")
  end
end


function Req_Del_Scene_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Del_Scene]" .. "	TVWall: " .. buffer(0,1) .. "	Scene: " .. buffer(1,2))
  tree:add(buffer(0,1), "TVWall: " .. buffer(0,1))
  tree:add(buffer(1,2), "Scene: " .. buffer(1,2))
end


function Ret_Del_Scene_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Del_Scene]" .. "	Ack: Success")
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Del_Scene]" .. "	Ack: Fail")
  end
end


function Req_Set_CardOut_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Set_CardOut]" .. "	Box: " .. buffer(0,1) .. "	Card: " .. buffer(1,1) .. "	Port ID: " .. buffer(2,1))
  tree:add(buffer(0,1), "Box: " .. buffer(0,1))
  tree:add(buffer(1,1), "Card: " .. buffer(1,1))
  tree:add(buffer(2,1), "Port ID: " .. buffer(2,1))
  tree:add(buffer(3,1), "Resolution: " .. pi[buffer(3,1):uint()])
  tree:add(buffer(3,1), "Refresh Rate: " .. ref[buffer(4,1):uint()])
end


function Ret_Set_CardOut_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Set_CardOut]" .. "	Ack: Success")
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Set_CardOut]" .. "	Ack: Fail")
  end
end


function Req_Get_CardOut_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Get_CardOut]" .. "	Box: " .. buffer(0,1) .. "	Card: " .. buffer(1,1) .. "	Port ID: " .. buffer(2,1))
  tree:add(buffer(0,1), "Box: " .. buffer(0,1))
  tree:add(buffer(1,1), "Card: " .. buffer(1,1))
  tree:add(buffer(2,1), "Port: " .. buffer(2,1))
end


function Ret_Get_CardOut_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Get_CardOut]" .. "Ack: Success" .. "	Box: " .. buffer(1,1) .. "	Card: " .. buffer(2,1) .. "	Port ID: " .. buffer(3,1))
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Get_CardOut]" .. "Ack: Fail")
  end  
  tree:add(buffer(1,1), "Box: " .. buffer(1,1))
  tree:add(buffer(2,1), "Card: " .. buffer(2,1))
  tree:add(buffer(3,1), "Port: " .. buffer(3,1))
  tree:add(buffer(4,1), "Resolution: " .. pi[buffer(4,1):uint()])
  tree:add(buffer(5,1), "Refresh Rate: " .. ref[buffer(5,1):uint()])
end


function Req_Test_Color_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Test_Color]" .. "Test Number: " .. buffer(0,2))
  tree:add(buffer(0,2), "Test Number: " .. buffer(0,2))
  tree:add(buffer(2,5*buffer(0,2):uint()), "Test Info: " .. tostring(buffer(2,5*buffer(0,2):uint())))
  tree:add(buffer(2+5*buffer(0,2):uint(),1), "Box: " .. buffer(2+5*buffer(0,2):uint(),1))
  tree:add(buffer(2+5*buffer(0,2):uint()+1,1), "Card: " .. buffer(2+5*buffer(0,2):uint()+1,1))
  tree:add(buffer(2+5*buffer(0,2):uint()+2,1), "Port: " .. buffer(2+5*buffer(0,2):uint()+2,1))
  tree:add(buffer(2+5*buffer(0,2):uint()+3,2), "Color: " .. buffer(2+5*buffer(0,2):uint()+3,2))
end


function Ret_Test_Color_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Test_Color]" .. "	Ack: Success")
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Test_Color]" .. "	Ack: Fail")
  end
end





function Req_Get_WinCam_dissector(buffer,pinfo,tree)
  tree:add(buffer(0,1), "TVWall: " .. buffer(0,1))
  if buffer(1,2):uint() == 65535 then
    tree:add(buffer(1,2), "Get All Scene (" .. tostring(buffer(1,2)) .. ")")
	pinfo.cols.info = ("[Req_Get_WinCam]" .. "TVWall: " .. buffer(0,1) .. "	Get All Scene")
  else
    tree:add(buffer(1,2), "Get Current Scene (" .. tostring(buffer(1,2)) .. ")")
	pinfo.cols.info = ("[Req_Get_WinCam]" .. "TVWall: " .. buffer(0,1) .. "	Get Current Scene")
  end 
end


function Ret_Get_WinCam_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Get_WinCam]" .. "	TVWall: " .. buffer(1,1) .. "	Windows Number: " .. buffer(2,2))
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Get_WinCam]" .. "	Fail")
  end
  tree:add(buffer(1,1), "TVWall: " .. buffer(1,1))
  tree:add(buffer(2,2), "Windows Number: " .. buffer(2,2))
  local n = buffer(2,2):uint()
    for i = 0, (n-1) do
      local Sub_tree = tree:add(Var,buffer(4+8*i,8),"Window" .. (i+1) .. " Info: ")
        Sub_tree:add(buffer(4+8*i,2), "Scene: " .. tostring(buffer(4+8*i,2)))
        Sub_tree:add(buffer(4+8*i+2,2), "Windows: " .. tostring(buffer(4+8*i+2,2)))
        Sub_tree:add(buffer(4+8*i+4,4), "Camera ID: " .. tostring(buffer(4+8*i+4,4)))
  end
end


function Snd_Report_WinCam_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Snd_Report_WinCam]" .. "	TVWall: " .. buffer(0,1) .. "	Scene: " .. buffer(1,2) .. "	Windows Number: " .. buffer(3,2):uint())
  tree:add(buffer(0,1), "TVWall: " .. buffer(0,1))
  tree:add(buffer(1,2), "Scene: " .. buffer(1,2))
  tree:add(buffer(3,2), "Windows Number: " .. buffer(3,2):uint())
  local n = buffer(3,2):uint()
    for i = 0, (n-1) do
      local Sub_tree = tree:add(Var,buffer(5+6*i,6),"Window" .. (i+1) .. " Info: ")
        Sub_tree:add(buffer(5+6*i,2), "Windows: " .. tostring(buffer(5+6*i,2)))
        Sub_tree:add(buffer(5+6*i+2,4), "Camera ID: " .. tostring(buffer(5+6*i+2,4)))
    end
end


function Req_Set_Brightness_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Set_Brightness]" .. "	Box: " .. buffer(0,1) .. "	Card: " .. buffer(1,1) .. "	Port: " .. buffer(2,1) .. "	Brightness: " .. buffer(3,1):uint())
  tree:add(buffer(0,1), "Box: " .. buffer(0,1))
  tree:add(buffer(1,1), "Card: " .. buffer(1,1))
  tree:add(buffer(2,1), "Port: " .. buffer(2,1))
  tree:add(buffer(3,1), "Brightness: " .. buffer(3,1):uint())
end


function Ret_Set_Brightness_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Set_Brightness]" .. "	Ack: Success")
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Set_Brightness]" .. "	Ack: Fail")
  end
end


function Req_Get_Brightness_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Get_Brightness]" .. "	Box: " .. buffer(0,1) .. "	Card: " .. buffer(1,1) .. "	Card: " .. buffer(2,1))
  tree:add(buffer(0,1), "Box: " .. buffer(0,1))
  tree:add(buffer(1,1), "Card: " .. buffer(1,1))
  tree:add(buffer(2,1), "Card: " .. buffer(2,1))
end


function Ret_Get_Brightness_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Get_Brightness]" .. "	Box: " .. buffer(1,1) .. "	Card: " .. buffer(2,1) .. "	Card: " .. buffer(3,1) .. "	Brightness: " .. buffer(4,1))
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Get_Brightness]" .. "	Ack: Fail")
  end
  tree:add(buffer(1,1), "Box: " .. buffer(1,1))
  tree:add(buffer(2,1), "Card: " .. buffer(2,1))
  tree:add(buffer(3,1), "Port: " .. buffer(3,1))
  tree:add(buffer(4,1), "Brightness: " .. buffer(4,1))
end


function Req_Set_Shade_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Set_Shade]" .. "	Box: " .. buffer(0,1) .. "	Card: " .. buffer(1,1) .. "	Port: " .. buffer(2,1) .. "	Shade: " .. buffer(3,1))
  tree:add(buffer(0,1), "Box: " .. buffer(0,1))
  tree:add(buffer(1,1), "Card: " .. buffer(1,1))
  tree:add(buffer(2,1), "Port: " .. buffer(2,1))
  tree:add(buffer(3,1), "Shade: " .. buffer(3,1))
end


function Ret_Set_Shade_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Set_Shade]" .. "	Ack: Success")
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Set_Shade]" .. "	Ack: Fail")
  end
end


function Req_Get_Shade_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Req_Get_Shade]" .. "	Box: " .. buffer(1,1) .. "	Card: " .. buffer(2,1) .. "	Port: " .. buffer(3,1))
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Req_Get_Shade]" .. "Fail")
  end
  tree:add(buffer(1,1), "Box: " .. buffer(1,1))
  tree:add(buffer(2,1), "Card: " .. buffer(2,1))
  tree:add(buffer(3,1), "Port: " .. buffer(3,1))
end


function Ret_Get_Shade_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Get_Shade]" .. "	Box: " .. buffer(1,1) .. "	Card: " .. buffer(2,1) .. "	Port: " .. buffer(3,1) .. "	Shade: " .. buffer(4,1))
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Get_Shade]" .. "	Fail")
  end
  tree:add(buffer(1,1), "Box: " .. buffer(1,1))
  tree:add(buffer(2,1), "Card: " .. buffer(2,1))
  tree:add(buffer(3,1), "Port: " .. buffer(3,1))
  tree:add(buffer(4,1), "Shade: " .. buffer(4,1))
end


function Req_Set_Contrast_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Set_Contrast]" .. "	Box: " .. buffer(0,1) .. "	Card: " .. buffer(1,1) .. "	Port: " .. buffer(2,1) .. "	Contrast: " .. buffer(3,1))
  tree:add(buffer(0,1), "Box: " .. buffer(0,1))
  tree:add(buffer(1,1), "Card: " .. buffer(1,1))
  tree:add(buffer(2,1), "Port: " .. buffer(2,1))
  tree:add(buffer(3,1), "Contrast: " .. buffer(3,1))
end


function Ret_Set_Contrast_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Set_Contrast]" .. "	Ack: Success")
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Set_Contrast]" .. "	Ack: Fail")
  end
end


function Req_Get_Contrast_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Get_Contrast]" .. "	Box: " .. buffer(0,1) .. "	Card: " .. buffer(1,1) .. "	Port: " .. buffer(2,1))
  tree:add(buffer(0,1), "Box: " .. buffer(0,1))
  tree:add(buffer(1,1), "Card: " .. buffer(1,1))
  tree:add(buffer(2,1), "Port: " .. buffer(2,1))
end


function Ret_Get_Contrast_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Get_Contrast]" .. "	Box: " .. buffer(1,1) .. "	Card: " .. buffer(2,1) .. "	Port: " .. buffer(3,1) .. "	Contrast: " .. buffer(4,1))
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Get_Contrast]" .. "	Ack: Fail")
  end
  tree:add(buffer(1,1), "Box: " .. buffer(1,1))
  tree:add(buffer(2,1), "Card: " .. buffer(2,1))
  tree:add(buffer(3,1), "Port: " .. buffer(3,1))
  tree:add(buffer(4,1), "Contrast: " .. buffer(4,1))
end


function Req_Set_Sturation_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Set_Sturation]" .. "	Box: " .. buffer(0,1) .. "	Card: " .. buffer(1,1) .. "	Port: " .. buffer(2,1) .. "	Sturation: " .. buffer(3,1))
  tree:add(buffer(0,1), "Box: " .. buffer(0,1))
  tree:add(buffer(1,1), "Card: " .. buffer(1,1))
  tree:add(buffer(2,1), "Port: " .. buffer(2,1))
  tree:add(buffer(3,1), "Sturation: " .. buffer(3,1))
end


function Ret_Set_Sturation_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Set_Sturation]" .. "	Ack: Success ")
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Set_Sturation]" .. "	Ack: Fail")
  end
end


function Req_Get_Sturation_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Get_Sturation]" .. "	Box: " .. buffer(0,1) .. "	Card: " .. buffer(1,1) .. "	Port: " .. buffer(2,1))
  tree:add(buffer(0,1), "Box: " .. buffer(0,1))
  tree:add(buffer(1,1), "Card: " .. buffer(1,1))
  tree:add(buffer(2,1), "Port: " .. buffer(2,1))
end


function Ret_Get_Sturation_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Get_Sturation]" .. "	Box: " .. buffer(1,1) .. "	Card: " .. buffer(2,1) .. "	Port: " .. buffer(3,1) .. "	Sturation: " .. buffer(4,1))
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Get_Sturation]" .. "	Ack: Fail")
  end
  tree:add(buffer(1,1), "Box: " .. buffer(1,1))
  tree:add(buffer(2,1), "Card: " .. buffer(2,1))
  tree:add(buffer(3,1), "Port: " .. buffer(3,1))
  tree:add(buffer(4,1), "Sturation: " .. buffer(4,1))
end


function Req_Set_MapEnable_dissector(buffer,pinfo,tree)
  local map = {
  [1] = "Disable",
  [2] = "Enable",}
  pinfo.cols.info = ("[Ret_Get_Sturation]" .. "	Box: " .. buffer(0,1) .. "	Card: " .. buffer(1,1) .. "	Port: " .. buffer(2,1) .. "	MapEnable: " .. buffer(3,1))
  tree:add(buffer(0,1), "Box: " .. buffer(0,1))
  tree:add(buffer(1,1), "Card: " .. buffer(1,1))
  tree:add(buffer(2,1), "Port: " .. buffer(2,1))
  tree:add(buffer(3,1), "MapEnable: " .. map[buffer(3,1)])
end


function Ret_Set_MapEnable_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Set_MapEnable]" .. "	Ack: Success")
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Set_MapEnable]" .. "	Ack: Fail")
  end
end


function Req_Set_Transparence_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Set_Transparence]" .. "	TVWall: " .. buffer(0,1) .. "	Scene: " .. buffer(1,2) .. "	Windows: " .. buffer(3,2) .. "	Transparence: " .. buffer(5,1))
  tree:add(buffer(0,1), "TVWall: " .. buffer(0,1))
  tree:add(buffer(1,2), "Scene: " .. buffer(1,2))
  tree:add(buffer(3,2), "Windows: " .. buffer(3,2))
  tree:add(buffer(5,1), "Transparence: " .. buffer(5,1):uint())
end


function Ret_Set_Transparence_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Set_Transparence]" .. "	Ack: Success")
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Set_Transparence]" .. "	Ack: Fail")
  end
end


function Req_Get_Transparence_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Get_Transparence]" .. "	TVWall: " .. buffer(0,1) .. "	Scene: " .. buffer(1,2) .. "	Windows: " .. buffer(3,2))
  tree:add(buffer(0,1), "TVWall: " .. buffer(0,1))
  tree:add(buffer(1,2), "Scene: " .. buffer(1,2))
  tree:add(buffer(3,2), "Windows: " .. buffer(3,2))
end


function Ret_Get_Transparence_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Get_Transparence]" .. "	TVWall: " .. buffer(1,1) .. "	Scene: " .. buffer(2,2) .. "	Windows: " .. buffer(4,2) .. "	Transparence: " .. buffer(6,1):uint())
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
	pinfo.cols.info = ("[Ret_Get_Transparence]" .. "	Ack: Fail")
  end
  tree:add(buffer(1,1), "TVWall: " .. buffer(1,1))
  tree:add(buffer(2,2), "Scene: " .. buffer(2,2))
  tree:add(buffer(4,2), "Windows: " .. buffer(4,2))
  tree:add(buffer(6,1), "Transparence: " .. buffer(6,1):uint()) 
end


function Req_Set_SwiEffect_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Get_Transparence]" .. "	TVWall: " .. buffer(0,1) .. "	Scene: " .. buffer(1,2) .. "	Windows: " .. buffer(3,2) .. "	SwiEffect: " .. buffer(5,1):uint())
  tree:add(buffer(0,1), "TVWall: " .. buffer(0,1))
  tree:add(buffer(1,2), "Scene: " .. buffer(1,2))
  tree:add(buffer(3,2), "Windows: " .. buffer(3,2))
  tree:add(buffer(5,1), "SwiEffect: " .. buffer(5,1):uint())
end


function Ret_Set_SwiEffect_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
	pinfo.cols.info = ("[Ret_Set_SwiEffect]" .. "	Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
	pinfo.cols.info = ("[Ret_Set_SwiEffect]" .. "	Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Get_SwiEffect_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Get_SwiEffect]" .. "	TVWall: " .. buffer(0,1) .. "	Scene: " .. buffer(1,2) .. "	Windows: " .. buffer(3,2) .. "	SwiEffect: " .. buffer(5,1):uint())
  tree:add(buffer(0,1), "TVWall: " .. buffer(0,1))
  tree:add(buffer(1,2), "Scene: " .. buffer(1,2))
  tree:add(buffer(3,2), "Windows: " .. buffer(3,2))
  tree:add(buffer(5,1), "SwiEffect: " .. buffer(5,1):uint())
end


function Ret_Get_SwiEffect_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
	pinfo.cols.info = ("[Ret_Get_SwiEffect]" .. "	Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
	pinfo.cols.info = ("[Ret_Get_SwiEffect]" .. "	Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Set_SwiTime_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Set_SwiTime]" .. "	TVWall: " .. buffer(0,1) .. "	Scene: " .. buffer(1,2) .. "	Windows: " .. buffer(3,2) .. "	SwiTime: " .. buffer(5,1):uint())
  tree:add(buffer(0,1), "TVWall: " .. buffer(0,1))
  tree:add(buffer(1,2), "Scene: " .. buffer(1,2))
  tree:add(buffer(3,2), "Windows: " .. buffer(3,2))
  tree:add(buffer(5,1), "SwiTime: " .. buffer(5,1):uint())
end


function Ret_Set_SwiTime_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
	pinfo.cols.info = ("[Ret_Set_SwiTime]" .. "	Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
	pinfo.cols.info = ("[Ret_Set_SwiTime]" .. "	Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Get_SwiTime_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Get_SwiTime]" .. "TVWall: " .. buffer(0,1) .. "	Scene: " .. buffer(1,2) .. "	Windows: " .. buffer(3,2))
  tree:add(buffer(0,1), "TVWall: " .. buffer(0,1))
  tree:add(buffer(1,2), "Scene: " .. buffer(1,2))
  tree:add(buffer(3,2), "Windows: " .. buffer(3,2))
end


function Ret_Get_SwiTime_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
	pinfo.cols.info = ("[Ret_Get_SwiTime]" .. "TVWall: " .. buffer(1,1) .. "	Scene: " .. buffer(2,2) .. "	Windows: " .. buffer(4,2) .. "	SwiTime: " .. buffer(6,1):uint())
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
  tree:add(buffer(1,1), "TVWall: " .. buffer(1,1))
  tree:add(buffer(2,2), "Scene: " .. buffer(2,2))
  tree:add(buffer(4,2), "Windows: " .. buffer(4,2))
  tree:add(buffer(6,1), "SwiTime: " .. buffer(6,1):uint()) 
end


function Req_Set_FreezingTime_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Set_FreezingTime]" .. "TVWall: " .. buffer(0,1) .. "	Scene: " .. buffer(1,2) .. "	Windows: " .. buffer(3,2) .. "	FreezingTime: " .. buffer(5,2):uint())
  tree:add(buffer(0,1), "TVWall: " .. buffer(0,1))
  tree:add(buffer(1,2), "Scene: " .. buffer(1,2))
  tree:add(buffer(3,2), "Windows: " .. buffer(3,2))
  tree:add(buffer(5,2), "FreezingTime: " .. buffer(5,2):uint())
end


function Ret_Set_FreezingTime_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
	pinfo.cols.info = ("[Ret_Set_FreezingTime]" .. "	Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
	pinfo.cols.info = ("[Ret_Set_FreezingTime]" .. "	Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Get_FreezingTime_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Get_FreezingTime]" .. "	TVWall: " .. buffer(0,1) .. "	Scene: " .. buffer(1,2) .. "	Windows: " .. buffer(3,2))
  tree:add(buffer(0,1), "TVWall: " .. buffer(0,1))
  tree:add(buffer(1,2), "Scene: " .. buffer(1,2))
  tree:add(buffer(3,2), "Windows: " .. buffer(3,2))
end


function Ret_Get_FreezingTime_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
	pinfo.cols.info = ("[Ret_Get_FreezingTime]" .. "	TVWall: " .. buffer(1,1) .. "	Scene: " .. buffer(2,2) .. "	Windows: " .. buffer(4,2) .. "	FreezingTime: " .. buffer(6,2):uint())
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
  tree:add(buffer(1,1), "TVWall: " .. buffer(1,1))
  tree:add(buffer(2,2), "Scene: " .. buffer(2,2))
  tree:add(buffer(4,2), "Windows: " .. buffer(4,2))
  tree:add(buffer(6,2), "FreezingTime: " .. buffer(6,2):uint()) 
end


function Req_Set_Reset_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Set_Reset]")
  return ture
end


function Ret_Set_Reset_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
	pinfo.cols.info = ("[Ret_Set_Reset]" .. "	Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
	pinfo.cols.info = ("[Ret_Set_Reset]" .. "	Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Get_CardPortInfo_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
	pinfo.cols.info = ("[Req_Get_CardPortInfo]" .. "	Input")
    tree:add(buffer(0,1), "Input (" .. tostring(buffer(0,1)) .. ")")
  else
	pinfo.cols.info = ("[Req_Get_CardPortInfo]" .. "	Output")
    tree:add(buffer(0,1), "Output (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Ret_Get_CardPortInfo_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
	pinfo.cols.info = ("[Ret_Get_CardPortInfo]" .. "	Port Info: " .. buffer(1,2))
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
	pinfo.cols.info = ("[Ret_Get_CardPortInfo]" .. "	Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
  tree:add(buffer(1,2), "Port Info: " .. buffer(1,2))
    local n = buffer(1,2):uint()
    for i = 0, (n-1) do
      local Sub_tree = tree:add(Var,buffer(3+4*i,4),"Port" .. (i+1) .. " Info: ")
        Sub_tree:add(buffer(3+4*i,1), "Box: " .. buffer(3+4*i,1))
        Sub_tree:add(buffer(3+4*i+1,1), "Card: " .. buffer(3+4*i+1,1))
        Sub_tree:add(buffer(3+4*i+2,1), "Port: " .. buffer(3+4*i+2,1))
        Sub_tree:add(buffer(3+4*i+3,1), "Channel: " .. buffer(3+4*i+3,1))
    end
end


function Req_Get_CardPortInfo_V2_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
	pinfo.cols.info = ("[Req_Get_CardPortInfo_V2]" .. "	Input")
    tree:add(buffer(0,1), "Input (" .. tostring(buffer(0,1)) .. ")")
  else
	pinfo.cols.info = ("[Req_Get_CardPortInfo_V2]" .. "	Output")
    tree:add(buffer(0,1), "Output (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Ret_Get_CardPortInfo_V2_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
	pinfo.cols.info = ("[Ret_Get_CardPortInfo_V2]" .. "	Port Info: " .. buffer(1,2))
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
	pinfo.cols.info = ("[Ret_Get_CardPortInfo_V2]" .. "	Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
  tree:add(buffer(1,2), "Port Info: " .. buffer(1,2))
    local n = buffer(1,2):uint()
    for i = 0, (n-1) do
      local Sub_tree = tree:add(Var,buffer(3+5*i,5),"Port" .. (i+1) .. " Info: ")
        Sub_tree:add(buffer(3+5*i,1), "Box: " .. buffer(3+5*i,1))
        Sub_tree:add(buffer(3+5*i+1,1), "Card: " .. buffer(3+5*i+1,1))
        Sub_tree:add(buffer(3+5*i+2,1), "Port: " .. buffer(3+5*i+2,1))
        Sub_tree:add(buffer(3+5*i+3,1), "Channel: " .. buffer(3+5*i+3,1))
    end
end


function Req_Set_MonChannelInfo_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Set_MonChannelInfo]" .. "	Moniter Number: " .. buffer(0,2))
  tree:add(buffer(0,2), "Moniter Number: " .. buffer(0,2))
  local n = buffer(0,2):uint()
      for i = 0, (n-1) do
      local Sub_tree = tree:add(Var,buffer(2+6*i,6),"Moniter" .. (i+1) .. " Info: ")
        Sub_tree:add(buffer(2+6*i,2), "Moniter ID: " .. tostring(buffer(2+6*i,2)))
        Sub_tree:add(buffer(2+6*i+2,1), "Box: " .. buffer(2+6*i+2,1))
        Sub_tree:add(buffer(2+6*i+3,1), "Solt: " .. buffer(2+6*i+3,1))
        Sub_tree:add(buffer(2+6*i+4,1), "Port: " .. buffer(2+6*i+4,1))
        Sub_tree:add(buffer(2+6*i+5,1), "Channel: " .. buffer(2+6*i+5,1))
      end
end


function Ret_Set_MonChannelInfo_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
	pinfo.cols.info = ("[Ret_Set_MonChannelInfo]" .. "	Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
	pinfo.cols.info = ("[Ret_Set_MonChannelInfo]" .. "	Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Del_MonChannelInfo_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Del_MonChannelInfo]" .. "	Monitor Number: " .. buffer(0,2):uint())
  tree:add(buffer(0,2), "Monitor Number: " .. buffer(0,2):uint())
  tree:add(buffer(2,2*(buffer(0,2):uint())), "Monitor ID: " .. tostring(buffer(2,2*(buffer(0,2):uint()))))
end


function Ret_Del_MonChannelInfo_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
	pinfo.cols.info = ("[Ret_Del_MonChannelInfo]" .. "	Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
	pinfo.cols.info = ("[Ret_Del_MonChannelInfo]" .. "	Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Get_MonChannelInfo_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Get_MonChannelInfo]")
  return true
end


function Ret_Get_MonChannelInfo_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
	pinfo.cols.info = ("[Ret_Get_MonChannelInfo]" .. "	Monitor NUmber Total: " .. buffer(1,2))
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
	pinfo.cols.info = ("[Ret_Get_MonChannelInfo]" .. "	Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
  tree:add(buffer(1,2), "Monitor NUmber Total: " .. buffer(1,2))
  local n = buffer(1,2):uint()
      for i = 0, (n-1) do
      local Sub_tree = tree:add(Var,buffer(3+6*i,6),"Moniter" .. (i+1) .. " Info: ")
        Sub_tree:add(buffer(3+6*i,2), "Moniter ID: " .. tostring(buffer(3+6*i,2)))
        Sub_tree:add(buffer(3+6*i+2,1), "Box: " .. buffer(3+6*i+2,1))
        Sub_tree:add(buffer(3+6*i+3,1), "Solt: " .. buffer(3+6*i+3,1))
        Sub_tree:add(buffer(3+6*i+4,1), "Port: " .. buffer(3+6*i+4,1))
        Sub_tree:add(buffer(3+6*i+5,1), "Channel: " .. buffer(3+6*i+5,1))
      end
end
	

function Req_Set_CamChannelInfo_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Set_CamChannelInfo]" .. "	Camera Number Total:" .. buffer(0,2))
  tree:add(buffer(0,2), "Camera Number Total:" .. buffer(0,2))
  local n = buffer(0,2):uint()
      for i = 0, (n-1) do
      local Sub_tree = tree:add(Var,buffer(2+10*i,10),"Camera" .. (i+1) .. " Info: ")
        Sub_tree:add(buffer(2+10*i,2), "Camera ID: " .. tostring(buffer(2+10*i,2)))
        Sub_tree:add(buffer(2+10*i+2,1), "Box: " .. buffer(2+10*i+2,1))
        Sub_tree:add(buffer(2+10*i+3,1), "Solt: " .. buffer(2+10*i+3,1))
        Sub_tree:add(buffer(2+10*i+4,1), "Port: " .. buffer(2+10*i+4,1))
        Sub_tree:add(buffer(2+10*i+5,1), "Channel: " .. buffer(2+10*i+5,1))
        Sub_tree:add(buffer(2+10*i+6,2), "Control ID: " .. buffer(2+10*i+6,2))
        Sub_tree:add(buffer(2+10*i+8,1), "Control Protocol: " .. pro[buffer(2+10*i+8,1)])
        Sub_tree:add(buffer(2+10*i+9,1), "Control bps: " .. bps[buffer(2+10*i+9,1)])
      end
end


function Ret_Set_CamChannelInfo_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
	pinfo.cols.info = ("[Ret_Set_CamChannelInfo]" .. "	Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
	pinfo.cols.info = ("[Ret_Set_CamChannelInfo]" .. "	Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Get_CamChannelInfo_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Get_CamChannelInfo]" .. "	Ack: Fail")
  return true
end


function Ret_Get_CamChannelInfo_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
	pinfo.cols.info = ("[Ret_Get_CamChannelInfo]" .. "	Camera Number Total:" .. buffer(1,2))
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
	pinfo.cols.info = ("[Ret_Get_CamChannelInfo]" .. "	Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end    
  tree:add(buffer(1,2), "Camera Number Total:" .. buffer(1,2))
  local n = buffer(1,2):uint()
      for i = 0, (n-1) do
      local Sub_tree = tree:add(Var,buffer(3+10*i,10),"Camera" .. (i+1) .. " Info: ")
        Sub_tree:add(buffer(3+10*i,2), "Camera ID: " .. tostring(buffer(3+10*i,2)))
        Sub_tree:add(buffer(3+10*i+2,1), "Box: " .. buffer(3+10*i+2,1))
        Sub_tree:add(buffer(3+10*i+3,1), "Solt: " .. buffer(3+10*i+3,1))
        Sub_tree:add(buffer(3+10*i+4,1), "Port: " .. buffer(3+10*i+4,1))
        Sub_tree:add(buffer(3+10*i+5,1), "Channel: " .. buffer(3+10*i+5,1))
        Sub_tree:add(buffer(3+10*i+6,2), "Control ID: " .. buffer(3+10*i+6,2))
        Sub_tree:add(buffer(3+10*i+8,1), "Control Protocol: " .. pro[buffer(3+10*i+8,1)])
        Sub_tree:add(buffer(3+10*i+9,1), "Control bps: " .. bps[buffer(3+10*i+9,1)])
      end
end


function Req_Del_CamChannelInfo_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Del_CamChannelInfo]" .. "	Camera Number Total:" .. buffer(0,2))
  tree:add(buffer(0,2), "Camera Number Total:" .. buffer(0,2))
  local n = buffer(0,2):uint()
      for i = 0, (n-1) do
      tree:add(Var,buffer(2+2*i,2),"Camera" .. (i+1) .. " ID: " .. tostring(buffer(2+2*i,2)))
      end
end


function Ret_Del_CamChannelInfo_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
	pinfo.cols.info = ("[Ret_Del_CamChannelInfo]" .. "	Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
	pinfo.cols.info = ("[Ret_Del_CamChannelInfo]" .. "	Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Set_WinTB_dissector(buffer,pinfo,tree)
  local tb = {
    [0] = "Top",
    [1] = "Down",}
  pinfo.cols.info = ("[Req_Set_WinTB]" .. "	TVWall: " .. buffer(0,1) .. "	Scene: " .. buffer(1,2) .. "	Windows: " .. buffer(3,2) .. "	WinTB: " .. tb[buffer(5,1)])
  tree:add(buffer(0,1), "TVWall: " .. buffer(0,1))
  tree:add(buffer(1,2), "Scene: " .. buffer(1,2))
  tree:add(buffer(3,2), "Windows: " .. buffer(3,2))
  tree:add(buffer(5,1), "WinTB: " .. tb[buffer(5,1)])
end


function Ret_Set_WinTB_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
	pinfo.cols.info = ("[Ret_Set_WinTB]" .. "	Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
	pinfo.cols.info = ("[Ret_Set_WinTB]" .. "	Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Set_Zoom_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Set_Zoom]" .. "	TVWall: " .. buffer(0,1) .. "	Scene: " .. buffer(1,2) .. "	Windows: " .. buffer(3,2))
  tree:add(buffer(0,1), "TVWall: " .. buffer(0,1))
  tree:add(buffer(1,2), "Scene: " .. buffer(1,2))
  tree:add(buffer(3,2), "Windows: " .. buffer(3,2))
  tree:add(buffer(5,4), "Windows Start Y:" .. buffer(5,4))
  tree:add(buffer(9,4), "Windows Start X:" .. buffer(9,4))
  tree:add(buffer(13,4), "Windows End Y:" .. buffer(13,4))
  tree:add(buffer(17,4), "Windows End X:" .. buffer(17,4))
end


function Ret_Set_Zoom_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
	pinfo.cols.info = ("[Ret_Set_Zoom]" .. "	Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
	pinfo.cols.info = ("[Ret_Set_Zoom]" .. "	Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Finish_Zoom_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Finish_Zoom]" .. "	TVWall: " .. buffer(0,1) .. "	Scene: " .. buffer(1,2) .. "	Windows: " .. buffer(3,2))
  tree:add(buffer(0,1), "TVWall: " .. buffer(0,1))
  tree:add(buffer(1,2), "Scene: " .. buffer(1,2))
  tree:add(buffer(3,2), "Windows: " .. buffer(3,2))
end


function Ret_Finish_Zoom_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
	pinfo.cols.info = ("[Ret_Finish_Zoom]" .. "	Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
	pinfo.cols.info = ("[Ret_Finish_Zoom]" .. "	Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Set_Scene_Name_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Set_Scene_Name]" .. "	Scene Name Info Number Total: " .. buffer(0,2) .. "	Scene Name Info: " .. buffer(2,1) .. "	TVWall: " .. buffer(3,1))
  tree:add(buffer(0,2), "Scene Name Info Number Total: " .. buffer(0,2))
  tree:add(buffer(2,1), "Scene Name Info: " .. buffer(2,1))
  tree:add(buffer(3,1), "TVWall: " .. buffer(3,1))
  tree:add(buffer(4,2), "Scene: " .. buffer(4,2))
  tree:add(buffer(6,128), "Scene Name:" .. tostring(buffer(6,128)))
end


function Ret_Set_Scene_Name_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
	pinfo.cols.info = ("[Ret_Set_Scene]" .. "	Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
	pinfo.cols.info = ("[Ret_Set_Scene]" .. "	Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Get_Scene_Name_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Get_Scene_Name]" .. "	TVWall: " .. buffer(0,1) .. "	Scene: " .. buffer(1,2))
  tree:add(buffer(0,1), "TVWall: " .. buffer(0,1))
  tree:add(buffer(1,2), "Scene: " .. buffer(1,2))
end


function Ret_Get_Scene_Name_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
	pinfo.cols.info = ("[Ret_Get_Scene_Name]" .. "	Scene Name Info Number Total: " .. buffer(1,2) .. "	Scene Name Info: " .. buffer(3,1) .. "	TVWall: " .. buffer(4,1) .. "	Scene: " .. buffer(5,2))
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
  tree:add(buffer(1,2), "Scene Name Info Number Total: " .. buffer(1,2))
  tree:add(buffer(3,1), "Scene Name Info: " .. buffer(3,1))
  tree:add(buffer(4,1), "TVWall: " .. buffer(4,1))
  tree:add(buffer(5,2), "Scene: " .. buffer(5,2))
  tree:add(buffer(7,128), "Scene Name:" .. tostring(buffer(7,128)))
end


function Req_Screen_Salvo_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Ret_Get_Scene_Name]" .. "	TVWall: " .. buffer(0,1) .. "	Salvo ID: " .. buffer(1,2) .. "	Mark: " .. buffer(3,1))
  tree:add(buffer(0,1), "TVWall: " .. buffer(0,1))
  tree:add(buffer(1,2), "Salvo ID: " .. buffer(1,2))
  tree:add(buffer(3,1), "Mark: " .. buffer(3,1))
end


function Ret_Screen_Salvo_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
	pinfo.cols.info = ("[Ret_Screen_Salvo]" .. "	Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
	pinfo.cols.info = ("[Ret_Screen_Salvo]" .. "	Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Dome_Ctrl_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Dome_Ctrl]" .. "	User ID: " .. buffer(1,2) .. "	Scene: " .. tostring(buffer(3,3)) .. "	Monitor ID: " .. tostring(buffer(6,3)) .. "	Camera ID: " .. tostring(buffer(9,4)))
  tree:add(buffer(0,1), "Start: " .. buffer(0,1))
  tree:add(buffer(1,2), "User ID: " .. buffer(1,2))
  tree:add(buffer(3,3), "Scene: " .. tostring(buffer(3,3)))
  tree:add(buffer(6,3), "Monitor ID: " .. tostring(buffer(6,3)))
  tree:add(buffer(9,4), "Camera ID: " .. tostring(buffer(9,4)))
  tree:add(buffer(13,3), "Command ID: " .. tostring(buffer(13,3)))
  tree:add(buffer(16,3), "Date1: " .. tostring(buffer(16,3)))
  tree:add(buffer(19,3), "Date2: " .. tostring(buffer(19,3)))
  tree:add(buffer(22,1), "End: " .. tostring(buffer(22,1)))
end


function Ret_Dome_Ctrl_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
	pinfo.cols.info = ("[Ret_Dome_Ctrl]" .. "	Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
	pinfo.cols.info = ("[Ret_Dome_Ctrl]" .. "	Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Set_Zero_Delay_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Set_Zero_Delay]" .. "	Box: " .. buffer(0,1) .. "	Card: " .. buffer(1,1) .. "	Port: " .. buffer(2,1) .. "	Mark: " .. buffer(2,1))
  tree:add(buffer(0,1), "Box: " .. buffer(0,1))
  tree:add(buffer(1,1), "Card: " .. buffer(1,1))
  tree:add(buffer(2,1), "Port: " .. buffer(2,1))
  tree:add(buffer(2,1), "Mark: " .. buffer(2,1))
end


function Ret_Set_Zero_Delay_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
	pinfo.cols.info = ("[Ret_Set_Zero]" .. "	Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
	pinfo.cols.info = ("[Ret_Set_Zero]" .. "	Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Get_Zero_Delay_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Get_Zero_Delay]" .. "	Box: " .. buffer(0,1) .. "	Card: " .. buffer(1,1) .. "	Port: " .. buffer(2,1))
  tree:add(buffer(0,1), "Box: " .. buffer(0,1))
  tree:add(buffer(1,1), "Card: " .. buffer(1,1))
  tree:add(buffer(2,1), "Port: " .. buffer(2,1))
end


function Ret_Get_Zero_Delay_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
	pinfo.cols.info = ("[Ret_Get_Zero_Delay]" .. "	Box: " .. buffer(1,1) .. "	Card: " .. buffer(2,1) .. "	Port: " .. buffer(3,1) .. "	Mark: " .. buffer(4,1))
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
	pinfo.cols.info = ("[Ret_Get_Zero_Delay]" .. "	Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
  tree:add(buffer(1,1), "Box: " .. buffer(1,1))
  tree:add(buffer(2,1), "Card: " .. buffer(2,1))
  tree:add(buffer(3,1), "Port: " .. buffer(3,1))
  tree:add(buffer(4,1), "Mark: " .. buffer(4,1))
end


function Req_Set_WinAndSwi_dissector(buffer,pinfo,tree)
  mark = {
    [0] = "Break",
    [1] = "Set",}
  pinfo.cols.info = ("[Req_Set_WinAndSwi]" .. "	TVWall: " .. buffer(0,1) .. "	Scene: " .. buffer(1,2) .. "	Mark: " .. mark[buffer(19,1)])
  tree:add(buffer(0,1), "TVWall: " .. buffer(0,1))
  tree:add(buffer(1,2), "Scene: " .. buffer(1,2))
  tree:add(buffer(3,4), "Windows Start Y: " .. buffer(3,4))
  tree:add(buffer(7,4), "Windows Start X: " .. buffer(7,4))
  tree:add(buffer(11,4), "Windows End Y: " .. buffer(11,4))
  tree:add(buffer(15,4), "Windows End X: " .. buffer(15,4))
  tree:add(buffer(19,1), "Mark: " .. mark[buffer(19,1)])
  tree:add(buffer(20,1), "Input Box: " .. buffer(20,1))
  tree:add(buffer(21,4), "Input Card: " .. buffer(21,4))
  tree:add(buffer(25,1), "Input Solt: " .. buffer(25,1))
  tree:add(buffer(26,1), "Input Port: " .. buffer(26,1))
  tree:add(buffer(27,1), "Input Channel: " .. buffer(27,1))
end


function Ret_Set_WinAndSwi_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
	pinfo.cols.info = ("[Ret_Set_WinAndSwi]" .. "	TVWall: " .. buffer(1,1) .. "	Scene: " .. buffer(2,2) .. "	Windows: " .. buffer(4,2))
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
	pinfo.cols.info = ("[Ret_Set_WinAndSwi]" .. "	Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
  tree:add(buffer(1,1), "TVWall: " .. buffer(1,1))
  tree:add(buffer(2,2), "Scene: " .. buffer(2,2))
  tree:add(buffer(4,2), "Windows: " .. buffer(4,2))
end


function Req_Add_Salvo_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Add_Salvo]" .. "	Message Total: " .. buffer(0,2) .. "	TVWall: " .. tostring(buffer(2,1)) .. "	Scene: " .. tostring(buffer(3,2)))
  tree:add(buffer(0,2), "Message Total: " .. buffer(0,2))
  tree:add(buffer(2,1), "TVWall: " .. tostring(buffer(2,1)))
  tree:add(buffer(3,2), "Scene: " .. tostring(buffer(3,2)))
  tree:add(buffer(5,1), "Salvo: " .. tostring(buffer(5,1)))
  tree:add(buffer(6,1), "Step: " .. tostring(buffer(6,1)))
  tree:add(buffer(7,2), "Windows: " .. tostring(buffer(7,2)))
  tree:add(buffer(9,4), "Camera: " .. tostring(buffer(9,4)))
  tree:add(buffer(13,2), "Hold Time: " .. tostring(buffer(13,2)))
  tree:add(buffer(15,1), "Set: " .. tostring(buffer(15,1)))
  tree:add(buffer(16,1), "Wip: " .. tostring(buffer(16,1)))
end


function Ret_Add_Salvo_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
	pinfo.cols.info = ("[Ret_Add_Salvo]" .. "	Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
	pinfo.cols.info = ("[Ret_Add_Salvo]" .. "	Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Del_Salvo_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Del_Salvo]" .. "	TVWall: " .. tostring(buffer(0,1)) .. "	Scene: " .. tostring(buffer(1,2)) .. "	Salvo: " .. tostring(buffer(3,1)) .. "	Step: " .. tostring(buffer(4,1)))
  tree:add(buffer(0,1), "TVWall: " .. tostring(buffer(0,1)))
  tree:add(buffer(1,2), "Scene: " .. tostring(buffer(1,2)))
  tree:add(buffer(3,1), "Salvo: " .. tostring(buffer(3,1)))
  tree:add(buffer(4,1), "Step: " .. tostring(buffer(4,1)))
end


function Ret_Del_Salvo_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
	pinfo.cols.info = ("[Ret_Del_Salvo]" .. "	Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
	pinfo.cols.info = ("[Ret_Del_Salvo]" .. "	Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Get_Salvo_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Get_Salvo]" .. "	TVWall: " .. tostring(buffer(0,1)) .. "	Scene: " .. tostring(buffer(1,2)) .. "	Salvo: " .. tostring(buffer(3,1)) .. "	Step: " .. tostring(buffer(4,1)))
  tree:add(buffer(0,1), "TVWall: " .. tostring(buffer(0,1)))
  tree:add(buffer(1,2), "Scene: " .. tostring(buffer(1,2)))
  tree:add(buffer(3,1), "Salvo: " .. tostring(buffer(3,1)))
  tree:add(buffer(4,1), "Step: " .. tostring(buffer(4,1)))
end


function Ret_Get_Salvo_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
	pinfo.cols.info = ("[Ret_Get_Salvo]" .. "	Message Total: " .. buffer(1+0,2) .. "	TVWall: " .. tostring(buffer(1+2,1)) .. "	Scene: " .. tostring(buffer(1+3,2)))
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
	pinfo.cols.info = ("[Ret_Get_Salvo]" .. "	Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
  tree:add(buffer(1+0,2), "Message Total: " .. buffer(1+0,2))
  tree:add(buffer(1+2,1), "TVWall: " .. tostring(buffer(1+2,1)))
  tree:add(buffer(1+3,2), "Scene: " .. tostring(buffer(1+3,2)))
  tree:add(buffer(1+5,1), "Salvo: " .. tostring(buffer(1+5,1)))
  tree:add(buffer(1+6,1), "Step: " .. tostring(buffer(1+6,1)))
  tree:add(buffer(1+7,2), "Windows: " .. tostring(buffer(1+7,2)))
  tree:add(buffer(1+9,4), "Camera: " .. tostring(buffer(1+9,4)))
  tree:add(buffer(1+13,2), "Hold Time: " .. tostring(buffer(1+13,2)))
  tree:add(buffer(1+15,1), "Set: " .. tostring(buffer(1+15,1)))
  tree:add(buffer(1+16,1), "Wip: " .. tostring(buffer(1+16,1)))
end


function Req_Add_Tour_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Add_Tour]" .. "	Message Total: " .. buffer(0,2) .. "	TVWall: " .. tostring(buffer(2,1)) .. "	Scene: " .. tostring(buffer(3,2)) .. "	Scene: " .. tostring(buffer(3,2)))
  tree:add(buffer(0,2), "Message Total: " .. buffer(0,2))
  tree:add(buffer(2,1), "TVWall: " .. tostring(buffer(2,1)))
  tree:add(buffer(3,2), "Scene: " .. tostring(buffer(3,2)))
  tree:add(buffer(5,1), "Salvo: " .. tostring(buffer(5,1)))
  tree:add(buffer(6,1), "Step: " .. tostring(buffer(6,1)))
  tree:add(buffer(7,4), "Camera: " .. tostring(buffer(7,4)))
  tree:add(buffer(11,2), "Hold Time: " .. tostring(buffer(11,2)))
  tree:add(buffer(13,1), "Set: " .. tostring(buffer(13,1)))
  tree:add(buffer(14,1), "Wip: " .. tostring(buffer(14,1)))
end


function Ret_Add_Tour_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
	pinfo.cols.info = ("[Ret_Add_Tour]" .. "	Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
	pinfo.cols.info = ("[Ret_Add_Tour]" .. "	Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Del_Tour_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Del_Tour]" .. "	TVWall: " .. tostring(buffer(0,1)) .. "	Scene: " .. tostring(buffer(1,2)) .. "	Salvo: " .. tostring(buffer(3,1)) .. "Step: " .. tostring(buffer(4,1)))
  tree:add(buffer(0,1), "TVWall: " .. tostring(buffer(0,1)))
  tree:add(buffer(1,2), "Scene: " .. tostring(buffer(1,2)))
  tree:add(buffer(3,1), "Salvo: " .. tostring(buffer(3,1)))
  tree:add(buffer(4,1), "Step: " .. tostring(buffer(4,1)))
end


function Ret_Del_Tour_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
	pinfo.cols.info = ("[Ret_Del_Tour]" .. "	Ack: Success")
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
	pinfo.cols.info = ("[Ret_Del_Tour]" .. "	Ack: Fail")
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
end


function Req_Get_Tour_dissector(buffer,pinfo,tree)
  pinfo.cols.info = ("[Req_Get_Tour]" .. "	TVWall: " .. tostring(buffer(0,1)) .. "	Scene: " .. tostring(buffer(1,2)) .. "	Salvo: " .. tostring(buffer(3,1)) .. "	Step: " .. tostring(buffer(4,1)))
  tree:add(buffer(0,1), "TVWall: " .. tostring(buffer(0,1)))
  tree:add(buffer(1,2), "Scene: " .. tostring(buffer(1,2)))
  tree:add(buffer(3,1), "Salvo: " .. tostring(buffer(3,1)))
  tree:add(buffer(4,1), "Step: " .. tostring(buffer(4,1)))
end


function Ret_Get_Tour_dissector(buffer,pinfo,tree)
  if buffer(0,1):uint() == 0 then
	pinfo.cols.info = ("[Ret_Get_Tour]" .. "	Message Total: " .. buffer(1+0,2) .. "	TVWall: " .. tostring(buffer(1+2,1)) .. "	Scene: " .. tostring(buffer(1+3,2)))
    tree:add(buffer(0,1), "Ack: Success (" .. tostring(buffer(0,1)) .. ")")
  else
    tree:add(buffer(0,1), "Ack: Fail (" .. tostring(buffer(0,1)) .. ")")
  end
  tree:add(buffer(1+0,2), "Message Total: " .. buffer(1+0,2))
  tree:add(buffer(1+2,1), "TVWall: " .. tostring(buffer(1+2,1)))
  tree:add(buffer(1+3,2), "Scene: " .. tostring(buffer(1+3,2)))
  tree:add(buffer(1+5,1), "Salvo: " .. tostring(buffer(1+5,1)))
  tree:add(buffer(1+6,1), "Step: " .. tostring(buffer(1+6,1)))
  tree:add(buffer(1+7,4), "Camera: " .. tostring(buffer(1+7,4)))
  tree:add(buffer(1+11,2), "Hold Time: " .. tostring(buffer(1+11,2)))
  tree:add(buffer(1+13,1), "Set: " .. tostring(buffer(1+13,1)))
  tree:add(buffer(1+14,1), "Wip: " .. tostring(buffer(1+14,1)))
end











  local dissector = {
    ["83070101"] = REQ_SET_HEARTJUMP_dissector,
    ["84070101"] = RET_SET_HEARTJUMP_dissector,
    ["82030101"] = Snd_Matrix_PowerOn_dissector,
    ["82030102"] = Snd_Matrix_CpuLog_dissector,
    ["82020103"] = Req_Set_MatrixIP_dissector,
    ["82040104"] = Ret_Set_MatrixIP_dissector,
    ["82010201"] = Req_Get_EquInfo_dissector,
    ["82040202"] = Ret_Get_EquInfo_dissector,
    ["82020203"] = Req_Set_ChannelInfo_dissector,
    ["82040204"] = Ret_Set_ChannelInfo_dissector,
    ["82020205"] = Req_Set_RouteInfo_dissector,
    ["82040206"] = Ret_Set_RouteInfo_dissector,
    ["82010207"] = Req_Get_RouteInfo_dissector,
    ["82040208"] = Ret_Get_RouteInfo_dissector,
    ["82020209"] = Req_Set_ReportMode_dissector,
    ["8204020a"] = Ret_Set_ReportMode_dissector,
    ["8201020b"] = Req_Get_WorkStatus_dissector,
    ["8204020c"] = Ret_Get_WorkStatus_dissector,
    ["8202020d"] = Req_Set_DeviceStatus_dissector,
    ["8204020e"] = Ret_Set_DeviceStatus_dissector,
    ["8203020f"] = Snd_Report_WorkStatus_dissector,
    ["82020210"] = Req_Set_SwitchInfo_dissector,
    ["82040211"] = Ret_Set_SwitchInfo_dissector,
    ["82020212"] = Req_Get_SwitchInfo_dissector,
    ["82040213"] = Ret_Get_SwitchInfo_dissector,
    ["82020214"] = Req_Set_MonitorInfo_dissector,
    ["82040215"] = Ret_Set_MonitorInfo_dissector,
    ["82020216"] = Req_Get_MonitorInfo_dissector,
    ["82040217"] = Ret_Get_MonitorInfo_dissector,
    ["82020218"] = Req_Set_TextDotInfo_dissector,
    ["82040219"] = Ret_Set_TextDotInfo_dissector,
    ["8202021a"] = Req_Active_dissector,
    ["8204021b"] = Ret_Active_dissector,
    ["81020305"] = Req_Set_MaskInfo_dissector,
    ["81040305"] = Ret_Set_MaskInfo_dissector,
    ["81020301"] = Req_Set_TextMask_dissector,
    ["81040302"] = Ret_Set_TextMask_dissector,
    ["81020303"] = Req_Set_Shield_dissector,
    ["81040304"] = Ret_Set_Shield_dissector,
    ["81020401"] = Req_Set_ChannelRoute_dissector,
    ["81040402"] = Ret_Set_ChannelRoute_dissector,
    ["80020501"] = Req_PT_PanTilt_dissector,
    ["80040502"] = Ret_PT_PanTilt_dissector,
    ["80020920"] = Req_Cpu_Update_dissector,
    ["80040921"] = Ret_Cpu_Update_dissector,   
    ["82010221"] = Req_Get_ChannelWorkStatus_dissector,
    ["82040222"] = Ret_Get_ChannelWorkStatus_dissector,
    ["82030223"] = Snd_Report_ChannelWorkStatus_dissector,
    ["82010221"] = Req_SwitchUser_dissector,
    ["82040222"] = Ret_SwitchUser_dissector,
    ["82030224"] = Snd_Report_SwitchUser_dissector,
    ["82010225"] = Req_Set_Fixed_ChannelRoute_dissector,
    ["82040226"] = Ret_Set_Fixed_ChannelRoute_dissector,
    ["82010227"] = Req_Set_Remote_InConn_ChannelRoute_dissector,
    ["82040228"] = Ret_Set_Remote_InConn_ChannelRoute_dissector,
    ["82010229"] = Req_Save_Fixed_Channel_dissector,
    ["82040230"] = Rsp_Save_Fixed_Channel_dissector,
    ["82010231"] = Req_Query_Fixed_Channel_dissector,
    ["82040232"] = Rsp_Query_Fixed_Channel_dissector,
    ["81010501"] = Req_Qry_Record_Channel_dissector,
    ["81040502"] = Rsp_Qry_Record_Channel_dissector,
    ["81020503"] = Req_Start_Record_dissector,
    ["81040504"] = Rsp_Start_Record_dissector,
    ["81020505"] = Req_Stop_Record_dissector,
    ["81020506"] = Rsp_Stop_Record_dissector,
    ["82030229"] = Req_OnOff_Alarm_dissector,
    ["82040230"] = Ret_OnOff_Alarm_dissector,
    ["83030101"] = Req_General_Alarm_dissector,
    ["83040101"] = Ret_General_Alarm_dissector,
    ["82020240"] = Req_Get_CardVersion_dissector,
    ["82040240"] = Ret_Get_CardVersion_dissector,
    ["82020241"] = Req_CpuDebug_Info_dissector,
    ["82040241"] = Ret_CpuDebug_Info_dissector,
    ["82020242"] = Snd_DisconnectOpt_Info_dissector,
    ["82040242"] = Ret_DisconnectOpt_Info_dissector,
    ["8202021e"] = Req_Search_CPUCard_dissector,
    ["8204021e"] = Ret_Search_CPUCard_dissector,
    ["8202021f"] = Req_Get_Boxinfo_dissector,
    ["8204021f"] = Ret_Get_Boxinfo_dissector,
    ["82020220"] = Req_Get_CenterCardinfo_dissector,
    ["82040220"] = Ret_Get_CenterCardinfo_dissector,
    ["82020221"] = Req_Get_FrontCardinfo_dissector,
    ["82040221"] = Ret_Get_FrontCardinfo_dissector,
    ["82020243"] = Req_Set_TextMask_HD_dissector,
    ["82040243"] = Ret_Set_TextMask_HD_dissector,        
    ["82020244"] = Req_Set_TimeMask_HD_dissector,
    ["82040244"] = Ret_Set_TimeMask_HD_dissector,
    ["82020253"] = Req_Query_VideoMapping_dissector,
    ["82040253"] = Ret_Query_VideoMapping_dissector,
    ["82040326"] = Ret_SetOutputMode_dissector,
    ["82020325"] = Req_SetOutputMode_dissector,
    ["82020335"] = Req_Reset_dissector,
    ["82020336"] = Ret_Reset_dissector,
    ["82020337"] = Req_SetPool_Channel_dissector,
    ["82040337"] = Ret_SetPool_Channel_dissector,
    ["80020922"] = Req_Set_Update_dissector,
    ["80040922"] = Ret_Set_Update_dissector,
    ["81020405"] = Req_Set_MulChannelRoute_dissector,
    ["81040405"] = Ret_Set_MulChannelRoute_dissector,
    ["83020401"] = Req_Set_MulCamSwi_dissector,
    ["83040401"] = Ret_Set_MulCamSwi_dissector,
    ["8202070a"] = Req_Set_MonitorRoute_dissector,
    ["8204070a"] = Ret_Set_MonitorRoute_dissector,
    ["8202060c"] = Req_Set_MulMonitorRoute_dissector,
    ["8204060c"] = Ret_Set_MulMonitorRoute_dissector,
    ["82020246"] = Req_Set_AlarmMask_dissector,
    ["82040246"] = Ret_Set_AlarmMask_dissector,
    ["82020339"] = Req_Set_CardReset_dissector,
    ["82040339"] = Ret_Set_CardReset_dissector,
    ["82020340"] = Req_Set_FlowStatis_dissector,
    ["82040340"] = Ret_Set_FlowStatis_dissector,
    ["82030102"] = Req_Trap_dissector,
    ["82040102"] = Ret_Trap_dissector,
    ["82020261"] = Req_Set_SwitchInfoV1_dissector,
    ["82040262"] = Ret_Set_SwitchInfoV1_dissector,
    ["82020263"] = Req_Get_SwitchInfoV1_dissector,
    ["82040264"] = Ret_Get_SwitchInfoV1_dissector,
    ["82020265"] = Req_Set_MonitorInfoV1_dissector,
    ["82040266"] = Ret_Set_MonitorInfoV1_dissector,
    ["82020267"] = Req_Get_MonitorInfoV1_dissector,
    ["82040268"] = Ret_Get_MonitorInfoV1_dissector,
    ["82020269"] = Req_Set_SiteNo_dissector,
    ["8204026a"] = Ret_Set_SiteNo_dissector,
    ["8202026b"] = Req_Get_WorkStatus_New_dissector,
    ["8204026c"] = Ret_Get_WorkStatus_New_dissector,
    ["82030105"] = Snd_Win_Input_dissector,
    ["82040106"] = Ret_Snd_Win_Input_dissector,
    ["82020107"] = Req_Set_UpdateV1_dissector,
    ["82040108"] = Ret_Set_UpdateV1_dissector,
    ["82020109"] = Req_Set_CardResetV1_dissector,
    ["8204010a"] = Ret_Set_CardResetV1_dissector,
    ["8202010b"] = Req_Get_CardVersionV1_dissector,
    ["8204010c"] = Ret_Get_CardVersionV1_dissector,


}
  
    
  local command ={
    ["83070101"] = "REQ_SET_HEARTJUMP_dissector",
    ["84070101"] = "RET_SET_HEARTJUMP_dissector",
    ["82030101"] = "Snd_Matrix_PowerOn_dissector",
    ["82030102"] = "Snd_Matrix_CpuLog_dissector",
    ["82020103"] = "Req_Set_MatrixIP_dissector",
    ["82040104"] = "Ret_Set_MatrixIP_dissector",
    ["82010201"] = "Req_Get_EquInfo_dissector",
    ["82040202"] = "Ret_Get_EquInfo_dissector",
    ["82020203"] = "Req_Set_ChannelInfo_dissector",
    ["82040204"] = "Ret_Set_ChannelInfo_dissector",
    ["82020205"] = "Req_Set_RouteInfo_dissector",
    ["82040206"] = "Ret_Set_RouteInfo_dissector",
    ["82010207"] = "Req_Get_RouteInfo_dissector",
    ["82040208"] = "Ret_Get_RouteInfo_dissector",
    ["82020209"] = "Req_Set_ReportMode_dissector",
    ["8204020a"] = "Ret_Set_ReportMode_dissector",
    ["8201020b"] = "Req_Get_WorkStatus_dissector",
    ["8204020c"] = "Ret_Get_WorkStatus_dissector",
    ["8202020d"] = "Req_Set_DeviceStatus_dissector",
    ["8204020e"] = "Ret_Set_DeviceStatus_dissector",
    ["8203020f"] = "Snd_Report_WorkStatus_dissector",
    ["82020210"] = "Req_Set_SwitchInfo_dissector",
    ["82040211"] = "Ret_Set_SwitchInfo_dissector",
    ["82020212"] = "Req_Get_SwitchInfo_dissector",
    ["82040213"] = "Ret_Get_SwitchInfo_dissector",
    ["82020214"] = "Req_Set_MonitorInfo_dissector",
    ["82040215"] = "Ret_Set_MonitorInfo_dissector",
    ["82020216"] = "Req_Get_MonitorInfo_dissector",
    ["82040217"] = "Ret_Get_MonitorInfo_dissector",
    ["82020218"] = "Req_Set_TextDotInfo_dissector",
    ["82040219"] = "Ret_Set_TextDotInfo_dissector",
    ["8202021a"] = "Req_Active_dissector",
    ["8204021b"] = "Ret_Active_dissector",
    ["81020305"] = "Req_Set_MaskInfo_dissector",
    ["81040305"] = "Ret_Set_MaskInfo_dissector",
    ["81020301"] = "Req_Set_TextMask_dissector",
    ["81040302"] = "Ret_Set_TextMask_dissector",
    ["81020303"] = "Req_Set_Shield_dissector",
    ["81040304"] = "Ret_Set_Shield_dissector",
    ["81020401"] = "Req_Set_ChannelRoute_dissector",
    ["81040402"] = "Ret_Set_ChannelRoute_dissector",
    ["80020501"] = "Req_PT_PanTilt_dissector",
    ["80040502"] = "Ret_PT_PanTilt_dissector",
    ["80020920"] = "Req_Cpu_Update_dissector",
    ["80040921"] = "Ret_Cpu_Update_dissector",   
    ["82010221"] = "Req_Get_ChannelWorkStatus_dissector",
    ["82040222"] = "Ret_Get_ChannelWorkStatus_dissector",
    ["82030223"] = "Snd_Report_ChannelWorkStatus_dissector",
    ["82010221"] = "Req_SwitchUser_dissector",
    ["82040222"] = "Ret_SwitchUser_dissector",
    ["82030224"] = "Snd_Report_SwitchUser_dissector",
    ["82010225"] = "Req_Set_Fixed_ChannelRoute_dissector",
    ["82040226"] = "Ret_Set_Fixed_ChannelRoute_dissector",
    ["82010227"] = "Req_Set_Remote_InConn_ChannelRoute_dissector",
    ["82040228"] = "Ret_Set_Remote_InConn_ChannelRoute_dissector",
    ["82010229"] = "Req_Save_Fixed_Channel_dissector",
    ["82040230"] = "Rsp_Save_Fixed_Channel_dissector",
    ["82010231"] = "Req_Query_Fixed_Channel_dissector",
    ["82040232"] = "Rsp_Query_Fixed_Channel_dissector",
    ["81010501"] = "Req_Qry_Record_Channel_dissector",
    ["81040502"] = "Rsp_Qry_Record_Channel_dissector",
    ["81020503"] = "Req_Start_Record_dissector",
    ["81040504"] = "Rsp_Start_Record_dissector",
    ["81020505"] = "Req_Stop_Record_dissector",
    ["81020506"] = "Rsp_Stop_Record_dissector",
    ["82030229"] = "Req_OnOff_Alarm_dissector",
    ["82040230"] = "Ret_OnOff_Alarm_dissector",
    ["83030101"] = "Req_General_Alarm_dissector",
    ["83040101"] = "Ret_General_Alarm_dissector",
    ["82020240"] = "Req_Get_CardVersion_dissector",
    ["82040240"] = "Ret_Get_CardVersion_dissector",
    ["82020241"] = "Req_CpuDebug_Info_dissector",
    ["82040241"] = "Ret_CpuDebug_Info_dissector",
    ["82020242"] = "Snd_DisconnectOpt_Info_dissector",
    ["82040242"] = "Ret_DisconnectOpt_Info_dissector",
    ["8202021e"] = "Req_Search_CPUCard_dissector",
    ["8204021e"] = "Ret_Search_CPUCard_dissector",
    ["8202021f"] = "Req_Get_Boxinfo_dissector",
    ["8204021f"] = "Ret_Get_Boxinfo_dissector",
    ["82020220"] = "Req_Get_CenterCardinfo_dissector",
    ["82040220"] = "Ret_Get_CenterCardinfo_dissector",
    ["82020221"] = "Req_Get_FrontCardinfo_dissector",
    ["82040221"] = "Ret_Get_FrontCardinfo_dissector",
    ["82020243"] = "Req_Set_TextMask_HD_dissector",
    ["82040243"] = "Ret_Set_TextMask_HD_dissector",        
    ["82020244"] = "Req_Set_TimeMask_HD_dissector",
    ["82040244"] = "Ret_Set_TimeMask_HD_dissector",
    ["82020253"] = "Req_Query_VideoMapping_dissector",
    ["82040253"] = "Ret_Query_VideoMapping_dissector",
    ["82040326"] = "Ret_SetOutputMode_dissector",
    ["82020325"] = "Req_SetOutputMode_dissector",
    ["82020335"] = "Req_Reset_dissector",
    ["82020336"] = "Ret_Reset_dissector",
    ["82020337"] = "Req_SetPool_Channel_dissector",
    ["82040337"] = "Ret_SetPool_Channel_dissector",
    ["80020922"] = "Req_Set_Update_dissector",
    ["80040922"] = "Ret_Set_Update_dissector",
    ["81020405"] = "Req_Set_MulChannelRoute_dissector",
    ["81040405"] = "Ret_Set_MulChannelRoute_dissector",
    ["83020401"] = "Req_Set_MulCamSwi_dissector",
    ["83040401"] = "Ret_Set_MulCamSwi_dissector",
    ["8202070a"] = "Req_Set_MonitorRoute_dissector",
    ["8204070a"] = "Ret_Set_MonitorRoute_dissector",
    ["8202060c"] = "Req_Set_MulMonitorRoute_dissector",
    ["8204060c"] = "Ret_Set_MulMonitorRoute_dissector",
    ["82020246"] = "Req_Set_AlarmMask_dissector",
    ["82040246"] = "Ret_Set_AlarmMask_dissector",
    ["82020339"] = "Req_Set_CardReset_dissector",
    ["82040339"] = "Ret_Set_CardReset_dissector",
    ["82020340"] = "Req_Set_FlowStatis_dissector",
    ["82040340"] = "Ret_Set_FlowStatis_dissector",
    ["82030102"] = "Req_Trap_dissector",
    ["82040102"] = "Ret_Trap_dissector",
    ["82020261"] = "Req_Set_SwitchInfoV1_dissector",
    ["82040262"] = "Ret_Set_SwitchInfoV1_dissector",
    ["82020263"] = "Req_Get_SwitchInfoV1_dissector",
    ["82040264"] = "Ret_Get_SwitchInfoV1_dissector",
    ["82020265"] = "Req_Set_MonitorInfoV1_dissector",
    ["82040266"] = "Ret_Set_MonitorInfoV1_dissector",
    ["82020267"] = "Req_Get_MonitorInfoV1_dissector",
    ["82040268"] = "Ret_Get_MonitorInfoV1_dissector",
    ["82020269"] = "Req_Set_SiteNo_dissector",
    ["8204026a"] = "Ret_Set_SiteNo_dissector",
    ["8202026b"] = "Req_Get_WorkStatus_New_dissector",
    ["8204026c"] = "Ret_Get_WorkStatus_New_dissector",
    ["82030105"] = "Snd_Win_Input_dissector",
    ["82040106"] = "Ret_Snd_Win_Input_dissector",
    ["82020107"] = "Req_Set_UpdateV1_dissector",
    ["82040108"] = "Ret_Set_UpdateV1_dissector",
    ["82020109"] = "Req_Set_CardResetV1_dissector",
    ["8204010a"] = "Ret_Set_CardResetV1_dissector",
    ["8202010b"] = "Req_Get_CardVersionV1_dissector",
    ["8204010c"] = "Ret_Get_CardVersionV1_dissector",

}

function Var.dissector(buffer,pinfo,tree)
  pinfo.cols.protocol = ("TCP[VAR]")
  local VAR_tree = tree:add(Var,buffer(0,buffer:len()),"VAR Protocol")
    local msg_head_tree = VAR_tree:add(Var,buffer(0,32),"Message Head")
      msg_head_tree:add(buffer(8,1),"Protocol Type: " .. protocol[buffer(8,1):uint()])
      msg_head_tree:add(buffer(9,1),"Message Type: " .. message[buffer(9,1):uint()])
	    msg_head_tree:add(buffer(2,2),"Message Length: " .. buffer(2,2):uint())
	    msg_head_tree:add(buffer(4,4),"Message Mark: " .. tostring(buffer(4,4)))
	    msg_head_tree:add(buffer(8,4),"Message Index: " .. tostring(buffer(8,4)))
	    msg_head_tree:add(buffer(12,4),"Message Send Index: " .. tostring(buffer(12,4)))
	    msg_head_tree:add(buffer(16,4),"Message Receive Index: " .. tostring(buffer(16,4)))
	    msg_head_tree:add(buffer(20,12),"Retain: " .. tostring(buffer(20,12)))
    local msg_data_tree = VAR_tree:add(Var,buffer(32,buffer:len()-40),"Message Data	[" .. command[tostring(buffer(8,4))] .. "	" .. tostring(buffer(8,4)) .. "]")
      dissector[tostring(buffer(8,4))](buffer(32,buffer:len()-40), pinfo, msg_data_tree)
    local msg_crc_tree = VAR_tree:add(Var,buffer(buffer:len()-8,8),"Message CRC")
      msg_crc_tree:add(buffer(buffer:len()-8,8),"Crc:" .. tostring(buffer(buffer:len()-8,8)))
end

  
local tcp_port_table = DissectorTable.get("tcp.port")
tcp_port_table:add(8800, Var)
tcp_port_table:add(9002, Var)

end