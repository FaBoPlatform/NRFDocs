# #207 Temperature I2C Brick

## Overview



## Connecting

ShinobiとFabo Temperatureを接続。

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
#define NRF_LOG_MODULE_NAME FABO_206_TEMPERATURE
#include "app_error.h"
#include "nrf_delay.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "adt7410.h"

NRF_LOG_MODULE_REGISTER();

int main(void) {
    int16_t pos_temp, neg_temp;

    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();

    NRF_LOG_INFO("FABO 207 Temperature Sample");

    adt7410_initialize();
    adt7410_set_ope_mode(ADT7410_OPE_MODE_CONT_CONV);
    adt7410_set_res_mode(ADT7410_RES_MODE_16);

    while(true) {
        adt7410_measurement(&pos_temp, &neg_temp);
        NRF_LOG_INFO("positive temperature:%d", pos_temp);
        NRF_LOG_INFO("negative temperature:%d", neg_temp);
        NRF_LOG_FLUSH();
        nrf_delay_ms(500);
    }    
}
```

adt7410.h
```c
#ifndef _ADT7410_H
#define _ADT7410_H

#define ADT7410_SLAVE_ADDRESS   0x48

#define ADT7410_REG_ADDR_TEMP_MSB   0x00
#define ADT7410_REG_ADDR_TEMP_LSB   0x01
#define ADT7410_REG_ADDR_STATUS     0x02
#define ADT7410_REG_ADDR_CONFIG     0x03
#define ADT7410_REG_ADDR_TH_MSB     0x04
#define ADT7410_REG_ADDR_TH_LSB     0x05
#define ADT7410_REG_ADDR_TL_MSB     0x06
#define ADT7410_REG_ADDR_TL_LSB     0x07
#define ADT7410_REG_ADDR_TC_MSB     0x08
#define ADT7410_REG_ADDR_TC_LSB     0x09
#define ADT7410_REG_ADDR_THST       0x0A
#define ADT7410_REG_ADDR_ID         0x0B
#define ADT7410_REG_ADDR_RESET      0x2F

#define ADT7410_OPE_MODE_CONT_CONV  0x00
#define ADT7410_OPE_MODE_ONE_SHOT   0x20
#define ADT7410_OPE_MODE_1SPS       0x40
#define ADT7410_OPE_MODE_SHUTDOWN   0x60

#define ADT7410_RES_MODE_13 0b00000000
#define ADT7410_RES_MODE_16 0b10000000

void    adt7410_initialize(void);
void    adt7410_set_ope_mode(uint8_t);
void    adt7410_set_res_mode(uint8_t);
void    adt7410_measurement(int16_t*, int16_t*);

#endif
```

adt7410.c
```c
#define NRF_LOG_MODULE_NAME ADT7410
#include "app_error.h"
#include "nrf_delay.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "adt7410.h"
#include "app_twi.h"

static uint8_t          adt7410_ope_mode        = ADT7410_OPE_MODE_CONT_CONV;
static uint8_t          adt7410_res_mode        = ADT7410_RES_MODE_13;
NRF_LOG_MODULE_REGISTER();

void    adt7410_initialize(void) {
    app_twi_init();
}

void    adt7410_set_ope_mode(uint8_t mode) {
    uint8_t rx_buff;
    uint8_t tx_buff;

    adt7410_ope_mode = mode;

    app_twi_rx_func(ADT7410_SLAVE_ADDRESS, ADT7410_REG_ADDR_CONFIG, &tx_buff, sizeof(tx_buff));
    tx_buff = (tx_buff & 0x9F) | adt7410_ope_mode;
    app_twi_tx_func(ADT7410_SLAVE_ADDRESS, ADT7410_REG_ADDR_CONFIG, &tx_buff, sizeof(tx_buff));
}

void    adt7410_set_res_mode(uint8_t mode) {
    uint8_t rx_buff;
    uint8_t tx_buff;

    adt7410_res_mode = mode;

    app_twi_rx_func(ADT7410_SLAVE_ADDRESS, ADT7410_REG_ADDR_CONFIG, &rx_buff, sizeof(rx_buff));
    tx_buff = (rx_buff & 0x7F) | adt7410_res_mode;
    app_twi_tx_func(ADT7410_SLAVE_ADDRESS, ADT7410_REG_ADDR_CONFIG, &tx_buff, sizeof(tx_buff));
}

void    adt7410_measurement(int16_t* a_pos_temp, int16_t* a_neg_temp) {
    uint8_t rx_buff[2];
    int16_t temp;
    int16_t sign_bit;

    NRF_LOG_DEBUG("operation mode:%x", adt7410_ope_mode);
    if(adt7410_ope_mode == ADT7410_OPE_MODE_CONT_CONV) {
        nrf_delay_ms(240);
    }

    app_twi_rx_func(ADT7410_SLAVE_ADDRESS, ADT7410_REG_ADDR_TEMP_MSB, rx_buff, sizeof(rx_buff));
    temp = (rx_buff[0] << 8) | rx_buff[1];

    NRF_LOG_DEBUG("resolution:%x", adt7410_res_mode);
    if(adt7410_res_mode == ADT7410_RES_MODE_13) {
        sign_bit = temp & 0x8000;
        temp &= 0x7fff;
        temp = temp >> 3;
        temp |= sign_bit;
        *a_pos_temp = temp / 16;
        *a_neg_temp = (temp - 8196) / 16;
    } else {
        *a_pos_temp = temp / 128;
        *a_neg_temp = (temp - 65536) / 128;
    }
}
```

app_twi.c/app_twi.hは省略(202を参照)

## 構成Parts
-

## GitHub
