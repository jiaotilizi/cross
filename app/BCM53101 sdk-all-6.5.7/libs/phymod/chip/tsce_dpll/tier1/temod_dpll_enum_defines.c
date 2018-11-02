/*----------------------------------------------------------------------
 * : temod_enum_defines.h,
 * : n *
 * Broadcom Corporation
 * Proprietary and Confidential information
 * All rights reserved
 * This source file is the property of Broadcom Corporation, and
 * may not be copied or distributed in any isomorphic form without the
 * prior written consent of Broadcom Corporation.
 *---------------------------------------------------------------------
 *---------------------------------------------------------------------
 ############### THIS FILE IS AUTOMATICALLY GENERATED.  ###############
 ############### DO !! NOT !! MANUALLY EDIT THIS FILE.  ###############
 *---------------------------------------------------------------------
 * Description: This file contains enums, elems, and doxygen comments
 * needed for SerDes Configuration programs.
 *---------------------------------------------------------------------
 * CVS INFORMATION:
 * Please see inc/enum_desc.txt for CVS information.
 *----------------------------------------------------------------------
 */
/*
 * $Id: $
 * $Copyright: (c) 2016 Broadcom.
 * Broadcom Proprietary and Confidential. All rights reserved.$
 */
/* This file is automatically generated. Do not modify it. Modify the
 * inc/enum_desc.txt to change enums, elems, or comments. For issues about
 * the process that creates this file contact the temod2pll development team.
 */

#include "temod_dpll_enum_defines.h"

char* e2s_temod2pll_core_select [CNT_temod2pll_core_select] = {
  "TEMOD2PLL_CORE_0_0_1" ,
  "TEMOD2PLL_CORE_0_1_0" ,
  "TEMOD2PLL_CORE_1_0_0" ,
  "TEMOD2PLL_CORE_0_1_1" ,
  "TEMOD2PLL_CORE_1_0_1" ,
  "TEMOD2PLL_CORE_1_1_1" ,
  "TEMOD2PLL_CORE_ILLEGAL"
}; /* e2s_temod2pll_core_select */

int e2n_temod2pll_core_select [CNT_temod2pll_core_select] = {
  1 ,
  2 ,
  4 ,
  3 ,
  5 ,
  7 ,
  0
}; /* e2n_temod2pll_core_select */

char* e2s_temod2pll_lane_select [CNT_temod2pll_lane_select] = {
  "TEMOD2PLL_LANE_0_0_0_1" ,
  "TEMOD2PLL_LANE_0_0_1_0" ,
  "TEMOD2PLL_LANE_0_0_1_1" ,
  "TEMOD2PLL_LANE_0_1_0_0" ,
  "TEMOD2PLL_LANE_0_1_0_1" ,
  "TEMOD2PLL_LANE_0_1_1_0" ,
  "TEMOD2PLL_LANE_0_1_1_1" ,
  "TEMOD2PLL_LANE_1_0_0_0" ,
  "TEMOD2PLL_LANE_1_0_0_1" ,
  "TEMOD2PLL_LANE_1_0_1_0" ,
  "TEMOD2PLL_LANE_1_0_1_1" ,
  "TEMOD2PLL_LANE_1_1_0_0" ,
  "TEMOD2PLL_LANE_1_1_0_1" ,
  "TEMOD2PLL_LANE_1_1_1_0" ,
  "TEMOD2PLL_LANE_1_1_1_1" ,
  "TEMOD2PLL_LANE_BCST" ,
  "TEMOD2PLL_LANE_ILLEGAL"
}; /* e2s_temod2pll_lane_select */

int e2n_temod2pll_lane_select [CNT_temod2pll_lane_select] = {
  1 ,
  2 ,
  3 ,
  4 ,
  5 ,
  6 ,
  7 ,
  8 ,
  9 ,
  10 ,
  11 ,
  12 ,
  13 ,
  14 ,
  15 ,
  15 ,
  0
}; /* e2n_temod2pll_lane_select */

