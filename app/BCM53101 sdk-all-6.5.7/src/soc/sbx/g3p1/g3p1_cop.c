
/*
 * $Id: cop_c.stg,v 1.24 Broadcom SDK $
 * $Copyright: (c) 2016 Broadcom.
 * Broadcom Proprietary and Confidential. All rights reserved.$
 *
 * g3p1_cop.c: Guadalupe2k V1.3 TMU table manager & wrappers
 *
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated from sdk/caladan_ucode/g3p1/src/g3p1_cop_cfg.lrp.
 * Edits to this file will be lost when it is regenerated.
 *
 */

#include <shared/bsl.h>

#include <soc/defs.h>

#if defined(BCM_CALADAN3_SUPPORT) && defined(BCM_CALADAN3_G3P1_SUPPORT) 

#include <sal/core/time.h>
#include <sal/core/alloc.h>
#include <sal/core/libc.h>
#include <sal/types.h>
#include <sal/appl/io.h>
#include <soc/types.h>
#include <soc/drv.h>
#include <sal/appl/sal.h>
#include <sal/core/time.h>
#include <appl/diag/test.h>
#include <sal/core/thread.h>  

#include <soc/sbx/caladan3/ocm.h>
#include <soc/sbx/caladan3/cmu.h>
#include <soc/error.h>
#include <soc/debug.h>

#include <soc/sbx/g3p1/g3p1_int.h>
#include <soc/sbx/g3p1/g3p1_cop.h>

#define COP_TIMER_QUEUE_DEPTH 8096

typedef struct cop_segment_desc_s {
  uint32 cop_instance;
  uint32 segment;
  uint32 num_entries;
  uint32 last_entry_num;
} cop_segment_desc_t;


static uint32 cop_ocm_memory[2] = {131840, 65536 }; /* this is calculated by ASM3 */

static cop_segment_desc_t policer_segment_desc[COP_POLICER_SEGMENT_LAST];
static cop_segment_desc_t sequencer_segment_desc[COP_SEQUENCER_SEGMENT_LAST];
static cop_segment_desc_t coherent_table_segment_desc[COP_COHERENT_TABLE_SEGMENT_LAST];
static cop_segment_desc_t timer_segment_desc[COP_TIMER_SEGMENT_LAST];
static void *timer_cb_cookie;
static soc_sbx_g3p1_cop_timer_event_callback_f timer_cb;

static int init_policer_segment_xtpol(int unit) {
    int rv;
    soc_sbx_caladan3_cop_segment_type_specific_config_t config;

    config.sPolicer.bErrorMask = 0;
    config.sPolicer.nErrorColor = 0;
    config.sPolicer.uMaxRateKbps = 102400;
    config.sPolicer.uMaxBurstBits = 524288;
    rv = soc_sbx_caladan3_cop_segment_register(unit, 0, 0,
              256,  SOC_SBX_CALADAN3_COP_SEGMENT_TYPE_POLICER, &config);
    if (SOC_FAILURE(rv)) {
        LOG_CLI((BSL_META_U(unit,
                            "Failed to register COP 0 segment 0 on unit %d\n"), unit));
        return rv;
    }

    policer_segment_desc[COP_POLICER_SEGMENT_XTPOL].cop_instance = 0;
    policer_segment_desc[COP_POLICER_SEGMENT_XTPOL].segment = 0;
    policer_segment_desc[COP_POLICER_SEGMENT_XTPOL].num_entries = 256;
    policer_segment_desc[COP_POLICER_SEGMENT_XTPOL].last_entry_num = 0;

    return SOC_E_NONE;
}

static int init_policer_segment_ingpol(int unit) {
    int rv;
    soc_sbx_caladan3_cop_segment_type_specific_config_t config;

    config.sPolicer.bErrorMask = 0;
    config.sPolicer.nErrorColor = 0;
    config.sPolicer.uMaxRateKbps = 104857600;
    config.sPolicer.uMaxBurstBits = 524288;
    rv = soc_sbx_caladan3_cop_segment_register(unit, 1, 0,
              65536,  SOC_SBX_CALADAN3_COP_SEGMENT_TYPE_POLICER, &config);
    if (SOC_FAILURE(rv)) {
        LOG_CLI((BSL_META_U(unit,
                            "Failed to register COP 1 segment 0 on unit %d\n"), unit));
        return rv;
    }

    policer_segment_desc[COP_POLICER_SEGMENT_INGPOL].cop_instance = 1;
    policer_segment_desc[COP_POLICER_SEGMENT_INGPOL].segment = 0;
    policer_segment_desc[COP_POLICER_SEGMENT_INGPOL].num_entries = 65536;
    policer_segment_desc[COP_POLICER_SEGMENT_INGPOL].last_entry_num = 0;

    return SOC_E_NONE;
}

