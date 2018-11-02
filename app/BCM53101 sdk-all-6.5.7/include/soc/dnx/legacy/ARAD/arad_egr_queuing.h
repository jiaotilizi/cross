/* $Id: jer2_arad_egr_queuing.h,v 1.19 Broadcom SDK $
 * $Copyright: (c) 2016 Broadcom.
 * Broadcom Proprietary and Confidential. All rights reserved.$
*/


#ifndef __JER2_ARAD_EGR_QUEUING_INCLUDED__
/* { */
#define __JER2_ARAD_EGR_QUEUING_INCLUDED__

/*************
 * INCLUDES  *
 *************/
/* { */
#include <soc/dnx/legacy/SAND/Utils/sand_header.h>
#include <soc/dnx/legacy/ARAD/arad_api_egr_queuing.h>
#include <soc/dnx/legacy/ARAD/arad_api_general.h>
/* } */
/*************
 * DEFINES   *
 *************/
/* { */
#define JER2_ARAD_EGR_NOF_Q_PAIRS                                     (256)
#define JER2_ARAD_EGR_NOF_BASE_Q_PAIRS                                (256)
#define JER2_ARAD_EGR_NOF_Q_PAIRS_IN_PS                               (8)
#define JER2_ARAD_EGR_NOF_PS                                          (JER2_ARAD_EGR_NOF_BASE_Q_PAIRS / JER2_ARAD_EGR_NOF_Q_PAIRS_IN_PS)
#define JER2_ARAD_EGR_NOF_TCG_IDS                                     (JER2_ARAD_EGR_NOF_PS*JER2_ARAD_NOF_TCGS)
#define JER2_ARAD_NOF_TCGS_IN_PS                                      (8)

#define JER2_ARAD_EGR_BASE_Q_PAIRS_NDX_MAX                            (JER2_ARAD_EGR_NOF_BASE_Q_PAIRS-1)
#define JER2_ARAD_EGR_INVALID_BASE_Q_PAIR                             (JER2_ARAD_EGR_BASE_Q_PAIRS_NDX_MAX)

#define JER2_ARAD_EGQ_THRESHOLD_PD_NOF_BITS                           (15)
#define JER2_ARAD_EGQ_THRESHOLD_DBUFF_NOF_BITS                        (14)

#define JER2_ARAD_EGR_Q_PRIORITY_TC_MAX                               (7)
#define JER2_ARAD_EGR_Q_PRIORITY_DP_MAX                               (3)

#define JER2_ARAD_EGQ_PD_INTERFACE_NOF_BITS                           (15)
#define JER2_ARAD_EGQ_SIZE_256_INTERFACE_NOF_BITS                     (14)


#define JER2_ARAD_EGR_QUEUING_MC_QUEUE_OFFSET(q_pair) \
    (q_pair + 16)

#define JER2_ARAD_EGQ_QDCT_TABLE_KEY_ENTRY(profile,egress_tc) \
  ((profile << 3) + egress_tc)

#define JER2_ARAD_EGR_SGMII_RATE                                      (1)

/* Give BW to other interfaces only if they need it */
#define JER2_ARAD_EGQ_NIF_PORT_CAL_BW_GIVE_UPON_REQUEST (125)
/* port rates */
#define JER2_ARAD_EGR_MAX_CAL_SIZE                                 (128)
#define JER2_ARAD_EGR_MAX_ENTRY_INDX                               (127)

#define JER2_ARAD_EGR_MAXIMAL_NUMBER_OF_MUX_COMPETITORS            (JER2_ARAD_NIF_NOF_NIFS)
#define JER2_ARAD_EGR_OTHERS_INDX                                  (28)

/* Indicates invalid entry */
#define JER2_ARAD_EGQ_NIF_PORT_CAL_BW_INVALID          127


/*FQP - max rate for higher rquest bandwidth*/
#define JER2_ARAD_EGR_QUEUEING_HIGER_REQ_MAX_RATE_MBPS 100000


/*************
 * MACROS    *
 *************/
/* { */
/* Base q-pair for the ERP is fixed. The 31th PS */
#define JER2_ARAD_EGQ_ERP_BASE_Q_PAIR (31*8)
/* } */

/*************
 * TYPE DEFS *
 *************/
/* { */

/* } */

/*************
 * GLOBALS   *
 *************/
/* { */

/* } */

/*************
 * FUNCTIONS *
 *************/
/* { */

/*********************************************************************
* NAME:
*     jer2_arad_egr_queuing_init
* FUNCTION:
*     Initialization of the Arad blocks configured in this module.
* INPUT:
*  DNX_SAND_IN  int                 unit -
*     Identifier of the device to access.
* RETURNS:
*   OK or ERROR indication.
* REMARKS:
*   Called as part of the initialization sequence.
*********************************************************************/
int
  jer2_arad_egr_queuing_init(
    DNX_SAND_IN  int                 unit,
    DNX_SAND_IN  JER2_ARAD_EGR_QUEUING_PARTITION_SCHEME  scheme
  );

/* Mapping from Queue-pair to OTM-Port and TC */
uint32
  jer2_arad_egr_queuing_q_pair_port_tc_find(
    DNX_SAND_IN  int                      unit,
    DNX_SAND_IN  uint32						q_pair,
    DNX_SAND_OUT uint8		                *found,
    DNX_SAND_OUT JER2_ARAD_FAP_PORT_ID               *ofp_idx,
    DNX_SAND_OUT uint32				      	*tc
  );


/*********************************************************************
* NAME:
*     jer2_arad_egr_ofp_thresh_type_set_unsafe
* TYPE:
*   PROC
* DATE:
*   Dec 20 2007
* FUNCTION:
*     Sets Outgoing FAP Port (OFP) threshold type, per port.
* INPUT:
*  DNX_SAND_IN  int                 unit -
*     Identifier of the device to access.
*  DNX_SAND_IN  JER2_ARAD_FAP_PORT_ID         ofp_ndx -
*     OFP index. Range: 0 - JER2_ARAD_FAP_PORT_ID_MAX
*  DNX_SAND_IN  JER2_ARAD_EGR_PORT_THRESH_TYPE ofp_thresh_type -
*     The threshold type to set. Port-level Drop thresholds
*     and Flow control thresholds will be set per threshold
*     type.
* REMARKS:
*     None.
* RETURNS:
*     OK or ERROR indication.
*********************************************************************/
uint32
  jer2_arad_egr_ofp_thresh_type_set_unsafe(
    DNX_SAND_IN  int                 unit,
    DNX_SAND_IN  int                 core,
    DNX_SAND_IN  JER2_ARAD_FAP_PORT_ID    ofp_ndx,
    DNX_SAND_IN  JER2_ARAD_EGR_PORT_THRESH_TYPE ofp_thresh_type
  );

/*********************************************************************
* NAME:
*     jer2_arad_egr_ofp_thresh_type_verify
* TYPE:
*   PROC
* DATE:
*   Apr 21 2008
* FUNCTION:
*     Sets Outgoing FAP Port (OFP) threshold type, per port.
* INPUT:
*  DNX_SAND_IN  int                 unit -
*     Identifier of the device to access.
*  DNX_SAND_IN  JER2_ARAD_FAP_PORT_ID         ofp_ndx -
*     OFP index. Range: 0 - JER2_ARAD_FAP_PORT_ID_MAX
*  DNX_SAND_IN  JER2_ARAD_EGR_PORT_THRESH_TYPE ofp_thresh_type -
*     The threshold type to set. Port-level Drop thresholds
*     and Flow control thresholds will be set per threshold
*     type.
* REMARKS:
*     None.
* RETURNS:
*     OK or ERROR indication.
*********************************************************************/
uint32
  jer2_arad_egr_ofp_thresh_type_verify(
    DNX_SAND_IN  int                 unit,
    DNX_SAND_IN  JER2_ARAD_FAP_PORT_ID         ofp_ndx,
    DNX_SAND_IN  JER2_ARAD_EGR_PORT_THRESH_TYPE ofp_thresh_type
  );

/*********************************************************************
* NAME:
*     jer2_arad_egr_ofp_thresh_type_get_unsafe
* TYPE:
*   PROC
* DATE:
*   Dec 20 2007
* FUNCTION:
*   See jer2_arad_egr_ofp_thresh_type_set_unsafe
* INPUT:
*  DNX_SAND_IN  int                 unit -
*     Identifier of the device to access.
*  DNX_SAND_IN  JER2_ARAD_FAP_PORT_ID         ofp_ndx -
*     OFP index. Range: 0 - JER2_ARAD_FAP_PORT_ID_MAX
*  DNX_SAND_OUT JER2_ARAD_EGR_PORT_THRESH_TYPE *ofp_thresh_type -
*     The threshold type to set. Port-level Drop thresholds
*     and Flow control thresholds will be set per threshold
*     type.
* REMARKS:
*     None.
* RETURNS:
*     OK or ERROR indication.
*********************************************************************/
uint32
  jer2_arad_egr_ofp_thresh_type_get_unsafe(
    DNX_SAND_IN  int                 unit,
    DNX_SAND_IN  int                 core_id,
    DNX_SAND_IN  JER2_ARAD_FAP_PORT_ID         ofp_ndx,
    DNX_SAND_OUT JER2_ARAD_EGR_PORT_THRESH_TYPE *ofp_thresh_type
  );