char* e2s_temod2pll_spd_intfc_type [CNT_temod2pll_spd_intfc_type] = {
  "TEMOD2PLL_SPD_ZERO" ,
  "TEMOD2PLL_SPD_10_X1_SGMII" ,
  "TEMOD2PLL_SPD_100_X1_SGMII" ,
  "TEMOD2PLL_SPD_1000_X1_SGMII" ,
  "TEMOD2PLL_SPD_2500_X1" ,
  "TEMOD2PLL_SPD_10_SGMII" ,
  "TEMOD2PLL_SPD_100_SGMII" ,
  "TEMOD2PLL_SPD_1000_SGMII" ,
  "TEMOD2PLL_SPD_2500" ,
  "TEMOD2PLL_SPD_5000" ,
  "TEMOD2PLL_SPD_1000_XFI" ,
  "TEMOD2PLL_SPD_5000_XFI" ,
  "TEMOD2PLL_SPD_10000_XFI" ,
  "TEMOD2PLL_SPD_10600_XFI_HG" ,
  "TEMOD2PLL_SPD_10000_HI" ,
  "TEMOD2PLL_SPD_10000" ,
  "TEMOD2PLL_SPD_12000_HI" ,
  "TEMOD2PLL_SPD_13000" ,
  "TEMOD2PLL_SPD_15000" ,
  "TEMOD2PLL_SPD_16000" ,
  "TEMOD2PLL_SPD_20000" ,
  "TEMOD2PLL_SPD_20000_SCR" ,
  "TEMOD2PLL_SPD_21000" ,
  "TEMOD2PLL_SPD_25455" ,
  "TEMOD2PLL_SPD_31500" ,
  "TEMOD2PLL_SPD_31500_MLD" ,
  "TEMOD2PLL_SPD_40G_X4" ,
  "TEMOD2PLL_SPD_42G_X4" ,
  "TEMOD2PLL_SPD_40G_XLAUI" ,
  "TEMOD2PLL_SPD_42G_XLAUI" ,
  "TEMOD2PLL_SPD_10000_X2" ,
  "TEMOD2PLL_SPD_10000_HI_DXGXS" ,
  "TEMOD2PLL_SPD_10000_DXGXS" ,
  "TEMOD2PLL_SPD_10000_HI_DXGXS_SCR" ,
  "TEMOD2PLL_SPD_10000_DXGXS_SCR" ,
  "TEMOD2PLL_SPD_10500_HI" ,
  "TEMOD2PLL_SPD_10500_HI_DXGXS" ,
  "TEMOD2PLL_SPD_12773_HI_DXGXS" ,
  "TEMOD2PLL_SPD_12773_DXGXS" ,
  "TEMOD2PLL_SPD_15750_HI_DXGXS" ,
  "TEMOD2PLL_SPD_20G_MLD_DXGXS" ,
  "TEMOD2PLL_SPD_21G_HI_MLD_DXGXS" ,
  "TEMOD2PLL_SPD_20G_DXGXS" ,
  "TEMOD2PLL_SPD_21G_HI_DXGXS" ,
  "TEMOD2PLL_SPD_100G_CR10" ,
  "TEMOD2PLL_SPD_107G_HG_CR10" ,
  "TEMOD2PLL_SPD_120G_CR12" ,
  "TEMOD2PLL_SPD_127G_HG_CR12" ,
  "TEMOD2PLL_SPD_4000" ,
  "TEMOD2PLL_SPD_10000_X4_10P3" ,
  "TEMOD2PLL_SPD_10000_CX4_10P3" ,
  "TEMOD2PLL_SPD_10000_KX4_10P3" ,
  "TEMOD2PLL_SPD_12P12_XFI" ,
  "TEMOD2PLL_SPD_24P24_MLD_DXGXS" ,
  "TEMOD2PLL_SPD_48P48_MLD" ,
  "TEMOD2PLL_SPD_21P21G_HG_DXGXS" ,
  "TEMOD2PLL_SPD_42P42G_HG2" ,
  "TEMOD2PLL_SPD_ILLEGAL"
}; /* e2s_temod2pll_spd_intfc_type */

int e2n_temod2pll_spd_intfc_type [CNT_temod2pll_spd_intfc_type] = {
  0 ,
  10 ,
  100 ,
  1000 ,
  2500 ,
  10 ,
  100 ,
  1000 ,
  2500 ,
  5000 ,
  5000 ,
  5000 ,
  10000 ,
  10560 ,
  10000 ,
  10000 ,
  12000 ,
  13000 ,
  15000 ,
  16000 ,
  20000 ,
  20000 ,
  21000 ,
  25000 ,
  31500 ,
  31500 ,
  40000 ,
  40000 ,
  40000 ,
  42000 ,
  10000 ,
  10000 ,
  10000 ,
  10000 ,
  10000 ,
  10500 ,
  10500 ,
  12773 ,
  12773 ,
  15750 ,
  20000 ,
  20000 ,
  20000 ,
  21000 ,
  100000 ,
  107000 ,
  120000 ,
  127000 ,
  4000 ,
  10000 ,
  10000 ,
  10000 ,
  12120 ,
  24240 ,
  48480 ,
  21210 ,
  42420 ,
  0
}; /* e2n_temod2pll_spd_intfc_type */