static int init_policer_segment_egrpol(int unit) {
    int rv;
    soc_sbx_caladan3_cop_segment_type_specific_config_t config;

    config.sPolicer.bErrorMask = 0;
    config.sPolicer.nErrorColor = 0;
    config.sPolicer.uMaxRateKbps = 104857600;
    config.sPolicer.uMaxBurstBits = 524288;
    rv = soc_sbx_caladan3_cop_segment_register(unit, 0, 1,
              65536,  SOC_SBX_CALADAN3_COP_SEGMENT_TYPE_POLICER, &config);
    if (SOC_FAILURE(rv)) {
        LOG_CLI((BSL_META_U(unit,
                            "Failed to register COP 0 segment 1 on unit %d\n"), unit));
        return rv;
    }

    policer_segment_desc[COP_POLICER_SEGMENT_EGRPOL].cop_instance = 0;
    policer_segment_desc[COP_POLICER_SEGMENT_EGRPOL].segment = 1;
    policer_segment_desc[COP_POLICER_SEGMENT_EGRPOL].num_entries = 65536;
    policer_segment_desc[COP_POLICER_SEGMENT_EGRPOL].last_entry_num = 0;

    return SOC_E_NONE;
}


static int init_timer_segment_oamtimer(int unit) {
  int rv;
  soc_sbx_caladan3_cop_segment_type_specific_config_t config;

  config.sTimer.bMode64 = TRUE; 
  config.sTimer.nTimerTickUs = 1000; 
  rv = soc_sbx_caladan3_cop_segment_register(unit, 0, 2,        
            65536,  SOC_SBX_CALADAN3_COP_SEGMENT_TYPE_TIMER, &config);
  if (SOC_FAILURE(rv)) {
    LOG_CLI((BSL_META_U(unit,
                        "Failed to register COP 0 segment 2 on unit %d\n"), unit));
    return rv;
  }

  timer_segment_desc[COP_TIMER_SEGMENT_OAMTIMER].cop_instance = 0;
  timer_segment_desc[COP_TIMER_SEGMENT_OAMTIMER].segment = 2;
  timer_segment_desc[COP_TIMER_SEGMENT_OAMTIMER].num_entries = 65536;
  timer_segment_desc[COP_TIMER_SEGMENT_OAMTIMER].last_entry_num = 0;

  return SOC_E_NONE;
}

static int init_sequencer_segment_oamseq(int unit) {
  int rv;
  soc_sbx_caladan3_cop_segment_type_specific_config_t config;

  config.sChecker.bMode32 = TRUE; 
  config.sChecker.uSequenceRange = 32; 
  rv = soc_sbx_caladan3_cop_segment_register(unit, 0, 3,
          512, SOC_SBX_CALADAN3_COP_SEGMENT_TYPE_SN_CHECKER, &config);
  if (SOC_FAILURE(rv)) {
    LOG_CLI((BSL_META_U(unit,
                        "Failed to register COP 0 segment 3 on unit %d\n"), unit));
    return rv;
  }

  sequencer_segment_desc[COP_SEQUENCER_SEGMENT_OAMSEQ].cop_instance = 0;
  sequencer_segment_desc[COP_SEQUENCER_SEGMENT_OAMSEQ].segment = 3;
  sequencer_segment_desc[COP_SEQUENCER_SEGMENT_OAMSEQ].num_entries = 512;
  sequencer_segment_desc[COP_SEQUENCER_SEGMENT_OAMSEQ].last_entry_num = 0;

  return SOC_E_NONE;
}

