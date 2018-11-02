/* $Id: arad_scheduler_ports.h,v 1.7 Broadcom SDK $
 * $Copyright: (c) 2016 Broadcom.
 * Broadcom Proprietary and Confidential. All rights reserved.$
*/


#ifndef __ARAD_SCHEDULER_PORTS_H_INCLUDED__
/* { */
#define __ARAD_SCHEDULER_PORTS_H_INCLUDED__

/*************
 * INCLUDES  *
 *************/
/* { */
#include <soc/dpp/SAND/Utils/sand_header.h>

#include <soc/dpp/ARAD/arad_api_end2end_scheduler.h>
#include <soc/dpp/ARAD/arad_ports.h>
/* } */

/*************
 * DEFINES   *
 *************/
/* { */
#define ARAD_NOF_TCG_IN_BITS                        (3)
/* } */

/*************
 *  MACROS   *
 *************/
/* { */
#define ARAD_SCH_PORT_TCG_ID_GET(base_port_tc,tcg_ndx) \
   (ARAD_BASE_PORT_TC2PS(base_port_tc)*ARAD_NOF_TCGS_IN_PS + tcg_ndx)
/* } */

/*************
 * TYPE DEFS *
 *************/
/* { */
typedef struct
{
  /*
   *  End-to-end scheduler credit rate, in Kbps. Typically - a
   *  nominal port rate + scheduler speedup.
   */
  uint32 rate;
  /*
   *  End-to-end maximum burst.
   *  Maximum credit balance in Bytes, that the port can
   *  accumulate, indicating the burst size of the OFP. Range:
   *  0 - 0xFFFF.
   */
  uint32 max_burst;
} ARAD_SCH_PORT_PRIORITY_RATE_INFO;

typedef struct
{
  /*
   *  End-to-end scheduler credit rate, in Kbps. Typically - a
   *  nominal port rate + scheduler speedup.
   */
  uint32 rate;
  /*
   *  End-to-end maximum burst.
   *  Maximum credit balance in Bytes, that the port can
   *  accumulate, indicating the burst size of the OFP. Range:
   *  0 - 0xFFFF.
   */
  uint32 max_burst;
} ARAD_SCH_TCG_RATE_INFO;


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
*     arad_sch_port_sched_verify
* TYPE:
*   PROC
* DATE:
*   Oct 18 2007
* FUNCTION:
*     See arad_sch_port_sched_set
* INPUT:
*  SOC_SAND_IN  int                 unit -
*     Identifier of device to access.
*  SOC_SAND_IN  int                 core -
*     Identifier of core on device to access.
*  SOC_SAND_IN  ARAD_SCH_PORT_ID        port_ndx -
*     Port index (0-63).
*  SOC_SAND_IN  ARAD_SCH_PORT_INFO      *port_info -
*     Scheduler port configuration info.
* RETURNS:
*   OK or ERROR indication.
*********************************************************************/
uint32
  arad_sch_port_sched_verify(
    SOC_SAND_IN  int                 unit,
    SOC_SAND_IN  int                 core,
    SOC_SAND_IN  uint32              tm_port,
    SOC_SAND_IN  ARAD_SCH_PORT_INFO  *port_info
  );

/*********************************************************************
* NAME:
*     arad_sch_port_sched_set_unsafe
* TYPE:
*   PROC
* DATE:
*   Oct 18 2007
* FUNCTION:
*     Sets the scheduler-port state (enable/disable), and its
*     HR mode of operation (single or dual). The driver writes
*     to the following tables: Scheduler Enable Memory (SEM),
*     HR-Scheduler-Configuration (SHC), Flow Group Memory
*     (FGM)
* INPUT:
*  SOC_SAND_IN  int                 unit -
*     Identifier of device to access.
*  SOC_SAND_IN  ARAD_SCH_PORT_ID        port_ndx -
*     Port index (0-63).
*  SOC_SAND_IN  ARAD_SCH_PORT_INFO      *port_info -
*     Scheduler port configuration info.
* RETURNS:
*   OK or ERROR indication.
*********************************************************************/
uint32
  arad_sch_port_sched_set_unsafe(
    SOC_SAND_IN  int                 unit,
    SOC_SAND_IN  int                 core,
    SOC_SAND_IN  uint32              tm_port,
    SOC_SAND_IN  ARAD_SCH_PORT_INFO  *port_info
  );

