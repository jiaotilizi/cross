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

#ifndef _SHR_SW_STATE_DPP_SOC_ARAD_PP_IPV4_INFO_ACCESS_H_
#define _SHR_SW_STATE_DPP_SOC_ARAD_PP_IPV4_INFO_ACCESS_H_

/********************************* access calbacks definitions *************************************/
/* this set of callbacks, are the callbacks used in the access calbacks struct 'sw_state_cbs_t' to */
/* access the data in 'sw_state_t'.                                                                */
/* the calbacks are inserted into the access struct by 'sw_state_access_cb_init'.                  */
/***************************************************************************************************/

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_set */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_set_cb)(
    int unit, CONST ARAD_PP_IPV4_INFO *ipv4_info);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_get */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_get_cb)(
    int unit, ARAD_PP_IPV4_INFO *ipv4_info);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_alloc */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_alloc_cb)(
    int unit);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_is_allocated */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_is_allocated_cb)(
    int unit, uint8 *is_allocated);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_free */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_free_cb)(
    int unit);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_verify */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_verify_cb)(
    int unit);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_default_fec_set */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_default_fec_set_cb)(
    int unit, uint32 default_fec);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_default_fec_get */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_default_fec_get_cb)(
    int unit, uint32 *default_fec);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_default_fec_verify */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_default_fec_verify_cb)(
    int unit);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_nof_lpm_entries_in_lpm_set */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_nof_lpm_entries_in_lpm_set_cb)(
    int unit, uint32 nof_lpm_entries_in_lpm);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_nof_lpm_entries_in_lpm_get */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_nof_lpm_entries_in_lpm_get_cb)(
    int unit, uint32 *nof_lpm_entries_in_lpm);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_nof_lpm_entries_in_lpm_verify */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_nof_lpm_entries_in_lpm_verify_cb)(
    int unit);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_nof_vrfs_set */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_nof_vrfs_set_cb)(
    int unit, uint32 nof_vrfs);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_nof_vrfs_get */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_nof_vrfs_get_cb)(
    int unit, uint32 *nof_vrfs);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_nof_vrfs_verify */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_nof_vrfs_verify_cb)(
    int unit);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_set */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_set_cb)(
    int unit, int _bit_num);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_clear */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_clear_cb)(
    int unit, int _bit_num);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_get */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_get_cb)(
    int unit, int _bit_num, uint8* result);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_read */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_read_cb)(
    int unit, int sw_state_bmp_first, int result_first, int _range, SHR_BITDCL *result);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_write */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_write_cb)(
    int unit, int sw_state_bmp_first, int input_bmp_first, int _range, SHR_BITDCL *input_bmp);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_and */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_and_cb)(
    int unit, int _first, int _count, SHR_BITDCL *input_bmp);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_or */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_or_cb)(
    int unit, int _first, int _count, SHR_BITDCL *input_bmp);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_xor */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_xor_cb)(
    int unit, int _first, int _count, SHR_BITDCL *input_bmp);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_remove */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_remove_cb)(
    int unit, int _first, int _count, SHR_BITDCL *input_bmp);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_negate */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_negate_cb)(
    int unit, int _first, int _count);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_clear */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_clear_cb)(
    int unit, int _first, int _count);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_set */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_set_cb)(
    int unit, int _first, int _count);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_null */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_null_cb)(
    int unit, int _first, int _count, uint8 *result);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_test */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_test_cb)(
    int unit, int _first, int _count, uint8 *result);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_eq */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_eq_cb)(
    int unit, SHR_BITDCL *input_bmp, int _first, int _count, uint8 *result);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_count */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_count_cb)(
    int unit, int _first, int _range, int *result);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_verify */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_verify_cb)(
    int unit, int vrf_modified_bitmask_idx_0);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_cache_modified_set */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_cache_modified_set_cb)(
    int unit, uint8 cache_modified);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_cache_modified_get */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_cache_modified_get_cb)(
    int unit, uint8 *cache_modified);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_cache_modified_verify */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_cache_modified_verify_cb)(
    int unit);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_cache_mode_set */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_cache_mode_set_cb)(
    int unit, uint32 cache_mode);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_cache_mode_get */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_cache_mode_get_cb)(
    int unit, uint32 *cache_mode);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_cache_mode_verify */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_cache_mode_verify_cb)(
    int unit);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
