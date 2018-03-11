# #105 Vibrator Brick

![](/img/VIBRATOR105/105.jpg)
<!--COLORME-->

## Overview
振動モーターを使用したBrickです。

I/Oピンから振動モーターのON/OFFを制御することができます。

## Connecting

## Parts Specification
| Document |
|:--|
| [LA3R5-480AH1](http://akizukidenshi.com/catalog/g/gP-06744/) |

## Schematic
<center>![](../img/VIBRATOR105/shematic_vibrator.PNG)
## Sample Code

タイマーでバイブレーターを0.5秒ごとに作動、停止させます。
動作には、５Vの電源が必要となり、そのままでは動きません。代用としてLED Brickで確認しましょう。


```c

#include <stdbool.h>
#include <stdint.h>
#include "nrf.h"
#include "nrf_drv_timer.h"
#include "bsp.h"
#include "app_error.h"

const nrf_drv_timer_t TIMER_LED = NRF_DRV_TIMER_INSTANCE(0);

#define PIN_NUMBER 3

void timer_led_event_handler(nrf_timer_event_t event_type, void* p_context)
{


    switch (event_type)
    {
        case NRF_TIMER_EVENT_COMPARE0:
						nrf_gpio_pin_toggle(PIN_NUMBER);
            break;

        default:
            break;
    }
}


int main(void)
{
    uint32_t time_ms = 500;
    uint32_t time_ticks;
    uint32_t err_code = NRF_SUCCESS;

		LEDS_CONFIGURE(1 << PIN_NUMBER);

    nrf_drv_timer_config_t timer_cfg = NRF_DRV_TIMER_DEFAULT_CONFIG;
    err_code = nrf_drv_timer_init(&TIMER_LED, &timer_cfg, timer_led_event_handler);
    APP_ERROR_CHECK(err_code);

    time_ticks = nrf_drv_timer_ms_to_ticks(&TIMER_LED, time_ms);

    nrf_drv_timer_extended_compare(
         &TIMER_LED, NRF_TIMER_CC_CHANNEL0, time_ticks, NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK, true);

    nrf_drv_timer_enable(&TIMER_LED);

    while (1)
    {
        __WFI();
    }
}

```


## 構成Parts
- 振動モーター LA3R5-480AH1

## GitHub
