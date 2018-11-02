/*
 * $Id: $
 * 
 * $Copyright: (c) 2016 Broadcom.
 * Broadcom Proprietary and Confidential. All rights reserved.$
 * 
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated.
 * Edits to this file will be lost when it is regenerated.
 */

#ifndef __BCM_QOS_H__
#define __BCM_QOS_H__

#include <bcm/types.h>
#include <bcm/multicast.h>
#include <bcm/l3.h>

/* QoS Configuration Flags. */
#define BCM_QOS_MAP_WITH_ID             0x0001     
#define BCM_QOS_MAP_REPLACE             0x0002     
#define BCM_QOS_MAP_L2                  0x0004     
#define BCM_QOS_MAP_L2_OUTER_TAG        BCM_QOS_MAP_L2 
#define BCM_QOS_MAP_L2_INNER_TAG        0x0008     
#define BCM_QOS_MAP_L2_UNTAGGED         0x0010     
#define BCM_QOS_MAP_L2_VLAN_PCP         0x0020     
#define BCM_QOS_MAP_L3                  0x0040     
#define BCM_QOS_MAP_IPV4                BCM_QOS_MAP_L3 
#define BCM_QOS_MAP_IPV6                0x0080     
#define BCM_QOS_MAP_MPLS                0x0100     
#define BCM_QOS_MAP_ENCAP               0x0200     
#define BCM_QOS_MAP_INGRESS             0x0400     
#define BCM_QOS_MAP_EGRESS              0x0800     
#define BCM_QOS_MAP_MPLS_ELSP           0x1000     
#define BCM_QOS_MAP_MIM_ITAG            0x2000     
#define BCM_QOS_MAP_QUEUE               0x4000     
#define BCM_QOS_MAP_POLICER             0x8000     
#define BCM_QOS_MAP_PACKET_INVALID      0x10000    
#define BCM_QOS_MAP_IGNORE_OFFSET       0x20000    
#define BCM_QOS_MAP_OPCODE              0x40000    
#define BCM_QOS_MAP_L2_ETAG             0x80000    
#define BCM_QOS_MAP_L2_VLAN_ETAG        0x100000   
#define BCM_QOS_MAP_MPLS_PHP            0x200000   
#define BCM_QOS_MAP_SUBPORT             0x400000   
#define BCM_QOS_MAP_L3_L2               0x800000   
#define BCM_QOS_MAP_VFT                 0x1000000  
#define BCM_QOS_MAP_VSAN                0x2000000  
#define BCM_QOS_MAP_OAM_PCP             0x4000000  
#define BCM_QOS_MAP_OAM_INTPRI          0x8000000  
#define BCM_QOS_MAP_OAM_OUTER_VLAN_PCP  0x10000000 
#define BCM_QOS_MAP_OAM_INNER_VLAN_PCP  0x20000000 
#define BCM_QOS_MAP_OAM_MPLS_EXP        0x40000000 
#define BCM_QOS_MAP_REPLICATION         0x80000000 
#define BCM_QOS_MAP_MIML                BCM_QOS_MAP_MIM_ITAG 
#define BCM_QOS_MAP_ENCAP_INTPRI_COLOR  BCM_QOS_MAP_VFT 

/* QoS Map structure */
typedef struct bcm_qos_map_s {
    uint8 pkt_pri;              /* Packet priority */
    uint8 pkt_cfi;              /* Packet CFI */
    int dscp;                   /* Packet DSCP */
    int exp;                    /* Packet EXP */
    int int_pri;                /* Internal priority */
    bcm_color_t color;          /* Color */
    int remark_int_pri;         /* (internal) remarking priority */
    bcm_color_t remark_color;   /* (internal) remark color */
    int policer_offset;         /* Offset based on pri/cos to fetch a policer */
    int queue_offset;           /* Offset based on int_pri to fetch cosq for
                                   subscriber ports */
    int port_offset;            /* Offset based on port connection for indexing
                                   into the action table */
    uint8 etag_pcp;             /* ETAG PCP field */
    uint8 etag_de;              /* ETAG DE field */
    int counter_offset;         /* Offset based on priority for indexing into
                                   the loss measurement counter table */
    int inherited_dscp_exp;     /* Inherited DSCP EXP value */
} bcm_qos_map_t;

/* Initialize the QoS Map structure. */
extern void bcm_qos_map_t_init(
    bcm_qos_map_t *qos_map);

#ifndef BCM_HIDE_DISPATCHABLE

/* Initialize the BCM QoS subsystem. */
extern int bcm_qos_init(
    int unit);

/* Detach the QoS software module. */
extern int bcm_qos_detach(
    int unit);

/* bcm_qos_map_create */
extern int bcm_qos_map_create(
    int unit, 
    uint32 flags, 
    int *map_id);

/* bcm_qos_map_destroy */
extern int bcm_qos_map_destroy(
    int unit, 
    int map_id);

/* bcm_qos_map_add */
extern int bcm_qos_map_add(
    int unit, 
    uint32 flags, 
    bcm_qos_map_t *map, 
    int map_id);

/* bcm_qos_map_multi_get */
extern int bcm_qos_map_multi_get(
    int unit, 
    uint32 flags, 
    int map_id, 
    int array_size, 
    bcm_qos_map_t *array, 
    int *array_count);

/* bcm_qos_map_delete */
extern int bcm_qos_map_delete(
    int unit, 
    uint32 flags, 
    bcm_qos_map_t *map, 
    int map_id);

/* bcm_qos_port_map_set */
extern int bcm_qos_port_map_set(
    int unit, 
    bcm_gport_t port, 
    int ing_map, 
    int egr_map);

/* bcm_qos_port_map_type_get */
extern int bcm_qos_port_map_type_get(
    int unit, 
    bcm_gport_t port, 
    uint32 flags, 
    int *map_id);

/* bcm_qos_port_map_get */
extern int bcm_qos_port_map_get(
    int unit, 
    bcm_gport_t port, 
    int *ing_map, 
    int *egr_map);

/* bcm_qos_port_vlan_map_set */
extern int bcm_qos_port_vlan_map_set(
    int unit, 
    bcm_port_t port, 
    bcm_vlan_t vid, 
    int ing_map, 
    int egr_map);

/* bcm_qos_port_vlan_map_get */
extern int bcm_qos_port_vlan_map_get(
    int unit, 
    bcm_port_t port, 
    bcm_vlan_t vid, 
    int *ing_map, 
    int *egr_map);

/* bcm_qos_multi_get */
extern int bcm_qos_multi_get(
    int unit, 
    int array_size, 
    int *map_ids_array, 
    int *flags_array, 
    int *array_count);

#endif /* BCM_HIDE_DISPATCHABLE */

#endif /* __BCM_QOS_H__ */
