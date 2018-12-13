# Sample(222 Environment)

## Build Option

### Preprocessor

#### Preprocessor Definitions
|Preprocessor Definitions|
|:--|
|NRF52832_XXAB|
|BOARD_CUSTOM|
|NRFX_TWI_ENABLED|
|NRFX_TWI0_ENABLED|
|TWI_ENABLED|
|TWI0_ENABLED|
|NRFX_RTC_ENABLED|
|RTC_ENABLED|
|NRFX_RTC1_ENABLED|
|RTC1_ENABLED|
|SOFTDEVICE_PRESENT|

#### User Include Directories
|User Include Directories|
|:--|
|../nRF5_SDK/components/libraries/mutex|
|../nRF5_SDK/components/ble/common|
|../nRF5_SDK/components/softdevice/s132/headers|
|../nRF5_SDK/components/softdevice/common|
|../nRF5_SDK/components/libraries/pwr_mgmt|
|../nRF5_SDK/components/libraries/button|
|../nRF5_SDK/modules/nrfx/hal|
|../nRF5_SDK/components/boards|
|../nRF5_SDK/components/libraries/bsp|
|../nRF5_SDK/modules/nrfx/drivers/src/prs|
|../nRF5_SDK/modules/nrfx/drivers/src|
|../nRF5_SDK/components/libraries/ringbuf|
|../nRF5_SDK/external/fprintf|
|../nRF5_SDK/components/libraries/atomic|
|../nRF5_SDK/components/libraries/balloc|
|../nRF5_SDK/components/libraries/memobj|
|../nRF5_SDK/components/libraries/log/src|
|../nRF5_SDK/components/libraries/strerror|
|../nRF5_SDK/components/libraries/experimental_section_vars|
|../nRF5_SDK/components/libraries/log|
|../nRF5_SDK/components/libraries/delay|
|../nRF5_SDK/modules/nrfx/drivers/include|
|../nRF5_SDK/integration/nrfx|
|../nRF5_SDK/modules/nrfx|
|../nRF5_SDK/integration/nrfx/legacy|
|../nRF5_SDK/components/drivers_nrf/nrf_soc_nosd|
|../nRF5_SDK/components/toolchain/cmsis/include|
|../nRF5_SDK/modules/nrfx/mdk|
|../nRF5_SDK/components/libraries/util|
|.|

### Linker

#### Linker Symbol Definitions

|Linker Symbol Definitions|
|:--|
|__app_ram_start__=app_ram_start$$Base|
|__start_sdh_req_observers=sdh_req_observers$$Base|
|__stop_sdh_req_observers=sdh_req_observers$$Limit|
|__start_sdh_state_observers=sdh_state_observers$$Base|
|__stop_sdh_state_observers=sdh_state_observers$$Limit|
|__start_pwr_mgmt_data=pwr_mgmt_data$$Base|
|__stop_pwr_mgmt_data=pwr_mgmt_data$$Limit|
|__start_log_const_data=log_const_data$$Base|
|__start_log_dynamic_data=log_dynamic_data$$Base|
|__stop_log_const_data=log_const_data$$Limit|

### Build

#### Memory Segments
FLASH RX 0x00026000 0x0005A000

RAM RWX 0x20002210 0x0000DDF0


### Code Generation

#### ARM FP ABI Type
Hard -> Softに変更

### Loader

#### Additional Load File[0]
|Additional Load File[0]|
|:--|
|(SDK_PATH)/components/softdevice/s132/hex/s132_nrf52_6.1.0_softdevice.hex|

