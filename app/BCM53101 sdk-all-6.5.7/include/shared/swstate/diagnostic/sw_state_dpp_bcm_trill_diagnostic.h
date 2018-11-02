/* $Id: $
 * 
 * $Copyright: (c) 2016 Broadcom.
 * Broadcom Proprietary and Confidential. All rights reserved.$
 * 
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated.
 * Edits to this file will be lost when it is regenerated.
 * search for 'sw_state_diagnostic_cbs_t' for the root of the struct
 */

#ifndef _SHR_SW_STATE_DPP_BCM_TRILL_DIAGNOSTIC_H_
#define _SHR_SW_STATE_DPP_BCM_TRILL_DIAGNOSTIC_H_

#ifdef BCM_WARM_BOOT_API_TEST
/********************************* diagnostic calbacks definitions *************************************/
/* this set of callbacks, are the callbacks used in the diagnostic calbacks struct 'sw_state_cbs_t' to */
/* access the data in 'sw_state_t'.                                                                */
/* the calbacks are inserted into the diagnostic struct by 'sw_state_diagnostic_cb_init'.                  */
/***************************************************************************************************/

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_bcm_trill_dump */
typedef int (*sw_state_dpp_bcm_trill_dump_cb)(
    int unit);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_bcm_trill_init_dump */
typedef int (*sw_state_dpp_bcm_trill_init_dump_cb)(
    int unit, int trill_idx_0);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_bcm_trill_mask_set_dump */
typedef int (*sw_state_dpp_bcm_trill_mask_set_dump_cb)(
    int unit, int trill_idx_0);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_bcm_trill_trill_out_ac_dump */
typedef int (*sw_state_dpp_bcm_trill_trill_out_ac_dump_cb)(
    int unit, int trill_idx_0);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_bcm_trill_trill_local_in_lif_dump */
typedef int (*sw_state_dpp_bcm_trill_trill_local_in_lif_dump_cb)(
    int unit, int trill_idx_0);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_bcm_trill_trill_global_in_lif_dump */
typedef int (*sw_state_dpp_bcm_trill_trill_global_in_lif_dump_cb)(
    int unit, int trill_idx_0);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_bcm_trill_last_used_id_dump */
typedef int (*sw_state_dpp_bcm_trill_last_used_id_dump_cb)(
    int unit, int trill_idx_0);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_bcm_trill_trill_ports_dump */
typedef int (*sw_state_dpp_bcm_trill_trill_ports_dump_cb)(
    int unit, int trill_idx_0);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_bcm_trill_trill_ports_allocated_cnt_dump */
typedef int (*sw_state_dpp_bcm_trill_trill_ports_allocated_cnt_dump_cb)(
    int unit, int trill_idx_0, int trill_ports_idx_0);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_bcm_trill_trill_ports_port_cnt_dump */
typedef int (*sw_state_dpp_bcm_trill_trill_ports_port_cnt_dump_cb)(
    int unit, int trill_idx_0, int trill_ports_idx_0);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_bcm_trill_trill_ports_ports_dump */
typedef int (*sw_state_dpp_bcm_trill_trill_ports_ports_dump_cb)(
    int unit, int trill_idx_0, int trill_ports_idx_0);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_bcm_trill_mc_trill_route_info_db_htb_handle_dump */
typedef int (*sw_state_dpp_bcm_trill_mc_trill_route_info_db_htb_handle_dump_cb)(
    int unit, int trill_idx_0);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_bcm_trill_mc_trill_root_src_db_htb_handle_dump */
typedef int (*sw_state_dpp_bcm_trill_mc_trill_root_src_db_htb_handle_dump_cb)(
    int unit, int trill_idx_0);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