/*********************************************************************
* NAME:
*     jer2_arad_egr_sched_drop_set_unsafe
* TYPE:
*   PROC
* DATE:
*   Apr 21 2008
* FUNCTION:
*     Set scheduled drop thresholds for egress queues per
*     queue-priority.
* INPUT:
*  DNX_SAND_IN  int                 unit -
*     Identifier of the device to access.
*  DNX_SAND_IN  JER2_ARAD_EGR_Q_PRIO          prio_ndx -
*     Queue priority index. Range: JER2_ARAD_EGR_Q_PRIO_LOW -
*     JER2_ARAD_EGR_Q_PRIO_HIGH.
*  DNX_SAND_IN  JER2_ARAD_EGR_DROP_THRESH     *thresh -
*     drop thresholds to set.
*  DNX_SAND_OUT JER2_ARAD_EGR_DROP_THRESH     *exact_thresh -
*     will be filled with exact values.
* REMARKS:
*     None.
* RETURNS:
*     OK or ERROR indication.
*********************************************************************/
uint32
  jer2_arad_egr_sched_drop_set_unsafe(
    DNX_SAND_IN  int                 unit,
    DNX_SAND_IN  int                 core,
    DNX_SAND_IN  int                 profile,
    DNX_SAND_IN  JER2_ARAD_EGR_Q_PRIO          prio_ndx,
    DNX_SAND_IN  JER2_ARAD_EGR_DROP_THRESH     *thresh,
    DNX_SAND_OUT JER2_ARAD_EGR_DROP_THRESH     *exact_thresh
  );

/*********************************************************************
* NAME:
*     jer2_arad_egr_sched_drop_verify
* TYPE:
*   PROC
* DATE:
*   Apr 21 2008
* FUNCTION:
*     Set scheduled drop thresholds for egress queues per
*     queue-priority.
* INPUT:
*  DNX_SAND_IN  int                 unit -
*     Identifier of the device to access.
*  DNX_SAND_IN  JER2_ARAD_EGR_Q_PRIO          prio_ndx -
*     Queue priority index. Range: JER2_ARAD_EGR_Q_PRIO_LOW -
*     JER2_ARAD_EGR_Q_PRIO_HIGH.
*  DNX_SAND_IN  JER2_ARAD_EGR_DROP_THRESH     *thresh -
*     drop thresholds to set.
* REMARKS:
*     None.
* RETURNS:
*     OK or ERROR indication.
*********************************************************************/
uint32
  jer2_arad_egr_sched_drop_verify(
    DNX_SAND_IN  int                 unit,
    DNX_SAND_IN  JER2_ARAD_EGR_Q_PRIO          prio_ndx,
    DNX_SAND_IN  JER2_ARAD_EGR_DROP_THRESH     *thresh
  );


/*********************************************************************
* NAME:
*     jer2_arad_egr_q_nif_cal_set_unsafe
* TYPE:
*   PROC
* DATE:
* FUNCTION:
*         Set the calender of the nif port "processing time" i.e every 2 clk there
*         is a context switch and different nif get "service" or others which include
          delete and recycling.
* INPUT:
*         DNX_SAND_IN int unit
*
* REMARKS:
*         This function consist of four steps:
*         1. Classifying the nif, mal configuration
*         2. Giving each nif  weight according to its type
*         3. Adding the "others" processes of recycling, deleting as competitor with a given value
*         4. Computing the optimal calender using "black box" soc_pb_ofp_rates_from_rates_to_calendar function
*         5. Using the values computed in 4. to initialize JER2_ARAD_EGQ_FQP_NIF_PORT_MUX_TBL address:
*
*         The calender should admit the constraint derived from the formula BW=(128 * 8)/(ClkFreq * # Clk )
*         => # Clk = (128 * 8)/(ClkFreq * BW) Given that the clock frequency is 3.3 Ns
*         WE get #Clk= (128 * 8) /(3.3 * BW)
*
* RETURNS:
*     OK or ERROR indication.
*********************************************************************/
int
  jer2_arad_egr_q_nif_cal_set_unsafe(
    DNX_SAND_IN int unit
  );

/*********************************************************************
* NAME:
*     jer2_arad_egr_sched_drop_get_unsafe
* TYPE:
*   PROC
* DATE:
*   Apr 21 2008
* FUNCTION:
*     Set scheduled drop thresholds for egress queues per
*     queue-priority.
* INPUT:
*  DNX_SAND_IN  int                 unit -
*     Identifier of the device to access.
*  DNX_SAND_IN  JER2_ARAD_EGR_Q_PRIO          prio_ndx -
*     Queue priority index. Range: JER2_ARAD_EGR_Q_PRIO_LOW -
*     JER2_ARAD_EGR_Q_PRIO_HIGH.
*  DNX_SAND_OUT JER2_ARAD_EGR_DROP_THRESH     *thresh -
*     drop thresholds to set.
* REMARKS:
*     None.
* RETURNS:
*     OK or ERROR indication.
*********************************************************************/
uint32
  jer2_arad_egr_sched_drop_get_unsafe(
    DNX_SAND_IN  int                 unit,
    DNX_SAND_IN  JER2_ARAD_EGR_Q_PRIO          prio_ndx,
    DNX_SAND_OUT JER2_ARAD_EGR_DROP_THRESH     *thresh
  );

/*********************************************************************
* NAME:
*     jer2_arad_egr_unsched_drop_set_unsafe
* TYPE:
*   PROC
* DATE:
*   Apr 21 2008
* FUNCTION:
*     Set unscheduled drop thresholds for egress queues, per
*     queue-priority and drop precedence.
* INPUT:
*  DNX_SAND_IN  int                 unit -
*     Identifier of the device to access.
*  DNX_SAND_IN  JER2_ARAD_EGR_Q_PRIO          prio_ndx -
*     Queue priority index. Range: JER2_ARAD_EGR_Q_PRIO_LOW -
*     JER2_ARAD_EGR_Q_PRIO_HIGH.
*  DNX_SAND_IN  uint32                 dp_ndx -
*     Drop precedence index. Range: 0 - JER2_ARAD_NOF_DP-1.
*  DNX_SAND_IN  JER2_ARAD_EGR_DROP_THRESH     *thresh -
*     drop thresholds to set.
*  DNX_SAND_OUT JER2_ARAD_EGR_DROP_THRESH     *exact_thresh -
*     Will be filled with exact values.
* REMARKS:
*     The unscheduled traffic is assigned to the matching threshold
*     not according to the packet Drop Precedence, rather then
*     according to the Unscheduled Drop Priority value, as set
*     by the 'jer2_arad_egr_unsched_drop_prio_set' API, per TC and DP
*     The "dp_ndx" in this API refers to this Drop Priority, and not
*     directly to the packet Drop Precedence field
* RETURNS:
*     OK or ERROR indication.
*********************************************************************/
uint32
  jer2_arad_egr_unsched_drop_set_unsafe(
    DNX_SAND_IN  int                 unit,
    DNX_SAND_IN  int                 core,
    DNX_SAND_IN  int                 profile,
    DNX_SAND_IN  JER2_ARAD_EGR_Q_PRIO          prio_ndx,
    DNX_SAND_IN  uint32                 dp_ndx,
    DNX_SAND_IN  JER2_ARAD_EGR_DROP_THRESH     *thresh,
    DNX_SAND_OUT JER2_ARAD_EGR_DROP_THRESH     *exact_thresh
  );

uint32
  jer2_arad_egr_sched_port_fc_thresh_set_unsafe(
    DNX_SAND_IN  int                unit,
    DNX_SAND_IN  int                core,
    DNX_SAND_IN  int                threshold_type,
    DNX_SAND_IN  DNX_TMC_EGR_FC_OFP_THRESH *thresh
  );

