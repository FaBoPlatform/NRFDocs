# #103 Button Brick

<center>![](/img/BUTTON103/103.jpg)

## Overview
ボタンを使ったBrickです。I/OピンよりボタンのON/OFFの状態を取得することができます。


## Connecting

![](/img/BUTTON103/Fabo_103_BUTTON_CONET.JPG)

## Schematic

## Sample Code

```c

#include <stdbool.h>
#include <stdint.h>
#include "nrf.h"
#include "bsp.h"
#include "nrf_delay.h"
#include "app_util_platform.h"

#define NRF_LOG_MODULE_NAME "FABO_103_BUTTON"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

#define FaBo_Shinobi_ANALOGPIN 3
#define FaBo_Shinobi_LEDPIN 18

static void gpio_init(void)
{
	nrf_gpio_cfg_sense_input(FaBo_Shinobi_ANALOGPIN, NRF_GPIO_PIN_PULLDOWN, NRF_GPIO_PIN_SENSE_HIGH);
	nrf_gpio_cfg_output(FaBo_Shinobi_LEDPIN);
	nrf_gpio_pin_clear(FaBo_Shinobi_LEDPIN);
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
					nrf_gpio_pin_set(FaBo_Shinobi_LEDPIN);
					NRF_LOG_INFO("PUSH BUTTON : %d\r\n",push_time);
					NRF_LOG_FLUSH();
					push_time++;
				}
				else {
					nrf_gpio_pin_clear(FaBo_Shinobi_LEDPIN);
				}
    }

}


```



## 構成Parts
- 12mm角タクトスイッチ

## GitHub
