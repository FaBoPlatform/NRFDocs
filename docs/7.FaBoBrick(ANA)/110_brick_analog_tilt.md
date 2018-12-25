# #110 Tilt Brick

![](/img/TILT110/110.jpg)
<!--COLORME-->

## Overview
傾斜センサーを使用したBrickです。

I/Oピンより傾斜センサーの状態をデジタル値(0〜1)取得することができます。

黒い部分の中に玉が入っていて傾くとデジタル値が変化します。

LED Brickを点灯/消灯させる際などに使用します。


## Connecting

![](/img/TILT110/FaBo_110_TILT_CONNECT.JPG)

## Schematic
![](/img/100_analog/schematic/110_tilt.png)

## Sample Code

```c
#include <stdbool.h>
#include <stdint.h>
#include "nrf.h"
#include "bsp.h"
#include "nrf_delay.h"
#include "app_util_platform.h"

#define NRF_LOG_MODULE_NAME "FABO 110 TILT"
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
				uint32_t TILT_PIN = 0;
				TILT_PIN = nrf_gpio_pin_read(FaBo_Shinobi_ANALOGPIN);

				if (TILT_PIN == 1) {
					nrf_gpio_pin_set(BSP_LED_0);
					NRF_LOG_INFO("Detect Slope.\r\n");
					NRF_LOG_FLUSH();
				}
				else {
					nrf_gpio_pin_clear(BSP_LED_0);
				}
    }

}


```

## 構成Parts
- 傾斜(振動)スイッチ

## GitHub
