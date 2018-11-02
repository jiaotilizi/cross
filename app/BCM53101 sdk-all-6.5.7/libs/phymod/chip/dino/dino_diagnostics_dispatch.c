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

#include <phymod/phymod.h>
#include <phymod/phymod_diagnostics.h>
#include <phymod/phymod_diagnostics_dispatch.h>

#ifdef PHYMOD_DINO_SUPPORT

#include <phymod/chip/dino_diagnostics.h>


__phymod_diagnostics__dispatch__t__ phymod_diagnostics_dino_diagnostics_driver = {

    NULL, /* phymod_phy_rx_slicer_position_set */
    NULL, /* phymod_phy_rx_slicer_position_get */
    NULL, /* phymod_phy_rx_slicer_position_max_get */
    dino_phy_prbs_config_set,
    dino_phy_prbs_config_get,
    dino_phy_prbs_enable_set,
    dino_phy_prbs_enable_get,
    dino_phy_prbs_status_get,
    NULL, /* phymod_phy_pattern_config_set */
    NULL, /* phymod_phy_pattern_config_get */
    NULL, /* phymod_phy_pattern_enable_set */
    NULL, /* phymod_phy_pattern_enable_get */
    NULL, /* phymod_core_diagnostics_get */
    dino_phy_diagnostics_get,
    dino_phy_pmd_info_dump,
    NULL, /* phymod_phy_pcs_info_dump */
    dino_phy_eyescan_run,
    dino_phy_link_mon_enable_set,
    dino_phy_link_mon_enable_get,
    dino_phy_link_mon_status_get,
    NULL, /* phymod_phy_fec_correctable_counter_get */
    NULL, /* phymod_phy_fec_uncorrectable_counter_get */
};

#endif /* PHYMOD_DINO_SUPPORT */
