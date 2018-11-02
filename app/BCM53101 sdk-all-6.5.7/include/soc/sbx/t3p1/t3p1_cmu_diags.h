/**
 *
 * $Id: t3p1_cmu_diags.h,v 1.1 Broadcom SDK $   
 * $Copyright: (c) 2016 Broadcom.
 * Broadcom Proprietary and Confidential. All rights reserved.$
 * 
 *
 * t3p1_cmu_diags.h: Guadalupe2k V1.3 microcode diagnostics routines 
 *
 * This file provides the public interface to the Guadalupe2k V1.3
 * microcode.  Only explicitly documented elements (types  & functions)
 * are supported, external interfaces.  Other elements are exported only
 * for debugging convenience.
 *
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated.
 * Edits to this file will be lost when it is regenerated.
 */

#ifndef _T3P1_CMU_DIAGS_H_
#define _T3P1_CMU_DIAGS_H_

#if defined(BCM_CALADAN3_SUPPORT) && defined(BCM_CALADAN3_T3P1_SUPPORT) 
#include <sal/types.h>
#include <soc/sbx/t3p1/t3p1_defs.h>
#include <soc/sbx/t3p1/t3p1_cmu.h>

/**
 * Print example_counters.
 *
 * @param[in]  unit chip unit number
 */
extern void soc_sbx_t3p1_example_counters_print(int unit, uint32 start_counter, uint32 num_counters);

/**
 * Reset example_counters.
 *
 * @param[in]  unit chip unit number
 */
extern void soc_sbx_t3p1_example_counters_reset(int unit);


/**
 * Print rtctr.
 *
 * @param[in]  unit chip unit number
 */
extern void soc_sbx_t3p1_rtctr_print(int unit, uint32 start_counter, uint32 num_counters);

/**
 * Reset rtctr.
 *
 * @param[in]  unit chip unit number
 */
extern void soc_sbx_t3p1_rtctr_reset(int unit);



extern int soc_sbx_t3p1_cmu_shell_print(int unit, int argc, char **argv);

extern int soc_sbx_t3p1_cmu_shell_reset(int unit, int argc, char **argv);
        
/** Diagnostic shell set operation usage message */
extern char soc_sbx_t3p1_cmu_reset_usage[];
/** Diagnostic shell print operation usage message */
extern char soc_sbx_t3p1_cmu_get_usage[];

#endif
#endif
