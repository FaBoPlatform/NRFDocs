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

## User Include Directories
Solution Option -> Preprocessor -> User Include Directoriesに以下を追加する。(../nRF5_SDKの部分は適宜変えてください。)

|Path|
|:--|
|../nRF5_SDK/modules/nrfx/drivers/src/prs|
|../nRF5_SDK/modules/nrfx/drivers/src|
|../nRF5_SDK/components/libraries/atomic|
|../nRF5_SDK/components/libraries/ringbuf|
|../nRF5_SDK/external/fprintf|
|../nRF5_SDK/components/libraries/balloc|
|../nRF5_SDK/components/libraries/memobj|
|../nRF5_SDK/components/libraries/log/src|
|../nRF5_SDK/components/libraries/strerror|
|../nRF5_SDK/components/libraries/experimental_section_vars|
|../nRF5_SDK/components/libraries/log|
|../nRF5_SDK/components/libraries/button|
|../nRF5_SDK/modules/nrfx/hal|
|../nRF5_SDK/components/boards|
|../nRF5_SDK/components/drivers_nrf/nrf_soc_nosd|
|../nRF5_SDK/integration/nrfx|
|../nRF5_SDK/modules/nrfx|
|../nRF5_SDK/modules/nrfx/drivers/include|
|../nRF5_SDK/components/toolchain/cmsis/include|
|../nRF5_SDK/integration/nrfx/legacy|
|../nRF5_SDK/modules/nrfx/mdk|
|../nRF5_SDK/components/libraries/bsp|
|../nRF5_SDK/components/libraries/util|
|.|

## Preprocessor Definitions
Solution Option -> Preprocessor -> Preprocessor Definitionsに以下を追加する。

|COPT|
|:--|
|NRFX_TIMER0_ENABLED|
|NRFX_TIMER_ENABLED|
|TIMER0_ENABLED|
|TIMER_ENABLED|
|NRF52832_XXAB|
|BOARD_CUSTOM|

## SDK File
Projectに以下のファイルを追加する。(../nRF5_SDKの部分は適宜変えてください。)

|File|Path|
|:--|:--|
|app_error_handler_gcc.c|../nRF5_SDK/components/libraries/util|
|app_error_weak.c|../nRF5_SDK/components/libraries/util|
|app_error.c|../nRF5_SDK/components/libraries/util|
|app_util_platform.c|../nRF5_SDK/components/libraries/util|
|nrf_atomic.c|../nRF5_SDK/components/libraries/atomic|
|nrf_balloc.c|../nRF5_SDK/components/libraries/balloc|
|nrf_drv_uart.c|../nRF5_SDK/integration/nrfx/legacy|
|nrf_fprintf_format.c|../nRF5_SDK/external/fprintf|
|nrf_fprintf.c|../nRF5_SDK/external/fprintf|
|nrf_log_backend_serial.c|../nRF5_SDK/components/libraries/log/src|
|nrf_log_backend_uart.c|../nRF5_SDK/components/libraries/log/src|
|nrf_log_default_backends.c|../nRF5_SDK/components/libraries/log/src|
|nrf_log_frontend.c|../nRF5_SDK/components/libraries/log/src|
|nrf_log_str_formatter.c|../nRF5_SDK/components/libraries/log/src|
|nrf_memobj.c|../nRF5_SDK/components/libraries/memobj|
|nrf_ringbuf.c|../nRF5_SDK/components/libraries/ringbuf|
|nrf_strerror.c|../nRF5_SDK/components/libraries/strerror|
|nrfx_prs.c|../nRF5_SDK/modules/nrfx/drivers/src/prs|
|nrfx_timer.c|../nRF5_SDK/modules/nrfx/drivers/src|
|nrfx_uart.c|../nRF5_SDK/modules/nrfx/drivers/src|
|nrfx_uarte.c|../nRF5_SDK/modules/nrfx/drivers/src|

## Section
SEGGER_Flash.icfファイルを編集する。(SEGGER_Flash.icfはProject配下に自動生成されている。以下抜粋)
```c
 :

define block log_const_data_start with size = 8 { symbol __start_log_const_data };
define block log_const_data_list { section .log_const_data* };
define block log_const_data_stop with size = 8 { symbol __stop_log_const_data };
define block log_const_data with fixed order { block log_const_data_start, block log_const_data_list, block log_const_data_stop };

 :

place in FLASH                           {
                                           block tdata_load,                       // Thread-local-storage load image
                                           section .log_backends,
                                           section .nrf_balloc,
                                           block log_const_data
                                         };
 :
```

## IRQHandler
Cortex_M_Startup.sファイルを編集する。(長いので抜粋)
```c
ISR_HANDLER ExternalISR0
ISR_HANDLER ExternalISR1
ISR_HANDLER UARTE0_UART0_IRQHandler //ExternalISR2
ISR_HANDLER ExternalISR3
ISR_HANDLER ExternalISR4
ISR_HANDLER ExternalISR5
ISR_HANDLER ExternalISR6
ISR_HANDLER ExternalISR7
ISR_HANDLER TIMER0_IRQHandler //ExternalISR8
ISR_HANDLER ExternalISR9
```

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
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#define NRF_LOG_MODULE_NAME FABO_105_VIBRATOR
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define PIN_NUMBER 3

const nrf_drv_timer_t TIMER_LED = NRF_DRV_TIMER_INSTANCE(0);
nrf_log_module_const_data_t*    __start_log_const_data;
void*                           __stop_log_const_data;
nrf_log_module_dynamic_data_t*  __start_log_dynamic_data;
void*                           __stop_log_dynamic_data;

void timer_led_event_handler(nrf_timer_event_t event_type, void* p_context)
{
    static uint32_t counter = 0;
    NRF_LOG_INFO("timer_led_event_handler() counter = %d, event_type = %d", counter, event_type);
    switch (event_type)
    {
        case NRF_TIMER_EVENT_COMPARE0:
            nrf_gpio_pin_toggle(PIN_NUMBER);
            break;
        default:
            break;
    }
    counter++;
}

int main(void)
{
    uint32_t time_ms = 500;
    uint32_t time_ticks;
    uint32_t err_code = NRF_SUCCESS;

    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();

    int clock = 16000000 / 2;

    LEDS_CONFIGURE(1 << PIN_NUMBER);

    nrf_drv_timer_config_t timer_cfg = NRF_DRV_TIMER_DEFAULT_CONFIG;
    timer_cfg.bit_width = NRF_TIMER_BIT_WIDTH_32;    
    APP_ERROR_CHECK(nrf_drv_timer_init(&TIMER_LED, &timer_cfg, timer_led_event_handler));

    time_ticks = nrf_drv_timer_ms_to_ticks(&TIMER_LED, time_ms);

    nrf_drv_timer_extended_compare(
         &TIMER_LED, NRF_TIMER_CC_CHANNEL0, time_ticks, NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK, true);

    nrf_drv_timer_enable(&TIMER_LED);

    while (1)
    {
        __WFI();
        NRF_LOG_FLUSH();
    }
}
```


## 構成Parts
- 振動モーター LA3R5-480AH1

## GitHub
