# Advertisingの開始

## Advertisingの開始

```c
void    ble_advertising_start(void) {
    APP_ERROR_CHECK(sd_ble_gap_adv_start(ble_adv_handle, APP_BLE_CONN_CFG_TAG));
}
```
main.c
```c
#include "app_error.h"
#include "bsp.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_sdh.h"
#include "nrf_sdh_ble.h"
#include "ble_advdata.h"

#define NRF_LOG_MODULE_NAME iBEACON_SAMPLE
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#define LED1                            BSP_BOARD_LED_0
#define APP_BLE_CONN_CFG_TAG            1
#define APP_COMPANY_IDENTIFIER          0x004C
#define APP_BEACON_INFO_LENGTH          0x17
#define APP_BEACON_TYPE                 0x02,0x15
#define APP_BEACON_UUID                 0x01,0x12,0x23,0x34,0x45,0xAA,0x67,0x78,0x89,0xBA,0x13,0xBC,0x33,0x1A,0x22,0xF0
#define APP_MAJOR_VALUE                 0x01,0x02
#define APP_MINOR_VALUE                 0x03,0x04
#define APP_MEASURED_RSSI               0xC3
#define NON_CONNECTABLE_ADV_INTERVAL    MSEC_TO_UNITS(100, UNIT_0_625_MS)

extern uint32_t __app_ram_start__;

static ble_gap_adv_params_t ble_gap_adv_params;
static uint8_t              ble_enc_advdata[BLE_GAP_ADV_SET_DATA_SIZE_MAX];
static uint8_t              ble_adv_handle = BLE_GAP_ADV_SET_HANDLE_NOT_SET;
static uint8_t  beacon_info[APP_BEACON_INFO_LENGTH] = {
    APP_BEACON_TYPE,
    APP_BEACON_UUID,
    APP_MAJOR_VALUE,
    APP_MINOR_VALUE,
    APP_MEASURED_RSSI
};
static ble_gap_adv_data_t   ble_gap_adv_data = {
    .adv_data = {
        .p_data = ble_enc_advdata,
        .len    = BLE_GAP_ADV_SET_DATA_SIZE_MAX
    },
    .scan_rsp_data = {
        .p_data = NULL,
        .len    = 0
    }
};

void    ble_advertising_start(void) {
    APP_ERROR_CHECK(sd_ble_gap_adv_start(ble_adv_handle, APP_BLE_CONN_CFG_TAG));
}

void    ble_advertising_init(void) {
    ble_advdata_manuf_data_t    manuf_specific_data;
    ble_advdata_t               advdata;

    memset(&advdata, 0x00, sizeof(ble_advdata_t));
    memset(&ble_gap_adv_params, 0x00, sizeof(ble_gap_adv_params_t));

    manuf_specific_data.company_identifier = APP_COMPANY_IDENTIFIER;
    manuf_specific_data.data.p_data = beacon_info;
    manuf_specific_data.data.size = APP_BEACON_INFO_LENGTH;

    advdata.name_type = BLE_ADVDATA_NO_NAME;
    advdata.flags = BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE;
    advdata.p_manuf_specific_data = &manuf_specific_data;
    ble_gap_adv_params.properties.type = BLE_GAP_ADV_TYPE_NONCONNECTABLE_NONSCANNABLE_UNDIRECTED;

    ble_gap_adv_params.p_peer_addr = NULL;
    ble_gap_adv_params.filter_policy = BLE_GAP_ADV_FP_ANY;
    ble_gap_adv_params.interval = NON_CONNECTABLE_ADV_INTERVAL;
    ble_gap_adv_params.duration = 0;

    APP_ERROR_CHECK(ble_advdata_encode(&advdata, ble_gap_adv_data.adv_data.p_data, &ble_gap_adv_data.adv_data.len));
    APP_ERROR_CHECK(sd_ble_gap_adv_set_configure(&ble_adv_handle, &ble_gap_adv_data, &ble_gap_adv_params));
}

void    ble_stack_init(void) {
    APP_ERROR_CHECK(nrf_sdh_enable_request());
    APP_ERROR_CHECK(nrf_sdh_ble_default_cfg_set(APP_BLE_CONN_CFG_TAG, &__app_ram_start__));
    APP_ERROR_CHECK(nrf_sdh_ble_enable(&__app_ram_start__));
}

void    log_init(void) {
    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();
}

int main(void) {
    log_init();
    NRF_LOG_INFO("iBEACON_SAMPLE");
    NRF_LOG_FLUSH();

    bsp_board_init(BSP_INIT_LEDS);

    APP_ERROR_CHECK(nrf_pwr_mgmt_init());
    ble_stack_init();
    ble_advertising_init();
    ble_advertising_start();

    bsp_board_led_on(LED1);

    while(true) {
        if(NRF_LOG_PROCESS() == false) {
            nrf_pwr_mgmt_run();
        }
    }
}
```
