# #205 Proximity I2C Brick

## Overview



## Connecting

ShinobiとFabo Proximityを接続。

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
#define NRF_LOG_MODULE_NAME 205_FABO_PROXIMITY
#include "app_error.h"
#include "nrf_delay.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "vcnl4010.h"

NRF_LOG_MODULE_REGISTER();

int main(void) {
    uint16_t proximity, ambient_light;
    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();

    NRF_LOG_INFO("FABO 205 PROXIMITY SAMPLE");

    vcnl4010_initialize();
    vcnl4010_set_command(VCNL4010_CMD_PROX_EN | VCNL4010_CMD_ALS_EN);
    vcnl4010_set_proximity_rate(VCNL4010_PROX_RATE_4S);
    vcnl4010_set_ir_led_current_value(VCNL4010_IR_LED_CUR_2);
    vcnl4010_set_ambient_light_parameter(true, VCNL4010_AL_MEASURE_RATE_2S, true, VCNL4010_AL_AVR_CYCLE_32);

    while(true) {
        vcnl4010_measurement(&proximity, &ambient_light);
        NRF_LOG_INFO("proximity   = %u", proximity);
        NRF_LOG_INFO("ambient_light = %u", ambient_light);
        NRF_LOG_FLUSH();
        nrf_delay_ms(1000);
    }


}
```

vcnl4010.h
```c
#ifndef _VCNL4010_H
#define _VCNL4010_H

#define VCNL4010_SLAVE_ADDRESS  0x13

#define VCNL4010_REG_ADDR_COMMAND       0x80
#define VCNL4010_REG_ADDR_PRID_REV      0x81
#define VCNL4010_REG_ADDR_PROX_RATE     0x82
#define VCNL4010_REG_ADDR_IR_LED_CUR    0x83
#define VCNL4010_REG_ADDR_AL_PARAM      0x84
#define VCNL4010_REG_ADDR_AL_H          0x85
#define VCNL4010_REG_ADDR_AL_L          0x86
#define VCNL4010_REG_ADDR_PROX_H        0x87
#define VCNL4010_REG_ADDR_PROX_L        0x88

#define VCNL4010_CMD_ALS_RDY        0x40
#define VCNL4010_CMD_PROX_RDY       0x20
#define VCNL4010_CMD_ALS_OD         0x10
#define VCNL4010_CMD_PROX_OD        0x08
#define VCNL4010_CMD_ALS_EN         0x05
#define VCNL4010_CMD_PROX_EN        0x03
#define VCNL4010_CMD_SELFTIMED_EN   0x01

#define VCNL4010_CONT_CONV_MODE 0x80
#define VCNL4010_AUTO_OFFSET    0x08

#define VCNL4010_PROX_RATE_2S   0
#define VCNL4010_PROX_RATE_4S   1
#define VCNL4010_PROX_RATE_8S   2
#define VCNL4010_PROX_RATE_17S  3
#define VCNL4010_PROX_RATE_31S  4
#define VCNL4010_PROX_RATE_63S  5
#define VCNL4010_PROX_RATE_125S 6
#define VCNL4010_PROX_RATE_250S 7

#define VCNL4010_IR_LED_CUR_0   0
#define VCNL4010_IR_LED_CUR_1   1
#define VCNL4010_IR_LED_CUR_2   2
#define VCNL4010_IR_LED_CUR_3   3
#define VCNL4010_IR_LED_CUR_4   4
#define VCNL4010_IR_LED_CUR_5   5
#define VCNL4010_IR_LED_CUR_6   6
#define VCNL4010_IR_LED_CUR_7   7
#define VCNL4010_IR_LED_CUR_8   8
#define VCNL4010_IR_LED_CUR_9   9
#define VCNL4010_IR_LED_CUR_10  10
#define VCNL4010_IR_LED_CUR_11  11
#define VCNL4010_IR_LED_CUR_12  12
#define VCNL4010_IR_LED_CUR_13  13
#define VCNL4010_IR_LED_CUR_14  14
#define VCNL4010_IR_LED_CUR_15  15
#define VCNL4010_IR_LED_CUR_16  16
#define VCNL4010_IR_LED_CUR_17  17
#define VCNL4010_IR_LED_CUR_18  18
#define VCNL4010_IR_LED_CUR_19  19
#define VCNL4010_IR_LED_CUR_20  20