/*********************************************************************
* NAME:
*     jer2_arad_egr_unsched_drop_verify
* TYPE:
*   PROC
* DATE:
*   Apr 21 2008
* FUNCTION:
*     Set unscheduled drop thresholds for egress queues, per
*     queue-priority and drop precedence.
* INPUT:
*  DNX_SAND_IN  int                 unit -
*     Identifier of the device to access.
*  DNX_SAND_IN  JER2_ARAD_EGR_Q_PRIO          prio_ndx -
*     Queue priority index. Range: JER2_ARAD_EGR_Q_PRIO_LOW -
*     JER2_ARAD_EGR_Q_PRIO_HIGH.
*  DNX_SAND_IN  uint32                 dp_ndx -
*     Drop precedence index. Range: 0 - JER2_ARAD_NOF_DP-1.
*  DNX_SAND_IN  JER2_ARAD_EGR_DROP_THRESH     *thresh -
*     drop thresholds to set.
* REMARKS:
*     The unscheduled traffic is assigned to the matching threshold
*     not according to the packet Drop Precedence, rather then
*     according to the Unscheduled Drop Priority value, as set
*     by the 'jer2_arad_egr_unsched_drop_prio_set' API, per TC and DP
*     The "dp_ndx" in this API refers to this Drop Priority, and not
*     directly to the packet Drop Precedence field
* RETURNS:
*     OK or ERROR indication.
*********************************************************************/
uint32
  jer2_arad_egr_unsched_drop_verify(
    DNX_SAND_IN  int                 unit,
    DNX_SAND_IN  JER2_ARAD_EGR_Q_PRIO          prio_ndx,
    DNX_SAND_IN  uint32                 dp_ndx,
    DNX_SAND_IN  JER2_ARAD_EGR_DROP_THRESH     *thresh
  );

/*********************************************************************
* NAME:
*     jer2_arad_egr_unsched_drop_get_unsafe
* TYPE:
*   PROC
* DATE:
*   Apr 21 2008
* FUNCTION:
*     Set unscheduled drop thresholds for egress queues, per
*     queue-priority and drop precedence.
* INPUT:
*  DNX_SAND_IN  int                 unit -
*     Identifier of the device to access.
*  DNX_SAND_IN  JER2_ARAD_EGR_Q_PRIO          prio_ndx -
*     Queue priority index. Range: JER2_ARAD_EGR_Q_PRIO_LOW -
*     JER2_ARAD_EGR_Q_PRIO_HIGH.
*  DNX_SAND_IN  uint32                 dp_ndx -
*     Drop precedence index. Range: 0 - JER2_ARAD_NOF_DP-1.
*  DNX_SAND_OUT JER2_ARAD_EGR_DROP_THRESH     *thresh -
*     drop thresholds to set.
* REMARKS:
*     The unscheduled traffic is assigned to the matching threshold
*     not according to the packet Drop Precedence, rather then
*     according to the Unscheduled Drop Priority value, as set
*     by the 'jer2_arad_egr_unsched_drop_prio_set' API, per TC and DP
*     The "dp_ndx" in this API refers to this Drop Priority, and not
*     directly to the packet Drop Precedence field
* RETURNS:
*     OK or ERROR indication.
*********************************************************************/
uint32
  jer2_arad_egr_unsched_drop_get_unsafe(
    DNX_SAND_IN  int                 unit,
    DNX_SAND_IN  JER2_ARAD_EGR_Q_PRIO          prio_ndx,
    DNX_SAND_IN  uint32                 dp_ndx,
    DNX_SAND_OUT JER2_ARAD_EGR_DROP_THRESH     *thresh
  );

/*********************************************************************
* NAME:
*     jer2_arad_egr_dev_fc_set_unsafe
* TYPE:
*   PROC
* DATE:
*   Apr 21 2008
* FUNCTION:
*     Set Flow Control thresholds for egress queues, based on
*     device-level resources. Threshold are set for overall
*     resources, and scheduled resources.
* INPUT:
*  DNX_SAND_IN  int                 unit -
*     Identifier of the device to access.
*  DNX_SAND_IN  JER2_ARAD_EGR_FC_DEVICE_THRESH *thresh -
*     Flow Control thresholds to set - Device-level resources.
*  DNX_SAND_OUT JER2_ARAD_EGR_FC_DEVICE_THRESH *exact_thresh -
*     Will be filled with exact values.
* REMARKS:
*     None.
* RETURNS:
*     OK or ERROR indication.
*********************************************************************/
uint32
  jer2_arad_egr_dev_fc_set_unsafe(
    DNX_SAND_IN  int                 unit,
    DNX_SAND_IN  int                 core,
    DNX_SAND_IN  JER2_ARAD_EGR_FC_DEVICE_THRESH *thresh,
    DNX_SAND_OUT JER2_ARAD_EGR_FC_DEVICE_THRESH *exact_thresh
  );

/*********************************************************************
* NAME:
*     jer2_arad_egr_dev_fc_verify
* TYPE:
*   PROC
* DATE:
*   Dec 20 2007
* FUNCTION:
*     Set Flow Control thresholds for egress queues, based on
*     device-level resources. Threshold are set for overall
*     resources, and scheduled resources.
* INPUT:
*  DNX_SAND_IN  int                 unit -
*     Identifier of the device to access.
*  DNX_SAND_IN  JER2_ARAD_EGR_FC_DEVICE_THRESH *thresh -
*     Flow Control thresholds to set - Device-level resources.
* REMARKS:
*     None.
* RETURNS:
*     OK or ERROR indication.
*********************************************************************/
uint32
  jer2_arad_egr_dev_fc_verify(
    DNX_SAND_IN  int                 unit,
    DNX_SAND_IN  JER2_ARAD_EGR_FC_DEVICE_THRESH *thresh
  );

/*********************************************************************
* NAME:
*     jer2_arad_egr_dev_fc_get_unsafe
* TYPE:
*   PROC
* DATE:
*   Dec 20 2007
* FUNCTION:
*     Set Flow Control thresholds for egress queues, based on
*     device-level resources. Threshold are set for overall
*     resources, and scheduled resources.
* INPUT:
*  DNX_SAND_IN  int                 unit -
*     Identifier of the device to access.
*  DNX_SAND_OUT JER2_ARAD_EGR_FC_DEVICE_THRESH *thresh -
*     Flow Control thresholds to set - Device-level resources.
* REMARKS:
*     None.
* RETURNS:
*     OK or ERROR indication.
*********************************************************************/
uint32
  jer2_arad_egr_dev_fc_get_unsafe(
    DNX_SAND_IN  int                 unit,
    DNX_SAND_IN  int                 core,
    DNX_SAND_OUT JER2_ARAD_EGR_FC_DEVICE_THRESH *thresh
  );

/*********************************************************************
* NAME:
*     jer2_arad_egr_xaui_spaui_fc_set_unsafe
* TYPE:
*   PROC
* DATE:
*   Dec 20 2007
* FUNCTION:
*     Set Flow Control thresholds for egress queues, per
*     channelized interface port, based on Channelized NIF
*     Ports resources.
* INPUT:
*  DNX_SAND_IN  int                 unit -
*     Identifier of the device to access.
*  DNX_SAND_IN  JER2_ARAD_INTERFACE_ID        if_ndx -
*     Channelized NIF index. Range: 0 -
*     JER2_ARAD_NOF_INTERFACES-1.
*  DNX_SAND_IN  JER2_ARAD_EGR_FC_CHNIF_THRESH *thresh -
*     Flow Control thresholds to set - CHNIF resources.
*  DNX_SAND_OUT JER2_ARAD_EGR_FC_CHNIF_THRESH *exact_thresh -
*     Will be filled with exact values.
* REMARKS:
*     None.
* RETURNS:
*     OK or ERROR indication.
*********************************************************************/
uint32
  jer2_arad_egr_xaui_spaui_fc_set_unsafe(
    DNX_SAND_IN  int                 unit,
    DNX_SAND_IN  JER2_ARAD_INTERFACE_ID        if_ndx,
    DNX_SAND_IN  JER2_ARAD_EGR_FC_CHNIF_THRESH *thresh,
    DNX_SAND_OUT JER2_ARAD_EGR_FC_CHNIF_THRESH *exact_thresh
  );

/*********************************************************************
* NAME:
*     jer2_arad_egr_xaui_spaui_fc_verify
* TYPE:
*   PROC
* DATE:
*   Dec 20 2007
* FUNCTION:
*     Set Flow Control thresholds for egress queues, per
*     channelized interface port, based on Channelized NIF
*     Ports resources.
* INPUT:
*  DNX_SAND_IN  int                 unit -
*     Identifier of the device to access.
*  DNX_SAND_IN  JER2_ARAD_INTERFACE_ID        if_ndx -
*     Channelized NIF index. Range: 0 -
*     JER2_ARAD_NOF_INTERFACES-1.
*  DNX_SAND_IN  JER2_ARAD_EGR_FC_CHNIF_THRESH *thresh -
*     Flow Control thresholds to set - CHNIF resources.
* REMARKS:
*     None.
* RETURNS:
*     OK or ERROR indication.
*********************************************************************/
uint32
  jer2_arad_egr_xaui_spaui_fc_verify(
    DNX_SAND_IN  int                 unit,
    DNX_SAND_IN  JER2_ARAD_INTERFACE_ID        if_ndx,
    DNX_SAND_IN  JER2_ARAD_EGR_FC_CHNIF_THRESH *thresh
  );

