/*
 * $Id: low_level_defines.csv,v 1.1.2.5 Broadcom SDK $
 * 
 * $Copyright: (c) 2016 Broadcom.
 * Broadcom Proprietary and Confidential. All rights reserved.$
 * This file is auto-generated by autoCoder
 * DO NOT EDIT THIS FILE!
 *
 */
#include <shared/bsl.h>
#include <soc/dfe/cmn/dfe_config_imp_defs.h>

#ifdef _ERR_MSG_MODULE_NAME
     #error "_ERR_MSG_MODULE_NAME redefined"
#endif /* _ERR_MSG_MODULE_NAME */

#define _ERR_MSG_MODULE_NAME BSL_SOC_INIT

soc_dfe_implementation_defines_t *soc_dfe_implementation_defines[SOC_MAX_NUM_DEVICES] = {NULL};

int soc_dfe_implementation_defines_init(int unit)
{
    SOCDNX_INIT_FUNC_DEFS;

    switch(SOC_INFO(unit).chip_type){

#ifdef BCM_88750_A0
    case SOC_INFO_CHIP_TYPE_FE1600:
        SOCDNX_IF_ERR_EXIT(soc_fe1600_implementation_defines_init(unit));
        break;
#endif /* BCM_88750_A0 */

#ifdef BCM_88950_A0
    case SOC_INFO_CHIP_TYPE_FE3200:
        SOCDNX_IF_ERR_EXIT(soc_fe3200_implementation_defines_init(unit));
        break;
#endif /* BCM_88950_A0 */

    default:
         SOCDNX_EXIT_WITH_ERR(SOC_E_INIT, (_BSL_SOCDNX_MSG("Defines share autoCoder: Unsupported device, chip type: %d"), SOC_INFO(unit).chip_type));
        break;
    }

exit:
    SOCDNX_FUNC_RETURN;
}

int soc_dfe_implementation_defines_deinit(int unit)
{
    SOCDNX_INIT_FUNC_DEFS;

    switch(SOC_INFO(unit).chip_type){

#ifdef BCM_88750_A0
    case SOC_INFO_CHIP_TYPE_FE1600:
        SOCDNX_IF_ERR_EXIT(soc_fe1600_implementation_defines_deinit(unit));
        break;
#endif /* BCM_88750_A0 */

#ifdef BCM_88950_A0
    case SOC_INFO_CHIP_TYPE_FE3200:
        SOCDNX_IF_ERR_EXIT(soc_fe3200_implementation_defines_deinit(unit));
        break;
#endif /* BCM_88950_A0 */

    default:
         SOCDNX_EXIT_WITH_ERR(SOC_E_INIT, (_BSL_SOCDNX_MSG("Defines share autoCoder: Unsupported device, chip type: %d"), SOC_INFO(unit).chip_type));
        break;
    }

exit:
    SOCDNX_FUNC_RETURN;
}