static int init_coherent_table_segment_coherent(int unit) {
  int rv;
  soc_sbx_caladan3_cop_segment_type_specific_config_t config;

  config.sCoherent.bReturnNext = FALSE;
  config.sCoherent.nOverflowMode = SOC_SBX_CALADAN3_COP_COHERENT_OVERFLOW_ROLLOVER;
  config.sCoherent.nFormat = SOC_SBX_CALADAN3_COP_COHERENT_FORMAT_32BIT;
  rv = soc_sbx_caladan3_cop_segment_register(unit, 0, 4,
            512, SOC_SBX_CALADAN3_COP_SEGMENT_TYPE_COHERENT, &config);
  if (SOC_FAILURE(rv)) {
    LOG_CLI((BSL_META_U(unit,
               			"Failed to register COP 0 segment 4 on unit %d\n"), unit));
    return rv;
  }

  coherent_table_segment_desc[COP_COHERENT_TABLE_SEGMENT_COHERENT].cop_instance = 0;
  coherent_table_segment_desc[COP_COHERENT_TABLE_SEGMENT_COHERENT].segment = 4;
  coherent_table_segment_desc[COP_COHERENT_TABLE_SEGMENT_COHERENT].num_entries = 512;
  coherent_table_segment_desc[COP_COHERENT_TABLE_SEGMENT_COHERENT].last_entry_num = 0;

  return SOC_E_NONE;
}


int soc_sbx_g3p1_cop_init(int unit) {
  sbx_caladan3_ocm_port_alloc_t ocm_desc;
  int i, rv;

  for (i=0; i<2; i++) {
    ocm_desc.port = (i == 0) ? SOC_SBX_CALADAN3_OCM_COP0_PORT : SOC_SBX_CALADAN3_OCM_COP1_PORT;
    ocm_desc.segment = -1;
    ocm_desc.size = cop_ocm_memory[i];
    ocm_desc.datum_size = SOC_SBX_CALADAN3_DATUM_SIZE_QUADWORD;

    rv = soc_sbx_caladan3_ocm_port_mem_alloc(unit, &ocm_desc);
    if (SOC_FAILURE(rv)) {
      LOG_CLI((BSL_META_U(unit,
               			  "C3 %d OCM memory Allocation failed for port %d\n"),unit, ocm_desc.port));
      return rv;
    }

    rv = soc_sbx_caladan3_cop_ocm_memory_size_set(unit, i, (ocm_desc.size * ocm_desc.datum_size)/8);
    if (SOC_FAILURE(rv)) {
      LOG_CLI((BSL_META_U(unit,
                 		  "Failed to config COP %d mem size on unit %d\n"), i, unit));
      return rv;
    }

    rv = soc_sbx_caladan3_cop_timer_event_queue_size_set(unit, i, COP_TIMER_QUEUE_DEPTH);
    if (SOC_FAILURE(rv)) {
      LOG_CLI((BSL_META_U(unit,
                 		  "Failed to config COP %d timer event queue size on unit %d\n"), i, unit));
      return rv;
    }
  }
  rv = init_policer_segment_xtpol(unit);
  if (SOC_FAILURE(rv)) {
      return rv;
  } 
  rv = init_policer_segment_ingpol(unit);
  if (SOC_FAILURE(rv)) {
      return rv;
  } 
  rv = init_policer_segment_egrpol(unit);
  if (SOC_FAILURE(rv)) {
      return rv;
  } 
  rv = init_timer_segment_oamtimer(unit);
  if (SOC_FAILURE(rv)) {
      return rv;
  }
  rv = init_sequencer_segment_oamseq(unit);
  if (SOC_FAILURE(rv)) {
      return rv;
  }
  rv = init_coherent_table_segment_coherent(unit);
  if (SOC_FAILURE(rv)) {
      return rv;
  }
  timer_cb = NULL;
  timer_cb_cookie = NULL;

  return SOC_E_NONE;
}

