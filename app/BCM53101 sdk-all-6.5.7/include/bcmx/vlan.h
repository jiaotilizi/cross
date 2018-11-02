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

#ifndef __BCMX_VLAN_H__
#define __BCMX_VLAN_H__

#include <bcm/types.h>
#include <bcmx/bcmx.h>
#include <bcmx/lplist.h>
#include <bcm/vlan.h>

typedef struct bcmx_vlan_data_s {
    bcm_vlan_t vlan_tag; 
    bcmx_lplist_t port_bitmap; 
    bcmx_lplist_t ut_port_bitmap; 
} bcmx_vlan_data_t;

typedef struct bcmx_vlan_block_s {
    bcmx_lplist_t known_multicast; 
    bcmx_lplist_t unknown_multicast; 
    bcmx_lplist_t unknown_unicast; 
    bcmx_lplist_t broadcast; 
} bcmx_vlan_block_t;

typedef bcm_vlan_port_t bcmx_vlan_port_t;

/* Initialize a VLAN block structure. */
extern void bcmx_vlan_block_t_init(
    bcmx_vlan_block_t *data);

/* Initialize the VLAN port structure. */
extern void bcmx_vlan_port_t_init(
    bcmx_vlan_port_t *vlan_port);

/* Allocate and configure a VLAN on the BCM device. */
extern int bcmx_vlan_create(
    bcm_vlan_t vid);

/* Deallocate VLAN from the BCM device. */
extern int bcmx_vlan_destroy(
    bcm_vlan_t vid);

/* Destroy all VLANs except the default VLAN. */
extern int bcmx_vlan_destroy_all(void);

/* Add ports to the specified vlan. */
extern int bcmx_vlan_port_add(
    bcm_vlan_t vid, 
    bcmx_lplist_t lplist, 
    bcmx_lplist_t ubmp);

/* Remove ports from a specified vlan. */
extern int bcmx_vlan_port_remove(
    bcm_vlan_t vid, 
    bcmx_lplist_t lplist);

/* Retrieves a list of the member ports of an existing VLAN. */
extern int bcmx_vlan_port_get(
    bcm_vlan_t vid, 
    bcmx_lplist_t *lplist, 
    bcmx_lplist_t *ubmp);

/* Get the default VLAN ID. */
extern int bcmx_vlan_default_get(
    bcm_vlan_t *vid_ptr);

/* Set the default VLAN ID. */
extern int bcmx_vlan_default_set(
    bcm_vlan_t vid);

/* Retrieve the VTABLE STG for the specified vlan. */
extern int bcmx_vlan_stg_get(
    bcm_vlan_t vid, 
    bcm_stg_t *stg_ptr);

/* Update the VTABLE STG for the specified vlan. */
extern int bcmx_vlan_stg_set(
    bcm_vlan_t vid, 
    bcm_stg_t stg);

/* Add a Gport to the specified vlan. */
extern int bcmx_vlan_gport_add(
    bcm_vlan_t vlan, 
    bcm_gport_t port, 
    int flags);

/* Remove a Gport from the specified vlan. */
extern int bcmx_vlan_gport_delete(
    bcm_vlan_t vlan, 
    bcm_gport_t port);

/* Remove all ports from the specified vlan. */
extern int bcmx_vlan_gport_delete_all(
    bcm_vlan_t vlan);

/* Get a Gport from the specified vlan. */
extern int bcmx_vlan_gport_get(
    bcm_vlan_t vlan, 
    bcm_gport_t port, 
    int *flags);

/* Get all Gports from the specified vlan. */
extern int bcmx_vlan_gport_get_all(
    bcm_vlan_t vlan, 
    int array_max, 
    bcm_gport_t *gport_array, 
    int *flags_array, 
    int *array_size);

/* Get or set the port's default VLAN tag actions. */
extern int bcmx_vlan_port_default_action_get(
    bcmx_lport_t port, 
    bcm_vlan_action_set_t *action);

/* Get or set the port's default VLAN tag actions. */
extern int bcmx_vlan_port_default_action_set(
    bcmx_lport_t port, 
    bcm_vlan_action_set_t *action);

/* Delete the port's default VLAN tag action. */
extern int bcmx_vlan_port_default_action_delete(
    bcmx_lport_t port);

