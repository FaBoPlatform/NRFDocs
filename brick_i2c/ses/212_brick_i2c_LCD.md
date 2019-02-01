# #212 LCD I2C Brick

## Overview



## Connecting

ShinobiとFabo 212 LCDを接続。

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
#include "pcf8574.h"
#include "lcd1602a.h"
#include "nrf_delay.h"

NRF_LOG_MODULE_REGISTER();

uint8_t text_data[] = "212 LCD SAMPLE";

void    main(
    void
) {
    app_log_init();

    NRF_LOG_INFO("212 LCD sample");

    APP_ERROR_CHECK(nrf_pwr_mgmt_init());

    pcf8574_initialize();

    lcd1602a_initialize(LCD1602A_MODE_4BIT);
    lcd1602a_function_set(LCD1602A_MODE_4BIT | LCD1602A_MODE_1LINE | LCD1602A_MODE_5x8DOTS);
    lcd1602a_display_control(LCD1602A_DISPLAY_ON | LCD1602A_DISPLAY_CURSOR_OFF | LCD1602A_DISPLAY_CURSOR_BLINK_OFF);
    lcd1602a_clear_display();
    lcd1602a_entry_mode_set(LCD1602A_MODE_DDRAM_ADDR_DEC | LCD1602A_MODE_SHIFT_TO_RIGHT);
    lcd1602a_write_data(text_data, sizeof(text_data));
    
    while(true) {
        nrf_delay_ms(1000);
        if(NRF_LOG_PROCESS() == false) {
            nrf_pwr_mgmt_run();
        } else {
            NRF_LOG_FLUSH();
        }
    }
}
```

pcf8574.c
```c
#define NRF_LOG_MODULE_NAME PCF8574
#include "nrf_log.h"
#include "app_twi.h"
#include "pcf8574.h"
#include "lcd1602a.h"
#include "nrf_delay.h"

NRF_LOG_MODULE_REGISTER();

void    pcf8574_initialize(
    void
) {
    app_twi_initialize();

    app_twi_search_device_id();
}
```

pcf8574.h
```c
#ifndef _PCF8574_H
#define _PCF8574_H

void    pcf8574_initialize(void);

#endif
```

lcd1602a.cpp
```c
#define NRF_LOG_MODULE_NAME LCD1602A
#include "nrf_log.h"
#include "nrf_delay.h"
#include "app_twi.h"
#include "lcd1602a.h"

NRF_LOG_MODULE_REGISTER();

void    lcd1602a_twi_tx(
    uint8_t     reg_addr,
    uint8_t*    data,
    uint16_t    length,
    bool        tx_addr_flag
) {
    uint32_t    i;
    uint8_t     tx_data[2];

    for(i = 0; i < length; i++) {

        memset(tx_data, *(data + i), sizeof(tx_data));

        tx_data[0] |= LCD1602A_EN_BIT;

        app_twi_tx(0, tx_data, sizeof(tx_data), false);

        nrf_delay_ms(2);

    }
}

void    lcd1602a_initialize(
    uint8_t mode
) {
    uint8_t tx_data = LCD1602A_D5_BIT | LCD1602A_D4_BIT | LCD1602A_BL_BIT;
    if(mode == LCD1602A_MODE_4BIT) {

        nrf_delay_ms(40);

        lcd1602a_twi_tx(0, &tx_data, sizeof(tx_data), false);

        nrf_delay_ms(5);

        lcd1602a_twi_tx(0, &tx_data, sizeof(tx_data), false);

        nrf_delay_ms(1);

        lcd1602a_twi_tx(0, &tx_data, sizeof(tx_data), false);

        tx_data = LCD1602A_D5_BIT | LCD1602A_BL_BIT;
        lcd1602a_twi_tx(0, &tx_data, sizeof(tx_data), false);

    }

    nrf_delay_ms(2);
}

void    lcd1602a_function_set(
    uint8_t data
) {
    uint8_t tx_data[2];

    memset(tx_data, 0, sizeof(tx_data));

    tx_data[0] = LCD1602A_BL_BIT | LCD1602A_CMD_FUNCTION_SET | (data & LCD1602A_MODE_8BIT);
    tx_data[1] = LCD1602A_BL_BIT | ((data & 0x0f) << 4);

    lcd1602a_twi_tx(0, tx_data, sizeof(tx_data), false);

    nrf_delay_ms(1);
}

void    lcd1602a_display_control(
    uint8_t data
) {
    uint8_t tx_data[2];

    memset(tx_data, 0, sizeof(tx_data));

    tx_data[0] = LCD1602A_BL_BIT;
    tx_data[1] = LCD1602A_BL_BIT | (LCD1602A_CMD_DISPLAY_CTRL << 4) | (data << 4);

    lcd1602a_twi_tx(0, tx_data, sizeof(tx_data), false);

    nrf_delay_ms(1);
}