int soc_sbx_g3p1_cop_uninit(int unit) {
  int i, rv;
  sbx_caladan3_ocm_port_alloc_t ocm_desc;

  for (i=0; i<2; i++) {
    ocm_desc.port = (i == 0) ? SOC_SBX_CALADAN3_OCM_COP0_PORT : SOC_SBX_CALADAN3_OCM_COP1_PORT;
    ocm_desc.segment = -1;
    ocm_desc.size = cop_ocm_memory[i];
    ocm_desc.datum_size = SOC_SBX_CALADAN3_DATUM_SIZE_QUADWORD;

    rv = soc_sbx_caladan3_cop_ocm_memory_size_set(unit, i, 0);
    if (SOC_FAILURE(rv)) {
      LOG_CLI((BSL_META_U(unit,
                 		  "Failed to config COP %d mem size on unit %d\n"), i, unit));
      return rv;
    }

    rv = soc_sbx_caladan3_ocm_port_mem_free(unit, &ocm_desc);
    if (SOC_FAILURE(rv)) {
         LOG_CLI((BSL_META_U(unit,
                    		 "C3 %d OCM memory free failed for port %d\n"),unit, ocm_desc.port));
         return rv;
    }
  }

  return SOC_E_NONE;
}

void soc_sbx_g3p1_policer_config_init(soc_sbx_g3p1_policer_config_t *config) {
  sal_memset(config, 0, sizeof(soc_sbx_g3p1_policer_config_t));
  config->mode = COP_POLICER_MODE_RFC_2697;
  config->policer_id = 0;
  config->ignore_packet_color = FALSE;
  config->strict_cir_mode = TRUE;
  config->strict_eir_mode = TRUE;
  config->drop_on_red = FALSE;
  config->cbs_non_decrement = FALSE;
  config->ebs_non_decrement = FALSE;
  config->packet_length_bias = 0;
  config->ignore_packet_length = FALSE;
}

int soc_sbx_g3p1_policer_create(int unit, soc_sbx_g3p1_policer_segment_t policer_segment, soc_sbx_g3p1_policer_config_t *config, uint32 *policer_handle) {
  int rv;
  cop_segment_desc_t *seg_desc;
  soc_sbx_caladan3_cop_policer_config_t policer;

  seg_desc = &policer_segment_desc[policer_segment];
  policer.uRfcMode = config->mode;
  policer.uCIR = config->cir;
  policer.uCBS = config->cbs;
  policer.uEIR = config->eir;
  policer.uEBS = config->ebs;
  policer.bBlindMode = config->ignore_packet_color;
  policer.bDropOnRed = config->drop_on_red;
  policer.bCoupling = config->coupling;
  policer.bCBSNoDecrement = config->cbs_non_decrement;
  policer.bEBSNoDecrement = config->ebs_non_decrement;
  policer.bCIRStrict = config->strict_cir_mode;
  policer.bEIRStrict = config->strict_eir_mode;
  policer.nLenAdjust = config->packet_length_bias;
  policer.bPktMode = config->ignore_packet_length;

  if (SAL_BOOT_BCMSIM) {
    rv = soc_sbx_caladan3_cop_policer_create_sim(unit, seg_desc->cop_instance, seg_desc->segment,
                   config->policer_id, &policer, policer_handle);  
  }
  else {
    rv = soc_sbx_caladan3_cop_policer_create(unit, seg_desc->cop_instance, seg_desc->segment,
                   config->policer_id, &policer, policer_handle);
  }
                   
  if (SOC_FAILURE(rv)) {
    LOG_CLI((BSL_META_U(unit,
               			"Failed to create policer %d on COP %d segment %d unit %d\n"),
               config->policer_id, seg_desc->cop_instance, seg_desc->segment, unit));
    return rv;
  }

  return SOC_E_NONE;
}

int soc_sbx_g3p1_policer_delete(int unit, soc_sbx_g3p1_policer_segment_t policer_segment, uint32 policer_id) {
  int rv;
  cop_segment_desc_t  *seg_desc;
  uint32 policer_handle;

  /* Construct handle */
  seg_desc = &policer_segment_desc[policer_segment];
  policer_handle = _COP_HANDLE_SET(seg_desc->cop_instance, seg_desc->segment, policer_id); 

  rv = soc_sbx_caladan3_cop_policer_delete(unit, policer_handle);
  if (SOC_FAILURE(rv)) {
    LOG_CLI((BSL_META_U(unit,
               			"Failed to delete policer %d unit %d\n"),
             policer_handle, unit));
    return rv;
  }

  return SOC_E_NONE;
}

