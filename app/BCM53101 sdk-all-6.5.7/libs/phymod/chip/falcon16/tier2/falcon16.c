/*
 *         
 * $Id: phymod.xml,v 1.1.2.5 Broadcom SDK $
 * 
 * $Copyright: (c) 2016 Broadcom.
 * Broadcom Proprietary and Confidential. All rights reserved.$
 *         
 *     
 */

#include <phymod/phymod.h>
#include <phymod/phymod_util.h>
#include <phymod/phymod_acc.h>
#include <phymod/phymod_dispatch.h>
#include <phymod/chip/bcmi_tscf_16nm_xgxs_defs.h>

#include "../tier1/src/falcon16_cfg_seq.h"
#include "../tier1/include/falcon16_tsc_enum.h"
#include "../tier1/include/falcon16_tsc_common.h"
#include "../tier1/include/falcon16_tsc_interface.h"
#include "../tier1/include/falcon16_tsc_dependencies.h"

#define FALCON16_ID0           0
#define FALCON16_ID1           0
#define FALCON16_MODEL         0x1b 
#define TSCF16_PHY_ALL_LANES   0xf
#define FALCON16_PMD_CRC_UCODE 1


#define TSCF16_CORE_TO_PHY_ACCESS(_phy_access, _core_access) \
    do{\
        PHYMOD_MEMCPY(&(_phy_access)->access, &(_core_access)->access, sizeof((_phy_access)->access));\
        (_phy_access)->type           = (_core_access)->type; \
        (_phy_access)->port_loc       = (_core_access)->port_loc; \
        (_phy_access)->device_op_mode = (_core_access)->device_op_mode; \
        (_phy_access)->access.lane_mask = TSCF16_PHY_ALL_LANES; \
    }while(0) 


#define TSCF16_NOF_DFES           9
#define TSCF16_NOF_LANES_IN_CORE  4 
extern unsigned char falcon16_ucode[];
extern unsigned short falcon16_ucode_len;
extern unsigned short falcon16_ucode_crc;


int falcon16_core_identify(const phymod_core_access_t* core, uint32_t core_id, uint32_t* is_identified)
{
    int ioerr = 0;
    const phymod_access_t *pm_acc = &core->access;
    uint32_t id2 = 0;
    uint32_t id3 = 0;
    falcon16_rev_id0_t rev_id0;
    falcon16_rev_id1_t rev_id1;
    *is_identified = 0;    
    
    if (core_id == 0){
        ioerr += PHYMOD_BUS_READ(pm_acc, 2, &id2);
        ioerr += PHYMOD_BUS_READ(pm_acc, 3, &id3);
    } else {
        id2 = (core_id >> 16) & 0xffff;
        id3 = core_id & 0xffff;
    }
        
    if (id2 == FALCON16_ID0 && id3 == FALCON16_ID1) {
        PHYMOD_IF_ERR_RETURN(falcon16_tsc_identify(pm_acc, &rev_id0, &rev_id1) );
        if (rev_id0.revid_model == FALCON16_MODEL){
            *is_identified = 1;
        }
    }
    return ioerr ? PHYMOD_E_IO : PHYMOD_E_NONE;

}


int falcon16_core_info_get(const phymod_core_access_t* core, phymod_core_info_t* info)
{
    info->core_version = phymodCoreVersionFalconA0;
    info->serdes_id = 0;        
    info->phy_id0 = 0;        
    info->phy_id1 = 0;        
        
    return PHYMOD_E_NONE;
    
}


int falcon16_core_lane_map_set(const phymod_core_access_t* core, const phymod_lane_map_t* lane_map)
{
         
        
    return PHYMOD_E_NONE;
    
}

int falcon16_core_lane_map_get(const phymod_core_access_t* core, phymod_lane_map_t* lane_map)
{
#if 0
    int lane;    
    uint32_t pmd_swap = 0; 

    PHYMOD_IF_ERR_RETURN(falcon16_pmd_lane_swap_tx_get(&core->access, &pmd_swap));
    for (lane = 0; lane < TSCF16_NOF_LANES_IN_CORE; lane++){
        lane_map->lane_map_tx[lane] = (pmd_swap >> (lane*4)) & 0x3;
        lane_map->lane_map_rx[lane] = lane;
    }        
    lane_map->num_of_lanes = TSCF16_NOF_LANES_IN_CORE;
#endif
    return PHYMOD_E_NONE;
    
}


int falcon16_core_reset_set(const phymod_core_access_t* core, phymod_reset_mode_t reset_mode, phymod_reset_direction_t direction)
{
    
    PHYMOD_DEBUG_ERROR(("This function is NOT SUPPORTED!! (falcon16_core_reset_set)\n"));   
        
    return PHYMOD_E_NONE;
    
}

int falcon16_core_reset_get(const phymod_core_access_t* core, phymod_reset_mode_t reset_mode, phymod_reset_direction_t* direction)
{
        
    PHYMOD_DEBUG_ERROR(("This function is NOT SUPPORTED!! (falcon16_core_reset_get)\n"));   
        
    return PHYMOD_E_NONE;
    
}


int falcon16_core_firmware_info_get(const phymod_core_access_t* core, phymod_core_firmware_info_t* fw_info)
{
        
    PHYMOD_DEBUG_ERROR(("This function is NOT SUPPORTED!! (falcon16_core_firmware_info_get)\n"));   
        
    return PHYMOD_E_NONE;
    
}


/* load tscf fw. the fw_loader parameter is valid just for external fw load*/
STATIC
int _falcon16_core_firmware_load(const phymod_core_access_t* core, const phymod_core_init_config_t* init_config)
{
    int wait;

    switch(init_config->firmware_load_method){
        case phymodFirmwareLoadMethodInternal:
            PHYMOD_IF_ERR_RETURN(falcon16_tsc_ucode_mdio_load(&core->access, falcon16_ucode, falcon16_ucode_len));
            break;
        case phymodFirmwareLoadMethodExternal:
            if(!PHYMOD_CORE_INIT_F_RESUME_AFTER_FW_LOAD_GET(init_config)) {
                PHYMOD_NULL_CHECK(init_config->firmware_loader);
                PHYMOD_IF_ERR_RETURN(falcon16_tsc_ucode_init(&core->access));
                if(PHYMOD_CORE_INIT_F_UNTIL_FW_LOAD_GET(init_config)) {
                    wait = 0;
                } else {
                    wait = 1;
                }
                PHYMOD_IF_ERR_RETURN(falcon16_pram_firmware_enable(&core->access, 1, wait));

                if(PHYMOD_CORE_INIT_F_UNTIL_FW_LOAD_GET(init_config)) {
                    return PHYMOD_E_NONE;
                }

                PHYMOD_IF_ERR_RETURN(init_config->firmware_loader(core, falcon16_ucode_len, falcon16_ucode));
            }
            PHYMOD_IF_ERR_RETURN(falcon16_pram_firmware_enable(&core->access, 0, 0));
            break;
        case phymodFirmwareLoadMethodNone:
            break;
        default:
            PHYMOD_RETURN_WITH_ERR(PHYMOD_E_CONFIG, (_PHYMOD_MSG("illegal fw load method %u"), init_config->firmware_load_method));
    }

    if(init_config->firmware_load_method != phymodFirmwareLoadMethodNone){
        /*PHYMOD_IF_ERR_RETURN(tscf16_core_firmware_info_get(core, &actual_fw));
        if((falcon16_ucode_crc != actual_fw.fw_crc) || (falcon16_ucode_ver != actual_fw.fw_version)){
            PHYMOD_RETURN_WITH_ERR(PHYMOD_E_CONFIG, (_PHYMOD_MSG("fw load validation was failed")));
        } */
    }

    return PHYMOD_E_NONE;
}

        
int falcon16_phy_firmware_core_config_set(const phymod_phy_access_t* phy, phymod_firmware_core_config_t fw_core_config)
{
    struct falcon16_tsc_uc_core_config_st serdes_firmware_core_config;
    uint32_t is_write_disabled;     
        
    PHYMOD_IF_ERR_RETURN(PHYMOD_IS_WRITE_DISABLED(&phy->access, &is_write_disabled));
    if (is_write_disabled){
        return PHYMOD_E_NONE;
    }    

    PHYMOD_MEMSET(&serdes_firmware_core_config, 0, sizeof(serdes_firmware_core_config));
   /* serdes_firmware_core_config.field.core_cfg_from_pcs = fw_core_config.CoreConfigFromPCS;
    serdes_firmware_core_config.field.vco_rate = fw_core_config.VcoRate;
    PHYMOD_IF_ERR_RETURN(falcon16_tsc_uc_core_config(&phy->access, serdes_firmware_core_config));*/ 
    PHYMOD_IF_ERR_RETURN(falcon16_tsc_set_core_config_from_pcs(&phy->access, fw_core_config.CoreConfigFromPCS));
  
    return PHYMOD_E_NONE;
    
}

