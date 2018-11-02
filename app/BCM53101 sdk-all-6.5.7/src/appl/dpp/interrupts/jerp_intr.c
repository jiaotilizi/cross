/*
 * $Id: jerp_appl_intr.c, v1 Broadcom SDK $
 *
 * $Copyright: (c) 2016 Broadcom.
 * Broadcom Proprietary and Confidential. All rights reserved.$
 *
 * Purpose:    Implements application interrupt lists for JERICHO.
 */

/*************
 * INCLUDES  *
 *************/
#include <shared/bsl.h>

#include <soc/dpp/JERP/jerp_intr.h>

#include <bcm/error.h>
#include <bcm/debug.h>
#include <bcm_int/common/debug.h>

#include <appl/diag/system.h>
#include <appl/dcmn/interrupts/dcmn_intr.h>

/*************
 * DEFINES   *
 *************/
#ifdef _ERR_MSG_MODULE_NAME
#error "_ERR_MSG_MODULE_NAME redefined"
#endif
#define _ERR_MSG_MODULE_NAME BSL_APPL_INTR

/*************
 * TYPE DEFS *
 *************/
jerp_interrupt_type jerp_int_disable_on_init[] = {
    INVALIDr
};



jerp_interrupt_type jerp_int_active_on_init[] = {
/*
 * List of interrupts that are vectors pointing to other interrupt registers
 */
    JERP_INT_DRCE_ERROR_ECC,
    JERP_INT_DRCD_ERROR_ECC,
    JERP_INT_MMU_ERROR_ECC,
    JERP_INT_IRE_ERROR_ECC,
    JERP_INT_IRE_EXTERNAL_IF_ERROR,
    JERP_INT_NBIH_ERROR_ECC,
    JERP_INT_NBIH_NBI_PKT_DROP_COUNTERS_0_75P_INTERRUPT,
    JERP_INT_NBIH_LINK_STATUS_CHANGE_INT,
    JERP_INT_ILKN_PML_ERROR_ECC,
    JERP_INT_OLP_ERROR_ECC,
    JERP_INT_IPS_ERROR_ECC,
    JERP_INT_IHP_ERROR_ECC,
    JERP_INT_EDB_ERROR_ECC,
    JERP_INT_EDB_GLEM_INTERRUPT_ONE,
    JERP_INT_DRCC_ERROR_ECC,
    JERP_INT_IDR_ERROR_ECC,
    JERP_INT_IDR_ERROR_REASSEMBLY,
    JERP_INT_DRCH_ERROR_ECC,
    JERP_INT_EPNI_ERROR_ECC,
    JERP_INT_EPNI_PP_INT_VEC,
    JERP_INT_DRCG_ERROR_ECC,
    JERP_INT_FDR_INT_REG_1,
    JERP_INT_FDR_INT_REG_2,
    JERP_INT_FDR_INT_REG_3,
    JERP_INT_FDR_INT_REG_4,
    JERP_INT_FMAC_INT_REG_1,
    JERP_INT_FMAC_INT_REG_2,
    JERP_INT_FMAC_INT_REG_3,
    JERP_INT_FMAC_INT_REG_4,
    JERP_INT_FMAC_INT_REG_5,
    JERP_INT_FMAC_INT_REG_6,
    JERP_INT_FMAC_INT_REG_7,
    JERP_INT_FMAC_INT_REG_8,
    JERP_INT_CRPS_ERROR_ECC,
    JERP_INT_CRPS_ENGINE,
    JERP_INT_CRPS_SRC_INVLID_ACCESS,
    JERP_INT_CRPS_OFFSET_WAS_FILTERED,
    JERP_INT_PPDB_A_ERROR_ECC,
    JERP_INT_PPDB_A_OEMA_INTERRUPT_ONE,
    JERP_INT_PPDB_A_OEMB_INTERRUPT_ONE,
    JERP_INT_CFC_ERROR_ECC,
    JERP_INT_EGQ_ERROR_ECC,
    JERP_INT_EGQ_ERPP_DISCARD_INT_VEC,
    JERP_INT_EGQ_PKT_REAS_INT_VEC,
    JERP_INT_EGQ_ERPP_DISCARD_INT_VEC_2,
    JERP_INT_IRR_ERROR_ECC,
    JERP_INT_MRPS_ERROR_ECC,
    JERP_INT_ILKN_PMH_ERROR_ECC,
    JERP_INT_DRCA_ERROR_ECC,
    JERP_INT_CGM_CGM_REP_AROUND_INT_VEC,
    JERP_INT_OAMP_ERROR_ECC,
    JERP_INT_OAMP_RMAPEM_INTERRUPT_ONE,
    JERP_INT_IHB_ERROR_ECC,
    JERP_INT_IHB_ISEM_INTERRUPT_ONE,
    JERP_INT_DRCF_ERROR_ECC,
    JERP_INT_SCH_ERROR_ECC,
    JERP_INT_IPST_ERROR_ECC,
    JERP_INT_IQM_ERROR_ECC,
    JERP_INT_NBIL_ERROR_ECC,
    JERP_INT_NBIL_NBI_PKT_DROP_COUNTERS_0_75P_INTERRUPT,
    JERP_INT_NBIL_LINK_STATUS_CHANGE_INT,
    JERP_INT_DRCB_ERROR_ECC,
    JERP_INT_IQMT_ERROR_ECC,
    JERP_INT_PPDB_B_ERROR_ECC,
    JERP_INT_PPDB_B_LARGE_EM_INTERRUPT_ONE,
    JERP_INT_PPDB_B_LARGE_EM_INTERRUPT_TWO,
    JERP_INT_ECI_ERROR_ECC,
    JERP_INT_FCR_ERROR_ECC,
    JERP_INT_FDA_ERROR_ECC,
    JERP_INT_FDR_ERROR_ECC,
    JERP_INT_FDT_ERROR_ECC,
    JERP_INT_FMAC_ERROR_ECC,
    JERP_INT_FSRD_ERROR_ECC,
    JERP_INT_IPT_ERROR_ECC,
    JERP_INT_MTRPS_EM_ERROR_ECC,
    JERP_INT_OCB_ERROR_ECC,
    JERP_INT_RTP_ERROR_ECC,

/*
 * Parity & ECC error interrupts
 */
    JERP_INT_DRCE_ECC_PARITY_ERR_INT,
    JERP_INT_DRCE_ECC_ECC_1B_ERR_INT,
    JERP_INT_DRCE_ECC_ECC_2B_ERR_INT,
    JERP_INT_OCB_CRC_ERR_INT,
    JERP_INT_OCB_ECC_PARITY_ERR_INT,
    JERP_INT_OCB_ECC_ECC_1B_ERR_INT,
    JERP_INT_OCB_ECC_ECC_2B_ERR_INT,
    JERP_INT_DRCD_ECC_PARITY_ERR_INT,
    JERP_INT_DRCD_ECC_ECC_1B_ERR_INT,
    JERP_INT_DRCD_ECC_ECC_2B_ERR_INT,
    JERP_INT_MMU_DRAM_OPP_CRC_ERR_INT,
    JERP_INT_MMU_ECC_PARITY_ERR_INT,
    JERP_INT_MMU_ECC_ECC_1B_ERR_INT,
    JERP_INT_MMU_ECC_ECC_2B_ERR_INT,
    JERP_INT_IRE_ECC_PARITY_ERR_INT,
    JERP_INT_IRE_ECC_ECC_1B_ERR_INT,
    JERP_INT_IRE_ECC_ECC_2B_ERR_INT,
    JERP_INT_NBIH_ECC_PARITY_ERR_INT,
    JERP_INT_NBIH_ECC_ECC_1B_ERR_INT,
    JERP_INT_NBIH_ECC_ECC_2B_ERR_INT,
    JERP_INT_ILKN_PML_ECC_PARITY_ERR_INT,
    JERP_INT_ILKN_PML_ECC_ECC_1B_ERR_INT,
    JERP_INT_ILKN_PML_ECC_ECC_2B_ERR_INT,
    JERP_INT_OLP_ECC_PARITY_ERR_INT,
    JERP_INT_OLP_ECC_ECC_1B_ERR_INT,
    JERP_INT_OLP_ECC_ECC_2B_ERR_INT,
    JERP_INT_IPS_CR_FLW_ID_ERR_INT,
    JERP_INT_IPS_ECC_PARITY_ERR_INT,
    JERP_INT_IPS_ECC_ECC_1B_ERR_INT,
    JERP_INT_IPS_ECC_ECC_2B_ERR_INT,
    JERP_INT_IHP_ECC_PARITY_ERR_INT,
    JERP_INT_IHP_ECC_ECC_1B_ERR_INT,
    JERP_INT_IHP_ECC_ECC_2B_ERR_INT,
    JERP_INT_FDA_ECC_PARITY_ERR_INT,
    JERP_INT_FDA_ECC_ECC_1B_ERR_INT,
    JERP_INT_FDA_ECC_ECC_2B_ERR_INT,
    JERP_INT_EDB_ECC_PARITY_ERR_INT,
    JERP_INT_EDB_ECC_ECC_1B_ERR_INT,
    JERP_INT_EDB_ECC_ECC_2B_ERR_INT,
    JERP_INT_DRCC_ECC_PARITY_ERR_INT,
    JERP_INT_DRCC_ECC_ECC_1B_ERR_INT,
    JERP_INT_DRCC_ECC_ECC_2B_ERR_INT,
    JERP_INT_IDR_MMU_ECC_1B_ERR_INT,
    JERP_INT_IDR_MMU_ECC_2B_ERR_INT,
    JERP_INT_IDR_ECC_PARITY_ERR_INT,
    JERP_INT_IDR_ECC_ECC_1B_ERR_INT,
    JERP_INT_IDR_ECC_ECC_2B_ERR_INT,
    JERP_INT_DRCH_ECC_PARITY_ERR_INT,
    JERP_INT_DRCH_ECC_ECC_1B_ERR_INT,
    JERP_INT_DRCH_ECC_ECC_2B_ERR_INT,
    JERP_INT_EPNI_ECC_PARITY_ERR_INT,
    JERP_INT_EPNI_ECC_ECC_1B_ERR_INT,
    JERP_INT_EPNI_ECC_ECC_2B_ERR_INT,
    JERP_INT_IPT_ECC_PARITY_ERR_INT,
    JERP_INT_IPT_ECC_ECC_1B_ERR_INT,
    JERP_INT_IPT_ECC_ECC_2B_ERR_INT,
    JERP_INT_DRCG_ECC_PARITY_ERR_INT,
    JERP_INT_DRCG_ECC_ECC_1B_ERR_INT,
    JERP_INT_DRCG_ECC_ECC_2B_ERR_INT,
    JERP_INT_FDR_ECC_PARITY_ERR_INT,
    JERP_INT_FDR_ECC_ECC_1B_ERR_INT,
    JERP_INT_FDR_ECC_ECC_2B_ERR_INT,
    JERP_INT_FDR_FDR_4_P_1_ECC_1B_ERR_INT,
    JERP_INT_FDR_FDR_4_P_1_ECC_2B_ERR_INT,
    JERP_INT_FDR_FDR_4_P_2_ECC_1B_ERR_INT,
    JERP_INT_FDR_FDR_4_P_2_ECC_2B_ERR_INT,
    JERP_INT_FDR_FDR_4_P_3_ECC_1B_ERR_INT,
    JERP_INT_FDR_FDR_4_P_3_ECC_2B_ERR_INT,
    JERP_INT_FMAC_ECC_PARITY_ERR_INT,
    JERP_INT_FMAC_ECC_ECC_1B_ERR_INT,
    JERP_INT_FMAC_ECC_ECC_2B_ERR_INT,
    JERP_INT_CRPS_ECC_PARITY_ERR_INT,
    JERP_INT_CRPS_ECC_ECC_1B_ERR_INT,
    JERP_INT_CRPS_ECC_ECC_2B_ERR_INT,
    JERP_INT_FDT_ECC_PARITY_ERR_INT,
    JERP_INT_FDT_ECC_ECC_1B_ERR_INT,
    JERP_INT_FDT_ECC_ECC_2B_ERR_INT,
    JERP_INT_PPDB_A_ECC_PARITY_ERR_INT,
    JERP_INT_PPDB_A_ECC_ECC_1B_ERR_INT,
    JERP_INT_PPDB_A_ECC_ECC_2B_ERR_INT,
    JERP_INT_CFC_ECC_PARITY_ERR_INT,
    JERP_INT_CFC_ECC_ECC_1B_ERR_INT,
    JERP_INT_CFC_ECC_ECC_2B_ERR_INT,
    JERP_INT_EGQ_ECC_PARITY_ERR_INT,
    JERP_INT_EGQ_ECC_ECC_1B_ERR_INT,
    JERP_INT_EGQ_ECC_ECC_2B_ERR_INT,
    JERP_INT_RTP_ECC_PARITY_ERR_INT,
    JERP_INT_RTP_ECC_ECC_1B_ERR_INT,
    JERP_INT_RTP_ECC_ECC_2B_ERR_INT,
    JERP_INT_IRR_ECC_PARITY_ERR_INT,
    JERP_INT_IRR_ECC_ECC_1B_ERR_INT,
    JERP_INT_IRR_ECC_ECC_2B_ERR_INT,
    JERP_INT_MRPS_ECC_PARITY_ERR_INT,
    JERP_INT_MRPS_ECC_ECC_1B_ERR_INT,
    JERP_INT_MRPS_ECC_ECC_2B_ERR_INT,
    JERP_INT_ILKN_PMH_ECC_PARITY_ERR_INT,
    JERP_INT_ILKN_PMH_ECC_ECC_1B_ERR_INT,
    JERP_INT_ILKN_PMH_ECC_ECC_2B_ERR_INT,
    JERP_INT_DRCA_ECC_PARITY_ERR_INT,
    JERP_INT_DRCA_ECC_ECC_1B_ERR_INT,
    JERP_INT_DRCA_ECC_ECC_2B_ERR_INT,
    JERP_INT_OAMP_ECC_PARITY_ERR_INT,
    JERP_INT_OAMP_ECC_ECC_1B_ERR_INT,
    JERP_INT_OAMP_ECC_ECC_2B_ERR_INT,
    JERP_INT_IHB_ECC_PARITY_ERR_INT,
    JERP_INT_IHB_ECC_ECC_1B_ERR_INT,
    JERP_INT_IHB_ECC_ECC_2B_ERR_INT,
    JERP_INT_DRCF_ECC_PARITY_ERR_INT,
    JERP_INT_DRCF_ECC_ECC_1B_ERR_INT,
    JERP_INT_DRCF_ECC_ECC_2B_ERR_INT,
    JERP_INT_MTRPS_EM_ECC_PARITY_ERR_INT,
    JERP_INT_MTRPS_EM_ECC_ECC_1B_ERR_INT,
    JERP_INT_MTRPS_EM_ECC_ECC_2B_ERR_INT,
    JERP_INT_FCR_ECC_PARITY_ERR_INT,
    JERP_INT_FCR_ECC_ECC_1B_ERR_INT,
    JERP_INT_FCR_ECC_ECC_2B_ERR_INT,
    JERP_INT_SCH_ECC_PARITY_ERR_INT,
    JERP_INT_SCH_ECC_ECC_1B_ERR_INT,
    JERP_INT_SCH_ECC_ECC_2B_ERR_INT,
    JERP_INT_IPST_ECC_PARITY_ERR_INT,
    JERP_INT_IPST_ECC_ECC_1B_ERR_INT,
    JERP_INT_IPST_ECC_ECC_2B_ERR_INT,
    JERP_INT_IQM_ECC_PARITY_ERR_INT,
    JERP_INT_IQM_ECC_ECC_1B_ERR_INT,
    JERP_INT_IQM_ECC_ECC_2B_ERR_INT,
    JERP_INT_NBIL_ECC_PARITY_ERR_INT,
    JERP_INT_NBIL_ECC_ECC_1B_ERR_INT,
    JERP_INT_NBIL_ECC_ECC_2B_ERR_INT,
    JERP_INT_DRCB_ECC_PARITY_ERR_INT,
    JERP_INT_DRCB_ECC_ECC_1B_ERR_INT,
    JERP_INT_DRCB_ECC_ECC_2B_ERR_INT,
    JERP_INT_IQMT_ECC_PARITY_ERR_INT,
    JERP_INT_IQMT_ECC_ECC_1B_ERR_INT,
    JERP_INT_IQMT_ECC_ECC_2B_ERR_INT,
    JERP_INT_FSRD_ECC_PARITY_ERR_INT,
    JERP_INT_FSRD_ECC_ECC_1B_ERR_INT,
    JERP_INT_FSRD_ECC_ECC_2B_ERR_INT,
    JERP_INT_ECI_ECC_PARITY_ERR_INT,
    JERP_INT_ECI_ECC_ECC_1B_ERR_INT,
    JERP_INT_ECI_ECC_ECC_2B_ERR_INT,
    JERP_INT_PPDB_B_ECC_PARITY_ERR_INT,
    JERP_INT_PPDB_B_ECC_ECC_1B_ERR_INT,
    JERP_INT_PPDB_B_ECC_ECC_2B_ERR_INT,
/*
 * DRC interrupts
 */
    JERP_INT_DRCA_PHY_CDR_ABOVE_TH,
    JERP_INT_DRCB_PHY_CDR_ABOVE_TH,
    JERP_INT_DRCC_PHY_CDR_ABOVE_TH,
    JERP_INT_DRCD_PHY_CDR_ABOVE_TH,
    JERP_INT_DRCE_PHY_CDR_ABOVE_TH,
    JERP_INT_DRCF_PHY_CDR_ABOVE_TH,
    JERP_INT_DRCG_PHY_CDR_ABOVE_TH,
    JERP_INT_DRCH_PHY_CDR_ABOVE_TH,
    INVALIDr
};

jerp_interrupt_type jerp_int_disable_print_on_init[] = {
    INVALIDr
};

/*************
 * FUNCTIONS *
 *************/
int
jerp_interrupt_cmn_param_init(int unit, intr_common_params_t* common_params)
{
    BCMDNX_INIT_FUNC_DEFS;

    BCMDNX_NULL_CHECK(common_params);

    common_params->int_disable_on_init = jerp_int_disable_on_init;
    common_params->int_disable_print_on_init = jerp_int_disable_print_on_init;
    common_params->int_active_on_init = jerp_int_active_on_init;

exit:
    BCMDNX_FUNC_RETURN;
}

#undef _ERR_MSG_MODULE_NAME
