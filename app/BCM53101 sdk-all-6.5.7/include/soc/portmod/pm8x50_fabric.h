/*
 *         
 * $Id:$
 * 
 * $Copyright: (c) 2016 Broadcom.
 * Broadcom Proprietary and Confidential. All rights reserved.$
 *         
 *     
 * DO NOT EDIT THIS FILE!
 *
 */

#ifndef _PM8X50_FABRIC_H__H_
#define _PM8X50_FABRIC_H__H_

#include <phymod/phymod.h>
#include <phymod/phymod_diagnostics.h>
#include <soc/portmod/portmod_defs.h>
/*Get whether the inerface type is supported by PM */
int pm8x50_fabric_pm_interface_type_is_supported(int unit, soc_port_if_t interface, int* is_supported);

/*Add new pm.*/
int pm8x50_fabric_pm_init(int unit, const portmod_pm_create_info_internal_t* pm_add_info, int wb_buffer_index, pm_info_t pm_info);

/*Release PM resources*/
int pm8x50_fabric_pm_destroy(int unit, pm_info_t pm_info);

/*Add new port*/
int pm8x50_fabric_port_attach(int unit, int port, pm_info_t pm_info, const portmod_port_add_info_t* add_info);

/*Set PM in bypass mode. should be called in the aggregator code.*/
int pm8x50_fabric_pm_bypass_set(int unit, pm_info_t pm_info, int enable);

/*get port cores' phymod access*/
int pm8x50_fabric_pm_core_info_get(int unit, pm_info_t pm_info, int phyn, portmod_pm_core_info_t* core_info);

/*Get PM phys.*/
int pm8x50_fabric_pm_phys_get(int unit, pm_info_t pm_info, portmod_pbmp_t* phys);

/*Port remove in PM level*/
int pm8x50_fabric_port_detach(int unit, int port, pm_info_t pm_info);

/*Port replace in PM level*/
int pm8x50_fabric_port_replace(int unit, int port, pm_info_t pm_info, int new_port);

/*Port enable*/
int pm8x50_fabric_port_enable_set(int unit, int port, pm_info_t pm_info, int flags, int enable);
int pm8x50_fabric_port_enable_get(int unit, int port, pm_info_t pm_info, int flags, int* enable);

/* set/get the interface, speed and encapsulation for the specified port.
            For the First port within core this function initialize the PM, MAC and PHY before configure the port.*/
int pm8x50_fabric_port_interface_config_set(int unit, int port, pm_info_t pm_info, const portmod_port_interface_config_t* config, int phy_init_flags);
int pm8x50_fabric_port_interface_config_get(int unit, int port, pm_info_t pm_info, portmod_port_interface_config_t* config, int phy_init_flags);

/* get the default line-side (outmost) interface type of a port based on its speed, encap, number of lanes, etc, when there is or there is not an ext PHY*/
int pm8x50_fabric_port_default_interface_get(int unit, int port, pm_info_t pm_info, const portmod_port_interface_config_t* config, soc_port_if_t* interface);

/*chage port PCS encoding */
int pm8x50_fabric_port_encoding_set(int unit, int port, pm_info_t pm_info, uint32 properties, portmod_port_pcs_t encoding);
int pm8x50_fabric_port_encoding_get(int unit, int port, pm_info_t pm_info, uint32* properties, portmod_port_pcs_t* encoding);

/*Port cl72 set\get*/
int pm8x50_fabric_port_cl72_set(int unit, int port, pm_info_t pm_info, uint32 enable);
int pm8x50_fabric_port_cl72_get(int unit, int port, pm_info_t pm_info, uint32* enable);

/*Port speed set\get*/
int pm8x50_fabric_port_loopback_set(int unit, int port, pm_info_t pm_info, portmod_loopback_mode_t loopback_type, int enable);
int pm8x50_fabric_port_loopback_get(int unit, int port, pm_info_t pm_info, portmod_loopback_mode_t loopback_type, int* enable);

