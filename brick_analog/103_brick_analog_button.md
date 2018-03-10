# #103 Button Brick

## Overview
ボタンを使ったBrickです。I/OピンよりボタンのON/OFFの状態を取得することができます。


## Connecting


## Schematic


## Sample Code


```c
#include <stdbool.h>
#include <stdint.h>
#include "nrf.h"
#include "bsp.h"
#include "nrf_delay.h"
#include "app_util_platform.h"

#define NRF_LOG_MODULE_NAME "FABO 103 BUTTON"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

#define FaBo_Shinobi_ANALOGPIN 3

static void gpio_init(void)
{
	nrf_gpio_cfg_sense_input(FaBo_Shinobi_ANALOGPIN, NRF_GPIO_PIN_PULLDOWN, NRF_GPIO_PIN_SENSE_HIGH);
	nrf_gpio_cfg_output(BSP_LED_0);
	nrf_gpio_pin_clear(BSP_LED_0);
}

int main(void)
{
		uint32_t err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);
		gpio_init();

    while (true)
    {
				uint32_t BUTTON_SWITCH = 0;
				static uint32_t push_time = 0;
				BUTTON_SWITCH = nrf_gpio_pin_read(FaBo_Shinobi_ANALOGPIN);

				if (BUTTON_SWITCH == 1) {
					nrf_gpio_pin_set(BSP_LED_0);
					NRF_LOG_INFO("PUSH BUTTON : %d\r\n",push_time);
					NRF_LOG_FLUSH();
					push_time++;
				}
				else {
					nrf_gpio_pin_clear(BSP_LED_0);
				}
    }

}

```



## 構成Parts
- 12mm角タクトスイッチ

## GitHub