/* Get or set the egress default VLAN tag actions. */
extern int bcmx_vlan_port_egress_default_action_get(
    bcmx_lport_t port, 
    bcm_vlan_action_set_t *action);

/* Get or set the egress default VLAN tag actions. */
extern int bcmx_vlan_port_egress_default_action_set(
    bcmx_lport_t port, 
    bcm_vlan_action_set_t *action);

/* Deletes the egress default VLAN tag actions. */
extern int bcmx_vlan_port_egress_default_action_delete(
    bcmx_lport_t port);

/* 
 * Add protocol based VLAN with specified action. If the entry already
 * exists, update the action.
 */
extern int bcmx_vlan_port_protocol_action_add(
    bcmx_lport_t port, 
    bcm_port_frametype_t frame, 
    bcm_port_ethertype_t ether, 
    bcm_vlan_action_set_t *action);

/* Get protocol based VLAN action. */
extern int bcmx_vlan_port_protocol_action_get(
    bcmx_lport_t port, 
    bcm_port_frametype_t frame, 
    bcm_port_ethertype_t ether, 
    bcm_vlan_action_set_t *action);

/* Delete protocol based VLAN action. */
extern int bcmx_vlan_port_protocol_action_delete(
    bcmx_lport_t port, 
    bcm_port_frametype_t frame, 
    bcm_port_ethertype_t ether);

/* Delete all protocol based VLAN actions. */
extern int bcmx_vlan_port_protocol_action_delete_all(
    bcmx_lport_t port);

/* 
 * Add an association from MAC address to VLAN, used  for VLAN tag
 *             assignment to untagged packets.
 */
extern int bcmx_vlan_mac_add(
    bcm_mac_t mac, 
    bcm_vlan_t vid, 
    int prio);

/* Remove an association from MAC address to VLAN. */
extern int bcmx_vlan_mac_delete(
    bcm_mac_t mac);

/* Remove all associations from MAC addresses to VLAN. */
extern int bcmx_vlan_mac_delete_all(void);

/* 
 * Add an association from MAC address to VLAN actions, which are
 *             used for VLAN tag/s assignment to untagged packets.
 */
extern int bcmx_vlan_mac_action_add(
    bcm_mac_t mac, 
    bcm_vlan_action_set_t *action);

/* 
 * Retrive an association from MAC address to VLAN actions, which
 *             are used for VLAN tag assignment to untagged packets.
 */
extern int bcmx_vlan_mac_action_get(
    bcm_mac_t mac, 
    bcm_vlan_action_set_t *action);

/* 
 * Remove an association from MAC address to VLAN actions, which
 *             are used for VLAN tag assignment to untagged packets.
 */
extern int bcmx_vlan_mac_action_delete(
    bcm_mac_t mac);

/* 
 * Remove all MAC addresses to VLAN actions associations.
 *             Mac to VLAN actions are used for VLAN tag assignment
 *             to untagged packets.
 */
extern int bcmx_vlan_mac_action_delete_all(void);

/* Add an entry to the VLAN Translation table. */
extern int bcmx_vlan_translate_add(
    bcmx_lport_t port, 
    bcm_vlan_t old_vid, 
    bcm_vlan_t new_vid, 
    int prio);

/* Add an entry to the VLAN Translation table. */
extern int bcmx_vlan_translate_get(
    bcmx_lport_t port, 
    bcm_vlan_t old_vid, 
    bcm_vlan_t *new_vid, 
    int *prio);

/* Delete an entry or entries from the VLAN Translation table. */
extern int bcmx_vlan_translate_delete(
    bcmx_lport_t port, 
    bcm_vlan_t old_vid);

/* Remove all entries from the VLAN Translation table. */
extern int bcmx_vlan_translate_delete_all(void);

/* Add an entry to the VLAN Translation table and assign VLAN actions. */
extern int bcmx_vlan_translate_action_add(
    bcm_gport_t port, 
    bcm_vlan_translate_key_t key_type, 
    bcm_vlan_t outer_vlan, 
    bcm_vlan_t inner_vlan, 
    bcm_vlan_action_set_t *action);

/* Get an entry to the VLAN Translation table and assign VLAN actions. */
extern int bcmx_vlan_translate_action_get(
    bcm_gport_t port, 
    bcm_vlan_translate_key_t key_type, 
    bcm_vlan_t outer_vlan, 
    bcm_vlan_t inner_vlan, 
    bcm_vlan_action_set_t *action);