int falcon16_phy_firmware_core_config_get(const phymod_phy_access_t* phy, phymod_firmware_core_config_t* fw_core_config)
{
    struct falcon16_tsc_uc_core_config_st serdes_firmware_core_config;
    PHYMOD_IF_ERR_RETURN(falcon16_tsc_get_uc_core_config(&phy->access, &serdes_firmware_core_config));
    PHYMOD_MEMSET(fw_core_config, 0, sizeof(*fw_core_config));
    fw_core_config->CoreConfigFromPCS = serdes_firmware_core_config.field.core_cfg_from_pcs;
    fw_core_config->VcoRate = serdes_firmware_core_config.field.vco_rate;
     
    return PHYMOD_E_NONE;
    
}


int _falcon16_phy_firmware_lane_config_set(const phymod_phy_access_t* phy, phymod_firmware_lane_config_t fw_config)
{
    uint32_t is_warm_boot;
    struct falcon16_tsc_uc_lane_config_st serdes_firmware_config;

    PHYMOD_MEMSET(&serdes_firmware_config, 0x0, sizeof(serdes_firmware_config));
    serdes_firmware_config.field.lane_cfg_from_pcs      = fw_config.LaneConfigFromPCS;
    serdes_firmware_config.field.an_enabled             = fw_config.AnEnabled;
    serdes_firmware_config.field.dfe_on                 = fw_config.DfeOn;
    serdes_firmware_config.field.force_brdfe_on         = fw_config.ForceBrDfe;
    /* serdes_firmware_config.field.cl72_emulation_en = fw_config.Cl72Enable; */
    serdes_firmware_config.field.scrambling_dis         = fw_config.ScramblingDisable;
    serdes_firmware_config.field.unreliable_los         = fw_config.UnreliableLos;
    serdes_firmware_config.field.media_type             = fw_config.MediaType;
    serdes_firmware_config.field.dfe_lp_mode            = fw_config.LpDfeOn;
    serdes_firmware_config.field.cl72_auto_polarity_en  = fw_config.Cl72AutoPolEn;
    serdes_firmware_config.field.cl72_restart_timeout_en = fw_config.Cl72RestTO;

    PHYMOD_IF_ERR_RETURN(PHYMOD_IS_WRITE_DISABLED(&phy->access, &is_warm_boot));

    if(!is_warm_boot) {
        PHYMOD_IF_ERR_RETURN(falcon16_tsc_set_uc_lane_cfg(&phy->access, serdes_firmware_config));
    }
    return PHYMOD_E_NONE;
}


int falcon16_phy_firmware_lane_config_set(const phymod_phy_access_t* phy, phymod_firmware_lane_config_t fw_lane_config)
{

   PHYMOD_IF_ERR_RETURN
            (falcon16_lane_soft_reset_release(&phy->access, 0));

   PHYMOD_IF_ERR_RETURN
            (_falcon16_phy_firmware_lane_config_set(phy, fw_lane_config));

   PHYMOD_IF_ERR_RETURN
            (falcon16_lane_soft_reset_release(&phy->access, 1));
    
    return PHYMOD_E_NONE;
    
}

int falcon16_phy_firmware_lane_config_get(const phymod_phy_access_t* phy, phymod_firmware_lane_config_t* fw_lane_config)
{
    struct falcon16_tsc_uc_lane_config_st serdes_firmware_config;

    PHYMOD_MEMSET(&serdes_firmware_config, 0x0, sizeof(serdes_firmware_config));
    PHYMOD_IF_ERR_RETURN(falcon16_tsc_get_uc_lane_cfg(&phy->access, &serdes_firmware_config));
    PHYMOD_MEMSET(fw_lane_config, 0, sizeof(*fw_lane_config));
    fw_lane_config->LaneConfigFromPCS = serdes_firmware_config.field.lane_cfg_from_pcs;
    fw_lane_config->AnEnabled         = serdes_firmware_config.field.an_enabled;
    fw_lane_config->DfeOn             = serdes_firmware_config.field.dfe_on;
    fw_lane_config->LpDfeOn           = serdes_firmware_config.field.dfe_lp_mode;
    fw_lane_config->ForceBrDfe        = serdes_firmware_config.field.force_brdfe_on;
    /* fw_config->Cl72Enable        = serdes_firmware_config.field.cl72_emulation_en; */
    fw_lane_config->ScramblingDisable = serdes_firmware_config.field.scrambling_dis;
    fw_lane_config->UnreliableLos     = serdes_firmware_config.field.unreliable_los;
    fw_lane_config->MediaType         = serdes_firmware_config.field.media_type;
    fw_lane_config->Cl72AutoPolEn     = serdes_firmware_config.field.cl72_auto_polarity_en;
    fw_lane_config->Cl72RestTO        = serdes_firmware_config.field.cl72_restart_timeout_en;

    return PHYMOD_E_NONE;
    
}


int falcon16_core_pll_sequencer_restart(const phymod_core_access_t* core, uint32_t flags, phymod_sequencer_operation_t operation)
{
     
    PHYMOD_DEBUG_ERROR(("This function is NOT SUPPORTED!! (falcon16_core_pll_sequencer_restart)\n"));   
        
    return PHYMOD_E_NONE;
    
}


int falcon16_core_wait_event(const phymod_core_access_t* core, phymod_core_event_t event, uint32_t timeout)
{
        
    PHYMOD_DEBUG_ERROR(("This function is NOT SUPPORTED!! (falcon16_core_wait_event)\n"));   
        
    return PHYMOD_E_NONE;
    
}


int falcon16_phy_rx_restart(const phymod_phy_access_t* phy)
{
        
    PHYMOD_IF_ERR_RETURN(falcon16_tsc_rx_restart(&phy->access, 1)); 
        
    return PHYMOD_E_NONE;
    
}


