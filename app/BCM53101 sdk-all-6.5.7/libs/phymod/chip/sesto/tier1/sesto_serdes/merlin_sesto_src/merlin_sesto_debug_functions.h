/*****************************************************************************************
 *****************************************************************************************
 *                                                                                       *
 *  Revision      :  $Id: merlin_sesto_debug_functions.h 776 2014-11-11 18:28:55Z kirand $ *
 *                                                                                       *
 *  Description   :  Functions used internally and available in debug shell only         *
 *                                                                                       *
 * $Copyright: (c) 2016 Broadcom.
 * Broadcom Proprietary and Confidential. All rights reserved.$                                                                 *
 *  No portions of this material may be reproduced in any form without                   *
 *  the written permission of:                                                           *
 *      Broadcom Corporation                                                             *
 *      5300 California Avenue                                                           *
 *      Irvine, CA  92617                                                                *
 *                                                                                       *
 *  All information contained in this document is Broadcom Corporation                   *
 *  company private proprietary, and trade secret.                                       *
 *                                                                                       *
 *****************************************************************************************
 *****************************************************************************************/

/** @file merlin_sesto_debug_functions.h
 * Functions used internally and available in debug shell only
 */

#ifndef MERLIN_SESTO_DEBUG_FUNCTIONS_H
#define MERLIN_SESTO_DEBUG_FUNCTIONS_H

#include "merlin_sesto_usr_includes.h"
#include "merlin_sesto_enum.h"
#include "merlin_sesto_common.h"
#include "eagle_merlin_api_uc_common.h"

/** Lane User Control Function Structure in Microcode */
struct merlin_sesto_usr_ctrl_func_st {
  /** Peaking Filter Adaptation */  
  uint8_t pf_adaptation            ;
  /** DC Offset Adaptation */ 
  uint8_t dc_adaptation            ;
  /** Variable Gain Amplifier adaptation */
  uint8_t vga_adaptation           ;
  /** Slicer Offset tuning */
  uint8_t slicer_offset_tuning     ;
  /** Clk90 Offset adaptation */
  uint8_t clk90_offset_adaptation  ;
  /** P1 Level tuning */
  uint8_t p1_level_tuning          ;
  /** Eye adaptation */
  uint8_t eye_adaptation           ;
  /** All adaptation */
  uint8_t all_adaptation           ;
};

/** Lane User DFE Control Function Structure in Microcode */
struct merlin_sesto_usr_ctrl_dfe_func_st {
  /** DFE tap 1 adaptation */  
  uint8_t dfe_tap1_adaptation      ;
  /** DFE tap 2 adaptation */  
  uint8_t dfe_tap2_adaptation      ;
  /** DFE tap 3 adaptation */  
  uint8_t dfe_tap3_adaptation      ;
  /** DFE tap 4 adaptation */  
  uint8_t dfe_tap4_adaptation      ;
  /** DFE tap 5 adaptation */  
  uint8_t dfe_tap5_adaptation      ;
  /** DFE tap 1 Duty Cycle Distortion */ 
  uint8_t dfe_tap1_dcd             ;
  /** DFE tap 2 Duty Cycle Distortion */ 
  uint8_t dfe_tap2_dcd             ;
};

/** Lane User Control Disable Function Struct */
struct merlin_sesto_usr_ctrl_disable_functions_st {
  struct merlin_sesto_usr_ctrl_func_st field;
  uint8_t  byte;                         
};

/** Lane User Control Disable DFE Function Struct */
struct merlin_sesto_usr_ctrl_disable_dfe_functions_st {
  struct merlin_sesto_usr_ctrl_dfe_func_st field;
  uint8_t  byte;                        
};



/** Isolate Control pins.
 * Can be used for debug to avoid any interference from inputs coming through pins.
 * @param enable Isolate pins enable (1 = Isolate pins; 0 = Pins not isolated)
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors) 
 */
err_code_t merlin_sesto_isolate_ctrl_pins(const phymod_access_t *pa, uint8_t enable);


/*-----------------------*/
/*  Stop/Resume uC Lane  */
/*-----------------------*/
/** Stop/Resume Micro operations on a Lane (Graceful Stop).
 * @param enable Enable micro lane stop (1 = Stop Micro opetarions on lane; 0 = Resume Micro operations on lane) 
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors) 
 */
