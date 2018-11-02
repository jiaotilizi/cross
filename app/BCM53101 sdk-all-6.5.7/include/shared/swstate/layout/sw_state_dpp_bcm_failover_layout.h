/* $Id: $
 * 
 * $Copyright: (c) 2016 Broadcom.
 * Broadcom Proprietary and Confidential. All rights reserved.$
 * 
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated.
 * Edits to this file will be lost when it is regenerated.
*/
#ifndef _SHR_sw_state_dpp_bcm_failover_H_
#define _SHR_sw_state_dpp_bcm_failover_H_


#define SW_STATE_DPP_BCM_FAILOVER_ID_SEQUENCE_LAYOUT_NOF_MAX_LAYOUT_NODES (1) 
#define SW_STATE_DPP_BCM_FAILOVER_LAYOUT_NOF_MAX_LAYOUT_NODES (1 + SW_STATE_DPP_BCM_FAILOVER_ID_SEQUENCE_LAYOUT_NOF_MAX_LAYOUT_NODES) 

#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
int sw_state_dpp_bcm_failover_layout_node_create(int unit, int* root_node_id, uint32* next_free_node_id);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
int sw_state_dpp_bcm_failover_id_sequence_layout_node_create(int unit, int* root_node_id, uint32* next_free_node_id);
#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 

#endif /* _SHR_sw_state_dpp_bcm_failover_H_ */
