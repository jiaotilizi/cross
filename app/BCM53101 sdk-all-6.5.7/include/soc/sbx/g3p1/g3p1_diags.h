/**
 * $Id: ocm_diags_h.stg,v 1.5 Broadcom SDK $ 
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


#ifndef _G3P1_DIAGS_H
#define _G3P1_DIAGS_H
#if defined(BCM_CALADAN3_SUPPORT) && defined(BCM_CALADAN3_G3P1_SUPPORT) 
#include <sal/types.h>
#include <soc/sbx/g3p1/g3p1_defs.h>

/*
 * Diag shell print routine for Constants
 */
int soc_sbx_g3p1_constant_shell_print(int unit, int cid);

/*
 * Diag shell print routine for Globals
 */
int soc_sbx_g3p1_global_shell_print(int unit, int gid);


/**
 * Print qos entry.
 *
 * @param[in]  unit chip unit number
 * @param[in]  e entry parameters
 */
extern void soc_sbx_g3p1_qos_print(int unit, soc_sbx_g3p1_qos_t *e);

/**
 * Print dscpqos entry.
 *
 * @param[in]  unit chip unit number
 * @param[in]  e entry parameters
 */
extern void soc_sbx_g3p1_dscpqos_print(int unit, soc_sbx_g3p1_dscpqos_t *e);

/**
 * Print irt entry.
 *
 * @param[in]  unit chip unit number
 * @param[in]  e entry parameters
 */
extern void soc_sbx_g3p1_irt_print(int unit, soc_sbx_g3p1_irt_t *e);

/**
 * Print lag entry.
 *
 * @param[in]  unit chip unit number
 * @param[in]  e entry parameters
 */
extern void soc_sbx_g3p1_lag_print(int unit, soc_sbx_g3p1_lag_t *e);

/**
 * Print rrt entry.
 *
 * @param[in]  unit chip unit number
 * @param[in]  e entry parameters
 */
extern void soc_sbx_g3p1_rrt_print(int unit, soc_sbx_g3p1_rrt_t *e);

/**
 * Print xt entry.
 *
 * @param[in]  unit chip unit number
 * @param[in]  e entry parameters
 */
extern void soc_sbx_g3p1_xt_print(int unit, soc_sbx_g3p1_xt_t *e);

/**
 * Print mirror entry.
 *
 * @param[in]  unit chip unit number
 * @param[in]  e entry parameters
 */
extern void soc_sbx_g3p1_mirror_print(int unit, soc_sbx_g3p1_mirror_t *e);

/**
 * Print emirror entry.
 *
 * @param[in]  unit chip unit number
 * @param[in]  e entry parameters
 */
extern void soc_sbx_g3p1_emirror_print(int unit, soc_sbx_g3p1_emirror_t *e);

/**
 * Print macage entry.
 *
 * @param[in]  unit chip unit number
 * @param[in]  e entry parameters
 */
extern void soc_sbx_g3p1_macage_print(int unit, soc_sbx_g3p1_macage_t *e);

/**
 * Print mst entry.
 *
 * @param[in]  unit chip unit number
 * @param[in]  e entry parameters
 */
extern void soc_sbx_g3p1_mst_print(int unit, soc_sbx_g3p1_mst_t *e);

/**
 * Print pv2e entry.
 *
 * @param[in]  unit chip unit number
 * @param[in]  e entry parameters
 */
extern void soc_sbx_g3p1_pv2e_print(int unit, soc_sbx_g3p1_pv2e_t *e);

/**
 * Print p2appdata entry.
 *
 * @param[in]  unit chip unit number
 * @param[in]  e entry parameters
 */
extern void soc_sbx_g3p1_p2appdata_print(int unit, soc_sbx_g3p1_p2appdata_t *e);

/**
 * Print pv2appdata entry.
 *
 * @param[in]  unit chip unit number
 * @param[in]  e entry parameters
 */
extern void soc_sbx_g3p1_pv2appdata_print(int unit, soc_sbx_g3p1_pv2appdata_t *e);

/**
 * Print pvv2edata entry.
 *
 * @param[in]  unit chip unit number
 * @param[in]  e entry parameters
 */
extern void soc_sbx_g3p1_pvv2edata_print(int unit, soc_sbx_g3p1_pvv2edata_t *e);

/**
 * Print v2e entry.
 *
 * @param[in]  unit chip unit number
 * @param[in]  e entry parameters
 */
extern void soc_sbx_g3p1_v2e_print(int unit, soc_sbx_g3p1_v2e_t *e);

