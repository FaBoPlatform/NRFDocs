#include "beacon.h"
#include "nordic_common.h"
#include "app_error.h"

#define APP_BEACON_INFO_LENGTH		0x18    // データサイズ
#define APP_CFG_NON_CONN_ADV_TIMEOUT  0                                 /**< Time for which the device must be advertising in non-connectable mode (in seconds). 0 disables timeout. */

#define UUID_OFFSET_IN_BEACON_INFO 0

static ble_gap_adv_params_t m_adv_params;    // アドバタイズパラメータ
static bool is_starting = false;

// ビーコン初期化
//void beacon_init(beacon_info_t info)
void beacon_init(beacon_info_t info,uint16_t company)
{
    uint32_t        err_code;
    ble_advdata_t   advdata;

    // データ構築
    ble_advdata_manuf_data_t manuf_specific_data;
    manuf_specific_data.company_identifier = company;

    uint8_t m_beacon_info[APP_BEACON_INFO_LENGTH] =
    {
        0,
        0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,     // 128 bit UUID value. 
        0,0,
        0,0,
        0,0
    };
    memcpy(m_beacon_info + UUID_OFFSET_IN_BEACON_INFO, info.uuid, 23);

    manuf_specific_data.data.p_data        = (uint8_t *) m_beacon_info;
    manuf_specific_data.data.size          = APP_BEACON_INFO_LENGTH;

    // データ設定
    memset(&advdata, 0, sizeof(advdata));
    advdata.name_type               = BLE_ADVDATA_NO_NAME;
    advdata.flags = BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED |
                                BLE_GAP_ADV_FLAG_LE_GENERAL_DISC_MODE;
    advdata.p_manuf_specific_data   = &manuf_specific_data;
    err_code = ble_advdata_set(&advdata, NULL);
    APP_ERROR_CHECK(err_code);

    // アドバタイジングの設定
    memset(&m_adv_params, 0, sizeof(m_adv_params));
    m_adv_params.type        = BLE_GAP_ADV_TYPE_ADV_NONCONN_IND;
    m_adv_params.p_peer_addr = NULL;
    m_adv_params.fp          = BLE_GAP_ADV_FP_ANY;
    m_adv_params.interval    = MSEC_TO_UNITS(info.interval, UNIT_0_625_MS);
    m_adv_params.timeout     = APP_CFG_NON_CONN_ADV_TIMEOUT;

    m_adv_params.channel_mask.ch_37_off = info.channel_mask.ch_37_off;
    m_adv_params.channel_mask.ch_38_off = info.channel_mask.ch_38_off;
    m_adv_params.channel_mask.ch_39_off = info.channel_mask.ch_39_off;
}


// ビーコン開始
void beacon_start(void)
{
    if (is_starting) return;
    
    uint32_t err_code;
    err_code = sd_ble_gap_adv_start(&m_adv_params);
    APP_ERROR_CHECK(err_code);
    
    is_starting = true;
}

// ビーコン停止
void beacon_stop(void)
{
    if (!is_starting) return;
    
	uint32_t err_code;
	err_code = sd_ble_gap_adv_stop();
	APP_ERROR_CHECK(err_code);
    
    is_starting = false;
}