int falcon16_phy_polarity_set(const phymod_phy_access_t* phy, const phymod_polarity_t* polarity)
{
        
    PHYMOD_IF_ERR_RETURN
        (falcon16_tx_rx_polarity_set(&phy->access, polarity->tx_polarity, polarity->rx_polarity));
        
    return PHYMOD_E_NONE;
    
}

int falcon16_phy_polarity_get(const phymod_phy_access_t* phy, phymod_polarity_t* polarity)
{
        
    PHYMOD_IF_ERR_RETURN
        (falcon16_tx_rx_polarity_get(&phy->access, &polarity->tx_polarity, &polarity->rx_polarity));
        
    return PHYMOD_E_NONE;
    
}


int falcon16_phy_tx_set(const phymod_phy_access_t* phy, const phymod_tx_t* tx)
{
    
    PHYMOD_IF_ERR_RETURN
        (falcon16_tsc_write_tx_afe(&phy->access, TX_AFE_PRE, tx->pre));
    PHYMOD_IF_ERR_RETURN
        (falcon16_tsc_write_tx_afe(&phy->access, TX_AFE_MAIN, tx->main));
    PHYMOD_IF_ERR_RETURN
        (falcon16_tsc_write_tx_afe(&phy->access, TX_AFE_POST1, tx->post));
    PHYMOD_IF_ERR_RETURN
        (falcon16_tsc_write_tx_afe(&phy->access, TX_AFE_POST2, tx->post2));
    PHYMOD_IF_ERR_RETURN
        (falcon16_tsc_write_tx_afe(&phy->access, TX_AFE_POST3, tx->post3));
/*
    PHYMOD_IF_ERR_RETURN
        (falcon16_tsc_write_tx_afe(&phy->access, TX_AFE_RPARA,  tx->amp)); */

    return PHYMOD_E_NONE;
    
}

int falcon16_phy_tx_get(const phymod_phy_access_t* phy, phymod_tx_t* tx)
{
    PHYMOD_IF_ERR_RETURN
        (falcon16_tsc_read_tx_afe(&phy->access, TX_AFE_PRE, &tx->pre));
    PHYMOD_IF_ERR_RETURN
        (falcon16_tsc_read_tx_afe(&phy->access, TX_AFE_MAIN, &tx->main));
    PHYMOD_IF_ERR_RETURN
        (falcon16_tsc_read_tx_afe(&phy->access, TX_AFE_POST1, &tx->post));
    PHYMOD_IF_ERR_RETURN
        (falcon16_tsc_read_tx_afe(&phy->access, TX_AFE_POST2, &tx->post2));
    PHYMOD_IF_ERR_RETURN
        (falcon16_tsc_read_tx_afe(&phy->access, TX_AFE_POST3, &tx->post3));
/*
    PHYMOD_IF_ERR_RETURN
        (falcon16_tsc_read_tx_afe(&phy->access, TX_AFE_AMP, &tx->amp));*/
        
    return PHYMOD_E_NONE;
    
}


int falcon16_phy_media_type_tx_get(const phymod_phy_access_t* phy, phymod_media_typed_t media, phymod_tx_t* tx)
{
    switch (media) {
    case phymodMediaTypeChipToChip:
      tx->pre   = 0xA;
      tx->main  = 0x41;
      tx->post  = 0x14;
      tx->post2 = 0x0;
      tx->post3 = 0x0;
      break;
    case phymodMediaTypeShort:
      tx->pre   = 0xA;
      tx->main  = 0x41;
      tx->post  = 0x14;
      tx->post2 = 0x0;
      tx->post3 = 0x0;
      break;
    case phymodMediaTypeMid:
      tx->pre   = 0xA;
      tx->main  = 0x41;
      tx->post  = 0x14;
      tx->post2 = 0x0;
      tx->post3 = 0x0;
      break;
    case phymodMediaTypeLong:
      tx->pre   = 0xA;
      tx->main  = 0x41;
      tx->post  = 0x14;
      tx->post2 = 0x0;
      tx->post3 = 0x0;
      break;
    default:
      tx->pre   = 0xA;
      tx->main  = 0x41;
      tx->post  = 0x14;
      tx->post2 = 0x0;
      tx->post3 = 0x0;
      break;
    }

    return PHYMOD_E_NONE;
    
}


int falcon16_phy_tx_override_set(const phymod_phy_access_t* phy, const phymod_tx_override_t* tx_override)
{
    PHYMOD_IF_ERR_RETURN
        (falcon16_tsc_tx_pi_freq_override(&phy->access,
                                        tx_override->phase_interpolator.enable,
                                        tx_override->phase_interpolator.value));
    
    
    return PHYMOD_E_NONE;
    
}

int falcon16_phy_tx_override_get(const phymod_phy_access_t* phy, phymod_tx_override_t* tx_override)
{
    
    /* Place your code here */

        
    return PHYMOD_E_NONE;
    
}


int falcon16_phy_rx_set(const phymod_phy_access_t* phy, const phymod_rx_t* rx)
{
    uint32_t i;

    /*params check*/
    if((rx->num_of_dfe_taps == 0) || (rx->num_of_dfe_taps > TSCF16_NOF_DFES)){
        PHYMOD_RETURN_WITH_ERR(PHYMOD_E_CONFIG, (_PHYMOD_MSG("illegal number of DFEs to set %u"), (unsigned int)rx->num_of_dfe_taps));
    }

    /*vga set*/
    if (rx->vga.enable) {
        /* first stop the rx adaption */
        PHYMOD_IF_ERR_RETURN(falcon16_tsc_stop_rx_adaptation(&phy->access, 1));
        PHYMOD_IF_ERR_RETURN(falcon16_tsc_write_rx_afe(&phy->access, RX_AFE_VGA, rx->vga.value));
    } else {
        PHYMOD_IF_ERR_RETURN(falcon16_tsc_stop_rx_adaptation(&phy->access, 0));
    }

    /*dfe set*/
    for (i = 0 ; i < rx->num_of_dfe_taps ; i++){
        if(rx->dfe[i].enable){
            PHYMOD_IF_ERR_RETURN(falcon16_tsc_stop_rx_adaptation(&phy->access, 1));
            switch (i) {
                case 0:
                    PHYMOD_IF_ERR_RETURN(falcon16_tsc_write_rx_afe(&phy->access, RX_AFE_DFE1, rx->dfe[i].value));
                    break;
                case 1:
                    PHYMOD_IF_ERR_RETURN(falcon16_tsc_write_rx_afe(&phy->access, RX_AFE_DFE2, rx->dfe[i].value));
                    break;
                case 2:
                    PHYMOD_IF_ERR_RETURN(falcon16_tsc_write_rx_afe(&phy->access, RX_AFE_DFE3, rx->dfe[i].value));
                    break;
                case 3:
                    PHYMOD_IF_ERR_RETURN(falcon16_tsc_write_rx_afe(&phy->access, RX_AFE_DFE4, rx->dfe[i].value));
                    break;
                case 4:
                    PHYMOD_IF_ERR_RETURN(falcon16_tsc_write_rx_afe(&phy->access, RX_AFE_DFE5, rx->dfe[i].value));
                    break;
                default:
                    return PHYMOD_E_PARAM;
            }
        } else {
            PHYMOD_IF_ERR_RETURN(falcon16_tsc_stop_rx_adaptation(&phy->access, 0));
        }
    }
    /*peaking filter set*/
    if(rx->peaking_filter.enable){
        /* first stop the rx adaption */
        PHYMOD_IF_ERR_RETURN(falcon16_tsc_stop_rx_adaptation(&phy->access, 1));
        PHYMOD_IF_ERR_RETURN(falcon16_tsc_write_rx_afe(&phy->access, RX_AFE_PF, rx->peaking_filter.value));
    } else {
        PHYMOD_IF_ERR_RETURN(falcon16_tsc_stop_rx_adaptation(&phy->access, 0));
    }

    if(rx->low_freq_peaking_filter.enable){
        /* first stop the rx adaption */
        PHYMOD_IF_ERR_RETURN(falcon16_tsc_stop_rx_adaptation(&phy->access, 1));
        PHYMOD_IF_ERR_RETURN(falcon16_tsc_write_rx_afe(&phy->access, RX_AFE_PF2, rx->low_freq_peaking_filter.value));
    } else {
        PHYMOD_IF_ERR_RETURN(falcon16_tsc_stop_rx_adaptation(&phy->access, 0));
    }
 
        
    return PHYMOD_E_NONE;
    
}