void    lcd1602a_clear_display(
    void
) {
    uint8_t tx_data[2];

    memset(tx_data, 0, sizeof(tx_data));

    tx_data[0] = LCD1602A_BL_BIT;
    tx_data[1] = LCD1602A_BL_BIT | (LCD1602A_CMD_CLEAR_DISPLAY << 4);

    lcd1602a_twi_tx(0, tx_data, sizeof(tx_data), false);

    nrf_delay_ms(2);
}


void    lcd1602a_entry_mode_set(
    uint8_t data
) {
    uint8_t tx_data[2];

    memset(tx_data, 0, sizeof(tx_data));

    tx_data[0] = LCD1602A_BL_BIT;
    tx_data[1] = LCD1602A_BL_BIT | ((LCD1602A_CMD_ENTRY_MODE_SET | data) << 4);

    lcd1602a_twi_tx(0, tx_data, sizeof(tx_data), false);

    nrf_delay_ms(2);
}

void    lcd1602a_write_data(
    uint8_t*    address,
    uint32_t    length
) {
    uint32_t    i;
    uint8_t     tx_data[2];

    NRF_LOG_HEXDUMP_DEBUG(address, length);

    for(i = 0; i < length; i++) {

        if(*(address + i) != 0x00) {

            memset(tx_data, 0, sizeof(tx_data));

            tx_data[0] = LCD1602A_BL_BIT | LCD1602A_RS_BIT | *(address + i) & 0xF0;
            tx_data[1] = LCD1602A_BL_BIT | LCD1602A_RS_BIT | ((*(address + i) & 0x0F) << 4);

            lcd1602a_twi_tx(0, tx_data, sizeof(tx_data), false);

            nrf_delay_ms(1);

            NRF_LOG_DEBUG("data = 0x%x", *(address + i));
            NRF_LOG_HEXDUMP_DEBUG(tx_data, sizeof(tx_data));

        }

    }

}
```

lcd1602a.h
```c
#ifndef _LCD1602A_H
#define _LCD1602A_H

#define LCD1602A_CMD_CLEAR_DISPLAY  0x01
#define LCD1602A_CMD_RETURN_HOME    0x02
#define LCD1602A_CMD_ENTRY_MODE_SET 0x04
#define LCD1602A_CMD_DISPLAY_CTRL   0x08
#define LCD1602A_CMD_CURSOR_SHIFT   0x10
#define LCD1602A_CMD_FUNCTION_SET   0x20
#define LCD1602A_CMD_SET_CGRAMADDR  0x40
#define LCD1602A_CMD_SET_DDRAMADDR  0x80

#define LCD1602A_MODE_8BIT  0x10
#define LCD1602A_MODE_4BIT  0x00

#define LCD1602A_MODE_1LINE     0x00
#define LCD1602A_MODE_2LINE     0x08
#define LCD1602A_MODE_5x10DOTS  0x04
#define LCD1602A_MODE_5x8DOTS   0x00

#define LCD1602A_MODE_DDRAM_ADDR_INC    0x00
#define LCD1602A_MODE_DDRAM_ADDR_DEC    0x02

#define LCD1602A_MODE_SHIFT_TO_RIGHT  0x00
#define LCD1602A_MODE_SHIFT_TO_LEFT   0x01

#define LCD1602A_DISPLAY_ON                 0x04
#define LCD1602A_DISPLAY_OFF                0x00
#define LCD1602A_DISPLAY_CURSOR_ON          0x02
#define LCD1602A_DISPLAY_CURSOR_OFF         0x00
#define LCD1602A_DISPLAY_CURSOR_BLINK_ON    0x01
#define LCD1602A_DISPLAY_CURSOR_BLINK_OFF   0x00

#define LCD1602A_RS_BIT 0x01
#define LCD1602A_RW_BIT 0x02
#define LCD1602A_EN_BIT 0x04
#define LCD1602A_BL_BIT 0x08
#define LCD1602A_D4_BIT 0x10
#define LCD1602A_D5_BIT 0x20
#define LCD1602A_D6_BIT 0x40
#define LCD1602A_D7_BIT 0x80



void    lcd1602a_initialize(uint8_t);
void    lcd1602a_function_set(uint8_t);
void    lcd1602a_display_control(uint8_t);
void    lcd1602a_clear_display(void);
void    lcd1602a_entry_mode_set(uint8_t);
void    lcd1602a_write_data(uint8_t* address, uint32_t length);

#endif
```

app_log.c
```c
#include "app_error.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "nrf_pwr_mgmt.h"

#include "app_log.h"

void    app_log_init(void) {
    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();
}
```

app_log.h
```c
#ifndef _APP_LOG_H
#define _APP_LOG_H

void    app_log_init(void);

#endif
```

app_twi.c
```c
#define NRF_LOG_MODULE_NAME APP_TWI
#ifndef APP_LOG_ENABLED
#define NRF_LOG_LEVEL   3
#endif
#include "app_error.h"
#include "nrf_drv_twi.h"
#include "nrf_log.h"
#include "app_twi.h"

#define ARDUINO_SCL_PIN 27
#define ARDUINO_SDA_PIN 26

static nrf_drv_twi_t    app_twi_instance    =   NRF_DRV_TWI_INSTANCE(0);
static volatile bool    app_twi_xfer_done;
static volatile bool    app_twi_device_id_set_done;
static uint8_t          app_twi_device_id;
NRF_LOG_MODULE_REGISTER();

