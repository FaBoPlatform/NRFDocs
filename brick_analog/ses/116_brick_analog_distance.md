# #116 Distance Brick

![](/img/DISTANCE116/116.jpg)
<!--COLORME-->

## Overview
距離センサーモジュールを使用したBrickです。

I/Oピンより距離センサーの正面についているレンズから物体までの距離をアナログ値(0〜1023)で取得することができます。

測定可能な距離は10〜80cmとなっています。

<center>![](../img/DISTANCE116/GP2Y0A21.jpg)


## Connecting

![](/img/DISTANCE116/FaBo_116_DISTANCE_CONNECT.JPG)

## GP2Y0A21YK Datasheet
| Document |
| -- |
| [GP2Y0A21YK Datasheet](http://www.sharpsma.com/webfm_send/1208) |

## User Include Directories
Solution Option -> Preprocessor -> User Include Directoriesに以下を追加する。(../nRF5_SDKの部分は適宜変えてください。)

|Path|
|:--|
|../nRF5_SDK/modules/nrfx/drivers/src|
|../nRF5_SDK/modules/nrfx/drivers/src/prs|
|../nRF5_SDK/components/libraries/mutex|
|../nRF5_SDK/components/libraries/atomic|
|../nRF5_SDK/components/libraries/ringbuf|
|../nRF5_SDK/external/fprintf|
|../nRF5_SDK/components/libraries/balloc|
|../nRF5_SDK/components/libraries/memobj|
|../nRF5_SDK/components/libraries/log/src|
|../nRF5_SDK/components/libraries/strerror|
|../nRF5_SDK/components/libraries/log|
|../nRF5_SDK/components/libraries/experimental_section_vars|
|../nRF5_SDK/components/libraries/pwr_mgmt|
|../nRF5_SDK/components/libraries/delay|
|../nRF5_SDK/modules/nrfx/hal|
|../nRF5_SDK/components/boards|
|../nRF5_SDK/components/drivers_nrf/nrf_soc_nosd|
|../nRF5_SDK/components/libraries/util|
|../nRF5_SDK/integration/nrfx|
|../nRF5_SDK/modules/nrfx|
|../nRF5_SDK/modules/nrfx/drivers/include|
|../nRF5_SDK/integration/nrfx/legacy|
|../nRF5_SDK/components/toolchain/cmsis/include|
|../nRF5_SDK/modules/nrfx/mdk|
|.|

## Preprocessor Definitions
Solution Option -> Preprocessor -> Preprocessor Definitionsに以下を追加する。

|COPT|
|:--|
|NRFX_SAADC_ENABLED|
|SAADC_ENABLED|
|NRFX_PPI_ENABLED|
|PPI_ENABLED|
|NRFX_POWER_ENABLED|
|POWER_ENABLED|
|NRFX_TIMER0_ENABLED|
|TIMER0_ENABLED|
|NRFX_TIMER_ENABLED|
|TIMER_ENABLED|
|NRF52832_XXAB|
|BOARD_CUSTOM|

## SDK File
Projectに以下のファイルを追加する。(../nRF5_SDKの部分は適宜変えてください。)

|File|Path|
|:--|:--|
|app_error.c|../nRF5_SDK/components/libraries/util|
|app_error_handler_gcc.c|../nRF5_SDK/components/libraries/util|
|app_error_weak.c|../nRF5_SDK/components/libraries/util|
|app_util_platform.c|../nRF5_SDK/components/libraries/util|
|nrf_atomic.c|../nRF5_SDK/components/libraries/atomic|
|nrf_balloc.c|../nRF5_SDK/components/libraries/balloc|
|nrf_drv_power.c|../nRF5_SDK/integration/nrfx/legacy|
|nrf_drv_ppi.c|../nRF5_SDK/integration/nrfx/legacy|
|nrf_drv_uart.c|../nRF5_SDK/integration/nrfx/legacy|
|nrf_fprintf.c|../nRF5_SDK/external/fprintf|
|nrf_fprintf_format.c|../nRF5_SDK/external/fprintf|
|nrf_log_backend_serial.c|../nRF5_SDK/components/libraries/log/src|
|nrf_log_backend_uart.c|../nRF5_SDK/components/libraries/log/src|
|nrf_log_default_backends.c|../nRF5_SDK/components/libraries/log/src|
|nrf_log_frontend.c|../nRF5_SDK/components/libraries/log/src|
|nrf_log_str_formatter.c|../nRF5_SDK/components/libraries/log/src|
|nrf_memobj.c|../nRF5_SDK/components/libraries/memobj|
|nrf_pwr_mgmt.c|../nRF5_SDK/components/libraries/pwr_mgmt|
|nrf_ringbuf.c|../nRF5_SDK/components/libraries/ringbuf|
|nrf_section_iter.c|../nRF5_SDK/components/libraries/experimental_section_vars|
|nrf_strerror.c|../nRF5_SDK/components/libraries/strerror|
|nrfx_power.c|../nRF5_SDK/modules/nrfx/drivers/src|
|nrfx_ppi.c|../nRF5_SDK/modules/nrfx/drivers/src|
|nrfx_prs.c|../nRF5_SDK/modules/nrfx/drivers/src/prs|
|nrfx_saadc.c|../nRF5_SDK/modules/nrfx/drivers/src|
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
ISR_HANDLER UARTE0_UART0_IRQHandler
ISR_HANDLER ExternalISR3
ISR_HANDLER ExternalISR4
ISR_HANDLER ExternalISR5
ISR_HANDLER ExternalISR6
ISR_HANDLER SAADC_IRQHandler
ISR_HANDLER ExternalISR8
ISR_HANDLER ExternalISR9
ISR_HANDLER ExternalISR10
```

## Sample Code
main.c
```c
#include <stdbool.h>
#include <stdint.h>
#include "nrf.h"
#include "bsp.h"
#include "nrf_delay.h"
#include "app_util_platform.h"

#define NRF_LOG_MODULE_NAME FABO_113_IR_RECEIVER
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#define FaBo_Shinobi_ANALOGPIN 3
#define FaBo_Shinobi_LEDPIN 18

nrf_log_module_const_data_t*    __start_log_const_data;
void*                           __stop_log_const_data;
nrf_log_module_dynamic_data_t*  __start_log_dynamic_data;
void*                           __stop_log_dynamic_data;

static void gpio_init(void)
{
    nrf_gpio_cfg_sense_input(FaBo_Shinobi_ANALOGPIN, NRF_GPIO_PIN_PULLDOWN, NRF_GPIO_PIN_SENSE_HIGH);
    nrf_gpio_cfg_output(FaBo_Shinobi_LEDPIN);
    nrf_gpio_pin_clear(FaBo_Shinobi_LEDPIN);
}

int main(void)
{
    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();

    gpio_init();

    NRF_LOG_INFO("FaBo_Shinobi_IR_RECEVIER SAMPLE.");
    NRF_LOG_FLUSH();

    while (true)
    {
        uint32_t BUTTON_SWITCH = 0;
        static uint32_t push_time = 0;
        BUTTON_SWITCH = nrf_gpio_pin_read(FaBo_Shinobi_ANALOGPIN);

        if (BUTTON_SWITCH == 1) {
            nrf_gpio_pin_set(FaBo_Shinobi_LEDPIN);
            NRF_LOG_INFO("IR_Received! push time:%d", push_time);
            NRF_LOG_FLUSH();
            push_time++;
        } else {
            nrf_gpio_pin_clear(FaBo_Shinobi_LEDPIN);
        }
    }
}
```

TeraTermを起動し確認します。リセットボタンを押すと起動します。
<center>![](../img/DISTANCE116/TeraTerm116.png)


## 構成Parts
- 距離センサーモジュール GP2Y0A21YK

## GitHub