/* Delete an entry from the VLAN Translation table. */
extern int bcmx_vlan_translate_action_delete(
    bcm_gport_t port, 
    bcm_vlan_translate_key_t key_type, 
    bcm_vlan_t outer_vlan, 
    bcm_vlan_t inner_vlan);

/* Add an entry to the egress VLAN Translation table. */
extern int bcmx_vlan_translate_egress_add(
    bcmx_lport_t port, 
    bcm_vlan_t old_vid, 
    bcm_vlan_t new_vid, 
    int prio);

/* Get an entry to the egress VLAN Translation table. */
extern int bcmx_vlan_translate_egress_get(
    bcmx_lport_t port, 
    bcm_vlan_t old_vid, 
    bcm_vlan_t *new_vid, 
    int *prio);

/* Remove an entry or entries from the VLAN egress Translation table. */
extern int bcmx_vlan_translate_egress_delete(
    bcmx_lport_t port, 
    bcm_vlan_t old_vid);

/* Remove all entries from the egress VLAN Translation table. */
extern int bcmx_vlan_translate_egress_delete_all(void);

/* 
 * Add an entry to the egress VLAN Translation table and assign VLAN
 * actions.
 */
extern int bcmx_vlan_translate_egress_action_add(
    int port_class, 
    bcm_vlan_t outer_vlan, 
    bcm_vlan_t inner_vlan, 
    bcm_vlan_action_set_t *action);

/* 
 * Get an entry to the egress VLAN Translation table and assign VLAN
 * actions.
 */
extern int bcmx_vlan_translate_egress_action_get(
    int port_class, 
    bcm_vlan_t outer_vlan, 
    bcm_vlan_t inner_vlan, 
    bcm_vlan_action_set_t *action);

/* Delete an entry from the egress VLAN Translation table. */
extern int bcmx_vlan_translate_egress_action_delete(
    int port_class, 
    bcm_vlan_t outer_vlan, 
    bcm_vlan_t inner_vlan);

/* Add an entry to the VLAN Translation table for double-tagging. */
extern int bcmx_vlan_dtag_add(
    bcmx_lport_t port, 
    bcm_vlan_t old_vid, 
    bcm_vlan_t new_vid, 
    int prio);

/* Get an entry to the VLAN Translation table for double-tagging. */
extern int bcmx_vlan_dtag_get(
    bcmx_lport_t port, 
    bcm_vlan_t old_vid, 
    bcm_vlan_t *new_vid, 
    int *prio);

/* Remove an entry from the VLAN Translation table for double-tagging. */
extern int bcmx_vlan_dtag_delete(
    bcmx_lport_t port, 
    bcm_vlan_t old_vid);

/* Remove all entries from the VLAN Translation table for double-tagging. */
extern int bcmx_vlan_dtag_delete_all(void);

/* Add a VLAN range to the VLAN Translation table. */
extern int bcmx_vlan_translate_range_add(
    bcmx_lport_t port, 
    bcm_vlan_t old_vid_low, 
    bcm_vlan_t old_vid_high, 
    bcm_vlan_t new_vid, 
    int int_prio);

/* Get a VLAN range to the VLAN Translation table. */
extern int bcmx_vlan_translate_range_get(
    bcmx_lport_t port, 
    bcm_vlan_t old_vid_low, 
    bcm_vlan_t old_vid_high, 
    bcm_vlan_t *new_vid, 
    int *int_prio);

/* Delete a VLAN range from the VLAN Translation table. */
extern int bcmx_vlan_translate_range_delete(
    bcmx_lport_t port, 
    bcm_vlan_t old_vid_low, 
    bcm_vlan_t old_vid_high);

/* Remove all VLAN ranges from the VLAN Translation table. */
extern int bcmx_vlan_translate_range_delete_all(void);

/* Add VLAN range to the VLAN Translation table for double-tagging. */
extern int bcmx_vlan_dtag_range_add(
    bcmx_lport_t port, 
    bcm_vlan_t old_vid_low, 
    bcm_vlan_t old_vid_high, 
    bcm_vlan_t new_vid, 
    int int_prio);