/*get link status*/
int pm8x50_fabric_port_link_get(int unit, int port, pm_info_t pm_info, int flags, int* link);

/*PRBS configuration set/get*/
int pm8x50_fabric_port_prbs_config_set(int unit, int port, pm_info_t pm_info, portmod_prbs_mode_t mode, int flags, const phymod_prbs_t* config);
int pm8x50_fabric_port_prbs_config_get(int unit, int port, pm_info_t pm_info, portmod_prbs_mode_t mode, int flags, phymod_prbs_t* config);

/*PRBS enable set/get*/
int pm8x50_fabric_port_prbs_enable_set(int unit, int port, pm_info_t pm_info, portmod_prbs_mode_t mode, int flags, int enable);
int pm8x50_fabric_port_prbs_enable_get(int unit, int port, pm_info_t pm_info, portmod_prbs_mode_t mode, int flags, int* enable);

/*PRBS status get*/
int pm8x50_fabric_port_prbs_status_get(int unit, int port, pm_info_t pm_info, portmod_prbs_mode_t mode, int flags, phymod_prbs_status_t* status);

/*Routine for MAC\PHY sync.*/
int pm8x50_fabric_port_update(int unit, int port, pm_info_t pm_info, const portmod_port_update_control_t* update_control);

/*get port cores' phymod access*/
int pm8x50_fabric_port_core_access_get(int unit, int port, pm_info_t pm_info, int phyn, int max_cores, phymod_core_access_t* core_access_arr, int* nof_cores, int* is_most_ext);

/*Get lane phymod access structure. can be used for per lane operations*/
int pm8x50_fabric_port_phy_lane_access_get(int unit, int port, pm_info_t pm_info, const portmod_access_get_params_t* params, int max_phys, phymod_phy_access_t* access, int* nof_phys, int* is_most_ext);

/*Port duplex set\get*/
int pm8x50_fabric_port_duplex_set(int unit, int port, pm_info_t pm_info, int enable);
int pm8x50_fabric_port_duplex_get(int unit, int port, pm_info_t pm_info, int* enable);

/*Attaches an external phy lane to a specific port macro*/
int pm8x50_fabric_ext_phy_lane_attach_to_pm(int unit, pm_info_t pm_info, int iphy, int phyn, const portmod_lane_connection_t* lane_connection);

/*Attaches an external phy lane to a specific port macro*/
int pm8x50_fabric_ext_phy_lane_detach_from_pm(int unit, pm_info_t pm_info, int iphy, int phyn, portmod_lane_connection_t* lane_connection);

/*set port mode.*/
int pm8x50_fabric_port_mode_set(int unit, int port, pm_info_t pm_info, const portmod_port_mode_info_t* mode);
int pm8x50_fabric_port_mode_get(int unit, int port, pm_info_t pm_info, portmod_port_mode_info_t* mode);

/*port diagnostics control.*/
int pm8x50_fabric_port_diag_ctrl(int unit, int port, pm_info_t pm_info, uint32 inst, int op_type, int op_cmd, const void* arg);

/*override function for board lane swap. */
int pm8x50_fabric_port_lane_map_set(int unit, int port, pm_info_t pm_info, const phymod_lane_map_t* lane_map);
int pm8x50_fabric_port_lane_map_get(int unit, int port, pm_info_t pm_info, phymod_lane_map_t* lane_map);

/*override function for board lane swap. */
int pm8x50_fabric_port_polarity_set(int unit, int port, pm_info_t pm_info, const phymod_polarity_t* polarity);
int pm8x50_fabric_port_polarity_get(int unit, int port, pm_info_t pm_info, phymod_polarity_t* polarity);

/*Write slow read rate value to relevant register*/
int pm8x50_fabric_slow_read_rate_set(int unit, int port, pm_info_t pm_info, int slow_read_rate);

#endif /*_PM8X50_FABRIC_H_*/