/*********************************************************************
* NAME:
*     arad_sch_port_sched_get_unsafe
* TYPE:
*   PROC
* DATE:
*   Oct 18 2007
* FUNCTION:
*     See arad_sch_port_sched_set_unsafe
* INPUT:
*  SOC_SAND_IN  int                 unit -
*     Identifier of device to access.
*  SOC_SAND_IN  ARAD_SCH_PORT_ID        port_ndx -
*     Port index (0-63).
*  SOC_SAND_OUT  ARAD_SCH_PORT_INFO      *port_info -
*     Scheduler port configuration info.
* RETURNS:
*   OK or ERROR indication.
*********************************************************************/


uint32
  arad_sch_port_sched_get_unsafe(
    SOC_SAND_IN  int                 unit,
    SOC_SAND_IN  int                 core,
    SOC_SAND_IN  uint32              tm_port,
    SOC_SAND_OUT ARAD_SCH_PORT_INFO  *port_info
  );

/*********************************************************************
* NAME:
*     arad_sch_port_tcg_weight_set/get _unsafe
* TYPE:
*   PROC
* DATE:
*  
* FUNCTION:
*     Sets, for a specified TCG within a certain Port
*     its excess rate. Excess traffic is scheduled between other TCGs
*     according to a weighted fair queueing or strict priority policy. 
* INPUT:
*  SOC_SAND_IN  int                 unit -
*     Identifier of device to access.
*  SOC_SAND_IN  int                 core -
*     Identifier of core on device to access.
*  SOC_SAND_IN  ARAD_SCH_PORT_ID          port_id -
*     Port id, 0 - 255. Set invalid in case of invalid attributes.
*  SOC_SAND_IN  ARAD_TCG_NDX              tcg_ndx -
*     TCG index. 0-7.
*  SOC_SAND_IN  ARAD_SCH_TCG_WEIGHT      *tcg_weight -
*     TCG weight information.
* RETURNS:
*   OK or ERROR indication.
* REMARKS:
*   This function must only be called for eight priorities port.
*********************************************************************/
uint32
  arad_sch_port_tcg_weight_set_unsafe(
    SOC_SAND_IN  int                 unit,
    SOC_SAND_IN  int                 core,
    SOC_SAND_IN  uint32              tm_port,
    SOC_SAND_IN  ARAD_TCG_NDX        tcg_ndx,
    SOC_SAND_IN  ARAD_SCH_TCG_WEIGHT *tcg_weight
  );

uint32
  arad_sch_port_tcg_weight_get_unsafe(
    SOC_SAND_IN  int                 unit,
    SOC_SAND_IN  int                 core,
    SOC_SAND_IN  uint32              tm_port,
    SOC_SAND_IN  ARAD_TCG_NDX        tcg_ndx,
    SOC_SAND_OUT ARAD_SCH_TCG_WEIGHT *tcg_weight
  );

uint32
  arad_sch_port_tcg_weight_set_verify_unsafe(
    SOC_SAND_IN  int                       unit,
    SOC_SAND_IN  int                       core,
    SOC_SAND_IN  uint32                    tm_port,
    SOC_SAND_IN  ARAD_TCG_NDX              tcg_ndx,
    SOC_SAND_IN  ARAD_SCH_TCG_WEIGHT       *tcg_weight
  );

uint32
  arad_sch_port_tcg_weight_get_verify_unsafe(
    SOC_SAND_IN  int                 unit,
    SOC_SAND_IN  int                 core,
    SOC_SAND_IN  uint32              tm_port,
    SOC_SAND_IN  ARAD_TCG_NDX        tcg_ndx,
    SOC_SAND_OUT ARAD_SCH_TCG_WEIGHT *tcg_weight
  );

/*****************************************************
* NAME
*   arad_sch_port_hp_class_conf_set_unsafe
* TYPE:
*   PROC
* DATE:
*   31/10/2007
* FUNCTION:
*     See p21v_sch_port_hp_class_conf_set_set
* INPUT:
*   SOC_SAND_IN  int                      unit -
*     Identifier of device to access.
*   SOC_SAND_IN  ARAD_SCH_PORT_HP_CLASS_INFO  *hp_class_info -
*    A set of available configurations for port low flow control
* RETURNS:
*   OK or ERROR indication.
* REMARKS:
*    None.
*****************************************************/
uint32
  arad_sch_port_hp_class_conf_verify(
    SOC_SAND_IN  int                    unit,
    SOC_SAND_IN  ARAD_SCH_PORT_HP_CLASS_INFO  *hp_class_info
  );