## SDK Source Code
|SDK Source Code|
|:--|
|(SDK_PATH)/components/libraries/util/app_error.c|
|(SDK_PATH)/components/libraries/util/app_error_handler_gcc.c|
|(SDK_PATH)/components/libraries/util/app_error_weak.c|
|(SDK_PATH)/components/libraries/util/app_util_platform.c|
|(SDK_PATH)/components/ble/common/ble_advdata.c|
|(SDK_PATH)/components/boards/boards.c|
|(SDK_PATH)/components/libraries/atomic/nrf_atomic.c|
|(SDK_PATH)/components/libraries/balloc/nrf_balloc.c|
|(SDK_PATH)/integration/nrfx/legacy/nrf_drv_clock.c|
|(SDK_PATH)/integration/nrfx/legacy/nrf_drv_twi.c|
|(SDK_PATH)/integration/nrfx/legacy/nrf_drv_uart.c|
|(SDK_PATH)/external/fprintf/nrf_fprintf.c|
|(SDK_PATH)/external/fprintf/nrf_fprintf_format.c|
|(SDK_PATH)/components/libraries/log/src/nrf_log_backend_serial.c|
|(SDK_PATH)/components/libraries/log/src/nrf_log_backend_uart.c|
|(SDK_PATH)/components/libraries/log/src/nrf_log_default_backends.c|
|(SDK_PATH)/components/libraries/log/src/nrf_log_frontend.c|
|(SDK_PATH)/components/libraries/log/src/nrf_log_str_formatter.c|
|(SDK_PATH)/components/libraries/memobj/nrf_memobj.c|
|(SDK_PATH)/components/libraries/pwr_mgmt/nrf_pwr_mgmt.c|
|(SDK_PATH)/components/libraries/ringbuf/nrf_ringbuf.c|
|(SDK_PATH)/components/softdevice/common/nrf_sdh.c|
|(SDK_PATH)/components/softdevice/common/nrf_sdh_ble.c|
|(SDK_PATH)/components/libraries/experimental_section_vars/nrf_section_iter.c|
|(SDK_PATH)/components/libraries/strerror/nrf_strerror.c|
|(SDK_PATH)/modules/nrfx/drivers/src/nrfx_clock.c|
|(SDK_PATH)/modules/nrfx/drivers/src/prs/nrfx_prs.c|
|(SDK_PATH)/modules/nrfx/drivers/src/nrfx_rtc.c|
|(SDK_PATH)/modules/nrfx/drivers/src/nrfx_twi.c|
|(SDK_PATH)/modules/nrfx/drivers/src/nrfx_uart.c|
|(SDK_PATH)/modules/nrfx/drivers/src/nrfx_uarte.c|

## Linker Script(SEGGER_Flash.icf)
```c
// **********************************************************************
// *                    SEGGER Microcontroller GmbH                     *
// *                        The Embedded Experts                        *
// **********************************************************************
// *                                                                    *
// *            (c) 2014 - 2018 SEGGER Microcontroller GmbH             *
// *            (c) 2001 - 2018 Rowley Associates Limited               *
// *                                                                    *
// *           www.segger.com     Support: support@segger.com           *
// *                                                                    *
// **********************************************************************
// *                                                                    *
// * All rights reserved.                                               *
// *                                                                    *
// * Redistribution and use in source and binary forms, with or         *
// * without modification, are permitted provided that the following    *
// * conditions are met:                                                *
// *                                                                    *
// * - Redistributions of source code must retain the above copyright   *
// *   notice, this list of conditions and the following disclaimer.    *
// *                                                                    *
// * - Neither the name of SEGGER Microcontroller GmbH                  *
// *   nor the names of its contributors may be used to endorse or      *
// *   promote products derived from this software without specific     *
// *   prior written permission.                                        *
// *                                                                    *
// * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND             *
// * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,        *
// * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF           *
// * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE           *
// * DISCLAIMED.                                                        *
// * IN NO EVENT SHALL SEGGER Microcontroller GmbH BE LIABLE FOR        *
// * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR           *
// * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT  *
// * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;    *
// * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF      *
// * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT          *
// * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE  *
// * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH   *
// * DAMAGE.                                                            *
// *                                                                    *
// **********************************************************************

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
define block log_const_data      { section .log_const_data* };
define block log_dynamic_data    { section .log_dynamic_data* };
define block pwr_mgmt_data       { section .pwr_mgmt_data* };
define block app_ram_start       { };
define block sdh_req_observers   { section .sdh_req_observers* };
define block sdh_state_observers { section .sdh_state_observers* };
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
                                           section .vectors                         // Vector table section
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
                                           section .nrf_balloc,
                                           section .log_backends,
                                           block log_const_data,
                                           block log_dynamic_data,
                                           block pwr_mgmt_data,
                                           block sdh_req_observers,
                                           block sdh_state_observers
                                         };
//                                      
// RAM Placement                        
//                                      
place in RAM                             {                                          // Special sections
                                           section .non_init, section .non_init.*,  // No initialization section
                                           block tls,                               // Thread-local-storage block
                                           block app_ram_start
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

## Sample Code

main.c
```c
#define NRF_LOG_MODULE_NAME MAIN
#include "app_error.h"
#include "bsp.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "bsec_integration.h"
#include "app_log.h"
#include "app_twi.h"
#include "app_bsec.h"
#include "app_ble.h"

#define LED1                            BSP_BOARD_LED_0
#define TEMP_OFFSET                     0.0f

NRF_LOG_MODULE_REGISTER();

