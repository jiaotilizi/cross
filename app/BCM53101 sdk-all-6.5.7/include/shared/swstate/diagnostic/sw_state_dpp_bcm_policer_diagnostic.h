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

#ifndef _SHR_SW_STATE_DPP_BCM_POLICER_DIAGNOSTIC_H_
#define _SHR_SW_STATE_DPP_BCM_POLICER_DIAGNOSTIC_H_

#ifdef BCM_WARM_BOOT_API_TEST
/********************************* diagnostic calbacks definitions *************************************/
/* this set of callbacks, are the callbacks used in the diagnostic calbacks struct 'sw_state_cbs_t' to */
/* access the data in 'sw_state_t'.                                                                */
/* the calbacks are inserted into the diagnostic struct by 'sw_state_diagnostic_cb_init'.                  */
/***************************************************************************************************/

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_bcm_policer_dump */
typedef int (*sw_state_dpp_bcm_policer_dump_cb)(
    int unit);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_bcm_policer_policer_group_dump */
typedef int (*sw_state_dpp_bcm_policer_policer_group_dump_cb)(
    int unit, int policer_idx_0);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_bcm_policer_policer_group_mode_dump */
typedef int (*sw_state_dpp_bcm_policer_policer_group_mode_dump_cb)(
    int unit, int policer_idx_0, int policer_group_idx_0);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

/*********************************** diagnostic calbacks struct ****************************************/
/* this set of structs, rooted at 'sw_state_cbs_t' define the diagnostic layer for the entire SW state.*/
/* use this tree to dump fields in the sw state rooted at 'sw_state_t'.              */
/* NOTE: 'sw_state_t' data should not be accessed directly.                                        */
/***************************************************************************************************/

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
typedef struct sw_state_dpp_bcm_policer_policer_group_mode_diagnostic_cbs_s {
    sw_state_dpp_bcm_policer_policer_group_mode_dump_cb dump;
} sw_state_dpp_bcm_policer_policer_group_mode_diagnostic_cbs_t;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
typedef struct sw_state_dpp_bcm_policer_policer_group_diagnostic_cbs_s {
    sw_state_dpp_bcm_policer_policer_group_dump_cb dump;
    sw_state_dpp_bcm_policer_policer_group_mode_diagnostic_cbs_t mode;
} sw_state_dpp_bcm_policer_policer_group_diagnostic_cbs_t;

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
typedef struct sw_state_dpp_bcm_policer_diagnostic_cbs_s {
#if defined(BCM_PETRA_SUPPORT)
    sw_state_dpp_bcm_policer_dump_cb dump;
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
    sw_state_dpp_bcm_policer_policer_group_diagnostic_cbs_t policer_group;
} sw_state_dpp_bcm_policer_diagnostic_cbs_t;

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

int sw_state_dpp_bcm_policer_diagnostic_cb_init(int unit);

#endif /* BCM_WARM_BOOT_API_TEST */

#endif /* _SHR_SW_STATE_DPP_BCM_POLICER_DIAGNOSTIC_H_ */
