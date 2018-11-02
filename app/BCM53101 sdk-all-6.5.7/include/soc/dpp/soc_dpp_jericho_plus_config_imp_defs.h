/*
 * $Id: low_level_defines.csv,v 1.1.2.5 Broadcom SDK $
 * 
 * $Copyright: (c) 2016 Broadcom.
 * Broadcom Proprietary and Confidential. All rights reserved.$
 * This file is auto-generated by autoCoder
 * DO NOT EDIT THIS FILE!
 *
 */
#ifndef SOC_DPP_JERICHO_PLUS_CONFIG_IMP_DEFS
#define SOC_DPP_JERICHO_PLUS_CONFIG_IMP_DEFS

#include <soc/defs.h>
#ifdef BCM_JERICHO_PLUS_SUPPORT


#define SOC_DPP_GET_JERICHO_PLUS(dpp_define)    SOC_DPP_##dpp_define##_JERICHO_PLUS
#define SOC_DPP_NOF_CHANNELIZED_INTERFACES_JERICHO_PLUS               (32)
#define SOC_DPP_NOF_SPECIAL_CHANNELIZED_INTERFACES_JERICHO_PLUS       (4)
#define SOC_DPP_NOF_SPECIAL_NON_CHANNELIZED_INTERFACES_JERICHO_PLUS   (0)
#define SOC_DPP_NOF_NON_CHANNELIZED_INTERFACES_JERICHO_PLUS           (96)
#define SOC_DPP_NOF_CORE_INTERFACES_JERICHO_PLUS                      (128)
#define SOC_DPP_NOF_FEC_BANKS_JERICHO_PLUS                            (8)
#define SOC_DPP_IHP_STP_TABLE_NOF_LONGS_JERICHO_PLUS                  (17)
#define SOC_DPP_IHB_PINFO_PMF_NOF_LONGS_JERICHO_PLUS                  (3)
#define SOC_DPP_IHB_PMF_PROGRAM_SELECTION_CAM_NOF_LONGS_JERICHO_PLUS  (7)
#define SOC_DPP_IHB_FEC_ECMP_NOF_LONGS_JERICHO_PLUS                   (2)
#define SOC_DPP_EGQ_PPCT_NOF_LONGS_JERICHO_PLUS                       (4)
#define SOC_DPP_EPNI_PRGE_PROGRAM_SELECTION_CAM_NOF_LONGS_JERICHO_PLUS (5)
#define SOC_DPP_IHP_LIF_ACCESSED_NOF_LINES_JERICHO_PLUS               (1024)
#define SOC_DPP_IHP_FLP_PROGRAM_SELECTION_CAM_NOF_LONGS_JERICHO_PLUS  (7)
#define SOC_DPP_IHP_FLP_LOOKUPS_NOF_LONGS_JERICHO_PLUS                (6)
#define SOC_DPP_IHB_PTC_INFO_NOF_LONGS_JERICHO_PLUS                   (3)
#define SOC_DPP_MACT_LIF_BASE_LENGTH_JERICHO_PLUS                     (17)
#define SOC_DPP_PPDB_LARGE_EM_FLUSH_DB_NOF_LONGS_JERICHO_PLUS         (8)
#define SOC_DPP_MESH_TOPOLOGY_REGISTER_CONFIG_4_VAL_JERICHO_PLUS      (10)
#define SOC_DPP_EGR_DELETE_FIFO_ALMOST_FULL_MC_LOW_PRIO_JERICHO_PLUS  (66)
#define SOC_DPP_EGR_DELETE_FIFO_ALMOST_FULL_MC_JERICHO_PLUS           (58)
#define SOC_DPP_EGR_DELETE_FIFO_ALMOST_FULL_ALL_JERICHO_PLUS          (50)
#define SOC_DPP_EGR_DELETE_FIFO_THRESHOLD_MAX_JERICHO_PLUS            (0x7f)
#define SOC_DPP_OUTLIF_PROFILE_NOF_BITS_JERICHO_PLUS                  (6)
#define SOC_DPP_DSP_EVENT_ROUTE_ENTRY_NOF_BITS_JERICHO_PLUS           (4)
#define SOC_DPP_MIRROR_SNOOP_DESTINATION_QUEUE_ENCODING_JERICHO_PLUS  (3|17<<8 |18<<16)
#define SOC_DPP_MIRROR_SNOOP_DESTINATION_MULTICAST_ENCODING_JERICHO_PLUS (2|17<<8 |18<<16)
#define SOC_DPP_MIRROR_SNOOP_DESTINATION_SYS_PHY_PORT_ENCODING_JERICHO_PLUS (2|15<<8 |18<<16)
#define SOC_DPP_MIRROR_SNOOP_DESTINATION_LAG_ENCODING_JERICHO_PLUS    (3|15<<8 |18<<16)
#define SOC_DPP_MDIO_INT_DIVIDEND_DEFAULT_JERICHO_PLUS                (1)
#define SOC_DPP_MDIO_INT_FREQ_DEFAULT_JERICHO_PLUS                    (2400)
#define SOC_DPP_MDIO_INT_OUT_DELAY_DEFAULT_JERICHO_PLUS               (0xf)
#define SOC_DPP_CMD_IPT_SNP_MIR_CMD_MAP_SNOOP_OFFSET_JERICHO_PLUS     (1<<4)
#define SOC_DPP_MIRROR_SNOOP_DEST_TM_TABLE_OFFSET_JERICHO_PLUS        (0)
#define SOC_DPP_FLP_INSTRUCTIONS_NOF_JERICHO_PLUS                     (32)
#define SOC_DPP_PP_EG_MIRROR_PROFILE_TABLE_BITS_PER_PROFILE_JERICHO_PLUS (10)
#define SOC_DPP_MIRROR_PROBABILITY_BITS_JERICHO_PLUS                  (24)
#define SOC_DPP_OAM_ID_NOF_BIT_JERICHO_PLUS                           (14)
#define SOC_DPP_ILKN_CTXT_MAP_START_JERICHO_PLUS                      (0)
#define SOC_DPP_NIF_CTXT_MAP_START_JERICHO_PLUS                       (0x600)
#define SOC_DPP_RCY_CTXT_MAP_START_CORE_0_JERICHO_PLUS                (0x690)
#define SOC_DPP_RCY_CTXT_MAP_START_CORE_1_JERICHO_PLUS                (0x790)
#define SOC_DPP_CPU_CTXT_MAP_START_JERICHO_PLUS                       (0x890)
#define SOC_DPP_SAT_CTXT_MAP_START_JERICHO_PLUS                       (0)
#define SOC_DPP_RCY_0_INTERFACE_JERICHO_PLUS                          (145)
#define SOC_DPP_RCY_1_INTERFACE_JERICHO_PLUS                          (146)
#define SOC_DPP_CPU_INTERFACE_JERICHO_PLUS                            (147)
#define SOC_DPP_SAT_INTERFACE_JERICHO_PLUS                            (0)
#define SOC_DPP_EGR_IF_MIN_JERICHO_PLUS                               (28)
#define SOC_DPP_EGR_IF_CPU_JERICHO_PLUS                               (28)
#define SOC_DPP_EGR_IF_OLP_JERICHO_PLUS                               (29)
#define SOC_DPP_EGR_IF_OAMP_JERICHO_PLUS                              (30)
#define SOC_DPP_EGR_IF_RCY_JERICHO_PLUS                               (31)
#define SOC_DPP_EGR_IF_SAT_JERICHO_PLUS                               (0)
#define SOC_DPP_EGR_IF_IPSEC_JERICHO_PLUS                             (0)
#define SOC_DPP_EGR_IF_MAX_JERICHO_PLUS                               (31)
#define SOC_DPP_EGR_TOTAL_PD_JERICHO_PLUS                             (32000)
#define SOC_DPP_EGR_TOTAL_DB_JERICHO_PLUS                             (12000)
#define SOC_DPP_EGR_TOTAL_UC_PD_JERICHO_PLUS                          (6000)
#define SOC_DPP_EGR_TOTAL_UC_DB_JERICHO_PLUS                          (6000)
#define SOC_DPP_EGR_TOTAL_MC_PD_JERICHO_PLUS                          (26000)
#define SOC_DPP_EGR_TOTAL_MC_DB_JERICHO_PLUS                          (6000)
#define SOC_DPP_EGR_TOTAL_UC_FC_PD_JERICHO_PLUS                       (6100)
#define SOC_DPP_EGR_TOTAL_UC_FC_DB_JERICHO_PLUS                       (6100)
#define SOC_DPP_RCI_SEVERITY_FACTOR_1_JERICHO_PLUS                    (4)
#define SOC_DPP_RCI_SEVERITY_FACTOR_2_JERICHO_PLUS                    (5)
#define SOC_DPP_RCI_SEVERITY_FACTOR_3_JERICHO_PLUS                    (6)
#define SOC_DPP_RCI_THRESHOLD_NOF_CONGESTED_LINKS_JERICHO_PLUS        (21)
#define SOC_DPP_KAPS_DMA_LINE_WIDTH_JERICHO_PLUS                      (120)
#define SOC_DPP_KAPS_DMA_ZONE_WIDTH_JERICHO_PLUS                      (30)


int soc_dpp_jericho_plus_implementation_defines_init(int unit);
int soc_dpp_jericho_plus_implementation_defines_deinit(int unit);


#else /* BCM_JERICHO_PLUS_SUPPORT */
#define SOC_DPP_GET_JERICHO_PLUS(dpp_define)    0
#endif /* BCM_JERICHO_PLUS_SUPPORT */
#endif /* SOC_DPP_JERICHO_PLUS_CONFIG_IMP_DEFS */