/* Get VLAN range to the VLAN Translation table for double-tagging. */
extern int bcmx_vlan_dtag_range_get(
    bcmx_lport_t port, 
    bcm_vlan_t old_vid_low, 
    bcm_vlan_t old_vid_high, 
    bcm_vlan_t *new_vid, 
    int *prio);

/* 
 * Remove a VLAN range from the VLAN Translation table for
 * double-tagging.
 */
extern int bcmx_vlan_dtag_range_delete(
    bcmx_lport_t port, 
    bcm_vlan_t old_vid_low, 
    bcm_vlan_t old_vid_high);

/* 
 * Remove all VLAN ranges from the VLAN Translation table for
 * double-tagging.
 */
extern int bcmx_vlan_dtag_range_delete_all(void);

extern int bcmx_vlan_translate_action_range_add(
    bcm_gport_t port, 
    bcm_vlan_t outer_vlan_low, 
    bcm_vlan_t outer_vlan_high, 
    bcm_vlan_t inner_vlan_low, 
    bcm_vlan_t inner_vlan_high, 
    bcm_vlan_action_set_t *action);

extern int bcmx_vlan_translate_action_range_get(
    bcm_gport_t port, 
    bcm_vlan_t outer_vlan_low, 
    bcm_vlan_t outer_vlan_high, 
    bcm_vlan_t inner_vlan_low, 
    bcm_vlan_t inner_vlan_high, 
    bcm_vlan_action_set_t *action);

extern int bcmx_vlan_translate_action_range_delete(
    bcm_gport_t port, 
    bcm_vlan_t outer_vlan_low, 
    bcm_vlan_t outer_vlan_high, 
    bcm_vlan_t inner_vlan_low, 
    bcm_vlan_t inner_vlan_high);

extern int bcmx_vlan_translate_action_range_delete_all(void);

/* 
 * Add an association from IP subnet to VLAN to use for assigning a VLAN
 * tag to untagged packets.
 */
extern int bcmx_vlan_ip_add(
    bcm_vlan_ip_t *vlan_ip);

/* Remove an association from IP subnet to VLAN. */
extern int bcmx_vlan_ip_delete(
    bcm_vlan_ip_t *vlan_ip);

/* Remove all associations from IP subnet to VLAN. */
extern int bcmx_vlan_ip_delete_all(void);

/* 
 * Add an association from IP subnet to VLAN actions to use for assigning
 * VLAN tag actions to untagged packets.
 */
extern int bcmx_vlan_ip_action_add(
    bcm_vlan_ip_t *vlan_ip, 
    bcm_vlan_action_set_t *action);

/* 
 * Get an association from IP subnet to VLAN actions to use for assigning
 * VLAN tag actions to untagged packets.
 */
extern int bcmx_vlan_ip_action_get(
    bcm_vlan_ip_t *vlan_ip, 
    bcm_vlan_action_set_t *action);

/* 
 * Delete an association from IP subnet to VLAN actions to use for
 * assigning VLAN tag actions to untagged packets.
 */
extern int bcmx_vlan_ip_action_delete(
    bcm_vlan_ip_t *vlan_ip);

/* 
 * Delete all associations from IP subnet to VLAN actions to use for
 * assigning VLAN tag actions to untagged packets.
 */
extern int bcmx_vlan_ip_action_delete_all(void);

/* Set/get miscellaneous VLAN-specific chip options. */
extern int bcmx_vlan_control_get(
    bcm_vlan_control_t type, 
    int *arg);

/* Set/get miscellaneous VLAN-specific chip options. */
extern int bcmx_vlan_control_set(
    bcm_vlan_control_t type, 
    int arg);

/* Set/get miscellaneous port-specific VLAN options. */
extern int bcmx_vlan_control_port_get(
    bcmx_lport_t port, 
    bcm_vlan_control_port_t type, 
    int *arg);

/* Set/get miscellaneous port-specific VLAN options. */
extern int bcmx_vlan_control_port_set(
    bcmx_lport_t port, 
    bcm_vlan_control_port_t type, 
    int arg);

/* Set or retrieve the current vlan multicast flood behavior. */
extern int bcmx_vlan_mcast_flood_get(
    bcm_vlan_t vlan, 
    bcm_vlan_mcast_flood_t *mode);