err_code_t merlin_sesto_stop_uc_lane(const phymod_access_t *pa, uint8_t enable);

/** Status of whether Micro is stopped on a lane.
 * @param *uc_lane_stopped Micro lane stopped status returned by API
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors) 
 */
err_code_t merlin_sesto_stop_uc_lane_status(const phymod_access_t *pa, uint8_t *uc_lane_stopped);

/** Write to lane user control disable startup function uC RAM variable.
 *  Note: This function should be used only during configuration under dp_reset.
 * @param set_val Value to be written into lane user control disable startup function RAM variable
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors) 
 */ 
err_code_t merlin_sesto_set_usr_ctrl_disable_startup(const phymod_access_t *pa, struct merlin_sesto_usr_ctrl_disable_functions_st set_val);

/** Write to lane user control disable startup dfe function uC RAM variable.
 *  Note: This function should be used only during configuration under dp_reset.
 * @param set_val Value to be written into lane user control disable startup dfe function RAM variable
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors) 
 */ 
err_code_t merlin_sesto_set_usr_ctrl_disable_startup_dfe(const phymod_access_t *pa, struct merlin_sesto_usr_ctrl_disable_dfe_functions_st set_val);

/** Write to lane user control disable steady-state function uC RAM variable.
 *  Note: This function should be used only during configuration under dp_reset.
 * @param set_val Value to be written into lane user control disable  steady-state function RAM variable
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors) 
 */ 
err_code_t merlin_sesto_set_usr_ctrl_disable_steady_state(const phymod_access_t *pa, struct merlin_sesto_usr_ctrl_disable_functions_st set_val);

/** Write to lane user control disable steady-state dfe function uC RAM variable.
 *  Note: This function should be used only during configuration under dp_reset.
 * @param set_val Value to be written into lane user control disable  steady-state dfe function RAM variable
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors) 
 */ 
err_code_t merlin_sesto_set_usr_ctrl_disable_steady_state_dfe(const phymod_access_t *pa, struct merlin_sesto_usr_ctrl_disable_dfe_functions_st set_val);

/** Read value of lane user control disable startup uC RAM variable.
 * @param *get_val Value read from lane user control disable startup RAM variable
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors) 
 */ 
err_code_t merlin_sesto_get_usr_ctrl_disable_startup(const phymod_access_t *pa, struct merlin_sesto_usr_ctrl_disable_functions_st *get_val);

/** Read value of lane user control disable startup dfe uC RAM variable.
 * @param *get_val Value read from lane user control disable startup dfe RAM variable
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors) 
 */
err_code_t merlin_sesto_get_usr_ctrl_disable_startup_dfe(const phymod_access_t *pa, struct merlin_sesto_usr_ctrl_disable_dfe_functions_st *get_val);

/** Read value of lane user control disable steady-state uC RAM variable.
 * @param *get_val Value read from lane user control disable steady-state RAM variable
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors) 
 */
err_code_t merlin_sesto_get_usr_ctrl_disable_steady_state(const phymod_access_t *pa, struct merlin_sesto_usr_ctrl_disable_functions_st *get_val);

/** Read value of lane user control disable steady-state dfe uC RAM variable.
 * @param *get_val Value read from lane user control disable steady-state dfe RAM variable
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors) 
 */
err_code_t merlin_sesto_get_usr_ctrl_disable_steady_state_dfe(const phymod_access_t *pa, struct merlin_sesto_usr_ctrl_disable_dfe_functions_st *get_val);


/*-------------------------------------------*/
/*  Registers and Core uC RAM Variable Dump  */
/*-------------------------------------------*/
/** Display values of both Core level and (currently selected) Lane level Registers.
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors) 
 */
err_code_t merlin_sesto_reg_dump(const phymod_access_t *pa );

/** Display values of all Core uC RAM Variables (Core RAM Variable Dump).
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors) 
 */
err_code_t merlin_sesto_uc_core_var_dump(const phymod_access_t *pa );


