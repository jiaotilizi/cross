
/*
 * $Id: rce_c.stg,v 1.8 Broadcom SDK $
 * $Copyright: (c) 2016 Broadcom.
 * Broadcom Proprietary and Confidential. All rights reserved.$
 *
 * t3p1_rce.c: Guadalupe2k V1.3 RCE
 *
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated from sdk/caladan_ucode/t3p1/src/t3p1_rce_cfg.lrp.
 * Edits to this file will be lost when it is regenerated.
 *
 */

#if defined(BCM_CALADAN3_SUPPORT) && defined(BCM_CALADAN3_T3P1_SUPPORT) 
#include <sal/types.h>
#include <sal/core/sync.h>
#include <sal/core/time.h>
#include <sal/core/thread.h>
#include <soc/sbx/caladan3/ocm.h>
#include <soc/sbx/caladan3/rce.h>
#include <soc/sbx/caladan3/rce_int.h>
#include <soc/sbx/t3p1/t3p1_defs.h>
#include <soc/sbx/t3p1/t3p1_cmu.h>

/*
 *  This provides an example, based upon the contents of the file
 *  $SDK/caladan_ucode/t3p1/doc/g3p1_rce.txt, of how the rce code expects the
 *  descriptions to be laid out.
 *
 *  In the long term, this file should be eliminated, and replaced by some
 *  structures generated and included in the LRP microcode package, so the RCE
 *  implementation can see what it has available for a given LRP microcode and
 *  act upon this.
 */

/*
 *  This specifies a program that is unused.
 */
#define _C3_RCE_PROGRAM_TABLE_UNUSED_ENTRY \
    { /* program unused */ \
        NULL                                /* program name */, \
        0                                   /* program flags */, \
        0                                   /* TMU keys bitmap */, \
        NULL                                /* key qualifier descriptions */, \
        { \
            NULL                            /* result register 0 actions */, \
            NULL                            /* result register 1 actions */, \
            NULL                            /* result register 2 actions */, \
            NULL                            /* result register 3 actions */ \
        }, \
    } \

/*
 *  This is a list of fields that the LRP microcode supports (basically, what
 *  the LRP microcode puts into the key). It will be available to SOC callers
 *  (such as the BCM layer) so they can choose what bits they want to use for
 *  various qualifiers.  Note this does not specify the qualification type --
 *  that is up to the caller.   The RCE driver does not make direct use of this
 *  table; it is informational and intended for the RCE driver's user.
 *
 *  Each qualifier is described in terms of which header and which bits.  From
 *  the frame side, the specified bit is MSb of the field (with bit 0 of a byte
 *  being the least significant bit of that byte), and the length is the number
 *  of bits spanned to the right for the field.  Note that this assumes the
 *  bytes are lined up so the byte number increases from left to right, with
 *  the bits lined up within bytes so the most significant bits are on the
 *  left, and that the span is contiguous even if the numbering is not.
 *
 *  Each qualifier also specifies where it is in the key.  In this case, the
 *  specified bit is the LSb of the field and the length is the number of
 *  contiguous bits to the left that are spanned.  In this context, bytes are
 *  lined up so their numbers increase from right to left (bits are still lined
 *  up so most significant bit of a byte is on the left and least significant
 *  bit is on the right). If there is more than one key field specified for a
 *  qualifier, the least significant one is specified first, then the next more
 *  significant one, and so on.
 *
 *  Note these are in 'contiguous blocks' of bits -- more than one 'standard'
 *  qualifier field may exist in any given one of these.  For example, the
 *  default configuration has TCP/UDP source and dest ports together in the
 *  key, and since they are together in the frame, they are noted as a single
 *  contiguous field here.  The application can decide how it wants to do
 *  comparisons, and divide the fields as it sees fit.
 */

   
/* rce_program_qualifier_list_template */
/*
 * ingressProgram Qualifier list
 */ 