/* Set or retrieve the current vlan multicast flood behavior. */
extern int bcmx_vlan_mcast_flood_set(
    bcm_vlan_t vlan, 
    bcm_vlan_mcast_flood_t mode);

/* Set or retrieve current vlan properties. */
extern int bcmx_vlan_control_vlan_get(
    bcm_vlan_t vlan, 
    bcm_vlan_control_vlan_t *control);

/* Set or retrieve current vlan properties. */
extern int bcmx_vlan_control_vlan_set(
    bcm_vlan_t vlan, 
    bcm_vlan_control_vlan_t control);

/* Set vlan_control_vlan flags over a vlan vector. */
extern int bcmx_vlan_vector_flags_set(
    bcm_vlan_vector_t vlan_vector, 
    uint32 flags_mask, 
    uint32 flags_value);

/* Retrieve vlan block properties. */
extern int bcmx_vlan_block_get(
    bcm_vlan_t vlan, 
    bcmx_vlan_block_t *vlan_block);

/* Set vlan block properties. */
extern int bcmx_vlan_block_set(
    bcm_vlan_t vlan, 
    bcmx_vlan_block_t *vlan_block);

extern int bcmx_vlan_cross_connect_add(
    bcm_vlan_t outer_vlan, 
    bcm_vlan_t inner_vlan, 
    bcm_gport_t port_1, 
    bcm_gport_t port_2);

extern int bcmx_vlan_cross_connect_delete(
    bcm_vlan_t outer_vlan, 
    bcm_vlan_t inner_vlan);

extern int bcmx_vlan_cross_connect_delete_all(void);

/* Extract per-VLAN statistics from the chip. */
extern int bcmx_vlan_stat_get(
    bcm_vlan_t vlan, 
    bcm_cos_t cos, 
    bcm_vlan_stat_t stat, 
    uint64 *val);

/* Extract per-VLAN statistics from the chip. */
extern int bcmx_vlan_stat_get32(
    bcm_vlan_t vlan, 
    bcm_cos_t cos, 
    bcm_vlan_stat_t stat, 
    uint32 *val);

/* 
 * Set the specified statistic to the indicated value for the specified
 * VLAN.
 */
extern int bcmx_vlan_stat_set(
    bcm_vlan_t vlan, 
    bcm_cos_t cos, 
    bcm_vlan_stat_t stat, 
    uint64 val);

/* 
 * Set the specified statistic to the indicated value for the specified
 * VLAN.
 */
extern int bcmx_vlan_stat_set32(
    bcm_vlan_t vlan, 
    bcm_cos_t cos, 
    bcm_vlan_stat_t stat, 
    uint32 val);

/* Enable/disable collection of statistics on the indicated VLAN. */
extern int bcmx_vlan_stat_enable_set(
    bcm_vlan_t vlan, 
    int enable);

/* Get 64-bit counter value for multiple VLAN statistic types. */
extern int bcmx_vlan_stat_multi_get(
    bcm_vlan_t vlan, 
    bcm_cos_t cos, 
    int nstat, 
    bcm_vlan_stat_t *stat_arr, 
    uint64 *value_arr);

/* Get lower 32-bit counter value for multiple VLAN statistic types. */
extern int bcmx_vlan_stat_multi_get32(
    bcm_vlan_t vlan, 
    bcm_cos_t cos, 
    int nstat, 
    bcm_vlan_stat_t *stat_arr, 
    uint32 *value_arr);

/* Set 64-bit counter value for multiple VLAN statistic types. */
extern int bcmx_vlan_stat_multi_set(
    bcm_vlan_t vlan, 
    bcm_cos_t cos, 
    int nstat, 
    bcm_vlan_stat_t *stat_arr, 
    uint64 *value_arr);

/* Set lower 32-bit counter value for multiple VLAN statistic types. */
extern int bcmx_vlan_stat_multi_set32(
    bcm_vlan_t vlan, 
    bcm_cos_t cos, 
    int nstat, 
    bcm_vlan_stat_t *stat_arr, 
    uint32 *value_arr);

/* Extract ingress VLAN translation statistics from the chip. */
extern int bcmx_vlan_translate_stat_get(
    bcm_gport_t port, 
    bcm_vlan_translate_key_t key_type, 
    bcm_vlan_t outer_vlan, 
    bcm_vlan_t inner_vlan, 
    bcm_vlan_stat_t stat, 
    uint64 *val);