char* e2s_temod2pll_regacc_type [CNT_temod2pll_regacc_type] = {
  "TEMOD2PLL_REGACC_CL22" ,
  "TEMOD2PLL_REGACC_CL45" ,
  "TEMOD2PLL_REGACC_TOTSC" ,
  "TEMOD2PLL_REGACC_SBUS_FD" ,
  "TEMOD2PLL_REGACC_SBUS_BD" ,
  "TEMOD2PLL_REGACC_ILLEGAL"
}; /* e2s_temod2pll_regacc_type */

char* e2s_temod2pll_port_type [CNT_temod2pll_port_type] = {
  "TEMOD2PLL_SINGLE_PORT" ,
  "TEMOD2PLL_MULTI_PORT" ,
  "TEMOD2PLL_DXGXS" ,
  "TEMOD2PLL_TRI1_PORT" ,
  "TEMOD2PLL_TRI2_PORT" ,
  "TEMOD2PLL_PORT_MODE_ILLEGAL"
}; /* e2s_temod2pll_port_type */

char* e2s_temod2pll_diag_type [CNT_temod2pll_diag_type] = {
  "TEMOD2PLL_DIAG_GENERAL" ,
  "TEMOD2PLL_DIAG_TOPOLOGY" ,
  "TEMOD2PLL_DIAG_LINK" ,
  "TEMOD2PLL_DIAG_SPEED" ,
  "TEMOD2PLL_DIAG_ANEG" ,
  "TEMOD2PLL_DIAG_TFC" ,
  "TEMOD2PLL_DIAG_AN_TIMERS" ,
  "TEMOD2PLL_DIAG_STATE" ,
  "TEMOD2PLL_DIAG_DEBUG" ,
  "TEMOD2PLL_DIAG_IEEE" ,
  "TEMOD2PLL_DIAG_EEE" ,
  "TEMOD2PLL_DIAG_BER" ,
  "TEMOD2PLL_DIAG_CFG" ,
  "TEMOD2PLL_DIAG_CL72" ,
  "TEMOD2PLL_DIAG_DSC",
  "TEMOD2PLL_SERDES_DIAG" ,
  "TEMOD2PLL_DIAG_ALL" ,
  "TEMOD2PLL_DIAG_ILLEGAL"
}; /* e2s_temod2pll_diag_type */

char* e2s_temod2pll_pmd_diag_type [CNT_temod2pll_pmd_diag_type] = {
  "TEMOD2PLL_SERDES_DIAG_CORE_CONFIG" ,
  "TEMOD2PLL_SERDES_DIAG_CORE_STATE" ,
  "TEMOD2PLL_SERDES_DIAG_LANE_CONFIG" ,
  "TEMOD2PLL_SERDES_DIAG_LANE_DEBUG_STATUS" ,
  "TEMOD2PLL_SERDES_DIAG_LANE_STATE" ,
  "TEMOD2PLL_SERDES_DIAG_LANE_STATE_HDR" ,
  "TEMOD2PLL_SERDES_DIAG_LANE_STATE_LEGEND" ,
  "TEMOD2PLL_SERDES_DIAG_CL72_STATUS" ,
  "TEMOD2PLL_SERDES_DIAG_EYE_DENSITY" ,
  "TEMOD2PLL_SERDES_DIAG_EYE_SCAN" ,
  "TEMOD2PLL_SERDES_DIAG_MEAS_EYE_DENSITY_DATA" ,
  "TEMOD2PLL_SERDES_DIAG_MEAS_EYE_SCAN_DONE" ,
  "TEMOD2PLL_SERDES_DIAG_MEAS_LOWBER_EYE" ,
  "TEMOD2PLL_SERDES_DIAG_READ_EYE_SCAN_STRIPE" ,
  "TEMOD2PLL_SERDES_DIAG_EYE_DENSITY_DATA" ,
  "TEMOD2PLL_SERDES_DIAG_LOWBER_EYE" ,
  "TEMOD2PLL_SERDES_DIAG_EYE_SCAN_VERTICAL" ,
  "TEMOD2PLL_SERDES_DIAG_EYE_SCAN_STRIPE" ,
  "TEMOD2PLL_SERDES_DIAG_EYE_SCAN_HEADER" ,
  "TEMOD2PLL_SERDES_DIAG_EYE_SCAN_FOOTER" ,
  "TEMOD2PLL_SERDES_DIAG_BER_SCAN_TEST" ,
  "TEMOD2PLL_SERDES_DIAG_READ_BER_SCAN_DATA" ,
  "TEMOD2PLL_SERDES_DIAG_EYE_MARGIN_PROJ" ,
  "TEMOD2PLL_SERDES_DIAG_DIG_LPBK" ,
  "TEMOD2PLL_SERDES_DIAG_MEAS_EYE_SCAN_START" ,
  "TEMOD2PLL_SERDES_DIAG_ILLEGAL"
}; /* e2s_temod2pll_pmd_diag_type */