int soc_sbx_g3p1_policer_delete_all(int unit, soc_sbx_g3p1_policer_segment_t policer_segment){
    int rv, num_entries;
    soc_sbx_caladan3_cop_segment_type_e_t seg_type;
    soc_sbx_caladan3_cop_segment_type_specific_config_t config;
    cop_segment_desc_t *seg_desc = &policer_segment_desc[policer_segment];

    rv = soc_sbx_caladan3_cop_segment_read(unit, seg_desc->cop_instance, seg_desc->segment,
                    &num_entries, &seg_type, &config);
    if (SOC_FAILURE(rv)) {
        LOG_CLI((BSL_META_U(unit,
                            "Failed to register COP %d segment %d on unit %d\n"), seg_desc->cop_instance, seg_desc->segment, unit));
        return rv;
    }

    rv = soc_sbx_caladan3_cop_segment_unregister(unit, seg_desc->cop_instance, seg_desc->segment);
    if (SOC_FAILURE(rv)) {
        LOG_CLI((BSL_META_U(unit,
                   			"Failed to delete all policers on COP %d segment %d unit %d\n"),
                   seg_desc->cop_instance, seg_desc->segment, unit));
        return rv;
    }

    rv = soc_sbx_caladan3_cop_segment_register(unit, seg_desc->cop_instance, seg_desc->segment,
              num_entries,  SOC_SBX_CALADAN3_COP_SEGMENT_TYPE_POLICER, &config);
    if (SOC_FAILURE(rv)) {
        LOG_CLI((BSL_META_U(unit,
                            "Failed to register COP 0 segment 0 on unit %d\n"), unit));
        return rv;
    }

    seg_desc->last_entry_num = 0;

    return SOC_E_NONE;
}

int soc_sbx_g3p1_policer_read(int unit, soc_sbx_g3p1_policer_segment_t policer_segment, uint32 policer_id, soc_sbx_g3p1_policer_config_t *config) {
  int rv;
  cop_segment_desc_t  *seg_desc;
  uint32 policer_handle;
  soc_sbx_caladan3_cop_policer_config_t policer;

  /* Construct handle */
  seg_desc = &policer_segment_desc[policer_segment];
  policer_handle = _COP_HANDLE_SET(seg_desc->cop_instance, seg_desc->segment, policer_id); 

  rv = soc_sbx_caladan3_cop_policer_read(unit, policer_handle, &policer);
  if (SOC_FAILURE(rv)) {
    if (rv != SOC_E_NOT_FOUND) {
      LOG_CLI((BSL_META_U(unit,
                 		  "Failed to read policer %d unit %d\n"),
                 policer_handle, unit));
    } 
    return rv;
  }

  /* Return data */
  config->policer_id = policer_id; 
  config->mode = policer.uRfcMode;
  config->cir = policer.uCIR;
  config->cbs = policer.uCBS;
  config->eir = policer.uEIR;
  config->ebs = policer.uEBS;
  config->ignore_packet_color = policer.bBlindMode;
  config->drop_on_red = policer.bDropOnRed;
  config->coupling = policer.bCoupling;
  config->strict_cir_mode = policer.bCIRStrict;
  config->strict_eir_mode = policer.bEIRStrict;
  config->cbs_non_decrement = policer.bCBSNoDecrement;
  config->ebs_non_decrement = policer.bEBSNoDecrement;
  config->packet_length_bias = policer.nLenAdjust;
  config->ignore_packet_length = 0;

  return SOC_E_NONE;
}

int soc_sbx_g3p1_timer_create(int unit, soc_sbx_g3p1_cop_timer_segment_t timer_segment, uint32 timeout_ticks, uint32* timer_handle, uint32 id, int doInterrupt, int start) {
  int rv;
  cop_segment_desc_t *seg_desc;
        soc_sbx_caladan3_cop_timer_config_t sTimer;

  seg_desc = &timer_segment_desc[timer_segment];
        sTimer.uTimeout = timeout_ticks;
        sTimer.bInterrupt = (doInterrupt != 0);
        sTimer.bStart = (start != 0);
  rv = soc_sbx_caladan3_cop_timer_create(unit, seg_desc->cop_instance, seg_desc->segment,
                     id, &sTimer, timer_handle);
  if (SOC_FAILURE(rv)) {
    LOG_CLI((BSL_META_U(unit,
               			"Failed to create timer %d on COP %d segment %d unit %d \n"),
               seg_desc->last_entry_num, seg_desc->cop_instance, seg_desc->segment, unit));
    return rv;
  }

  return SOC_E_NONE;
}