/*****************************************************
* NAME
*   arad_sch_port_hp_class_conf_set_unsafe
* TYPE:
*   PROC
* DATE:
*   31/10/2007
* FUNCTION:
*   Sets the group of available configurations for high priority
*   hr class settings.
*   Out of 5 possible configurations, 4 are available at any time.
* INPUT:
*   SOC_SAND_IN  int                      unit -
*     Identifier of device to access.
*   SOC_SAND_IN  ARAD_SCH_PORT_HP_CLASS_INFO  *hp_class_info -
*    A set of available configurations for port low flow control
* RETURNS:
*   OK or ERROR indication.
* REMARKS:
*    None.
*****************************************************/
uint32
  arad_sch_port_hp_class_conf_set_unsafe(
    SOC_SAND_IN  int                    unit,
    SOC_SAND_IN  ARAD_SCH_PORT_HP_CLASS_INFO  *hp_class_info
  );

/*****************************************************
* NAME
*   arad_sch_port_hp_class_conf_set_unsafe
* TYPE:
*   PROC
* DATE:
*   31/10/2007
* FUNCTION:
*     See p21v_sch_port_hp_class_conf_set_set
* INPUT:
*   SOC_SAND_IN  int                      unit -
*     Identifier of device to access.
*   SOC_SAND_IN  ARAD_SCH_PORT_HP_CLASS_INFO  *hp_class_info -
*    A set of available configurations for port low flow control
* RETURNS:
*   OK or ERROR indication.
* REMARKS:
*    None.
*****************************************************/
uint32
  arad_sch_port_hp_class_conf_get_unsafe(
    SOC_SAND_IN  int                    unit,
    SOC_SAND_OUT  ARAD_SCH_PORT_HP_CLASS_INFO  *hp_class_info
  );

/*****************************************************
* NAME
*   arad_sch_hr_to_port_assign_set
* TYPE:
*   PROC
* DATE:
*   26/12/2007
* FUNCTION:
*   Assign HR scheduling element to port.
*   This will direct port credits to the HR.
* INPUT:
*   SOC_SAND_IN  ARAD_SCH_PORT_ID  port_ndx -
*     The index of the port to set.
*     Range: 0 - 79
*   SOC_SAND_IN  uint8           is_port_hr -
*     If TRUE, the HR will be assigned to the port.
*     Otherwise - unasigned.
*     HR that is not assigned to port can be used as
*     HR scheduler.
* RETURNS:
*   OK or ERROR indication.
* REMARKS:
*    None.
*****************************************************/
uint32
  arad_sch_hr_to_port_assign_set(
    SOC_SAND_IN  int           unit,
    SOC_SAND_IN  int           core,
    SOC_SAND_IN  uint32        tm_port,
    SOC_SAND_IN  uint8         is_port_hr
  );

/*****************************************************
* NAME
*   arad_sch_hr_to_port_assign_set
* TYPE:
*   PROC
* DATE:
*   26/12/2007
* FUNCTION:
*   Check if an HR scheduling element is assigned to port.
*   This will direct port credits to the HR.
* INPUT:
*   SOC_SAND_IN  ARAD_SCH_PORT_ID  port_ndx -
*     The index of the port to set.
*     Range: 0 - 79
*   SOC_SAND_OUT  uint8           is_port_hr -
*     If TRUE, the HR is assigned to the port.
*     Otherwise - unasigned.
*     HR that is not assigned to port can be used as
*     HR scheduler.
* RETURNS:
*   OK or ERROR indication.
* REMARKS:
*    None.
*****************************************************/
uint32
  arad_sch_hr_to_port_assign_get(
    SOC_SAND_IN  int           unit,
    SOC_SAND_IN  int           core,
    SOC_SAND_IN  uint32        tm_port,
    SOC_SAND_OUT uint8         *is_port_hr
  );