int main(void) {
    return_values_init  rc_init;
    bsec_version_t      bsec_version;

    app_log_init();

    NRF_LOG_INFO("ble advertising + bsec sample");

    bsp_board_init(BSP_INIT_LEDS);
    APP_ERROR_CHECK(nrf_pwr_mgmt_init());
    app_ble_stack_init();
    app_twi_init();
    app_bsec_rtc_init();

    bsec_get_version(&bsec_version);
    NRF_LOG_DEBUG("bsec_version.major        : %d", bsec_version.major);
    NRF_LOG_DEBUG("bsec_version.minor        : %d", bsec_version.minor);
    NRF_LOG_DEBUG("bsec_version.major_bugfix : %d", bsec_version.major_bugfix);
    NRF_LOG_DEBUG("bsec_version.minor_bugfix : %d", bsec_version.minor_bugfix);

    rc_init = bsec_iot_init(BSEC_SAMPLE_RATE_LP, TEMP_OFFSET, app_twi_tx_func, app_twi_rx_func, app_bsec_sleep, app_bsec_state_load, app_bsec_config_load);
    NRF_LOG_DEBUG("rc_init.bme680_status : %d", rc_init.bme680_status);
    NRF_LOG_DEBUG("rc_init.bsec_status   : %d", rc_init.bsec_status);

    if(rc_init.bme680_status == BSEC_OK && rc_init.bsec_status == BSEC_OK) {
        bsec_iot_loop(app_bsec_sleep, app_bsec_get_timestamp, app_bsec_output, app_bsec_state_save, 10000);
    }
}
```

app_log.h
```c
#ifndef _APP_LOG_H
#define _APP_LOG_H

void    app_log_init(void);

#endif
```

app_log.c
```c
#include "app_error.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "app_log.h"

void    app_log_init(void) {
    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();
}
```

app_twi.h
```c
#ifndef _APP_TWI_H
#define _APP_TWI_H

void    app_twi_init(void);
int8_t  app_twi_tx_func(uint8_t dev_addr, uint8_t reg_addr, uint8_t* tx_buff_addr, uint16_t tx_data_size);
int8_t  app_twi_rx_func(uint8_t dev_addr, uint8_t reg_addr, uint8_t* rx_buff_addr, uint16_t rx_data_size);

#endif
```

app_twi.c
```c
#define NRF_LOG_MODULE_NAME APP_TWI
#include "app_error.h"
#include "nrf_drv_twi.h"
#include "nrf_log.h"
#include "app_twi.h"

#define ARDUINO_SCL_PIN 27
#define ARDUINO_SDA_PIN 26

static nrf_drv_twi_t    app_twi_instance    =   NRF_DRV_TWI_INSTANCE(0);
static volatile bool    app_twi_xfer_done   =   false;
NRF_LOG_MODULE_REGISTER();

void    app_twi_event_handler(nrf_drv_twi_evt_t const* a_event, void* a_context) {
    NRF_LOG_DEBUG("app_twi_event_handler() ### START ###");
    NRF_LOG_DEBUG("a_event->type = %d", a_event->type);
    switch(a_event->type) {
        case NRF_DRV_TWI_EVT_DONE:
            NRF_LOG_DEBUG("app_twi_xfer_done = %d", app_twi_xfer_done);
            if(app_twi_xfer_done == false) {
                app_twi_xfer_done = true;
            }
            break;
        default:
            break;
    }

    NRF_LOG_DEBUG("app_twi_event_handler() ### END ###");
}

void    app_twi_init(void) {
    NRF_LOG_DEBUG("app_twi_init() ### START ###");
    nrf_drv_twi_config_t config = {
        .scl                = ARDUINO_SCL_PIN,
        .sda                = ARDUINO_SDA_PIN,
        .frequency          = NRF_TWI_FREQ_400K,
        .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
        .clear_bus_init     = false
    };

    APP_ERROR_CHECK(nrf_drv_twi_init(&app_twi_instance, &config, app_twi_event_handler, NULL));
    nrf_drv_twi_enable(&app_twi_instance);

    NRF_LOG_DEBUG("app_twi_init() ### END ###");
}

int8_t  app_twi_tx_func(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len) {
    uint8_t tx_buf[len + 1];

    NRF_LOG_DEBUG("app_twi_tx_func() ### START ###");
    NRF_LOG_DEBUG("dev_id   : %02X", dev_id);
    NRF_LOG_DEBUG("reg_addr : %02X", reg_addr);
    NRF_LOG_DEBUG("data     : %08X", data);
    NRF_LOG_DEBUG("len      : %d", len);

    memset(tx_buf, 0, len + 1);

    tx_buf[0] = reg_addr;
    if(len) {
        memcpy(&tx_buf[1], data, len);
    }

    NRF_LOG_HEXDUMP_DEBUG(tx_buf, len + 1);

    app_twi_xfer_done = false;
    APP_ERROR_CHECK(nrf_drv_twi_tx(&app_twi_instance, dev_id, tx_buf, len + 1, false));
    while(app_twi_xfer_done == false);

    NRF_LOG_DEBUG("app_twi_tx_func() ### END ###");

    return 0;
}

