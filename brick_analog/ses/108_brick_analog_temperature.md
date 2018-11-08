# #108 Temperature Brick

![](/img/TMP108/108.jpg)
<!--COLORME-->

## Overview
温度を計測するBrickです。

アナログ値(ADC 12bitの場合　0〜4096)を取得でき、変換することで−30度から100度までの温度を計測することができます。

## Connecting

![](/img/TMP108/FaBo_108_TEMPRATURE_CONNECT.JPG)

## LM61CIZ Datasheet
| Document |
|:--|
| [LM61CIZ Datasheet](http://akizukidenshi.com/catalog/g/gI-02726/) |

## Schematic
![](/img/100_analog/schematic/108_temperature.png)

## User Include Directories
Solution Option -> Preprocessor -> User Include Directoriesに以下を追加する。(../nRF5_SDKの部分は適宜変えてください。)

|Path|
|:--|
|../nRF5_SDK/modules/nrfx/drivers/src/prs|
|../nRF5_SDK/modules/nrfx/drivers/src|
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
|NRFX_POWER_ENABLED|
|NRFX_PPI_ENABLED|
|NRFX_TIMER_ENABLED|
|NRFX_TIMER0_ENABLED|
|SAADC_ENABLED|
|POWER_ENABLED|
|PPI_ENABLED|
|TIMER_ENABLED|
|TIMER0_ENABLED|
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
SEGGER_Flash.icfファイルを編集する。(SEGGER_Flash.icfはProject配下に自動生成されている)
```c
define memory with size = 4G;
//
// Block definitions
//
define block ctors { section .ctors, section .ctors.*, block with alphabetical order { init_array } };
define block dtors { section .dtors, section .dtors.*, block with reverse alphabetical order { fini_array } };
define block exidx { section .ARM.exidx, section .ARM.exidx.* };
define block tbss  { section .tbss,  section .tbss.*  };
define block tdata { section .tdata, section .tdata.* };
define block tls   { block tbss, block tdata };
define block tdata_load { copy of block tdata };
define block heap  with size = __HEAPSIZE__,  alignment = 8, /* fill =0x00, */ readwrite access { };
define block stack with size = __STACKSIZE__, alignment = 8, /* fill =0xCD, */ readwrite access { };

define block log_const_data_start with size = 8 { symbol __start_log_const_data };
define block log_const_data_list { section .log_const_data* };
define block log_const_data_stop with size = 8 { symbol __stop_log_const_data };
define block log_const_data with fixed order { block log_const_data_start, block log_const_data_list, block log_const_data_stop };

//
// Explicit initialization settings for sections
//
do not initialize                           { section .non_init, section .non_init.* };
initialize by copy /* with packing=auto */  { section .data, section .data.* };
initialize by copy /* with packing=auto */  { section .fast, section .fast.* };
//
// ROM Placement
//
place at start of FLASH                 {
                                           section .vectors,                         // Vector table section
                                        };
place in FLASH with minimum size order  {
                                           section .init, section .init.*,          // Init code section
                                           section .text, section .text.*,          // Code section
                                           section .rodata, section .rodata.*,      // Read-only data section
                                           section .segger.*,                       // Auto-generated initialization
                                           block exidx,                             // ARM exception unwinding block
                                           block ctors,                             // Constructors block
                                           block dtors                              // Destructors block
                                         };
place in FLASH                           {
                                           block tdata_load,                       // Thread-local-storage load image
                                           section .log_backends,
                                           section .nrf_balloc,
                                           block log_const_data
                                         };
//                                      
// RAM Placement                        
//                                      
place in RAM                             {                                          // Special sections
                                           section .non_init, section .non_init.*,  // No initialization section
                                           block tls,                                // Thread-local-storage block
                                           section .log_dynamic_data
                                         };
place in RAM with auto order             {                                          // Initialized sections
                                           section .fast, section .fast.*,          // "ramfunc" section
                                           section .data, section .data.*,          // Initialized data section
                                           section .bss, section .bss.*             // Static data section
                                         };
place in RAM                             {
                                           /* expandable */ block heap              // Heap reserved block
                                         };
place at end of RAM                      {
                                           block stack                              // Stack reserved block at the end
                                         };
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

#define NRF_LOG_MODULE_NAME FABO_108_TEMPERATURE
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
nrf_log_module_dynamic_data_t*  __start_log_dynamic_data;
void*                           __stop_log_const_data;
void*                           __stop_log_dynamic_data;
void*                           __start_pwr_mgmt_data;
void*                           __stop_pwr_mgmt_data;

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
        NRF_LOG_INFO("saadc_callback() m_adc_evt_counter:%d", (int)m_adc_evt_counter);

        for (i = 0; i < SAMPLES_IN_BUFFER; i++)
        {
            double temp = (((p_event->data.done.p_buffer[i] / 1024.0)*3300.0) - 600.0)/10.0;
            NRF_LOG_INFO("Celsius=" NRF_LOG_FLOAT_MARKER, NRF_LOG_FLOAT(temp));
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
    APP_ERROR_CHECK(err_code);  

    err_code = nrf_drv_saadc_buffer_convert(m_buffer_pool[0], SAMPLES_IN_BUFFER);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_saadc_buffer_convert(m_buffer_pool[1], SAMPLES_IN_BUFFER);
    APP_ERROR_CHECK(err_code);

}


int main(void)
{

    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();

    APP_ERROR_CHECK(nrf_drv_power_init(NULL));

    APP_ERROR_CHECK(nrf_pwr_mgmt_init());

    int nrf_log_item_data_const = &NRF_LOG_ITEM_DATA_CONST(NRF_LOG_MODULE_NAME);
    int nrf_log_module_id = NRF_LOG_MODULE_ID;
    int log_const_data_addr = NRF_SECTION_START_ADDR(log_const_data);
    NRF_LOG_INFO("Fabo Shinobi Temprature Brick 108");
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
- IC温度センサ LM61CIZ

## GitHub