/*********************************************************************
* NAME:
*     arad_sch_se2port_tc_id_get_unsafe
* TYPE:
*   PROC
* DATE:
*   Oct 18 2007
* FUNCTION:
*     Calculates port id and TC given the appropriate scheduling
*     element id. 
* INPUT:
*  SOC_SAND_IN  ARAD_SCH_SE_ID          se_id -
*     flow id, 0 - 32K-1
*  SOC_SAND_IN  ARAD_SCH_PORT_ID        port_id -
*     Port id, 0 - 255. Set invalid in case of invalid attributes.
*  SOC_SAND_OUT  uint32              tc -
*     Egress TC, 0 - 7. 
* RETURNS:
*   OK or ERROR indication.
*********************************************************************/
uint32
  arad_sch_se2port_tc_id_get_unsafe(
    SOC_SAND_IN  int               unit,
    SOC_SAND_IN  int               core,
    SOC_SAND_IN  ARAD_SCH_SE_ID    se_id,
    SOC_SAND_OUT ARAD_SCH_PORT_ID  *port_id,
    SOC_SAND_OUT uint32            *tc 
  );

/*********************************************************************
* NAME:
*     arad_sch_port_tc2se_id_get_unsafe
* TYPE:
*   PROC
* DATE:
*   Oct 18 2007
* FUNCTION:
*     Calculates scheduling element id given the appropriate
*     port id and priority TC. 
* INPUT:
*  SOC_SAND_IN  ARAD_SCH_PORT_ID        port_id -
*     Port id, 0 - 255
*  SOC_SAND_IN  uint32               tc -
*     Egress TC, 0 - 7
* RETURNS:
*   OK or ERROR indication.
*********************************************************************/
uint32
  arad_sch_port_tc2se_id_get_unsafe(
    SOC_SAND_IN  int               unit,
    SOC_SAND_IN  int               core,
    SOC_SAND_IN  uint32            tm_port,
    SOC_SAND_IN  uint32            tc,
    SOC_SAND_OUT ARAD_SCH_SE_ID    *se_id
  );

/*********************************************************************
* NAME:
*     arad_sch_port_priority_shaper_rate_set_unsafe
* TYPE:
*   PROC
* DATE: 
*  
* FUNCTION:
*     Sets, for a specified port_priority 
*     its maximal credit rate. This API is
* INPUT:
*  SOC_SAND_IN  ARAD_SCH_PORT_ID        base_port_tc -
*     Base Port tc, 0 - 255
*  SOC_SAND_IN  uint32               priority_ndx -
*     Egress TC, 0 - 7
*  SOC_SAND_IN  ARAD_SCH_PORT_PRIORITY_RATE_INFO info -
*     Port priority rate information includes rate shaper and max burst
*  SOC_SAND_IN  ARAD_SCH_PORT_PRIORITY_RATE_INFO exact_info -
*     returns exact info
* RETURNS:
*   OK or ERROR indication.
*********************************************************************/
uint32
  arad_sch_port_priority_shaper_rate_set_unsafe(
    SOC_SAND_IN     int               unit,
    SOC_SAND_IN     int               core,
    SOC_SAND_IN     uint32            tm_port,
    SOC_SAND_IN     uint32            priority_ndx,
    SOC_SAND_IN     uint32            rate
  );

uint32
  arad_sch_port_priority_shaper_rate_get_unsafe(
    SOC_SAND_IN     int               unit,
    SOC_SAND_IN     int               core,
    SOC_SAND_IN     uint32            tm_port,
    SOC_SAND_IN     uint32            priority_ndx,    
    SOC_SAND_OUT    ARAD_SCH_PORT_PRIORITY_RATE_INFO *info
  );

uint32 
arad_sch_port_priority_shaper_max_burst_set_unsafe(
    SOC_SAND_IN     int                  unit,
    SOC_SAND_IN     int                  core,
    SOC_SAND_IN     uint32               tm_port,
    SOC_SAND_IN     uint32               priority_ndx,
    SOC_SAND_IN     uint32               burst
  );


uint32
  arad_sch_port_priority_shaper_hw_set_unsafe(
    SOC_SAND_IN     int               unit,
    SOC_SAND_IN     int               core
  );