#define VCNL4010_AL_MEASURE_RATE_1S     0
#define VCNL4010_AL_MEASURE_RATE_2S     1
#define VCNL4010_AL_MEASURE_RATE_3S     2
#define VCNL4010_AL_MEASURE_RATE_4S     3
#define VCNL4010_AL_MEASURE_RATE_5S     4
#define VCNL4010_AL_MEASURE_RATE_6S     5
#define VCNL4010_AL_MEASURE_RATE_8S     6
#define VCNL4010_AL_MEASURE_RATE_10S    7

#define VCNL4010_AL_AVR_CYCLE_1     0
#define VCNL4010_AL_AVR_CYCLE_2     1
#define VCNL4010_AL_AVR_CYCLE_4     2
#define VCNL4010_AL_AVR_CYCLE_8     3
#define VCNL4010_AL_AVR_CYCLE_16    4
#define VCNL4010_AL_AVR_CYCLE_32    5
#define VCNL4010_AL_AVR_CYCLE_64    6
#define VCNL4010_AL_AVR_CYCLE_128   7

void    vcnl4010_initialize(void);
void    vcnl4010_set_command(uint8_t);
void    vcnl4010_set_proximity_rate(uint8_t);
void    vcnl4010_set_ir_led_current_value(uint8_t);
void    vcnl4010_set_ambient_light_parameter(bool, uint8_t, bool, uint8_t);
void    vcnl4010_measurement(uint16_t*, uint16_t*);

#endif
```

vcnl4010.c
```c
#define NRF_LOG_MODULE_NAME VCNL4010
#include "app_error.h"
#include "nrf_delay.h"
#include "nrf_log.h"
#include "vcnl4010.h"
#include "app_twi.h"

static uint8_t          vcnl4010_mode           = 0;
static uint8_t          vcnl4010_prox_rate      = 0;
NRF_LOG_MODULE_REGISTER();

void    vcnl4010_measurement_proximity(uint16_t* proximity) {
    uint8_t     rx_buff[2];
    uint16_t    ret;

    app_twi_rx_func(VCNL4010_SLAVE_ADDRESS, VCNL4010_REG_ADDR_PROX_H, rx_buff, sizeof(rx_buff));

    NRF_LOG_HEXDUMP_DEBUG(rx_buff, sizeof(rx_buff));

    *proximity = ((uint16_t)rx_buff[0] << 8) | rx_buff[1];
    NRF_LOG_INFO("proximity  :%d", *proximity);
}

void    vcnl4010_measurement_proximity_ondemand(uint16_t* proximity) {
    uint8_t tx_buff = VCNL4010_CMD_PROX_OD;
    uint8_t rx_buff;

    app_twi_tx_func(VCNL4010_SLAVE_ADDRESS, VCNL4010_REG_ADDR_COMMAND, &tx_buff, sizeof(tx_buff));

    while(true) {
        app_twi_rx_func(VCNL4010_SLAVE_ADDRESS, VCNL4010_REG_ADDR_COMMAND, &rx_buff, sizeof(rx_buff));
        if((rx_buff & VCNL4010_CMD_PROX_RDY) == VCNL4010_CMD_PROX_RDY)
        {
            break;
        }
        nrf_delay_ms(10);
    }

    vcnl4010_measurement_proximity(proximity);
}

void    vcnl4010_measurement_ambient_light(uint16_t* ambient_light) {
    uint8_t rx_buff[2];

    app_twi_rx_func(VCNL4010_SLAVE_ADDRESS, VCNL4010_REG_ADDR_AL_H, rx_buff, sizeof(rx_buff));

    NRF_LOG_HEXDUMP_DEBUG(rx_buff, sizeof(rx_buff));

    *ambient_light = ((uint16_t)rx_buff[0] << 8) | rx_buff[1];
    NRF_LOG_DEBUG("ambient light:%d", *ambient_light);
}