int soc_sbx_g3p1_timer_delete(int unit, uint32 timer_handle) {
  int rv;

  rv = soc_sbx_caladan3_cop_timer_delete(unit, timer_handle);
  if (SOC_FAILURE(rv)) {
    LOG_CLI((BSL_META_U(unit,
               			"Failed to delete timer unit %d\n"), unit));
    return rv;
  }

  return SOC_E_NONE;
}

int soc_sbx_g3p1_timer_delete_all(int unit, soc_sbx_g3p1_cop_timer_segment_t timer_segment){
    int rv, num_entries;
    soc_sbx_caladan3_cop_segment_type_e_t seg_type;
    soc_sbx_caladan3_cop_segment_type_specific_config_t config;
    cop_segment_desc_t *seg_desc = &policer_segment_desc[timer_segment];
    
    rv = soc_sbx_caladan3_cop_segment_read(unit, seg_desc->cop_instance, seg_desc->segment,
                    &num_entries, &seg_type, &config);
    if (SOC_FAILURE(rv)) {
        LOG_CLI((BSL_META_U(unit,
                   			"Failed to register COP %d segment %d on unit %d\n"), seg_desc->cop_instance, seg_desc->segment, unit));
        return rv;
    }

    rv = soc_sbx_caladan3_cop_segment_unregister(unit, seg_desc->cop_instance, seg_desc->segment);
    if (SOC_FAILURE(rv)) {
        LOG_CLI((BSL_META_U(unit,
                   			"Failed to delete all policers on COP %d segment %d unit %d\n"),
                   seg_desc->cop_instance, seg_desc->segment, unit));
        return rv;
    }

    rv = soc_sbx_caladan3_cop_segment_register(unit, seg_desc->cop_instance, seg_desc->segment,
              num_entries,  SOC_SBX_CALADAN3_COP_SEGMENT_TYPE_TIMER, &config);
    if (SOC_FAILURE(rv)) {
        LOG_CLI((BSL_META_U(unit,
                   			"Failed to register COP 0 segment 0 on unit %d\n"), unit));
        return rv;
    }

    seg_desc->last_entry_num = 0;

    return SOC_E_NONE;
}

int soc_sbx_g3p1_timer_poll(int unit, soc_sbx_g3p1_cop_timer_event_t *event) {
  int rv, i, j;
  soc_sbx_caladan3_cop_timer_expire_event_t timer_event;

  for (i=0; i<2; i++) {
    rv = soc_sbx_caladan3_cop_timer_event_dequeue(unit, i, &timer_event);
      if (SOC_FAILURE(rv)) {
         continue;
      }

      for (j=0; j<COP_TIMER_SEGMENT_LAST; j++) {
        if (timer_segment_desc[j].segment == timer_event.uSegment) {
          event->timer_segment = timer_event.uSegment;
          event->fired_timer_handle = timer_event.uTimer;
          event->forced_timeout = timer_event.bForced;
          event->timer_active_when_forced = timer_event.bActiveWhenForced;

          return SOC_E_NONE;
        }
      }
  }

  return SOC_E_NOT_FOUND;
}

int soc_sbx_g3p1_sequencer_create(int unit, soc_sbx_g3p1_cop_sequencer_segment_t seq_segment, uint32 init_value, uint32 *handle) {
  int rv;
  cop_segment_desc_t *seg_desc;

  seg_desc = &sequencer_segment_desc[seq_segment];
  rv = soc_sbx_caladan3_cop_seq_checker_create(unit, seg_desc->cop_instance, seg_desc->segment, seg_desc->last_entry_num, init_value, handle);
  if (SOC_FAILURE(rv)) {
    LOG_CLI((BSL_META_U(unit,
               			"Failed to create sequence checker %d on COP %d segment %d unit %d\n"),
               seg_desc->last_entry_num, seg_desc->cop_instance, seg_desc->segment, unit));
    return rv;
  }

  seg_desc->last_entry_num++;
  return SOC_E_NONE;
}

