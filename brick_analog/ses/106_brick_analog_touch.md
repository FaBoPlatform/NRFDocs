# #106 Touch Brick
![](/img/TOUCH106/106.jpg)
<!--COLORME-->

## Overview
感圧センサーを使用したタッチセンサーBrickです。
I/Oピンより、感圧部分に加えられた力の大きさの変化をアナログ値で取得することができます。

## Connecting

![](/img/TOUCH106/FaBo_106_TOUCH_CONNECT.JPG)

## Datasheet
| Document |
|:--|
| [Datasheet](http://interlinkelectronics.com/datasheets/Datasheet_FSR.pdf) |

## Schematic
![](/img/100_analog/schematic/106_touch.png)

## User Include Directories
Solution Option -> Preprocessor -> User Include Directoriesに以下を追加する。(../nRF5_SDKの部分は適宜変えてください。)

|Path|
|:--|
|/nRF5_SDK/modules/nrfx/drivers/src/prs|
|/nRF5_SDK/modules/nrfx/drivers/src|
|/nRF5_SDK/components/libraries/mutex|
|/nRF5_SDK/components/libraries/atomic|
|/nRF5_SDK/components/libraries/ringbuf|
|/nRF5_SDK/external/fprintf|
|/nRF5_SDK/components/libraries/balloc|
|/nRF5_SDK/components/libraries/memobj|
|/nRF5_SDK/components/libraries/log/src|
|/nRF5_SDK/components/libraries/strerror|
|/nRF5_SDK/components/libraries/experimental_section_vars|
|/nRF5_SDK/modules/nrfx/hal|
|/nRF5_SDK/components/drivers_nrf/nrf_soc_nosd|
|/nRF5_SDK/integration/nrfx|
|/nRF5_SDK/modules/nrfx|
|/nRF5_SDK/modules/nrfx/drivers/include|
|/nRF5_SDK/components/toolchain/cmsis/include|
|/nRF5_SDK/modules/nrfx/mdk|
|/nRF5_SDK/integration/nrfx/legacy|
|/nRF5_SDK/components/boards|
|/nRF5_SDK/components/libraries/util|
|/nRF5_SDK/components/libraries/delay|
|/nRF5_SDK/components/libraries/pwr_mgmt|
|/nRF5_SDK/components/libraries/log|
|.|

## Preprocessor Definitions
Solution Option -> Preprocessor -> Preprocessor Definitionsに以下を追加する。

|COPT|
|:--|
|NRFX_SAADC_ENABLED|
|NRFX_PPI_ENABLED|
|NRFX_POWER_ENABLED|
|NRFX_TIMER_ENABLED|
|NRFX_TIMER0_ENABLED|
|SAADC_ENABLED|
|PPI_ENABLED|
|POWER_ENABLED|
|TIMER_ENABLED|
|TIMER0_ENABLED|
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
|nrf_drv_power.c|../nRF5_SDK/integration/nrfx/legacy|
|nrf_drv_ppi.c|../nRF5_SDK/integration/nrfx/legacy|
|nrf_drv_uart.c|../nRF5_SDK/integration/nrfx/legacy|
|nrf_fprintf_format.c|../nRF5_SDK/external/fprintf|
|nrf_fprintf.c|../nRF5_SDK/external/fprintf|
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
SEGGER_Flash.icfファイルを編集する。(SEGGER_Flash.icfはProject配下に自動生成されているハズ。以下抜粋)
```c
place in FLASH                           {  
                                           block tdata_load,                       // Thread-local-storage load image
                                           //この下の4Lineを追加する
                                           section .log_const_data_FABO_106_TOUCH,
                                           section .nrf_balloc,
                                           section .log_const_data_app,
                                           section .log_backends
                                         };
```

## IRQHandler
Cortex_M_Startup.sファイルを編集する。(長いので抜粋)
```c
ISR_HANDLER ExternalISR0
ISR_HANDLER ExternalISR1
ISR_HANDLER UARTE0_UART0_IRQHandler // ExternalISR2
ISR_HANDLER ExternalISR3
ISR_HANDLER ExternalISR4
ISR_HANDLER ExternalISR5
ISR_HANDLER ExternalISR6
ISR_HANDLER SAADC_IRQHandler //ExternalISR7
ISR_HANDLER ExternalISR8
ISR_HANDLER ExternalISR9
ISR_HANDLER ExternalISR10
```

## Sample Code

A1コネクタに接続したTouch Brickの感圧によって、A0コネクタに接続したLED Brickを点灯/消灯させています。

```c
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "nrf.h"
#include "nrf_drv_saadc.h"
#include "nrf_drv_ppi.h"
#include "nrf_drv_timer.h"
#include "boards.h"
#include "app_error.h"
#include "nrf_delay.h"
#include "app_util_platform.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_drv_power.h"

#define NRF_LOG_MODULE_NAME FABO_106_TOUCH
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#define SAMPLES_IN_BUFFER 10
volatile uint8_t state = 1;

static const nrf_drv_timer_t m_timer = NRF_DRV_TIMER_INSTANCE(0);
static nrf_saadc_value_t     m_buffer_pool[2][SAMPLES_IN_BUFFER];
static nrf_ppi_channel_t     m_ppi_channel;
static uint32_t              m_adc_evt_counter;
nrf_log_module_const_data_t*    __start_log_const_data;
void*                           __start_pwr_mgmt_data;
void*                           __stop_log_const_data;
void*                           __stop_pwr_mgmt_data;
nrf_log_module_dynamic_data_t*  __start_log_dynamic_data;

void nrf_log_module_initialize()
{
    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();
    *(NRF_SECTION_ITEM_GET(log_const_data, nrf_log_module_const_data_t, NRF_LOG_MODULE_ID_GET_CONST(&NRF_LOG_ITEM_DATA_CONST(NRF_LOG_MODULE_NAME)) & 0x0000ffff)) = NRF_LOG_ITEM_DATA_CONST(NRF_LOG_MODULE_NAME);
}

void timer_handler(nrf_timer_event_t event_type, void * p_context)
{

}


void saadc_sampling_event_init(void)
{
    ret_code_t err_code;

    err_code = nrf_drv_ppi_init();
    APP_ERROR_CHECK(err_code);

    nrf_drv_timer_config_t timer_cfg = NRF_DRV_TIMER_DEFAULT_CONFIG;
    timer_cfg.bit_width = NRF_TIMER_BIT_WIDTH_32;
    err_code = nrf_drv_timer_init(&m_timer, &timer_cfg, timer_handler);
    APP_ERROR_CHECK(err_code);

    uint32_t ticks = nrf_drv_timer_ms_to_ticks(&m_timer, 100);
    nrf_drv_timer_extended_compare(&m_timer,
                                   NRF_TIMER_CC_CHANNEL0,
                                   ticks,
                                   NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK,
                                   false);
    nrf_drv_timer_enable(&m_timer);

    uint32_t timer_compare_event_addr = nrf_drv_timer_compare_event_address_get(&m_timer,
                                                                                NRF_TIMER_CC_CHANNEL0);
    uint32_t saadc_sample_task_addr   = nrf_drv_saadc_sample_task_get();

    /* setup ppi channel so that timer compare event is triggering sample task in SAADC */
    err_code = nrf_drv_ppi_channel_alloc(&m_ppi_channel);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_ppi_channel_assign(m_ppi_channel,
                                          timer_compare_event_addr,
                                          saadc_sample_task_addr);
    APP_ERROR_CHECK(err_code);
}


void saadc_sampling_event_enable(void)
{
    ret_code_t err_code = nrf_drv_ppi_channel_enable(m_ppi_channel);

    APP_ERROR_CHECK(err_code);
}


void saadc_callback(nrf_drv_saadc_evt_t const * p_event)
{
    if (p_event->type == NRF_DRV_SAADC_EVT_DONE)
    {
        ret_code_t err_code;

        err_code = nrf_drv_saadc_buffer_convert(p_event->data.done.p_buffer, SAMPLES_IN_BUFFER);
        APP_ERROR_CHECK(err_code);

        int i;
        NRF_LOG_INFO("ADC event number: %d", (int)m_adc_evt_counter);

        for (i = 0; i < SAMPLES_IN_BUFFER; i++)
        {
            NRF_LOG_INFO("p_event->data.done.p_buffer[%d]:%d", i, p_event->data.done.p_buffer[i]);
        }
        m_adc_evt_counter++;
    }
}


void saadc_init(void)
{
    ret_code_t err_code;
    nrf_saadc_channel_config_t channel_config =
        NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN1);

    err_code = nrf_drv_saadc_init(NULL, saadc_callback);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_saadc_channel_init(0, &channel_config);
    err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_saadc_buffer_convert(m_buffer_pool[0], SAMPLES_IN_BUFFER);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_saadc_buffer_convert(m_buffer_pool[1], SAMPLES_IN_BUFFER);
    APP_ERROR_CHECK(err_code);

}


int main(void)
{
    nrf_log_module_initialize();
    APP_ERROR_CHECK(nrf_drv_power_init(NULL));

    APP_ERROR_CHECK(nrf_pwr_mgmt_init());

    NRF_LOG_INFO("Fabo Shinobi TOUCH Brick 106 Sample.");
    saadc_init();
    saadc_sampling_event_init();
    saadc_sampling_event_enable();

    while (1)
    {
        nrf_pwr_mgmt_run();
        NRF_LOG_FLUSH();
    }
}


```

## 構成Parts
- 感圧センサー

## GitHub