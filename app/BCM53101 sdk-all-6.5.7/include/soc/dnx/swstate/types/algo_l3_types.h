/* $Id: $
 * 
 * $Copyright: (c) 2016 Broadcom.
 * Broadcom Proprietary and Confidential. All rights reserved.$
 * 
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated.
 * Edits to this file will be lost when it is regenerated.
 */

#ifndef _SOC_ALGO_L3_TYPES_H_
#define _SOC_ALGO_L3_TYPES_H_

#ifdef BCM_DNX_SUPPORT
#include <soc/dnx/swstate/sw_state_defs.h>

#include <shared/swstate/sw_state_res_tag_bitmap.h>

/*** Definitions ***/


/*** Typedefs ***/

typedef struct source_address_table_allocation_t_s {
    sw_state_res_tag_bitmap_handle_t res_tag_bitmap_handle;
} source_address_table_allocation_t;


typedef struct algo_l3_sw_state_t_s {
    source_address_table_allocation_t source_address_table_allocation;
} algo_l3_sw_state_t;


#endif /* BCM_DNX_SUPPORT*/ 

#endif /* _SOC_ALGO_L3_TYPES_H_ */
