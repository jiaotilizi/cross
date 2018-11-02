/*
 * $Id: soc_dcmn_mem_cache.c, v1 16/06/2014 09:55:39 azarrin $
 *
 * $Copyright: (c) 2016 Broadcom.
 * Broadcom Proprietary and Confidential. All rights reserved.$
 *
 * Purpose:    Implement soc cache memories.
 */

/*************
 * INCLUDES  *
 *************/
#include <shared/bsl.h>
#include <soc/drv.h>
#include <soc/mem.h>
#ifdef BCM_DPP_SUPPORT
#include <soc/dpp/drv.h>
#endif /* BCM_DPP_SUPPORT */

#include <soc/dcmn/error.h>

/*************
 * DEFINES   *
 *************/
#ifdef _ERR_MSG_MODULE_NAME
#error "_ERR_MSG_MODULE_NAME redefined"
#endif
#define _ERR_MSG_MODULE_NAME BSL_SOC_INTR

/*************
 * FUNCTIONS *
 *************/
int
dcmn_mem_cache_attach(int unit, soc_reg_t mem, int block_instance)
{
    int rc;
    
    SOCDNX_INIT_FUNC_DEFS;
   
    if (soc_mem_is_valid(unit, mem) &&
        ((SOC_MEM_INFO(unit, mem).blocks | SOC_MEM_INFO(unit, mem).blocks_hi) != 0)) {

       rc = soc_mem_cache_set(unit, mem, block_instance, 1);
       SOCDNX_IF_ERR_EXIT(rc);

    } else {
            SOCDNX_IF_ERR_EXIT(SOC_E_UNAVAIL);
    }
   
exit:
    SOCDNX_FUNC_RETURN;
}

int
dcmn_mem_cache_detach(int unit, soc_reg_t mem, int block_instance)
{
    int rc;
  
    SOCDNX_INIT_FUNC_DEFS;
  
    if (soc_mem_is_valid(unit, mem) &&
            ((SOC_MEM_INFO(unit, mem).blocks | SOC_MEM_INFO(unit, mem).blocks_hi) != 0)) {
        rc = soc_mem_cache_set(unit, mem, block_instance, 0);
        SOCDNX_IF_ERR_EXIT(rc);

    }
    else {
        SOCDNX_IF_ERR_EXIT(SOC_E_UNAVAIL);
    }

exit:
    SOCDNX_FUNC_RETURN;
}