/*********************************************************************
* NAME:
*     jer2_arad_egr_xaui_spaui_fc_get_unsafe
* TYPE:
*   PROC
* DATE:
*   Dec 20 2007
* FUNCTION:
*     Set Flow Control thresholds for egress queues, per
*     channelized interface port, based on Channelized NIF
*     Ports resources.
* INPUT:
*  DNX_SAND_IN  int                 unit -
*     Identifier of the device to access.
*  DNX_SAND_IN  JER2_ARAD_INTERFACE_ID        if_ndx -
*     Channelized NIF index. Range: 0 -
*     JER2_ARAD_NOF_INTERFACES-1.
*  DNX_SAND_OUT JER2_ARAD_EGR_FC_CHNIF_THRESH *thresh -
*     Flow Control thresholds to set - CHNIF resources.
* REMARKS:
*     None.
* RETURNS:
*     OK or ERROR indication.
*********************************************************************/
uint32
  jer2_arad_egr_xaui_spaui_fc_get_unsafe(
    DNX_SAND_IN  int                 unit,
    DNX_SAND_IN  JER2_ARAD_INTERFACE_ID        if_ndx,
    DNX_SAND_OUT JER2_ARAD_EGR_FC_CHNIF_THRESH *thresh
  );

/*********************************************************************
* NAME:
*     jer2_arad_egr_ofp_fc_set_unsafe
* TYPE:
*   PROC
* DATE:
*   Dec 20 2007
* FUNCTION:
*     Set Flow Control thresholds for egress queues, per port
*     queue priority and threshold type, based on Outgoing FAP
*     Port (OFP) resources.
* INPUT:
*  DNX_SAND_IN  int                 unit -
*     Identifier of the device to access.
*  DNX_SAND_IN  JER2_ARAD_EGR_Q_PRIO          prio_ndx -
*     Queue priority index. Range: JER2_ARAD_EGR_Q_PRIO_LOW -
*     JER2_ARAD_EGR_Q_PRIO_HIGH.
*  DNX_SAND_IN  JER2_ARAD_EGR_PORT_THRESH_TYPE ofp_type_ndx -
*     Per-port threshold type index. Range: 0 -
*     JER2_ARAD_EGR_PORT_NOF_THRESH_TYPES-1.
*  DNX_SAND_IN  JER2_ARAD_EGR_FC_OFP_THRESH   *thresh -
*     Flow Control thresholds to set - FAP Port resources.
*  DNX_SAND_OUT JER2_ARAD_EGR_FC_OFP_THRESH   *exact_thresh -
*     Will be filled with exact values.
* REMARKS:
*     None.
* RETURNS:
*     OK or ERROR indication.
*********************************************************************/
uint32
  jer2_arad_egr_ofp_fc_set_unsafe(
    DNX_SAND_IN  int                 unit,
    DNX_SAND_IN  int                 core,
    DNX_SAND_IN  uint32                 prio_ndx,
    DNX_SAND_IN  JER2_ARAD_EGR_PORT_THRESH_TYPE ofp_type_ndx,
    DNX_SAND_IN  JER2_ARAD_EGR_FC_OFP_THRESH   *thresh,
    DNX_SAND_OUT JER2_ARAD_EGR_FC_OFP_THRESH   *exact_thresh
  );

/*********************************************************************
* NAME:
*     jer2_arad_egr_ofp_fc_verify
* TYPE:
*   PROC
* DATE:
*   Dec 20 2007
* FUNCTION:
*     Set Flow Control thresholds for egress queues, per port
*     queue priority and threshold type, based on Outgoing FAP
*     Port (OFP) resources.
* INPUT:
*  DNX_SAND_IN  int                 unit -
*     Identifier of the device to access.
*  DNX_SAND_IN  JER2_ARAD_EGR_Q_PRIO          prio_ndx -
*     Queue priority index. Range: JER2_ARAD_EGR_Q_PRIO_LOW -
*     JER2_ARAD_EGR_Q_PRIO_HIGH.
*  DNX_SAND_IN  JER2_ARAD_EGR_PORT_THRESH_TYPE ofp_type_ndx -
*     Per-port threshold type index. Range: 0 -
*     JER2_ARAD_EGR_PORT_NOF_THRESH_TYPES-1.
*  DNX_SAND_IN  JER2_ARAD_EGR_FC_OFP_THRESH   *thresh -
*     Flow Control thresholds to set - FAP Port resources.
* REMARKS:
*     None.
* RETURNS:
*     OK or ERROR indication.
*********************************************************************/
uint32
  jer2_arad_egr_ofp_fc_verify(
    DNX_SAND_IN  int                 unit,
    DNX_SAND_IN  JER2_ARAD_EGR_Q_PRIO          prio_ndx,
    DNX_SAND_IN  JER2_ARAD_EGR_PORT_THRESH_TYPE ofp_type_ndx,
    DNX_SAND_IN  JER2_ARAD_EGR_FC_OFP_THRESH   *thresh
  );

/*********************************************************************
* NAME:
*     jer2_arad_egr_ofp_fc_get_unsafe
* TYPE:
*   PROC
* DATE:
*   Dec 20 2007
* FUNCTION:
*     Set Flow Control thresholds for egress queues, per port
*     queue priority and threshold type, based on Outgoing FAP
*     Port (OFP) resources.
* INPUT:
*  DNX_SAND_IN  int                 unit -
*     Identifier of the device to access.
*  DNX_SAND_IN  JER2_ARAD_EGR_Q_PRIO          prio_ndx -
*     Queue priority index. Range: JER2_ARAD_EGR_Q_PRIO_LOW -
*     JER2_ARAD_EGR_Q_PRIO_HIGH.
*  DNX_SAND_IN  JER2_ARAD_EGR_PORT_THRESH_TYPE ofp_type_ndx -
*     Per-port threshold type index. Range: 0 -
*     JER2_ARAD_EGR_PORT_NOF_THRESH_TYPES-1.
*  DNX_SAND_OUT JER2_ARAD_EGR_FC_OFP_THRESH   *thresh -
*     Flow Control thresholds to set - FAP Port resources.
* REMARKS:
*     None.
* RETURNS:
*     OK or ERROR indication.
*********************************************************************/
uint32
  jer2_arad_egr_ofp_fc_get_unsafe(
    DNX_SAND_IN  int                 unit,
    DNX_SAND_IN  int                 core,
    DNX_SAND_IN  JER2_ARAD_EGR_Q_PRIO          prio_ndx,
    DNX_SAND_IN  JER2_ARAD_EGR_PORT_THRESH_TYPE ofp_type_ndx,
    DNX_SAND_OUT JER2_ARAD_EGR_FC_OFP_THRESH   *thresh
  );

/*********************************************************************
* NAME:
*     jer2_arad_egr_ofp_scheduling_set_unsafe
* TYPE:
*   PROC
* DATE:
*   Dec 20 2007
* FUNCTION:
*     Set per-port egress scheduling information.
* INPUT:
*  DNX_SAND_IN  int                 unit -
*     Identifier of the device to access.
*  DNX_SAND_IN  JER2_ARAD_FAP_PORT_ID         ofp_ndx -
*     Outgoing Fap Port index to configure.
*  DNX_SAND_IN  JER2_ARAD_EGR_OFP_SCH_INFO    *info -
*     Per-port egress scheduling info
* REMARKS:
*   Some of the scheduling info may be irrelevant -
*   i.e. channelized interface priority is only relevant if the port
*   is mapped to a channelized NIF.
* RETURNS:
*     OK or ERROR indication.
*********************************************************************/
uint32
  jer2_arad_egr_ofp_scheduling_set_unsafe(
    DNX_SAND_IN  int                 unit,
    DNX_SAND_IN  int                 core,
    DNX_SAND_IN  uint32              tm_port,
    DNX_SAND_IN  JER2_ARAD_EGR_OFP_SCH_INFO    *info
  );

/*********************************************************************
* NAME:
*     jer2_arad_egr_ofp_scheduling_verify
* TYPE:
*   PROC
* DATE:
*   Dec 20 2007
* FUNCTION:
*   See jer2_arad_egr_ofp_scheduling_set_unsafe
* REMARKS:
*   Some of the scheduling info may be irrelevant -
*   i.e. channelized interface priority is only relevant if the port
*   is mapped to a channelized NIF.
* RETURNS:
*     OK or ERROR indication.
*********************************************************************/
uint32
  jer2_arad_egr_ofp_scheduling_verify(
    DNX_SAND_IN  int                 unit,
    DNX_SAND_IN  JER2_ARAD_FAP_PORT_ID         ofp_ndx,
    DNX_SAND_IN  JER2_ARAD_EGR_OFP_SCH_INFO    *info
  );