int8_t  app_twi_rx_func(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len) {

    NRF_LOG_DEBUG("app_twi_rx_func() ### START ###");
    NRF_LOG_DEBUG("dev_id   : %02X", dev_id);
    NRF_LOG_DEBUG("reg_addr : %02X", reg_addr);
    NRF_LOG_DEBUG("data     : %08X", data);
    NRF_LOG_DEBUG("len      : %d", len);

    memset(data, 0x00, len);

    app_twi_tx_func(dev_id, reg_addr, NULL, 0);

    app_twi_xfer_done = false;
    APP_ERROR_CHECK(nrf_drv_twi_rx(&app_twi_instance, dev_id, data, len));
    while(app_twi_xfer_done == false);

    NRF_LOG_HEXDUMP_DEBUG(data, len);

    NRF_LOG_DEBUG("app_twi_rx_func() ### END ###");

    return 0;
}
```

app_bsec.h
```c
#ifndef _APP_BSEC_H
#define _APP_BSEC_H

void        app_bsec_output(int64_t, float, uint8_t, float, float, float, float, float, float, bsec_library_return_t, float, float, float);
void        app_bsec_state_save(const uint8_t*, uint32_t);
int64_t     app_bsec_get_timestamp(void);
void        app_bsec_sleep(uint32_t);
uint32_t    app_bsec_state_load(uint8_t*, uint32_t);
uint32_t    app_bsec_config_load(uint8_t*, uint32_t);
void        app_bsec_rtc_init(void);

#endif
```

app_bsec.c

- SoftDevice有効時にRTC1を使う場合、CLOCK関連の初期化はSoftDeviceが実施するので、APL側でやってはいけない

```c
#define NRF_LOG_MODULE_NAME APP_BSEC
#include <stdint.h>
#include "nrf_drv_rtc.h"
#include "nrf_drv_clock.h"
#include "nrf_delay.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "bsec_integration.h"
#include "app_ble.h"
#include "app_bsec.h"

nrf_drv_rtc_t   app_bsec_rtc                =   NRF_DRV_RTC_INSTANCE(1);
static uint32_t app_bsec_rtc_ovr_flw_ctr    =   0;
static int32_t  app_bsec_rtc_max_ticks      =   0;
NRF_LOG_MODULE_REGISTER();

void    app_bsec_rtc_handler(nrf_drv_rtc_int_type_t int_type)
{
    NRF_LOG_DEBUG("app_bsec_rtc_handler() ### START ###");
    NRF_LOG_DEBUG("int_type = %d", int_type);
    if(int_type == NRF_DRV_RTC_INT_OVERFLOW) {
        NRF_LOG_DEBUG("rtc1 overflow detection.");
        app_bsec_rtc_ovr_flw_ctr++;
    }
    NRF_LOG_DEBUG("app_bsec_rtc_handler() ### END ###");
}

void    app_bsec_rtc_init(void) {
    nrf_drv_rtc_config_t    app_bsec_rtc_config = NRF_DRV_RTC_DEFAULT_CONFIG;

#ifndef SOFTDEVICE_PRESENT
    APP_ERROR_CHECK(nrf_drv_clock_init());

    nrf_drv_clock_lfclk_request(NULL);
#endif

    APP_ERROR_CHECK(nrf_drv_rtc_init(&app_bsec_rtc, &app_bsec_rtc_config, app_bsec_rtc_handler));

    nrf_drv_rtc_enable(&app_bsec_rtc);

    nrf_drv_rtc_overflow_enable(&app_bsec_rtc, true);

    app_bsec_rtc_max_ticks = nrf_drv_rtc_max_ticks_get(&app_bsec_rtc);
}

