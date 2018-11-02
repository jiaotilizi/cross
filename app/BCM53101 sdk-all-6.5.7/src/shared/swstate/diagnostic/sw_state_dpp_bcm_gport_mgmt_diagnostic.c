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
#include <shared/swstate/diagnostic/sw_state_dpp_bcm_gport_mgmt_diagnostic.h>

#ifdef BCM_WARM_BOOT_API_TEST
#ifdef _ERR_MSG_MODULE_NAME
    #error "_ERR_MSG_MODULE_NAME redefined"
#endif

#define _ERR_MSG_MODULE_NAME BSL_LS_SHARED_SWSTATE

extern shr_sw_state_t *sw_state[BCM_MAX_NUM_UNITS];

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_bcm_gport_mgmt_dump(int unit){
    SW_STATE_INIT_FUNC_DEFS;
    {
        uint32 j0, J0;
        sw_state_get_nof_elements(unit, sw_state[unit]->dpp.bcm.gport_mgmt, sizeof(*sw_state[unit]->dpp.bcm.gport_mgmt), &j0 ,&J0);
        for (; j0 < J0; j0++) {
            shr_sw_state_dump_update_current_idx(unit, j0);
            sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.fec_remote_lif.dump(unit, j0);
            sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.bcm_dpp_sw_resources_fec_to_gport.dump(unit, j0);
            sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.outlif_info.dump(unit, j0);
            sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.inlif_info.dump(unit, j0);
            sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.vlan_port_db_htb_handle.dump(unit, j0);
            sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.trill_info_db_htb_handle.dump(unit, j0);
            sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.mc_trill_db_htb_handle.dump(unit, j0);
            sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.trill_vpn_db_htb_handle.dump(unit, j0);
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
int sw_state_dpp_bcm_gport_mgmt_fec_remote_lif_dump(int unit, int gport_mgmt_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    {
        uint32 j0, J0;
        sw_state_get_nof_elements(unit, sw_state[unit]->dpp.bcm.gport_mgmt->fec_remote_lif, sizeof(*sw_state[unit]->dpp.bcm.gport_mgmt->fec_remote_lif), &j0 ,&J0);
        for (; j0 < J0; j0++) {
            shr_sw_state_dump_update_current_idx(unit, j0);
            SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.bcm.gport_mgmt->fec_remote_lif[j0],
                "sw_state[%d]->dpp.bcm.gport_mgmt->fec_remote_lif[%d]: ", unit, j0);
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
int sw_state_dpp_bcm_gport_mgmt_bcm_dpp_sw_resources_fec_to_gport_dump(int unit, int gport_mgmt_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    {
        uint32 j0, J0;
        sw_state_get_nof_elements(unit, sw_state[unit]->dpp.bcm.gport_mgmt->bcm_dpp_sw_resources_fec_to_gport, sizeof(*sw_state[unit]->dpp.bcm.gport_mgmt->bcm_dpp_sw_resources_fec_to_gport), &j0 ,&J0);
        for (; j0 < J0; j0++) {
            shr_sw_state_dump_update_current_idx(unit, j0);
            SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.bcm.gport_mgmt->bcm_dpp_sw_resources_fec_to_gport[j0],
                "sw_state[%d]->dpp.bcm.gport_mgmt->bcm_dpp_sw_resources_fec_to_gport[%d]: ", unit, j0);
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
int sw_state_dpp_bcm_gport_mgmt_outlif_info_dump(int unit, int gport_mgmt_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    {
        uint32 j0, J0;
        sw_state_get_nof_elements(unit, sw_state[unit]->dpp.bcm.gport_mgmt->outlif_info, sizeof(*sw_state[unit]->dpp.bcm.gport_mgmt->outlif_info), &j0 ,&J0);
        for (; j0 < J0; j0++) {
            shr_sw_state_dump_update_current_idx(unit, j0);
            sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.outlif_info.lif_type.dump(unit, gport_mgmt_idx_0, j0);
            sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.outlif_info.flags.dump(unit, gport_mgmt_idx_0, j0);
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
int sw_state_dpp_bcm_gport_mgmt_outlif_info_lif_type_dump(int unit, int gport_mgmt_idx_0, int outlif_info_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.bcm.gport_mgmt->outlif_info[outlif_info_idx_0].lif_type,
        "sw_state[%d]->dpp.bcm.gport_mgmt->outlif_info[%d].lif_type: ", unit, outlif_info_idx_0);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_bcm_gport_mgmt_outlif_info_flags_dump(int unit, int gport_mgmt_idx_0, int outlif_info_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.bcm.gport_mgmt->outlif_info[outlif_info_idx_0].flags,
        "sw_state[%d]->dpp.bcm.gport_mgmt->outlif_info[%d].flags: ", unit, outlif_info_idx_0);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_bcm_gport_mgmt_inlif_info_dump(int unit, int gport_mgmt_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    {
        uint32 j0, J0;
        sw_state_get_nof_elements(unit, sw_state[unit]->dpp.bcm.gport_mgmt->inlif_info, sizeof(*sw_state[unit]->dpp.bcm.gport_mgmt->inlif_info), &j0 ,&J0);
        for (; j0 < J0; j0++) {
            shr_sw_state_dump_update_current_idx(unit, j0);
            sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.inlif_info.lif_type.dump(unit, gport_mgmt_idx_0, j0);
            sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.inlif_info.flags.dump(unit, gport_mgmt_idx_0, j0);
            sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.inlif_info.criteria.dump(unit, gport_mgmt_idx_0, j0);
            sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.inlif_info.port.dump(unit, gport_mgmt_idx_0, j0);
            sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.inlif_info.match1.dump(unit, gport_mgmt_idx_0, j0);
            sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.inlif_info.match2.dump(unit, gport_mgmt_idx_0, j0);
            sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.inlif_info.match_tunnel.dump(unit, gport_mgmt_idx_0, j0);
            sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.inlif_info.match_ethertype.dump(unit, gport_mgmt_idx_0, j0);
            sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.inlif_info.gport_id.dump(unit, gport_mgmt_idx_0, j0);
            sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.inlif_info.key1.dump(unit, gport_mgmt_idx_0, j0);
            sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.inlif_info.peer_gport.dump(unit, gport_mgmt_idx_0, j0);
            sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.inlif_info.learn_gport_id.dump(unit, gport_mgmt_idx_0, j0);
            sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.inlif_info.tpid_profile_type.dump(unit, gport_mgmt_idx_0, j0);
            sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.inlif_info.vsi.dump(unit, gport_mgmt_idx_0, j0);
            sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.inlif_info.additional_flags.dump(unit, gport_mgmt_idx_0, j0);
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
int sw_state_dpp_bcm_gport_mgmt_inlif_info_lif_type_dump(int unit, int gport_mgmt_idx_0, int inlif_info_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.bcm.gport_mgmt->inlif_info[inlif_info_idx_0].lif_type,
        "sw_state[%d]->dpp.bcm.gport_mgmt->inlif_info[%d].lif_type: ", unit, inlif_info_idx_0);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_bcm_gport_mgmt_inlif_info_flags_dump(int unit, int gport_mgmt_idx_0, int inlif_info_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.bcm.gport_mgmt->inlif_info[inlif_info_idx_0].flags,
        "sw_state[%d]->dpp.bcm.gport_mgmt->inlif_info[%d].flags: ", unit, inlif_info_idx_0);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_bcm_gport_mgmt_inlif_info_criteria_dump(int unit, int gport_mgmt_idx_0, int inlif_info_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.bcm.gport_mgmt->inlif_info[inlif_info_idx_0].criteria,
        "sw_state[%d]->dpp.bcm.gport_mgmt->inlif_info[%d].criteria: ", unit, inlif_info_idx_0);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_bcm_gport_mgmt_inlif_info_port_dump(int unit, int gport_mgmt_idx_0, int inlif_info_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.bcm.gport_mgmt->inlif_info[inlif_info_idx_0].port,
        "sw_state[%d]->dpp.bcm.gport_mgmt->inlif_info[%d].port: ", unit, inlif_info_idx_0);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_bcm_gport_mgmt_inlif_info_match1_dump(int unit, int gport_mgmt_idx_0, int inlif_info_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.bcm.gport_mgmt->inlif_info[inlif_info_idx_0].match1,
        "sw_state[%d]->dpp.bcm.gport_mgmt->inlif_info[%d].match1: ", unit, inlif_info_idx_0);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_bcm_gport_mgmt_inlif_info_match2_dump(int unit, int gport_mgmt_idx_0, int inlif_info_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.bcm.gport_mgmt->inlif_info[inlif_info_idx_0].match2,
        "sw_state[%d]->dpp.bcm.gport_mgmt->inlif_info[%d].match2: ", unit, inlif_info_idx_0);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_bcm_gport_mgmt_inlif_info_match_tunnel_dump(int unit, int gport_mgmt_idx_0, int inlif_info_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.bcm.gport_mgmt->inlif_info[inlif_info_idx_0].match_tunnel,
        "sw_state[%d]->dpp.bcm.gport_mgmt->inlif_info[%d].match_tunnel: ", unit, inlif_info_idx_0);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_bcm_gport_mgmt_inlif_info_match_ethertype_dump(int unit, int gport_mgmt_idx_0, int inlif_info_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.bcm.gport_mgmt->inlif_info[inlif_info_idx_0].match_ethertype,
        "sw_state[%d]->dpp.bcm.gport_mgmt->inlif_info[%d].match_ethertype: ", unit, inlif_info_idx_0);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_bcm_gport_mgmt_inlif_info_gport_id_dump(int unit, int gport_mgmt_idx_0, int inlif_info_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.bcm.gport_mgmt->inlif_info[inlif_info_idx_0].gport_id,
        "sw_state[%d]->dpp.bcm.gport_mgmt->inlif_info[%d].gport_id: ", unit, inlif_info_idx_0);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_bcm_gport_mgmt_inlif_info_key1_dump(int unit, int gport_mgmt_idx_0, int inlif_info_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.bcm.gport_mgmt->inlif_info[inlif_info_idx_0].key1,
        "sw_state[%d]->dpp.bcm.gport_mgmt->inlif_info[%d].key1: ", unit, inlif_info_idx_0);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_bcm_gport_mgmt_inlif_info_peer_gport_dump(int unit, int gport_mgmt_idx_0, int inlif_info_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.bcm.gport_mgmt->inlif_info[inlif_info_idx_0].peer_gport,
        "sw_state[%d]->dpp.bcm.gport_mgmt->inlif_info[%d].peer_gport: ", unit, inlif_info_idx_0);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_bcm_gport_mgmt_inlif_info_learn_gport_id_dump(int unit, int gport_mgmt_idx_0, int inlif_info_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.bcm.gport_mgmt->inlif_info[inlif_info_idx_0].learn_gport_id,
        "sw_state[%d]->dpp.bcm.gport_mgmt->inlif_info[%d].learn_gport_id: ", unit, inlif_info_idx_0);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_bcm_gport_mgmt_inlif_info_tpid_profile_type_dump(int unit, int gport_mgmt_idx_0, int inlif_info_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.bcm.gport_mgmt->inlif_info[inlif_info_idx_0].tpid_profile_type,
        "sw_state[%d]->dpp.bcm.gport_mgmt->inlif_info[%d].tpid_profile_type: ", unit, inlif_info_idx_0);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_bcm_gport_mgmt_inlif_info_vsi_dump(int unit, int gport_mgmt_idx_0, int inlif_info_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.bcm.gport_mgmt->inlif_info[inlif_info_idx_0].vsi,
        "sw_state[%d]->dpp.bcm.gport_mgmt->inlif_info[%d].vsi: ", unit, inlif_info_idx_0);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_bcm_gport_mgmt_inlif_info_additional_flags_dump(int unit, int gport_mgmt_idx_0, int inlif_info_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.bcm.gport_mgmt->inlif_info[inlif_info_idx_0].additional_flags,
        "sw_state[%d]->dpp.bcm.gport_mgmt->inlif_info[%d].additional_flags: ", unit, inlif_info_idx_0);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_bcm_gport_mgmt_vlan_port_db_htb_handle_dump(int unit, int gport_mgmt_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.bcm.gport_mgmt->vlan_port_db_htb_handle,
        "sw_state[%d]->dpp.bcm.gport_mgmt->vlan_port_db_htb_handle: ", unit);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_bcm_gport_mgmt_trill_info_db_htb_handle_dump(int unit, int gport_mgmt_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.bcm.gport_mgmt->trill_info_db_htb_handle,
        "sw_state[%d]->dpp.bcm.gport_mgmt->trill_info_db_htb_handle: ", unit);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_bcm_gport_mgmt_mc_trill_db_htb_handle_dump(int unit, int gport_mgmt_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.bcm.gport_mgmt->mc_trill_db_htb_handle,
        "sw_state[%d]->dpp.bcm.gport_mgmt->mc_trill_db_htb_handle: ", unit);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_bcm_gport_mgmt_trill_vpn_db_htb_handle_dump(int unit, int gport_mgmt_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.bcm.gport_mgmt->trill_vpn_db_htb_handle,
        "sw_state[%d]->dpp.bcm.gport_mgmt->trill_vpn_db_htb_handle: ", unit);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 


int
sw_state_dpp_bcm_gport_mgmt_diagnostic_cb_init(int unit){
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.dump = sw_state_dpp_bcm_gport_mgmt_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.fec_remote_lif.dump = sw_state_dpp_bcm_gport_mgmt_fec_remote_lif_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.bcm_dpp_sw_resources_fec_to_gport.dump = sw_state_dpp_bcm_gport_mgmt_bcm_dpp_sw_resources_fec_to_gport_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.outlif_info.dump = sw_state_dpp_bcm_gport_mgmt_outlif_info_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.outlif_info.lif_type.dump = sw_state_dpp_bcm_gport_mgmt_outlif_info_lif_type_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.outlif_info.flags.dump = sw_state_dpp_bcm_gport_mgmt_outlif_info_flags_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.inlif_info.dump = sw_state_dpp_bcm_gport_mgmt_inlif_info_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.inlif_info.lif_type.dump = sw_state_dpp_bcm_gport_mgmt_inlif_info_lif_type_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.inlif_info.flags.dump = sw_state_dpp_bcm_gport_mgmt_inlif_info_flags_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.inlif_info.criteria.dump = sw_state_dpp_bcm_gport_mgmt_inlif_info_criteria_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.inlif_info.port.dump = sw_state_dpp_bcm_gport_mgmt_inlif_info_port_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.inlif_info.match1.dump = sw_state_dpp_bcm_gport_mgmt_inlif_info_match1_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.inlif_info.match2.dump = sw_state_dpp_bcm_gport_mgmt_inlif_info_match2_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.inlif_info.match_tunnel.dump = sw_state_dpp_bcm_gport_mgmt_inlif_info_match_tunnel_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.inlif_info.match_ethertype.dump = sw_state_dpp_bcm_gport_mgmt_inlif_info_match_ethertype_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.inlif_info.gport_id.dump = sw_state_dpp_bcm_gport_mgmt_inlif_info_gport_id_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.inlif_info.key1.dump = sw_state_dpp_bcm_gport_mgmt_inlif_info_key1_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.inlif_info.peer_gport.dump = sw_state_dpp_bcm_gport_mgmt_inlif_info_peer_gport_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.inlif_info.learn_gport_id.dump = sw_state_dpp_bcm_gport_mgmt_inlif_info_learn_gport_id_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.inlif_info.tpid_profile_type.dump = sw_state_dpp_bcm_gport_mgmt_inlif_info_tpid_profile_type_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.inlif_info.vsi.dump = sw_state_dpp_bcm_gport_mgmt_inlif_info_vsi_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.inlif_info.additional_flags.dump = sw_state_dpp_bcm_gport_mgmt_inlif_info_additional_flags_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.vlan_port_db_htb_handle.dump = sw_state_dpp_bcm_gport_mgmt_vlan_port_db_htb_handle_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.trill_info_db_htb_handle.dump = sw_state_dpp_bcm_gport_mgmt_trill_info_db_htb_handle_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.mc_trill_db_htb_handle.dump = sw_state_dpp_bcm_gport_mgmt_mc_trill_db_htb_handle_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.bcm.gport_mgmt.trill_vpn_db_htb_handle.dump = sw_state_dpp_bcm_gport_mgmt_trill_vpn_db_htb_handle_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
    return _SHR_E_NONE;
}

#undef _ERR_MSG_MODULE_NAME
#endif /* BCM_WARM_BOOT_API_TEST */