int falcon16_phy_rx_get(const phymod_phy_access_t* phy, phymod_rx_t* rx)
{
        int8_t val;
    uint32_t rx_adaptation;

    rx_adaptation = PHYMOD_RX_ADAPTATION_ON_GET(rx);
    PHYMOD_IF_ERR_RETURN(falcon16_tsc_stop_rx_adaptation(&phy->access, 1));

    PHYMOD_IF_ERR_RETURN
        (falcon16_tsc_read_rx_afe(&phy->access, RX_AFE_PF, &val));
    rx->peaking_filter.value = val;

    PHYMOD_IF_ERR_RETURN
        (falcon16_tsc_read_rx_afe(&phy->access, RX_AFE_PF2, &val));
    rx->low_freq_peaking_filter.value = val;

    PHYMOD_IF_ERR_RETURN
        (falcon16_tsc_read_rx_afe(&phy->access, RX_AFE_VGA, &val));
    rx->vga.value = val;

    PHYMOD_IF_ERR_RETURN
        (falcon16_tsc_read_rx_afe(&phy->access, RX_AFE_DFE1, &val));
    rx->dfe[0].value = val;

    PHYMOD_IF_ERR_RETURN
        (falcon16_tsc_read_rx_afe(&phy->access, RX_AFE_DFE2, &val));
    rx->dfe[1].value = val;

    PHYMOD_IF_ERR_RETURN
        (falcon16_tsc_read_rx_afe(&phy->access, RX_AFE_DFE3, &val));
    rx->dfe[2].value = val;

    PHYMOD_IF_ERR_RETURN
        (falcon16_tsc_read_rx_afe(&phy->access, RX_AFE_DFE4, &val));
    rx->dfe[3].value = val;

    PHYMOD_IF_ERR_RETURN
        (falcon16_tsc_read_rx_afe(&phy->access, RX_AFE_DFE5, &val));
    rx->dfe[4].value = val;

    rx->num_of_dfe_taps = 5;
    rx->dfe[0].enable = 1;
    rx->dfe[1].enable = 1;
    rx->dfe[2].enable = 1;
    rx->dfe[3].enable = 1;
    rx->dfe[4].enable = 1;
    rx->vga.enable = 1;
    rx->low_freq_peaking_filter.enable = 1;
    rx->peaking_filter.enable = 1;

    if (rx_adaptation) {
        PHYMOD_IF_ERR_RETURN(falcon16_tsc_stop_rx_adaptation(&phy->access, 0));
    }
    
    return PHYMOD_E_NONE;
    
}


int falcon16_phy_reset_set(const phymod_phy_access_t* phy, const phymod_phy_reset_t* reset)
{
    /*Reset per RX/TX is not supported*/
    if (reset->rx != reset->tx)
    {
        PHYMOD_DEBUG_ERROR(("Reset per RX/TX is NOT SUPPORTED!! (falcon_phy_reset_set) \n"));
    }
   
    switch (reset->tx)
    {
          case phymodResetDirectionIn:
              PHYMOD_IF_ERR_RETURN(falcon16_lane_soft_reset_release(&phy->access, 0));
          break;
          case phymodResetDirectionOut:
              PHYMOD_IF_ERR_RETURN(falcon16_lane_soft_reset_release(&phy->access, 1));
          break;
          case phymodResetDirectionInOut:
              PHYMOD_IF_ERR_RETURN(falcon16_lane_soft_reset_release(&phy->access, 0));
              PHYMOD_USLEEP(10);
              PHYMOD_IF_ERR_RETURN(falcon16_lane_soft_reset_release(&phy->access, 1));
          break;
          default:
          break;
    }
    
    
    return PHYMOD_E_NONE;
    
}

int falcon16_phy_reset_get(const phymod_phy_access_t* phy, phymod_phy_reset_t* reset)
{
        
    uint32_t rst;
    PHYMOD_IF_ERR_RETURN(falcon16_lane_soft_reset_release_get(&phy->access, &rst));
    if(rst == 0) {
       reset->tx = phymodResetDirectionIn;
       reset->rx = phymodResetDirectionIn;
    } else {
       reset->tx = phymodResetDirectionOut;
       reset->rx = phymodResetDirectionOut;
    }
 
    return PHYMOD_E_NONE;
    
}


int falcon16_phy_power_set(const phymod_phy_access_t* phy, const phymod_phy_power_t* power)
{
        enum srds_core_pwrdn_mode_enum mode;
    if ((power->tx == phymodPowerOff) && (power->rx == phymodPowerNoChange)) {
            /*disable tx on the PMD side */
            mode = PWRDN_TX;
            PHYMOD_IF_ERR_RETURN(falcon16_tsc_lane_pwrdn(&phy->access, mode));
    }
    if ((power->tx == phymodPowerOn) && (power->rx == phymodPowerNoChange)) {
            /*enable tx on the PMD side */
            PHYMOD_IF_ERR_RETURN(falcon16_tsc_pwrdn_set(&phy->access, 1, 0));
    }
    if ((power->tx == phymodPowerNoChange) && (power->rx == phymodPowerOff)) {
            /*disable rx on the PMD side */
            mode = PWRDN_RX;
            PHYMOD_IF_ERR_RETURN(falcon16_tsc_lane_pwrdn(&phy->access, mode));
    }
    if ((power->tx == phymodPowerNoChange) && (power->rx == phymodPowerOn)) {
            PHYMOD_IF_ERR_RETURN(falcon16_tsc_pwrdn_set(&phy->access, 0, 0));
            /*enable rx on the PMD side */
    }
    if ((power->tx == phymodPowerOn) && (power->rx == phymodPowerOn)) {
            mode = PWR_ON;
            PHYMOD_IF_ERR_RETURN(falcon16_tsc_lane_pwrdn(&phy->access, mode));
    }
    if ((power->tx == phymodPowerOff) && (power->rx == phymodPowerOff)) {
            /* Both Tx and Rx power down */
            mode = PWRDN;
            PHYMOD_IF_ERR_RETURN(falcon16_tsc_lane_pwrdn(&phy->access, mode));
    }
    
    
    return PHYMOD_E_NONE;
    
}

int falcon16_phy_power_get(const phymod_phy_access_t* phy, phymod_phy_power_t* power)
{
    power_status_t pwrdn;

    PHYMOD_IF_ERR_RETURN(falcon16_tsc_pwrdn_get(&phy->access, &pwrdn));
    power->rx = (pwrdn.rx_s_pwrdn == 0)? phymodPowerOn: phymodPowerOff;
    power->tx = (pwrdn.tx_s_pwrdn == 0)? phymodPowerOn: phymodPowerOff;
    
    
    return PHYMOD_E_NONE;
    
}


