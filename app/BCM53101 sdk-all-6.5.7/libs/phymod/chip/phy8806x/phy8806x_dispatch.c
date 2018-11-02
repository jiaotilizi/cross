/*
 *         
 * $Id: phymod.xml,v 1.1.2.5 Broadcom SDK $
 * 
 * $Copyright: (c) 2016 Broadcom.
 * Broadcom Proprietary and Confidential. All rights reserved.$
 *         
 *     
 * DO NOT EDIT THIS FILE!
 *
 */

#include <phymod/phymod.h>
#include <phymod/phymod.h>
#include <phymod/phymod_dispatch.h>

#ifdef PHYMOD_PHY8806X_SUPPORT

#include <phymod/chip/phy8806x.h>


__phymod__dispatch__t__ phymod_phy8806x_driver = {

    phy8806x_core_identify,
    phy8806x_core_info_get,
    phy8806x_core_lane_map_set,
    phy8806x_core_lane_map_get,
    phy8806x_core_reset_set,
    phy8806x_core_reset_get,
    phy8806x_core_firmware_info_get,
    phy8806x_phy_firmware_core_config_set,
    phy8806x_phy_firmware_core_config_get,
    phy8806x_phy_firmware_lane_config_set,
    phy8806x_phy_firmware_lane_config_get,
    phy8806x_core_pll_sequencer_restart,
    phy8806x_core_wait_event,
    phy8806x_phy_rx_restart,
    phy8806x_phy_polarity_set,
    phy8806x_phy_polarity_get,
    phy8806x_phy_tx_set,
    phy8806x_phy_tx_get,
    phy8806x_phy_media_type_tx_get,
    phy8806x_phy_tx_override_set,
    phy8806x_phy_tx_override_get,
    phy8806x_phy_rx_set,
    phy8806x_phy_rx_get,
    NULL, /* phymod_phy_rx_adaptation_resume */
    phy8806x_phy_reset_set,
    phy8806x_phy_reset_get,
    phy8806x_phy_power_set,
    phy8806x_phy_power_get,
    NULL, /* phymod_phy_hg2_codec_control_set */
    NULL, /* phymod_phy_hg2_codec_control_get */
    phy8806x_phy_tx_lane_control_set,
    phy8806x_phy_tx_lane_control_get,
    phy8806x_phy_rx_lane_control_set,
    phy8806x_phy_rx_lane_control_get,
    phy8806x_phy_fec_enable_set,
    phy8806x_phy_fec_enable_get,
    phy8806x_phy_forced_speed_line_side_set,
    phy8806x_phy_forced_speed_line_side_get,
    phy8806x_phy_flow_control_mode_set,
    phy8806x_phy_flow_control_mode_get,
    phy8806x_phy_psm_cos_bmp_set,
    phy8806x_phy_psm_cos_bmp_get,
    NULL, /* phymod_phy_autoneg_oui_set */
    NULL, /* phymod_phy_autoneg_oui_get */
    phy8806x_phy_eee_set,
    phy8806x_phy_eee_get,
    phy8806x_phy_interface_config_set,
    phy8806x_phy_interface_config_get,
    phy8806x_phy_cl72_set,
    phy8806x_phy_cl72_get,
    phy8806x_phy_cl72_status_get,
    phy8806x_phy_autoneg_ability_set,
    phy8806x_phy_autoneg_ability_get,
    phy8806x_phy_autoneg_remote_ability_get,
    phy8806x_phy_autoneg_set,
    phy8806x_phy_autoneg_get,
    NULL, /* phymod_phy_autoneg_restart_set */
    phy8806x_phy_autoneg_status_get,
    phy8806x_core_init,
    phy8806x_phy_pll_multiplier_get,
    phy8806x_phy_init,
    phy8806x_phy_loopback_set,
    phy8806x_phy_loopback_get,
    phy8806x_phy_rx_pmd_locked_get,
    NULL, /* phymod_phy_rx_signal_detect_get */
    phy8806x_phy_link_status_get,
    NULL, /* phymod_phy_status_dump */
    phy8806x_phy_pcs_userspeed_set,
    phy8806x_phy_pcs_userspeed_get,
    phy8806x_phy_reg_read,
    phy8806x_phy_reg_write,
    phy8806x_phy_private_read,
    phy8806x_phy_private_write,
    NULL, /* phymod_phy_rev_id */
    NULL, /* phymod_phy_lane_cross_switch_map_set */
    NULL, /* phymod_phy_lane_cross_switch_map_get */
    NULL, /* phymod_phy_intr_enable_set */
    NULL, /* phymod_phy_intr_enable_get */
    NULL, /* phymod_phy_intr_status_get */
    NULL, /* phymod_phy_intr_status_clear */
    phy8806x_phy_i2c_read,
    phy8806x_phy_i2c_write,
    NULL, /* phymod_phy_gpio_config_set */
    NULL, /* phymod_phy_gpio_config_get */
    NULL, /* phymod_phy_gpio_pin_value_set */
    NULL, /* phymod_phy_gpio_pin_value_get */
    NULL, /* phymod_timesync_config_set */
    NULL, /* phymod_timesync_config_get */
    NULL, /* phymod_timesync_enable_set */
    NULL, /* phymod_timesync_enable_get */
    NULL, /* phymod_timesync_nco_addend_set */
    NULL, /* phymod_timesync_nco_addend_get */
    NULL, /* phymod_timesync_framesync_mode_set */
    NULL, /* phymod_timesync_framesync_mode_get */
    NULL, /* phymod_timesync_local_time_set */
    NULL, /* phymod_timesync_local_time_get */
    NULL, /* phymod_timesync_load_ctrl_set */
    NULL, /* phymod_timesync_load_ctrl_get */
    NULL, /* phymod_timesync_tx_timestamp_offset_set */
    NULL, /* phymod_timesync_tx_timestamp_offset_get */
    NULL, /* phymod_timesync_rx_timestamp_offset_set */
    NULL, /* phymod_timesync_rx_timestamp_offset_get */
    NULL, /* phymod_timesync_capture_timestamp_get */
    NULL, /* phymod_timesync_heartbeat_timestamp_get */
    NULL, /* phymod_timesync_do_sync */
    NULL, /* phymod_edc_config_set */
    NULL, /* phymod_edc_config_get */
    NULL, /* phymod_phy_core_mode_set */
    NULL, /* phymod_phy_core_mode_get */
    NULL, /* phymod_failover_mode_set */
    NULL, /* phymod_failover_mode_get */
    phy8806x_port_init,
    phy8806x_phy_autoneg_try_enable,
    phy8806x_debug_ether,
    NULL, /* phymod_phy_short_chn_mode_enable_set */
    NULL, /* phymod_phy_short_chn_mode_enable_get */
    phy8806x_port_enable_set,
    phy8806x_port_enable_get,
    NULL, /* phymod_phy_eye_margin_est_get */
    NULL, /* phymod_phy_multi_get */
    NULL, /* phymod_phy_rescal_set */
    NULL, /* phymod_phy_rescal_get */
    NULL, /* phymod_phy_sw_an_control_status_get */
    NULL, /* phymod_phy_sw_an_base_page_exchange_handler */
    NULL, /* phymod_phy_sw_an_lp_page_rdy_handler */
    NULL, /* phymod_phy_sw_an_advert_set */
    NULL, /* phymod_phy_sw_autoneg_enable */
};

#endif /* PHYMOD_PHY8806X_SUPPORT */
