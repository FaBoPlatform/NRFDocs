# #121 IR_RECEVIER Brick

## Overview

## Connecting

## Schematic

## Sample

Shinobi_NRFのボタンを利用します。ボタンを押すと、赤外線LEDが発行されます。

```c

#include <stdbool.h>
#include <stdint.h>
#include "nrf.h"
#include "bsp.h"
#include "nrf_delay.h"
#include "app_util_platform.h"

#define NRF_LOG_MODULE_NAME "FABO 121 IR_RECEIVER"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

#define FaBo_Shinobi_ANALOGPIN 16
#define FaBo_Shinobi_BUTTONPIN 3

static void gpio_init(void)
{
	nrf_gpio_cfg_sense_input(FaBo_Shinobi_ANALOGPIN, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
	nrf_gpio_cfg_output(FaBo_Shinobi_BUTTONPIN);
	nrf_gpio_pin_clear(FaBo_Shinobi_BUTTONPIN);
}

int main(void)
{
		uint32_t err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);
		NRF_LOG_INFO("FaBo_Shinobi_IR_RECEVIER SAMPLE.\r\n");
		NRF_LOG_FLUSH();
		gpio_init();

    while (true)
    {
				uint32_t BUTTON_SWITCH = 0;
				static uint32_t push_time = 0;
				BUTTON_SWITCH = nrf_gpio_pin_read(FaBo_Shinobi_ANALOGPIN);

				if (BUTTON_SWITCH == 1) {
					nrf_gpio_pin_clear(FaBo_Shinobi_BUTTONPIN);
				}
				else {
					nrf_gpio_pin_set(FaBo_Shinobi_BUTTONPIN);
					NRF_LOG_INFO("Button pressed Emission.: %d\r\n",push_time);
					NRF_LOG_FLUSH();
					push_time++;
				}
    }

}



```

## 構成Parts
- 12mm角タクトスイッチ

## GitHub
- https://github.com/FaBoPlatform/FaBo/tree/master/103_button
