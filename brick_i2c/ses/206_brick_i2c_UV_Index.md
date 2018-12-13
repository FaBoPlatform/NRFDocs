# #206 UV Index I2C Brick

## Overview



## Connecting

ShinobiとFabo UV Indexを接続。

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
#define NRF_LOG_MODULE_NAME 206_FABO_UV_INDEX
#include "app_error.h"
#include "nrf_delay.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "si1132.h"

NRF_LOG_MODULE_REGISTER();

int main(void) {
    uint16_t    uv_index, als_ir, als_vis;

    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();

    NRF_LOG_INFO("FABO 206 UV INDEX SAMPLE");

    si1132_initialize();
    si1132_set_chlist(SI1132_CHLIST_EN_UV | SI1132_CHLIST_EN_ALS_IR | SI1132_CHLIST_EN_ALS_VIS | SI1132_CHLIST_EN_AUX);
    si1132_set_aux_adcmux(SI1132_AUX_ADCMUX_VOLT);
    si1132_set_autonomous_mode(10000);

    while(1) {
        si1132_measurement(&uv_index, &als_ir, &als_vis);
        NRF_LOG_INFO("UV_INDEX:%d", uv_index);
        NRF_LOG_INFO("ALS_IR  :%d", als_ir);
        NRF_LOG_INFO("ALS_VIS :%d", als_vis);
        NRF_LOG_FLUSH();
    }


}
```

si1132.h
```c
#ifndef _SI1132_H
#define _SI1132_H

#define SI1132_SLAVE_ADDRESS        0x60

#define SI1132_REG_ADDR_PART_ID         0x00
#define SI1132_REG_ADDR_REV_ID          0x01
#define SI1132_REG_ADDR_SEQ_ID          0x02
#define SI1132_REG_ADDR_INT_CFG         0x03
#define SI1132_REG_ADDR_IRQ_ENABLE      0x04
#define SI1132_REG_ADDR_HW_KEY          0x07
#define SI1132_REG_ADDR_MEAS_RATE0      0x08
#define SI1132_REG_ADDR_MEAS_RATE1      0x09
#define SI1132_REG_ADDR_UCOEF0          0x13
#define SI1132_REG_ADDR_UCOEF1          0x14
#define SI1132_REG_ADDR_UCOEF2          0x15
#define SI1132_REG_ADDR_UCOEF3          0x16
#define SI1132_REG_ADDR_PARAM_WR        0x17
#define SI1132_REG_ADDR_COMMAND         0x18
#define SI1132_REG_ADDR_RESPONSE        0x20
#define SI1132_REG_ADDR_IRQ_STATUS      0x21
#define SI1132_REG_ADDR_ALS_VIS_DATA0   0x22
#define SI1132_REG_ADDR_ALS_VIS_DATA1   0x23
#define SI1132_REG_ADDR_ALS_IR_DATA0    0x24
#define SI1132_REG_ADDR_ALS_IR_DATA1    0x25
#define SI1132_REG_ADDR_AUX_DATA0       0x2C
#define SI1132_REG_ADDR_UVINDEX0        0x2C
#define SI1132_REG_ADDR_AUX_DATA1       0x2D
#define SI1132_REG_ADDR_UVINDEX1        0x2D
#define SI1132_REG_ADDR_PARAM_RD        0x2E
#define SI1132_REG_ADDR_CHIP_STAT       0x2F
#define SI1132_REG_ADDR_ANA_IN_KEY      0x3B

#define SI1132_CMD_PARAM_QUERY          0b10000000
#define SI1132_CMD_PARAM_SET            0b10100000
#define SI1132_CMD_NOP                  0b00000000
#define SI1132_CMD_RESET                0b00000001
#define SI1132_CMD_BUSADDR              0b00000010
#define SI1132_CMD_GET_CAL              0b00010010
#define SI1132_CMD_ALS_FORCE            0b00000110
#define SI1132_CMD_ALS_PAUSE            0b00001010
#define SI1132_CMD_ALS_AUTO             0b00001110

#define SI1132_RAM_ADDR_I2C_ADDR            0x00
#define SI1132_RAM_ADDR_CHLIST              0x01
#define SI1132_RAM_ADDR_ALS_ENCODING        0x06
#define SI1132_RAM_ADDR_ALS_IR_ADCMUX       0x0E
#define SI1132_RAM_ADDR_AUX_ADCMUX          0x0F
#define SI1132_RAM_ADDR_ALS_VIS_ADC_COUNTER 0x10
#define SI1132_RAM_ADDR_ALS_VIS_ADC_GAIN    0x11
#define SI1132_RAM_ADDR_ALS_VIS_ADC_MISC    0x12
#define SI1132_RAM_ADDR_ALS_IR_ADC_COUNTER  0x1D
#define SI1132_RAM_ADDR_ALS_IR_ADC_GAIN     0x1E
#define SI1132_RAM_ADDR_ALS_IR_ADC_MISC     0x1F

#define SI1132_CHLIST_EN_UV         0x80
#define SI1132_CHLIST_EN_AUX        0x40
#define SI1132_CHLIST_EN_ALS_IR     0x20
#define SI1132_CHLIST_EN_ALS_VIS    0x10

#define SI1132_AUX_ADCMUX_TEMP  0x65
#define SI1132_AUX_ADCMUX_VOLT  0x75

#define SI1132_RESPONSE_ERR_CHK_BIT 0x80
#define SI1132_RESPONSE_CMD_CTR_MSK 0x0f
#define SI1132_MEAS_PER_DUR_BASE    33

void    si1132_initialize(void);
void    si1132_set_chlist(uint8_t);
void    si1132_set_autonomous_mode(uint16_t);
void    si1132_set_aux_adcmux(uint8_t);
void    si1132_measurement(uint16_t*, uint16_t*, uint16_t*);