/*********************************************************************
* NAME:
*     jer2_arad_egr_ofp_scheduling_get_unsafe
* TYPE:
*   PROC
* DATE:
*   Dec 20 2007
* FUNCTION:
*   See jer2_arad_egr_ofp_scheduling_set_unsafe
* INPUT:
*  DNX_SAND_IN  int                 unit -
*     Identifier of the device to access.
*  DNX_SAND_IN  JER2_ARAD_FAP_PORT_ID         ofp_ndx -
*     Outgoing Fap Port index to configure.
*  DNX_SAND_OUT JER2_ARAD_EGR_OFP_SCH_INFO    *info -
*     Per-port egress scheduling info
* REMARKS:
*   Some of the scheduling info may be irrelevant -
*   i.e. channelized interface priority is only relevant if the port
*   is mapped to a channelized NIF.
* RETURNS:
*     OK or ERROR indication.
*********************************************************************/
uint32
  jer2_arad_egr_ofp_scheduling_get_unsafe(
    DNX_SAND_IN  int                 unit,
    DNX_SAND_IN  int                 core,
    DNX_SAND_IN  uint32              tm_port,
    DNX_SAND_OUT JER2_ARAD_EGR_OFP_SCH_INFO    *info
  );

/*********************************************************************
* NAME:
 *   jer2_arad_egr_q_prio_set_unsafe
 * TYPE:
 *   PROC
 * FUNCTION:
 *   Sets egress queue priority per traffic class and drop
 *   precedence.
 * INPUT:
 *   DNX_SAND_IN  int                     unit -
 *     Identifier of the device to access.
 *   DNX_SAND_IN  JER2_ARAD_EGR_Q_PRIO_MAPPING_TYPE map_type_ndx -
 *     mapping type, defining what traffic type
 *     (unicast/multicast) is mapped to what egress queue type
 *     (scheduled/unscheduled).
 *   DNX_SAND_IN  uint32                     tc_ndx -
 *     Traffic Class, as embedded in the packet header. Range:
 *     0 - 7.
 *   DNX_SAND_IN  uint32                     dp_ndx -
 *     Drop Precedence, as embedded in the packet header.
 *     Range: 0 - 3.
 *   DNX_SAND_IN  uint32                     map_profile_ndx -
 *     Mapping profile index. Range: 0 - 3.
 *   DNX_SAND_IN  JER2_ARAD_EGR_Q_PRIORITY             *priority -
 *     Egress Queuing priority (Drop precedence and Traffic
 *     class).
 * REMARKS:
 *   Each OFP is mapped to an egress queue profile by the
 *   jer2_arad_egr_q_profile_map_set API.
 * RETURNS:
 *   OK or ERROR indication.
*********************************************************************/
int
  jer2_arad_egr_q_prio_set(
    DNX_SAND_IN  int                            unit,
    DNX_SAND_IN  int                            core,
    DNX_SAND_IN  JER2_ARAD_EGR_Q_PRIO_MAPPING_TYPE   map_type_ndx,
    DNX_SAND_IN  uint32                         tc_ndx,
    DNX_SAND_IN  uint32                         dp_ndx,
    DNX_SAND_IN  uint32                         map_profile_ndx,
    DNX_SAND_IN  JER2_ARAD_EGR_Q_PRIORITY            *priority
  );

/*********************************************************************
*     Gets the configuration set by the
 *     "jer2_arad_egr_q_prio_set_unsafe" API.
 *     Refer to "jer2_arad_egr_q_prio_set_unsafe" API for details.
*********************************************************************/
int
  jer2_arad_egr_q_prio_get(
    DNX_SAND_IN  int                            unit,
    DNX_SAND_IN  int                            core,
    DNX_SAND_IN  JER2_ARAD_EGR_Q_PRIO_MAPPING_TYPE   map_type_ndx,
    DNX_SAND_IN  uint32                         tc_ndx,
    DNX_SAND_IN  uint32                         dp_ndx,
    DNX_SAND_IN  uint32                         map_profile_ndx,
    DNX_SAND_OUT JER2_ARAD_EGR_Q_PRIORITY            *priority
  );

/*********************************************************************
* NAME:
 *   jer2_arad_egr_q_profile_map_set_unsafe
 * TYPE:
 *   PROC
 * FUNCTION:
 *   Function description
 * INPUT:
 *   DNX_SAND_IN  int                      unit -
 *     Identifier of the device to access.
 *   DNX_SAND_IN  JER2_ARAD_FAP_PORT_ID              ofp_ndx -
 *     Outgoing Fap Port index. Range: 0 - 79.
 *   DNX_SAND_IN  uint32                      map_profile_id -
 *     Egress queue priority profile index. Range: 0 - 3.
 * REMARKS:
 *   The profile configuration is set by the
 *   jer2_arad_egr_q_prio_set API.
 * RETURNS:
 *   OK or ERROR indication.
*********************************************************************/
int
  jer2_arad_egr_q_profile_map_set(
    DNX_SAND_IN  int                    unit,
    DNX_SAND_IN  int                    core_id,
    DNX_SAND_IN  uint32                 tm_port,
    DNX_SAND_IN  uint32                 map_profile_id
  );

/*********************************************************************
*     Gets the configuration set by the
 *     "jer2_arad_egr_q_profile_map_set_unsafe" API.
 *     Refer to "jer2_arad_egr_q_profile_map_set_unsafe" API for
 *     details.
*********************************************************************/
int
  jer2_arad_egr_q_profile_map_get(
    DNX_SAND_IN  int                    unit,
    DNX_SAND_IN  int                    core_id,
    DNX_SAND_IN  uint32                 tm_port,
    DNX_SAND_OUT uint32                 *map_profile_id
  );

/*********************************************************************
* NAME:
 *   jer2_arad_egr_cgm_interface_set
 * TYPE:
 *   PROC
 * FUNCTION:
 *   Function description
 * INPUT:
 *   DNX_SAND_IN  int                      unit -
 *     Identifier of the device to access.
 *   DNX_SAND_IN  uint32              tm_port -
 *     Outgoing Fap Port index. Range: 0 - 79.
 *   DNX_SAND_IN  uint32                      cgm_interface -
 *     Egress queue cgm interface.
 * RETURNS:
 *   OK or ERROR indication.
*********************************************************************/
int
  jer2_arad_egr_q_cgm_interface_set(
    DNX_SAND_IN  int                    unit,
    DNX_SAND_IN  int                    core,
    DNX_SAND_IN  uint32                 tm_port,
    DNX_SAND_IN  uint32                 cgm_interface
  );

/*********************************************************************
* NAME:
 *   jer2_arad_egr_q_profile_map_set_unsafe
 * TYPE:
 *   PROC
 * FUNCTION:
 *   Function description
 * INPUT:
 *   DNX_SAND_IN  int                      unit -
 *     Identifier of the device to access.
 *   DNX_SAND_IN  JER2_ARAD_FAP_PORT_ID              ofp_ndx -
 *     Outgoing Fap Port index. Range: 0 - 255.
 *   DNX_SAND_IN  JER2_ARAD_EGR_PORT_SHAPER_MODE     shaper_mode -
 *     Egress shaper mode data or packet. Range: 0 - 1.
 * REMARKS:
 *   None
 * RETURNS:
 *   OK or ERROR indication.
*********************************************************************/
uint32
  jer2_arad_egr_dsp_pp_shaper_mode_set_unsafe(
    DNX_SAND_IN  int                      unit,
    DNX_SAND_IN  int                            core,
    DNX_SAND_IN  JER2_ARAD_FAP_PORT_ID               ofp_ndx,
    DNX_SAND_IN  JER2_ARAD_EGR_PORT_SHAPER_MODE      shaper_mode
  );

uint32
  jer2_arad_egr_dsp_pp_shaper_mode_set_verify(
    DNX_SAND_IN  int                      unit,
    DNX_SAND_IN  JER2_ARAD_FAP_PORT_ID               ofp_ndx,
    DNX_SAND_IN  JER2_ARAD_EGR_PORT_SHAPER_MODE      shaper_mode
  );

uint32
  jer2_arad_egr_dsp_pp_shaper_mode_get_verify(
    DNX_SAND_IN  int                      unit,
    DNX_SAND_IN  JER2_ARAD_FAP_PORT_ID               ofp_ndx
  );

/*********************************************************************
*     Gets the configuration set by the
 *     "jer2_arad_egr_dsp_pp_shaper_mode_set_unsafe" API.
 *     Refer to "jer2_arad_egr_dsp_pp_shaper_mode_set_unsafe" API for
 *     details.
*********************************************************************/
uint32
  jer2_arad_egr_dsp_pp_shaper_mode_get_unsafe(
    DNX_SAND_IN  int                      unit,
    DNX_SAND_IN  JER2_ARAD_FAP_PORT_ID              ofp_ndx,
    DNX_SAND_OUT JER2_ARAD_EGR_PORT_SHAPER_MODE     *shaper_mode
  );


