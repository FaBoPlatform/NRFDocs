# #209 Ktemp I2C Brick

## Overview



## Connecting

ShinobiとFabo 209 Ktempを接続。

## User Include Directories
Solution Option -> Preprocessor -> User Include Directoriesに以下を追加する。(../nRF5_SDKの部分は適宜変えてください。)

|User Include Directories|
|:--|
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

## Preprocessor Definitions
Solution Option -> Preprocessor -> Preprocessor Definitionsに以下を追加する。

|Preprocessor Definitions|
|:--|
|NRFX_TWI_ENABLED|
|TWI_ENABLED|
|NRFX_TWI0_ENABLED|
|NRFX_TWI1_ENABLED|
|TWI0_ENABLED|
|TWI1_ENABLED|
|NRF52832_XXAB|
|BOARD_CUSTOM|

## Linker Symbol Definitions
Solution Option -> Linker -> Linker Symbol Definitionsに以下を追加する。

|Linker Symbol Definitions|
|:--|
|__start_log_const_data=log_const_data$$Base|
|__stop_log_const_data=log_const_data$$Limit|
|__start_log_dynamic_data=log_dynamic_data$$Base|

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
|nrf_drv_twi.c|../nRF5_SDK/integration/nrfx/legacy|
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
|nrfx_twi.c|../nRF5_SDK/modules/nrfx/drivers/src|
|nrfx_uart.c|../nRF5_SDK/modules/nrfx/drivers/src|
|nrfx_uarte.c|../nRF5_SDK/modules/nrfx/drivers/src|

## Section
SEGGER_Flash.icf
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
define block log_const_data { section .log_const_data* };
define block log_dynamic_data { section .log_dynamic_data* };
define block pwr_mgmt_data { section .pwr_mgmt_data* };
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
                                           block tdata_load,                        // Thread-local-storage load image
                                           section .log_backends,
                                           section .nrf_balloc,
                                           block log_const_data,
                                           block log_dynamic_data,
                                           block pwr_mgmt_data
                                         };
