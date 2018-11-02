/*
 * $Id: interrupt_handler.c,v 1.17 Broadcom SDK $
 *
 * $Copyright: (c) 2016 Broadcom.
 * Broadcom Proprietary and Confidential. All rights reserved.$
 */


#ifdef _ERR_MSG_MODULE_NAME
#error "_ERR_MSG_MODULE_NAME redefined"
#endif
#define _ERR_MSG_MODULE_NAME BSL_BCM_INTR

/* 
 *  include  
 */ 
#include <sal/core/time.h>

#include <soc/dpp/ARAD/arad_interrupts.h>
#include <soc/intr.h>
#include <soc/drv.h>
#include <soc/dpp/ARAD/arad_sw_db.h>

#include <soc/dpp/drv.h>

#include <bcm/error.h>
#include <bcm/debug.h>
#include <bcm/switch.h>

#include <bcm_int/common/debug.h>

#include <appl/diag/system.h>

#include <appl/dpp/interrupts/interrupt_handler.h>
#include <appl/dpp/interrupts/interrupt_handler_cb_func.h>
#include <appl/dpp/interrupts/interrupt_handler_corr_act_func.h>

#include <appl/dcmn/interrupts/interrupt_handler.h>


arad_interrupt_type arad_int_disable_on_init[] = {
    ARAD_INT_LAST
};


