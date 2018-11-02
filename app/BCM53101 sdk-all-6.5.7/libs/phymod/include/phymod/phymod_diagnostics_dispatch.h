/*
 *         
 * $Id: phymod.xml,v 1.1.2.5 Broadcom SDK $
 * 
 * $Copyright: (c) 2016 Broadcom.
 * Broadcom Proprietary and Confidential. All rights reserved.$
 *         
 *     
 * DO NOT EDIT THIS FILE!
 *
 */

#ifndef _PHYMOD_DIAGNOSTICS_DISPATCH_H__H_
#define _PHYMOD_DIAGNOSTICS_DISPATCH_H__H_

#include <phymod/phymod_definitions.h>
#include <phymod/phymod_diagnostics.h>

typedef int (*__dispatch__phymod_phy_rx_slicer_position_set_f)(const phymod_phy_access_t* phy, uint32_t flags, const phymod_slicer_position_t* position);
typedef int (*__dispatch__phymod_phy_rx_slicer_position_get_f)(const phymod_phy_access_t* phy, uint32_t flags, phymod_slicer_position_t* position);
typedef int (*__dispatch__phymod_phy_rx_slicer_position_max_get_f)(const phymod_phy_access_t* phy, uint32_t flags, const phymod_slicer_position_t* position_min, const phymod_slicer_position_t* position_max);
typedef int (*__dispatch__phymod_phy_prbs_config_set_f)(const phymod_phy_access_t* phy, uint32_t flags , const phymod_prbs_t* prbs);
typedef int (*__dispatch__phymod_phy_prbs_config_get_f)(const phymod_phy_access_t* phy, uint32_t flags , phymod_prbs_t* prbs);
typedef int (*__dispatch__phymod_phy_prbs_enable_set_f)(const phymod_phy_access_t* phy, uint32_t flags , uint32_t enable);
typedef int (*__dispatch__phymod_phy_prbs_enable_get_f)(const phymod_phy_access_t* phy, uint32_t flags , uint32_t* enable);
typedef int (*__dispatch__phymod_phy_prbs_status_get_f)(const phymod_phy_access_t* phy, uint32_t flags, phymod_prbs_status_t* prbs_status);
typedef int (*__dispatch__phymod_phy_pattern_config_set_f)(const phymod_phy_access_t* phy, const phymod_pattern_t* pattern);
typedef int (*__dispatch__phymod_phy_pattern_config_get_f)(const phymod_phy_access_t* phy, phymod_pattern_t* pattern);
typedef int (*__dispatch__phymod_phy_pattern_enable_set_f)(const phymod_phy_access_t* phy, uint32_t enable, const phymod_pattern_t* pattern);
typedef int (*__dispatch__phymod_phy_pattern_enable_get_f)(const phymod_phy_access_t* phy, uint32_t* enable);
typedef int (*__dispatch__phymod_core_diagnostics_get_f)(const phymod_core_access_t* core, phymod_core_diagnostics_t* diag);
typedef int (*__dispatch__phymod_phy_diagnostics_get_f)(const phymod_phy_access_t* phy, phymod_phy_diagnostics_t* diag);
typedef int (*__dispatch__phymod_phy_pmd_info_dump_f)(const phymod_phy_access_t* phy, char* type);
typedef int (*__dispatch__phymod_phy_pcs_info_dump_f)(const phymod_phy_access_t* phy, char* type);
typedef int (*__dispatch__phymod_phy_eyescan_run_f)(const phymod_phy_access_t* phy, uint32_t flags, phymod_eyescan_mode_t mode, const phymod_phy_eyescan_options_t* eyescan_options);
typedef int (*__dispatch__phymod_phy_link_mon_enable_set_f)(const phymod_phy_access_t* phy, phymod_link_monitor_mode_t link_mon_mode, uint32_t enable);
typedef int (*__dispatch__phymod_phy_link_mon_enable_get_f)(const phymod_phy_access_t* phy, phymod_link_monitor_mode_t link_mon_mode, uint32_t* enable);
typedef int (*__dispatch__phymod_phy_link_mon_status_get_f)(const phymod_phy_access_t* phy, uint32_t* lock_status, uint32_t* lock_lost_lh, uint32_t* error_count);
typedef int (*__dispatch__phymod_phy_fec_correctable_counter_get_f)(const phymod_phy_access_t* phy, uint32_t* count);
typedef int (*__dispatch__phymod_phy_fec_uncorrectable_counter_get_f)(const phymod_phy_access_t* phy, uint32_t* count);

typedef struct __phymod_diagnostics__dispatch__s__ {
    __dispatch__phymod_phy_rx_slicer_position_set_f                                  f_phymod_phy_rx_slicer_position_set;
    __dispatch__phymod_phy_rx_slicer_position_get_f                                  f_phymod_phy_rx_slicer_position_get;
    __dispatch__phymod_phy_rx_slicer_position_max_get_f                              f_phymod_phy_rx_slicer_position_max_get;
    __dispatch__phymod_phy_prbs_config_set_f                                         f_phymod_phy_prbs_config_set;
    __dispatch__phymod_phy_prbs_config_get_f                                         f_phymod_phy_prbs_config_get;
    __dispatch__phymod_phy_prbs_enable_set_f                                         f_phymod_phy_prbs_enable_set;
    __dispatch__phymod_phy_prbs_enable_get_f                                         f_phymod_phy_prbs_enable_get;
    __dispatch__phymod_phy_prbs_status_get_f                                         f_phymod_phy_prbs_status_get;
    __dispatch__phymod_phy_pattern_config_set_f                                      f_phymod_phy_pattern_config_set;
    __dispatch__phymod_phy_pattern_config_get_f                                      f_phymod_phy_pattern_config_get;
    __dispatch__phymod_phy_pattern_enable_set_f                                      f_phymod_phy_pattern_enable_set;
    __dispatch__phymod_phy_pattern_enable_get_f                                      f_phymod_phy_pattern_enable_get;
    __dispatch__phymod_core_diagnostics_get_f                                        f_phymod_core_diagnostics_get;
    __dispatch__phymod_phy_diagnostics_get_f                                         f_phymod_phy_diagnostics_get;
    __dispatch__phymod_phy_pmd_info_dump_f                                           f_phymod_phy_pmd_info_dump;
    __dispatch__phymod_phy_pcs_info_dump_f                                           f_phymod_phy_pcs_info_dump;
    __dispatch__phymod_phy_eyescan_run_f                                             f_phymod_phy_eyescan_run;
    __dispatch__phymod_phy_link_mon_enable_set_f                                     f_phymod_phy_link_mon_enable_set;
    __dispatch__phymod_phy_link_mon_enable_get_f                                     f_phymod_phy_link_mon_enable_get;
    __dispatch__phymod_phy_link_mon_status_get_f                                     f_phymod_phy_link_mon_status_get;
    __dispatch__phymod_phy_fec_correctable_counter_get_f                             f_phymod_phy_fec_correctable_counter_get;
    __dispatch__phymod_phy_fec_uncorrectable_counter_get_f                           f_phymod_phy_fec_uncorrectable_counter_get;
} __phymod_diagnostics__dispatch__t__;

extern __phymod_diagnostics__dispatch__t__* __phymod_diagnostics__dispatch__[phymodDispatchTypeCount];

#endif /*_PHYMOD_DIAGNOSTICS_DISPATCH_H_*/
