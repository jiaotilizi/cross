do

OBEP = Proto ("OBEP","OBEP","My Self-defined Protocol")

function treeadd(tree,buffer,str,fun,usrtype)
	if fun == nil then
		if usrtype == nil then
			tree:add(buffer, str .. buffer)
		else
			tree:add(buffer, str .. usrtype[buffer:uint()])
		end
	else
		tree:add(buffer, str .. fun(buffer))
	end
end


function treeadd_tab(tree,buffer,tab)
	offset = 0
	for i = 1,table.getn(tab)
		do
		treeadd(tree,buffer(offset,tab[i][1]),tab[i][2],tab[i][3],tab[i][4])
		offset = offset + tab[i][1]
	end
end

function  fun_type_select_dissector(buffer,pinfo,tree)
	 
	            
				 --[[
				 Set_Xun_hu_dissector(buffer,pinfo,tree)
	             Response_Xun_hu_dissector(buffer,pinfo,tree)
				 
				 Set_Start_dissector(buffer,pinfo,tree)
				 Response_Start_dissector(buffer,pinfo,tree)
				 
				 
				 
				 
				 --]]
				 
				 
				 
end 
	



function head_dissector(buffer,pinfo,tree)
	local tab ={
			{3,"Organization Code:",},
			{2,"Protocol Type: ",},
			{1,"Version: ",},
			{1,"Message Type: ",},
			{2,"Message Length: ",},
			{2,"Request ID: ",},
			{6,"MAC of the Switch: ",},
			}
	treeadd_tab(tree,buffer(0,17),tab)
end

function Set_Xun_hu_dissector(buffer,pinfo,tree)
	local tab ={
			{1,"Get Code: ",},
			{1,"Result Status: ", },
			{buffer:len()-2,"Pad: ", },
			}
	treeadd_tab(tree,buffer(0,buffer:len()),tab)
end


function Response_Xun_hu_dissector(buffer,pinfo,tree)
	local tab ={
			{1,"Get Code: ",},
			{1,"Result Status: ", },
			{1,"Res: ", },
			{8,"Switch Type: ", },
			{2,"SoftVersion: ", },
			{1,"ChipType: ", },
			{4,"FeatureMask: ", },
			{buffer:len()-18,"Pad: ", },
			}
	treeadd_tab(tree,buffer(0,buffer:len()),tab)
end

function Set_Start_dissector(buffer,pinfo,tree)
	local tab ={
			{1,"Set Code(start): ",},
			{1,"Result Status: ", },
			
			{buffer:len()-2,"Pad: ", },
			}
	treeadd_tab(tree,buffer(0,buffer:len()),tab)
end

function Response_Start_dissector(buffer,pinfo,tree)
	local tab ={
			{1,"Set Code(start): ",},
			{1,"Result Status: ", },
			
			{buffer:len()-2,"Pad: ", },
			}
	treeadd_tab(tree,buffer(0,buffer:len()),tab)
end

local dissector = {
	["ff"] = Set_Xun_hu_dissector,}





function OBEP.dissector(buffer,pinfo,tree)
	pinfo.cols.protocol = "OBEP"
	local OBEP_tree = tree:add(OBEP,buffer(0,buffer:len()),"OBEP Protocol")
	command=tostring(buffer(17,1))
	
	local head_tree = OBEP_tree:add(OBEP,buffer(0,17),"Message Head")
	head_dissector(buffer(0,17),pinfo,head_tree)
		
	local data_tree = OBEP_tree:add(OBEP,buffer(17,buffer:len()-17),"Message Data")
	dissector[command](buffer(17,buffer:len()-17), pinfo, data_tree)
end


local eth_type_table = DissectorTable.get("ethertype")
local my_type = 0x88b7
eth_type_table:add(my_type, OBEP)


end