char* e2s_temod2pll_an_type [CNT_temod2pll_an_type] = {
  "TEMOD2PLL_CL73" ,
  "TEMOD2PLL_CL37" ,
  "TEMOD2PLL_CL73_BAM" ,
  "TEMOD2PLL_CL37_BAM" ,
  "TEMOD2PLL_CL37_SGMII" ,
  "TEMOD2PLL_HPAM" ,
  "TEMOD2PLL_AN_TYPE_ILLEGAL"
}; /* e2s_temod2pll_an_type */

char* e2s_temod2pll_eye_direction [CNT_temod2pll_eye_direction] = {
  "TEMOD2PLL_EYE_VU" ,
  "TEMOD2PLL_EYE_VD" ,
  "TEMOD2PLL_EYE_HL" ,
  "TEMOD2PLL_EYE_HR" ,
  "TEMOD2PLL_EYE_ILLEGAL"
}; /* e2s_temod2pll_eye_direction */

char* e2s_temod2pll_tech_ability [CNT_temod2pll_tech_ability] = {
  "TEMOD2PLL_ABILITY_1G_KX" ,
  "TEMOD2PLL_ABILITY_10G_KX4" ,
  "TEMOD2PLL_ABILITY_10G_KR" ,
  "TEMOD2PLL_ABILITY_40G_KR4" ,
  "TEMOD2PLL_ABILITY_40G_CR4" ,
  "TEMOD2PLL_ABILITY_100G_CR10" ,
  "TEMOD2PLL_ABILITY_20G_KR2" ,
  "TEMOD2PLL_ABILITY_20G_CR2" ,
  "TEMOD2PLL_ABILITY_ILLEGAL"
}; /* e2s_temod2pll_tech_ability */

int e2n_temod2pll_tech_ability [CNT_temod2pll_tech_ability] = {
  0x5 ,
  0x6 ,
  0x7 ,
  0x8 ,
  0x9 ,
  0xa ,
  0x100 ,
  0x101 ,
  0x102
}; /* e2n_temod2pll_tech_ability */

char* e2s_temod2pll_cl37bam_ability [CNT_temod2pll_cl37bam_ability] = {
  "TEMOD2PLL_BAM37ABL_2P5G" ,
  "TEMOD2PLL_BAM37ABL_5G_X4" ,
  "TEMOD2PLL_BAM37ABL_6G_X4" ,
  "TEMOD2PLL_BAM37ABL_10G_HIGIG" ,
  "TEMOD2PLL_BAM37ABL_10G_CX4" ,
  "TEMOD2PLL_BAM37ABL_12G_X4" ,
  "TEMOD2PLL_BAM37ABL_12P5_X4" ,
  "TEMOD2PLL_BAM37ABL_13G_X4" ,
  "TEMOD2PLL_BAM37ABL_15G_X4" ,
  "TEMOD2PLL_BAM37ABL_16G_X4" ,
  "TEMOD2PLL_BAM37ABL_20G_X4_CX4" ,
  "TEMOD2PLL_BAM37ABL_20G_X4" ,
  "TEMOD2PLL_BAM37ABL_21G_X4" ,
  "TEMOD2PLL_BAM37ABL_25P455G" ,
  "TEMOD2PLL_BAM37ABL_31P5G" ,
  "TEMOD2PLL_BAM37ABL_32P7G" ,
  "TEMOD2PLL_BAM37ABL_40G" ,
  "TEMOD2PLL_BAM37ABL_10G_X2_CX4" ,
  "TEMOD2PLL_BAM37ABL_10G_DXGXS" ,
  "TEMOD2PLL_BAM37ABL_10P5G_DXGXS" ,
  "TEMOD2PLL_BAM37ABL_12P7_DXGXS" ,
  "TEMOD2PLL_BAM37ABL_15P75G_R2" ,
  "TEMOD2PLL_BAM37ABL_20G_X2_CX4" ,
  "TEMOD2PLL_BAM37ABL_20G_X2" ,
  "TEMOD2PLL_BAM37ABL_ILLEGAL"
}; /* e2s_temod2pll_cl37bam_ability */

char* e2s_temod2pll_diag_an_type [CNT_temod2pll_diag_an_type] = {
  "TEMOD2PLL_DIAG_AN_DONE" ,
  "TEMOD2PLL_DIAG_AN_HCD" ,
  "TEMOD2PLL_DIAG_AN_TYPE_ILLEGAL"
}; /* e2s_temod2pll_diag_an_type */