const soc_c3_rce_qual_uc_desc_t _soc_t3p1_rce_ingressProgram_qualifiers[] = {
    {
       { socC3RceDataHeaderEther,     SOC_C3_RCE_FRAME_BIT( 0, 7),  48 },
       { 
         { SOC_C3_RCE_KEY_BIT( 0, 0),  48 },
         { SOC_C3_RCE_NO_BITS }
       } 
    },    {
       { socC3RceDataHeaderVlan,     SOC_C3_RCE_FRAME_BIT( 2, 7),  16 },
       { 
         { SOC_C3_RCE_KEY_BIT( 6, 0),  16 },
         { SOC_C3_RCE_NO_BITS }
       } 
    },    {
       { socC3RceDataHeaderEther,     SOC_C3_RCE_FRAME_BIT( 6, 7),  48 },
       { 
         { SOC_C3_RCE_KEY_BIT( 8, 0),  48 },
         { SOC_C3_RCE_NO_BITS }
       } 
    },    {
       { socC3RceDataHeaderEther,     SOC_C3_RCE_FRAME_BIT( 12, 7),  16 },
       { 
         { SOC_C3_RCE_KEY_BIT( 14, 0),  16 },
         { SOC_C3_RCE_NO_BITS }
       } 
    },    {
       { socC3RceDataHeaderIpv4,     SOC_C3_RCE_FRAME_BIT( 16, 7),  32 },
       { 
         { SOC_C3_RCE_KEY_BIT( 16, 0),  32 },
         { SOC_C3_RCE_NO_BITS }
       } 
    },    {
       { socC3RceDataHeaderIpv4,     SOC_C3_RCE_FRAME_BIT( 12, 7),  32 },
       { 
         { SOC_C3_RCE_KEY_BIT( 20, 0),  32 },
         { SOC_C3_RCE_NO_BITS }
       } 
    },    {
       { socC3RceDataHeaderIpv4,     SOC_C3_RCE_FRAME_BIT( 9, 7),  8 },
       { 
         { SOC_C3_RCE_KEY_BIT( 28, 0),  8 },
         { SOC_C3_RCE_NO_BITS }
       } 
    },    {
       { socC3RceDataHeaderIpv4,     SOC_C3_RCE_FRAME_BIT( 1, 7),  8 },
       { 
         { SOC_C3_RCE_KEY_BIT( 29, 0),  8 },
         { SOC_C3_RCE_NO_BITS }
       } 
    },    {
       { socC3RceDataHeaderIpv6,     SOC_C3_RCE_FRAME_BIT( 24, 7),  128 },
       { 
         { SOC_C3_RCE_KEY_BIT( 32, 0),  96 },
         { SOC_C3_RCE_KEY_BIT( 16, 0),  32 },
       } 
    },    {
       { socC3RceDataHeaderIpv6,     SOC_C3_RCE_FRAME_BIT( 8, 7),  128 },
       { 
         { SOC_C3_RCE_KEY_BIT( 44, 0),  96 },
         { SOC_C3_RCE_KEY_BIT( 20, 0),  32 },
       } 
    },    {
       { socC3RceDataHeaderIpv6,     SOC_C3_RCE_FRAME_BIT( 6, 7),  8 },
       { 
         { SOC_C3_RCE_KEY_BIT( 28, 0),  8 },
         { SOC_C3_RCE_NO_BITS }
       } 
    },    {
       { socC3RceDataHeaderIpv6,     SOC_C3_RCE_FRAME_BIT( 0, 3),  8 },
       { 
         { SOC_C3_RCE_KEY_BIT( 29, 0),  8 },
         { SOC_C3_RCE_NO_BITS }
       } 
    },    {
       { socC3RceDataHeaderTcpUdp,     SOC_C3_RCE_FRAME_BIT( 0, 7),  32 },
       { 
         { SOC_C3_RCE_KEY_BIT( 24, 0),  32 },
         { SOC_C3_RCE_NO_BITS }
       } 
    },    {
       { socC3RceDataHeaderTcpUdp,     SOC_C3_RCE_FRAME_BIT( 13, 5),  6 },
       { 
         { SOC_C3_RCE_KEY_BIT( 30, 0),  6 },
         { SOC_C3_RCE_NO_BITS }
       } 
    },    {
       { socC3RceDataMetadata,     SOC_C3_RCE_FRAME_BIT( 0, 0),  7 },
       { 
         { SOC_C3_RCE_KEY_BIT( 31, 0),  7 },
         { SOC_C3_RCE_NO_BITS }
       } 
    },
    { /* Last */
      { socC3RceDataOffsetCount, 0, 0 },
      {{ SOC_C3_RCE_NO_BITS }, { SOC_C3_RCE_NO_BITS }}
    }
};


/*
 * irt Action list
 */ 
