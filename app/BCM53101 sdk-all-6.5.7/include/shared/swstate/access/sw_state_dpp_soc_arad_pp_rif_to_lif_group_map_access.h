/* $Id: $
 * 
 * $Copyright: (c) 2016 Broadcom.
 * Broadcom Proprietary and Confidential. All rights reserved.$
 * 
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated.
 * Edits to this file will be lost when it is regenerated.
 * search for 'sw_state_cbs_t' for the root of the struct
 */

#ifndef _SHR_SW_STATE_DPP_SOC_ARAD_PP_RIF_TO_LIF_GROUP_MAP_ACCESS_H_
#define _SHR_SW_STATE_DPP_SOC_ARAD_PP_RIF_TO_LIF_GROUP_MAP_ACCESS_H_

/********************************* access calbacks definitions *************************************/
/* this set of callbacks, are the callbacks used in the access calbacks struct 'sw_state_cbs_t' to */
/* access the data in 'sw_state_t'.                                                                */
/* the calbacks are inserted into the access struct by 'sw_state_access_cb_init'.                  */
/***************************************************************************************************/

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_rif_to_lif_group_map_alloc */
typedef int (*sw_state_dpp_soc_arad_pp_rif_to_lif_group_map_alloc_cb)(
    int unit);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_rif_to_lif_group_map_is_allocated */
typedef int (*sw_state_dpp_soc_arad_pp_rif_to_lif_group_map_is_allocated_cb)(
    int unit, uint8 *is_allocated);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_rif_to_lif_group_map_free */
typedef int (*sw_state_dpp_soc_arad_pp_rif_to_lif_group_map_free_cb)(
    int unit);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_rif_to_lif_group_map_verify */
typedef int (*sw_state_dpp_soc_arad_pp_rif_to_lif_group_map_verify_cb)(
    int unit);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_rif_to_lif_group_map_rif_urpf_mode_set */
typedef int (*sw_state_dpp_soc_arad_pp_rif_to_lif_group_map_rif_urpf_mode_set_cb)(
    int unit, int rif_urpf_mode_idx_0, uint8 rif_urpf_mode);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_rif_to_lif_group_map_rif_urpf_mode_get */
typedef int (*sw_state_dpp_soc_arad_pp_rif_to_lif_group_map_rif_urpf_mode_get_cb)(
    int unit, int rif_urpf_mode_idx_0, uint8 *rif_urpf_mode);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_rif_to_lif_group_map_rif_urpf_mode_alloc */
typedef int (*sw_state_dpp_soc_arad_pp_rif_to_lif_group_map_rif_urpf_mode_alloc_cb)(
    int unit, int nof_instances_to_alloc);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_rif_to_lif_group_map_rif_urpf_mode_is_allocated */
typedef int (*sw_state_dpp_soc_arad_pp_rif_to_lif_group_map_rif_urpf_mode_is_allocated_cb)(
    int unit, uint8 *is_allocated);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_rif_to_lif_group_map_rif_urpf_mode_free */
typedef int (*sw_state_dpp_soc_arad_pp_rif_to_lif_group_map_rif_urpf_mode_free_cb)(
    int unit);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_rif_to_lif_group_map_rif_urpf_mode_verify */
typedef int (*sw_state_dpp_soc_arad_pp_rif_to_lif_group_map_rif_urpf_mode_verify_cb)(
    int unit, int rif_urpf_mode_idx_0);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

/*********************************** access calbacks struct ****************************************/
/* this set of structs, rooted at 'sw_state_cbs_t' define the access layer for the entire SW state.*/
/* use this tree to alloc/free/set/get fields in the sw state rooted at 'sw_state_t'.              */
/* NOTE: 'sw_state_t' data should not be accessed directly.                                        */
/***************************************************************************************************/

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
typedef struct sw_state_dpp_soc_arad_pp_rif_to_lif_group_map_rif_urpf_mode_cbs_s {
    sw_state_dpp_soc_arad_pp_rif_to_lif_group_map_rif_urpf_mode_set_cb set;
    sw_state_dpp_soc_arad_pp_rif_to_lif_group_map_rif_urpf_mode_get_cb get;
    sw_state_dpp_soc_arad_pp_rif_to_lif_group_map_rif_urpf_mode_alloc_cb alloc;
    sw_state_dpp_soc_arad_pp_rif_to_lif_group_map_rif_urpf_mode_is_allocated_cb is_allocated;
    sw_state_dpp_soc_arad_pp_rif_to_lif_group_map_rif_urpf_mode_free_cb free;
    sw_state_dpp_soc_arad_pp_rif_to_lif_group_map_rif_urpf_mode_verify_cb verify;
} sw_state_dpp_soc_arad_pp_rif_to_lif_group_map_rif_urpf_mode_cbs_t;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
typedef struct sw_state_dpp_soc_arad_pp_rif_to_lif_group_map_cbs_s {
    sw_state_dpp_soc_arad_pp_rif_to_lif_group_map_alloc_cb alloc;
    sw_state_dpp_soc_arad_pp_rif_to_lif_group_map_is_allocated_cb is_allocated;
    sw_state_dpp_soc_arad_pp_rif_to_lif_group_map_free_cb free;
    sw_state_dpp_soc_arad_pp_rif_to_lif_group_map_verify_cb verify;
    sw_state_dpp_soc_arad_pp_rif_to_lif_group_map_rif_urpf_mode_cbs_t rif_urpf_mode;
} sw_state_dpp_soc_arad_pp_rif_to_lif_group_map_cbs_t;

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

int sw_state_dpp_soc_arad_pp_rif_to_lif_group_map_access_cb_init(int unit);

#endif /* _SHR_SW_STATE_DPP_SOC_ARAD_PP_RIF_TO_LIF_GROUP_MAP_ACCESS_H_ */