#endif
```

si1132.c
```c
#define NRF_LOG_MODULE_NAME SI1132
#include "app_error.h"
#include "nrf_delay.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "si1132.h"
#include "app_twi.h"

static uint8_t          si1132_channel_list     = 0;
static uint8_t          si1132_command_counter  = 0;
static uint16_t         si1132_measurement_rate = 0;
static bool             si1132_autonomous_mode  = false;

static void si1132_reset(void);
static void si1132_ram_rx(uint8_t, uint8_t*);
static void si1132_chk_response(void);

NRF_LOG_MODULE_REGISTER();

void    si1132_initialize(void) {
    app_twi_init();
}

void    si1132_reset(void) {
    uint8_t tx_buff = SI1132_CMD_RESET;

    app_twi_tx_func(SI1132_SLAVE_ADDRESS, SI1132_REG_ADDR_COMMAND, &tx_buff, sizeof(tx_buff));
}

void    si1132_ram_rx(uint8_t address, uint8_t* data) {
    uint8_t rx_buff;
    uint8_t tx_buff = SI1132_CMD_PARAM_QUERY | address;

    app_twi_tx_func(SI1132_SLAVE_ADDRESS, SI1132_REG_ADDR_COMMAND, &tx_buff, sizeof(tx_buff));

    si1132_chk_response();

    app_twi_rx_func(SI1132_SLAVE_ADDRESS, SI1132_REG_ADDR_PARAM_RD, &rx_buff, sizeof(rx_buff));

    *data = rx_buff;
}

void    si1132_set_chlist(uint8_t chlist) {
    uint8_t tx_buf[2] = { chlist, SI1132_CMD_PARAM_SET | SI1132_RAM_ADDR_CHLIST };    

    si1132_channel_list = chlist;

    app_twi_tx_func(SI1132_SLAVE_ADDRESS, SI1132_REG_ADDR_PARAM_WR, tx_buf, sizeof(tx_buf));

    si1132_chk_response();
}

void    si1132_chk_response(void) {
    uint8_t rx_buff;
    uint8_t counter;

    do {
        app_twi_rx_func(SI1132_SLAVE_ADDRESS, SI1132_REG_ADDR_RESPONSE, &rx_buff, sizeof(rx_buff));
        if((rx_buff & SI1132_RESPONSE_ERR_CHK_BIT) == SI1132_RESPONSE_ERR_CHK_BIT) {
            while(true);
        }
        counter = rx_buff & SI1132_RESPONSE_CMD_CTR_MSK;
    } while(counter == si1132_command_counter);

    si1132_command_counter = counter;

    NRF_LOG_DEBUG("command counter value : %d", si1132_command_counter);
}

void    si1132_set_meas_rate(
    uint16_t meas_rate
){
    uint8_t tx_buff[2] = { meas_rate & 0xff, (meas_rate & 0xff00) >> 8 };

    app_twi_tx_func(SI1132_SLAVE_ADDRESS, SI1132_REG_ADDR_MEAS_RATE0, tx_buff, sizeof(tx_buff));

    si1132_chk_response();
}

void    si1132_set_autonomous_mode(uint16_t meas_rate) {
    uint8_t tx_buff = SI1132_CMD_ALS_AUTO;

    si1132_autonomous_mode = true;
    si1132_measurement_rate = meas_rate;

    si1132_set_meas_rate(meas_rate);

    app_twi_tx_func(SI1132_SLAVE_ADDRESS, SI1132_REG_ADDR_COMMAND, &tx_buff, sizeof(tx_buff));

    si1132_chk_response();
}

void    si1132_measurement(uint16_t* a_uv_index, uint16_t* a_als_ir, uint16_t* a_als_vis) {
    uint8_t     rx_buff[2];

    if(si1132_autonomous_mode) {
        nrf_delay_us(si1132_measurement_rate * SI1132_MEAS_PER_DUR_BASE);
        if((si1132_channel_list & SI1132_CHLIST_EN_UV) == SI1132_CHLIST_EN_UV) {
            app_twi_rx_func(SI1132_SLAVE_ADDRESS, SI1132_REG_ADDR_UVINDEX0, rx_buff, sizeof(rx_buff));
            *a_uv_index = rx_buff[0] + (rx_buff[1] << 8);
        }
        if((si1132_channel_list & SI1132_CHLIST_EN_ALS_IR) == SI1132_CHLIST_EN_ALS_IR) {
            app_twi_rx_func(SI1132_SLAVE_ADDRESS, SI1132_REG_ADDR_ALS_IR_DATA0, rx_buff, sizeof(rx_buff));
            *a_als_ir = rx_buff[0] + (rx_buff[1] << 8);
        }
        if((si1132_channel_list & SI1132_CHLIST_EN_ALS_VIS) == SI1132_CHLIST_EN_ALS_VIS) {
            app_twi_rx_func(SI1132_SLAVE_ADDRESS, SI1132_REG_ADDR_ALS_VIS_DATA0, rx_buff, sizeof(rx_buff));
            *a_als_vis = rx_buff[0] + (rx_buff[1] << 8);
        }
    }
}

void    si1132_set_aux_adcmux(uint8_t aux_adcmux) {
    uint8_t tx_buff[2] = { aux_adcmux, SI1132_CMD_PARAM_SET | SI1132_RAM_ADDR_AUX_ADCMUX };

    app_twi_tx_func(SI1132_SLAVE_ADDRESS, SI1132_REG_ADDR_PARAM_WR, tx_buff, sizeof(tx_buff));

    si1132_chk_response();
}
```

app_twi.c/app_twi.hは省略(202を参照)

## 構成Parts
-

## GitHub