/*-----------------------------*/
/*  uC RAM Lane Variable Dump  */
/*-----------------------------*/
/** Display values of all Lane uC RAM Variables (Lane RAM Variable Dump).
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors) 
 */
err_code_t merlin_sesto_uc_lane_var_dump(const phymod_access_t *pa );


/*--------------------------*/
/*  TX_PI Jitter Generation */
/*--------------------------*/

/** Generate TX_PI Sinusoidal or Spread-Spectrum (SSC) jitter.
 * @param enable Enable/Disable jitter generation (1 = Enable; 0 = Disable)
 * @param freq_override_val Fixed Frequency Override value (-8192 to + 8192)
 * @param jit_type Jitter generation mode
 * @param tx_pi_jit_freq_idx Jitter generation frequency index (0 to 63) [see spec for more details]
 * @param tx_pi_jit_amp Jitter generation amplification factor (0 to 63) [max value of this register depends on tx_pi_jit_freq_idx and freq_override values]
 * @return Error Code generated by invalid TX_PI settings (returns ERR_CODE_NONE if no errors)
 */
err_code_t merlin_sesto_tx_pi_jitt_gen(const phymod_access_t *pa, uint8_t enable, int16_t freq_override_val, enum srds_tx_pi_freq_jit_gen_enum jit_type, uint8_t tx_pi_jit_freq_idx, uint8_t tx_pi_jit_amp);


/*-------------*/
/*  Event Log  */
/*-------------*/
/** Get Event Log from uC.
 * Dump uC events from core memory.
 * @param *trace_mem Pre-allocated buffer to store trace memory dump.
 * @param display_mode Enable event logs decoding. \n 
 *                      EVENT_LOG_ENCODED(0) - display log in hex octets, \n
 *                      EVENT_LOG_DECODED(1) - display log in plain text, \n
 *                      EVENT_LOG_ENCODED_AND_DECODED(2) - display log in both hex octects and plain text
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors)
 */ 
err_code_t merlin_sesto_read_event_log(const phymod_access_t *pa, uint8_t *trace_mem,enum srds_event_log_display_mode_enum display_mode);

/** Stop Serdes uC Event Logging.
 * Stop writing uC events to core memory.
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors)
 */ 
err_code_t merlin_sesto_event_log_stop(const phymod_access_t *pa );

/** Read Serdes uC Event Logging.
 * Dump uC events from core memory.
 * @param *trace_mem Pre-allocated buffer to store trace memory dump.
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors)
 */ 
err_code_t merlin_sesto_event_log_readmem(const phymod_access_t *pa, uint8_t *trace_mem);

/** Display Serdes uC Event Logging.
 * Display uC events from buffer.
 * @param *trace_mem Pre-allocated buffer to store trace memory dump.
 * @param display_mode Enable event logs decoding. \n
 *                      EVENT_LOG_ENCODED(0) - display log in hex octets, \n 
 *                      EVENT_LOG_DECODED(1) - display log in plain text, \n
 *                      EVENT_LOG_ENCODED_AND_DECODED(2) - display log in both hex octects and plain text
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors)
 */ 
err_code_t merlin_sesto_event_log_display(const phymod_access_t *pa, uint8_t *trace_mem,enum srds_event_log_display_mode_enum display_mode);

/** Write to usr_ctrl_lane_event_log_level uC RAM variable.
 *  Note: This function should be used only during configuration under dp_reset.
 * @param lane_event_log_level Value to be written into usr_ctrl_lane_event_log_level RAM variable
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors) 
 */
err_code_t merlin_sesto_set_usr_ctrl_lane_event_log_level(const phymod_access_t *pa, uint8_t lane_event_log_level);

/** Read value of usr_ctrl_lane_event_log_level uC RAM variable.
 * @param *lane_event_log_level Value read from usr_ctrl_lane_event_log_level RAM variable
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors) 
 */
err_code_t merlin_sesto_get_usr_ctrl_lane_event_log_level(const phymod_access_t *pa, uint8_t *lane_event_log_level);

/** Write to usr_ctrl_core_event_log_level uC RAM variable. 
 * @param core_event_log_level Value to be written into the usr_ctrl_core_event_log_level RAM variable
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors) 
 */
