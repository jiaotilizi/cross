/**
 * $Id: ppe_diags_h.stg,v 1.11 Broadcom SDK $
 * $Copyright: (c) 2016 Broadcom.
 * Broadcom Proprietary and Confidential. All rights reserved.$
 * 
 *
 * g3p1_diags.h: Guadalupe2k V1.3 microcode diagnostics routines 
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


#ifndef _G3P1_PPE_DIAGS_H
#define _G3P1_PPE_DIAGS_H
#if defined(BCM_CALADAN3_SUPPORT) && defined(BCM_CALADAN3_G3P1_SUPPORT) 
#include <sal/types.h>
#include <soc/sbx/g3p1/g3p1_defs.h>
#include <soc/sbx/g3p1/g3p1_ppe_tables.h>

int soc_sbx_g3p1_ppe_table_shell_print(int unit, int eid, int argc, char **argv);









extern soc_sbx_g3p1_ppe_ptable_cfg_t soc_sbx_g3p1_ppe_ptable_cfg;
extern char soc_sbx_g3p1_ptable_get_usage[];
extern char soc_sbx_g3p1_ptable_set_usage[];
extern int soc_sbx_g3p1_ptable_shell_set(int unit, int argc, char **argv);
extern int soc_sbx_g3p1_ptable_shell_print(int unit, int argc, char **argv);

int soc_sbx_g3p1_ppe_shell_print(int unit, int argc, char **argv);

int soc_sbx_g3p1_ppe_shell_set(int unit, int argc, char **argv);

/** Diagnostic shell set operation usage message */
extern char soc_sbx_g3p1_ppe_set_usage[];
/** Diagnostic shell print operation usage message */
extern char soc_sbx_g3p1_ppe_get_usage[];

#endif
#endif
