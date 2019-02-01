# #213 LCD mini I2C Brick

## Overview



## Connecting

ShinobiとFabo 213 LCD miniを接続。

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
#include "nrf_delay.h"

#include "app_log.h"
#include "aqm0802a.h"
NRF_LOG_MODULE_REGISTER();

void    main(
    void
) {
    uint8_t buffer[16];

    app_log_init();

    NRF_LOG_INFO("213 LCD mini");

    APP_ERROR_CHECK(nrf_pwr_mgmt_init());

    aqm0802a_initialize();

    for(int i = 0; ; i++) {
        snprintf(buffer, sizeof(buffer), "%d%d", i, i);
        aqm0802a_write_data(buffer);
        if(NRF_LOG_PROCESS() == false) {
            nrf_pwr_mgmt_run();
        } else {
            NRF_LOG_FLUSH();
        }
        nrf_delay_ms(1000);
    }
}
```

aqm0802a.h
```c
#ifndef _AQM0802A_H
#define _AQM0802A_H

#define AQM0802A_SLAVE_ADDRESS  0x3e

#define DB0 0x01
#define DB1 0x02
#define DB2 0x04
#define DB3 0x08
#define DB4 0x10
#define DB5 0x20
#define DB6 0x40
#define DB7 0x80

#define AQM0802A_CMD_CLEAR_DISPLAY                  DB0
#define AQM0802A_CMD_RETURN_HOME                    DB1
#define AQM0802A_CMD_ENTRY_MODE_SET                 DB2
#define AQM0802A_CMD_DISPLAY_IO_CONTROL             DB3
#define AQM0802A_CMD_INTERNAL_OSC_FREQUENCY         DB4
#define AQM0802A_CMD_FUNCTION_SET                   DB5
#define AQM0802A_CMD_SET_DDRAM_ADDR                 DB7
#define AQM0802A_CMD_CONTRAST_SET                   (DB6 | DB5 | DB4)
#define AQM0802A_CMD_POWER_ICON_CONTRAST_CONTROL    (DB6 | DB4)
#define AQM0802A_CMD_FOLLOWER_CONTROL               (DB6 | DB5)

#define AQM0802A_DIOC_D DB2
#define AQM0802A_DIOC_C DB1
#define AQM0802A_DIOC_B DB0

#define AQM0802A_FC_FON     DB3
#define AQM0802A_FC_RAB2    DB2
#define AQM0802A_FC_RAB1    DB1
#define AQM0802A_FC_RAB0    DB0

#define AQM0802A_PICC_ION   DB3
#define AQM0802A_PICC_BON   DB2
#define AQM0802A_PICC_C5    DB1
#define AQM0802A_PICC_C4    DB0

#define AQM0802A_IOF_BS DB3
#define AQM0802A_IOF_F2 DB2
#define AQM0802A_IOF_F1 DB1
#define AQM0802A_IOF_F0 DB0

#define AQM0802A_FS_DL  DB4
#define AQM0802A_FS_N   DB3
#define AQM0802A_FS_DH  DB2
#define AQM0802A_FS_IS  DB0

#define AQM0802A_CO_BIT DB7

#define AQM0802A_RS_BIT DB6

#define AQM0802A_DDRAM_ADDRESS_L1   0x00
#define AQM0802A_DDRAM_ADDRESS_L2   0x40

void    aqm0802a_initialize(void);
void    aqm0802a_function_set(uint8_t);
void    aqm0802a_internal_osc_frequency(uint8_t);
void    aqm0802a_contrast_set(uint8_t);
void    aqm0802a_power_icon_contrast_control(uint8_t);
void    aqm0802a_follower_control(uint8_t);
void    aqm0802a_display_io_control(uint8_t);
void    aqm0802a_clear_display(uint8_t);
void    aqm0802a_set_ddram_address(uint8_t);
void    aqm0802a_write_data(uint8_t*);

#endif
```

aqm0802a.c
```c
#define NRF_LOG_MODULE_NAME AQM0802A
#ifndef APP_LOG_ENABLED
#define NRF_LOG_LEVEL   4
#endif
#include "nrf_log.h"
#include "nrf_delay.h"

#include "aqm0802a.h"
#include "app_twi.h"
#include "app_log.h"

NRF_LOG_MODULE_REGISTER();

void    aqm0802a_initialize(
    void
){
    app_twi_initialize();

    nrf_delay_ms(50);
    aqm0802a_function_set(AQM0802A_FS_DL | AQM0802A_FS_N);
    nrf_delay_ms(1);
    aqm0802a_function_set(AQM0802A_FS_DL | AQM0802A_FS_N | AQM0802A_FS_IS);
    nrf_delay_ms(1);
    aqm0802a_internal_osc_frequency(AQM0802A_IOF_F2);
    nrf_delay_ms(1);
    aqm0802a_contrast_set(0);
    nrf_delay_ms(1);
    aqm0802a_power_icon_contrast_control(AQM0802A_PICC_BON | AQM0802A_PICC_C5);
    nrf_delay_ms(1);
    aqm0802a_follower_control(AQM0802A_FC_FON | AQM0802A_FC_RAB2);
    nrf_delay_ms(300);
    aqm0802a_function_set(AQM0802A_FS_DL | AQM0802A_FS_N);
    nrf_delay_ms(1);
    aqm0802a_display_io_control(AQM0802A_DIOC_D);
    nrf_delay_ms(1);
    aqm0802a_clear_display(0);
    nrf_delay_ms(2);
}