int falcon16_phy_tx_lane_control_set(const phymod_phy_access_t* phy, phymod_phy_tx_lane_control_t tx_control)
{
    switch (tx_control)        
    {
         case phymodTxElectricalIdleEnable:
             PHYMOD_IF_ERR_RETURN(falcon16_electrical_idle_set(&phy->access, 1));
             break;
         case phymodTxElectricalIdleDisable:
             PHYMOD_IF_ERR_RETURN(falcon16_electrical_idle_set(&phy->access, 0));
             break;
         case phymodTxSquelchOn:
             PHYMOD_IF_ERR_RETURN(falcon16_tsc_tx_disable(&phy->access, 1));
             break;
         case phymodTxSquelchOff:
             PHYMOD_IF_ERR_RETURN(falcon16_tsc_tx_disable(&phy->access, 0));
             break;
         default:
             PHYMOD_DEBUG_ERROR(("This control is NOT SUPPORTED!! (falcon16_phy_tx_lane_control_set)\n"));
    } 

    return PHYMOD_E_NONE;
    
}

int falcon16_phy_tx_lane_control_get(const phymod_phy_access_t* phy, phymod_phy_tx_lane_control_t* tx_control)
{
    uint8_t disable;
  
    PHYMOD_IF_ERR_RETURN(falcon16_tsc_tx_disable_get(&phy->access, &disable));        
    if(disable){
        *tx_control = phymodTxSquelchOn;  
    } else {
        *tx_control = phymodTxSquelchOff;  

    } 
        
    return PHYMOD_E_NONE;
    
}


int falcon16_phy_rx_lane_control_set(const phymod_phy_access_t* phy, phymod_phy_rx_lane_control_t rx_control)
{
        
    PHYMOD_DEBUG_ERROR(("This function is NOT SUPPORTED!! (falcon16_phy_rx_lane_control_set)\n"));   
        
    return PHYMOD_E_NONE;
    
}

int falcon16_phy_rx_lane_control_get(const phymod_phy_access_t* phy, phymod_phy_rx_lane_control_t* rx_control)
{
        
    PHYMOD_DEBUG_ERROR(("This function is NOT SUPPORTED!! (falcon16_phy_rx_lane_control_get)\n"));   
        
    return PHYMOD_E_NONE;
    
}


int falcon16_phy_interface_config_set(const phymod_phy_access_t* phy, uint32_t flags, const phymod_phy_inf_config_t* config)
{
    /* phymod_tx_t tx_params; */
    uint32_t      current_pll_div=0;
    uint32_t vco_rate;
    uint32_t new_pll_div=0;
    int16_t  new_os_mode =0;
    phymod_phy_access_t pm_phy_copy;
    int start_lane, num_lane, i;
    uint32_t enable[PHYMOD_MAX_LANES_PER_CORE];

    /* sc_table_entry exp_entry; RAVI */
    phymod_firmware_lane_config_t firmware_lane_config;
    phymod_firmware_core_config_t firmware_core_config;

    PHYMOD_MEMSET(&firmware_lane_config, 0x0, sizeof(firmware_lane_config));
    PHYMOD_MEMSET(&firmware_core_config, 0x0, sizeof(firmware_core_config));
    firmware_lane_config.MediaType = 0;

    /*next program the tx fir taps and driver current based on the input*/
    PHYMOD_IF_ERR_RETURN
        (phymod_util_lane_config_get(&phy->access, &start_lane, &num_lane));

    PHYMOD_MEMCPY(&pm_phy_copy, phy, sizeof(pm_phy_copy));

    /*Get lane reset status*/
    for (i = 0; i < num_lane; i++) {
        pm_phy_copy.access.lane_mask = 1 << (start_lane + i);
        PHYMOD_IF_ERR_RETURN
            (falcon16_lane_soft_reset_release_get(&pm_phy_copy.access, &enable[i]));
    }
     
    /*Hold the per lne soft reset bit*/
    for (i = 0; i < num_lane; i++) {
        if (enable[i])
        {
            pm_phy_copy.access.lane_mask = 1 << (start_lane + i);
            PHYMOD_IF_ERR_RETURN
                (falcon16_lane_soft_reset_release(&pm_phy_copy.access, 0));
        }
    }

    pm_phy_copy.access.lane_mask = 0x1 << start_lane;
     PHYMOD_IF_ERR_RETURN
        (falcon16_phy_firmware_lane_config_get(&pm_phy_copy, &firmware_lane_config));

    /*make sure that an and config from pcs is off*/
    firmware_core_config.CoreConfigFromPCS = 0;
    firmware_lane_config.AnEnabled = 0;
    firmware_lane_config.LaneConfigFromPCS = 0;
    firmware_lane_config.DfeOn = 1;
    firmware_lane_config.LpDfeOn = 0;
    firmware_lane_config.Cl72RestTO = 1;
    if(config->data_rate == 1000)
       firmware_lane_config.DfeOn = 0;

    if (PHYMOD_INTF_MODES_FIBER_GET(config)) {
        firmware_lane_config.MediaType = phymodFirmwareMediaTypeOptics;
    } else if (PHYMOD_INTF_MODES_COPPER_GET(config)) {
        firmware_lane_config.MediaType = phymodFirmwareMediaTypeCopperCable;
    } else {
        firmware_lane_config.MediaType = phymodFirmwareMediaTypePcbTraceBackPlane;
    }    
    /* Check unreliable LOS */
    if(config->interface_modes & ~(0x200)) {
        firmware_lane_config.UnreliableLos = 1;
    } else {
        firmware_lane_config.UnreliableLos = 0;
    }

     PHYMOD_IF_ERR_RETURN
        (falcon16_tsc_get_pll_vco_osmode(config, &vco_rate, &new_pll_div, &new_os_mode));

    PHYMOD_IF_ERR_RETURN
        (falcon16_pll_mode_get(&pm_phy_copy.access, &current_pll_div));

    
    /*if pll change is enabled*/
    if((current_pll_div != new_pll_div) && (PHYMOD_INTF_F_DONT_TURN_OFF_PLL & flags)){
        PHYMOD_RETURN_WITH_ERR(PHYMOD_E_CONFIG,
        (_PHYMOD_MSG("pll has to change for speed_set from %u to %u but DONT_TURN_OFF_PLL flag is enabled"),
        (unsigned int)current_pll_div, (unsigned int)new_pll_div));
    }
    /*pll switch is required and expected */
    if((current_pll_div != new_pll_div) && !(PHYMOD_INTF_F_DONT_TURN_OFF_PLL & flags)) {
        /* phymod_access_t tmp_phy_access; */
        PHYMOD_IF_ERR_RETURN
            (falcon16_core_soft_reset_release(&pm_phy_copy.access, 0));

        /*release the uc reset */
#if 0
        PHYMOD_IF_ERR_RETURN
            (falcon16_tsc_uc_reset(&pm_phy_copy.access ,0));
#endif
        /*set the PLL divider */
        PHYMOD_IF_ERR_RETURN
            (falcon16_pll_mode_set(&pm_phy_copy.access, new_pll_div));

        firmware_core_config.VcoRate = (vco_rate * 16 + 500) / 1000 - 224;

        /*change the  master port num to the current caller port */
        
        /* 
        PHYMOD_IF_ERR_RETURN
            (tefmod_master_port_num_set(&phy->access, start_lane)); */
        /* Do we need PLL reset */
         
#if 0
        PHYMOD_IF_ERR_RETURN
            (falcon16_pll_reset_enable_set(&pm_phy_copy.access, 1));
#endif
        /*update the firmware config properly*/
        PHYMOD_IF_ERR_RETURN
            (falcon16_phy_firmware_core_config_set(&pm_phy_copy, firmware_core_config));
        PHYMOD_IF_ERR_RETURN
            (falcon16_core_soft_reset_release(&pm_phy_copy.access, 1));
    }

    /*
    PHYMOD_IF_ERR_RETURN
        (tefmod_set_spd_intf(&phy->access, spd_intf));
    */

    /*change TX parameters if enabled*/
    /*
    if((PHYMOD_IF_F_DONT_OVERIDE_TX_PARAMS & flags) == 0) {
        PHYMOD_IF_ERR_RETURN
            (tscf_phy_media_type_tx_get(phy, phymodMediaTypeMid, &tx_params));
    }
    */
    for (i = 0; i < num_lane; i++) {
        pm_phy_copy.access.lane_mask = 0x1 << (start_lane + i);
        PHYMOD_IF_ERR_RETURN
             (_falcon16_phy_firmware_lane_config_set(&pm_phy_copy, firmware_lane_config));
    }   
    for (i = 0; i < num_lane; i++) {
        pm_phy_copy.access.lane_mask = 0x1 << (start_lane + i);
        PHYMOD_IF_ERR_RETURN
            (falcon16_osr_mode_set(&pm_phy_copy.access, new_os_mode));
    }

    /*release the per lne soft reset bit*/
    for (i = 0; i < num_lane; i++) {
        if (enable[i])
        {
            pm_phy_copy.access.lane_mask = 1 << (start_lane + i);
            PHYMOD_IF_ERR_RETURN
                (falcon16_lane_soft_reset_release(&pm_phy_copy.access, 1));
        }
    }
    
    return PHYMOD_E_NONE;
    
}