arad_interrupt_type arad_int_active_on_init[] = {
/*
 * List of interrupts that are vectors pointing to other interrupt registers
 */
    ARAD_INT_FDR_INTREG1,
    ARAD_INT_FDR_INTREG2,
    ARAD_INT_FDR_INTREG3,
    ARAD_INT_FMAC_INTREG1,
    ARAD_INT_FMAC_INTREG2,
    ARAD_INT_FMAC_INTREG3,
    ARAD_INT_FMAC_INTREG4,
    ARAD_INT_FMAC_INTREG5,
    ARAD_INT_FMAC_INTREG6,
    ARAD_INT_FMAC_INTREG7,
    ARAD_INT_FMAC_INTREG8,
    ARAD_INT_FMAC_INTREG9,
    ARAD_INT_FSRD_INTREG0,
    ARAD_INT_FSRD_INTREG1,
    ARAD_INT_FSRD_INTREG2,
    ARAD_INT_NBI_ECCPARITYINT,
    ARAD_INT_NBI_STATINT,
    ARAD_INT_NBI_LINKSTATUSCHANGEINT,
    ARAD_INT_NBI_ILKNINT,
    ARAD_INT_NBI_STATCNT75P,
    ARAD_INT_NBI_NBITHROWNBURSTSCOUNTERS0_75PINTERRUPT,
    ARAD_INT_EGQ_ERPPDISCARDINTVEC,
    ARAD_INT_EGQ_PKTREASINTVEC,
    ARAD_INT_EGQ_ERPPDISCARDINTVEC2,
    ARAD_INT_EGQ_ERRORECC,
    ARAD_INT_EPNI_ERRORECC,
    ARAD_INT_EPNI_PPINTVEC,
    ARAD_INT_EPNI_ESEMINTERRUPTONE,
    ARAD_INT_CRPS_SRCINVLIDACCESS,
    ARAD_INT_CRPS_PARERRINTERRUPT,
    ARAD_INT_IPT_ECCERRINTERRUPT,
    ARAD_INT_IQM_ECCINTRERR,
    ARAD_INT_IRE_ERRORECC,
    ARAD_INT_IDR_ERRORECC,
    ARAD_INT_IDR_ERRORREASSEMBLY,
    ARAD_INT_IRR_ERRORECC,
    ARAD_INT_IHP_MACTINTERRUPTONE,
    ARAD_INT_IHP_ISAINTERRUPTONE,
    ARAD_INT_IHP_ISBINTERRUPTONE,
    ARAD_INT_IHP_MACTINTERRUPTTWO,
    ARAD_INT_IHB_OEMAINTERRUPTONE,
    ARAD_INT_IHB_OEMBINTERRUPTONE,
    ARAD_INT_SCH_ECCERRORFIXED,
    ARAD_INT_SCH_ECCERROR,
    ARAD_INT_SCH_PARITYERROR,
    ARAD_INT_OAMP_RMAPEMINTERRUPTONE,
    ARAD_INT_OAMP_ERRECC,
    ARAD_INT_MMU_ERRORECC,
    ARAD_INT_OLP_ERRORECC,
/*
 * Parity & ECC error interrupts
 */
    ARAD_INT_RTP_LINKMASKCHANGE,
    ARAD_INT_CFC_PARITYERRINT,
    ARAD_INT_CRPS_PARERRINTERRUPT,
    ARAD_INT_CRPS_PARITYERRINT,
    ARAD_INT_EGQ_PARITYERRINT,
    ARAD_INT_EGQ_DBFECC_1BERRINT,
    ARAD_INT_EGQ_DBFECC_2BERRINT,
    ARAD_INT_EGQ_ECC_1BERRINT,
    ARAD_INT_EGQ_ECC_2BERRINT,
    ARAD_INT_EPNI_ECC_1BERRINT,
    ARAD_INT_EPNI_ECC_2BERRINT,
    ARAD_INT_EPNI_PARITYERRINT,
    ARAD_INT_FCR_ECC_1BERRINT,
    ARAD_INT_FCR_ECC_2BERRINT,
    ARAD_INT_FDR_PRMECC_1BERRINT,
    ARAD_INT_FDR_PRMECC_2BERRINT,
    ARAD_INT_FDR_SECECC_1BERRINT,
    ARAD_INT_FDR_SECECC_2BERRINT,
    ARAD_INT_FDT_ECC_1BERRINT,
    ARAD_INT_FDT_ECC_2BERRINT,
    ARAD_INT_FDT_PARITYERRINT,
    ARAD_INT_FMAC_ECC_1BERRINT,
    ARAD_INT_FMAC_ECC_2BERRINT,
    ARAD_INT_IDR_ECC_1BERRINT,
    ARAD_INT_IDR_ECC_2BERRINT,
    ARAD_INT_IDR_PARITYERRINT,
    ARAD_INT_IHB_ECC_1BERRINT,
    ARAD_INT_IHB_ECC_2BERRINT,
    ARAD_INT_IHB_PARITYERRINT,
    ARAD_INT_IHP_ECC_1BERRINT,
    ARAD_INT_IHP_ECC_2BERRINT,
    ARAD_INT_IHP_PARITYERRINT,
    ARAD_INT_IPS_ECC_1BERRINT,
    ARAD_INT_IPS_ECC_2BERRINT,
    ARAD_INT_IPS_PARITYERRINT,
    ARAD_INT_IPT_ECC_1BERRINT,
    ARAD_INT_IPT_ECC_2BERRINT,
    ARAD_INT_IPT_PARITYERRINT,
    ARAD_INT_IQM_ECC_1BERRINT,
    ARAD_INT_IQM_ECC_2BERRINT,
    ARAD_INT_IQM_PARITYERRINT,
    ARAD_INT_IRE_ECC_1BERRINT,
    ARAD_INT_IRE_ECC_2BERRINT,
    ARAD_INT_IRE_PARITYERRINT,
    ARAD_INT_IRR_ECC_1BERRINT,
    ARAD_INT_IRR_ECC_2BERRINT,
    ARAD_INT_IRR_PARITYERRINT,
    ARAD_INT_MMU_ECC_1BERRINT,
    ARAD_INT_MMU_ECC_2BERRINT,
    ARAD_INT_NBI_ECC_1BERRINT,
    ARAD_INT_NBI_ECC_2BERRINT,
    ARAD_INT_NBI_PARITYERRINT,
/*  ARAD_INT_NBI_ILKNRXPARITYERRINT,  These interrupts are excluded from this list cause ILKN indicates on false alarm for unused lanes
    ARAD_INT_NBI_ILKNTXPARITYERRINT,*/
    ARAD_INT_OAMP_ECC_1BERRINT,
    ARAD_INT_OAMP_ECC_2BERRINT,
    ARAD_INT_OAMP_PARITYERRINT,
    ARAD_INT_OLP_ECC_1BERRINT,
    ARAD_INT_OLP_ECC_2BERRINT,
    ARAD_INT_OLP_PARITYERRINT,
    ARAD_INT_SCH_DCDECCERRORFIXED,
    ARAD_INT_SCH_DHDECCERRORFIXED,
    ARAD_INT_SCH_FDMDECCERRORFIXED,
    ARAD_INT_SCH_FLHCLECCERRORFIXED,
    ARAD_INT_SCH_FLHFQECCERRORFIXED,
    ARAD_INT_SCH_FLHHRECCERRORFIXED,
    ARAD_INT_SCH_FLTCLECCERRORFIXED,
    ARAD_INT_SCH_FLTFQECCERRORFIXED,
    ARAD_INT_SCH_FLTHRECCERRORFIXED,
    ARAD_INT_SCH_FSMECCERRORFIXED,
    ARAD_INT_SCH_SHDDECCERRORFIXED,
    ARAD_INT_SCH_DCDECCERROR,
    ARAD_INT_SCH_DHDECCERROR,
    ARAD_INT_SCH_FDMDECCERROR,
    ARAD_INT_SCH_FLHCLECCERROR,
    ARAD_INT_SCH_FLHFQECCERROR,
    ARAD_INT_SCH_FLHHRECCERROR,
    ARAD_INT_SCH_FLTCLECCERROR,
    ARAD_INT_SCH_FLTFQECCERROR,
    ARAD_INT_SCH_FLTHRECCERROR,
    ARAD_INT_SCH_FSMECCERROR,
    ARAD_INT_SCH_SHDDECCERROR,
    ARAD_INT_SCH_CAL0PARERROR,
    ARAD_INT_SCH_CAL1PARERROR,
    ARAD_INT_SCH_CAL2PARERROR,
    ARAD_INT_SCH_CAL3PARERROR,
    ARAD_INT_SCH_CAL4PARERROR,
    ARAD_INT_SCH_CSDTPARERROR,
    ARAD_INT_SCH_CSSTPARERROR,
    ARAD_INT_SCH_DPNPARERROR,
    ARAD_INT_SCH_DRMPARERROR,
    ARAD_INT_SCH_DSMPARERROR,
    ARAD_INT_SCH_FDMSPARERROR,
    ARAD_INT_SCH_FFMPARERROR,
    ARAD_INT_SCH_FGMPARERROR,
    ARAD_INT_SCH_FIMPARERROR,
    ARAD_INT_SCH_FQMPARERROR,
    ARAD_INT_SCH_FSFPARERROR,
    ARAD_INT_SCH_PSDDPARERROR,
    ARAD_INT_SCH_PSDTPARERROR,
    ARAD_INT_SCH_PSSTPARERROR,
    ARAD_INT_SCH_PSWPARERROR,
    ARAD_INT_SCH_SCCPARERROR,
    ARAD_INT_SCH_SCTPARERROR,
    ARAD_INT_SCH_SEMPARERROR,
    ARAD_INT_SCH_SHCPARERROR,
    ARAD_INT_SCH_SHDSPARERROR,
    ARAD_INT_SCH_SIMPARERROR,
    ARAD_INT_SCH_TMCPARERROR,
    ARAD_INT_IDR_MMUECC_1BERRINT,
    ARAD_INT_IDR_MMUECC_2BERRINT,
    ARAD_INT_LAST
};

