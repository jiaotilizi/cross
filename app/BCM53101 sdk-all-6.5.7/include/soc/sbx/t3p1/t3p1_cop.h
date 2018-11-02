
/*
 * $Id: cop_h.stg,v 1.15 Broadcom SDK $
 * $Copyright: (c) 2016 Broadcom.
 * Broadcom Proprietary and Confidential. All rights reserved.$
 *
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated from sdk/caladan_ucode/t3p1/src/t3p1_cop_cfg.lrp.
 * Edits to this file will be lost when it is regenerated.
 *
 */

#ifndef _SOC_SBX_T3P1_COP_H
#define _SOC_SBX_T3P1_COP_H

#if defined(BCM_CALADAN3_SUPPORT) && defined(BCM_CALADAN3_T3P1_SUPPORT) 
#include "cop.h"


extern int soc_sbx_t3p1_cop_init(int unit);
extern int soc_sbx_t3p1_cop_uninit(int unit);

/*
 * POLICERS
 */
typedef enum soc_sbx_t3p1_policer_segment_e {
    COP_POLICER_SEGMENT_INGPOL, 
    COP_POLICER_SEGMENT_LAST
} soc_sbx_t3p1_policer_segment_t;

typedef enum soc_sbx_policer_token_bucket_mode_e {
    COP_POLICER_MODE_RFC_2697,
    COP_POLICER_MODE_RFC_2698,
    COP_POLICER_MODE_RFC_4115,
    COP_POLICER_MODE_MEF
} soc_sbx_policer_token_bucket_mode_t;

typedef struct soc_sbx_t3p1_policer_config_s {

    soc_sbx_policer_token_bucket_mode_t mode;

    /* ID of the policer */
    uint32  policer_id;
    
    /* Two token buckets characterized by bitrate and burst size
    *    C_Bucket CIR: Committed bitrate in kilobits per second.
    *         CBS: Committed burst size in bytes
    *    E_Bucket EIR: Allowed excess bitrate (on top of CIR) in kilobits per second.
    *         EBS: Excess burst size in bytes
    */
    uint32 cir; /* in kbps  */
    uint32 cbs; /* in Bytes */
    uint32 eir; /* in kbps  */
    uint32 ebs; /* in Bytes */

    uint32 ignore_packet_color; /* TRUE: Token bucket does not take any existing packet color into account.
                               * FALSE: Existing packet color is taken into account when metering
                               * Default: False
                               */

    uint32 strict_cir_mode;  /* TRUE: A packet conforms to C_Bucket only when its size is less than tokens in C_Bucket
                * FALSE: A packet conforms when token count in C_Bucket is positive
                * Default: True
                */
                
    uint32 strict_eir_mode;  /* TRUE: A packet conforms to E_Bucket only when its size is less than tokens in E_Bucket
                * FALSE: A packet conforms when token count in E_Bucket is positive
                * Default: True
                */
    uint32 drop_on_red; /* TRUE: Set the drop bit on packets determined to be of red color.
             * FALSE: Do not set the drop bit.
             * Default: False
             */
             
    uint32 cbs_non_decrement; /* TRUE:  Tokens are never deducted from C_Bucket
                 * FALSE: Normal token bucket operation.
                 * Default: False
                 */
    uint32 ebs_non_decrement; /* TRUE:  Tokens are never deducted from E_Bucket
                 * FALSE: Normal token bucket operation.
                 * Default: False
                 */

    int8 packet_length_bias; /* When non-zero, this length is added to packet length. Set to -headerLength
                * to remove the header length from token bucket's packet size based metering
                * Default value: zero
                */
    uint32 ignore_packet_length; /* TRUE: Ignore packet length and use a global packet length value instead
                  * FALSE: Token buckets use the packet length
                  * Default: false
                  */
    uint32 coupling;

} soc_sbx_t3p1_policer_config_t;

extern void soc_sbx_t3p1_policer_config_init(soc_sbx_t3p1_policer_config_t *config);