STATIC
int _falcon16_pll_multiplier_get(uint32_t pll_div, uint32_t *pll_multiplier)
{
    switch (pll_div) {
    case 0x0:
        *pll_multiplier = 64;
        break;
    case 0x1:
        *pll_multiplier = 66;
        break;
    case 0x2:
        *pll_multiplier = 80;
        break;
    case 0x3:
        *pll_multiplier = 128;
        break;
    case 0x4:
        *pll_multiplier = 132;
        break;
    case 0x5:
        *pll_multiplier = 140;
        break;
    case 0x6:
        *pll_multiplier = 160;
        break;
    case 0x7:
        *pll_multiplier = 165;
        break;
    case 0x8:
        *pll_multiplier = 168;
        break;
    case 0x9:
        *pll_multiplier = 170;
        break;
    case 0xa:
        *pll_multiplier = 175;
        break;
    case 0xb:
        *pll_multiplier = 180;
        break;
    case 0xc:
        *pll_multiplier = 184;
        break;
    case 0xd:
        *pll_multiplier = 200;
        break;
    case 0xe:
        *pll_multiplier = 224;
        break;
    case 0xf:
        *pll_multiplier = 264;
        break;
    default:
        *pll_multiplier = 165;
        break;
    }
    return PHYMOD_E_NONE;
}


STATIC
int _falcon16_actual_osr_get(int osr_mode, int* actual_os)
{
    switch(osr_mode) {
        case 0: *actual_os = 1; break;
        case 1: *actual_os = 2; break;
        case 2: *actual_os = 4; break;
        default:
            PHYMOD_RETURN_WITH_ERR(PHYMOD_E_INTERNAL, (_PHYMOD_MSG("unsupported OS mode %d"), osr_mode));
    }
    return PHYMOD_E_NONE;
}


int falcon16_phy_interface_config_get(const phymod_phy_access_t* phy, uint32_t flags, phymod_ref_clk_t ref_clock, phymod_phy_inf_config_t* config)
{
    int osr_mode;
    uint32_t pll_div;
    uint32_t pll_multiplier, refclk;
    phymod_phy_access_t phy_copy;
    int actual_osr;

    config->ref_clock = ref_clock;

    PHYMOD_MEMCPY(&phy_copy, phy, sizeof(phy_copy));
    phy_copy.access.lane_mask = 0x1;

    PHYMOD_IF_ERR_RETURN
        (falcon16_osr_mode_get(&phy->access, &osr_mode));
    PHYMOD_IF_ERR_RETURN
        (falcon16_pll_mode_get(&phy_copy.access, &pll_div));
    PHYMOD_IF_ERR_RETURN
        (_falcon16_pll_multiplier_get(pll_div, &pll_multiplier));

        if (ref_clock == phymodRefClk156Mhz) {
        refclk = 15625;
    } else if (ref_clock == phymodRefClk125Mhz) {
        refclk = 12500;
    } else {
        PHYMOD_RETURN_WITH_ERR(PHYMOD_E_INTERNAL,  (_PHYMOD_MSG("Unknown refclk")));
    }

    PHYMOD_IF_ERR_RETURN(_falcon16_actual_osr_get(osr_mode, &actual_osr));

    config->data_rate = (refclk*pll_multiplier)/(100*actual_osr);
    config->interface_type = phymodInterfaceBypass;

    if(osr_mode == 1) {
        PHYMOD_INTF_MODES_OS2_SET(config);
    }
    
    return PHYMOD_E_NONE;
    
}


int falcon16_phy_cl72_set(const phymod_phy_access_t* phy, uint32_t cl72_en)
{
    PHYMOD_IF_ERR_RETURN
        (falcon16_clause72_control(&phy->access, cl72_en));
 
    return PHYMOD_E_NONE;
    
}

int falcon16_phy_cl72_get(const phymod_phy_access_t* phy, uint32_t* cl72_en)
{
    PHYMOD_IF_ERR_RETURN
        (falcon16_clause72_control_get(&phy->access, cl72_en));

    return PHYMOD_E_NONE;
    
}


int falcon16_phy_cl72_status_get(const phymod_phy_access_t* phy, phymod_cl72_status_t* status)
{
    uint32_t local_status;

    PHYMOD_IF_ERR_RETURN
        (falcon16_pmd_cl72_receiver_status(&phy->access, &local_status));
    status->locked = local_status;
    
        
    return PHYMOD_E_NONE;
    
}


int falcon16_phy_autoneg_ability_set(const phymod_phy_access_t* phy, const phymod_autoneg_ability_t* an_ability_set_type)
{
        
    PHYMOD_DEBUG_ERROR(("This function is NOT SUPPORTED!! (falcon16_phy_autoneg_ability_set)\n"));   
    
    return PHYMOD_E_NONE;
    
}

int falcon16_phy_autoneg_ability_get(const phymod_phy_access_t* phy, phymod_autoneg_ability_t* an_ability_get_type)
{
        
    PHYMOD_DEBUG_ERROR(("This function is NOT SUPPORTED!! (falcon16_phy_autoneg_ability_get)\n"));   
    
    return PHYMOD_E_NONE;
    
}


int falcon16_phy_autoneg_set(const phymod_phy_access_t* phy, const phymod_autoneg_control_t* an)
{

    PHYMOD_DEBUG_ERROR(("This function is NOT SUPPORTED!! (falcon16_phy_autoneg_set)\n"));   
        
    return PHYMOD_E_NONE;
    
}