arad_interrupt_type ardon_int_active_on_init[] = {
/*
 * List of interrupts that are vectors pointing to other interrupt registers
 */
    ARAD_INT_FDR_INTREG1,
    ARAD_INT_FDR_INTREG2,
    ARAD_INT_FDR_INTREG3,
    ARAD_INT_FMAC_INTREG1,
    ARAD_INT_FMAC_INTREG2,
    ARAD_INT_FMAC_INTREG3,
    ARAD_INT_FMAC_INTREG4,
    ARAD_INT_FMAC_INTREG5,
    ARAD_INT_FMAC_INTREG6,
    ARAD_INT_FMAC_INTREG7,
    ARAD_INT_FMAC_INTREG8,
    ARAD_INT_FMAC_INTREG9,
    ARAD_INT_FSRD_INTREG0,
    ARAD_INT_FSRD_INTREG1,
    ARAD_INT_FSRD_INTREG2,
    ARAD_INT_NBI_ECCPARITYINT,
    ARAD_INT_EGQ_ERPPDISCARDINTVEC,
    ARAD_INT_EGQ_PKTREASINTVEC,
    ARAD_INT_EGQ_ERPPDISCARDINTVEC2,
    ARAD_INT_EGQ_ERRORECC,
    ARAD_INT_EPNI_ERRORECC,
    ARAD_INT_EPNI_PPINTVEC,
    ARAD_INT_CRPS_SRCINVLIDACCESS,
    ARAD_INT_CRPS_PARERRINTERRUPT,
    ARAD_INT_IPT_ECCERRINTERRUPT,
    ARAD_INT_IQM_ECCINTRERR,
    ARAD_INT_IRE_ERRORECC,
    ARAD_INT_IDR_ERRORECC,
    ARAD_INT_IDR_ERRORREASSEMBLY,
    ARAD_INT_IRR_ERRORECC,
    ARAD_INT_SCH_ECCERRORFIXED,
    ARAD_INT_SCH_ECCERROR,
    ARAD_INT_SCH_PARITYERROR,
    ARAD_INT_OAMP_RMAPEMINTERRUPTONE,
    ARAD_INT_OAMP_ERRECC,
    ARAD_INT_MMU_ERRORECC,
    ARAD_INT_OLP_ERRORECC,
    ARAD_INT_CFC_PARITYERRINT,
    ARAD_INT_CRPS_PARERRINTERRUPT,
    ARAD_INT_EGQ_PARITYERRINT,
    ARAD_INT_EGQ_DBFECC_1BERRINT,
    ARAD_INT_EGQ_DBFECC_2BERRINT,
    ARAD_INT_EGQ_ECC_1BERRINT,
    ARAD_INT_EGQ_ECC_2BERRINT,
    ARAD_INT_EPNI_ECC_1BERRINT,
    ARAD_INT_EPNI_ECC_2BERRINT,
    ARAD_INT_FCR_ECC_1BERRINT,
    ARAD_INT_FCR_ECC_2BERRINT,
    ARAD_INT_FDR_PRMECC_1BERRINT,
    ARAD_INT_FDR_PRMECC_2BERRINT,
    ARAD_INT_FDR_SECECC_1BERRINT,
    ARAD_INT_FDR_SECECC_2BERRINT,
    ARAD_INT_FDT_ECC_1BERRINT,
    ARAD_INT_FDT_ECC_2BERRINT,
    ARAD_INT_FMAC_ECC_1BERRINT,
    ARAD_INT_FMAC_ECC_2BERRINT,
    ARAD_INT_IDR_ECC_1BERRINT,
    ARAD_INT_IDR_ECC_2BERRINT,
    ARAD_INT_IDR_PARITYERRINT,
    ARAD_INT_IHP_PARITYERRINT,
    ARAD_INT_IPS_ECC_1BERRINT,
    ARAD_INT_IPS_ECC_2BERRINT,
    ARAD_INT_IPS_PARITYERRINT,
    ARAD_INT_IPT_ECC_1BERRINT,
    ARAD_INT_IPT_ECC_2BERRINT,
    ARAD_INT_IPT_PARITYERRINT,
    ARAD_INT_IQM_ECC_1BERRINT,
    ARAD_INT_IQM_ECC_2BERRINT,
    ARAD_INT_IQM_PARITYERRINT,
    ARAD_INT_IRE_ECC_1BERRINT,
    ARAD_INT_IRE_ECC_2BERRINT,
    ARAD_INT_IRE_PARITYERRINT,
    ARAD_INT_IRR_ECC_1BERRINT,
    ARAD_INT_IRR_ECC_2BERRINT,
    ARAD_INT_IRR_PARITYERRINT,
    ARAD_INT_MMU_ECC_1BERRINT,
    ARAD_INT_MMU_ECC_2BERRINT,
    ARAD_INT_NBI_ECC_1BERRINT,
    ARAD_INT_NBI_ECC_2BERRINT,
    ARAD_INT_NBI_PARITYERRINT,
/*  ARAD_INT_NBI_ILKNRXPARITYERRINT,  These interrupts are excluded from this list cause ILKN indicates on false alarm for unused lanes
    ARAD_INT_NBI_ILKNTXPARITYERRINT,*/
    ARAD_INT_OAMP_ECC_1BERRINT,
    ARAD_INT_OAMP_ECC_2BERRINT,
    ARAD_INT_OAMP_PARITYERRINT,
    ARAD_INT_OLP_ECC_1BERRINT,
    ARAD_INT_OLP_ECC_2BERRINT,
    ARAD_INT_OLP_PARITYERRINT,
    ARAD_INT_SCH_DCDECCERRORFIXED,
    ARAD_INT_SCH_DHDECCERRORFIXED,
    ARAD_INT_SCH_FDMDECCERRORFIXED,
    ARAD_INT_SCH_FLHCLECCERRORFIXED,
    ARAD_INT_SCH_FLHFQECCERRORFIXED,
    ARAD_INT_SCH_FLHHRECCERRORFIXED,
    ARAD_INT_SCH_FLTCLECCERRORFIXED,
    ARAD_INT_SCH_FLTFQECCERRORFIXED,
    ARAD_INT_SCH_FLTHRECCERRORFIXED,
    ARAD_INT_SCH_FSMECCERRORFIXED,
    ARAD_INT_SCH_SHDDECCERRORFIXED,
    ARAD_INT_LAST
};