/* Extract ingress VLAN translation statistics from the chip. */
extern int bcmx_vlan_translate_stat_get32(
    bcm_gport_t port, 
    bcm_vlan_translate_key_t key_type, 
    bcm_vlan_t outer_vlan, 
    bcm_vlan_t inner_vlan, 
    bcm_vlan_stat_t stat, 
    uint32 *val);

/* 
 * Set the specified statistic to the indicated value for the specified
 * ingress VLAN translation.
 */
extern int bcmx_vlan_translate_stat_set(
    bcm_gport_t port, 
    bcm_vlan_translate_key_t key_type, 
    bcm_vlan_t outer_vlan, 
    bcm_vlan_t inner_vlan, 
    bcm_vlan_stat_t stat, 
    uint64 val);

/* 
 * Set the specified statistic to the indicated value for the specified
 * ingress VLAN translation.
 */
extern int bcmx_vlan_translate_stat_set32(
    bcm_gport_t port, 
    bcm_vlan_translate_key_t key_type, 
    bcm_vlan_t outer_vlan, 
    bcm_vlan_t inner_vlan, 
    bcm_vlan_stat_t stat, 
    uint32 val);

/* 
 * Enable/disable collection of statistics on the indicated ingress VLAN
 * translation.
 */
extern int bcmx_vlan_translate_stat_enable_set(
    bcm_gport_t port, 
    bcm_vlan_translate_key_t key_type, 
    bcm_vlan_t outer_vlan, 
    bcm_vlan_t inner_vlan, 
    int enable);

/* 
 * Get 64-bit counter value for multiple ingress VLAN translation
 * statistic types.
 */
extern int bcmx_vlan_translate_stat_multi_get(
    bcm_gport_t port, 
    bcm_vlan_translate_key_t key_type, 
    bcm_vlan_t outer_vlan, 
    bcm_vlan_t inner_vlan, 
    int nstat, 
    bcm_vlan_stat_t *stat_arr, 
    uint64 *value_arr);

/* 
 * Get lower 32-bit counter value for multiple ingress VLAN translation
 * statistic types.
 */
extern int bcmx_vlan_translate_stat_multi_get32(
    bcm_gport_t port, 
    bcm_vlan_translate_key_t key_type, 
    bcm_vlan_t outer_vlan, 
    bcm_vlan_t inner_vlan, 
    int nstat, 
    bcm_vlan_stat_t *stat_arr, 
    uint32 *value_arr);

/* 
 * Set 64-bit counter value for multiple ingress VLAN translation
 * statistic types.
 */
extern int bcmx_vlan_translate_stat_multi_set(
    bcm_gport_t port, 
    bcm_vlan_translate_key_t key_type, 
    bcm_vlan_t outer_vlan, 
    bcm_vlan_t inner_vlan, 
    int nstat, 
    bcm_vlan_stat_t *stat_arr, 
    uint64 *value_arr);

/* 
 * Set lower 32-bit counter value for multiple ingress VLAN translation
 * statistic types.
 */
extern int bcmx_vlan_translate_stat_multi_set32(
    bcm_gport_t port, 
    bcm_vlan_translate_key_t key_type, 
    bcm_vlan_t outer_vlan, 
    bcm_vlan_t inner_vlan, 
    int nstat, 
    bcm_vlan_stat_t *stat_arr, 
    uint32 *value_arr);

/* Extract egress VLAN translation statistics from the chip. */
extern int bcmx_vlan_translate_egress_stat_get(
    int port_class, 
    bcm_vlan_t outer_vlan, 
    bcm_vlan_t inner_vlan, 
    bcm_vlan_stat_t stat, 
    uint64 *val);

/* Extract egress VLAN translation statistics from the chip. */
extern int bcmx_vlan_translate_egress_stat_get32(
    int port_class, 
    bcm_vlan_t outer_vlan, 
    bcm_vlan_t inner_vlan, 
    bcm_vlan_stat_t stat, 
    uint32 *val);

/* 
 * Set the specified statistic to the indicated value for the specified
 * egress VLAN translation.
 */
extern int bcmx_vlan_translate_egress_stat_set(
    int port_class, 
    bcm_vlan_t outer_vlan, 
    bcm_vlan_t inner_vlan, 
    bcm_vlan_stat_t stat, 
    uint64 val);