int soc_sbx_g3p1_sequencer_delete(int unit, uint32 seq_handle) {
  int rv;

  rv = soc_sbx_caladan3_cop_seq_checker_delete(unit, seq_handle);
  if (SOC_FAILURE(rv)) {
    LOG_CLI((BSL_META_U(unit,
               			"Failed to delete sequencer unit %d\n"), unit));
    return rv;
  }

  return SOC_E_NONE;
}

int soc_sbx_g3p1_sequencer_delete_all(int unit, soc_sbx_g3p1_cop_sequencer_segment_t seq_segment){
    int rv, num_entries;
    soc_sbx_caladan3_cop_segment_type_e_t seg_type;
    soc_sbx_caladan3_cop_segment_type_specific_config_t config;
    cop_segment_desc_t *seg_desc = &sequencer_segment_desc[seq_segment];

    rv = soc_sbx_caladan3_cop_segment_read(unit, seg_desc->cop_instance, seg_desc->segment,
                    &num_entries, &seg_type, &config);
    if (SOC_FAILURE(rv)) {
        LOG_CLI((BSL_META_U(unit,
                   			"Failed to register COP %d segment %d on unit %d\n"), seg_desc->cop_instance, seg_desc->segment, unit));
        return rv;
    }

    rv = soc_sbx_caladan3_cop_segment_unregister(unit, seg_desc->cop_instance, seg_desc->segment);
    if (SOC_FAILURE(rv)) {
        LOG_CLI((BSL_META_U(unit,
                   			"Failed to delete all sequencers on COP %d segment %d unit %d\n"),
                   seg_desc->cop_instance, seg_desc->segment, unit));
        return rv;
    }

    rv = soc_sbx_caladan3_cop_segment_register(unit, seg_desc->cop_instance, seg_desc->segment,
              num_entries,  SOC_SBX_CALADAN3_COP_SEGMENT_TYPE_SN_CHECKER, &config);
    if (SOC_FAILURE(rv)) {
        LOG_CLI((BSL_META_U(unit,
                   			"Failed to register COP 0 segment 0 on unit %d\n"), unit));
        return rv;
    }

    seg_desc->last_entry_num = 0;

    return SOC_E_NONE;
}

int soc_sbx_g3p1_coherent_table_create(int unit, soc_sbx_g3p1_cop_coherent_table_segment_t segment,
                      uint32 init_value_bits31_0, uint32 init_value_bits63_32, uint32 *handle) {
  int rv;
  cop_segment_desc_t *seg_desc;

  seg_desc = &coherent_table_segment_desc[segment];
  rv = soc_sbx_caladan3_cop_coherent_table_create(unit, seg_desc->cop_instance, seg_desc->segment,
              seg_desc->last_entry_num, init_value_bits31_0, init_value_bits63_32, handle);
  if (SOC_FAILURE(rv)) {
    LOG_CLI((BSL_META_U(unit,
               			"Failed to create coherent table %d on COP %d segment %d unit %d\n"),
               seg_desc->last_entry_num, seg_desc->cop_instance, seg_desc->segment, unit));
    return rv;
  }

  seg_desc->last_entry_num++;
  return SOC_E_NONE;
}

int soc_sbx_g3p1_coherent_table_get(int unit,
        soc_sbx_g3p1_cop_coherent_table_segment_t segment, uint32 entry,
        uint32 *bits31_0, uint32 *bits63_32) {

    int rv = SOC_E_NONE;
    cop_segment_desc_t *seg_desc;
    uint32 handle;

    if (segment >= COP_COHERENT_TABLE_SEGMENT_LAST) {
        LOG_CLI((BSL_META_U(unit,
                   			"Invalid coherent table %d of unit %d, max %d\n"),
                   segment, unit, COP_COHERENT_TABLE_SEGMENT_LAST));
        return SOC_E_PARAM;
    }

    seg_desc = &coherent_table_segment_desc[segment];
    if (entry > seg_desc->num_entries) {
        LOG_CLI((BSL_META_U(unit,
                   			"Invalid coherent table entry %d of table %d unit %d, max %d\n"),
                   entry, segment, unit, seg_desc->num_entries));
        return SOC_E_PARAM;
    }

	handle = _COP_HANDLE_SET(seg_desc->cop_instance, seg_desc->segment, segment);
    rv = soc_sbx_caladan3_cop_coherent_table_get(unit, handle, entry, bits31_0, bits63_32);

    if (SOC_FAILURE(rv)) {
        LOG_CLI((BSL_META_U(unit,
                   			"Failed to get coherent table %d on COP %d segment %d unit %d\n"),
                   entry, seg_desc->cop_instance, seg_desc->segment, unit));
        return rv;
    }

    return SOC_E_NONE;
}

