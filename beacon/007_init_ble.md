# BLEのInit

iBeaconをは心するためにBLE StackのInit処理をおこないます。

## Incluedファイルの追加

```c
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
```

## Defineの追加

```c
#define CENTRAL_LINK_COUNT              0                                           
#define PERIPHERAL_LINK_COUNT           1 
```

## BLE Stackの　Init

```c
/**@brief Function for initializing the BLE stack.
 */
static void ble_stack_init(void) 
{
	uint32_t err_code;
	nrf_clock_lf_cfg_t clock_lf_cfg = NRF_CLOCK_LFCLKSRC;
	SOFTDEVICE_HANDLER_INIT(&clock_lf_cfg, NULL);
	
	ble_enable_params_t ble_enable_params;
	err_code = softdevice_enable_get_default_config(CENTRAL_LINK_COUNT,PERIPHERAL_LINK_COUNT,&ble_enable_params);
	APP_ERROR_CHECK(err_code);
	
	CHECK_RAM_START_ADDR(CENTRAL_LINK_COUNT,PERIPHERAL_LINK_COUNT);
	
	err_code = softdevice_enable(&ble_enable_params);
	APP_ERROR_CHECK(err_code);
	
	err_code = softdevice_ble_evt_handler_set(ble_evt_dispatch);
	APP_ERROR_CHECK(err_code);

	bsp_board_led_on(LED1);
}
```

> SOFTDEVICE_HANDLER_INIT

Macroの中身。内部発振と外部発振等の設定ができる。内部発振使用の場合は、精度は250ppm。

```c
do                                                                                             
{                                                                                              
    static uint32_t BLE_EVT_BUFFER[CEIL_DIV(BLE_STACK_EVT_MSG_BUF_SIZE, sizeof(uint32_t))];    
    uint32_t ERR_CODE;                                                                         
    ERR_CODE = softdevice_handler_init((CLOCK_SOURCE),                                         
                                       BLE_EVT_BUFFER,                                         
                                       sizeof(BLE_EVT_BUFFER),                                 
                                       EVT_HANDLER);      
    APP_ERROR_CHECK(ERR_CODE);                                                                 
} while (0)
```

> softdevice_enable_get_default_config

Central, Peripheralの接続数を指定して、Defaultのconfigを生成

> CHECK_RAM_START_ADDR

Macro。RAM要件が満たされているか、チェック。

> softdevice_enable

SoftDeviceをEnableにする。

>  softdevice_ble_evt_handler_set

BLEのイベントハンドラを設定する。




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

/**@brief Function for application main entry.
 */
int main(void)
{        
        ret_code_t err_code;
        err_code = NRF_LOG_INIT(NULL);
		APP_ERROR_CHECK(err_code);
		leds_init();
		ble_stack_init();
        
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