const soc_c3_rce_action_uc_desc_t _soc_t3p1_rce_irt_actions[] = {
  {socC3RceActionNewVsi, "vlan", 3, 0, { {0, 20} } }, /* rce_program_action_list_entry_template */
  {socC3RceActionNewFtIndex, "ftidx", 4, 0, { {0, 20} } }, /* rce_program_action_list_entry_template */
  {socC3RceActionMirror, "mirror", ~0, 0, { {20, 2} } }, /* rce_program_action_list_entry_template */
  {socC3RceActionEnable, "usevlan", ~0, 8, { {22, 1} } }, /* rce_program_action_list_entry_template */
  {socC3RceActionEnable, "useftidx", ~0, 0, { {23, 1} } }, /* rce_program_action_list_entry_template */
  {socC3RceActionCopyToCpu, "copy", ~0, 0, { {24, 1} } }, /* rce_program_action_list_entry_template */
  {socC3RceActionNewDp, "dp", 8, 0, { {32, 2} } }, /* rce_program_action_list_entry_template */
  {socC3RceActionNewPrio, "coses", 9, 0, { {34, 4} } }, /* rce_program_action_list_entry_template */
  {socC3RceActionEnable, "usedp", ~0, 0, { {38, 1} } }, /* rce_program_action_list_entry_template */
  {socC3RceActionEnable, "usecos", ~0, 0, { {39, 1} } }, /* rce_program_action_list_entry_template */
  {socC3RceActionPolicer, "policer", 11, 0, { {40, 15} } }, /* rce_program_action_list_entry_template */
  {socC3RceActionEnable, "policer_enable", ~0, 0, { {55, 3} } }, /* rce_program_action_list_entry_template */
  {socC3RceActionCount, NULL, ~0, ~0, {{0, 0 }} }
};


/*
 * Actions tables
 */
 const _soc_c3_rce_actions_uc_desc_t _soc_t3p1_rce_actions_irt = {
         "irt",                               /* action table name */
         &(_soc_t3p1_rce_irt_actions[0]),    /* action fields descriptions */
         16384 /* action slots */,
         1 /* number of OCM segments */,
         {
         {
            "irt", /* Segment name */
            SOC_SBX_CALADAN3_OCM_LRP3_PORT /* OCM port */,
            1 /* OCM segment */,
            64 /* bits per action slot */,
            3 /* byte order mask */,
            1 /* actions per OCM element */,
            1 /* OCM elements per action */,
         }
         },
          "rtctr"                                 /* counter segment name */,
         (_soc_c3_rce_counter_clear_f)soc_sbx_t3p1_rtctr_clear, /* clear counters */
         (_soc_c3_rce_counter_read_f)soc_sbx_t3p1_rtctr_read,   /* read counters */
     };
/*
 *  This describes each program, including flags (enable, &c) and includes
 *  pointers to the key description and the action description for each.
 */
const _soc_c3_rce_program_uc_desc_t
_soc_t3p1_rce_programs_data[SOC_C3_RCE_PROGRAM_COUNT] = {

    { /* program: ingressProgram */
    	"ingressProgram",                           /* program name */
        _SOC_C3_RCE_PROGRAM_ENABLE,
        128                     /* LRP key IDs for this program */,
        &(_soc_t3p1_rce_ingressProgram_qualifiers[0]) /* key fields description */,
        {
          NULL,
          NULL,
          NULL,
          &_soc_t3p1_rce_actions_irt
        },
    },
  _C3_RCE_PROGRAM_TABLE_UNUSED_ENTRY,
  _C3_RCE_PROGRAM_TABLE_UNUSED_ENTRY,
  _C3_RCE_PROGRAM_TABLE_UNUSED_ENTRY,
  _C3_RCE_PROGRAM_TABLE_UNUSED_ENTRY,
  _C3_RCE_PROGRAM_TABLE_UNUSED_ENTRY,
  _C3_RCE_PROGRAM_TABLE_UNUSED_ENTRY,
  _C3_RCE_PROGRAM_TABLE_UNUSED_ENTRY,
  _C3_RCE_PROGRAM_TABLE_UNUSED_ENTRY,
  _C3_RCE_PROGRAM_TABLE_UNUSED_ENTRY,
  _C3_RCE_PROGRAM_TABLE_UNUSED_ENTRY,
  _C3_RCE_PROGRAM_TABLE_UNUSED_ENTRY,
  _C3_RCE_PROGRAM_TABLE_UNUSED_ENTRY,
  _C3_RCE_PROGRAM_TABLE_UNUSED_ENTRY,
  _C3_RCE_PROGRAM_TABLE_UNUSED_ENTRY,
  _C3_RCE_PROGRAM_TABLE_UNUSED_ENTRY
};


#endif
