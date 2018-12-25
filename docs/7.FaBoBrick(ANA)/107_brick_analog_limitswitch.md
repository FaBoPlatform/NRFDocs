# #107 LimitSwitch Brick

![](/img/LIMITSWICH107/107.jpg)
<!--COLORME-->

## Overview
リミットスイッチを使ったBrickです。

I/OピンよりスイッチのON/OFFの状態を取得することができます。

機械の自動停止や位置検出の際に使用します。

## Connecting

![](/img/LIMITSWICH107/FaBo_107_LIMITSWITCH_CONNECT.JPG)

### Arduino

## Support

## Schematic
![](/img/100_analog/schematic/107_limitswitch.png)

## Sample Code
A1コネクタにLimitSwitch Brickを接続し、A0コネクタに接続したLED Brickの点灯/消灯を制御しています。

```c

#include <stdbool.h>
#include <stdint.h>
#include "nrf.h"
#include "bsp.h"
#include "nrf_delay.h"
#include "app_util_platform.h"

#define NRF_LOG_MODULE_NAME "FABO_107_LIMITSWITCH"
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
				uint32_t LimitSwitch = 0;
				static uint32_t push_time = 0;
				LimitSwitch = nrf_gpio_pin_read(FaBo_Shinobi_ANALOGPIN);

				if (LimitSwitch == 1) {
					nrf_gpio_pin_set(FaBo_Shinobi_LEDPIN);
					NRF_LOG_INFO("PUSH LIMITSWITCH : %d\r\n",push_time);
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
- リミットスイッチ

## GitHub