arad_interrupt_type arad_int_disable_print_on_init[] = {
    ARAD_INT_RTP_LINKMASKCHANGE,
    ARAD_INT_LAST
};

int
arad_interrupt_handler_init_cmn_param(int unit, interrupt_common_params_t* common_params)
{
    int nof_interrupts;
    int rc;

    SOCDNX_INIT_FUNC_DEFS;

    SOCDNX_NULL_CHECK(common_params);

    rc = soc_arad_nof_interrupts(unit, &nof_interrupts);
    SOCDNX_IF_ERR_EXIT(rc);

    common_params->nof_interrupts = nof_interrupts;
    common_params->interrupt_add_interrupt_handler_init = arad_interrupt_add_interrupt_handler_init;
    common_params->interrupt_handle_block_instance = soc_dpp_nof_block_instances;
    common_params->int_disable_on_init = arad_int_disable_on_init;
    common_params->int_disable_print_on_init = arad_int_disable_print_on_init;
    if(SOC_IS_ARDON(unit)) {
        common_params->int_active_on_init = ardon_int_active_on_init;
        common_params->cached_mem = NULL;
    } else {
        common_params->int_active_on_init = arad_int_active_on_init;
        common_params->cached_mem = NULL;
    }


exit:
    SOCDNX_FUNC_RETURN;
}

#undef _ERR_MSG_MODULE_NAME