/*********************************************************************
* NAME:
 *   jer2_arad_egr_dsp_pp_to_base_q_pair_set_unsafe
 * TYPE:
 *   PROC
 * FUNCTION:
 *   Function description
 * INPUT:
 *   DNX_SAND_IN  int                      unit -
 *     Identifier of the device to access.
 *   DNX_SAND_IN  JER2_ARAD_FAP_PORT_ID              ofp_ndx -
 *     Outgoing Fap Port index. Range: 0 - 255.
 *   DNX_SAND_IN  uint32                      base_q_pair -
 *     Egress base queue pair index. Range: 0 - 255.
 * REMARKS:
 *   base queue pair is the internal out tm port.
 * RETURNS:
 *   OK or ERROR indication.
*********************************************************************/
int
  jer2_arad_egr_dsp_pp_to_base_q_pair_set(
    DNX_SAND_IN  int        unit,
    DNX_SAND_IN  int        core_id,
    DNX_SAND_IN  uint32     tm_port,
    DNX_SAND_IN  uint32     base_q_pair
  );

uint32
  jer2_arad_egr_dsp_pp_to_base_q_pair_set_verify(
    DNX_SAND_IN  int                      unit,
    DNX_SAND_IN  int                      core,
    DNX_SAND_IN  uint32                   tm_port,
    DNX_SAND_IN  uint32                   base_q_pair
  );

uint32
  jer2_arad_egr_dsp_pp_to_base_q_pair_get_verify(
    DNX_SAND_IN  int                        unit,
    DNX_SAND_IN  int                        core,
    DNX_SAND_IN  JER2_ARAD_FAP_PORT_ID           ofp_ndx
  );

/*********************************************************************
*     Gets the configuration set by the
 *     "jer2_arad_egr_dsp_pp_to_base_q_pair_set_unsafe" API.
 *     Refer to "jer2_arad_egr_dsp_pp_to_base_q_pair_set_unsafe" API for
 *     details.
*********************************************************************/
uint32
  jer2_arad_egr_dsp_pp_to_base_q_pair_get_unsafe(
    DNX_SAND_IN  int                      unit,
    DNX_SAND_IN  int                      core,
    DNX_SAND_IN  JER2_ARAD_FAP_PORT_ID              ofp_ndx,
    DNX_SAND_OUT uint32                      *base_q_pair
  );

/*********************************************************************
* NAME:
 *   jer2_arad_egr_dsp_pp_to_base_q_pair_set_unsafe
 * TYPE:
 *   PROC
 * FUNCTION:
 *   Function description
 * INPUT:
 *   DNX_SAND_IN  int                      unit -
 *     Identifier of the device to access.
 *   DNX_SAND_IN  JER2_ARAD_FAP_PORT_ID              ofp_ndx -
 *     Outgoing Fap Port index. Range: 0 - 255.
 *   DNX_SAND_IN  uint32                      base_q_pair -
 *     Egress base queue pair index. Range: 0 - 255.
 * REMARKS:
 *   base queue pair is the internal out tm port.
 * RETURNS:
 *   OK or ERROR indication.
*********************************************************************/
int
  jer2_arad_egr_dsp_pp_priorities_mode_set(
    DNX_SAND_IN  int                            unit,
    DNX_SAND_IN  int                            core_id,
    DNX_SAND_IN  uint32                         tm_port,
    DNX_SAND_IN  JER2_ARAD_EGR_PORT_PRIORITY_MODE    priority_mode
  );

uint32
  jer2_arad_egr_dsp_pp_priorities_mode_set_verify(
    DNX_SAND_IN  int                      unit,
    DNX_SAND_IN  JER2_ARAD_FAP_PORT_ID               ofp_ndx,
    DNX_SAND_IN  JER2_ARAD_EGR_PORT_PRIORITY_MODE    priority_mode
  );

uint32
  jer2_arad_egr_dsp_pp_priorities_mode_get_verify(
    DNX_SAND_IN  int                     unit,
    DNX_SAND_IN  JER2_ARAD_FAP_PORT_ID              ofp_ndx
  );

/*********************************************************************
*     Gets the configuration set by the
 *     "jer2_arad_egr_dsp_pp_to_base_q_pair_set_unsafe" API.
 *     Refer to "jer2_arad_egr_dsp_pp_to_base_q_pair_set_unsafe" API for
 *     details.
*********************************************************************/
uint32
  jer2_arad_egr_dsp_pp_priorities_mode_get_unsafe(
    DNX_SAND_IN  int                      unit,
    DNX_SAND_IN  JER2_ARAD_FAP_PORT_ID               ofp_ndx,
    DNX_SAND_OUT JER2_ARAD_EGR_PORT_PRIORITY_MODE    *priority_mode
  );

/*********************************************************************
* NAME:
 *   jer2_arad_egr_queuing_dev_set/get _unsafe
 * TYPE:
 *   PROC
 *	Set the thresholds of the Multicast / Unicast service pools at device-level.
 * INPUT
 *	DNX_SAND_IN(DNX_SAND_OUT in get)
 *    JER2_ARAD_EGR_QUEUING_DEV_TH	*info -
 *		Service pool parameters
 * REMARKS:
 *   None.
 * RETURNS:
 *   OK or ERROR indication.
*********************************************************************/
uint32	
  jer2_arad_egr_queuing_dev_set_unsafe(
	DNX_SAND_IN	 int	unit,
    DNX_SAND_IN  int    core,
	DNX_SAND_IN  JER2_ARAD_EGR_QUEUING_DEV_TH	*info
  );

uint32	
  jer2_arad_egr_queuing_dev_get_unsafe(
	DNX_SAND_IN	 int	unit,
    DNX_SAND_IN  int    core,
	DNX_SAND_OUT JER2_ARAD_EGR_QUEUING_DEV_TH	*info
  );

uint32    
  jer2_arad_egr_queuing_global_drop_set_unsafe(
      DNX_SAND_IN  int   unit,
      DNX_SAND_IN  int   core, 
      DNX_SAND_IN  soc_dnx_cosq_threshold_type_t threshold_type,
      DNX_SAND_IN  int    threshold_value,
      DNX_SAND_IN  soc_dnx_cosq_threshold_global_type_t drop_type 
  );

uint32    
  jer2_arad_egr_queuing_global_drop_get_unsafe(
      DNX_SAND_IN  int   unit,
      DNX_SAND_IN  int   core, 
      DNX_SAND_IN  soc_dnx_cosq_threshold_type_t threshold_type,
      DNX_SAND_OUT int*    threshold_value,
      DNX_SAND_IN  soc_dnx_cosq_threshold_global_type_t drop_type 
  );

uint32
  jer2_arad_egr_queuing_sp_tc_drop_set_unsafe(
    DNX_SAND_IN    int    unit,
    DNX_SAND_IN    int    core,
    DNX_SAND_IN    int    tc,
    DNX_SAND_IN    soc_dnx_cosq_threshold_type_t threshold_type,
    DNX_SAND_IN    int    threshold_value,
    DNX_SAND_IN    soc_dnx_cosq_threshold_global_type_t drop_type
  );
uint32
  jer2_arad_egr_queuing_sp_tc_drop_get_unsafe(
    DNX_SAND_IN    int    unit,
    DNX_SAND_IN    int    core,
    DNX_SAND_IN    int    tc,
    DNX_SAND_IN    soc_dnx_cosq_threshold_type_t threshold_type,
    DNX_SAND_OUT   int*   threshold_value,
    DNX_SAND_IN    soc_dnx_cosq_threshold_global_type_t drop_type
  );

uint32
  jer2_arad_egr_queuing_sp_reserved_set_unsafe(
    DNX_SAND_IN    int    unit,
    DNX_SAND_IN    int    core,
    DNX_SAND_IN    int    tc,
    DNX_SAND_IN    soc_dnx_cosq_threshold_type_t threshold_type,
    DNX_SAND_IN    int    threshold_value,
    DNX_SAND_IN    soc_dnx_cosq_threshold_global_type_t drop_type
  );

uint32
  jer2_arad_egr_queuing_sp_reserved_get_unsafe(
    DNX_SAND_IN    int    unit,
    DNX_SAND_IN    int    core,
    DNX_SAND_IN    int    tc,
    DNX_SAND_IN    soc_dnx_cosq_threshold_type_t threshold_type,
    DNX_SAND_OUT   int*   threshold_value,
    DNX_SAND_IN    soc_dnx_cosq_threshold_global_type_t drop_type
  );

uint32 
  jer2_arad_egr_queuing_sch_unsch_drop_set_unsafe(
    DNX_SAND_IN    int    unit,
    DNX_SAND_IN    int    core,
    DNX_SAND_IN    int    threshold_type,
    DNX_SAND_IN    DNX_TMC_EGR_QUEUING_DEV_TH *dev_thresh
  );