/*********************************** diagnostic calbacks struct ****************************************/
/* this set of structs, rooted at 'sw_state_cbs_t' define the diagnostic layer for the entire SW state.*/
/* use this tree to dump fields in the sw state rooted at 'sw_state_t'.              */
/* NOTE: 'sw_state_t' data should not be accessed directly.                                        */
/***************************************************************************************************/

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
typedef struct sw_state_dpp_bcm_trill_init_diagnostic_cbs_s {
    sw_state_dpp_bcm_trill_init_dump_cb dump;
} sw_state_dpp_bcm_trill_init_diagnostic_cbs_t;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
typedef struct sw_state_dpp_bcm_trill_mask_set_diagnostic_cbs_s {
    sw_state_dpp_bcm_trill_mask_set_dump_cb dump;
} sw_state_dpp_bcm_trill_mask_set_diagnostic_cbs_t;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
typedef struct sw_state_dpp_bcm_trill_trill_out_ac_diagnostic_cbs_s {
    sw_state_dpp_bcm_trill_trill_out_ac_dump_cb dump;
} sw_state_dpp_bcm_trill_trill_out_ac_diagnostic_cbs_t;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
typedef struct sw_state_dpp_bcm_trill_trill_local_in_lif_diagnostic_cbs_s {
    sw_state_dpp_bcm_trill_trill_local_in_lif_dump_cb dump;
} sw_state_dpp_bcm_trill_trill_local_in_lif_diagnostic_cbs_t;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
typedef struct sw_state_dpp_bcm_trill_trill_global_in_lif_diagnostic_cbs_s {
    sw_state_dpp_bcm_trill_trill_global_in_lif_dump_cb dump;
} sw_state_dpp_bcm_trill_trill_global_in_lif_diagnostic_cbs_t;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
typedef struct sw_state_dpp_bcm_trill_last_used_id_diagnostic_cbs_s {
    sw_state_dpp_bcm_trill_last_used_id_dump_cb dump;
} sw_state_dpp_bcm_trill_last_used_id_diagnostic_cbs_t;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
typedef struct sw_state_dpp_bcm_trill_trill_ports_allocated_cnt_diagnostic_cbs_s {
    sw_state_dpp_bcm_trill_trill_ports_allocated_cnt_dump_cb dump;
} sw_state_dpp_bcm_trill_trill_ports_allocated_cnt_diagnostic_cbs_t;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
typedef struct sw_state_dpp_bcm_trill_trill_ports_port_cnt_diagnostic_cbs_s {
    sw_state_dpp_bcm_trill_trill_ports_port_cnt_dump_cb dump;
} sw_state_dpp_bcm_trill_trill_ports_port_cnt_diagnostic_cbs_t;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
typedef struct sw_state_dpp_bcm_trill_trill_ports_ports_diagnostic_cbs_s {
    sw_state_dpp_bcm_trill_trill_ports_ports_dump_cb dump;
} sw_state_dpp_bcm_trill_trill_ports_ports_diagnostic_cbs_t;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
typedef struct sw_state_dpp_bcm_trill_trill_ports_diagnostic_cbs_s {
    sw_state_dpp_bcm_trill_trill_ports_dump_cb dump;
    sw_state_dpp_bcm_trill_trill_ports_allocated_cnt_diagnostic_cbs_t allocated_cnt;
    sw_state_dpp_bcm_trill_trill_ports_port_cnt_diagnostic_cbs_t port_cnt;
    sw_state_dpp_bcm_trill_trill_ports_ports_diagnostic_cbs_t ports;
} sw_state_dpp_bcm_trill_trill_ports_diagnostic_cbs_t;

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
typedef struct sw_state_dpp_bcm_trill_mc_trill_route_info_db_htb_handle_diagnostic_cbs_s {
    sw_state_dpp_bcm_trill_mc_trill_route_info_db_htb_handle_dump_cb dump;
} sw_state_dpp_bcm_trill_mc_trill_route_info_db_htb_handle_diagnostic_cbs_t;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
typedef struct sw_state_dpp_bcm_trill_mc_trill_root_src_db_htb_handle_diagnostic_cbs_s {
    sw_state_dpp_bcm_trill_mc_trill_root_src_db_htb_handle_dump_cb dump;
} sw_state_dpp_bcm_trill_mc_trill_root_src_db_htb_handle_diagnostic_cbs_t;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
typedef struct sw_state_dpp_bcm_trill_diagnostic_cbs_s {
#if defined(BCM_PETRA_SUPPORT)
    sw_state_dpp_bcm_trill_dump_cb dump;
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
    sw_state_dpp_bcm_trill_init_diagnostic_cbs_t init;
    sw_state_dpp_bcm_trill_mask_set_diagnostic_cbs_t mask_set;
    sw_state_dpp_bcm_trill_trill_out_ac_diagnostic_cbs_t trill_out_ac;
    sw_state_dpp_bcm_trill_trill_local_in_lif_diagnostic_cbs_t trill_local_in_lif;
    sw_state_dpp_bcm_trill_trill_global_in_lif_diagnostic_cbs_t trill_global_in_lif;
    sw_state_dpp_bcm_trill_last_used_id_diagnostic_cbs_t last_used_id;
    sw_state_dpp_bcm_trill_trill_ports_diagnostic_cbs_t trill_ports;
    sw_state_dpp_bcm_trill_mc_trill_route_info_db_htb_handle_diagnostic_cbs_t mc_trill_route_info_db_htb_handle;
    sw_state_dpp_bcm_trill_mc_trill_root_src_db_htb_handle_diagnostic_cbs_t mc_trill_root_src_db_htb_handle;
} sw_state_dpp_bcm_trill_diagnostic_cbs_t;

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

int sw_state_dpp_bcm_trill_diagnostic_cb_init(int unit);

#endif /* BCM_WARM_BOOT_API_TEST */

#endif /* _SHR_SW_STATE_DPP_BCM_TRILL_DIAGNOSTIC_H_ */