int falcon16_phy_autoneg_get(const phymod_phy_access_t* phy, phymod_autoneg_control_t* an, uint32_t* an_done)
{
        
    PHYMOD_DEBUG_ERROR(("This function is NOT SUPPORTED!! (falcon16_phy_autoneg_get)\n"));   
        
    return PHYMOD_E_NONE;
    
}


int falcon16_phy_autoneg_status_get(const phymod_phy_access_t* phy, phymod_autoneg_status_t* status)
{
        
    PHYMOD_DEBUG_ERROR(("This function is NOT SUPPORTED!! (falcon16_phy_autoneg_status_get)\n"));   
        
    return PHYMOD_E_NONE;
    
}


int falcon16_core_init(const phymod_core_access_t* core, const phymod_core_init_config_t* init_config, const phymod_core_status_t* core_status)
{
        
    int rv;
    phymod_phy_access_t phy_access, phy_access_copy;
    phymod_core_access_t  core_copy;
    phymod_firmware_core_config_t  firmware_core_config_tmp;

    TSCF16_CORE_TO_PHY_ACCESS(&phy_access, core);
    phy_access_copy = phy_access;
    PHYMOD_MEMCPY(&core_copy, core, sizeof(core_copy));
    core_copy.access.lane_mask = 0x1;
    phy_access_copy = phy_access;
    phy_access_copy.access = core->access;
    phy_access_copy.access.lane_mask = 0x1;
    phy_access_copy.type = core->type;



    if(!PHYMOD_CORE_INIT_F_RESUME_AFTER_FW_LOAD_GET(init_config)) {
        PHYMOD_IF_ERR_RETURN
            (falcon16_pmd_reset_seq(&core_copy.access, core_status->pmd_active));
    }

    rv = _falcon16_core_firmware_load(&core_copy, init_config);
    if (rv != PHYMOD_E_NONE) {
        PHYMOD_DEBUG_ERROR(("devad 0x%"PRIx32" lane 0x%"PRIx32": UC firmware-load failed\n", core->access.addr, core->access.lane_mask));
        PHYMOD_IF_ERR_RETURN(rv);
    }

    if(PHYMOD_CORE_INIT_F_UNTIL_FW_LOAD_GET(init_config)) {
        return PHYMOD_E_NONE;
    }

    /*next we need to check if the load is correct or not */
    if(init_config->firmware_load_method != phymodFirmwareLoadMethodNone) {

        /*next we need to set the uc active and release uc */
        PHYMOD_IF_ERR_RETURN
            (falcon16_uc_active_set(&core_copy.access ,1));

        /*release the uc reset */
        PHYMOD_IF_ERR_RETURN
            (falcon16_tsc_uc_reset(&core_copy.access ,0));

#ifndef FALCON_PMD_CRC_UCODE
        if(PHYMOD_CORE_INIT_F_FIRMWARE_LOAD_VERIFY_GET(init_config)) {
            rv = falcon16_tsc_ucode_load_verify(&core_copy.access, (uint8_t *) &falcon16_ucode, falcon16_ucode_len);

            if (rv != PHYMOD_E_NONE) {
                PHYMOD_DEBUG_ERROR(("devad 0x%x lane 0x%x: UC load-verify failed\n", core->access.addr, core->access.lane_mask));
                PHYMOD_IF_ERR_RETURN(rv);
            }
        }
#endif

        PHYMOD_IF_ERR_RETURN
            (falcon16_pmd_ln_h_rstb_pkill_override( &phy_access_copy.access, 0x1));

        /* we need to wait at least 10ms for the uc to settle */
        PHYMOD_USLEEP(10000);

       /* poll the ready bit in 10 ms */
#ifndef FALCON16_PMD_CRC_UCODE
        PHYMOD_IF_ERR_RETURN
            (serdes_INTERNAL_poll_uc_dsc_ready_for_cmd_equals_1(&phy_access_copy.access, 1, CMD_READ_DIAG_DATA_BYTE)); 
#else
        if(PHYMOD_CORE_INIT_F_FIRMWARE_LOAD_VERIFY_GET(init_config)) {
            rv = falcon16_tsc_ucode_crc_verify(&core_copy.access, falcon16_ucode_len, falcon16_ucode_crc);
            if (rv != PHYMOD_E_NONE) {
                PHYMOD_DEBUG_ERROR(("devad 0x%"PRIx32" lane 0x%"PRIx32": UC load-verify failed\n", core->access.addr, core->access.lane_mask));
                PHYMOD_IF_ERR_RETURN(rv);
            }
        }
#endif
        PHYMOD_IF_ERR_RETURN
            (falcon16_pmd_ln_h_rstb_pkill_override( &phy_access_copy.access, 0x0));
    }

    /* AFE/PLL config */
    if(init_config->afe_pll.afe_pll_change_default) {
      PHYMOD_IF_ERR_RETURN
        (falcon16_afe_pll_reg_set(&core_copy.access, &init_config->afe_pll));
      firmware_core_config_tmp.disable_write_pll_iqp = 1;
    } else {
      PHYMOD_IF_ERR_RETURN
        (falcon16_afe_pll_reg_set(&core_copy.access, &init_config->afe_pll));
      firmware_core_config_tmp.disable_write_pll_iqp = 0;
    }
    /* plldiv CONFIG */
    PHYMOD_IF_ERR_RETURN
        (falcon16_pll_mode_set(&core_copy.access, 0xa));

    /*now config the lane mapping and polarity */
    PHYMOD_IF_ERR_RETURN
        (falcon16_core_lane_map_set(core, &init_config->lane_map));
    /*
    PHYMOD_IF_ERR_RETURN
        (tscf16_core_lane_map_set(core, &init_config->lane_map));
    PHYMOD_IF_ERR_RETURN
        (tefmod_autoneg_timer_init(&core->access));
    PHYMOD_IF_ERR_RETURN
        (tefmod_master_port_num_set(&core->access, 0));
    */
    /*don't overide the fw that set in config set if not specified*/
    firmware_core_config_tmp = init_config->firmware_core_config;
    firmware_core_config_tmp.CoreConfigFromPCS = 0;
    /*set the vco rate to be default at 10.3125G */
    firmware_core_config_tmp.VcoRate = 0x13;

    PHYMOD_IF_ERR_RETURN
        (falcon16_phy_firmware_core_config_set(&phy_access_copy, firmware_core_config_tmp));


    /* release core soft reset */
    PHYMOD_IF_ERR_RETURN
        (falcon16_core_soft_reset_release(&core_copy.access, 1));

        
    return PHYMOD_E_NONE;
    
}