/* 
 * Set the specified statistic to the indicated value for the specified
 * egress VLAN translation.
 */
extern int bcmx_vlan_translate_egress_stat_set32(
    int port_class, 
    bcm_vlan_t outer_vlan, 
    bcm_vlan_t inner_vlan, 
    bcm_vlan_stat_t stat, 
    uint32 val);

/* 
 * Enable/disable collection of statistics on the indicated egress VLAN
 * translation.
 */
extern int bcmx_vlan_translate_egress_stat_enable_set(
    int port_class, 
    bcm_vlan_t outer_vlan, 
    bcm_vlan_t inner_vlan, 
    int enable);

/* 
 * Get 64-bit counter value for multiple egress VLAN translation
 * statistic types.
 */
extern int bcmx_vlan_translate_egress_stat_multi_get(
    int port_class, 
    bcm_vlan_t outer_vlan, 
    bcm_vlan_t inner_vlan, 
    int nstat, 
    bcm_vlan_stat_t *stat_arr, 
    uint64 *value_arr);

/* 
 * Get lower 32-bit counter value for multiple egress VLAN translation
 * statistic types.
 */
extern int bcmx_vlan_translate_egress_stat_multi_get32(
    int port_class, 
    bcm_vlan_t outer_vlan, 
    bcm_vlan_t inner_vlan, 
    int nstat, 
    bcm_vlan_stat_t *stat_arr, 
    uint32 *value_arr);

/* 
 * Set 64-bit counter value for multiple egress VLAN translation
 * statistic types.
 */
extern int bcmx_vlan_translate_egress_stat_multi_set(
    int port_class, 
    bcm_vlan_t outer_vlan, 
    bcm_vlan_t inner_vlan, 
    int nstat, 
    bcm_vlan_stat_t *stat_arr, 
    uint64 *value_arr);

/* 
 * Set lower 32-bit counter value for multiple egress VLAN translation
 * statistic types.
 */
extern int bcmx_vlan_translate_egress_stat_multi_set32(
    int port_class, 
    bcm_vlan_t outer_vlan, 
    bcm_vlan_t inner_vlan, 
    int nstat, 
    bcm_vlan_stat_t *stat_arr, 
    uint32 *value_arr);

/* Create a VLAN queue map entry. */
extern int bcmx_vlan_queue_map_create(
    uint32 flags, 
    int *qmid);

/* Delete a VLAN queue map entry. */
extern int bcmx_vlan_queue_map_destroy(
    int qmid);

/* Delete all VLAN queue map entries. */
extern int bcmx_vlan_queue_map_destroy_all(void);

/* Set a VLAN queue map entry. */
extern int bcmx_vlan_queue_map_set(
    int qmid, 
    int pkt_pri, 
    int cfi, 
    int queue, 
    int color);

/* Get a VLAN queue map entry. */
extern int bcmx_vlan_queue_map_get(
    int qmid, 
    int pkt_pri, 
    int cfi, 
    int *queue, 
    int *color);

/* Attach a queue map object to a VLAN or VFI. */
extern int bcmx_vlan_queue_map_attach(
    bcm_vlan_t vlan, 
    int qmid);

/* Get the queue map object which is attached to a VLAN or VFI. */
extern int bcmx_vlan_queue_map_attach_get(
    bcm_vlan_t vlan, 
    int *qmid);

/* Detach a queue map object from a VLAN or VFI. */
extern int bcmx_vlan_queue_map_detach(
    bcm_vlan_t vlan);

/* Detach queue map objects from all VLAN or VFI. */
extern int bcmx_vlan_queue_map_detach_all(void);

/* 
 * Create a layer 2 logical port.  Places the ID in the logical port
 * descriptor if WITH_ID flag is not provided, uses the ID in the logical
 * port descriptor if WITH_ID flag specified.
 */
extern int bcmx_vlan_port_create(
    bcmx_vlan_port_t *vlan_port);

/* Destroy a layer 2 logical port. */
extern int bcmx_vlan_port_destroy(
    bcm_gport_t gport);

/* Get/find a layer 2 logical port given the GPORT id or match criteria. */
extern int bcmx_vlan_port_find(
    bcmx_vlan_port_t *vlan_port);

#endif /* __BCMX_VLAN_H__ */
