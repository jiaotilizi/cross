/*
 * $Id: $
 * $Copyright: (c) 2016 Broadcom.
 * Broadcom Proprietary and Confidential. All rights reserved.$
 * 
 * INFO: this module is the entry point the branch of the sw state that compose the dnx bcm 
 * layer's sw state 
 *  
 */
#ifndef _DNX_SW_STATE_H
/* { */
#define _DNX_SW_STATE_H

#ifndef BCM_DNX_SUPPORT
#error "This file is for use by DNX (JR2) family only!"
#endif
#define DNX_SOC_CONFIG_VERSION_LENGTH_MAX 100

/*************
* INCLUDES  *
*************/
/* { */
#include <soc/dnx/legacy/SAND/Utils/sand_sorted_list.h>
#include <soc/dnx/legacy/SAND/Utils/sand_occupation_bitmap.h>
#include <soc/dnx/legacy/SAND/Utils/sand_hashtable.h>
#include <soc/dnx/legacy/SAND/Utils/sand_multi_set.h>

#include <include/soc/dnx/legacy/ARAD/arad_sw_db.h>

#include <shared/swstate/sw_state_resmgr.h>
#include <shared/swstate/sw_state_hash_tbl.h>
#include <shared/dnx_shr_template.h>


#include <soc/dnx/dbal/dbal_structures.h>
#include <soc/dnx/mdb.h>
/* } */

/*
 * Entry point structure for all SAND utilities.
 */
typedef struct
{
  PARSER_HINT_PTR utilex_sw_state_sorted_list_t *sorted_list;
  PARSER_HINT_PTR utilex_sw_state_occ_bitmap_t *occ_bitmap;
  PARSER_HINT_PTR utilex_sw_state_hash_table_t *hash_table;
  PARSER_HINT_PTR utilex_sw_state_multi_set_t *multi_set;
} utilex_sw_state_t;

typedef struct
{
  dbal_sw_state_table_t sw_tables[DBAL_NOF_TABLES];
} dnx_dbal_sw_state_t;

/*legacy sw state*/
typedef struct soc_dnx_dnx_sand_sw_state_s{
  PARSER_HINT_PTR dnx_sand_sw_state_sorted_list_t *sorted_list ;
  PARSER_HINT_PTR dnx_sand_sw_state_occ_bitmap_t  *occ_bitmap ;
  PARSER_HINT_PTR dnx_sand_sw_state_hash_table_t  *hash_table ;
  PARSER_HINT_PTR dnx_sand_sw_state_multi_set_t   *multi_set ;
} soc_dnx_dnx_sand_sw_state_t ;

typedef struct soc_dnx_soc_jer2_arad_sw_state_s{
    PARSER_HINT_PTR soc_jer2_arad_sw_state_tm_t *tm;
} soc_dnx_soc_jer2_arad_sw_state_t;

typedef struct soc_jer2_jericho_sw_state_tm_s {
    uint16 nof_remote_faps_with_remote_credit_value;
    PARSER_HINT_PTR DNX_TMC_FC_PFC_GEN_BMP_INFO *pfc_gen_bmp;
    PARSER_HINT_ARR DNX_TMC_ITM_INGRESS_RESERVED_RESOURCE *ingress_reserved_resource;
    soc_pbmp_t is_tdm_queuing_on; /*port bitmap indicating if port have tdm queuing on */	
} soc_jer2_jericho_sw_state_tm_t;


typedef struct soc_dnx_soc_jer2_jericho_sw_state_s {
    soc_jer2_jericho_sw_state_tm_t tm;
} soc_dnx_soc_jer2_jericho_sw_state_t;

typedef struct soc_jer2_qax_sw_state_tm_s {
    DNX_TMC_ITM_GUARANTEED_RESOURCE guaranteed_info[SOC_DNX_DEFS_MAX(NOF_CORES)];
} soc_jer2_qax_sw_state_tm_t;

typedef struct soc_dnx_soc_jer2_qax_sw_state_s {
    soc_jer2_qax_sw_state_tm_t       tm;
} soc_dnx_soc_jer2_qax_sw_state_t;

typedef struct soc_dnx_soc_config_s{
    uint32      autosync;
    char        version[DNX_SOC_CONFIG_VERSION_LENGTH_MAX];
    int         nested_api_counter;
} soc_dnx_soc_config_t;

typedef struct soc_dnx_soc_sw_state_s{
    soc_dnx_soc_jer2_arad_sw_state_t jer2_arad;
	soc_dnx_soc_jer2_jericho_sw_state_t jer2_jericho;
    soc_dnx_soc_jer2_qax_sw_state_t jer2_qax;
	soc_dnx_dnx_sand_sw_state_t sand;
    soc_dnx_soc_config_t config;
} soc_dnx_soc_sw_state_t;

typedef struct soc_dnx_shr_sw_state_s{
    _sw_state_res_unit_desc_t       *resmgr_info;
    sw_state_hash_table_db_t        htbls;
    sw_state_res_tag_bitmap_info_t  bmp_info;
    _dnx_shr_template_unit_desc_t       *template_info;
} soc_dnx_shr_sw_state_t;
/* } */
#endif /*#define _DNX_SW_STATE_H*/

