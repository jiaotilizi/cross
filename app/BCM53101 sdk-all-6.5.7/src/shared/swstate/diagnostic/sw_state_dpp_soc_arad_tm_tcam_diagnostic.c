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
#include <shared/swstate/diagnostic/sw_state_dpp_soc_arad_tm_tcam_diagnostic.h>

#ifdef BCM_WARM_BOOT_API_TEST
#ifdef _ERR_MSG_MODULE_NAME
    #error "_ERR_MSG_MODULE_NAME redefined"
#endif

#define _ERR_MSG_MODULE_NAME BSL_LS_SHARED_SWSTATE

extern shr_sw_state_t *sw_state[BCM_MAX_NUM_UNITS];

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_soc_arad_tm_tcam_dump(int unit, int tm_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    {
        uint32 j0, J0;
        sw_state_get_nof_elements(unit, sw_state[unit]->dpp.soc.arad.tm->tcam, sizeof(*sw_state[unit]->dpp.soc.arad.tm->tcam), &j0 ,&J0);
        for (; j0 < J0; j0++) {
            shr_sw_state_dump_update_current_idx(unit, j0);
            sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_bank_entries_used.dump(unit, tm_idx_0, j0);
            sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_db_priorities.dump(unit, tm_idx_0, j0);
            sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_db_entries_used.dump(unit, tm_idx_0, j0);
            sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.entry_id_to_location.dump(unit, tm_idx_0, j0);
            sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.bank.dump(unit, tm_idx_0, j0);
            sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_db.dump(unit, tm_idx_0, j0);
            sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.db_location_tbl.dump(unit, tm_idx_0, j0);
            sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.global_location_tbl.dump(unit, tm_idx_0, j0);
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
int sw_state_dpp_soc_arad_tm_tcam_tcam_bank_entries_used_dump(int unit, int tm_idx_0, int tcam_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    {
        int i0;
        i0 = shr_sw_state_dump_check_all_the_same(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->tcam_bank_entries_used
            , sizeof(*sw_state[unit]->dpp.soc.arad.tm->tcam->tcam_bank_entries_used), SOC_DPP_DEFS_MAX_TCAM_NOF_BANKS) ? SOC_DPP_DEFS_MAX_TCAM_NOF_BANKS - 1 : 0;
        for (; i0 < SOC_DPP_DEFS_MAX_TCAM_NOF_BANKS; i0++) {
            shr_sw_state_dump_update_current_idx(unit, i0);
            {
                int i1;
                i1 = shr_sw_state_dump_check_all_the_same(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->tcam_bank_entries_used[i0]
                    , sizeof(*sw_state[unit]->dpp.soc.arad.tm->tcam->tcam_bank_entries_used[i0]), 2) ? 2 - 1 : 0;
                for (; i1 < 2; i1++) {
                    shr_sw_state_dump_update_current_idx(unit, i1);
                    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->tcam_bank_entries_used[i0][i1],
                        "sw_state[%d]->dpp.soc.arad.tm->tcam->tcam_bank_entries_used[%d][%d]: ", unit, i0, i1);
                }
                shr_sw_state_dump_end_of_stride(unit);
            }
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
int sw_state_dpp_soc_arad_tm_tcam_tcam_db_priorities_dump(int unit, int tm_idx_0, int tcam_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    {
        int i0;
        i0 = shr_sw_state_dump_check_all_the_same(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->tcam_db_priorities
            , sizeof(*sw_state[unit]->dpp.soc.arad.tm->tcam->tcam_db_priorities), ARAD_TCAM_MAX_NOF_LISTS) ? ARAD_TCAM_MAX_NOF_LISTS - 1 : 0;
        for (; i0 < ARAD_TCAM_MAX_NOF_LISTS; i0++) {
            shr_sw_state_dump_update_current_idx(unit, i0);
            SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->tcam_db_priorities[i0],
                "sw_state[%d]->dpp.soc.arad.tm->tcam->tcam_db_priorities[%d]: ", unit, i0);
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
int sw_state_dpp_soc_arad_tm_tcam_tcam_db_entries_used_dump(int unit, int tm_idx_0, int tcam_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    {
        int i0;
        i0 = shr_sw_state_dump_check_all_the_same(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->tcam_db_entries_used
            , sizeof(*sw_state[unit]->dpp.soc.arad.tm->tcam->tcam_db_entries_used), ARAD_TCAM_MAX_NOF_LISTS) ? ARAD_TCAM_MAX_NOF_LISTS - 1 : 0;
        for (; i0 < ARAD_TCAM_MAX_NOF_LISTS; i0++) {
            shr_sw_state_dump_update_current_idx(unit, i0);
            {
                int i1;
                i1 = shr_sw_state_dump_check_all_the_same(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->tcam_db_entries_used[i0]
                    , sizeof(*sw_state[unit]->dpp.soc.arad.tm->tcam->tcam_db_entries_used[i0]), SOC_DPP_DEFS_MAX_TCAM_NOF_BANKS) ? SOC_DPP_DEFS_MAX_TCAM_NOF_BANKS - 1 : 0;
                for (; i1 < SOC_DPP_DEFS_MAX_TCAM_NOF_BANKS; i1++) {
                    shr_sw_state_dump_update_current_idx(unit, i1);
                    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->tcam_db_entries_used[i0][i1],
                        "sw_state[%d]->dpp.soc.arad.tm->tcam->tcam_db_entries_used[%d][%d]: ", unit, i0, i1);
                }
                shr_sw_state_dump_end_of_stride(unit);
            }
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
int sw_state_dpp_soc_arad_tm_tcam_entry_id_to_location_dump(int unit, int tm_idx_0, int tcam_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->entry_id_to_location,
        "sw_state[%d]->dpp.soc.arad.tm->tcam->entry_id_to_location: ", unit);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_soc_arad_tm_tcam_bank_dump(int unit, int tm_idx_0, int tcam_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    {
        int i0;
        i0 = shr_sw_state_dump_check_all_the_same(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->bank
            , sizeof(*sw_state[unit]->dpp.soc.arad.tm->tcam->bank), SOC_DPP_DEFS_MAX_TCAM_NOF_BANKS) ? SOC_DPP_DEFS_MAX_TCAM_NOF_BANKS - 1 : 0;
        for (; i0 < SOC_DPP_DEFS_MAX_TCAM_NOF_BANKS; i0++) {
            shr_sw_state_dump_update_current_idx(unit, i0);
            sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.bank.valid.dump(unit, tm_idx_0, tcam_idx_0, i0);
            sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.bank.has_direct_table.dump(unit, tm_idx_0, tcam_idx_0, i0);
            sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.bank.entry_size.dump(unit, tm_idx_0, tcam_idx_0, i0);
            sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.bank.nof_entries_free.dump(unit, tm_idx_0, tcam_idx_0, i0);
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
int sw_state_dpp_soc_arad_tm_tcam_bank_valid_dump(int unit, int tm_idx_0, int tcam_idx_0, int bank_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->bank[bank_idx_0].valid,
        "sw_state[%d]->dpp.soc.arad.tm->tcam->bank[%d].valid: ", unit, bank_idx_0);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_soc_arad_tm_tcam_bank_has_direct_table_dump(int unit, int tm_idx_0, int tcam_idx_0, int bank_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->bank[bank_idx_0].has_direct_table,
        "sw_state[%d]->dpp.soc.arad.tm->tcam->bank[%d].has_direct_table: ", unit, bank_idx_0);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_soc_arad_tm_tcam_bank_entry_size_dump(int unit, int tm_idx_0, int tcam_idx_0, int bank_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->bank[bank_idx_0].entry_size,
        "sw_state[%d]->dpp.soc.arad.tm->tcam->bank[%d].entry_size: ", unit, bank_idx_0);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_soc_arad_tm_tcam_bank_nof_entries_free_dump(int unit, int tm_idx_0, int tcam_idx_0, int bank_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->bank[bank_idx_0].nof_entries_free,
        "sw_state[%d]->dpp.soc.arad.tm->tcam->bank[%d].nof_entries_free: ", unit, bank_idx_0);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_soc_arad_tm_tcam_tcam_db_dump(int unit, int tm_idx_0, int tcam_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    {
        int i0;
        i0 = shr_sw_state_dump_check_all_the_same(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->tcam_db
            , sizeof(*sw_state[unit]->dpp.soc.arad.tm->tcam->tcam_db), ARAD_TCAM_MAX_NOF_LISTS) ? ARAD_TCAM_MAX_NOF_LISTS - 1 : 0;
        for (; i0 < ARAD_TCAM_MAX_NOF_LISTS; i0++) {
            shr_sw_state_dump_update_current_idx(unit, i0);
            sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_db.valid.dump(unit, tm_idx_0, tcam_idx_0, i0);
            sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_db.action_bitmap_ndx.dump(unit, tm_idx_0, tcam_idx_0, i0);
            sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_db.entry_size.dump(unit, tm_idx_0, tcam_idx_0, i0);
            sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_db.prefix_size.dump(unit, tm_idx_0, tcam_idx_0, i0);
            sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_db.bank_used.dump(unit, tm_idx_0, tcam_idx_0, i0);
            sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_db.is_direct.dump(unit, tm_idx_0, tcam_idx_0, i0);
            sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_db.use_small_banks.dump(unit, tm_idx_0, tcam_idx_0, i0);
            sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_db.no_insertion_priority_order.dump(unit, tm_idx_0, tcam_idx_0, i0);
            sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_db.sparse_priorities.dump(unit, tm_idx_0, tcam_idx_0, i0);
            sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_db.prefix.dump(unit, tm_idx_0, tcam_idx_0, i0);
            sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_db.access_profile_id.dump(unit, tm_idx_0, tcam_idx_0, i0);
            sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_db.forbidden_dbs.dump(unit, tm_idx_0, tcam_idx_0, i0);
            sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_db.bank_nof_entries.dump(unit, tm_idx_0, tcam_idx_0, i0);
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
int sw_state_dpp_soc_arad_tm_tcam_tcam_db_valid_dump(int unit, int tm_idx_0, int tcam_idx_0, int tcam_db_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->tcam_db[tcam_db_idx_0].valid,
        "sw_state[%d]->dpp.soc.arad.tm->tcam->tcam_db[%d].valid: ", unit, tcam_db_idx_0);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_soc_arad_tm_tcam_tcam_db_action_bitmap_ndx_dump(int unit, int tm_idx_0, int tcam_idx_0, int tcam_db_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->tcam_db[tcam_db_idx_0].action_bitmap_ndx,
        "sw_state[%d]->dpp.soc.arad.tm->tcam->tcam_db[%d].action_bitmap_ndx: ", unit, tcam_db_idx_0);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_soc_arad_tm_tcam_tcam_db_entry_size_dump(int unit, int tm_idx_0, int tcam_idx_0, int tcam_db_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->tcam_db[tcam_db_idx_0].entry_size,
        "sw_state[%d]->dpp.soc.arad.tm->tcam->tcam_db[%d].entry_size: ", unit, tcam_db_idx_0);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_soc_arad_tm_tcam_tcam_db_prefix_size_dump(int unit, int tm_idx_0, int tcam_idx_0, int tcam_db_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->tcam_db[tcam_db_idx_0].prefix_size,
        "sw_state[%d]->dpp.soc.arad.tm->tcam->tcam_db[%d].prefix_size: ", unit, tcam_db_idx_0);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_soc_arad_tm_tcam_tcam_db_bank_used_dump(int unit, int tm_idx_0, int tcam_idx_0, int tcam_db_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    {
        int i0;
        i0 = shr_sw_state_dump_check_all_the_same(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->tcam_db[tcam_db_idx_0].bank_used
            , sizeof(*sw_state[unit]->dpp.soc.arad.tm->tcam->tcam_db[tcam_db_idx_0].bank_used), SOC_DPP_DEFS_MAX_TCAM_NOF_BANKS) ? SOC_DPP_DEFS_MAX_TCAM_NOF_BANKS - 1 : 0;
        for (; i0 < SOC_DPP_DEFS_MAX_TCAM_NOF_BANKS; i0++) {
            shr_sw_state_dump_update_current_idx(unit, i0);
            SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->tcam_db[tcam_db_idx_0].bank_used[i0],
                "sw_state[%d]->dpp.soc.arad.tm->tcam->tcam_db[%d].bank_used[%d]: ", unit, tcam_db_idx_0, i0);
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
int sw_state_dpp_soc_arad_tm_tcam_tcam_db_is_direct_dump(int unit, int tm_idx_0, int tcam_idx_0, int tcam_db_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->tcam_db[tcam_db_idx_0].is_direct,
        "sw_state[%d]->dpp.soc.arad.tm->tcam->tcam_db[%d].is_direct: ", unit, tcam_db_idx_0);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_soc_arad_tm_tcam_tcam_db_use_small_banks_dump(int unit, int tm_idx_0, int tcam_idx_0, int tcam_db_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->tcam_db[tcam_db_idx_0].use_small_banks,
        "sw_state[%d]->dpp.soc.arad.tm->tcam->tcam_db[%d].use_small_banks: ", unit, tcam_db_idx_0);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_soc_arad_tm_tcam_tcam_db_no_insertion_priority_order_dump(int unit, int tm_idx_0, int tcam_idx_0, int tcam_db_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->tcam_db[tcam_db_idx_0].no_insertion_priority_order,
        "sw_state[%d]->dpp.soc.arad.tm->tcam->tcam_db[%d].no_insertion_priority_order: ", unit, tcam_db_idx_0);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_soc_arad_tm_tcam_tcam_db_sparse_priorities_dump(int unit, int tm_idx_0, int tcam_idx_0, int tcam_db_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->tcam_db[tcam_db_idx_0].sparse_priorities,
        "sw_state[%d]->dpp.soc.arad.tm->tcam->tcam_db[%d].sparse_priorities: ", unit, tcam_db_idx_0);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_soc_arad_tm_tcam_tcam_db_prefix_dump(int unit, int tm_idx_0, int tcam_idx_0, int tcam_db_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_db.prefix.bits.dump(unit, tm_idx_0, tcam_idx_0, tcam_db_idx_0);
    sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_db.prefix.length.dump(unit, tm_idx_0, tcam_idx_0, tcam_db_idx_0);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_soc_arad_tm_tcam_tcam_db_prefix_bits_dump(int unit, int tm_idx_0, int tcam_idx_0, int tcam_db_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->tcam_db[tcam_db_idx_0].prefix.bits,
        "sw_state[%d]->dpp.soc.arad.tm->tcam->tcam_db[%d].prefix.bits: ", unit, tcam_db_idx_0);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_soc_arad_tm_tcam_tcam_db_prefix_length_dump(int unit, int tm_idx_0, int tcam_idx_0, int tcam_db_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->tcam_db[tcam_db_idx_0].prefix.length,
        "sw_state[%d]->dpp.soc.arad.tm->tcam->tcam_db[%d].prefix.length: ", unit, tcam_db_idx_0);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_soc_arad_tm_tcam_tcam_db_access_profile_id_dump(int unit, int tm_idx_0, int tcam_idx_0, int tcam_db_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    {
        int i0;
        i0 = shr_sw_state_dump_check_all_the_same(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->tcam_db[tcam_db_idx_0].access_profile_id
            , sizeof(*sw_state[unit]->dpp.soc.arad.tm->tcam->tcam_db[tcam_db_idx_0].access_profile_id), ARAD_PP_FP_KEY_NOF_KEYS_PER_DB_MAX) ? ARAD_PP_FP_KEY_NOF_KEYS_PER_DB_MAX - 1 : 0;
        for (; i0 < ARAD_PP_FP_KEY_NOF_KEYS_PER_DB_MAX; i0++) {
            shr_sw_state_dump_update_current_idx(unit, i0);
            SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->tcam_db[tcam_db_idx_0].access_profile_id[i0],
                "sw_state[%d]->dpp.soc.arad.tm->tcam->tcam_db[%d].access_profile_id[%d]: ", unit, tcam_db_idx_0, i0);
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
int sw_state_dpp_soc_arad_tm_tcam_tcam_db_forbidden_dbs_dump(int unit, int tm_idx_0, int tcam_idx_0, int tcam_db_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    {
        int i0;
        i0 = shr_sw_state_dump_check_all_the_same(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->tcam_db[tcam_db_idx_0].forbidden_dbs
            , sizeof(*sw_state[unit]->dpp.soc.arad.tm->tcam->tcam_db[tcam_db_idx_0].forbidden_dbs), ARAD_BIT_TO_U32(ARAD_TCAM_MAX_NOF_LISTS)) ? ARAD_BIT_TO_U32(ARAD_TCAM_MAX_NOF_LISTS) - 1 : 0;
        for (; i0 < ARAD_BIT_TO_U32(ARAD_TCAM_MAX_NOF_LISTS); i0++) {
            shr_sw_state_dump_update_current_idx(unit, i0);
            SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->tcam_db[tcam_db_idx_0].forbidden_dbs[i0],
                "sw_state[%d]->dpp.soc.arad.tm->tcam->tcam_db[%d].forbidden_dbs[%d]: ", unit, tcam_db_idx_0, i0);
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
int sw_state_dpp_soc_arad_tm_tcam_tcam_db_bank_nof_entries_dump(int unit, int tm_idx_0, int tcam_idx_0, int tcam_db_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    {
        int i0;
        i0 = shr_sw_state_dump_check_all_the_same(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->tcam_db[tcam_db_idx_0].bank_nof_entries
            , sizeof(*sw_state[unit]->dpp.soc.arad.tm->tcam->tcam_db[tcam_db_idx_0].bank_nof_entries), SOC_DPP_DEFS_MAX_TCAM_NOF_BANKS) ? SOC_DPP_DEFS_MAX_TCAM_NOF_BANKS - 1 : 0;
        for (; i0 < SOC_DPP_DEFS_MAX_TCAM_NOF_BANKS; i0++) {
            shr_sw_state_dump_update_current_idx(unit, i0);
            SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->tcam_db[tcam_db_idx_0].bank_nof_entries[i0],
                "sw_state[%d]->dpp.soc.arad.tm->tcam->tcam_db[%d].bank_nof_entries[%d]: ", unit, tcam_db_idx_0, i0);
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
int sw_state_dpp_soc_arad_tm_tcam_db_location_tbl_dump(int unit, int tm_idx_0, int tcam_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    {
        uint32 j0, J0;
        sw_state_get_nof_elements(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->db_location_tbl, sizeof(*sw_state[unit]->dpp.soc.arad.tm->tcam->db_location_tbl), &j0 ,&J0);
        for (; j0 < J0; j0++) {
            shr_sw_state_dump_update_current_idx(unit, j0);
            sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.db_location_tbl.bank_id.dump(unit, tm_idx_0, tcam_idx_0, j0);
            sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.db_location_tbl.entry.dump(unit, tm_idx_0, tcam_idx_0, j0);
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
int sw_state_dpp_soc_arad_tm_tcam_db_location_tbl_bank_id_dump(int unit, int tm_idx_0, int tcam_idx_0, int db_location_tbl_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->db_location_tbl[db_location_tbl_idx_0].bank_id,
        "sw_state[%d]->dpp.soc.arad.tm->tcam->db_location_tbl[%d].bank_id: ", unit, db_location_tbl_idx_0);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_soc_arad_tm_tcam_db_location_tbl_entry_dump(int unit, int tm_idx_0, int tcam_idx_0, int db_location_tbl_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->db_location_tbl[db_location_tbl_idx_0].entry,
        "sw_state[%d]->dpp.soc.arad.tm->tcam->db_location_tbl[%d].entry: ", unit, db_location_tbl_idx_0);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_soc_arad_tm_tcam_global_location_tbl_dump(int unit, int tm_idx_0, int tcam_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    {
        uint32 j0, J0;
        sw_state_get_nof_elements(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->global_location_tbl, sizeof(*sw_state[unit]->dpp.soc.arad.tm->tcam->global_location_tbl), &j0 ,&J0);
        for (; j0 < J0; j0++) {
            shr_sw_state_dump_update_current_idx(unit, j0);
            sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.global_location_tbl.tcam_db_id.dump(unit, tm_idx_0, tcam_idx_0, j0);
            sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.global_location_tbl.entry_id.dump(unit, tm_idx_0, tcam_idx_0, j0);
            sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.global_location_tbl.priority.dump(unit, tm_idx_0, tcam_idx_0, j0);
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
int sw_state_dpp_soc_arad_tm_tcam_global_location_tbl_tcam_db_id_dump(int unit, int tm_idx_0, int tcam_idx_0, int global_location_tbl_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->global_location_tbl[global_location_tbl_idx_0].tcam_db_id,
        "sw_state[%d]->dpp.soc.arad.tm->tcam->global_location_tbl[%d].tcam_db_id: ", unit, global_location_tbl_idx_0);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_soc_arad_tm_tcam_global_location_tbl_entry_id_dump(int unit, int tm_idx_0, int tcam_idx_0, int global_location_tbl_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->global_location_tbl[global_location_tbl_idx_0].entry_id,
        "sw_state[%d]->dpp.soc.arad.tm->tcam->global_location_tbl[%d].entry_id: ", unit, global_location_tbl_idx_0);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
/* AUTO-GENERATED - DO NOT MODIFY */
int sw_state_dpp_soc_arad_tm_tcam_global_location_tbl_priority_dump(int unit, int tm_idx_0, int tcam_idx_0, int global_location_tbl_idx_0){
    SW_STATE_INIT_FUNC_DEFS;
    SW_STATE_PRINT_OPAQUE(unit, sw_state[unit]->dpp.soc.arad.tm->tcam->global_location_tbl[global_location_tbl_idx_0].priority,
        "sw_state[%d]->dpp.soc.arad.tm->tcam->global_location_tbl[%d].priority: ", unit, global_location_tbl_idx_0);
    SW_STATE_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 


int
sw_state_dpp_soc_arad_tm_tcam_diagnostic_cb_init(int unit){
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.dump = sw_state_dpp_soc_arad_tm_tcam_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_bank_entries_used.dump = sw_state_dpp_soc_arad_tm_tcam_tcam_bank_entries_used_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_db_priorities.dump = sw_state_dpp_soc_arad_tm_tcam_tcam_db_priorities_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_db_entries_used.dump = sw_state_dpp_soc_arad_tm_tcam_tcam_db_entries_used_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.entry_id_to_location.dump = sw_state_dpp_soc_arad_tm_tcam_entry_id_to_location_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.bank.dump = sw_state_dpp_soc_arad_tm_tcam_bank_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.bank.valid.dump = sw_state_dpp_soc_arad_tm_tcam_bank_valid_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.bank.has_direct_table.dump = sw_state_dpp_soc_arad_tm_tcam_bank_has_direct_table_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.bank.entry_size.dump = sw_state_dpp_soc_arad_tm_tcam_bank_entry_size_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.bank.nof_entries_free.dump = sw_state_dpp_soc_arad_tm_tcam_bank_nof_entries_free_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_db.dump = sw_state_dpp_soc_arad_tm_tcam_tcam_db_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_db.valid.dump = sw_state_dpp_soc_arad_tm_tcam_tcam_db_valid_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_db.action_bitmap_ndx.dump = sw_state_dpp_soc_arad_tm_tcam_tcam_db_action_bitmap_ndx_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_db.entry_size.dump = sw_state_dpp_soc_arad_tm_tcam_tcam_db_entry_size_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_db.prefix_size.dump = sw_state_dpp_soc_arad_tm_tcam_tcam_db_prefix_size_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_db.bank_used.dump = sw_state_dpp_soc_arad_tm_tcam_tcam_db_bank_used_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_db.is_direct.dump = sw_state_dpp_soc_arad_tm_tcam_tcam_db_is_direct_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_db.use_small_banks.dump = sw_state_dpp_soc_arad_tm_tcam_tcam_db_use_small_banks_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_db.no_insertion_priority_order.dump = sw_state_dpp_soc_arad_tm_tcam_tcam_db_no_insertion_priority_order_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_db.sparse_priorities.dump = sw_state_dpp_soc_arad_tm_tcam_tcam_db_sparse_priorities_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_db.prefix.dump = sw_state_dpp_soc_arad_tm_tcam_tcam_db_prefix_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_db.prefix.bits.dump = sw_state_dpp_soc_arad_tm_tcam_tcam_db_prefix_bits_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_db.prefix.length.dump = sw_state_dpp_soc_arad_tm_tcam_tcam_db_prefix_length_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_db.access_profile_id.dump = sw_state_dpp_soc_arad_tm_tcam_tcam_db_access_profile_id_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_db.forbidden_dbs.dump = sw_state_dpp_soc_arad_tm_tcam_tcam_db_forbidden_dbs_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.tcam_db.bank_nof_entries.dump = sw_state_dpp_soc_arad_tm_tcam_tcam_db_bank_nof_entries_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.db_location_tbl.dump = sw_state_dpp_soc_arad_tm_tcam_db_location_tbl_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.db_location_tbl.bank_id.dump = sw_state_dpp_soc_arad_tm_tcam_db_location_tbl_bank_id_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.db_location_tbl.entry.dump = sw_state_dpp_soc_arad_tm_tcam_db_location_tbl_entry_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.global_location_tbl.dump = sw_state_dpp_soc_arad_tm_tcam_global_location_tbl_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.global_location_tbl.tcam_db_id.dump = sw_state_dpp_soc_arad_tm_tcam_global_location_tbl_tcam_db_id_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.global_location_tbl.entry_id.dump = sw_state_dpp_soc_arad_tm_tcam_global_location_tbl_entry_id_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
    sw_state_diagnostic[unit].dpp.soc.arad.tm.tcam.global_location_tbl.priority.dump = sw_state_dpp_soc_arad_tm_tcam_global_location_tbl_priority_dump;
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
    return _SHR_E_NONE;
}

#undef _ERR_MSG_MODULE_NAME
#endif /* BCM_WARM_BOOT_API_TEST */
