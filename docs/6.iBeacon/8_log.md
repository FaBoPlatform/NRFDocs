# Logの出力

```c
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "nrf.h"
#define NRF_LOG_MODULE_NAME "APP"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "bsp.h"

#define LED1 BSP_BOARD_LED_0
#define LED2 BSP_BOARD_LED_1
#define LED3 BSP_BOARD_LED_2
#define LED4 BSP_BOARD_LED_3

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

## sdk_config.hの変更

![](./img/log_001.png)

## Tera Termの起動と設定

![](./img/log_002.png)

![](./img/log_003.png)

![](./img/log_004.png)