err_code_t merlin_sesto_set_usr_ctrl_core_event_log_level(const phymod_access_t *pa, uint8_t core_event_log_level);

/** Read value of usr_ctrl_core_event_log_level uC RAM variable.
 * @param *core_event_log_level Value read from usr_ctrl_core_event_log_level RAM variable
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors) 
 */
err_code_t merlin_sesto_get_usr_ctrl_core_event_log_level(const phymod_access_t *pa, uint8_t *core_event_log_level);


/*---------------------------------------------*/
/*  Serdes IP RAM access - Lane RAM Variables  */
/*---------------------------------------------*/
/*          rd - read; wr - write              */ 
/*          b  - byte; w  - word               */
/*          l  - lane; c  - core               */
/*          s  - signed                        */
/*---------------------------------------------*/
/** Unsigned Byte Read of a uC RAM Lane variable.
 * Read access through Micro Register Interface for PMD IPs; through Serdes FW DSC Command Interface for external micro IPs.
 * @param *err_code Error Code generated by API (returns ERR_CODE_NONE if no errors)
 * @param addr Address of RAM lane variable to be read
 * @return 8bit unsigned value read from uC RAM
 */ 
uint8_t merlin_sesto_rdbl_uc_var(const phymod_access_t *pa, err_code_t *err_code, uint16_t addr);

/** Unsigned Word Read of a uC RAM Lane variable.
 * Read access through Micro Register Interface for PMD IPs; through Serdes FW DSC Command Interface for external micro IPs.
 * @param *err_code Error Code generated by API (returns ERR_CODE_NONE if no errors)
 * @param addr Address of RAM lane variable to be read
 * @return 16bit unsigned value read from uC RAM
 */ 
uint16_t merlin_sesto_rdwl_uc_var(const phymod_access_t *pa, err_code_t *err_code, uint16_t addr);

/** Unsigned Byte Write of a uC RAM Lane variable.
 * Write access through Micro Register Interface for PMD IPs; through Serdes FW DSC Command Interface for external micro IPs.
 * @param addr Address of RAM lane variable to be written
 * @param wr_val 8bit unsigned value to be written to RAM variable
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors)
 */ 
err_code_t merlin_sesto_wrbl_uc_var(const phymod_access_t *pa, uint16_t addr, uint8_t wr_val);

/** Unsigned Word Write of a uC RAM Lane variable.
 * Write access through Micro Register Interface for PMD IPs; through Serdes FW DSC Command Interface for external micro IPs.
 * @param addr Address of RAM lane variable to be written
 * @param wr_val 16bit unsigned value to be written to RAM variable
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors)
 */ 
err_code_t merlin_sesto_wrwl_uc_var(const phymod_access_t *pa, uint16_t addr, uint16_t wr_val);


/* Signed version of above 4 functions */

/** Signed Byte Read of a uC RAM Lane variable.
 * Read access through Micro Register Interface for PMD IPs; through Serdes FW DSC Command Interface for external micro IPs.
 * @param *err_code Error Code generated by API (returns ERR_CODE_NONE if no errors)
 * @param addr Address of RAM lane variable to be read
 * @return 8bit signed value read from uC RAM
 */ 
int8_t merlin_sesto_rdbls_uc_var(const phymod_access_t *pa, err_code_t *err_code, uint16_t addr);

/** Signed Word Read of a uC RAM Lane variable.
 * Read access through Micro Register Interface for PMD IPs; through Serdes FW DSC Command Interface for external micro IPs.
 * @param *err_code Error Code generated by API (returns ERR_CODE_NONE if no errors)
 * @param addr Address of RAM lane variable to be read
 * @return 16bit signed value read from uC RAM
 */ 
int16_t merlin_sesto_rdwls_uc_var(const phymod_access_t *pa, err_code_t *err_code, uint16_t addr);

/** Signed Byte Write of a uC RAM Lane variable.
 * Write access through Micro Register Interface for PMD IPs; through Serdes FW DSC Command Interface for external micro IPs.
 * @param addr Address of RAM lane variable to be written
 * @param wr_val 8bit signed value to be written to RAM variable
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors)
 */ 
err_code_t merlin_sesto_wrbls_uc_var(const phymod_access_t *pa, uint16_t addr, int8_t wr_val);

