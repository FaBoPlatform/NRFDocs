# #103 Button Brick

![](/img/BUTTON103/103.jpg)

## Overview
ボタンを使ったBrickです。I/OピンよりボタンのON/OFFの状態を取得することができます。


## Connecting

![](/img/BUTTON103/Fabo_103_BUTTON_CONET.JPG)

## Schematic

## User Include Directories
Solution Option -> Preprocessor -> User Include Directoriesに以下を追加する。(../nRF5_SDKの部分は適宜変えてください。)

|Path|
|:--|
|../nRF5_SDK/modules/nrfx/drivers/src/prs|
|../nRF5_SDK/modules/nrfx/drivers/src|
|../nRF5_SDK/components/libraries/atomic|
|../nRF5_SDK/components/libraries/ringbuf|
|../nRF5_SDK/modules/nrfx/drivers/include|
|../nRF5_SDK/integration/nrfx/legacy|
|../nRF5_SDK/external/fprintf|
|../nRF5_SDK/components/libraries/strerror|
|../nRF5_SDK/components/libraries/experimental_section_vars|
|../nRF5_SDK/components/libraries/balloc|
|../nRF5_SDK/components/libraries/memobj|
|../nRF5_SDK/components/libraries/log/src|
|../nRF5_SDK/components/libraries/log|
|../nRF5_SDK/components/libraries/delay|
|../nRF5_SDK/components/libraries/button|
|../nRF5_SDK/components/drivers_nrf/nrf_soc_nosd|
|../nRF5_SDK/components/libraries/util|
|../nRF5_SDK/integration/nrfx|
|../nRF5_SDK/modules/nrfx|
|../nRF5_SDK/modules/nrfx/hal|
|../nRF5_SDK/components/boards|
|../nRF5_SDK/components/libraries/bsp|
|../nRF5_SDK/components/toolchain/cmsis/include|
|../nRF5_SDK/modules/nrfx/mdk|
|.|

## Preprocessor Definitions
Solution Option -> Preprocessor -> Preprocessor Definitionsに以下を追加する。

|COPT|
|:--|
|BOARD_CUSTOM|
|NRF52832_XXAA|

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
|nrfx_uart.c|../nRF5_SDK/modules/nrfx/drivers/src|
|nrfx_uarte.c|../nRF5_SDK/modules/nrfx/drivers/src|

## SDK Config
sdk_config.hのNRF_LOG_DEFERREDをOFF(0)に変更する。

## Sample Code

```c

#include <stdbool.h>
#include <stdint.h>
#include "nrf.h"
#include "bsp.h"
#include "nrf_delay.h"
#include "app_util_platform.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#define NRF_LOG_MODULE_NAME FABO_103_BUTTON
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

nrf_log_module_const_data_t* __start_log_const_data;
void* __stop_log_const_data;
nrf_log_module_dynamic_data_t* __start_log_dynamic_data;

#define FaBo_Shinobi_ANALOGPIN 3
#define FaBo_Shinobi_LEDPIN 18

static void nrf_log_module_initialize()
{
    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();
    *(NRF_SECTION_ITEM_GET(log_const_data, nrf_log_module_const_data_t, NRF_LOG_MODULE_ID_GET_CONST(&NRF_LOG_ITEM_DATA_CONST(NRF_LOG_MODULE_NAME)) & 0x0000ffff)) = NRF_LOG_ITEM_DATA_CONST(NRF_LOG_MODULE_NAME);
}

static void gpio_init(void)
{
    nrf_gpio_cfg_sense_input(FaBo_Shinobi_ANALOGPIN, NRF_GPIO_PIN_PULLDOWN, NRF_GPIO_PIN_SENSE_HIGH);
    nrf_gpio_cfg_output(FaBo_Shinobi_LEDPIN);
    nrf_gpio_pin_clear(FaBo_Shinobi_LEDPIN);
}

int main(void)
{
    nrf_log_module_initialize();
    gpio_init();

    while (true)
    {
        uint32_t BUTTON_SWITCH = 0;
        static uint32_t push_time = 0;
        BUTTON_SWITCH = nrf_gpio_pin_read(FaBo_Shinobi_ANALOGPIN);
        if (BUTTON_SWITCH == 1) {
            nrf_gpio_pin_set(FaBo_Shinobi_LEDPIN);
            NRF_LOG_INFO("PUSH BUTTON push_time:%d", push_time);
            NRF_LOG_FLUSH();
            push_time++;
        } else {
            nrf_gpio_pin_clear(FaBo_Shinobi_LEDPIN);
        }    
    }
}


```



## 構成Parts
- 12mm角タクトスイッチ

## GitHub