char* e2s_temod2pll_tier1_function_type [CNT_temod2pll_tier1_function_type] = {
  "PCS_BYPASS_CTL" ,
  "INIT_PCS" ,
  "INIT_PMD_SW" ,
  "INIT_PMD" ,
  "PMD_RESET_SEQ" ,
  "PMD_X4_RESET" ,
  "WAIT_SC_DONE" ,
  "ENABLE_SET" ,
  "FECMODE_SET" ,
  "GET_PCS_LINK_STATUS" ,
  "OVERRIDE_SET" ,
  "CREDIT_OVERRIDE_SET" ,
  "ENCODE_SET" ,
  "DECODE_SET" ,
  "CREDIT_CONTROL" ,
  "TX_LANE_CONTROL" ,
  "RX_LANE_CONTROL" ,
  "TX_LANE_DISABLE" ,
  "POWER_CONTROL" ,
  "AUTONEG_SET" ,
  "AUTONEG_GET" ,
  "AUTONEG_CONTROL" ,
  "TSC12_CONTROL" ,
  "CHECK_SC_STATS" ,
  "REG_READ" ,
  "REG_WRITE" ,
  "PRBS_CHECK" ,
  "CJPAT_CRPAT_MODE_SET" ,
  "CJPAT_CRPAT_CHECK" ,
  "TEMOD2PLL_DIAG" ,
  "PCS_LANE_SWAP" ,
  "PMD_LANE_SWAP" ,
  "PMD_LANE_SWAP_TX" ,
  "PARALLEL_DETECT_CONTROL" ,
  "REVID_READ" ,
  "SOFT_RESET" ,
  "SET_SPD_INTF" ,
  "SET_PORT_MODE" ,
  "EEE_PASSTHRU_SET" ,
  "EEE_PASSTHRU_GET" ,
  "FEC_CONTROL" ,
  "HIGIG2_CONTROL" ,
  "LF_RF_CONTROL" ,
  "RX_FAST_LOCK_CONTROL" ,
  "PMD_CORE_RESET" ,
  "PMD_LANE_RESET" ,
  "AFE_SPEED_UP_DSC_VGA" ,
  "CLAUSE_72_CONTROL" ,
  "PLL_SEQUENCER_CONTROL" ,
  "PLL_LOCK_WAIT" ,
  "PROG_DATA" ,
  "RX_SEQ_CONTROL" ,
  "SET_POLARITY" ,
  "PRBS_CONTROL" ,
  "PRBS_MODE" ,
  "RX_PF_CONTROL" ,
  "RX_VGA_CONTROL" ,
  "CJPAT_CRPAT_CONTROL" ,
  "TX_LOOPBACK_CONTROL" ,
  "TX_PMD_LOOPBACK_CONTROL" ,
  "RX_LOOPBACK_CONTROL" ,
  "DBG_MASK_LPBK_EN" ,
  "DBG_MASK_LPBK_DIS" ,
  "RX_P1_SLICER_CONTROL" ,
  "RX_M1_SLICER_CONTROL" ,
  "RX_D_SLICER_CONTROL" ,
  "WAIT_PMD_LOCK" ,
  "FIRMWARE_SET" ,
  "INIT_PMD_QSGMII" ,
  "INIT_PCS_ILKN" ,
  "PMD_RESET_BYPASS" ,
  "PMD_OVERRIDE_CONTROL" ,
  "PCS_1588_CONTROL" ,
  "SET_1588_FCLK" ,
  "SET_1588_UI_VALUES" ,
  "SET_1588_TXRX_FIXED_LATENCY" ,
  "SET_1588_RX_DESKEW" ,
  "SET_1588_NO_PMD_TXRX_FIXED_LATENCY" ,
  "READ_INFO_ADET" ,
  "TIER1_FUNCTION_ILLEGAL"
}; /* e2s_temod2pll_tier1_function_type */

char* e2s_temod2pll_sc_mode_type [CNT_sc_mode_type] = {
  "TEMOD2PLL_SC_MODE_HT_WITH_BASIC_OVERRIDE" ,
  "TEMOD2PLL_SC_MODE_HT_OVERRIDE" ,
  "TEMOD2PLL_SC_MODE_ST" ,
  "TEMOD2PLL_SC_MODE_ST_OVERRIDE" ,
  "TEMOD2PLL_SC_MODE_AN_CL37" ,
  "TEMOD2PLL_SC_MODE_AN_CL73" ,
  "TEMOD2PLL_SC_MODE_BYPASS" ,
  "TEMOD2PLL_SC_MODE_ILLEGAL"
}; /* e2s_temod2pll_sc_mode_type */

int e2n_temod2pll_sc_mode_type [CNT_sc_mode_type] = {
  0 ,
  1 ,
  2 ,
  3 ,
  4 ,
  5 ,
  6 ,
  7
}; /* e2n_temod2pll_sc_mode_type */

