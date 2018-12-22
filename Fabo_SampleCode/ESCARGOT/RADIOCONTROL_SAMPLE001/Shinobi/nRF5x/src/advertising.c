#include "advertising.h"
#include "nordic_common.h"
#include "app_error.h"

static bool is_starting = false;

void advertising_init(ble_uuid_t *adv_uuids)
{
    uint32_t               err_code;
    ble_advdata_t          advdata;

    memset(&advdata, 0, sizeof(advdata));

    advdata.name_type               = BLE_ADVDATA_FULL_NAME;
    advdata.include_appearance      = false;
    advdata.flags                   = BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE;
    advdata.uuids_complete.uuid_cnt = sizeof(adv_uuids) / sizeof(adv_uuids[0]);
    advdata.uuids_complete.p_uuids  = adv_uuids;

    err_code = ble_advdata_set(&advdata, NULL);
    APP_ERROR_CHECK(err_code);
}

void advertising_start(int interval, int timeout)
{
    uint32_t err_code;
    ble_gap_adv_params_t adv_params;

    if (is_starting) return;
    is_starting = true;

    // アドバタイジングの設定
    memset(&adv_params, 0, sizeof(adv_params));
    adv_params.type = BLE_GAP_ADV_TYPE_ADV_IND;
    adv_params.p_peer_addr = NULL;
    adv_params.fp = BLE_GAP_ADV_FP_ANY;
    adv_params.interval    = MSEC_TO_UNITS(100, UNIT_0_625_MS);
    adv_params.timeout = timeout;

    err_code = sd_ble_gap_adv_start(&adv_params);
    APP_ERROR_CHECK(err_code);
}

void advertising_stop()
{
    if (!is_starting) return;
    is_starting = false;

    uint32_t err_code;
    err_code = sd_ble_gap_adv_stop();
    APP_ERROR_CHECK(err_code);
}

void advertising_ble_evt(ble_evt_t *p_ble_evt)
{
    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
        	is_starting = false;
            break; // BLE_GAP_EVT_CONNECTED
    }
}