uint32
  jer2_arad_egr_queuing_global_fc_set_unsafe(
      DNX_SAND_IN  int   unit,
      DNX_SAND_IN  int   core, 
      DNX_SAND_IN  soc_dnx_cosq_threshold_type_t threshold_type,
      DNX_SAND_IN  int    threshold_value, 
      DNX_SAND_IN  soc_dnx_cosq_threshold_global_type_t drop_type
  );

uint32
  jer2_arad_egr_queuing_global_fc_get_unsafe(
      DNX_SAND_IN  int   unit,
      DNX_SAND_IN  int   core, 
      DNX_SAND_IN  soc_dnx_cosq_threshold_type_t threshold_type,
      DNX_SAND_OUT int*   threshold_value, 
      DNX_SAND_IN  soc_dnx_cosq_threshold_global_type_t drop_type
  );

uint32 
  jer2_arad_egr_queuing_mc_tc_fc_set_unsafe(
    DNX_SAND_IN    int    unit,
    DNX_SAND_IN    int    core,
    DNX_SAND_IN    int    tc,
    DNX_SAND_IN    soc_dnx_cosq_threshold_type_t threshold_type,
    DNX_SAND_IN    int    threshold_value
  );

uint32 
  jer2_arad_egr_queuing_mc_tc_fc_get_unsafe(
    DNX_SAND_IN    int    unit,
    DNX_SAND_IN    int    core,
    DNX_SAND_IN    int    tc,
    DNX_SAND_IN    soc_dnx_cosq_threshold_type_t threshold_type,
    DNX_SAND_OUT   int*    threshold_value
  );

/*********************************************************************
* NAME:
 *   jer2_arad_egr_queuing_mc_cos_map_set/get _unsafe
 * TYPE:
 *   PROC
 *	Set the COS mapping for egress multicast packets: TC-Group, Service Pool id and Service Pool eligibility.
 * INPUT
 *	DNX_SAND_IN	uint32	tc_ndx -
 *		Traffic Class. Range: 0 - 7.
 *	DNX_SAND_IN	uint32	dp_ndx -
 *		Drop Precedence. Range: 0 - 3.
 *	DNX_SAND_IN	(DNX_SAND_OUT in get) JER2_ARAD_EGR_QUEUING_MC_COS_MAP	*info -
 *		COS mapping parameters
 * REMARKS:
 *   None.
 * RETURNS:
 *   OK or ERROR indication.
*********************************************************************/

uint32	
  jer2_arad_egr_queuing_mc_cos_map_set_unsafe(
	DNX_SAND_IN	int	unit,
    DNX_SAND_IN int core,
	DNX_SAND_IN	uint32	tc_ndx,
	DNX_SAND_IN	uint32	dp_ndx,
	DNX_SAND_IN JER2_ARAD_EGR_QUEUING_MC_COS_MAP	*info
  );

uint32	
  jer2_arad_egr_queuing_mc_cos_map_get_unsafe(
	DNX_SAND_IN	 int	unit,
    DNX_SAND_IN  int    core,
	DNX_SAND_IN	 uint32	tc_ndx,
	DNX_SAND_IN	 uint32	dp_ndx,
	DNX_SAND_OUT JER2_ARAD_EGR_QUEUING_MC_COS_MAP	*info
  );

/*********************************************************************
* NAME:
 *   jer2_arad_egr_queuing_if_fc_set/get _unsafe
 * TYPE:
 *   PROC
 *	Set the Interface Flow Control profiles for UC and MC.
 * INPUT
 *	DNX_SAND_IN	JER2_ARAD_INTERFACE_ID	if_ndx -
 *		Interface ID.
 *	DNX_SAND_IN	(DNX_SAND_OUT in get) JER2_ARAD_EGR_QUEUING_IF_FC	*info -
 *		Interface Flow Control profiles
 * REMARKS:
 *   None.
 * RETURNS:
 *   OK or ERROR indication.
*********************************************************************/
uint32	
  jer2_arad_egr_queuing_if_fc_set_unsafe(
	DNX_SAND_IN	 int	unit,
	DNX_SAND_IN	 JER2_ARAD_INTERFACE_ID	if_ndx,
	DNX_SAND_IN  JER2_ARAD_EGR_QUEUING_IF_FC	*info
  );

uint32	
  jer2_arad_egr_queuing_if_fc_get_unsafe(
	DNX_SAND_IN	 int	unit,
	DNX_SAND_IN	 JER2_ARAD_INTERFACE_ID	if_ndx,
	DNX_SAND_OUT JER2_ARAD_EGR_QUEUING_IF_FC	*info
  );

/*********************************************************************
 * is_high_priority indicates if port is high or low  priority
*********************************************************************/
soc_error_t
jer2_arad_egr_queuing_is_high_priority_port_get(int unit, int core, uint32 tm_port, int *is_high_priority);

/*********************************************************************
* NAME:
 *   jer2_arad_egr_queuing_if_fc_uc_set/get _unsafe
 * TYPE:
 *   PROC
 *	Set the Interface Flow Control profile attributes for UC traffic.
 * INPUT
 *	DNX_SAND_IN	uint32	uc_if_profile_ndx-
 *		Unicast interface threshold profile.
 *	DNX_SAND_IN	(DNX_SAND_OUT for get) JER2_ARAD_EGR_QUEUING_IF_UC_FC	*info -
 *		Interface Flow Control profile attributes
 * REMARKS:
 *   None.
 * RETURNS:
 *   OK or ERROR indication.
*********************************************************************/

uint32	
  jer2_arad_egr_queuing_if_fc_uc_set_unsafe(
	DNX_SAND_IN	int	unit,
    DNX_SAND_IN int core,
	DNX_SAND_IN	uint32	uc_if_profile_ndx,
	DNX_SAND_IN JER2_ARAD_EGR_QUEUING_IF_UC_FC	*info
  );

uint32	
  jer2_arad_egr_queuing_if_fc_uc_get_unsafe(
	DNX_SAND_IN	 int	unit,
    DNX_SAND_IN  int    core,
	DNX_SAND_IN	 uint32	uc_if_profile_ndx,
	DNX_SAND_OUT JER2_ARAD_EGR_QUEUING_IF_UC_FC	*info
  );

/*********************************************************************
* NAME:
 *   jer2_arad_egr_queuing_if_fc_mc_set/get _unsafe
 * TYPE:
 *   PROC
 *	Set the Interface Flow Control profile attributes for MC traffic.
 * INPUT
 *	DNX_SAND_IN	uint32	mc_if_profile_ndx-
 *		Unicast interface threshold profile.
 *	DNX_SAND_IN	(DNX_SAND_OUT for get) uint32	pd_th -
 * Total consumed Multicast PD per interface threshold.
 * Range: 0 - 0x7FFF.
 * REMARKS:
 *   None.
 * RETURNS:
 *   OK or ERROR indication.
*********************************************************************/

uint32	
  jer2_arad_egr_queuing_if_fc_mc_set_unsafe(
	DNX_SAND_IN	int	unit,
    DNX_SAND_IN int core,
	DNX_SAND_IN	uint32	mc_if_profile_ndx,
	DNX_SAND_IN uint32    pd_th
  );

uint32	
  jer2_arad_egr_queuing_if_fc_mc_get_unsafe(
	DNX_SAND_IN	 int	unit,
	DNX_SAND_IN	 uint32	mc_if_profile_ndx,
	DNX_SAND_OUT uint32   *pd_th
  );

uint32 
  jer2_arad_egr_queuing_if_uc_map_set_unsafe(
    DNX_SAND_IN  int        unit,
    DNX_SAND_IN  int        core,
    DNX_SAND_IN  soc_port_if_t interface_type,
    DNX_SAND_IN  uint32     internal_if_id,
    DNX_SAND_IN  int        profile
  );

uint32 
  jer2_arad_egr_queuing_if_mc_map_set_unsafe(
    DNX_SAND_IN  int        unit,
    DNX_SAND_IN  int        core,
    DNX_SAND_IN  soc_port_if_t interface_type,
    DNX_SAND_IN  uint32     internal_if_id,
    DNX_SAND_IN  int        profile
  );

/*********************************************************************
* NAME:
 *   jer2_arad_egr_queuing_ofp_tcg_set/get _unsafe
 * TYPE:
 * PROC
 *	Associate the queue-pair (Port,Priority) to traffic class
 *    groups (TCG) attributes.
 * Input
 *   DNX_SAND_IN  int                      unit -
 *     Identifier of the device to access.
 *   DNX_SAND_IN  JER2_ARAD_FAP_PORT_ID              ofp_ndx -
 *     Outgoing Fap Port index. Range: 0 - 255.
 *   DNX_SAND_IN  uint32	                    tcg_info -
 *     TCG attributes to be filled
 * REMARKS:
 *   The last four TCG are single-member groups. Scheduling within
 *   a TCG is done in a strict priority manner according to the
 *   priority level. (e.g. If P1,P2,P7 within the same TCG1.
 *   Then SP select is descending priority P7,P2,P1).
 * RETURNS:
 *   OK or ERROR indication.
*********************************************************************/
uint32
  jer2_arad_egr_queuing_ofp_tcg_set_unsafe(
    DNX_SAND_IN  int                            unit,
    DNX_SAND_IN  int                            core,
    DNX_SAND_IN  uint32                         tm_port,
    DNX_SAND_IN  JER2_ARAD_EGR_QUEUING_TCG_INFO      *tcg_info
  );

