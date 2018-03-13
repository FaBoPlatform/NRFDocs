# エラーハンドラ

## Error Handlerの実装とテスト

```c
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#define NRF_LOG_MODULE_NAME "APP"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "bsp.h"

#define LED1 BSP_BOARD_LED_0
#define LED2 BSP_BOARD_LED_1
#define LED3 BSP_BOARD_LED_2
#define LED4 BSP_BOARD_LED_3


/**@brief Error handler
 */
void app_error_fault_handler(uint32_t id, uint32_t pc, uint32_t info)
{
	NRF_LOG_INFO("id:0x%x\r\n", id)
	NRF_LOG_INFO("info:0x%x\r\n", pc)
	NRF_LOG_INFO("pc:0x%x\r\n", info);
	NRF_LOG_FLUSH();
}


/**@brief Function for the LEDs initialization.
 *
 * @details Initializes all LEDs used by the application.
 */
static void leds_init(void)
{
    bsp_board_leds_init();
}

/**@brief Function for application main entry.
 */
int main(void)
{        
        ret_code_t err_code;
        err_code = NRF_LOG_INIT(NULL);
				
        NRF_LOG_INFO("TEST\r\n");
		NRF_LOG_FLUSH();
		
		// Test of error
		APP_ERROR_CHECK(1);
	
		leds_init();
        bsp_board_led_on(LED1);
        bsp_board_led_on(LED2);
        bsp_board_led_on(LED3);
        bsp_board_led_on(LED4);
}


/**
 * @}
 */
```


## Error Handlerが呼ばれたらSystemReset

app_error_fault_handlerが呼ばれたら、NVIC_SystemReset()でシステムリセットする。
また、err_code = NRF_LOG_INIT(NULL);のerr_codeをAPP_ERROR_CHECKでチェックする。


```c
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#define NRF_LOG_MODULE_NAME "APP"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "bsp.h"

#define LED1 BSP_BOARD_LED_0
#define LED2 BSP_BOARD_LED_1
#define LED3 BSP_BOARD_LED_2
#define LED4 BSP_BOARD_LED_3


/**@brief Error handler
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

/**@brief Function for application main entry.
 */
int main(void)
{        
        ret_code_t err_code;
        err_code = NRF_LOG_INIT(NULL);
		APP_ERROR_CHECK(err_code);

        NRF_LOG_INFO("TEST\r\n");
		NRF_LOG_FLUSH();
		
		// Test of error
		APP_ERROR_CHECK(1);
	
		leds_init();
        bsp_board_led_on(LED1);
        bsp_board_led_on(LED2);
        bsp_board_led_on(LED3);
        bsp_board_led_on(LED4);
}


/**
 * @}
 */
```