void    app_twi_event_handler(nrf_drv_twi_evt_t const* a_event, void* a_context) {
    NRF_LOG_DEBUG("app_twi_event_handler() ### START ###");
    NRF_LOG_DEBUG("a_event->type = %d", a_event->type);
    switch(a_event->type) {
        case NRF_DRV_TWI_EVT_DONE:
            if(app_twi_device_id_set_done == false) {
                app_twi_device_id = a_event->xfer_desc.address;
                app_twi_device_id_set_done = true;
            }
            break;
        case NRF_DRV_TWI_EVT_ADDRESS_NACK:
            NRF_LOG_ERROR("NRF_DRV_TWI_EVENT_ADDRESS_NACK");
            break;
        case NRF_DRV_TWI_EVT_DATA_NACK:
            NRF_LOG_ERROR("NRF_DRV_TWI_EVT_DATA_NACK");
            break;
        default:
            break;
    }

    NRF_LOG_DEBUG("app_twi_xfer_done = %d", app_twi_xfer_done);
    if(app_twi_xfer_done == false) {
        app_twi_xfer_done = true;
    }

    NRF_LOG_DEBUG("app_twi_event_handler() ### END ###");
}

void    app_twi_initialize(void) {
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

void    app_twi_tx(
    uint8_t     reg_addr,
    uint8_t*    data,
    uint16_t    length,
    bool        tx_addr_flag
) {
    uint8_t tx_length = 0;
    uint8_t tx_buff[length + 1];

    NRF_LOG_DEBUG("app_twi_tx_func() ### START ###");
    NRF_LOG_DEBUG("reg_addr     : %02X", reg_addr);
    NRF_LOG_DEBUG("data         : %08X", data);
    NRF_LOG_DEBUG("length       : %d", length);
    NRF_LOG_DEBUG("tx_addr_flag : %d", tx_addr_flag);

    memset(tx_buff, 0, length + 1);

    if(tx_addr_flag == true) {
        tx_buff[0] = reg_addr;
        tx_length++;
    }

    if(length != 0) {
        memcpy(&tx_buff[tx_length], data, length);
        tx_length += length;
    }

    NRF_LOG_HEXDUMP_DEBUG(tx_buff, tx_length);

    app_twi_xfer_done = false;
    APP_ERROR_CHECK(nrf_drv_twi_tx(&app_twi_instance, app_twi_device_id, tx_buff, tx_length, false));
    while(app_twi_xfer_done == false);

    NRF_LOG_DEBUG("app_twi_tx_func() ### END ###");

    return;
}

void    app_twi_rx(
    uint8_t     reg_addr,
    uint8_t*    data,
    uint16_t    len,
    bool        tx_addr_flag
) {

    NRF_LOG_DEBUG("app_twi_rx_func() ### START ###");
    NRF_LOG_DEBUG("reg_addr     : %02X", reg_addr);
    NRF_LOG_DEBUG("data         : %08X", data);
    NRF_LOG_DEBUG("len          : %d", len);
    NRF_LOG_DEBUG("tx_addr_flag : %d", tx_addr_flag);

    memset(data, 0x00, len);

    if(tx_addr_flag == true) {
        app_twi_tx(reg_addr, NULL, 0, true);
    }

    app_twi_xfer_done = false;
    APP_ERROR_CHECK(nrf_drv_twi_rx(&app_twi_instance, app_twi_device_id, data, len));
    while(app_twi_xfer_done == false);

    NRF_LOG_HEXDUMP_DEBUG(data, len);

    NRF_LOG_DEBUG("app_twi_rx_func() ### END ###");

    return;
}

void    app_twi_set_device_id(
    uint8_t device_id
) {
    app_twi_device_id = device_id;
}

void    app_twi_search_device_id(
    void
) {
    uint32_t    i;
    uint8_t     rx_data;

    app_twi_device_id_set_done = false;
    for(i = 0; (i <= 0xff) && (app_twi_device_id_set_done == false); i++) {
        app_twi_xfer_done = false;
        APP_ERROR_CHECK(nrf_drv_twi_rx(&app_twi_instance, i, &rx_data, sizeof(rx_data)));
        while(app_twi_xfer_done == false);
    }

    NRF_LOG_INFO("app_twi_device_id = 0x%02X", app_twi_device_id);
    NRF_LOG_INFO("rx_data = 0x%02X", rx_data);
}
```

app_twi.h
```c
#ifndef _APP_TWI_H
#define _APP_TWI_H

void    app_twi_initialize(void);
void    app_twi_tx(uint8_t reg_addr, uint8_t* tx_buff_addr, uint16_t tx_data_size, bool tx_addr_flg);
void    app_twi_rx(uint8_t reg_addr, uint8_t* rx_buff_addr, uint16_t rx_data_size, bool tx_addr_flg);
void    app_twi_set_device_id(uint8_t);
void    app_twi_search_device_id(void);

#endif
```

## 構成Parts
-

## GitHub