uint32
  jer2_arad_egr_queuing_ofp_tcg_get_unsafe(
    DNX_SAND_IN  int                            unit,
    DNX_SAND_IN  int                            core,
    DNX_SAND_IN  uint32                         tm_port,
    DNX_SAND_OUT JER2_ARAD_EGR_QUEUING_TCG_INFO      *tcg_info
  );

uint32
  jer2_arad_egr_queuing_ofp_tcg_set_verify(
    DNX_SAND_IN  int                      unit,
    DNX_SAND_IN  int                      core,
    DNX_SAND_IN  uint32                   tm_port,    
    DNX_SAND_IN  JER2_ARAD_EGR_QUEUING_TCG_INFO      *tcg_info
  );

/*********************************************************************
* NAME:
*     jer2_arad_sch_port_tcg_weight_set/get _unsafe
* TYPE:
*   PROC
* DATE:
*  
* FUNCTION:
*     Sets, for a specified TCG within a certain OFP
*     its excess rate. Excess traffic is scheduled between other TCGs
*     according to a weighted fair queueing or strict priority policy.
*     Set invalid, in case TCG not take part of this policy.
* INPUT:
*  DNX_SAND_IN  int                 unit -
*     Identifier of device to access.
*  DNX_SAND_IN  JER2_ARAD_FAP_PORT_ID          ofp_ndx -
*     Port id, 0 - 255. 
*  DNX_SAND_IN  JER2_ARAD_TCG_NDX              tcg_ndx -
*     TCG index. 0-7.
*  DNX_SAND_IN  JER2_ARAD_EGR_TCG_SCH_WFQ      *tcg_weight -
*     TCG weight information.
* RETURNS:
*   OK or ERROR indication.
* REMARKS:
*   This function must only be called for eight priorities port.
*********************************************************************/
uint32
  jer2_arad_egr_queuing_tcg_weight_set_unsafe(
    DNX_SAND_IN  int                       unit,
    DNX_SAND_IN  int                       core,
    DNX_SAND_IN  uint32                    tm_port,
    DNX_SAND_IN  JER2_ARAD_TCG_NDX              tcg_ndx,
    DNX_SAND_IN  JER2_ARAD_EGR_TCG_SCH_WFQ      *tcg_weight
  );

uint32
  jer2_arad_egr_queuing_tcg_weight_get_unsafe(
    DNX_SAND_IN  int                       unit,
    DNX_SAND_IN  int                       core,
    DNX_SAND_IN  uint32                    tm_port,
    DNX_SAND_IN  JER2_ARAD_TCG_NDX              tcg_ndx,
    DNX_SAND_OUT JER2_ARAD_EGR_TCG_SCH_WFQ      *tcg_weight
  );

uint32
  jer2_arad_egr_queuing_tcg_weight_set_verify_unsafe(
    DNX_SAND_IN  int                       unit,
    DNX_SAND_IN  int                       core,
    DNX_SAND_IN  uint32                    tm_port,
    DNX_SAND_IN  JER2_ARAD_TCG_NDX              tcg_ndx,
    DNX_SAND_IN  JER2_ARAD_EGR_TCG_SCH_WFQ      *tcg_weight
  );

uint32
  jer2_arad_egr_queuing_tcg_weight_get_verify_unsafe(
    DNX_SAND_IN  int                       unit,
    DNX_SAND_IN  int                       core,
    DNX_SAND_IN  uint32                    tm_port,
    DNX_SAND_IN  JER2_ARAD_TCG_NDX              tcg_ndx,
    DNX_SAND_IN JER2_ARAD_EGR_TCG_SCH_WFQ       *tcg_weight
  );


uint32
  jer2_arad_egr_thresh_fld_to_mnt_exp(
    DNX_SAND_IN  JER2_ARAD_REG_FIELD     *thresh_fld,
    DNX_SAND_IN  uint32            thresh,
    DNX_SAND_OUT uint32            *exact_thresh,
    DNX_SAND_OUT uint32            *thresh_fld_val
  );

uint32
  jer2_arad_egr_mnt_exp_to_thresh_fld(
    DNX_SAND_IN  JER2_ARAD_REG_FIELD  *thresh_fld,
    DNX_SAND_IN  uint32         *thresh_fld_val_in,
    DNX_SAND_OUT uint32         *thresh_out
  );

uint32
  JER2_ARAD_EGR_Q_PRIORITY_verify(
    DNX_SAND_IN  JER2_ARAD_EGR_Q_PRIORITY *info
  );

/*********************************************************************
* NAME:
 *   jer2_arad_egr_queuing_partition_scheme_set
 * TYPE:
 *   PROC
 * FUNCTION:
 *   Set the partitioning scheme of the service pools.
 * INPUT:
 *   DNX_SAND_IN	JER2_ARAD_EGR_QUEUING_PARTITION_SCHEME	scheme -
 *   Service Pool partition scheme
 * REMARKS:
 *   None.
 * RETURNS:
 *   OK or ERROR indication.
*********************************************************************/
int
  jer2_arad_egr_queuing_partition_scheme_set_unsafe(
      DNX_SAND_IN   int unit,
      DNX_SAND_IN   JER2_ARAD_EGR_QUEUING_PARTITION_SCHEME	scheme
  );

/*********************************************************************
* NAME:
*   soc_jer2_arad_congestion_statistics_get
* FUNCTION:
*   Get Arad congestion statistics.
* REMARKS:
* Output will be returned in each of the first three structure pointers if it is not Null.
*
* If disable_updates is non zero, then maximum statistics update will be disabled during
* maximum statistics collection.
* This will provide correlated maximum statistics, at the expense of not updating
* the maximum statistics during the operation.
*
* If max_stats is not null, the maximum values are reset when they are read.
* The next read will contain maximum values from this function call.
*********************************************************************/

int soc_jer2_arad_egr_congestion_statistics_get(
  DNX_SAND_IN int unit,
  DNX_SAND_IN int core,
  DNX_SAND_INOUT JER2_ARAD_EGR_CGM_CONGENSTION_STATS *cur_stats,   /* place current statistics output here */
  DNX_SAND_INOUT JER2_ARAD_EGR_CGM_CONGENSTION_STATS *max_stats,   /* place maximum statistics output here */
  DNX_SAND_INOUT JER2_ARAD_EGR_CGM_CONGENSTION_COUNTERS *counters, /* place counters output here */
  DNX_SAND_IN int disable_updates /* should the function disable maximum statistics updates when it collects them */
  );


/*********************************************************************
* NAME:
*     jer2_arad_egr_q_fqp_scheduer_config
* TYPE:
*   PROC
* DATE:
* FUNCTION:
*         Set fqp scheduler configuration:
*         1. Enable BW requests by others
*         2. Disable BW higher requests on account port with rate of 1009 or higher
* INPUT:
*         DNX_SAND_IN int unit
*
* RETURNS:
*     OK or ERROR indication.
*********************************************************************/

int
  jer2_arad_egr_q_fqp_scheduler_config(
    DNX_SAND_IN int unit
  );

/* } */


int 
jer2_arad_egr_queuing_egr_interface_alloc(
    DNX_SAND_IN  int             unit,
    DNX_SAND_IN  soc_port_t      port
    );

int 
jer2_arad_egr_queuing_egr_interface_free(
    DNX_SAND_IN  int             unit,
    DNX_SAND_IN  soc_port_t      port
    );

uint32
jer2_arad_egr_threshold_types_verify(
   DNX_SAND_IN    int   unit,
   DNX_SAND_IN    soc_dnx_cosq_threshold_type_t threshold_type);

uint32
    jer2_arad_egr_ofp_fc_q_pair_thresh_set_unsafe(
      DNX_SAND_IN  int                 unit,
      DNX_SAND_IN  int                 core,
      DNX_SAND_IN  uint32                 egress_tc,
      DNX_SAND_IN  uint32                 threshold_type,
      DNX_SAND_IN  JER2_ARAD_EGR_THRESH_INFO      *thresh_info
    );

int jer2_arad_egr_queuing_init_thresholds(int unit, int port_rate, int nof_priorities, int nof_channels, DNX_TMC_EGR_QUEUING_CGM_INIT_THRESHOLDS* cgm_init_thresholds);

#include <soc/dnx/legacy/SAND/Utils/sand_footer.h>


/* } __JER2_ARAD_EGR_QUEUING_INCLUDED__*/
#endif

