/* $Id: $
 * 
 * $Copyright: (c) 2016 Broadcom.
 * Broadcom Proprietary and Confidential. All rights reserved.$
 * 
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated.
 * Edits to this file will be lost when it is regenerated.
 */

#include <sal/core/libc.h>
#include <shared/swstate/sw_state.h>
#include <shared/error.h>
#include <shared/swstate/sw_state_defs.h>
#include <shared/bsl.h>
#include <shared/swstate/sw_state_dump.h>
#include <shared/swstate/diagnostic/sw_state_diagnostic.h>
#include <shared/swstate/diagnostic/sw_state_dpp_soc_arad_pp_vrrp_info_diagnostic.h>

#ifdef BCM_WARM_BOOT_API_TEST
#ifdef _ERR_MSG_MODULE_NAME
    #error "_ERR_MSG_MODULE_NAME redefined"
#endif

#define _ERR_MSG_MODULE_NAME BSL_LS_SHARED_SWSTATE

extern shr_sw_state_t *sw_state[BCM_MAX_NUM_UNITS];

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_soc_arad_pp_vrrp_info_dump(int unit, int pp_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    {
        uint32 j0, J0;
        sw_state_get_nof_elements(unit, sw_state[unit]->dpp.soc.arad.pp->vrrp_info, sizeof(*sw_state[unit]->dpp.soc.arad.pp->vrrp_info), &j0 ,&J0);
        for (; j0 < J0; j0++) {
            shr_sw_state_dump_update_current_idx(unit, j0);
            sw_state_diagnostic[unit].dpp.soc.arad.pp.vrrp_info.vrrp_mac_use_bit_map.dump(unit, pp_idx_0, j0);
        }
        shr_sw_state_dump_end_of_stride(unit);
    }
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_soc_arad_pp_vrrp_info_vrrp_mac_use_bit_map_dump(int unit, int pp_idx_0, int vrrp_info_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    {
        int i0;
        i0 = shr_sw_state_dump_check_all_the_same(unit, sw_state[unit]->dpp.soc.arad.pp->vrrp_info->vrrp_mac_use_bit_map
            , sizeof(*sw_state[unit]->dpp.soc.arad.pp->vrrp_info->vrrp_mac_use_bit_map), ARAD_PP_VRRP_NOF_MAC_ADDRESSES/16) ? ARAD_PP_VRRP_NOF_MAC_ADDRESSES/16 - 1 : 0;
        for (; i0 < ARAD_PP_VRRP_NOF_MAC_ADDRESSES/16; i0++) {
            shr_sw_state_dump_update_current_idx(unit, i0);
            SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.soc.arad.pp->vrrp_info->vrrp_mac_use_bit_map[i0],
                "sw_state[%d]->dpp.soc.arad.pp->vrrp_info->vrrp_mac_use_bit_map[%d]: ", unit, i0);
        }
        shr_sw_state_dump_end_of_stride(unit);
    }
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 


int
sw_state_dpp_soc_arad_pp_vrrp_info_diagnostic_cb_init(int unit){
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.soc.arad.pp.vrrp_info.dump = sw_state_dpp_soc_arad_pp_vrrp_info_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.soc.arad.pp.vrrp_info.vrrp_mac_use_bit_map.dump = sw_state_dpp_soc_arad_pp_vrrp_info_vrrp_mac_use_bit_map_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
    return _SHR_E_NONE;
}

#undef _ERR_MSG_MODULE_NAME
#endif /* BCM_WARM_BOOT_API_TEST */
