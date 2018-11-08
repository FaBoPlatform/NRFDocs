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
|../nRF5_SDK/components/libraries/balloc|
|../nRF5_SDK/components/libraries/memobj|
|../nRF5_SDK/components/libraries/log/src|
|../nRF5_SDK/components/libraries/strerror|
|../nRF5_SDK/components/libraries/experimental_section_vars|
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
|nrf_drv_uart.c|../nRF5_SDK/integration/nrfx/legacy|
|nrf_fprintf.c|../nRF5_SDK/external/fprintf|
|nrf_fprintf_format.c|../nRF5_SDK/external/fprintf|
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

## Section
SEGGER_Flash.icfファイルを編集する。(SEGGER_Flash.icfはProject配下に自動生成されているハズ。以下抜粋)
```c
place in FLASH                           {  
                                           block tdata_load,                       // Thread-local-storage load image
                                           //この下の4Lineを追加する
										   section .log_const_data_FABO_107_LIMITSWITCH,
                                           section .log_const_data_app,
                                           section .log_backends,
                                           section .nrf_balloc
                                         };
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
ISR_HANDLER ExternalISR8
ISR_HANDLER ExternalISR9
ISR_HANDLER ExternalISR10
```

## Sample Code
A1コネクタにLimitSwitch Brickを接続し、A0コネクタに接続したLED Brickの点灯/消灯を制御しています。

```c
#include <stdbool.h>
#include <stdint.h>
#include "nrf.h"
#include "bsp.h"
#include "nrf_delay.h"
#include "app_util_platform.h"

#define NRF_LOG_MODULE_NAME FABO_107_LIMITSWITCH
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#define FaBo_Shinobi_ANALOGPIN 3
#define FaBo_Shinobi_LEDPIN 18

nrf_log_module_const_data_t*    __start_log_const_data;
nrf_log_module_dynamic_data_t*  __start_log_dynamic_data;
void*                           __stop_log_const_data;
void*                           __stop_log_dynamic_data;

static void gpio_init(void)
{
    nrf_gpio_cfg_sense_input(FaBo_Shinobi_ANALOGPIN, NRF_GPIO_PIN_PULLDOWN, NRF_GPIO_PIN_SENSE_HIGH);
    nrf_gpio_cfg_output(FaBo_Shinobi_LEDPIN);
    nrf_gpio_pin_clear(FaBo_Shinobi_LEDPIN);
}

void nrf_log_module_initialize()
{
    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();
    *(NRF_SECTION_ITEM_GET(log_const_data, nrf_log_module_const_data_t, NRF_LOG_MODULE_ID_GET_CONST(&NRF_LOG_ITEM_DATA_CONST(NRF_LOG_MODULE_NAME)) & 0x0000ffff)) = NRF_LOG_ITEM_DATA_CONST(NRF_LOG_MODULE_NAME);
}

int main(void)
{
    nrf_log_module_initialize();
    gpio_init();

    while (true)
    {
        uint32_t LimitSwitch = 0;
        static uint32_t push_time = 0;
        LimitSwitch = nrf_gpio_pin_read(FaBo_Shinobi_ANALOGPIN);

        if (LimitSwitch == 1) {
            nrf_gpio_pin_set(FaBo_Shinobi_LEDPIN);
            NRF_LOG_INFO("PUSH LIMITSWITCH push_time:%d",push_time);
            NRF_LOG_FLUSH();
            push_time++;
        } else {
            nrf_gpio_pin_clear(FaBo_Shinobi_LEDPIN);
        }
    }
}
```

## 構成Parts
- リミットスイッチ

## GitHub
