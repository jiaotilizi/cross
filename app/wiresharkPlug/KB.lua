do

KB = Proto ("KB","UDP for KeyBoard","My Self-defined Protocol")
	
	local 	vs_fun = {
		[0] = "Stop",
		[1] = "Left",
		[2] = "Right",
		[3] = "Down",
		[4] = "Up",
		[5] = "Down-left",
		[6] = "Up-left",
		[7] = "Down-right",
		[8] = "Up-right",
		[9] = "Far",
		[10] = "Near",
		[11] = "Close",
		[12] = "Open",
		[13] = "Tele",
		[14] = "Wide",
		[15] = "1 ON",
		[16] = "1 OFF",
		[17] = "2 ON",
		[18] = "2 OFF",
		[19] = "3 ON",
		[20] = "3 OFF",
		[55] = "Set",
		[56] = "Delset",
		[57] = "Preset",
		[31] = "Switch",
		[30] = "Switch",
		[70] = "Capture",
		[71] = "M1",
		[72] = "M2",
		[73] = "M3",
		[74] = "Global Preset"
	}




	local f_host = ProtoField.uint8("host", "Host ID",base.DEC)
	local f_user = ProtoField.uint8("user", "User ID",base.DEC)
	local f_site = ProtoField.uint8("site", "Site ID",base.DEC)
	local f_cam = ProtoField.uint16("cam", "Cam ID",base.DEC)
	local f_mon = ProtoField.uint16("mon", "Mon ID",base.DEC)
	local f_spd_x = ProtoField.uint8("spd_x", "Speed of X")
	local f_spd_y = ProtoField.uint8("spd_y", "Speed of Y")
	local f_fun = ProtoField.uint8("fun", "Function", base.DEC, vs_fun)
	local f_set =  ProtoField.uint8("set", "SetID", base.DEC)
	KB.fields = { f_host, f_user, f_site, f_cam, f_mon, f_spd_x, f_spd_y, f_fun, f_set }

	local data_dis = Dissector.get("data")


function control_dissector(buffer,pinfo,tree)
	local msg_fun = buffer(8.1):uint()
	pinfo.cols.info:set(vs_fun[msg_fun] .. "	Site:" .. buffer(3,1):uint() .. "	Cam:" .. (buffer(4,1):uint()*100+buffer(5,1):uint()))
	local tree = tree:add(KB,buffer(0,8), "UDP for KeyBoard" .. ": " .. vs_fun[msg_fun])
	tree:add(f_fun, buffer(8,1))
	tree:add(f_host, buffer(1,1))
	tree:add(f_user, buffer(2,1))
	tree:add(f_site, buffer(3,1))
	tree:add(f_cam, buffer(4,2), (buffer(4,1):uint()*100+buffer(5,1):uint()))
	tree:add(f_spd_x, buffer(6,1))
	tree:add(f_spd_y, buffer(7,1))
end

function set_dissector(buffer,pinfo,tree)
	local msg_fun = buffer(8.1):uint()
	pinfo.cols.info:set(vs_fun[msg_fun] .. ":" .. buffer(7,1):uint() .. "	Site:" .. buffer(3,1):uint() .. "	Cam:" .. (buffer(4,1):uint()*100+buffer(5,1):uint()))
	local tree = tree:add(KB,buffer(0,8), "UDP for KeyBoard" .. ": " .. vs_fun[msg_fun])
	tree:add(f_fun, buffer(8,1))
	tree:add(f_host, buffer(1,1))
	tree:add(f_user, buffer(2,1))
	tree:add(f_site, buffer(3,1))
	tree:add(f_cam, buffer(4,2), (buffer(4,1):uint()*100+buffer(5,1):uint()))
	tree:add(f_set, buffer(7,1))
end


function switch_dissector(buffer,pinfo,tree)
	local msg_fun = buffer(8.1):uint()
	pinfo.cols.info:set(vs_fun[msg_fun] .. "	Site:" .. buffer(5,1):uint()  .. "	Cam:" .. (buffer(6,1):uint()*100+buffer(7,1):uint()) .. "	Mon:" .. (buffer(3,1):uint()*200+buffer(4,1):uint()))
	local tree = tree:add(KB,buffer(0,8), "UDP for KeyBoard" .. ": " .. vs_fun[msg_fun])
	tree:add(f_fun, buffer(8,1))
	tree:add(f_host, buffer(1,1))
	tree:add(f_user, buffer(2,1))
	tree:add(f_mon, buffer(3,2), (buffer(3,1):uint()*200+buffer(4,1):uint()))
	tree:add(f_site, buffer(5,1))
	tree:add(f_cam, buffer(6,2),(buffer(6,1):uint()*100+buffer(7,1):uint()))
	
end


function pelco_D_dissector(buffer,pinfo,tree)
	local msg_pelco_fun = tostring(buffer(3,1))
	pinfo.cols.info:set("Pelco-D	Cam:" .. buffer(1,1) .. msg_pelco_fun)
	local tree = tree:add(KB,buffer)
		tree:add("ON")
	local B3_b5 = string.sub(msg_pelco_fun,4,4)
	if B3_b5 == "1" then
		tree:add("OFF")
	end
end


function pelco_P_dissector(buffer,pinfo,tree)
	pinfo.cols.info:set("Pelco-P	Cam:" .. buffer(1,1))		
end


function KB.dissector(buffer,pinfo,tree)
	pinfo.cols.protocol = "KB"
	local msg_start = buffer(0,1):uint()
	
	if msg_start == 248 then
		local msg_fun = buffer(8,1):uint()
		if ((msg_fun == 0) or (msg_fun == 1) or (msg_fun == 2) or (msg_fun == 3) or (msg_fun == 4) or (msg_fun == 5) 
			or (msg_fun == 6) or (msg_fun == 7) or (msg_fun == 8) or (msg_fun == 9) or (msg_fun == 10) or (msg_fun == 11) 
			or (msg_fun == 12) or (msg_fun == 13) or (msg_fun == 14) or (msg_fun == 15) or (msg_fun == 16) or (msg_fun == 17) or (msg_fun == 18)
			or (msg_fun == 19) or (msg_fun == 20))  then
			control_dissector(buffer,pinfo,tree)
		elseif ((msg_fun == 55) or (msg_fun == 56) or (msg_fun == 57)) or (msg_fun == 74) then
			set_dissector(buffer,pinfo,tree)
		elseif ((msg_fun == 30) or (msg_fun == 31) or (msg_fun == 70) or (msg_fun == 71) or (msg_fun == 72) or (msg_fun == 73) 
			or (msg_fun == 15) or (msg_fun == 16) or (msg_fun == 17) or (msg_fun == 18) or (msg_fun == 19) or (msg_fun == 20)) then
			switch_dissector(buffer,pinfo,tree)
		else
			data_dis:call(buffer,pinfo,tree)
		end
	elseif (msg_start == 255) then
		pelco_D_dissector(buffer,pinfo,tree)
	elseif (msg_start == 160) then
		pelco_P_dissector(buffer,pinfo,tree)
	end
end


local udp_port_table = DissectorTable.get("udp.port")
local my_port = 1026
udp_port_table:add(my_port, KB)


end