char* e2s_temod2pll_pll_mode_type [CNT_temod2pll_pll_mode_type] = {
  "TEMOD2PLL_PLL_MODE_DIV_ZERO" ,
  "TEMOD2PLL_PLL_MODE_DIV_72" ,
  "TEMOD2PLL_PLL_MODE_DIV_40" ,
  "TEMOD2PLL_PLL_MODE_DIV_42" ,
  "TEMOD2PLL_PLL_MODE_DIV_48" ,
  "TEMOD2PLL_PLL_MODE_DIV_50" ,
  "TEMOD2PLL_PLL_MODE_DIV_52" ,
  "TEMOD2PLL_PLL_MODE_DIV_54" ,
  "TEMOD2PLL_PLL_MODE_DIV_60" ,
  "TEMOD2PLL_PLL_MODE_DIV_64" ,
  "TEMOD2PLL_PLL_MODE_DIV_66" ,
  "TEMOD2PLL_PLL_MODE_DIV_68" ,
  "TEMOD2PLL_PLL_MODE_DIV_70" ,
  "TEMOD2PLL_PLL_MODE_DIV_80" ,
  "TEMOD2PLL_PLL_MODE_DIV_92" ,
  "TEMOD2PLL_PLL_MODE_DIV_100" ,
  "TEMOD2PLL_PLL_MODE_DIV_82P5" ,
  "TEMOD2PLL_PLL_MODE_DIV_87P5" ,
  "TEMOD2PLL_PLL_MODE_DIV_ILLEGAL"
}; /* e2s_temod2pll_pll_mode_type */

int e2n_temod2pll_pll_mode_type [CNT_temod2pll_pll_mode_type] = {
  0 ,
  40 ,
  42 ,
  48 ,
  52 ,
  54 ,
  60 ,
  64 ,
  66 ,
  70 ,
  80 ,
  92 ,
  0
}; /* e2n_temod2pll_pll_mode_type */

char* e2s_temod2pll_os_mode_type [CNT_temod2pll_os_mode_type] = {
  "TEMOD2PLL_PMA_OS_MODE_1" ,
  "TEMOD2PLL_PMA_OS_MODE_2" ,
  "TEMOD2PLL_PMA_OS_MODE_3" ,
  "TEMOD2PLL_PMA_OS_MODE_3_3" ,
  "TEMOD2PLL_PMA_OS_MODE_4" ,
  "TEMOD2PLL_PMA_OS_MODE_5" ,
  "TEMOD2PLL_PMA_OS_MODE_7_25" ,
  "TEMOD2PLL_PMA_OS_MODE_8" ,
  "TEMOD2PLL_PMA_OS_MODE_8_25" ,
  "TEMOD2PLL_PMA_OS_MODE_10" ,
  "TEMOD2PLL_PMA_OS_MODE_ILLEGAL"
}; /* e2s_temod2pll_os_mode_type */

int e2n_temod2pll_os_mode_type [CNT_temod2pll_os_mode_type] = {
  1 ,
  2 ,
  3 ,
  33 ,
  4 ,
  5 ,
  725 ,
  8 ,
  825 ,
  9 ,
  0
}; /* e2n_temod2pll_os_mode_type */

char* e2s_temod2pll_scr_mode [CNT_temod2pll_scr_mode] = {
  "TEMOD2PLL_SCR_MODE_BYPASS" ,
  "TEMOD2PLL_SCR_MODE_66B" ,
  "TEMOD2PLL_SCR_MODE_80B" ,
  "TEMOD2PLL_SCR_MODE_64B"
}; /* e2s_temod2pll_scr_mode */

int e2n_temod2pll_scr_mode [CNT_temod2pll_scr_mode] = {
  0 ,
  1 ,
  2 ,
  3
}; /* e2n_temod2pll_scr_mode */

char* e2s_temod2pll_encode_mode [CNT_temod2pll_encode_mode] = {
  "TEMOD2PLL_ENCODE_MODE_NONE" ,
  "TEMOD2PLL_ENCODE_MODE_CL48" ,
  "TEMOD2PLL_ENCODE_MODE_CL48_2_LANE" ,
  "TEMOD2PLL_ENCODE_MODE_CL36" ,
  "TEMOD2PLL_ENCODE_MODE_CL82" ,
  "TEMOD2PLL_ENCODE_MODE_CL49" ,
  "TEMOD2PLL_ENCODE_MODE_BRCM" ,
  "TEMOD2PLL_ENCODE_MODE_ILLEGAL"
}; /* e2s_temod2pll_encode_mode */

int e2n_temod2pll_encode_mode [CNT_temod2pll_encode_mode] = {
  0 ,
  1 ,
  2 ,
  3 ,
  4 ,
  5 ,
  6 ,
  7
}; /* e2n_temod2pll_encode_mode */

