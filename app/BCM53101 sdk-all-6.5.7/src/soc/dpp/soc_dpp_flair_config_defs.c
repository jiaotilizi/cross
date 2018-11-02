/*
 * $Id:dpp_config_defs.csv,v 1.1.2.5 Broadcom SDK $
 * 
 * $Copyright: (c) 2016 Broadcom.
 * Broadcom Proprietary and Confidential. All rights reserved.$
 * This file is auto-generated by autoCoder
 * DO NOT EDIT THIS FILE!
 *
 */

#include <shared/bsl.h>
#include <soc/defs.h>
#ifdef BCM_FLAIR_SUPPORT

#include <soc/dpp/dpp_config_defs.h>
#include <soc/dpp/soc_dpp_flair_config_defs.h>

#ifdef _ERR_MSG_MODULE_NAME
    #error "_ERR_MSG_MODULE_NAME redefined"
#endif /* _ERR_MSG_MODULE_NAME */

#define _ERR_MSG_MODULE_NAME BSL_SOC_INIT

CONST soc_dpp_defines_t soc_dpp_defines_flair= {
    SOC_DPP_NOF_FLOWS_FLAIR,
    SOC_DPP_NOF_FLOWS_PER_PIPE_FLAIR,
    SOC_DPP_NOF_QUEUES_FLAIR,
    SOC_DPP_NOF_QUEUES_PER_PIPE_FLAIR,
    SOC_DPP_MAX_QUEUES_FLAIR,
    SOC_DPP_NOF_POOLS_PER_INTERDIGITATED_REGION_FLAIR,
    SOC_DPP_OCB_MEMORY_SIZE_FLAIR,
    SOC_DPP_HW_DRAM_INTERFACES_MAX_FLAIR,
    SOC_DPP_NOF_COUNTER_PROCESSORS_FLAIR,
    SOC_DPP_COUNTERS_PER_COUNTER_PROCESSOR_FLAIR,
    SOC_DPP_NOF_SMALL_COUNTER_PROCESSORS_FLAIR,
    SOC_DPP_COUNTERS_PER_SMALL_COUNTER_PROCESSOR_FLAIR,
    SOC_DPP_NOF_COUNTER_FIFOS_FLAIR,
    SOC_DPP_MAX_NOF_FIFOS_PER_COUNTER_FLAIR,
    SOC_DPP_COUNTER_FIFO_DEPTH_FLAIR,
    SOC_DPP_PDM_SIZE_FLAIR,
    SOC_DPP_NOF_INSTANCES_FSRD_FLAIR,
    SOC_DPP_NOF_QUADS_IN_FSRD_FLAIR,
    SOC_DPP_NOF_INSTANCES_FMAC_FLAIR,
    SOC_DPP_NOF_FABRIC_LINKS_FLAIR,
    SOC_DPP_FIRST_FABRIC_LINK_ID_FLAIR,
    SOC_DPP_FIRST_SFI_PHY_PORT_FLAIR,
    SOC_DPP_NOF_RCI_LEVELS_FLAIR,
    SOC_DPP_NOF_FABRIC_LINKS_IN_MAC_FLAIR,
    SOC_DPP_FABRIC_RMGR_UNITS_FLAIR,
    SOC_DPP_FABRIC_RMGR_NOF_LINKS_FLAIR,
    SOC_DPP_FABRIC_MAX_DEST_MESH_MODE_FLAIR,
    SOC_DPP_FABRIC_MAX_DEST_MESH_MC_MODE_FLAIR,
    SOC_DPP_MAX_NOF_FAP_ID_MAPPED_TO_DEST_LIMIT_FLAIR,
    SOC_DPP_FABRIC_MESH_MC_ID_MAX_VALID_FLAIR,
    SOC_DPP_FABRIC_SR_CELL_RECEIVED_NOF_SIDES_FLAIR,
    SOC_DPP_NOF_SCH_ACTIVE_LINKS_FLAIR,
    SOC_DPP_VRRP_MYMAC_CAM_SIZE_FLAIR,
    SOC_DPP_VRRP_MYMAC_MAP_SIZE_FLAIR,
    SOC_DPP_VRRP_MYMAC_MAP_WIDTH_FLAIR,
    SOC_DPP_ISEM_WIDTH_FLAIR,
    SOC_DPP_NOF_ISEM_LINES_FLAIR,
    SOC_DPP_NOF_ISEM_TABLES_FLAIR,
    SOC_DPP_ISEM_PREFIX_NOF_BITS_FLAIR,
    SOC_DPP_ISEM_PAYLOAD_NOF_BITS_FLAIR,
    SOC_DPP_ISEM_PAYLOAD_NOF_UINT32_FLAIR,
    SOC_DPP_OUT_LIF_NOF_BITS_FLAIR,
    SOC_DPP_OAM_LIF_NOF_BITS_FLAIR,
    SOC_DPP_NOF_LOCAL_LIFS_FLAIR,
    SOC_DPP_VRRP_NOF_PROTOCOL_GROUPS_FLAIR,
    SOC_DPP_NOF_GLOBAL_LIFS_FLAIR,
    SOC_DPP_NOF_OUT_LIFS_FLAIR,
    SOC_DPP_LIF_WIDTH_FLAIR,
    SOC_DPP_LEM_WIDTH_FLAIR,
    SOC_DPP_NOF_LEM_LINES_FLAIR,
    SOC_DPP_NOF_LEM_BANKS_FLAIR,
    SOC_DPP_LEM_PAYLOAD_WIDTH_FLAIR,
    SOC_DPP_NOF_LEM_PREFIXES_FLAIR,
    SOC_DPP_EEDB_WIDTH_FLAIR,
    SOC_DPP_NOF_EEDB_LINES_PER_BANK_FLAIR,
    SOC_DPP_NOF_EEDB_LINES_FLAIR,
    SOC_DPP_NOF_EEDB_PAYLOADS_FLAIR,
    SOC_DPP_FEC_NOF_BITS_FLAIR,
    SOC_DPP_NOF_FECS_FLAIR,
    SOC_DPP_NOF_FEC_BANKS_FLAIR,
    SOC_DPP_NOF_FIDS_FLAIR,
    SOC_DPP_TCAM_ACTION_WIDTH_FLAIR,
    SOC_DPP_TCAM_CASCADED_DATA_NOF_BITS_FLAIR,
    SOC_DPP_TCAM_BIG_BANK_KEY_NOF_BITS_FLAIR,
    SOC_DPP_NOF_TCAM_BIG_BANK_LINES_FLAIR,
    SOC_DPP_NOF_TCAM_BIG_BANKS_FLAIR,
    SOC_DPP_NOF_TCAM_SMALL_BANKS_FLAIR,
    SOC_DPP_NOF_TCAM_ENTRIES_160_BITS_FLAIR,
    SOC_DPP_NOF_VSI_LOWERS_FLAIR,
    SOC_DPP_IN_RIF_NOF_BITS_FLAIR,
    SOC_DPP_NOF_RIFS_FLAIR,
    SOC_DPP_MAX_NOF_RIFS_FLAIR,
    SOC_DPP_VLAN_MEMBERSHIP_WIDTH_FLAIR,
    SOC_DPP_NOF_VLAN_MEMBERSHIP_LINES_FLAIR,
    SOC_DPP_NOF_VLAN_MEMBERSHIP_TABLES_FLAIR,
    SOC_DPP_GLEM_WIDTH_FLAIR,
    SOC_DPP_NOF_GLEM_LINES_FLAIR,
    SOC_DPP_NOF_GLEM_PAYLOADS_FLAIR,
    SOC_DPP_NOF_GLEM_BANKS_FLAIR,
    SOC_DPP_ESEM_WIDTH_FLAIR,
    SOC_DPP_NOF_ESEM_LINES_FLAIR,
    SOC_DPP_NOF_ESEM_PAYLOADS_FLAIR,
    SOC_DPP_MULTICAST_GROUP_NOF_BITS_FLAIR,
    SOC_DPP_NOF_MULTICAST_GROUPS_FLAIR,
    SOC_DPP_NOF_VIRTUAL_PORT_LINES_FLAIR,
    SOC_DPP_VIRTUAL_PORT_NOF_BITS_FLAIR,
    SOC_DPP_VRF_NOF_BITS_FLAIR,
    SOC_DPP_NOF_VRFS_FLAIR,
    SOC_DPP_TOPOLOGY_ID_NOF_BITS_FLAIR,
    SOC_DPP_NOF_TOPOLOGY_IDS_FLAIR,
    SOC_DPP_VLAN_DOMAIN_NOF_BITS_FLAIR,
    SOC_DPP_NOF_VLAN_DOMAINS_FLAIR,
    SOC_DPP_ELK_LOOKUP_PAYLOAD_NOF_BITS_FLAIR,
    SOC_DPP_OAM_2_ID_NOF_BITS_FLAIR,
    SOC_DPP_OAM_COUNTER_INDEX_NOF_BITS_FLAIR,
    SOC_DPP_NOF_OAM_COUNTER_INDEXES_FLAIR,
    SOC_DPP_COUNTER_NOF_BITS_FLAIR,
    SOC_DPP_NOF_COUNTERS_FLAIR,
    SOC_DPP_NOF_FEM_4_FLAIR,
    SOC_DPP_NOF_FEM_16_FLAIR,
    SOC_DPP_NOF_FEM_19_FLAIR,
    SOC_DPP_NOF_FEM_24_FLAIR,
    SOC_DPP_FEM_MAX_ACTION_SIZE_NOF_BITS_FLAIR,
    SOC_DPP_NOF_ECMP_FLAIR,
    SOC_DPP_ECMP_MAX_SIZE_FLAIR,
    SOC_DPP_VLAN_TRANSLATION_PROFILE_NOF_BITS_FLAIR,
    SOC_DPP_NOF_VTT_PROGRAM_SELECTION_LINES_FLAIR,
    SOC_DPP_NOF_VTT_PROGRAMS_FLAIR,
    SOC_DPP_IN_PP_PORT_TERMINATION_PROFILE_NOF_BITS_FLAIR,
    SOC_DPP_NOF_CORES_FLAIR,
    SOC_DPP_MAX_MACT_LIMIT_FLAIR,
    SOC_DPP_LEM_IS_DYNAMIC_LSB_FLAIR,
    SOC_DPP_LEM_3B_PAYLOAD_FORMAT_EEI_NOF_BITS_FLAIR,
    SOC_DPP_LEM_3B_PAYLOAD_FORMAT_NATIVE_VSI_NOF_BITS_FLAIR,
    SOC_DPP_NOF_LOGICAL_PORTS_FLAIR,
    SOC_DPP_NOF_LOCAL_PORTS_FLAIR,
    SOC_DPP_NOF_PRGE_PROGRAMS_FLAIR,
    SOC_DPP_NOF_PRGE_INSTR_ENTRIES_FLAIR,
    SOC_DPP_NOF_EGRESS_PMF_ACTIONS_FLAIR,
    SOC_DPP_NOF_EG_ENCAP_LSBS_FLAIR,
    SOC_DPP_NOF_EG_ENCAP_RSVS_FLAIR,
    SOC_DPP_EG_ENCAP_ACCESS_PREFIX_MSB_FLAIR,
    SOC_DPP_EG_ENCAP_ACCESS_PREFIX_LSB_FLAIR,
    SOC_DPP_EG_ENCAP_NOF_BANKS_FLAIR,
    SOC_DPP_EG_ENCAP_NOF_TOP_BANKS_FLAIR,
    SOC_DPP_EG_ENCAP_NOF_PHASES_FLAIR,
    SOC_DPP_EG_ENCAP_PHASE_NOF_BITS_FLAIR,
    SOC_DPP_NOF_FAILOVER_FEC_IDS_FLAIR,
    SOC_DPP_NOF_FAILOVER_INGRESS_IDS_FLAIR,
    SOC_DPP_FAILOVER_INGRESS_LAST_HW_ID_FLAIR,
    SOC_DPP_NOF_FAILOVER_EGRESS_IDS_FLAIR,
    SOC_DPP_CORE_CLOCK_FREQ_KHZ_FLAIR,
    SOC_DPP_GLOB_CLOCK_FREQ_MHZ_FLAIR,
    SOC_DPP_JUMBO_MAX_SIZE_FLAIR,
    SOC_DPP_COSQ_EGR_DEFAULT_THRESH_TYPE_FLAIR,
    SOC_DPP_MODID_MAX_VALID_FLAIR,
    SOC_DPP_NOF_FLP_PROGRAM_SELECTION_LINES_FLAIR,
    SOC_DPP_IHB_FLP_PROGRAM_SELECTION_CAM_MASK_NOF_BITS_FLAIR,
    SOC_DPP_NOF_FLP_PROGRAMS_FLAIR,
    SOC_DPP_NOF_FLP_KEYS_FLAIR,
    SOC_DPP_NOF_FLP_16B_INSTRUCTIONS_FLAIR,
    SOC_DPP_NOF_FLP_32B_INSTRUCTIONS_FLAIR,
    SOC_DPP_NOF_FLP_INSTRUCTIONS_LSB_FLAIR,
    SOC_DPP_NOF_FLP_CYCLES_FLAIR,
    SOC_DPP_NOF_FLP_80B_ZONES_FLAIR,
    SOC_DPP_NOF_FLP_KEY_ZONES_FLAIR,
    SOC_DPP_NOF_FLP_KEY_ZONE_BITS_FLAIR,
    SOC_DPP_NOF_INGRESS_PMF_PROGRAM_SELECTION_LINES_FLAIR,
    SOC_DPP_IHB_PMF_PROGRAM_SELECTION_CAM_MASK_NOF_BITS_FLAIR,
    SOC_DPP_NOF_INGRESS_PMF_PROGRAMS_FLAIR,
    SOC_DPP_NOF_INGRESS_PMF_KEYS_FLAIR,
    SOC_DPP_NOF_INGRESS_PMF_INSTRUCTIONS_LSB_FLAIR,
    SOC_DPP_NOF_INGRESS_PMF_CYCLES_FLAIR,
    SOC_DPP_NOF_INGRESS_PMF_80B_ZONES_FLAIR,
    SOC_DPP_NOF_INGRESS_PMF_KEY_ZONES_FLAIR,
    SOC_DPP_NOF_INGRESS_PMF_KEY_ZONE_BITS_FLAIR,
    SOC_DPP_NOF_EGRESS_PMF_PROGRAM_SELECTION_LINES_FLAIR,
    SOC_DPP_EGQ_PMF_PROGRAM_SELECTION_CAM_MASK_NOF_BITS_FLAIR,
    SOC_DPP_NOF_EGRESS_PMF_PROGRAMS_FLAIR,
    SOC_DPP_NOF_EGRESS_PMF_KEYS_FLAIR,
    SOC_DPP_NOF_EGRESS_PMF_CYCLES_FLAIR,
    SOC_DPP_NOF_EGRESS_PMF_INSTRUCTIONS_LSB_FLAIR,
    SOC_DPP_NOF_EGRESS_PMF_80B_ZONES_FLAIR,
    SOC_DPP_NOF_EGRESS_PMF_KEY_ZONES_FLAIR,
    SOC_DPP_NOF_EGRESS_PMF_KEY_ZONE_BITS_FLAIR,
    SOC_DPP_NOF_SLB_PROGRAM_SELECTION_LINES_FLAIR,
    SOC_DPP_IHP_CONSISTENT_HASHING_PROGRAM_SEL_TCAM_MASK_NOF_BITS_FLAIR,
    SOC_DPP_NOF_SLB_PROGRAMS_FLAIR,
    SOC_DPP_NOF_SLB_KEYS_FLAIR,
    SOC_DPP_NOF_SLB_INSTRUCTIONS_LSB_FLAIR,
    SOC_DPP_NOF_SLB_CYCLES_FLAIR,
    SOC_DPP_NOF_SLB_80B_ZONES_FLAIR,
    SOC_DPP_NOF_SLB_KEY_ZONES_FLAIR,
    SOC_DPP_NOF_SLB_KEY_ZONE_BITS_FLAIR,
    SOC_DPP_OAMP_NUMBER_OF_ETH_Y1731_MEP_PROFILES_FLAIR,
    SOC_DPP_OAMP_NUMBER_MEP_DB_ENTRIES_FLAIR,
    SOC_DPP_OAMP_NUMBER_OF_MEPS_FLAIR,
    SOC_DPP_OAMP_NUMBER_OF_RMEPS_FLAIR,
    SOC_DPP_OAMP_NUMBER_OF_PUNT_PROFILES_FLAIR,
    SOC_DPP_OAMP_NUMBER_OF_SD_SF_DB_FLAIR,
    SOC_DPP_OAMP_NUMBER_OF_SD_SF_Y_1711_DB_FLAIR,
    SOC_DPP_OAMP_NUMBER_OF_SD_SF_PROFILES_FLAIR,
    SOC_DPP_NUM_OF_REASSEMBLY_CONTEXT_FLAIR,
    SOC_DPP_OAMP_UMC_TABLE_SIZE_FLAIR,
    SOC_DPP_EGR_PRGE_NOF_LFEMS_FLAIR,
    SOC_DPP_EGR_PRGE_NOF_PROGRAM_INSTRUCTIONS_FLAIR,
    SOC_DPP_EGR_PRGE_NOF_INSTRUCTION_MEMS_FLAIR,
    SOC_DPP_EGR_PRGE_NOF_LFEM_TABLES_FLAIR,
    SOC_DPP_LEM_ENTRY_TYPE_IS_FEC_EEI_LSB_FLAIR,
    SOC_DPP_LEM_SA_DROP_LSB_FLAIR,
    SOC_DPP_NOF_ECMPS_FLAIR,
    SOC_DPP_INLIF_BANK_MSBS_MASK_FLAIR,
    SOC_DPP_INLIF_BANK_MSBS_MASK_START_FLAIR,
    SOC_DPP_INLIF_BANK_LSBS_MASK_FLAIR,
    SOC_DPP_INLIF_BANK_LSBS_MASK_END_FLAIR,
    SOC_DPP_NOF_INTERLAKEN_PORTS_FLAIR,
    SOC_DPP_NOF_CAUI_PORTS_FLAIR,
    SOC_DPP_NOF_FC_PFC_GENERIC_BITMAPS_FLAIR,
    SOC_DPP_NOF_ROO_LL_FORMAT_ETH_TYPE_INDEXS_FLAIR,
    SOC_DPP_OAMP_LOCAL_PORT_2_SYS_PORT_SIZE_FLAIR,
    SOC_DPP_OAMP_PE_PROG_TCAM_SIZE_FLAIR,
    SOC_DPP_OAMP_PE_PROG_TCAM_NOF_BITS_FLAIR,
    SOC_DPP_OAMP_PE_PROG_TCAM_PACKET_TYPE_OFFSET_FLAIR,
    SOC_DPP_OAMP_PE_PROG_TCAM_PACKET_TYPE_NOF_BITS_FLAIR,
    SOC_DPP_OAMP_PE_PROG_TCAM_MEP_TYPE_OFFSET_FLAIR,
    SOC_DPP_OAMP_PE_PROG_TCAM_MEP_TYPE_NOF_BITS_FLAIR,
    SOC_DPP_OAMP_PE_PROG_TCAM_MEP_PROFILE_OFFSET_FLAIR,
    SOC_DPP_OAMP_PE_PROG_TCAM_MEP_PROFILE_NOF_BITS_FLAIR,
    SOC_DPP_OAMP_PE_PROG_TCAM_MEP_PE_PROFILE_OFFSET_FLAIR,
    SOC_DPP_OAMP_PE_PROG_TCAM_MEP_PE_PROFILE_NOF_BITS_FLAIR,
    SOC_DPP_OAMP_PE_PROG_TCAM_MSG_TYPE_OFFSET_FLAIR,
    SOC_DPP_OAMP_PE_PROG_TCAM_MSG_TYPE_NOF_BITS_FLAIR,
    SOC_DPP_INLIF_P2P_OUT_LIF_VALID_BIT_FLAIR,
    SOC_DPP_REPEATER_NONE_EMPTY_CELL_SIZE_FLAIR,
    SOC_DPP_REPEATER_DEFAULT_EMPTY_CELL_SIZE_FLAIR,
    SOC_DPP_FABRIC_VSC256_MAX_CELL_SIZE_FLAIR,
    SOC_DPP_NOF_CHANNELIZED_CALENDARS_FLAIR,
    SOC_DPP_NOF_BIG_CHANNELIZED_CALENDARS_FLAIR,
    SOC_DPP_NOF_SMALL_CHANNELIZED_CALENDARS_FLAIR,
    SOC_DPP_FABRIC_COMMA_BURST_PERIOD_FLAIR,
    SOC_DPP_SMALL_CHANNELIZED_CAL_SIZE_FLAIR,
    SOC_DPP_BIG_CHANNELIZED_CAL_SIZE_FLAIR,
    SOC_DPP_NOF_EVE_PROFILE_BITS_FLAIR,
    SOC_DPP_CAL_INTERNAL_RATE_MAX_FLAIR,
    SOC_DPP_NON_CHANNELIZED_CAL_ID_FLAIR,
    SOC_DPP_FABRIC_MAC_BUS_SIZE_FLAIR,
    SOC_DPP_OAMP_PE_PROG_SEL_PROFILE_NOF_FLAIR,
    SOC_DPP_NOF_CREDIT_REQUEST_PROFILES_FLAIR,
    SOC_DPP_NOF_LINKS_IN_FSRD_FLAIR,
    SOC_DPP_NOF_VT_PROGRAM_SELECTION_LINES_FLAIR,
    SOC_DPP_IHP_VTT_1ST_PROGRAM_SELECTION_TCAM_MASK_NOF_BITS_FLAIR,
    SOC_DPP_NOF_VT_PROGRAMS_FLAIR,
    SOC_DPP_NOF_VT_KEYS_FLAIR,
    SOC_DPP_NOF_VT_16B_INSTRUCTIONS_FLAIR,
    SOC_DPP_NOF_VT_32B_INSTRUCTIONS_FLAIR,
    SOC_DPP_NOF_VT_INSTRUCTIONS_LSB_FLAIR,
    SOC_DPP_NOF_VT_CYCLES_FLAIR,
    SOC_DPP_NOF_VT_80B_ZONES_FLAIR,
    SOC_DPP_NOF_VT_KEY_ZONES_FLAIR,
    SOC_DPP_NOF_VT_KEY_ZONE_BITS_FLAIR,
    SOC_DPP_VT_CE_BUFFER_LENGTH_FLAIR,
    SOC_DPP_NOF_TT_PROGRAM_SELECTION_LINES_FLAIR,
    SOC_DPP_IHP_VTT_2ND_PROGRAM_SELECTION_TCAM_MASK_NOF_BITS_FLAIR,
    SOC_DPP_NOF_TT_PROGRAMS_FLAIR,
    SOC_DPP_NOF_TT_KEYS_FLAIR,
    SOC_DPP_NOF_TT_16B_INSTRUCTIONS_FLAIR,
    SOC_DPP_NOF_TT_32B_INSTRUCTIONS_FLAIR,
    SOC_DPP_NOF_TT_INSTRUCTIONS_LSB_FLAIR,
    SOC_DPP_NOF_TT_CYCLES_FLAIR,
    SOC_DPP_NOF_TT_80B_ZONES_FLAIR,
    SOC_DPP_NOF_TT_KEY_ZONES_FLAIR,
    SOC_DPP_NOF_TT_KEY_ZONE_BITS_FLAIR,
    SOC_DPP_TT_CE_BUFFER_LENGTH_FLAIR,
    SOC_DPP_MAX_GBPS_RATE_EGQ_FLAIR,
    SOC_DPP_MAX_GBPS_RATE_SCH_FLAIR,
    SOC_DPP_SIZE_OF_OAM_KEY_FLAIR,
    SOC_DPP_FC_INB_CAL_LEN_MAX_FLAIR,
    SOC_DPP_ITM_GLOB_RCS_FC_BDBS_SIZE_MAX_FLAIR,
    SOC_DPP_ITM_GLOB_RCS_FC_UC_SIZE_MAX_FLAIR,
    SOC_DPP_ITM_GLOB_RCS_FC_FMC_SIZE_MAX_FLAIR,
    SOC_DPP_ITM_GLOB_RCS_FC_HEADROOM_PD_SIZE_MAX_FLAIR,
    SOC_DPP_ITM_GLOB_RCS_FC_HEADROOM_SIZE_MAX_FLAIR,
    SOC_DPP_ITM_GLOB_RCS_FC_MNMC_SIZE_MAX_FLAIR,
    SOC_DPP_ITM_GLOB_RCS_FC_OCB_SIZE_MAX_FLAIR,
    SOC_DPP_ITM_GLOB_RCS_FC_P0_BYTE_SIZE_MAX_FLAIR,
    SOC_DPP_ITM_GLOB_RCS_FC_P0_PD_SIZE_MAX_FLAIR,
    SOC_DPP_ITM_GLOB_RCS_FC_P0_SIZE_MAX_FLAIR,
    SOC_DPP_ITM_GLOB_RCS_FC_P1_BYTE_SIZE_MAX_FLAIR,
    SOC_DPP_ITM_GLOB_RCS_FC_P1_PD_SIZE_MAX_FLAIR,
    SOC_DPP_ITM_GLOB_RCS_FC_P1_SIZE_MAX_FLAIR,
    SOC_DPP_ITM_GLOB_RCS_FC_OCB_P0_SIZE_MAX_FLAIR,
    SOC_DPP_ITM_GLOB_RCS_FC_OCB_P1_SIZE_MAX_FLAIR,
    SOC_DPP_ITM_GLOB_RCS_FC_OCB_PDB_SIZE_MAX_FLAIR,
    SOC_DPP_ITM_GLOB_RCS_FC_MIX_P0_SIZE_MAX_FLAIR,
    SOC_DPP_ITM_GLOB_RCS_FC_MIX_P1_SIZE_MAX_FLAIR,
    SOC_DPP_MAX_OOB_WD_PERIOD_FLAIR,
    SOC_DPP_IP_TUNNEL_LIF_LEARN_DATA_NOF_BITS_FLAIR,
    SOC_DPP_AC_MP_LIF_LEARN_DATA_NOF_BITS_FLAIR,
    SOC_DPP_IP_TUNNEL_LIF_UC_FLOW_LEARN_DATA_STATIC_LSBS_FLAIR,
    SOC_DPP_AC_MP_LIF_UC_FLOW_LEARN_DATA_STATIC_LSBS_FLAIR,
    SOC_DPP_ENCODE_DEST_PREFIX_NOF_BITS_19_FEC_PTR_FLAIR,
    SOC_DPP_ENCODE_DEST_PREFIX_VALUE_19_FEC_PTR_FLAIR,
    SOC_DPP_ENCODE_DEST_PREFIX_NOF_BITS_19_MC_ID_FLAIR,
    SOC_DPP_ENCODE_DEST_PREFIX_VALUE_19_MC_ID_FLAIR,
    SOC_DPP_ENCODE_DEST_PREFIX_VALUE_19_SYS_PORT_FLAIR,
    SOC_DPP_MAC_COUNTER_FIRST_FLAIR,
    SOC_DPP_FID_NOF_BITS_FLAIR,
    SOC_DPP_SCM_QP_TCG_CR_TO_ADD_NOF_BITS_FLAIR,
    SOC_DPP_NOF_EPNI_ISID_FLAIR,
    SOC_DPP_SOURCE_ROUTED_CELLS_HEADER_OFFSET_FLAIR,
    SOC_DPP_EGQ_QDCT_PD_MAX_VAL_FLAIR,
    SOC_DPP_EGR_PRGE_NOF_PROG_SEL_TCAM_ENTRIES_FLAIR,
    SOC_DPP_NOF_RIF_PROFILES_FLAIR,
    SOC_DPP_FLOW_REGION_FIXED_TYPE0_END_FLAIR,
    SOC_DPP_NOF_PM4X25_FLAIR,
    SOC_DPP_NOF_PM4X2P5_FLAIR,
    SOC_DPP_NOF_PM4X10_FLAIR,
    SOC_DPP_NOF_PM4X10Q_FLAIR,
    SOC_DPP_PMH_BASE_LANE_FLAIR,
    SOC_DPP_PML0_BASE_LANE_FLAIR,
    SOC_DPP_PML1_BASE_LANE_FLAIR,
    SOC_DPP_PMX_BASE_LANE_FLAIR,
    SOC_DPP_PML_BASE_LANE_FLAIR,
    SOC_DPP_NOF_PMS_PER_NBI_FLAIR,
    SOC_DPP_NOF_PMS_FLAIR,
    SOC_DPP_NOF_INSTANCES_NBIL_FLAIR,
    SOC_DPP_NOF_LANES_PER_NBI_FLAIR,
    SOC_DPP_NOF_PORTS_NBIH_FLAIR,
    SOC_DPP_NOF_PORTS_NBIL_FLAIR,
    SOC_DPP_PLL_TYPE_PMH_LAST_PHY_LANE_FLAIR,
    SOC_DPP_PLL_TYPE_PML0_LAST_PHY_LANE_FLAIR,
    SOC_DPP_PLL_TYPE_PML1_LAST_PHY_LANE_FLAIR,
    SOC_DPP_PLL_TYPE_PMX_LAST_PHY_LANE_FLAIR,
    SOC_DPP_PLL_TYPE_PML_LAST_PHY_LANE_FLAIR,
    SOC_DPP_XAUI_IF_BASE_LANE_FLAIR,
    SOC_DPP_RXAUI_IF_BASE_LANE_FLAIR,
    SOC_DPP_NOF_OUT_VSI_FLAIR,
    SOC_DPP_SIZE_OF_PDM_EXTENSION_FLAIR,
    SOC_DPP_OAMP_PE_LFEM_NOF_FLAIR,
    SOC_DPP_SYS_HDRS_FORMAT_CODE_BITS_FLAIR,
    SOC_DPP_VALUE_1_OFFSET_BITS_FLAIR,
    SOC_DPP_VALUE_2_OFFSET_BITS_FLAIR,
    SOC_DPP_SYS_HDRS_FORMAT_CODE_PROFILES_FLAIR,
    SOC_DPP_VXLAN_TUNNEL_TERM_IN_SEM_MY_VTEP_INDEX_NOF_BITS_FLAIR,
    SOC_DPP_NOF_PP_PORTS_PER_CORE_FLAIR,
    SOC_DPP_LLVP_PROFILES_COUNT_FLAIR,
    SOC_DPP_METER_POINTER_NOF_BITS_FLAIR,
    SOC_DPP_NOF_INLIF_BANKS_FLAIR,
    SOC_DPP_NOF_LOCAL_LIFS_PER_BANK_FLAIR,
    SOC_DPP_MAX_VSQ_RT_CLS_FLAIR,
    SOC_DPP_MAX_VSQ_A_RT_CLS_FLAIR,
    SOC_DPP_NOF_VSQ_A_FLAIR,
    SOC_DPP_NOF_VSQ_B_FLAIR,
    SOC_DPP_NOF_VSQ_C_FLAIR,
    SOC_DPP_NOF_VSQ_D_FLAIR,
    SOC_DPP_NOF_VSQ_E_FLAIR,
    SOC_DPP_NOF_VSQ_F_FLAIR,
    SOC_DPP_MIN_INTERDIGIT_FLOW_QUARTET_FLAIR,
    SOC_DPP_VSQ_OCB_ONLY_SUPPORT_FLAIR,
    SOC_DPP_FIELD_LARGE_DIRECT_LU_KEY_LENGTH_FLAIR,
    SOC_DPP_MAX_OAMP_MEP_DB_ENTRY_ID_BITS_FLAIR,
    SOC_DPP_FEM_KEY_SELECT_NOP_FLAIR,
    SOC_DPP_GRANULARITY_MODEM_BIT_SHAPER_RATE_FLAIR,
};

/* defines struct init func for flair */
int soc_dpp_flair_defines_init(int unit)
{
    SOCDNX_INIT_FUNC_DEFS;

    if ( soc_dpp_defines[unit] == NULL ) {
        soc_dpp_defines[unit] = (soc_dpp_defines_t *) sal_alloc(sizeof(soc_dpp_defines_t),"Defines struct");
        if ( soc_dpp_defines[unit] == NULL ) {
            SOCDNX_EXIT_WITH_ERR(SOC_E_MEMORY, (_BSL_SOCDNX_MSG("Failed to allocate memory for configuration defines struct")));
        }
    }
        sal_memcpy(soc_dpp_defines[unit], &soc_dpp_defines_flair, sizeof(soc_dpp_defines_t));

exit:
    SOCDNX_FUNC_RETURN;
}

/* defines struct deinit func for flair */
int soc_dpp_flair_defines_deinit(int unit)
{
    if ( soc_dpp_defines[unit] != NULL ) {
        sal_free(soc_dpp_defines[unit]);
        soc_dpp_defines[unit] = NULL;
    }

    return SOC_E_NONE;
}

/**************************************/
/*  Operation mode specific logic    */
/**************************************/

#endif /* BCM_FLAIR_SUPPORT */