void    app_bsec_output(
    int64_t                 timestamp,
    float                   iaq,
    uint8_t                 iaq_accuracy,
    float                   temperature,
    float                   humidity,
    float                   pressure,
    float                   raw_temperature,
    float                   raw_humidity,
    float                   gas,
    bsec_library_return_t   bsec_status,
    float                   static_iaq,
    float                   co2_equivalent,
    float                   breath_voc_equivalent
) {
    NRF_LOG_DEBUG("app_bsec_output() ### START ###");
    NRF_LOG_INFO("timestamp             : %lu", timestamp / 10000000);
    NRF_LOG_INFO("iaq                   : " NRF_LOG_FLOAT_MARKER, NRF_LOG_FLOAT(iaq));
    NRF_LOG_INFO("iaq_accuracy          : %d", iaq_accuracy);
    NRF_LOG_INFO("temperature           : " NRF_LOG_FLOAT_MARKER, NRF_LOG_FLOAT(temperature));
    NRF_LOG_INFO("humidity              : " NRF_LOG_FLOAT_MARKER, NRF_LOG_FLOAT(humidity));
    NRF_LOG_INFO("pressure              : " NRF_LOG_FLOAT_MARKER, NRF_LOG_FLOAT(pressure));
    NRF_LOG_INFO("raw_temperature       : " NRF_LOG_FLOAT_MARKER, NRF_LOG_FLOAT(raw_temperature));
    NRF_LOG_INFO("raw_humidity          : " NRF_LOG_FLOAT_MARKER, NRF_LOG_FLOAT(raw_humidity));
    NRF_LOG_INFO("gas                   : " NRF_LOG_FLOAT_MARKER, NRF_LOG_FLOAT(gas));
    NRF_LOG_INFO("bsec_status           : %d", bsec_status);
    NRF_LOG_INFO("static_iaq            : " NRF_LOG_FLOAT_MARKER, NRF_LOG_FLOAT(static_iaq));
    NRF_LOG_INFO("co2_equivalent        : " NRF_LOG_FLOAT_MARKER, NRF_LOG_FLOAT(co2_equivalent));
    NRF_LOG_INFO("breath_voc_equivalent : " NRF_LOG_FLOAT_MARKER, NRF_LOG_FLOAT(breath_voc_equivalent));
    NRF_LOG_DEBUG("app_bsec_output() ### END ###");
    app_ble_beacon_info_set(temperature * 100, humidity * 100, pressure / 100, gas, iaq * 100);
    app_ble_advertising_start();
}

void    app_bsec_state_save(
    const uint8_t*  a_state,
    uint32_t        len
) {
    NRF_LOG_DEBUG("app_bsec_state_save() ### START ###");
    NRF_LOG_DEBUG("a_state   : 0x%08X", a_state);
    NRF_LOG_DEBUG("len       : %d", len);

    NRF_LOG_DEBUG("app_bsec_state_save() ### END ###");
}

int64_t app_bsec_get_timestamp(void) {
    int32_t rtc_counter = nrf_drv_rtc_counter_get(&app_bsec_rtc);
    float   temp1, temp2;
    int64_t ret;

    NRF_LOG_DEBUG("app_bsec_get_timestamp() ### START ###");
    NRF_LOG_DEBUG("rtc_counter = %u", rtc_counter);

    ret = (float)((float)rtc_counter + (float)(app_bsec_rtc_max_ticks * app_bsec_rtc_ovr_flw_ctr)) / (float)NRFX_RTC_DEFAULT_CONFIG_FREQUENCY * 1000000;    

    NRF_LOG_DEBUG("ret = %ld", ret);
    NRF_LOG_DEBUG("app_bsec_get_timestamp() ### END ###");

    return ret;
}

void    app_bsec_sleep(uint32_t msec) {
    NRF_LOG_DEBUG("app_bsec_sleep() ### START ###");
    NRF_LOG_DEBUG("msec = %d", msec);
    nrf_delay_ms(msec);
    NRF_LOG_DEBUG("app_bsec_sleep() ### END ###");
}

uint32_t    app_bsec_state_load(uint8_t* a_buf, uint32_t buf_size) {
    uint8_t work_buffer_state[BSEC_MAX_STATE_BLOB_SIZE];
    uint32_t  n_work_buffer_size = BSEC_MAX_STATE_BLOB_SIZE;
    uint32_t  n_serialized_state = 0;

    NRF_LOG_DEBUG("app_bsec_state_load() ### START ###");

    bsec_get_state(0, a_buf, buf_size, work_buffer_state, n_work_buffer_size, &n_serialized_state);

    NRF_LOG_HEXDUMP_DEBUG(a_buf, n_serialized_state);

    NRF_LOG_DEBUG("app_bsec_state_load() ### END ### n_serialized_state : %d", n_serialized_state);

    return n_serialized_state;
}

uint32_t    app_bsec_config_load(uint8_t* a_buf, uint32_t buf_size) {
    uint8_t work_buffer[BSEC_MAX_PROPERTY_BLOB_SIZE];
    uint32_t n_work_buffer = BSEC_MAX_PROPERTY_BLOB_SIZE;
    uint32_t n_serialized_settings = 0;

    NRF_LOG_DEBUG("app_bsec_config_load() ### START ###");

    bsec_get_configuration(0, a_buf, buf_size, work_buffer, n_work_buffer, &n_serialized_settings);

    NRF_LOG_HEXDUMP_DEBUG(a_buf, n_serialized_settings);

    NRF_LOG_DEBUG("app_bsec_config_load() ### END ### n_serialized_settings : %d", n_serialized_settings);

    return n_serialized_settings;
}
```

app_ble.h
```c
#ifndef _APP_BLE_H
#define _APP_BLE_H