/*********************************************************************
* NAME:
*     arad_sch_tcg_shaper_rate_set_unsafe
* TYPE:
*   PROC
* DATE: 
*  
* FUNCTION:
*     Sets, for a specified port_priority 
*     its maximal credit rate. This API is
* INPUT:
*  SOC_SAND_IN  ARAD_SCH_PORT_ID        base_port_tc -
*     Base Port tc, 0 - 255
*  SOC_SAND_IN  ARAD_TCG_NDX            tcg_ndx -
*     TCG, 0 - 7
*  SOC_SAND_IN  ARAD_SCH_TCG_RATE_INFO info -
*     TCG rate information includes rate shaper and max burst
*  SOC_SAND_IN  ARAD_SCH_TCG_RATE_INFO exact_info -
*     returns exact info
* RETURNS:
*   OK or ERROR indication.
*********************************************************************/
uint32
  arad_sch_tcg_shaper_rate_set_unsafe(
    SOC_SAND_IN     int               unit,
    SOC_SAND_IN     int               core,
    SOC_SAND_IN     uint32            tm_port,
    SOC_SAND_IN     ARAD_TCG_NDX      tcg_ndx,
    SOC_SAND_IN     int               rate
  );

uint32
  arad_sch_tcg_shaper_rate_get_unsafe(
    SOC_SAND_IN     int               unit,
    SOC_SAND_IN     int               core,
    SOC_SAND_IN     uint32            tm_port,
    SOC_SAND_IN     ARAD_TCG_NDX      tcg_ndx,    
    SOC_SAND_OUT    ARAD_SCH_TCG_RATE_INFO  *info
  );

uint32
arad_sch_tcg_shaper_max_burst_set_unsafe(
    SOC_SAND_IN     int                  unit,
    SOC_SAND_IN     int                  core,
    SOC_SAND_IN     uint32               tm_port,
    SOC_SAND_IN     ARAD_TCG_NDX         tcg_ndx,
    SOC_SAND_IN     uint32               burst
  );

/* } */

void
  arad_ARAD_SCH_PORT_PRIORITY_RATE_INFO_clear(
    SOC_SAND_OUT ARAD_SCH_PORT_PRIORITY_RATE_INFO *info
  );

void
  arad_ARAD_SCH_TCG_RATE_INFO_clear(
    SOC_SAND_OUT ARAD_SCH_TCG_RATE_INFO *info
  );

int 
arad_sch_e2e_interface_allocate(
    SOC_SAND_IN  int             unit,
    SOC_SAND_IN  soc_port_t      port
    );

int 
arad_sch_e2e_interface_deallocate(
    SOC_SAND_IN  int             unit,
    SOC_SAND_IN  soc_port_t      port
    );

int
  arad_sch_port_rate_kbits_per_sec_to_qaunta(
    SOC_SAND_IN       int       unit,
    SOC_SAND_IN       uint32    rate,     /* in Kbits/sec */
    SOC_SAND_IN       uint32    credit_div, /*REBOUNDED/ASSIGNED_CREDIT*/
    SOC_SAND_IN       uint32    ticks_per_sec,
    SOC_SAND_OUT      uint32*   quanta  /* in device clocks */
  );

int
  arad_sch_port_qunta_to_rate_kbits_per_sec(
    SOC_SAND_IN       int       unit,
    SOC_SAND_IN       uint32    quanta, /* in device clocks */
    SOC_SAND_IN       uint32    credit_div,  /*REBOUNDED/ASSIGNED_CREDIT*/
    SOC_SAND_IN       uint32    ticks_per_sec,
    SOC_SAND_OUT      uint32*   rate      /* in Kbits/sec */
  );

uint32
arad_sch_calendar_info_get(int unit, int core, int hr_calendar_num ,  int is_priority_rate_calendar ,
                          uint32 *credit_div, uint32 *nof_ticks, uint32 *quanta_nof_bits);

int
arad_sch_port_sched_min_bw_group_get(
    SOC_SAND_IN     int                  unit,
    SOC_SAND_IN     int                  core,
    SOC_SAND_OUT    uint32               *group
  );

int 
arad_sch_port_hr_group_get(
    SOC_SAND_IN     int                  unit,
    SOC_SAND_IN     int                  core,
    SOC_SAND_IN     uint32               tm_port,
    SOC_SAND_OUT    uint32               *group
  );
#include <soc/dpp/SAND/Utils/sand_footer.h>


/* } __ARAD_SCHEDULER_PORTS_H_INCLUDED__*/
#endif