/** Signed Word Write of a uC RAM Lane variable.
 * Write access through Micro Register Interface for PMD IPs; through Serdes FW DSC Command Interface for external micro IPs.
 * @param addr Address of RAM lane variable to be written
 * @param wr_val 16bit signed value to be written to RAM variable
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors)
 */ 
err_code_t merlin_sesto_wrwls_uc_var(const phymod_access_t *pa, uint16_t addr, int16_t wr_val);


/*---------------------------------------------*/
/*  Serdes IP RAM access - Core RAM Variables  */
/*---------------------------------------------*/
/** Unsigned Byte Read of a uC RAM Core variable.
 * Read access through Micro Register Interface for PMD IPs; through Serdes FW DSC Command Interface for external micro IPs.
 * @param *err_code Error Code generated by API (returns ERR_CODE_NONE if no errors)
 * @param addr Address of RAM core variable to be read
 * @return 8bit unsigned value read from uC RAM
 */ 
uint8_t merlin_sesto_rdbc_uc_var(const phymod_access_t *pa, err_code_t *err_code, uint8_t addr);

/** Unsigned Word Read of a uC RAM Core variable.
 * Read access through Micro Register Interface for PMD IPs; through Serdes FW DSC Command Interface for external micro IPs.
 * @param *err_code Error Code generated by API (returns ERR_CODE_NONE if no errors)
 * @param addr Address of RAM core variable to be read
 * @return 16bit unsigned value read from uC RAM
 */ 
uint16_t merlin_sesto_rdwc_uc_var(const phymod_access_t *pa, err_code_t *err_code, uint8_t addr);

/** Unsigned Byte Write of a uC RAM Core variable.
 * Write access through Micro Register Interface for PMD IPs; through Serdes FW DSC Command Interface for external micro IPs.
 * @param addr Address of RAM core variable to be written
 * @param wr_val 8bit unsigned value to be written to RAM variable
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors)
 */ 
err_code_t merlin_sesto_wrbc_uc_var(const phymod_access_t *pa, uint8_t addr, uint8_t wr_val);

/** Unsigned Word Write of a uC RAM Core variable.
 * Write access through Micro Register Interface for PMD IPs; through Serdes FW DSC Command Interface for external micro IPs.
 * @param addr Address of RAM core variable to be written
 * @param wr_val 16bit unsigned value to be written to RAM variable
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors)
 */ 
err_code_t merlin_sesto_wrwc_uc_var(const phymod_access_t *pa, uint8_t addr, uint16_t wr_val);


/* Signed version of above 4 functions */

/** Signed Byte Read of a uC RAM Core variable.
 * Read access through Micro Register Interface for PMD IPs; through Serdes FW DSC Command Interface for external micro IPs.
 * @param *err_code Error Code generated by API (returns ERR_CODE_NONE if no errors)
 * @param addr Address of RAM core variable to be read
 * @return 8bit signed value read from uC RAM
 */ 
int8_t merlin_sesto_rdbcs_uc_var(const phymod_access_t *pa, err_code_t *err_code, uint8_t addr);

/** Signed Word Read of a uC RAM Core variable.
 * Read access through Micro Register Interface for PMD IPs; through Serdes FW DSC Command Interface for external micro IPs.
 * @param *err_code Error Code generated by API (returns ERR_CODE_NONE if no errors)
 * @param addr Address of RAM core variable to be read
 * @return 16bit signed value read from uC RAM
 */ 
int16_t merlin_sesto_rdwcs_uc_var(const phymod_access_t *pa, err_code_t *err_code, uint8_t addr);

/** Signed Byte Write of a uC RAM Core variable.
 * Write access through Micro Register Interface for PMD IPs; through Serdes FW DSC Command Interface for external micro IPs.
 * @param addr Address of RAM core variable to be written
 * @param wr_val 8bit signed value to be written to RAM variable
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors)
 */ 
err_code_t merlin_sesto_wrbcs_uc_var(const phymod_access_t *pa, uint8_t addr, int8_t wr_val);

