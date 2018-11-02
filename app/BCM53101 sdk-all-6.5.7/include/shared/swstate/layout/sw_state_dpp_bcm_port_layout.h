/* $Id: $
 * 
 * $Copyright: (c) 2016 Broadcom.
 * Broadcom Proprietary and Confidential. All rights reserved.$
 * 
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated.
 * Edits to this file will be lost when it is regenerated.
*/
#ifndef _SHR_sw_state_dpp_bcm_port_H_
#define _SHR_sw_state_dpp_bcm_port_H_


#define SW_STATE_DPP_BCM_PORT_TPIDS_COUNT_LAYOUT_NOF_MAX_LAYOUT_NODES (1) 
#define SW_STATE_DPP_BCM_PORT_DPP_PORT_CONFIG_BCM_PETRA_PORT_INIT_ARRAYS_DONE_LAYOUT_NOF_MAX_LAYOUT_NODES (1) 
#define SW_STATE_DPP_BCM_PORT_DPP_PORT_CONFIG_PORT_PP_INITIALIZED_LAYOUT_NOF_MAX_LAYOUT_NODES (1) 
#define SW_STATE_DPP_BCM_PORT_DPP_PORT_CONFIG_MAP_TBL_USE_LAYOUT_NOF_MAX_LAYOUT_NODES (1) 
#define SW_STATE_DPP_BCM_PORT_DPP_PORT_CONFIG_TRAP_TO_FLAG_LAYOUT_NOF_MAX_LAYOUT_NODES (1) 
#define SW_STATE_DPP_BCM_PORT_DPP_PORT_CONFIG_BCM_PORT_TPID_INFO_TPID_LAYOUT_NOF_MAX_LAYOUT_NODES (1) 
#define SW_STATE_DPP_BCM_PORT_DPP_PORT_CONFIG_BCM_PORT_TPID_INFO_TPID_COUNT_LAYOUT_NOF_MAX_LAYOUT_NODES (1) 
#define SW_STATE_DPP_BCM_PORT_DPP_PORT_CONFIG_BCM_PORT_TPID_INFO_LAYOUT_NOF_MAX_LAYOUT_NODES (1 + SW_STATE_DPP_BCM_PORT_DPP_PORT_CONFIG_BCM_PORT_TPID_INFO_TPID_LAYOUT_NOF_MAX_LAYOUT_NODES + SW_STATE_DPP_BCM_PORT_DPP_PORT_CONFIG_BCM_PORT_TPID_INFO_TPID_COUNT_LAYOUT_NOF_MAX_LAYOUT_NODES) 
#define SW_STATE_DPP_BCM_PORT_DPP_PORT_CONFIG_LAYOUT_NOF_MAX_LAYOUT_NODES (1 + SW_STATE_DPP_BCM_PORT_DPP_PORT_CONFIG_BCM_PETRA_PORT_INIT_ARRAYS_DONE_LAYOUT_NOF_MAX_LAYOUT_NODES + SW_STATE_DPP_BCM_PORT_DPP_PORT_CONFIG_PORT_PP_INITIALIZED_LAYOUT_NOF_MAX_LAYOUT_NODES + SW_STATE_DPP_BCM_PORT_DPP_PORT_CONFIG_MAP_TBL_USE_LAYOUT_NOF_MAX_LAYOUT_NODES + SW_STATE_DPP_BCM_PORT_DPP_PORT_CONFIG_TRAP_TO_FLAG_LAYOUT_NOF_MAX_LAYOUT_NODES + SW_STATE_DPP_BCM_PORT_DPP_PORT_CONFIG_BCM_PORT_TPID_INFO_LAYOUT_NOF_MAX_LAYOUT_NODES) 
#define SW_STATE_DPP_BCM_PORT_PRBS_MAC_MODE_LAYOUT_NOF_MAX_LAYOUT_NODES (1) 
#define SW_STATE_DPP_BCM_PORT_LAYOUT_NOF_MAX_LAYOUT_NODES (1 + SW_STATE_DPP_BCM_PORT_TPIDS_COUNT_LAYOUT_NOF_MAX_LAYOUT_NODES + SW_STATE_DPP_BCM_PORT_DPP_PORT_CONFIG_LAYOUT_NOF_MAX_LAYOUT_NODES + SW_STATE_DPP_BCM_PORT_PRBS_MAC_MODE_LAYOUT_NOF_MAX_LAYOUT_NODES) 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
int sw_state_dpp_bcm_port_layout_node_create(int unit, int* root_node_id, uint32* next_free_node_id);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
int sw_state_dpp_bcm_port_tpids_count_layout_node_create(int unit, int* root_node_id, uint32* next_free_node_id);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
int sw_state_dpp_bcm_port_dpp_port_config_layout_node_create(int unit, int* root_node_id, uint32* next_free_node_id);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
int sw_state_dpp_bcm_port_dpp_port_config_bcm_petra_port_init_arrays_done_layout_node_create(int unit, int* root_node_id, uint32* next_free_node_id);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
int sw_state_dpp_bcm_port_dpp_port_config_port_pp_initialized_layout_node_create(int unit, int* root_node_id, uint32* next_free_node_id);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
int sw_state_dpp_bcm_port_dpp_port_config_map_tbl_use_layout_node_create(int unit, int* root_node_id, uint32* next_free_node_id);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
int sw_state_dpp_bcm_port_dpp_port_config_trap_to_flag_layout_node_create(int unit, int* root_node_id, uint32* next_free_node_id);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
int sw_state_dpp_bcm_port_dpp_port_config_bcm_port_tpid_info_layout_node_create(int unit, int* root_node_id, uint32* next_free_node_id);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
int sw_state_dpp_bcm_port_dpp_port_config_bcm_port_tpid_info_tpid_layout_node_create(int unit, int* root_node_id, uint32* next_free_node_id);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
int sw_state_dpp_bcm_port_dpp_port_config_bcm_port_tpid_info_tpid_count_layout_node_create(int unit, int* root_node_id, uint32* next_free_node_id);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
int sw_state_dpp_bcm_port_prbs_mac_mode_layout_node_create(int unit, int* root_node_id, uint32* next_free_node_id);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#endif /* _SHR_sw_state_dpp_bcm_port_H_ */