#include <stdint.h>

#ifdef  SOFTDEVICE_PRESENT

void    app_ble_stack_init(void);
void    app_ble_advertising_init(void);
void    app_ble_advertising_start(void);
void    app_ble_beacon_info_set(uint16_t temperature, uint16_t hummidity, uint16_t pressure, uint32_t gas, uint16_t iaq);

extern uint32_t __app_ram_start__;

#else

#define app_ble_stack_init()
#define app_ble_advertising_init()
#define app_ble_advertising_start()
#define app_ble_beacon_info_set(temperature, humidyty, pressure, gas, iaq)

#endif

#endif
```

app_ble.c
```c
#ifdef  SOFTDEVICE_PRESENT
#define NRF_LOG_MODULE_NAME APP_BLE
#include "app_error.h"
#include "nrf_sdh.h"
#include "nrf_sdh_ble.h"
#include "ble_advdata.h"
#include "nrf_error_sdm.h"
#include "nrf_log.h"
#include "app_ble.h"

#define APP_BLE_CONN_CFG_TAG                1
#define APP_COMPANY_IDENTIFIER              0x0059
#define NON_CONNECTABLE_ADV_INTERVAL        MSEC_TO_UNITS(100, UNIT_0_625_MS)
#define APP_BLE_ADVERTISING_STATUS_START    1
#define APP_BLE_ADVERTISING_STATUS_STOP     0

typedef struct {
    uint8_t sensor_id[4];
    uint8_t device_id[2];
    uint8_t temperature[2];
    uint8_t humidity[2];
    uint8_t pressure[2];
    uint8_t gas[4];
    uint8_t iaq[2];
} app_ble_bme680_advertising_data_t;

extern uint32_t __app_ram_start__;

static ble_gap_adv_params_t app_ble_gap_adv_params;
static uint8_t              app_ble_enc_advdata[BLE_GAP_ADV_SET_DATA_SIZE_MAX];
static uint8_t              app_ble_adv_handle = BLE_GAP_ADV_SET_HANDLE_NOT_SET;
static uint16_t             app_ble_conn_handle = BLE_CONN_HANDLE_INVALID;
static uint8_t              app_ble_advertising_status  = APP_BLE_ADVERTISING_STATUS_STOP;
static ble_gap_adv_data_t   app_ble_gap_adv_data = {
    .adv_data = {
        .p_data = app_ble_enc_advdata,
        .len    = BLE_GAP_ADV_SET_DATA_SIZE_MAX
    },
    .scan_rsp_data = {
        .p_data = NULL,
        .len    = 0
    }
};
app_ble_bme680_advertising_data_t   app_ble_bme680_advertising_data = {
    .sensor_id = { 0xff, 0xff, 0xff, 0xff },
    .device_id = { 0xff, 0xff },
};
NRF_LOG_MODULE_REGISTER();

void    app_ble_stack_init(void) {
    NRF_LOG_DEBUG("app_ble_stack_init() ### START ###");

    APP_ERROR_CHECK(nrf_sdh_enable_request());
    APP_ERROR_CHECK(nrf_sdh_ble_default_cfg_set(APP_BLE_CONN_CFG_TAG, &__app_ram_start__));
    APP_ERROR_CHECK(nrf_sdh_ble_enable(&__app_ram_start__));

    NRF_LOG_DEBUG("app_ble_stack_init() ### END ###");
}

void    app_ble_advertising_init(void) {
    NRF_LOG_DEBUG("app_ble_advertising_init() ### START ###");

    ble_advdata_manuf_data_t    manuf_specific_data;
    ble_advdata_t               advdata;

    memset(&advdata, 0x00, sizeof(ble_advdata_t));
    memset(&app_ble_gap_adv_params, 0x00, sizeof(ble_gap_adv_params_t));

    manuf_specific_data.company_identifier = APP_COMPANY_IDENTIFIER;
    manuf_specific_data.data.p_data = (uint8_t*)(&app_ble_bme680_advertising_data);
    manuf_specific_data.data.size = sizeof(app_ble_bme680_advertising_data_t);

    advdata.name_type = BLE_ADVDATA_NO_NAME;
    advdata.flags = BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE;
    advdata.p_manuf_specific_data = &manuf_specific_data;

    app_ble_gap_adv_params.properties.type = BLE_GAP_ADV_TYPE_NONCONNECTABLE_NONSCANNABLE_UNDIRECTED;
    app_ble_gap_adv_params.p_peer_addr = NULL;
    app_ble_gap_adv_params.filter_policy = BLE_GAP_ADV_FP_ANY;
    app_ble_gap_adv_params.interval = NON_CONNECTABLE_ADV_INTERVAL;
    app_ble_gap_adv_params.duration = 0;

    APP_ERROR_CHECK(ble_advdata_encode(&advdata, app_ble_gap_adv_data.adv_data.p_data, &app_ble_gap_adv_data.adv_data.len));

    NRF_LOG_DEBUG("app_ble_advertising_init() ### END ###");
}