/**
 * Print vrid2e entry.
 *
 * @param[in]  unit chip unit number
 * @param[in]  e entry parameters
 */
extern void soc_sbx_g3p1_vrid2e_print(int unit, soc_sbx_g3p1_vrid2e_t *e);

/**
 * Print lp entry.
 *
 * @param[in]  unit chip unit number
 * @param[in]  e entry parameters
 */
extern void soc_sbx_g3p1_lp_print(int unit, soc_sbx_g3p1_lp_t *e);

/**
 * Print l2cp entry.
 *
 * @param[in]  unit chip unit number
 * @param[in]  e entry parameters
 */
extern void soc_sbx_g3p1_l2cp_print(int unit, soc_sbx_g3p1_l2cp_t *e);

/**
 * Print l2cpslow entry.
 *
 * @param[in]  unit chip unit number
 * @param[in]  e entry parameters
 */
extern void soc_sbx_g3p1_l2cpslow_print(int unit, soc_sbx_g3p1_l2cpslow_t *e);

/**
 * Print l2cpnop entry.
 *
 * @param[in]  unit chip unit number
 * @param[in]  e entry parameters
 */
extern void soc_sbx_g3p1_l2cpnop_print(int unit, soc_sbx_g3p1_l2cpnop_t *e);

/**
 * Print ft entry.
 *
 * @param[in]  unit chip unit number
 * @param[in]  e entry parameters
 */
extern void soc_sbx_g3p1_ft_print(int unit, soc_sbx_g3p1_ft_t *e);

/**
 * Print evp2e entry.
 *
 * @param[in]  unit chip unit number
 * @param[in]  e entry parameters
 */
extern void soc_sbx_g3p1_evp2e_print(int unit, soc_sbx_g3p1_evp2e_t *e);

/**
 * Print oi2e entry.
 *
 * @param[in]  unit chip unit number
 * @param[in]  e entry parameters
 */
extern void soc_sbx_g3p1_oi2e_print(int unit, soc_sbx_g3p1_oi2e_t *e);

/**
 * Print remark entry.
 *
 * @param[in]  unit chip unit number
 * @param[in]  e entry parameters
 */
extern void soc_sbx_g3p1_remark_print(int unit, soc_sbx_g3p1_remark_t *e);

/**
 * Print epv2e entry.
 *
 * @param[in]  unit chip unit number
 * @param[in]  e entry parameters
 */
extern void soc_sbx_g3p1_epv2e_print(int unit, soc_sbx_g3p1_epv2e_t *e);

/**
 * Print ert entry.
 *
 * @param[in]  unit chip unit number
 * @param[in]  e entry parameters
 */
extern void soc_sbx_g3p1_ert_print(int unit, soc_sbx_g3p1_ert_t *e);

/**
 * Print oam_bubble entry.
 *
 * @param[in]  unit chip unit number
 * @param[in]  e entry parameters
 */
extern void soc_sbx_g3p1_oam_bubble_print(int unit, soc_sbx_g3p1_oam_bubble_t *e);

/**
 * Print oamrx_p2e entry.
 *
 * @param[in]  unit chip unit number
 * @param[in]  e entry parameters
 */
extern void soc_sbx_g3p1_oamrx_p2e_print(int unit, soc_sbx_g3p1_oamrx_p2e_t *e);

/**
 * Print oam_peer_state entry.
 *
 * @param[in]  unit chip unit number
 * @param[in]  e entry parameters
 */
extern void soc_sbx_g3p1_oam_peer_state_print(int unit, soc_sbx_g3p1_oam_peer_state_t *e);

/**
 * Print ptp_compensation entry.
 *
 * @param[in]  unit chip unit number
 * @param[in]  e entry parameters
 */
extern void soc_sbx_g3p1_ptp_compensation_print(int unit, soc_sbx_g3p1_ptp_compensation_t *e);

/**
 * Print bfd_ld2edata entry.
 *
 * @param[in]  unit chip unit number
 * @param[in]  e entry parameters
 */
extern void soc_sbx_g3p1_bfd_ld2edata_print(int unit, soc_sbx_g3p1_bfd_ld2edata_t *e);

/**
 * Print bfd_ld2edatac entry.
 *
 * @param[in]  unit chip unit number
 * @param[in]  e entry parameters
 */
extern void soc_sbx_g3p1_bfd_ld2edatac_print(int unit, soc_sbx_g3p1_bfd_ld2edatac_t *e);

/**
 * Print sample6 entry.
 *
 * @param[in]  unit chip unit number
 * @param[in]  e entry parameters
 */
extern void soc_sbx_g3p1_sample6_print(int unit, soc_sbx_g3p1_sample6_t *e);