void    aqm0802a_function_set(
    uint8_t option
){
    uint8_t tx_data[2];

    app_log_func_start();

    tx_data[0] = 0;
    tx_data[1] = option | AQM0802A_CMD_FUNCTION_SET;
    NRF_LOG_HEXDUMP_DEBUG(tx_data, sizeof(tx_data));
    app_twi_tx(AQM0802A_SLAVE_ADDRESS, 0, tx_data, sizeof(tx_data), false);

    app_log_func_end();
}

void    aqm0802a_internal_osc_frequency(
    uint8_t option
) {
    uint8_t tx_data[2];

    app_log_func_start();

    tx_data[0] = 0;
    tx_data[1] = option | AQM0802A_CMD_INTERNAL_OSC_FREQUENCY;
    NRF_LOG_HEXDUMP_DEBUG(tx_data, sizeof(tx_data));
    app_twi_tx(AQM0802A_SLAVE_ADDRESS, 0, tx_data, sizeof(tx_data), false);

    app_log_func_end();
}

void    aqm0802a_contrast_set(
    uint8_t option
) {
    uint8_t tx_data[2];

    app_log_func_start();

    tx_data[0] = 0;
    tx_data[1] = option | AQM0802A_CMD_CONTRAST_SET;
    NRF_LOG_HEXDUMP_DEBUG(tx_data, sizeof(tx_data));
    app_twi_tx(AQM0802A_SLAVE_ADDRESS, 0, tx_data, sizeof(tx_data), false);

    app_log_func_end();
}

void    aqm0802a_power_icon_contrast_control(
    uint8_t option
) {
    uint8_t tx_data[2];

    app_log_func_start();

    tx_data[0] = 0;
    tx_data[1] = option | AQM0802A_CMD_POWER_ICON_CONTRAST_CONTROL;
    NRF_LOG_HEXDUMP_DEBUG(tx_data, sizeof(tx_data));
    app_twi_tx(AQM0802A_SLAVE_ADDRESS, 0, tx_data, sizeof(tx_data), false);

    app_log_func_end();
}

void    aqm0802a_follower_control(
    uint8_t option
) {
    uint8_t tx_data[2];

    app_log_func_start();

    tx_data[0] = 0;
    tx_data[1] = option | AQM0802A_CMD_FOLLOWER_CONTROL;
    NRF_LOG_HEXDUMP_DEBUG(tx_data, sizeof(tx_data));
    app_twi_tx(AQM0802A_SLAVE_ADDRESS, 0, tx_data, sizeof(tx_data), false);

    app_log_func_end();
}

void    aqm0802a_display_io_control(
    uint8_t option
) {
    uint8_t tx_data[2];

    app_log_func_start();

    tx_data[0] = 0;
    tx_data[1] = option | AQM0802A_CMD_DISPLAY_IO_CONTROL;
    NRF_LOG_HEXDUMP_DEBUG(tx_data, sizeof(tx_data));
    app_twi_tx(AQM0802A_SLAVE_ADDRESS, 0, tx_data, sizeof(tx_data), false);

    app_log_func_end();
}

void    aqm0802a_clear_display(
    uint8_t option
) {
    uint8_t tx_data[2];

    app_log_func_start();

    tx_data[0] = 0;
    tx_data[1] = option | AQM0802A_CMD_CLEAR_DISPLAY;
    NRF_LOG_HEXDUMP_DEBUG(tx_data, sizeof(tx_data));
    app_twi_tx(AQM0802A_SLAVE_ADDRESS, 0, tx_data, sizeof(tx_data), false);

    app_log_func_end();
}

void    aqm0802a_set_ddram_address(
    uint8_t address
) {
    uint8_t tx_data[2];

    app_log_func_start();

    tx_data[0] = 0;
    tx_data[1] = address | AQM0802A_CMD_SET_DDRAM_ADDR;
    NRF_LOG_HEXDUMP_DEBUG(tx_data, sizeof(tx_data));
    app_twi_tx(AQM0802A_SLAVE_ADDRESS, 0, tx_data, sizeof(tx_data), false);

    nrf_delay_ms(1);

    app_log_func_end();    
}

void    aqm0802a_write_data(
    uint8_t*    data
) {
    uint32_t    i;
    uint32_t    size = strlen(data);
    uint8_t     tx_data[2];

    app_log_func_start();

    aqm0802a_set_ddram_address(AQM0802A_DDRAM_ADDRESS_L1);

    for(i = 0; i < size && i < 8; i++) {
        tx_data[0] = AQM0802A_RS_BIT;
        tx_data[1] = *(data + i);
        NRF_LOG_HEXDUMP_DEBUG(tx_data, sizeof(tx_data));
        app_twi_tx(AQM0802A_SLAVE_ADDRESS, 0, tx_data, sizeof(tx_data), false);
        nrf_delay_ms(1);
    }

    aqm0802a_set_ddram_address(AQM0802A_DDRAM_ADDRESS_L2);

    for(; i < size; i++) {
        tx_data[0] = AQM0802A_RS_BIT;
        tx_data[1] = *(data + i);
        NRF_LOG_HEXDUMP_DEBUG(tx_data, sizeof(tx_data));
        app_twi_tx(AQM0802A_SLAVE_ADDRESS, 0, tx_data, sizeof(tx_data), false);
        nrf_delay_ms(1);
    }

    app_log_func_end();
}
```

## 構成Parts
-

## GitHub