extern int soc_sbx_t3p1_policer_create(int unit, soc_sbx_t3p1_policer_segment_t policer_segment, soc_sbx_t3p1_policer_config_t *config, uint32 *policer_handle);
extern int soc_sbx_t3p1_policer_delete(int unit, soc_sbx_t3p1_policer_segment_t policer_segment, uint32 policer_id);
extern int soc_sbx_t3p1_policer_delete_all(int unit, soc_sbx_t3p1_policer_segment_t policer_segment);
extern int soc_sbx_t3p1_policer_read(int unit, soc_sbx_t3p1_policer_segment_t policer_segment, uint32 policer_id, soc_sbx_t3p1_policer_config_t *config);  
/*
 * TIMER
 */
typedef enum soc_sbx_t3p1_cop_timer_segment_e {
    COP_TIMER_SEGMENT_OAMTIMER, 
    COP_TIMER_SEGMENT_LAST
} soc_sbx_t3p1_cop_timer_segment_t;

typedef struct soc_sbx_t3p1_cop_timer_fire_s {
    soc_sbx_t3p1_cop_timer_segment_t timer_segment;
    uint32 fired_timer_handle;
    uint8 forced_timeout;
    uint8 timer_active_when_forced;
} soc_sbx_t3p1_cop_timer_event_t;

typedef void (*soc_sbx_t3p1_cop_timer_event_callback_f)(int unit, soc_sbx_t3p1_cop_timer_event_t *event, void *user_cookie);

extern int soc_sbx_t3p1_timer_create(int unit, soc_sbx_t3p1_cop_timer_segment_t timer_segment,
          uint32 timeout_ticks, uint32* timer_handle, uint32 id, int doInterrupt, int start);

extern int soc_sbx_t3p1_timer_delete(int unit, uint32 timer_handle);
extern int soc_sbx_t3p1_timer_delete_all(int unit, soc_sbx_t3p1_cop_timer_segment_t timer_segment);

extern int soc_sbx_t3p1_timer_poll(int unit, soc_sbx_t3p1_cop_timer_event_t *event);

/*
 * Sequencer
 */
typedef enum soc_sbx_t3p1_cop_sequencer_segment_e {
    COP_SEQUENCER_SEGMENT_OAMSEQ, 
    COP_SEQUENCER_SEGMENT_LAST
} soc_sbx_t3p1_cop_sequencer_segment_t;

extern int soc_sbx_t3p1_sequencer_create(int unit, soc_sbx_t3p1_cop_sequencer_segment_t seq_segment, uint32 init_value, uint32 *handle);

extern int soc_sbx_t3p1_sequencer_delete(int unit, uint32 handle);
extern int soc_sbx_t3p1_sequencer_delete_all(int unit, soc_sbx_t3p1_cop_sequencer_segment_t seq_segment);

/*
 * Coherent table
 */
typedef enum soc_sbx_t3p1_cop_coherent_segment_e {
    COP_COHERENT_TABLE_SEGMENT_COHERENT, 
    COP_COHERENT_TABLE_SEGMENT_MAC_LIMIT, 
    COP_COHERENT_TABLE_SEGMENT_LAST
} soc_sbx_t3p1_cop_coherent_table_segment_t;

extern int soc_sbx_t3p1_coherent_table_create(int unit, soc_sbx_t3p1_cop_coherent_table_segment_t segment,
          uint32 init_value_bits31_0, uint32 init_value_bits63_32, uint32 *handle);
extern int soc_sbx_t3p1_coherent_table_get(int unit,
        soc_sbx_t3p1_cop_coherent_table_segment_t segment, uint32 entry,
        uint32 *bits31_0, uint32 *bits63_32);
extern int soc_sbx_t3p1_coherent_table_set(int unit,
        soc_sbx_t3p1_cop_coherent_table_segment_t segment, uint32 entry,
        uint32 bits31_0, uint32 bits63_32); 
extern int soc_sbx_t3p1_coherent_table_delete(int unit, uint32 handle);
extern int soc_sbx_t3p1_coherent_table_delete_all(int unit, soc_sbx_t3p1_cop_coherent_table_segment_t segment);

#endif

#endif

