# Advertising DataのInit

## ソースコード

```c
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#define NRF_LOG_MODULE_NAME "APP"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "bsp.h"
#include "ble.h"
#include "ble_hci.h"
#include "ble_srv_common.h"
#include "ble_advdata.h"
#include "ble_conn_params.h"
#include "ble_lbs.h"
#include "ble_gap.h"
#include "softdevice_handler.h"

#define LED1 BSP_BOARD_LED_0
#define LED2 BSP_BOARD_LED_1
#define LED3 BSP_BOARD_LED_2
#define LED4 BSP_BOARD_LED_3

#define CENTRAL_LINK_COUNT              0                                           
#define PERIPHERAL_LINK_COUNT           1 

#define APP_COMPANY_IDENTIFIER 0x002C // Apple
#define APP_BEACON_INFO_LENGTH 0x17 // Beaconのデータの長さ
#define APP_BEACON_TYPE 0x02, 0x15 // Beaconのタイプ
#define APP_BEACON_UUID     0x01, 0x12, 0x23, 0x34, \
                            0x45, 0xaa, 0x67, 0x78, \
                            0x89, 0xba, 0x13, 0xbc, \
                            0x33, 0x1a, 0x22, 0xf0 // iBeaconのUUID
#define APP_MAJOR_VALUE 0x01, 0x02                        // iBeaconのMajor 
#define APP_MINOR_VALUE 0x03, 0x04                        // iBeaconのMinor 
#define APP_MEASURED_RSSI 0xC3 // RSSI出力の計測値

static uint8_t m_beacon_info[APP_BEACON_INFO_LENGTH] =  // iBeaconのAdvertising Data
{
    APP_BEACON_TYPE,
    APP_BEACON_UUID,     
    APP_MAJOR_VALUE,     
    APP_MINOR_VALUE,    
    APP_MEASURED_RSSI
};

/**@brief Error
 */
void app_error_fault_handler(uint32_t id, uint32_t pc, uint32_t info)
{
	NRF_LOG_INFO("id:0x%x\r\n", id)
	NRF_LOG_INFO("info:0x%x\r\n", pc)
	NRF_LOG_INFO("pc:0x%x\r\n", info);
	NRF_LOG_FLUSH();
	NVIC_SystemReset();
}


/**@brief Function for the LEDs initialization.
 *
 * @details Initializes all LEDs used by the application.
 */
static void leds_init(void)
{
    bsp_board_leds_init();
}

/**@brief Function for the Power Manager.
 */
static void power_manage(void)
{
    uint32_t err_code = sd_app_evt_wait();

    APP_ERROR_CHECK(err_code);
}

/**@brief Function for dispatching a BLE stack event.
 */
static void ble_evt_dispatch(ble_evt_t * p_ble_evt)
{
	
}

/**@brief Function for initializing the BLE stack.
 */
static void ble_stack_init(void) 
{
	// SoftDeviceの内部発振と外部発振等の設定
	uint32_t err_code;
	nrf_clock_lf_cfg_t clock_lf_cfg = NRF_CLOCK_LFCLKSRC;
	SOFTDEVICE_HANDLER_INIT(&clock_lf_cfg, NULL);
	
	// DefaultのConfigを取得
	ble_enable_params_t ble_enable_params;
	err_code = softdevice_enable_get_default_config(CENTRAL_LINK_COUNT,PERIPHERAL_LINK_COUNT,&ble_enable_params);
	APP_ERROR_CHECK(err_code);
	
	// RAM要件を満たしているかチェック
	CHECK_RAM_START_ADDR(CENTRAL_LINK_COUNT,PERIPHERAL_LINK_COUNT);
	
	// BLE StackをEnableに
	err_code = softdevice_enable(&ble_enable_params);
	APP_ERROR_CHECK(err_code);
	
	// Eventハンドラを登録
	err_code = softdevice_ble_evt_handler_set(ble_evt_dispatch);
	APP_ERROR_CHECK(err_code);

	// Init完了時にLED1を点灯させる。
	bsp_board_led_on(LED1);
}

/**@brief Function for initializing the Advertising functionality.
 * /
static void advertising_init(void)
{
    uint32_t err_code;
   
    // AdvDataのManufacture Specificの領域の値の定義.
    ble_advdata_manuf_data_t manuf_specific_data;
    manuf_specific_data.company_identifier = APP_COMPANY_IDENTIFIER;
    manuf_specific_data.data.p_data = (uint8_t *) m_beacon_info;
    manuf_specific_data.data.size = APP_BEACON_INFO_LENGTH;

    // AdvDataを構築.
    ble_advdata_t advdata;
    memset(&advdata, 0, sizeof(advdata));
    
    // AdvDataの設定.
    advdata.name_type = BLE_ADVDATA_NO_NAME;
    advdata.include_appearance = true;
    advdata.flags = BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE;

    // Manufacture Specificの値を設定.
    advdata.p_manuf_specific_data = &manuf_specific_data;

    // AdvDataを登録.
    err_code = ble_advdata_set(&advdata, NULL);
    APP_ERROR_CHECK(err_code);
}

/**@brief Function for application main entry.
 */
int main(void)
{        
        ret_code_t err_code;
        err_code = NRF_LOG_INIT(NULL);
		PP_ERROR_CHECK(err_code);
		leds_init();
		ble_stack_init();
		advertising_init();
        
		// Enter main loop.
        for (;;)
        {
            if (NRF_LOG_PROCESS() == false)
            {
                power_manage();
            }
        }
}


/**
 * @}
 */
```