/** Signed Word Write of a uC RAM Core variable.
 * Write access through Micro Register Interface for PMD IPs; through Serdes FW DSC Command Interface for external micro IPs.
 * @param addr Address of RAM core variable to be written
 * @param wr_val 16bit signed value to be written to RAM variable
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors)
 */ 
err_code_t merlin_sesto_wrwcs_uc_var(const phymod_access_t *pa, uint8_t addr, int16_t wr_val);


/*---------------------------------------------------*/
/*  Micro Commands through uC DSC Command Interface  */
/*---------------------------------------------------*/
/** Issue a Micro command through the uC DSC Command Interface and return control immediately.
 * @param cmd Micro command to be issued
 * @param supp_info Supplement information for the Micro command to be issued (RAM read/write address or Micro Control command)
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors) 
 */
err_code_t merlin_sesto_pmd_uc_cmd_return_immediate(const phymod_access_t *pa, enum srds_pmd_uc_cmd_enum cmd, uint8_t supp_info);

/** Issue a Micro command through the uC DSC Command Interface. Control returned only after command is finished.
 * @param cmd Micro command to be issued
 * @param supp_info Supplement information for the Micro command to be issued (RAM read/write address or Micro Control command)
 * @param timeout_ms Time interval in milliseconds inside which the command should be completed; else error issued
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors) 
 */
err_code_t merlin_sesto_pmd_uc_cmd(const phymod_access_t *pa, enum srds_pmd_uc_cmd_enum cmd, uint8_t supp_info, uint32_t timeout_ms);                         

/** Issue a Micro command with data through the uC DSC Command Interface and return control immediately.
 * @param cmd Micro command to be issued
 * @param supp_info Supplement information for the Micro command to be issued (RAM write address)
 * @param data Data to be written to dsc_data for use by uC
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors) 
 */
err_code_t merlin_sesto_pmd_uc_cmd_with_data_return_immediate(const phymod_access_t *pa, enum srds_pmd_uc_cmd_enum cmd, uint8_t supp_info, uint16_t data);

/** Issue a Micro command with data through the uC DSC Command Interface. Control returned only after command is finished.
 * @param cmd Micro command to be issued
 * @param supp_info Supplement information for the Micro command to be issued (RAM write address)
 * @param data Data to be written to dsc_data for use by uC
 * @param timeout_ms Time interval in milliseconds inside which the command should be completed; else error issued
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors) 
 */
err_code_t merlin_sesto_pmd_uc_cmd_with_data(const phymod_access_t *pa, enum srds_pmd_uc_cmd_enum cmd, uint8_t supp_info, uint16_t data, uint32_t timeout_ms); 

/** Issue a Micro Control command through the uC DSC Command Interface and return control immediately.
 * @param control Micro Control command to be issued
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors) 
 */
err_code_t merlin_sesto_pmd_uc_control_return_immediate(const phymod_access_t *pa, enum srds_pmd_uc_ctrl_cmd_enum control);

/** Issue a Micro Control command through the uC DSC Command Interface. Control returned only after command is finished.
 * @param control Micro Control command to be issued
 * @param timeout_ms Time interval in milliseconds inside which the command should be completed; else error issued
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors) 
 */
err_code_t merlin_sesto_pmd_uc_control(const phymod_access_t *pa, enum srds_pmd_uc_ctrl_cmd_enum control, uint32_t timeout_ms);                              

/** Issue a Micro Control command through the uC DSC DIAG_EN Command Interface. Control returned only after command is finished.
 * @param control Micro DIAG Control command to be issued
 * @param timeout_ms Time interval in milliseconds inside which the command should be completed; else error issued
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors) 
 */
err_code_t merlin_sesto_pmd_uc_diag_cmd(const phymod_access_t *pa, enum srds_pmd_uc_diag_cmd_enum control, uint32_t timeout_ms);





/** Unsigned Block RAM read through Micro Register Interface.
 * @param *mem Pointer to memory location where the read values from the Block RAM read should be stored
 * @param addr Starting Address of RAM block to be read
 * @param cnt Number of byte locations to be read from the block
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors)
 */ 
err_code_t merlin_sesto_rdblk_uc_ram(const phymod_access_t *pa, uint8_t *mem, uint16_t addr, uint16_t cnt);

#endif