void    app_ble_advertising_update(void) {
    NRF_LOG_DEBUG("app_ble_advertising_update() ### START ###");

    APP_ERROR_CHECK(sd_ble_gap_adv_stop(app_ble_adv_handle));
    APP_ERROR_CHECK(sd_ble_gap_adv_set_configure(&app_ble_adv_handle, &app_ble_gap_adv_data, &app_ble_gap_adv_params));
    APP_ERROR_CHECK(sd_ble_gap_adv_start(app_ble_adv_handle, APP_BLE_CONN_CFG_TAG));

    NRF_LOG_DEBUG("app_ble_advertising_update() ### END ###");
}

void    app_ble_advertising_start(void) {
    NRF_LOG_DEBUG("app_ble_advertising_start() ### START ###");

    app_ble_advertising_init();

    NRF_LOG_DEBUG("app_ble_advertising_status = %d", app_ble_advertising_status);
    if(app_ble_advertising_status == APP_BLE_ADVERTISING_STATUS_START) {
        app_ble_advertising_update();
    } else {
        APP_ERROR_CHECK(sd_ble_gap_adv_set_configure(&app_ble_adv_handle, &app_ble_gap_adv_data, &app_ble_gap_adv_params));
        APP_ERROR_CHECK(sd_ble_gap_adv_start(app_ble_adv_handle, APP_BLE_CONN_CFG_TAG));
        app_ble_advertising_status = APP_BLE_ADVERTISING_STATUS_START;
    }
    NRF_LOG_DEBUG("app_ble_advertising_start() ### END ###");
}

void    app_ble_beacon_info_set(
    uint16_t    temperature,
    uint16_t    humidity,
    uint16_t    pressure,
    uint32_t    gas,
    uint16_t    iaq
) {
    NRF_LOG_DEBUG("app_ble_beacon_info_set() ### START ###");
    NRF_LOG_INFO("temperature = %u", temperature);
    NRF_LOG_HEXDUMP_INFO(&temperature, sizeof(uint16_t));
    NRF_LOG_INFO("humidity = %u", humidity);
    NRF_LOG_HEXDUMP_INFO(&humidity, sizeof(uint16_t));
    NRF_LOG_INFO("pressure = %u", pressure);
    NRF_LOG_HEXDUMP_INFO(&pressure, sizeof(uint16_t));
    NRF_LOG_INFO("gas = %u", gas);
    NRF_LOG_HEXDUMP_INFO(&gas, sizeof(uint32_t));
    NRF_LOG_INFO("iaq = %u", iaq);
    NRF_LOG_HEXDUMP_INFO(&iaq, sizeof(uint16_t));

    memcpy(app_ble_bme680_advertising_data.temperature, &temperature, sizeof(uint16_t));
    memcpy(app_ble_bme680_advertising_data.humidity,    &humidity,    sizeof(uint16_t));
    memcpy(app_ble_bme680_advertising_data.pressure,    &pressure,    sizeof(uint16_t));
    memcpy(app_ble_bme680_advertising_data.gas,         &gas,         sizeof(uint32_t));
    memcpy(app_ble_bme680_advertising_data.iaq,         &iaq,         sizeof(uint16_t));

    NRF_LOG_INFO("app_ble_bme680_advertising_data hex dump");
    NRF_LOG_HEXDUMP_INFO(&app_ble_bme680_advertising_data, sizeof(app_ble_bme680_advertising_data_t));

    NRF_LOG_DEBUG("app_ble_beacon_info_set() ### END ###");
}