void    vcnl4010_measurement_ambient_light_ondemand(uint16_t* ambient_light) {
    uint8_t     address = VCNL4010_REG_ADDR_COMMAND;
    uint8_t     command;
    uint8_t     command_data[2] = { VCNL4010_REG_ADDR_COMMAND, VCNL4010_CMD_ALS_OD };
    uint8_t     al_data[2];
    uint16_t    al_data_value;

    uint8_t tx_buff = VCNL4010_CMD_ALS_OD;
    uint8_t rx_buff;

    app_twi_tx_func(VCNL4010_SLAVE_ADDRESS, VCNL4010_REG_ADDR_COMMAND, &tx_buff, sizeof(tx_buff));

    while(true) {
        app_twi_rx_func(VCNL4010_SLAVE_ADDRESS, VCNL4010_REG_ADDR_COMMAND, &rx_buff, sizeof(rx_buff));
        if((rx_buff & VCNL4010_CMD_ALS_RDY) == VCNL4010_CMD_ALS_RDY)
        {
            break;
        }
        nrf_delay_ms(10);
    }

    vcnl4010_measurement_ambient_light(ambient_light);
}

void    vcnl4010_measurement(uint16_t* proximity, uint16_t* ambient_light) {
    if((vcnl4010_mode & (uint8_t)VCNL4010_CMD_PROX_EN) == (uint8_t)VCNL4010_CMD_PROX_EN) {
        vcnl4010_measurement_proximity(proximity);
    }

    if((vcnl4010_mode & (uint8_t)VCNL4010_CMD_PROX_OD) == (uint8_t)VCNL4010_CMD_PROX_OD) {
        vcnl4010_measurement_proximity_ondemand(proximity);
    }
    if((vcnl4010_mode & (uint8_t)VCNL4010_CMD_ALS_EN) == (uint8_t)VCNL4010_CMD_ALS_EN) {
        vcnl4010_measurement_ambient_light(ambient_light);
    }

    if((vcnl4010_mode & (uint8_t)VCNL4010_CMD_ALS_OD) == (uint8_t)VCNL4010_CMD_ALS_OD) {
        vcnl4010_measurement_ambient_light_ondemand(ambient_light);
    }
}

void    vcnl4010_set_command(uint8_t mode) {
    uint8_t tx_buff;

    vcnl4010_mode = mode;
    tx_buff = vcnl4010_mode;

    app_twi_tx_func(VCNL4010_SLAVE_ADDRESS, VCNL4010_REG_ADDR_COMMAND, &tx_buff, sizeof(tx_buff));
}

void    vcnl4010_set_ambient_light_parameter(
    bool    mode,
    uint8_t measure_rate,
    bool    auto_offset,
    uint8_t avr_cycle
){
    uint8_t tx_buff = 0;

    if(mode == true) {
        tx_buff |= VCNL4010_CONT_CONV_MODE;
    }

    tx_buff |= (measure_rate << 4);

    if(auto_offset == true) {
        tx_buff |= VCNL4010_AUTO_OFFSET;
    }

    tx_buff |= avr_cycle;

    app_twi_tx_func(VCNL4010_SLAVE_ADDRESS, VCNL4010_REG_ADDR_AL_PARAM, &tx_buff, sizeof(tx_buff));
}

void    vcnl4010_set_ir_led_current_value(uint8_t ir_led_cur) {
    uint8_t tx_buff = ir_led_cur;

    app_twi_tx_func(VCNL4010_SLAVE_ADDRESS, VCNL4010_REG_ADDR_IR_LED_CUR, &tx_buff, sizeof(tx_buff));
}

void    vcnl4010_set_proximity_rate(uint8_t prox_rate) {
    uint8_t tx_buff = prox_rate;

    vcnl4010_prox_rate = prox_rate;

    app_twi_tx_func(VCNL4010_SLAVE_ADDRESS, VCNL4010_REG_ADDR_PROX_RATE, &tx_buff, sizeof(tx_buff));
}

void    vcnl4010_initialize(void) {
    app_twi_init();
}
```

app_twi.c/app_twi.hは省略(202を参照)

## 構成Parts
-

## GitHub
