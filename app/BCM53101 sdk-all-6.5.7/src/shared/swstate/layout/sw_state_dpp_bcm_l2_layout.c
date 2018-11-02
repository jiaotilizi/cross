/* $Id: $
 * 
 * $Copyright: (c) 2016 Broadcom.
 * Broadcom Proprietary and Confidential. All rights reserved.$
 * 
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated.
 * Edits to this file will be lost when it is regenerated.
*/
#include <sal/core/libc.h>
#include <shared/swstate/sw_state.h>
#include <shared/error.h>
#include <shared/swstate/sw_state_defs.h>
#include <shared/swstate/sw_state_utils.h>
#include <shared/bsl.h>
#include <shared/swstate/layout/sw_state_layout.h>
#include <shared/swstate/layout/sw_state_dpp_bcm_l2_layout.h>

#ifdef _ERR_MSG_MODULE_NAME  
  #error "_ERR_MSG_MODULE_NAME redefined"  
#endif  
#define _ERR_MSG_MODULE_NAME BSL_LS_SHARED_SWSTATE 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
int sw_state_dpp_bcm_l2_layout_node_create(int unit, int* root_node_id, uint32* next_free_node_id){  

   int younger_brother_node_id = 0; 
   int offset = 0; 
   l2_data_t* dummy_struct; 
   SOC_INIT_FUNC_DEFS;
   /* alloc dummy struct */ 
   dummy_struct = sal_alloc(sizeof(l2_data_t),"l2_data_t"); 

   /* update current root node */  
   *root_node_id = *next_free_node_id; 
   /* add node */    
   _SOC_IF_ERR_EXIT(shr_sw_state_ds_layout_node_set(unit, 
                                   *root_node_id,                 /* node id var */      
                                   "l2",             /* name */         
                                   sizeof(l2_data_t),    /* size of the element's type*/          
                                   1,                 /* nof pointers */ 
                                   "l2_data_t",              /* param type */
                                   0,                 /* array size 0 */ 
                                   0));             /* array size 1 */ 
   /* update next free node id */ 
    SW_STATE_NODE_ID_CHECK(unit, ++(*next_free_node_id));  

   /* add node */ 
   _SOC_IF_ERR_EXIT(sw_state_dpp_bcm_l2_mymac_msb_is_set_layout_node_create(unit, &younger_brother_node_id, next_free_node_id));
   /* connect node (1st child) to its parent */ 
   _SOC_IF_ERR_EXIT(shr_sw_state_ds_layout_add_child(unit, *root_node_id, younger_brother_node_id)); 
   /* update offset */ 
   offset = ((uint8*) &(dummy_struct->mymac_msb_is_set)) - (( uint8*) dummy_struct); 
   _SOC_IF_ERR_EXIT(shr_sw_state_ds_layout_update_offset(unit, younger_brother_node_id, offset)); 

   /* add node */ 
   _SOC_IF_ERR_EXIT(sw_state_dpp_bcm_l2_l2_initialized_layout_node_create(unit, &younger_brother_node_id, next_free_node_id));
   /* connect node (1st child) to its parent */ 
   _SOC_IF_ERR_EXIT(shr_sw_state_ds_layout_add_child(unit, *root_node_id, younger_brother_node_id)); 
   /* update offset */ 
   offset = ((uint8*) &(dummy_struct->l2_initialized)) - (( uint8*) dummy_struct); 
   _SOC_IF_ERR_EXIT(shr_sw_state_ds_layout_update_offset(unit, younger_brother_node_id, offset)); 

   /* add node */ 
   _SOC_IF_ERR_EXIT(sw_state_dpp_bcm_l2_bcm_petra_l2_freeze_state_layout_node_create(unit, &younger_brother_node_id, next_free_node_id));
   /* connect node (1st child) to its parent */ 
   _SOC_IF_ERR_EXIT(shr_sw_state_ds_layout_add_child(unit, *root_node_id, younger_brother_node_id)); 
   /* update offset */ 
   offset = ((uint8*) &(dummy_struct->bcm_petra_l2_freeze_state)) - (( uint8*) dummy_struct); 
   _SOC_IF_ERR_EXIT(shr_sw_state_ds_layout_update_offset(unit, younger_brother_node_id, offset)); 

   /* add node */ 
   _SOC_IF_ERR_EXIT(sw_state_dpp_bcm_l2_mpls_extended_label_ether_type_index_table_is_set_layout_node_create(unit, &younger_brother_node_id, next_free_node_id));
   /* connect node (1st child) to its parent */ 
   _SOC_IF_ERR_EXIT(shr_sw_state_ds_layout_add_child(unit, *root_node_id, younger_brother_node_id)); 
   /* update offset */ 
   offset = ((uint8*) &(dummy_struct->mpls_extended_label_ether_type_index_table_is_set)) - (( uint8*) dummy_struct); 
   _SOC_IF_ERR_EXIT(shr_sw_state_ds_layout_update_offset(unit, younger_brother_node_id, offset)); 

   SOC_EXIT;
 exit:
   /* free dummy struct */ 
   sal_free(dummy_struct); 
   SOC_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
int sw_state_dpp_bcm_l2_mymac_msb_is_set_layout_node_create(int unit, int* root_node_id, uint32* next_free_node_id){  

   SOC_INIT_FUNC_DEFS;

   /* update current root node */  
   *root_node_id = *next_free_node_id; 
   /* add node */    
   _SOC_IF_ERR_EXIT(shr_sw_state_ds_layout_node_set(unit, 
                                   *root_node_id,                 /* node id var */      
                                   "mymac_msb_is_set",             /* name */         
                                   sizeof(uint8),    /* size of the element's type*/          
                                   0,                 /* nof pointers */ 
                                   "uint8",              /* param type */
                                   0,                 /* array size 0 */ 
                                   0));             /* array size 1 */ 
   /* update next free node id */ 
    SW_STATE_NODE_ID_CHECK(unit, ++(*next_free_node_id));  

   SOC_EXIT;
 exit:
   SOC_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
int sw_state_dpp_bcm_l2_l2_initialized_layout_node_create(int unit, int* root_node_id, uint32* next_free_node_id){  

   SOC_INIT_FUNC_DEFS;

   /* update current root node */  
   *root_node_id = *next_free_node_id; 
   /* add node */    
   _SOC_IF_ERR_EXIT(shr_sw_state_ds_layout_node_set(unit, 
                                   *root_node_id,                 /* node id var */      
                                   "l2_initialized",             /* name */         
                                   sizeof(int),    /* size of the element's type*/          
                                   0,                 /* nof pointers */ 
                                   "int",              /* param type */
                                   0,                 /* array size 0 */ 
                                   0));             /* array size 1 */ 
   /* update next free node id */ 
    SW_STATE_NODE_ID_CHECK(unit, ++(*next_free_node_id));  

   SOC_EXIT;
 exit:
   SOC_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
int sw_state_dpp_bcm_l2_bcm_petra_l2_freeze_state_layout_node_create(int unit, int* root_node_id, uint32* next_free_node_id){  

   int younger_brother_node_id = 0; 
   int offset = 0; 
   _bcm_petra_l2_freeze_t* dummy_struct; 
   SOC_INIT_FUNC_DEFS;
   /* alloc dummy struct */ 
   dummy_struct = sal_alloc(sizeof(_bcm_petra_l2_freeze_t),"_bcm_petra_l2_freeze_t"); 

   /* update current root node */  
   *root_node_id = *next_free_node_id; 
   /* add node */    
   _SOC_IF_ERR_EXIT(shr_sw_state_ds_layout_node_set(unit, 
                                   *root_node_id,                 /* node id var */      
                                   "bcm_petra_l2_freeze_state",             /* name */         
                                   sizeof(_bcm_petra_l2_freeze_t),    /* size of the element's type*/          
                                   0,                 /* nof pointers */ 
                                   "_bcm_petra_l2_freeze_t",              /* param type */
                                   0,                 /* array size 0 */ 
                                   0));             /* array size 1 */ 
   /* update next free node id */ 
    SW_STATE_NODE_ID_CHECK(unit, ++(*next_free_node_id));  

   /* add node */ 
   _SOC_IF_ERR_EXIT(sw_state_dpp_bcm_l2_bcm_petra_l2_freeze_state_frozen_layout_node_create(unit, &younger_brother_node_id, next_free_node_id));
   /* connect node (1st child) to its parent */ 
   _SOC_IF_ERR_EXIT(shr_sw_state_ds_layout_add_child(unit, *root_node_id, younger_brother_node_id)); 
   /* update offset */ 
   offset = ((uint8*) &(dummy_struct->frozen)) - (( uint8*) dummy_struct); 
   _SOC_IF_ERR_EXIT(shr_sw_state_ds_layout_update_offset(unit, younger_brother_node_id, offset)); 

   /* add node */ 
   _SOC_IF_ERR_EXIT(sw_state_dpp_bcm_l2_bcm_petra_l2_freeze_state_save_age_ena_layout_node_create(unit, &younger_brother_node_id, next_free_node_id));
   /* connect node (1st child) to its parent */ 
   _SOC_IF_ERR_EXIT(shr_sw_state_ds_layout_add_child(unit, *root_node_id, younger_brother_node_id)); 
   /* update offset */ 
   offset = ((uint8*) &(dummy_struct->save_age_ena)) - (( uint8*) dummy_struct); 
   _SOC_IF_ERR_EXIT(shr_sw_state_ds_layout_update_offset(unit, younger_brother_node_id, offset)); 

   /* add node */ 
   _SOC_IF_ERR_EXIT(sw_state_dpp_bcm_l2_bcm_petra_l2_freeze_state_save_learn_ena_layout_node_create(unit, &younger_brother_node_id, next_free_node_id));
   /* connect node (1st child) to its parent */ 
   _SOC_IF_ERR_EXIT(shr_sw_state_ds_layout_add_child(unit, *root_node_id, younger_brother_node_id)); 
   /* update offset */ 
   offset = ((uint8*) &(dummy_struct->save_learn_ena)) - (( uint8*) dummy_struct); 
   _SOC_IF_ERR_EXIT(shr_sw_state_ds_layout_update_offset(unit, younger_brother_node_id, offset)); 

   SOC_EXIT;
 exit:
   /* free dummy struct */ 
   sal_free(dummy_struct); 
   SOC_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
int sw_state_dpp_bcm_l2_bcm_petra_l2_freeze_state_frozen_layout_node_create(int unit, int* root_node_id, uint32* next_free_node_id){  

   SOC_INIT_FUNC_DEFS;

   /* update current root node */  
   *root_node_id = *next_free_node_id; 
   /* add node */    
   _SOC_IF_ERR_EXIT(shr_sw_state_ds_layout_node_set(unit, 
                                   *root_node_id,                 /* node id var */      
                                   "frozen",             /* name */         
                                   sizeof(int),    /* size of the element's type*/          
                                   0,                 /* nof pointers */ 
                                   "int",              /* param type */
                                   0,                 /* array size 0 */ 
                                   0));             /* array size 1 */ 
   /* update next free node id */ 
    SW_STATE_NODE_ID_CHECK(unit, ++(*next_free_node_id));  

   SOC_EXIT;
 exit:
   SOC_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
int sw_state_dpp_bcm_l2_bcm_petra_l2_freeze_state_save_age_ena_layout_node_create(int unit, int* root_node_id, uint32* next_free_node_id){  

   SOC_INIT_FUNC_DEFS;

   /* update current root node */  
   *root_node_id = *next_free_node_id; 
   /* add node */    
   _SOC_IF_ERR_EXIT(shr_sw_state_ds_layout_node_set(unit, 
                                   *root_node_id,                 /* node id var */      
                                   "save_age_ena",             /* name */         
                                   sizeof(int),    /* size of the element's type*/          
                                   0,                 /* nof pointers */ 
                                   "int",              /* param type */
                                   0,                 /* array size 0 */ 
                                   0));             /* array size 1 */ 
   /* update next free node id */ 
    SW_STATE_NODE_ID_CHECK(unit, ++(*next_free_node_id));  

   SOC_EXIT;
 exit:
   SOC_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
int sw_state_dpp_bcm_l2_bcm_petra_l2_freeze_state_save_learn_ena_layout_node_create(int unit, int* root_node_id, uint32* next_free_node_id){  

   SOC_INIT_FUNC_DEFS;

   /* update current root node */  
   *root_node_id = *next_free_node_id; 
   /* add node */    
   _SOC_IF_ERR_EXIT(shr_sw_state_ds_layout_node_set(unit, 
                                   *root_node_id,                 /* node id var */      
                                   "save_learn_ena",             /* name */         
                                   sizeof(int),    /* size of the element's type*/          
                                   0,                 /* nof pointers */ 
                                   "int",              /* param type */
                                   0,                 /* array size 0 */ 
                                   0));             /* array size 1 */ 
   /* update next free node id */ 
    SW_STATE_NODE_ID_CHECK(unit, ++(*next_free_node_id));  

   SOC_EXIT;
 exit:
   SOC_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#if defined(BCM_PETRA_SUPPORT)
#ifdef BCM_PETRA_SUPPORT
int sw_state_dpp_bcm_l2_mpls_extended_label_ether_type_index_table_is_set_layout_node_create(int unit, int* root_node_id, uint32* next_free_node_id){  

   SOC_INIT_FUNC_DEFS;

   /* update current root node */  
   *root_node_id = *next_free_node_id; 
   /* add node */    
   _SOC_IF_ERR_EXIT(shr_sw_state_ds_layout_node_set(unit, 
                                   *root_node_id,                 /* node id var */      
                                   "mpls_extended_label_ether_type_index_table_is_set",             /* name */         
                                   sizeof(uint16),    /* size of the element's type*/          
                                   0,                 /* nof pointers */ 
                                   "uint16",              /* param type */
                                   0,                 /* array size 0 */ 
                                   0));             /* array size 1 */ 
   /* update next free node id */ 
    SW_STATE_NODE_ID_CHECK(unit, ++(*next_free_node_id));  

   SOC_EXIT;
 exit:
   SOC_FUNC_RETURN;
}

#endif /* BCM_PETRA_SUPPORT*/ 
#endif /* defined(BCM_PETRA_SUPPORT)*/ 