#endif
```

Cortex_M_Startup.s
```c
// **********************************************************************
// *                    SEGGER Microcontroller GmbH                     *
// *                        The Embedded Experts                        *
// **********************************************************************
// *                                                                    *
// *            (c) 2014 - 2018 SEGGER Microcontroller GmbH             *
// *            (c) 2001 - 2018 Rowley Associates Limited               *
// *                                                                    *
// *           www.segger.com     Support: support@segger.com           *
// *                                                                    *
// **********************************************************************
// *                                                                    *
// * All rights reserved.                                               *
// *                                                                    *
// * Redistribution and use in source and binary forms, with or         *
// * without modification, are permitted provided that the following    *
// * conditions are met:                                                *
// *                                                                    *
// * - Redistributions of source code must retain the above copyright   *
// *   notice, this list of conditions and the following disclaimer.    *
// *                                                                    *
// * - Neither the name of SEGGER Microcontroller GmbH                  *
// *   nor the names of its contributors may be used to endorse or      *
// *   promote products derived from this software without specific     *
// *   prior written permission.                                        *
// *                                                                    *
// * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND             *
// * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,        *
// * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF           *
// * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE           *
// * DISCLAIMED.                                                        *
// * IN NO EVENT SHALL SEGGER Microcontroller GmbH BE LIABLE FOR        *
// * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR           *
// * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT  *
// * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;    *
// * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF      *
// * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT          *
// * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE  *
// * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH   *
// * DAMAGE.                                                            *
// *                                                                    *
// **********************************************************************

.macro ISR_HANDLER name=
  .section .vectors, "ax"
  .word \name
  .section .init, "ax"
  .thumb_func
  .weak \name
\name:
1: b 1b /* endless loop */
.endm

.macro ISR_RESERVED
  .section .vectors, "ax"
  .word 0
.endm

  .syntax unified
  .global reset_handler
  .global Reset_Handler
  .equ Reset_Handler, reset_handler

  .section .vectors, "ax"
  .code 16
  .balign 2
  .global _vectors

.macro DEFAULT_ISR_HANDLER name=
  .thumb_func
  .weak \name
\name:
1: b 1b /* endless loop */
.endm

_vectors:
  .word __stack_end__
  .word reset_handler
ISR_HANDLER NMI_Handler
ISR_HANDLER HardFault_Handler
ISR_HANDLER MemManage_Handler
ISR_HANDLER BusFault_Handler
ISR_HANDLER UsageFault_Handler
ISR_RESERVED
ISR_RESERVED
ISR_RESERVED
ISR_RESERVED
ISR_HANDLER SVC_Handler
ISR_HANDLER DebugMon_Handler
ISR_RESERVED
ISR_HANDLER PendSV_Handler
ISR_HANDLER SysTick_Handler
#ifdef __VECTORS
#include __VECTORS
#else  
ISR_HANDLER POWER_CLOCK_IRQHandler
ISR_HANDLER ExternalISR1
ISR_HANDLER UARTE0_UART0_IRQHandler
ISR_HANDLER SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQHandler
ISR_HANDLER ExternalISR4
ISR_HANDLER ExternalISR5
ISR_HANDLER ExternalISR6
ISR_HANDLER ExternalISR7
ISR_HANDLER ExternalISR8
ISR_HANDLER ExternalISR9
ISR_HANDLER ExternalISR10
ISR_HANDLER ExternalISR11
ISR_HANDLER ExternalISR12
ISR_HANDLER ExternalISR13
ISR_HANDLER ExternalISR14
ISR_HANDLER ExternalISR15
ISR_HANDLER ExternalISR16
ISR_HANDLER RTC1_IRQHandler
ISR_HANDLER ExternalISR18
ISR_HANDLER ExternalISR19
ISR_HANDLER ExternalISR20
ISR_HANDLER ExternalISR21
ISR_HANDLER ExternalISR22
ISR_HANDLER ExternalISR23
ISR_HANDLER ExternalISR24
ISR_HANDLER ExternalISR25
ISR_HANDLER ExternalISR26
ISR_HANDLER ExternalISR27
ISR_HANDLER ExternalISR28
ISR_HANDLER ExternalISR29
ISR_HANDLER ExternalISR30
ISR_HANDLER ExternalISR31
#endif
  .section .vectors, "ax"
_vectors_end:

  .section .init, "ax"
  .balign 2

  .thumb_func
  reset_handler:

#ifndef __NO_SYSTEM_INIT
  ldr r0, =__stack_end__
  mov sp, r0
  bl SystemInit
#endif

#if !defined(__SOFTFP__)
  // Enable CP11 and CP10 with CPACR |= (0xf<<20)
  movw r0, 0xED88
  movt r0, 0xE000
  ldr r1, [r0]
  orrs r1, r1, #(0xf << 20)
  str r1, [r0]
#endif

  b _start

#ifndef __NO_SYSTEM_INIT
  .thumb_func
  .weak SystemInit
SystemInit:
  bx lr
#endif
```

BME680/BSEC関連は↓
https://www.bosch-sensortec.com/bst/products/all_products/bsec