char* e2s_temod2pll_check_end_mode [CNT_temod2pll_check_end_mode] = {
  "TEMOD2PLL_CL48_CHECK_END_OFF" ,
  "TEMOD2PLL_CL48_CHECK_END_ON"
}; /* e2s_temod2pll_check_end_mode */

char* e2s_temod2pll_sigdet_filter [CNT_temod2pll_sigdet_filter] = {
  "TEMOD2PLL_SIGDET_FILTER_NONCX4" ,
  "TEMOD2PLL_SIGDET_FILTER_CX4"
}; /* e2s_temod2pll_sigdet_filter */

char* e2s_temod2pll_blocksync_mode [CNT_temod2pll_blocksync_mode] = {
  "TEMOD2PLL_BLOCKSYNC_MODE_NONE" ,
  "TEMOD2PLL_BLOCKSYNC_MODE_CL49" ,
  "TEMOD2PLL_BLOCKSYNC_MODE_CL82" ,
  "TEMOD2PLL_BLOCKSYNC_MODE_8B10B" ,
  "TEMOD2PLL_BLOCKSYNC_MODE_FEC" ,
  "TEMOD2PLL_BLOCKSYNC_MODE_BRCM" ,
  "TEMOD2PLL_BLOCKSYNC_MODE_ILLEGAL"
}; /* e2s_temod2pll_blocksync_mode */

char* e2s_temod2pll_reorder_mode [CNT_temod2pll_reorder_mode] = {
  "TEMOD2PLL_R_REORDER_MODE_NONE" ,
  "TEMOD2PLL_R_REORDER_MODE_CL48" ,
  "TEMOD2PLL_R_REORDER_MODE_CL36" ,
  "TEMOD2PLL_R_REORDER_MODE_CL36_CL48"
}; /* e2s_temod2pll_reorder_mode */

char* e2s_temod2pll_cl36_mode [CNT_temod2pll_cl36_mode] = {
  "TEMOD2PLL_CL36_DISABLE" ,
  "TEMOD2PLL_CL36_ENABLE"
}; /* e2s_temod2pll_cl36_mode */

char* e2s_temod2pll_descrambler_mode [CNT_temod2pll_descrambler_mode] = {
  "TEMOD2PLL_R_DESCR1_MODE_BYPASS" ,
  "TEMOD2PLL_R_DESCR1_MODE_66B" ,
  "TEMOD2PLL_R_DESCR1_MODE_10B" ,
  "TEMOD2PLL_R_DESCR1_MODE_ILLEGAL"
}; /* e2s_temod2pll_descrambler_mode */

char* e2s_temod2pll_decoder_mode [CNT_temod2pll_decoder_mode] = {
  "TEMOD2PLL_DECODER_MODE_NONE" ,
  "TEMOD2PLL_DECODER_MODE_CL49" ,
  "TEMOD2PLL_DECODER_MODE_BRCM" ,
  "TEMOD2PLL_DECODER_MODE_ALU" ,
  "TEMOD2PLL_DECODER_MODE_CL48" ,
  "TEMOD2PLL_DECODER_MODE_CL36" ,
  "TEMOD2PLL_DECODER_MODE_CL82" ,
  "TEMOD2PLL_DECODER_MODE_ILLEGAL"
}; /* e2s_temod2pll_decoder_mode */

char* e2s_temod2pll_deskew_mode [CNT_temod2pll_deskew_mode] = {
  "TEMOD2PLL_R_DESKEW_MODE_BYPASS" ,
  "TEMOD2PLL_R_DESKEW_MODE_8B_10B" ,
  "TEMOD2PLL_R_DESKEW_MODE_BRCM_66B" ,
  "TEMOD2PLL_R_DESKEW_MODE_CL82_66B" ,
  "TEMOD2PLL_R_DESKEW_MODE_CL36_10B" ,
  "TEMOD2PLL_R_DESKEW_MODE_ILLEGAL"
}; /* e2s_temod2pll_deskew_mode */

char* e2s_temod2pll_descrambler2_mode [CNT_temod2pll_descrambler2_mode] = {
  "TEMOD2PLL_DESC2_MODE_NONE" ,
  "TEMOD2PLL_DESC2_MODE_CL49" ,
  "TEMOD2PLL_DESC2_MODE_BRCM" ,
  "TEMOD2PLL_DESC2_MODE_ALU" ,
  "TEMOD2PLL_DESC2_MODE_CL48" ,
  "TEMOD2PLL_DESC2_MODE_CL36" ,
  "TEMOD2PLL_DESC2_MODE_CL82" ,
  "TEMOD2PLL_DESC2_MODE_ILLEGAL"
}; /* e2s_temod2pll_descrambler2_mode */

