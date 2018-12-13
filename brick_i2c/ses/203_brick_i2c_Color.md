# #203 Color I2C Brick

## Overview



## Connecting

ShinobiとFabo Colorを接続。

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
SEGGER_Flash.icfファイルを編集する。(SEGGER_Flash.icfはProject配下に自動生成されている。以下抜粋)
```c
 :
 define block log_const_data { section .log_const_data* };
 define block log_dynamic_data { section .log_dynamic_data* };
 :
place in FLASH                           {
                                           block tdata_load,                       // Thread-local-storage load image
                                           section .log_backends,
                                           section .nrf_balloc,
                                           block log_const_data,
                                           block log_dynamic_data
                                         };
 :
```

## IRQHandler
Cortex_M_Startup.sファイルを編集する。(長いので抜粋)
```c
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
```

## Sample Code
main.c
```c
#define NRF_LOG_MODULE_NAME FABO_203_COLOR
#include"app_error.h"
#include"nrf_log.h"
#include"nrf_log_ctrl.h"
#include"nrf_log_default_backends.h"
#include"s11059.h"

NRF_LOG_MODULE_REGISTER();

int main(void) {
    uint16_t    red, green, blue, infrared;

    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();

    NRF_LOG_INFO("FABO 203 COLOR SAMPLE");
    NRF_LOG_FLUSH();

    s11059_initialize();
    s11059_parameter_set(S11059_GAIN_HIGH, S11059_MODE_MANUAL, S11059_CTRL_TIME_875U, 0x0C30);
    s11059_measurement_start();

    while(1) {
        s11059_measurement_rgbi_delay(&red, &green, &blue, &infrared);
        NRF_LOG_INFO("red:      :%d", red);
        NRF_LOG_INFO("green     :%d", green);
        NRF_LOG_INFO("blue      :%d", blue);
        NRF_LOG_INFO("infrared  :%d", infrared);
        NRF_LOG_FLUSH();
    }
}
```

s11059.h
```c
#ifndef _S11059_H
#define _S11059_H

#define S11059_CONTROL          0x00
#define S11059_TIMING_H         0x01
#define S11059_TIMING_L         0x02
#define S11059_DATA_RED_H       0x03
#define S11059_DATA_RED_L       0x04
#define S11059_DATA_GREEN_H     0x05
#define S11059_DATA_GREEN_L     0x06
#define S11059_DATA_BLUE_H      0x07
#define S11059_DATA_BLUE_L      0x08
#define S11059_DATA_IR_H        0x09
#define S11059_DATA_IR_L        0x0A
#define S11059_CTRL_RESET       0x80
#define S11059_CTRL_SLEEP       0x40
#define S11059_CTRL_GAIN        0x08
#define S11059_CTRL_MODE        0x04
#define S11059_CTRL_TIME_875U   0x00
#define S11059_CTRL_TIME_14M    0x01
#define S11059_CTRL_TIME_224M   0x02
#define S11059_CTRL_TIME_1792M  0x03
#define S11059_GAIN_HIGH        1
#define S11059_GAIN_LOW         0
#define S11059_MODE_MANUAL      1
#define S11059_MODE_FIXED       0
#define S11059_SLAVE_ADDRESS    0x2A

void    s11059_initialize(void);
void    s11059_parameter_set(uint8_t, uint8_t, uint8_t, uint16_t);
void    s11059_measurement_start(void);
void    s11059_measurement_rgbi_nodelay(uint16_t*, uint16_t*, uint16_t*, uint16_t*);
void    s11059_measurement_rgbi_delay(uint16_t*, uint16_t*, uint16_t*, uint16_t*);

#endif
```

