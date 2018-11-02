/*
 * $Id: wb_db_vswitch.h,v 1.0 Broadcom SDK $
 * $Copyright: (c) 2016 Broadcom.
 * Broadcom Proprietary and Confidential. All rights reserved.$
 *
 * VSWITCH warmboot functions
 *
 */

#ifndef __BCM_INT_SBX_CALADAN3_WB_DB_VSWITCH_H__
#define __BCM_INT_SBX_CALADAN3_WB_DB_VSWITCH_H__

#include <bcm/error.h>
#include <bcm/module.h>

#include <bcm_int/common/debug.h>

#ifdef BCM_WARM_BOOT_SUPPORT

/*
 *  Versioning...
 */
#define BCM_CALADAN3_WB_VSWITCH_VERSION_1_0      SOC_SCACHE_VERSION(1, 0)
#define BCM_CALADAN3_WB_VSWITCH_VERSION_CURR     BCM_CALADAN3_WB_VSWITCH_VERSION_1_0


/*
 *  Overall descriptor for VSWITCH warmboot 
 */
typedef struct bcm_caladan3_wb_vswitch_state_scache_info_s {
    int         init_done;
    int         is_dirty;

    uint16      version;
    uint8       *scache_ptr;
    unsigned int         scache_len;


} bcm_caladan3_wb_vswitch_state_scache_info_t;

/*
 *  Function
 *    bcm_caladan3_vswitch_all_wb_state_sync
 *  Purpose
 *    Sync the entire field state to the warm boot buffer
 *  Arguments
 *    IN unit = unit number
 *  Results
 *    bcm_error_t (cast as int)
 *      BCM_E_NONE for success
 *      BCM_E_* otherwise as appropriate
 *  Notes
 *    Does not report error conditions for many things...
 *
 *    Use this call from anywhere outside of the VSWITCH module.
 */
int bcm_caladan3_wb_vswitch_state_sync(int unit);

/*
 *  Function
 *    bcm_caladan3_wb_vswitch_state_init
 *  Purpose
 *    Initialise the warm boot support for field APIs
 *  Arguments
 *    IN unit = unit number
 *  Results
 *    bcm_error_t (cast as int)
 *      BCM_E_NONE if success
 *      BCM_E_* otherwise as appropriate
 *  Notes
 */
int bcm_caladan3_wb_vswitch_state_init(int unit);

#endif /* def BCM_WARM_BOOT_SUPPORT */

#endif /* __BCM_INT_SBX_CALADAN3_WB_DB_VSWITCH_H__  */