char* e2s_temod2pll_byte_del_mode [CNT_temod2pll_byte_del_mode] = {
  "TEMOD2PLL_R_DESC2_BYTE_DELETION_100M" ,
  "TEMOD2PLL_R_DESC2_BYTE_DELETION_10M" ,
  "TEMOD2PLL_R_DESC2_BYTE_DELETION_NONE"
}; /* e2s_temod2pll_byte_del_mode */

char* e2s_temod2pll_decode_descr_mode [CNT_temod2pll_decode_descr_mode] = {
  "TEMOD2PLL_R_DEC1_DESCR_MODE_NONE" ,
  "TEMOD2PLL_R_DEC1_DESCR_MODE_BRCM64B66B"
}; /* e2s_temod2pll_decode_descr_mode */

char* e2s_temod2pll_an_property_enable [CNT_an_property_enable] = {
  "TEMOD2PLL_AN_PROPERTY_ENABLE_NONE" ,
  "TEMOD2PLL_AN_PROPERTY_ENABLE_SGMII_MASTER_MODE" ,
  "TEMOD2PLL_AN_PROPERTY_ENABLE_AN_PD_TO_CL37" ,
  "TEMOD2PLL_AN_PROPERTY_ENABLE_SGMII_TO_CL37_AUTO" ,
  "TEMOD2PLL_AN_PROPERTY_ENABLE_CL37_BAM_to_SGMII_AUTO" ,
  "TEMOD2PLL_AN_PROPERTY_ENABLE_HPAM_TO_CL73_AUTO" ,
  "TEMOD2PLL_AN_PROPERTY_ENABLE_CL73_BAM_TO_HPAM_AUTO" ,
  "TEMOD2PLL_AN_PROPERTY_ENABLE_ILLEGAL"
}; /* e2s_temod2pll_an_property_enable */

char* e2s_temod2pll_credit_type_t [CNT_credit_type_t] = {
  "TEMOD2PLL_CREDIT_RESET" ,
  "TEMOD2PLL_CREDIT_TABLE" ,
  "TEMOD2PLL_CREDIT_CLOCK_COUNT_0" ,
  "TEMOD2PLL_CREDIT_CLOCK_COUNT_1" ,
  "TEMOD2PLL_CREDIT_LOOP_COUNT_0" ,
  "TEMOD2PLL_CREDIT_LOOP_COUNT_1" ,
  "TEMOD2PLL_CREDIT_MAC" ,
  "TEMOD2PLL_CREDIT_PCS_CLOCK_COUNT_0" ,
  "TEMOD2PLL_CREDIT_PCS_GEN_COUNT" ,
  "TEMOD2PLL_CREDIT_EN" ,
  "TEMOD2PLL_CREDIT_PCS_REPCNT" ,
  "TEMOD2PLL_CREDIT_SGMII_SPD" ,
  "TEMOD2PLL_CREDIT_ILLEGAL"
}; /* e2s_temod2pll_credit_type_t */

char* e2s_temod2pll_override_type_t [CNT_override_type_t] = {
  "TEMOD2PLL_OVERRIDE_RESET" ,
  "TEMOD2PLL_OVERRIDE_CL72" ,
  "TEMOD2PLL_OVERRIDE_SPDID" ,
  "TEMOD2PLL_OVERRIDE_NUM_LANES" ,
  "TEMOD2PLL_OVERRIDE_OS_MODE" ,
  "TEMOD2PLL_OVERRIDE_FEC_EN" ,
  "TEMOD2PLL_OVERRIDE_DESKEW_MODE" ,
  "TEMOD2PLL_OVERRIDE_DESC2_MODE" ,
  "TEMOD2PLL_OVERRIDE_CL36BYTEDEL_MODE" ,
  "TEMOD2PLL_OVERRIDE_BRCM64B66_DESCR_MODE" ,
  "TEMOD2PLL_OVERRIDE_CHKEND_EN" ,
  "TEMOD2PLL_OVERRIDE_BLKSYNC_MODE" ,
  "TEMOD2PLL_OVERRIDE_DECODE_MODE" ,
  "TEMOD2PLL_OVERRIDE_REORDER_EN" ,
  "TEMOD2PLL_OVERRIDE_CL36_EN" ,
  "TEMOD2PLL_OVERRIDE_SCR_MODE" ,
  "TEMOD2PLL_OVERRIDE_DESCR_MODE" ,
  "TEMOD2PLL_OVERRIDE_ENCODE_MODE" ,
  "TEMOD2PLL_OVERRIDE_ALL"
}; /* e2s_temod2pll_override_type_t */

char* e2s_temod2pll_ref_clk_t [CNT_temod2pll_ref_clk_t] = {
  "TEMOD2PLLREFCLK156MHZ" ,
  "TEMOD2PLLREFCLK125MHZ" ,
  "TEMOD2PLLREFCLKCOUNT"
}; /* e2s_temod2pll_ref_clk_t */