#ifdef SOC_SAND_DEBUG
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_lem_add_fail_set */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_lem_add_fail_set_cb)(
    int unit, uint8 lem_add_fail);
#endif /* SOC_SAND_DEBUG*/ 
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
#ifdef SOC_SAND_DEBUG
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_lem_add_fail_get */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_lem_add_fail_get_cb)(
    int unit, uint8 *lem_add_fail);
#endif /* SOC_SAND_DEBUG*/ 
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
#ifdef SOC_SAND_DEBUG
/* implemented by: sw_state_dpp_soc_arad_pp_ipv4_info_lem_add_fail_verify */
typedef int (*sw_state_dpp_soc_arad_pp_ipv4_info_lem_add_fail_verify_cb)(
    int unit);
#endif /* SOC_SAND_DEBUG*/ 
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

/*********************************** access calbacks struct ****************************************/
/* this set of structs, rooted at 'sw_state_cbs_t' define the access layer for the entire SW state.*/
/* use this tree to alloc/free/set/get fields in the sw state rooted at 'sw_state_t'.              */
/* NOTE: 'sw_state_t' data should not be accessed directly.                                        */
/***************************************************************************************************/

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
typedef struct sw_state_dpp_soc_arad_pp_ipv4_info_default_fec_cbs_s {
    sw_state_dpp_soc_arad_pp_ipv4_info_default_fec_set_cb set;
    sw_state_dpp_soc_arad_pp_ipv4_info_default_fec_get_cb get;
    sw_state_dpp_soc_arad_pp_ipv4_info_default_fec_verify_cb verify;
} sw_state_dpp_soc_arad_pp_ipv4_info_default_fec_cbs_t;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
typedef struct sw_state_dpp_soc_arad_pp_ipv4_info_nof_lpm_entries_in_lpm_cbs_s {
    sw_state_dpp_soc_arad_pp_ipv4_info_nof_lpm_entries_in_lpm_set_cb set;
    sw_state_dpp_soc_arad_pp_ipv4_info_nof_lpm_entries_in_lpm_get_cb get;
    sw_state_dpp_soc_arad_pp_ipv4_info_nof_lpm_entries_in_lpm_verify_cb verify;
} sw_state_dpp_soc_arad_pp_ipv4_info_nof_lpm_entries_in_lpm_cbs_t;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
typedef struct sw_state_dpp_soc_arad_pp_ipv4_info_nof_vrfs_cbs_s {
    sw_state_dpp_soc_arad_pp_ipv4_info_nof_vrfs_set_cb set;
    sw_state_dpp_soc_arad_pp_ipv4_info_nof_vrfs_get_cb get;
    sw_state_dpp_soc_arad_pp_ipv4_info_nof_vrfs_verify_cb verify;
} sw_state_dpp_soc_arad_pp_ipv4_info_nof_vrfs_cbs_t;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
typedef struct sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_cbs_s {
    sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_set_cb bit_set;
    sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_clear_cb bit_clear;
    sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_get_cb bit_get;
    sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_read_cb bit_range_read;
    sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_write_cb bit_range_write;
    sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_and_cb bit_range_and;
    sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_or_cb bit_range_or;
    sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_xor_cb bit_range_xor;
    sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_remove_cb bit_range_remove;
    sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_negate_cb bit_range_negate;
    sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_clear_cb bit_range_clear;
    sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_set_cb bit_range_set;
    sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_null_cb bit_range_null;
    sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_test_cb bit_range_test;
    sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_eq_cb bit_range_eq;
    sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_bit_range_count_cb bit_range_count;
    sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_verify_cb verify;
} sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_cbs_t;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
typedef struct sw_state_dpp_soc_arad_pp_ipv4_info_cache_modified_cbs_s {
    sw_state_dpp_soc_arad_pp_ipv4_info_cache_modified_set_cb set;
    sw_state_dpp_soc_arad_pp_ipv4_info_cache_modified_get_cb get;
    sw_state_dpp_soc_arad_pp_ipv4_info_cache_modified_verify_cb verify;
} sw_state_dpp_soc_arad_pp_ipv4_info_cache_modified_cbs_t;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
typedef struct sw_state_dpp_soc_arad_pp_ipv4_info_cache_mode_cbs_s {
    sw_state_dpp_soc_arad_pp_ipv4_info_cache_mode_set_cb set;
    sw_state_dpp_soc_arad_pp_ipv4_info_cache_mode_get_cb get;
    sw_state_dpp_soc_arad_pp_ipv4_info_cache_mode_verify_cb verify;
} sw_state_dpp_soc_arad_pp_ipv4_info_cache_mode_cbs_t;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
#ifdef SOC_SAND_DEBUG
typedef struct sw_state_dpp_soc_arad_pp_ipv4_info_lem_add_fail_cbs_s {
#ifdef SOC_SAND_DEBUG
    sw_state_dpp_soc_arad_pp_ipv4_info_lem_add_fail_set_cb set;
#endif /* SOC_SAND_DEBUG*/ 
#ifdef SOC_SAND_DEBUG
    sw_state_dpp_soc_arad_pp_ipv4_info_lem_add_fail_get_cb get;
#endif /* SOC_SAND_DEBUG*/ 
#ifdef SOC_SAND_DEBUG
    sw_state_dpp_soc_arad_pp_ipv4_info_lem_add_fail_verify_cb verify;
#endif /* SOC_SAND_DEBUG*/ 
} sw_state_dpp_soc_arad_pp_ipv4_info_lem_add_fail_cbs_t;
#endif /* SOC_SAND_DEBUG*/ 
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
typedef struct sw_state_dpp_soc_arad_pp_ipv4_info_cbs_s {
    sw_state_dpp_soc_arad_pp_ipv4_info_set_cb set;
    sw_state_dpp_soc_arad_pp_ipv4_info_get_cb get;
    sw_state_dpp_soc_arad_pp_ipv4_info_alloc_cb alloc;
    sw_state_dpp_soc_arad_pp_ipv4_info_is_allocated_cb is_allocated;
    sw_state_dpp_soc_arad_pp_ipv4_info_free_cb free;
    sw_state_dpp_soc_arad_pp_ipv4_info_verify_cb verify;
    sw_state_dpp_soc_arad_pp_ipv4_info_default_fec_cbs_t default_fec;
    sw_state_dpp_soc_arad_pp_ipv4_info_nof_lpm_entries_in_lpm_cbs_t nof_lpm_entries_in_lpm;
    sw_state_dpp_soc_arad_pp_ipv4_info_nof_vrfs_cbs_t nof_vrfs;
    sw_state_dpp_soc_arad_pp_ipv4_info_vrf_modified_bitmask_cbs_t vrf_modified_bitmask;
    sw_state_dpp_soc_arad_pp_ipv4_info_cache_modified_cbs_t cache_modified;
    sw_state_dpp_soc_arad_pp_ipv4_info_cache_mode_cbs_t cache_mode;
#ifdef SOC_SAND_DEBUG
    sw_state_dpp_soc_arad_pp_ipv4_info_lem_add_fail_cbs_t lem_add_fail;
#endif /* SOC_SAND_DEBUG*/ 
} sw_state_dpp_soc_arad_pp_ipv4_info_cbs_t;

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

int sw_state_dpp_soc_arad_pp_ipv4_info_access_cb_init(int unit);

#endif /* _SHR_SW_STATE_DPP_SOC_ARAD_PP_IPV4_INFO_ACCESS_H_ */