/**
 * Print sample8 entry.
 *
 * @param[in]  unit chip unit number
 * @param[in]  e entry parameters
 */
extern void soc_sbx_g3p1_sample8_print(int unit, soc_sbx_g3p1_sample8_t *e);

/**
 * Print sample9 entry.
 *
 * @param[in]  unit chip unit number
 * @param[in]  e entry parameters
 */
extern void soc_sbx_g3p1_sample9_print(int unit, soc_sbx_g3p1_sample9_t *e);




/*
 * Diag shell print & set drivers
 */

/**
 * Diagnostic shell print.
 *
 * This function drives printing the state of microcode objects
 * (constants, globals, entries, memories and the memory map) based
 * on the supplied command line arguments.
 *
 * @param[in]  unit chip unit number
 * @param[in]  argc number of argument strings
 * @param[in]  argv pointer to array of argument strings
 */
extern int soc_sbx_g3p1_shell_print(int unit, int argc, char **argv);

/**
 * Diagnostic shell set.
 *
 * This function drives setting the state of microcode objects
 * (globals, entries, and memories) based
 * on the supplied command line arguments.
 *
 * @param[in]  unit chip unit number
 * @param[in]  argc number of argument strings
 * @param[in]  argv pointer to array of argument strings
 */
extern int soc_sbx_g3p1_shell_set(int unit, int argc, char **argv);

/**
 * Diagnostic shell delete.
 *
 * This function drives deleting microcode entries that support a 
 * delete operation based on the supplied command line arguments.
 *
 * @param[in]  unit chip unit number
 * @param[in]  argc number of argument strings
 * @param[in]  argv pointer to array of argument strings
 */
extern int soc_sbx_g3p1_shell_delete(int unit, int argc, char **argv);

/**
 * Diagnostic shell global print.
 *
 * This function drives printing the state of microcode global objects
 * based on the supplied command line arguments.
 *
 * @param[in]  unit chip unit number
 * @param[in]  argc number of argument strings
 * @param[in]  argv pointer to array of argument strings
 */
extern int soc_sbx_g3p1_shell_print_globals(int unit, int argc, char **argv);

/**
 * Diagnostic shell global set.
 *
 * This function drives setting the state of microcode global objects
 * based on the supplied command line arguments.
 *
 * @param[in]  unit chip unit number
 * @param[in]  argc number of argument strings
 * @param[in]  argv pointer to array of argument strings
 */
extern int soc_sbx_g3p1_shell_set_globals(int unit, int argc, char **argv);

/**
 * Diagnostic shell memory print.
 *
 * This function drives printing the state of microcode 
 * memories based on the supplied command line arguments.
 *
 * @param[in]  unit chip unit number
 * @param[in]  argc number of argument strings
 * @param[in]  argv pointer to array of argument strings
 */
extern int soc_sbx_g3p1_shell_print_memories(int unit, int argc, char **argv);

/**
 * Diagnostic shell memory set.
 *
 * This function drives setting the state of microcode memories 
 * based on the supplied command line arguments.
 *
 * @param[in]  unit chip unit number
 * @param[in]  argc number of argument strings
 * @param[in]  argv pointer to array of argument strings
 */
extern int soc_sbx_g3p1_shell_set_memories(int unit, int argc, char **argv);

/**
 * Diagnostic shell constant print.
 *
 * This function drives printing the state of microcode constant objects
 *
 * @param[in]  unit chip unit number
 * @param[in]  argc number of argument strings
 * @param[in]  argv pointer to array of argument strings
 */
extern int soc_sbx_g3p1_shell_print_constants(int unit, int argc, char **argv);


/*
 * Diag shell usage messages
 */

/** Diagnostic shell set operation usage message */
extern char soc_sbx_g3p1_set_usage[];
/** Diagnostic shell print operation usage message */
extern char soc_sbx_g3p1_get_usage[];
/** Diagnostic shell delete operation usage message */
extern char soc_sbx_g3p1_delete_usage[];
/** Diagnostic shell constant operation usage message */
extern char soc_sbx_g3p1_constant_usage[];
/** Diagnostic shell global set operation usage message */
extern char soc_sbx_g3p1_global_set_usage[];
/** Diagnostic shell global get operation usage message */
extern char soc_sbx_g3p1_global_get_usage[];
/** Diagnostic shell mem set operation usage message */
extern char soc_sbx_g3p1_mem_get_usage[];
/** Diagnostic shell mem get operation usage message */
extern char soc_sbx_g3p1_mem_set_usage[];

#endif
#endif