int falcon16_phy_init(const phymod_phy_access_t* phy, const phymod_phy_init_config_t* init_config)
{
    const phymod_access_t *pm_acc = &phy->access;
    phymod_phy_access_t pm_phy_copy;
    int start_lane, num_lane, i;
    int lane_bkup;
    phymod_polarity_t tmp_pol;

    PHYMOD_MEMSET(&tmp_pol, 0x0, sizeof(tmp_pol));
    PHYMOD_MEMCPY(&pm_phy_copy, phy, sizeof(pm_phy_copy));

    /*next program the tx fir taps and driver current based on the input*/
    PHYMOD_IF_ERR_RETURN
        (phymod_util_lane_config_get(pm_acc, &start_lane, &num_lane));
    /*per lane based reset release */
    /* PHYMOD_IF_ERR_RETURN
        (tefmod_pmd_x4_reset(pm_acc)); */
    PHYMOD_IF_ERR_RETURN(falcon16_lane_hard_soft_reset_release(&pm_phy_copy.access, 0));
    PHYMOD_IF_ERR_RETURN(falcon16_lane_hard_soft_reset_release(&pm_phy_copy.access, 1));
    PHYMOD_IF_ERR_RETURN(falcon16_lane_soft_reset_release(&pm_phy_copy.access, 0));
    PHYMOD_IF_ERR_RETURN(falcon16_lane_soft_reset_release(&pm_phy_copy.access, 1));
    PHYMOD_IF_ERR_RETURN(falcon16_lane_soft_reset_release(&pm_phy_copy.access, 0));

    lane_bkup = pm_phy_copy.access.lane_mask;
    for (i = 0; i < num_lane; i++) {
        pm_phy_copy.access.lane_mask = 1 << (start_lane + i);
        PHYMOD_IF_ERR_RETURN
            (falcon16_lane_soft_reset_release(&pm_phy_copy.access, 1));
    }
    for (i = 0; i < num_lane; i++) {
        pm_phy_copy.access.lane_mask = 1 << (start_lane + i);
        PHYMOD_IF_ERR_RETURN
            (falcon16_lane_soft_reset_release(&pm_phy_copy.access, 0));
    }
    pm_phy_copy.access.lane_mask = lane_bkup;
    
    /* program the rx/tx polarity */
    for (i = 0; i < num_lane; i++) {
        pm_phy_copy.access.lane_mask = 0x1 << (i + start_lane);
        tmp_pol.tx_polarity = (init_config->polarity.tx_polarity) >> (i + start_lane) & 0x1;
        tmp_pol.rx_polarity = (init_config->polarity.rx_polarity) >> (i + start_lane) & 0x1;
        PHYMOD_IF_ERR_RETURN
            (falcon16_phy_polarity_set(&pm_phy_copy, &tmp_pol));
    }

    for (i = 0; i < num_lane; i++) {
        pm_phy_copy.access.lane_mask = 0x1 << (i + start_lane);
        PHYMOD_IF_ERR_RETURN
            (falcon16_phy_tx_set(&pm_phy_copy, &init_config->tx[i]));
    }

    PHYMOD_IF_ERR_RETURN
        (falcon16_phy_cl72_set(&pm_phy_copy, init_config->cl72_en));

    /* ONLY for PCS
    PHYMOD_IF_ERR_RETURN
        (tefmod_update_port_mode(pm_acc, &pll_restart));

    PHYMOD_IF_ERR_RETURN
        (tefmod_rx_lane_control_set(pm_acc, 1));
    PHYMOD_IF_ERR_RETURN
        (tefmod_tx_lane_control_set(pm_acc, TEFMOD_TX_LANE_RESET_TRAFFIC_ENABLE));
    */

    return PHYMOD_E_NONE;
    
}


int falcon16_phy_loopback_set(const phymod_phy_access_t* phy, phymod_loopback_mode_t loopback, uint32_t enable)
{
        
    int i;
    int start_lane, num_lane;
    int rv = PHYMOD_E_NONE;
    phymod_phy_access_t phy_copy;

    PHYMOD_MEMCPY(&phy_copy, phy, sizeof(phy_copy));

    /* next figure out the lane num and start_lane based on the input */
    PHYMOD_IF_ERR_RETURN
        (phymod_util_lane_config_get(&phy->access, &start_lane, &num_lane));

    switch (loopback) {
    case phymodLoopbackGlobal :
        /* PHYMOD_IF_ERR_RETURN(tefmod_tx_loopback_control(&phy->access, enable, start_lane, num_lane)); */
        break;
    case phymodLoopbackGlobalPMD :
        for (i = 0; i < num_lane; i++) {
            phy_copy.access.lane_mask = 0x1 << (i + start_lane);
            PHYMOD_IF_ERR_RETURN(falcon16_tsc_dig_lpbk(&phy_copy.access, (uint8_t) enable));
            PHYMOD_IF_ERR_RETURN(falcon16_pmd_force_signal_detect(&phy_copy.access, (int) enable));
        }
        break;
    case phymodLoopbackRemotePMD :
        PHYMOD_IF_ERR_RETURN(falcon16_tsc_rmt_lpbk(&phy->access, (uint8_t)enable));
        break;
    case phymodLoopbackRemotePCS :
        /* PHYMOD_IF_ERR_RETURN(tefmod_rx_loopback_control(&phy->access, enable)); */
        break;
    default :
        break;
    }

    return rv;
    
}

int falcon16_phy_loopback_get(const phymod_phy_access_t* phy, phymod_loopback_mode_t loopback, uint32_t* enable)
{
        
    int start_lane, num_lane;

    /*next figure out the lane num and start_lane based on the input*/
    PHYMOD_IF_ERR_RETURN
        (phymod_util_lane_config_get(&phy->access, &start_lane, &num_lane));

    switch (loopback) {
    case phymodLoopbackGlobal :
        /* PHYMOD_IF_ERR_RETURN(temod_tx_loopback_get(&phy->access, &enable_core)); */
        /* *enable = (enable_core >> start_lane) & 0x1; */
        break;
    case phymodLoopbackGlobalPMD :
        PHYMOD_IF_ERR_RETURN(falcon16_tsc_dig_lpbk_get(&phy->access, enable));
        break;
    case phymodLoopbackRemotePMD :
        PHYMOD_IF_ERR_RETURN(falcon16_tsc_rmt_lpbk_get(&phy->access, enable));
        break;
    case phymodLoopbackRemotePCS :
        /* PHYMOD_IF_ERR_RETURN(temod_rx_loopback_control(&phy->access, enable, enable, enable)); */
        break;
    default :
        break;
    }
 
        
    return PHYMOD_E_NONE;
    
}


int falcon16_phy_link_status_get(const phymod_phy_access_t* phy, uint32_t* link_status)
{
    unsigned char rx_lock;

    PHYMOD_IF_ERR_RETURN(falcon16_tsc_pmd_lock_status(&phy->access, &rx_lock));
    *link_status = (uint32_t ) rx_lock;

    return PHYMOD_E_NONE;

}


int falcon16_phy_rx_pmd_locked_get(const phymod_phy_access_t* phy, uint32_t* rx_pmd_locked)
{
        
    
    PHYMOD_IF_ERR_RETURN(falcon16_phy_link_status_get(phy, rx_pmd_locked)); 
        
    return PHYMOD_E_NONE;
    
}


int falcon16_phy_rx_signal_detect_get(const phymod_phy_access_t* phy, uint32_t* rx_signal_detect)
{
        
    PHYMOD_IF_ERR_RETURN(falcon16_tsc_signal_detect(&phy->access, rx_signal_detect));

    return PHYMOD_E_NONE;
    
}



int falcon16_phy_reg_read(const phymod_phy_access_t* phy, uint32_t reg_addr, uint32_t* val)
{
        
    PHYMOD_IF_ERR_RETURN(phymod_tsc_iblk_read(&phy->access, reg_addr, val)); 

    return PHYMOD_E_NONE;
    
}


int falcon16_phy_reg_write(const phymod_phy_access_t* phy, uint32_t reg_addr, uint32_t val)
{
        
    PHYMOD_IF_ERR_RETURN(phymod_tsc_iblk_write(&phy->access, reg_addr, val));
        
    return PHYMOD_E_NONE;
    
}