s11059.c
```c
#define NRF_LOG_MODULE_NAME S11059
#include "app_error.h"
#include "nrf_delay.h"
#include "nrf_log.h"
#include "s11059.h"
#include "app_twi.h"

static uint8_t              s11059_gain;
static uint8_t              s11059_mode;
static uint8_t              s11059_time;
static uint16_t             s11059_timing;
static uint8_t              s11059_config;
NRF_LOG_MODULE_REGISTER();

void    s11059_initialize(void) {
    app_twi_init();
}

void    s11059_timing_parameter_set(uint16_t timing) {
    uint8_t tx_buff[2] = { (timing & 0xff00) >> 8, timing & 0x00ff };

    s11059_timing = timing;
    if(s11059_mode == S11059_MODE_MANUAL) {
        app_twi_tx_func(S11059_SLAVE_ADDRESS, S11059_TIMING_H, tx_buff, sizeof(tx_buff));
    }
}

void    s11059_control_parameter_set(uint8_t gain, uint8_t mode, uint8_t time) {
    uint8_t tx_buff;
    uint8_t rx_buff;

    s11059_gain     = gain;
    s11059_mode     = mode;
    s11059_time     = time;

    app_twi_rx_func(S11059_SLAVE_ADDRESS, S11059_CONTROL, &rx_buff, sizeof(rx_buff));
    s11059_config = rx_buff;

    tx_buff = rx_buff;

    if(s11059_gain == S11059_GAIN_HIGH) {
        tx_buff |= S11059_CTRL_GAIN;
    } else {
        tx_buff &= ~S11059_CTRL_GAIN;
    }

    if(mode == S11059_MODE_MANUAL) {
        tx_buff |= S11059_CTRL_MODE;
    } else {
        tx_buff &= ~S11059_CTRL_MODE;
    }

    tx_buff &= 0xFC;
    tx_buff |= time;    
    tx_buff |= 0xC0;

    app_twi_tx_func(S11059_SLAVE_ADDRESS, S11059_CONTROL, &tx_buff, sizeof(tx_buff));
}

void    s11059_parameter_set(uint8_t gain, uint8_t mode, uint8_t time, uint16_t timing) {
    s11059_control_parameter_set(gain, mode, time);
    s11059_timing_parameter_set(timing);
}

void    s11059_measurement_start(void) {
    uint8_t tx_buff;
    uint8_t rx_buff;

    app_twi_rx_func(S11059_SLAVE_ADDRESS, S11059_CONTROL, &rx_buff, sizeof(rx_buff));
    s11059_config = rx_buff;
    tx_buff = rx_buff & 0x3f;

    app_twi_tx_func(S11059_SLAVE_ADDRESS, S11059_CONTROL, &tx_buff, sizeof(tx_buff));
}

void    s11059_measurement_rgbi(uint16_t* red, uint16_t* green, uint16_t* blue, uint16_t* infrared) {
    uint8_t rx_buff[8];

    app_twi_rx_func(S11059_SLAVE_ADDRESS, S11059_DATA_RED_H, rx_buff, sizeof(rx_buff));

    *red        = ((uint16_t)rx_buff[0] << 8) | rx_buff[1];
    *green      = ((uint16_t)rx_buff[2] << 8) | rx_buff[3];
    *blue       = ((uint16_t)rx_buff[4] << 8) | rx_buff[5];
    *infrared   = ((uint16_t)rx_buff[6] << 8) | rx_buff[7];
}

void    s11059_measurement_rgbi_nodelay(uint16_t* red, uint16_t* green, uint16_t* blue, uint16_t* infrared) {
    s11059_measurement_rgbi(red, blue, green, infrared);
}

void    s11059_measurement_stop(void) {
    uint8_t tx_buff;
    uint8_t rx_buff;

    app_twi_rx_func(S11059_SLAVE_ADDRESS, S11059_CONTROL, &rx_buff, sizeof(rx_buff));

    s11059_config = rx_buff;
    tx_buff = rx_buff;
    tx_buff |= 0x80;
    tx_buff &= 0xbf;

    app_twi_tx_func(S11059_SLAVE_ADDRESS, S11059_CONTROL, &tx_buff, sizeof(tx_buff));
}

void    s11059_check_sleep_bit(void) {
    uint8_t rx_data;

    while(true) {
        app_twi_rx_func(S11059_SLAVE_ADDRESS, S11059_CONTROL, &rx_data, sizeof(rx_data));
        if((rx_data & 0x20) == 0x20) {
            break;
        }
        nrf_delay_ms(10);
    }
}

void    s11059_measurement_restart(void) {
    s11059_measurement_stop();
    s11059_measurement_start();
    s11059_check_sleep_bit();
}


void    s11059_measurement_rgbi_delay(uint16_t* red, uint16_t* green, uint16_t* blue, uint16_t* infrared) {
    uint32_t    delay_us;

    if(s11059_mode == S11059_MODE_FIXED) {
        switch(s11059_time) {
            case S11059_CTRL_TIME_875U:
                delay_us = 88 * 4;
                break;
            case S11059_CTRL_TIME_14M:
                delay_us = 1400 * 4;
                break;
            case S11059_CTRL_TIME_224M:
                delay_us = 22400 * 4;
                break;
            case S11059_CTRL_TIME_1792M:
                delay_us = 179200 * 4;
                break;
            default:
                return;
        }
        nrf_delay_us(delay_us);
    } else if(s11059_mode == S11059_MODE_MANUAL) {
        s11059_measurement_restart();
    }

    s11059_measurement_rgbi(red, blue, green, infrared);
}
```

app_twi.c/app_twi.hは省略(202を参照)

## 構成Parts
-

## GitHub