//                                      
// RAM Placement                        
//                                      
place in RAM                             {                                          // Special sections
                                           section .non_init, section .non_init.*,  // No initialization section
                                           block tls                                // Thread-local-storage block
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
ISR_HANDLER ExternalISR0
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
ISR_HANDLER ExternalISR17
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

## Sample Code
main.c
```c
#define NRF_LOG_MODULE_NAME MAIN
#include "app_error.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_pwr_mgmt.h"
#include "app_log.h"
#include "mcp3421.h"
#include "nrf_delay.h"

NRF_LOG_MODULE_REGISTER();

void main(void) {
    uint32_t    data;

    app_log_init();

    NRF_LOG_INFO("209 Ktemp sample");

    APP_ERROR_CHECK(nrf_pwr_mgmt_init());

    mcp3421_initialize();
    mcp3421_set_configuration(MCP3421_MODE_OS, MCP3421_SAMPLE_RATE_18BIT, MCP3421_GAIN_1);
    while(true) {
        mcp3421_measurement(&data);
        NRF_LOG_INFO("data = %u", data);
        if(NRF_LOG_PROCESS() == false) {
            nrf_pwr_mgmt_run();
        } else {
            NRF_LOG_FLUSH();
        }
    }
}
```

mcp3421.h
```c

#ifndef _MCP3421_H
#define _MCP3421_H

#define MCP3421_SLAVE_ADDRESS   0x69

#define MCP3421_SAMPLE_RATE_12BIT   0
#define MCP3421_SAMPLE_RATE_14BIT   1
#define MCP3421_SAMPLE_RATE_16BIT   2
#define MCP3421_SAMPLE_RATE_18BIT   3

#define MCP3421_GAIN_1  0
#define MCP3421_GAIN_2  1
#define MCP3421_GAIN_4  2
#define MCP3421_GAIN_8  3

#define MCP3421_MODE_OS 0
#define MCP3421_MODE_CC 1

#define MCP3421_READY_BIT   0x80

void    mcp3421_initialize(void);
#ifdef MCP3421_DEVICE_ADDRESS_SEARCH_ENABLED
void    mcp3421_set_device_address(uint8_t);
#else
#define mcp3421_set_device_address(address)
#endif
bool    mcp3421_set_configuration(uint8_t mode, uint8_t sample_rate, uint8_t gain);
void    mcp3421_measurement(uint32_t*);

#endif
```

mcp3421.c
```c
#define NRF_LOG_MODULE_NAME MCP3421
#include "app_error.h"
#include "nrf_log.h"
#include "app_twi.h"
#include "mcp3421.h"
#include "nrf_delay.h"

#ifdef MCP3421_DEVICE_ADDRESS_SEARCH_ENABLED
static bool     mcp3421_device_address_enabled;
#endif
static uint8_t  mcp3421_device_address;
static uint8_t  mcp3421_configuration = 0;
static uint8_t  mcp3421_mode;
static uint8_t  mcp3421_sample_rate;
static uint8_t  mcp3421_gain;
NRF_LOG_MODULE_REGISTER();

#ifdef MCP3421_DEVICE_ADDRESS_SEARCH_ENABLED
void    mcp3421_search_device_address(
    void
){
    uint8_t address;
    uint8_t tx_data = 0;

    mcp3421_device_address_enabled = false;
    for(address = 0x68; address <= 0x6f; address++) {
        app_twi_rx_func(address, 0, &tx_data, sizeof(tx_data));
    }
}
#endif

void    mcp3421_initialize(
    void
){
    app_twi_init();

#ifdef MCP3421_DEVICE_ADDRESS_SEARCH_ENABLED
    mcp3421_search_device_address();
#else
    mcp3421_device_address = MCP3421_SLAVE_ADDRESS;
#endif
}

#ifdef MCP3421_DEVICE_ADDRESS_SEARCH_ENABLED
void    mcp3421_set_device_address(
    uint8_t device_address
){
    if(mcp3421_device_address_enabled == false) {
        mcp3421_device_address = device_address;
        mcp3421_device_address_enabled = true;
    }
}
#endif

bool    mcp3421_check_ready_bit(
    uint8_t configuration
) {
    return ((configuration & MCP3421_READY_BIT) == MCP3421_READY_BIT) ? true : false;
}

uint8_t mcp3421_convert_configuration(
    void
) {
    return mcp3421_gain | (mcp3421_sample_rate << 2) | (mcp3421_mode << 4);
}

bool    mcp3421_set_configuration(
    uint8_t mode,
    uint8_t sample_rate,
    uint8_t gain
){
    NRF_LOG_INFO("mode        = 0x%02X", mode);
    if((mode != MCP3421_MODE_CC) && (mode != MCP3421_MODE_OS)) {
        NRF_LOG_ERROR("unrecognized mode specified");
        return false;
    }

    NRF_LOG_INFO("sample rate = 0x%02X", sample_rate);
    if((sample_rate != MCP3421_SAMPLE_RATE_12BIT) &&
       (sample_rate != MCP3421_SAMPLE_RATE_14BIT) &&
       (sample_rate != MCP3421_SAMPLE_RATE_16BIT) &&
       (sample_rate != MCP3421_SAMPLE_RATE_18BIT)) {
        NRF_LOG_ERROR("unrecognized sample rate specified");
        return false;
    }

    NRF_LOG_INFO("gain        = 0x%02X", gain);
    if((gain != MCP3421_GAIN_1) &&
       (gain != MCP3421_GAIN_2) &&
       (gain != MCP3421_GAIN_4) &&
       (gain != MCP3421_GAIN_8)){
        NRF_LOG_ERROR("unrecognized gain specified");
        return false;
    }

    mcp3421_mode = mode;
    mcp3421_sample_rate = sample_rate;
    mcp3421_gain = gain;

    mcp3421_configuration = mcp3421_convert_configuration();
    if(mcp3421_mode == MCP3421_MODE_OS) {
        mcp3421_configuration |= MCP3421_READY_BIT;
    }

    NRF_LOG_DEBUG("mcp3421_configuration = 0x%02X", mcp3421_configuration);

    app_twi_tx_func(mcp3421_device_address, mcp3421_configuration, NULL, 0);

    return true;
}

void    mcp3421_measurement(
    uint32_t*   data
){
    uint8_t rx_size;
    uint8_t sample_rate;
    uint8_t rx_buff[4] = { 0 };
    uint8_t configuration;
    uint8_t tx_buff;
    bool    end = false;

    if(mcp3421_sample_rate == MCP3421_SAMPLE_RATE_18BIT) {
        rx_size = 4;
    } else {
        rx_size = 3;
    }

    while(end == false) {
        app_twi_rx_func_notx(mcp3421_device_address, 0, rx_buff, rx_size);

        NRF_LOG_HEXDUMP_DEBUG(rx_buff, rx_size);

        configuration = rx_buff[rx_size - 1];
        if(mcp3421_check_ready_bit(configuration)) {
            nrf_delay_ms(1);
        } else {
            end = true;
            *data = 0;
            switch(mcp3421_sample_rate) {
                case MCP3421_SAMPLE_RATE_12BIT:
                case MCP3421_SAMPLE_RATE_14BIT:
                case MCP3421_SAMPLE_RATE_16BIT:
                    *data = ((rx_buff[0] & 0xff) << 8) | rx_buff[1];
                    break;
                case MCP3421_SAMPLE_RATE_18BIT:
                    *data = ((rx_buff[0] & 0x03) << 16) | rx_buff[1] << 8 | rx_buff[2];
                    configuration = rx_buff[3];
                    break;
                default:
                    break;
            }
        }
    }

    if(mcp3421_mode == MCP3421_MODE_OS) {
        app_twi_tx_func(mcp3421_device_address, mcp3421_configuration, NULL, 0);
    }

    return;
}
```

## 構成Parts
-

## GitHub