int soc_sbx_g3p1_coherent_table_set(int unit,
        soc_sbx_g3p1_cop_coherent_table_segment_t segment, uint32 entry,
        uint32 bits31_0, uint32 bits63_32) {

    int rv = SOC_E_NONE;
    cop_segment_desc_t *seg_desc;
    uint32 handle;

    if (segment >= COP_COHERENT_TABLE_SEGMENT_LAST) {
        LOG_CLI((BSL_META_U(unit,
                   			"Invalid coherent table %d of unit %d, max %d\n"),
                   segment, unit, COP_COHERENT_TABLE_SEGMENT_LAST));
        return SOC_E_PARAM;
    }

    seg_desc = &coherent_table_segment_desc[segment];
    if (entry > seg_desc->num_entries) {
        LOG_CLI((BSL_META_U(unit,
                   			"Invalid coherent table entry %d of table %d unit %d, max %d\n"),
                   entry, segment, unit, seg_desc->num_entries));
        return SOC_E_PARAM;
    }

    handle = _COP_HANDLE_SET(seg_desc->cop_instance, seg_desc->segment, segment);
    rv = soc_sbx_caladan3_cop_coherent_table_set(unit, handle, entry, bits31_0, bits63_32);

    if (SOC_FAILURE(rv)) {
        LOG_CLI((BSL_META_U(unit,
                   			"Failed to set coherent table %d on COP %d segment %d unit %d\n"),
                   entry, seg_desc->cop_instance, seg_desc->segment, unit));
        return rv;
    }

    return SOC_E_NONE;
} 

int soc_sbx_g3p1_coherent_table_delete(int unit, uint32 handle) {
  int rv;

  rv = soc_sbx_caladan3_cop_coherent_table_delete(unit, handle);
  if (SOC_FAILURE(rv)) {
    LOG_CLI((BSL_META_U(unit,
               			"Failed to delete coherent table unit %d\n"), unit));
    return rv;
  }

  return SOC_E_NONE;
}

int soc_sbx_g3p1_coherent_table_delete_all(int unit, soc_sbx_g3p1_cop_coherent_table_segment_t coherent_segment){
    int rv, num_entries;
    soc_sbx_caladan3_cop_segment_type_e_t seg_type;
    soc_sbx_caladan3_cop_segment_type_specific_config_t config;
    cop_segment_desc_t *seg_desc = &coherent_table_segment_desc[coherent_segment];
    
    rv = soc_sbx_caladan3_cop_segment_read(unit, seg_desc->cop_instance, seg_desc->segment,
                    &num_entries, &seg_type, &config);
    if (SOC_FAILURE(rv)) {
        LOG_CLI((BSL_META_U(unit,
                   			"Failed to register COP %d segment %d on unit %d\n"), seg_desc->cop_instance, seg_desc->segment, unit));
        return rv;
    }

    rv = soc_sbx_caladan3_cop_segment_unregister(unit, seg_desc->cop_instance, seg_desc->segment);
    if (SOC_FAILURE(rv)) {
        LOG_CLI((BSL_META_U(unit,
                   			"Failed to delete all coherent tables on COP %d segment %d unit %d\n"),
                   seg_desc->cop_instance, seg_desc->segment, unit));
        return rv;
    }

    rv = soc_sbx_caladan3_cop_segment_register(unit, seg_desc->cop_instance, seg_desc->segment,
              num_entries,  SOC_SBX_CALADAN3_COP_SEGMENT_TYPE_COHERENT, &config);
    if (SOC_FAILURE(rv)) {
        LOG_CLI((BSL_META_U(unit,
                   			"Failed to register COP 0 segment 0 on unit %d\n"), unit));
        return rv;
    }
    seg_desc->last_entry_num = 0;

    return SOC_E_NONE;
}



#endif
