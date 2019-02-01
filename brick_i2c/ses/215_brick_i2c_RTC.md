# #215 RTC I2C Brick

## Overview



## Connecting

ShinobiとFabo 215 RTCを接続。

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

## SAMPLE CODE
pcf2129.h
```c
#ifndef _PCF2129_H
#define _PCF2129_H

#include <stdint.h>

#define PCF2129_WD_SUN  0x00
#define PCF2129_WD_MON  0x01
#define PCF2129_WD_TUE  0x02
#define PCF2129_WD_WED  0x03
#define PCF2129_WD_THU  0x04
#define PCF2129_WD_FRI  0x05
#define PCF2129_WD_SAT  0x06

#define PCF2129_MON_JAN 0x01
#define PCF2129_MON_FEB 0x02
#define PCF2129_MON_MAR 0x03
#define PCF2129_MON_APR 0x04
#define PCF2129_MON_MAY 0x05
#define PCF2129_MON_JUN 0x06
#define PCF2129_MON_JUL 0x07
#define PCF2129_MON_AUG 0x08
#define PCF2129_MON_SEP 0x09
#define PCF2129_MON_OCT 0x10
#define PCF2129_MON_DEC 0x11
#define PCF2129_MON_NOV 0x12

typedef struct {
     uint8_t    year;
     uint8_t    month;
     uint8_t    day;
     uint8_t    week_day;
     bool       ampm;
     uint8_t    hour;
     uint8_t    min;
     uint8_t    sec;
} pcf2129_time_t;

void    pcf2129_initialize(void);
void    pcf2129_set_time(pcf2129_time_t*);
void    pcf2129_get_time(pcf2129_time_t*);
```

pcf2129.c
```c
#define NRF_LOG_MODULE_NAME PCF2129
#define NRF_LOG_DEFAULT_LEVEL   3

#include "nrf_delay.h"
#include "pcf2129.h"
#include "app_log.h"
#include "app_twi.h"

#define PCF2129_SLAVE_ADDRESS   0x51

#define PCF2129_REG_ADDR_CTRL1          0x00
#define PCF2129_REG_ADDR_CTRL2          0x01
#define PCF2129_REG_ADDR_CTRL3          0x02
#define PCF2129_REG_ADDR_SEC            0x03
#define PCF2129_REG_ADDR_MIN            0x04
#define PCF2129_REG_ADDR_HOUR           0x05
#define PCF2129_REG_ADDR_DAY            0x06
#define PCF2129_REG_ADDR_WKDAY          0x07
#define PCF2129_REG_ADDR_MONTH          0x08
#define PCF2129_REG_ADDR_YEAR           0x09
#define PCF2129_REG_ADDR_ALM_SEC        0x0A
#define PCF2129_REG_ADDR_ALM_MIN        0x0B
#define PCF2129_REG_ADDR_ALM_HOUR       0x0C
#define PCF2129_REG_ADDR_ALM_DAY        0x0D
#define PCF2129_REG_ADDR_ALM_WKDAY      0x0E
#define PCF2129_REG_ADDR_CLKOUT_CTRL    0x0F
#define PCF2129_REG_ADDR_WDT_TIM_CTRL   0x10
#define PCF2129_REG_ADDR_WDT_TIM_VAL    0x11
#define PCF2129_REG_ADDR_TMSTP_CTRL     0x12
#define PCF2129_REG_ADDR_TMSTP_SEC      0x13
#define PCF2129_REG_ADDR_TMSTP_MIN      0x14
#define PCF2129_REG_ADDR_TMSTP_HOUR     0x15
#define PCF2129_REG_ADDR_TMSTP_DAY      0x16
#define PCF2129_REG_ADDR_TMSTP_MONTH    0x17
#define PCF2129_REG_ADDR_TMSTP_YEAR     0x18
#define PCF2129_REG_ADDR_AGING_OFFSET   0x19

#define PCF2129_CTRL1_EXT_TEST  0x80
#define PCF2129_CTRL1_STOP      0x20
#define PCF2129_CTRL1_TSF       0x10
#define PCF2129_CTRL1_POR_OVRD  0x08
#define PCF2129_CTRL1_12_24     0x04
#define PCF2129_CTRL1_MI        0x02
#define PCF2129_CTRL1_SI        0x01

#define PCF2129_HOUR_AMPM       0x20

#define PCF2129_RX_SIZE_TIME    7
#define PCF2129_TX_SIZE_TIME    7

NRF_LOG_MODULE_REGISTER();

static uint8_t  pcf2129_reg_ctrl1;
static uint8_t  pcf2129_reg_ctrl2;
static uint8_t  pcf2129_reg_ctrl3;

typedef enum {
    RTC_OFF, RTC_ON
} E_RTC_STATE;

static uint8_t dec_bcddec(
    uint8_t data
) {
    return ((data & 0xf0) >> 4) * 10 + (data & 0x0f);
}

static uint8_t  enc_decbcd(
    uint8_t data
) {
    app_log_func_start();

    NRF_LOG_DEBUG("dec = %d", data);
    NRF_LOG_DEBUG("bcd = %x", ((data / 10) << 4) | (data % 10));

    app_log_func_end();

    return ((data / 10) << 4) | (data % 10);
}

static void pcf2129_set_rtc_clock_state(
    E_RTC_STATE state
) {
    if(state == RTC_ON) {
        pcf2129_reg_ctrl1 &= ~(PCF2129_CTRL1_STOP);
    } else {
        pcf2129_reg_ctrl1 |= PCF2129_CTRL1_STOP;
    }

    app_twi_tx(PCF2129_SLAVE_ADDRESS, PCF2129_REG_ADDR_CTRL1, &pcf2129_reg_ctrl1, sizeof(pcf2129_reg_ctrl1), true);

}

void    pcf2129_set_time(
    pcf2129_time_t* time
) {
    uint8_t tx_data[PCF2129_TX_SIZE_TIME];

    app_log_func_start();

    tx_data[0] = enc_decbcd(time->sec);
    tx_data[1] = enc_decbcd(time->min);
    tx_data[2] = enc_decbcd(time->hour);
    if(time->ampm) {
        tx_data[2] |= PCF2129_HOUR_AMPM;
    }
    tx_data[3] = enc_decbcd(time->day);
    tx_data[4] = time->week_day;
    tx_data[5] = time->month;
    tx_data[6] = enc_decbcd(time->year);

    NRF_LOG_HEXDUMP_INFO(tx_data, sizeof(tx_data));

    //pcf2129_set_rtc_clock_state(RTC_OFF);

    app_twi_tx(PCF2129_SLAVE_ADDRESS, PCF2129_REG_ADDR_SEC, tx_data, sizeof(tx_data), true);

    //pcf2129_set_rtc_clock_state(RTC_ON);

    app_log_func_end();
}

void    pcf2129_get_time(
    pcf2129_time_t* time
) {
    uint8_t rx_data[PCF2129_RX_SIZE_TIME];

    app_log_func_start();

    memset(time, 0x00, sizeof(pcf2129_time_t));

    app_twi_rx(PCF2129_SLAVE_ADDRESS, PCF2129_REG_ADDR_SEC, rx_data, sizeof(rx_data), true);

    NRF_LOG_HEXDUMP_INFO(rx_data, sizeof(rx_data));

    time->sec = dec_bcddec(rx_data[0] & 0x7f);
    time->min = dec_bcddec(rx_data[1] & 0x7f);
    if((pcf2129_reg_ctrl1 & PCF2129_CTRL1_12_24) == PCF2129_CTRL1_12_24) {
        time->hour = dec_bcddec(rx_data[2] & 0x1f);
        if((rx_data[2] & PCF2129_HOUR_AMPM) == PCF2129_HOUR_AMPM) {
            time->ampm = true;
        }
    } else {
        time->hour = dec_bcddec(rx_data[2] & 0x3f);
    }
    time->day = dec_bcddec(rx_data[3] & 0x3f);
    time->week_day = dec_bcddec(rx_data[4] & 0x07);
    time->month = dec_bcddec(rx_data[5] & 0x1f);
    time->year = dec_bcddec(rx_data[6]);

    app_log_func_end();
}

void    pcf2129_initialize(
    void
) {
    uint8_t rx_data[3];
    uint8_t tx_data[3] = { 0 };

    app_twi_init();

    app_log_func_start();

    app_twi_tx(PCF2129_SLAVE_ADDRESS, PCF2129_REG_ADDR_CTRL1, tx_data, sizeof(tx_data), true);

    app_twi_rx(PCF2129_SLAVE_ADDRESS, PCF2129_REG_ADDR_CTRL1, rx_data, sizeof(rx_data), true);

    NRF_LOG_HEXDUMP_INFO(rx_data, sizeof(rx_data));

    pcf2129_reg_ctrl1 = rx_data[0];
    pcf2129_reg_ctrl2 = rx_data[1];
    pcf2129_reg_ctrl3 = rx_data[2];

    app_log_func_end();
}
```

main.c
```c
#define NRF_LOG_MODULE_NAME MAIN
#include "app_error.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_delay.h"

#include "app_log.h"
#include "pcf2129.h"

NRF_LOG_MODULE_REGISTER();

void    main(
    void
) {
    pcf2129_time_t  time;

    app_log_init();

    NRF_LOG_INFO("215 RTC");

    APP_ERROR_CHECK(nrf_pwr_mgmt_init());

    pcf2129_initialize();

    time.ampm = false;
    time.year = 19;
    time.month = PCF2129_MON_JAN;
    time.day = 24;
    time.week_day = PCF2129_WD_THU;
    time.hour = 15;
    time.min = 17;
    time.sec = 0;

    //pcf2129_set_time(&time);

    while(true) {
        pcf2129_get_time(&time);

        NRF_LOG_INFO("%02u/%02u/%02u %02u:%02u:%02u", time.year, time.month, time.day, time.hour, time.min, time.sec);

        if(NRF_LOG_PROCESS() == false) {
            nrf_pwr_mgmt_run();
        } else {
            NRF_LOG_FLUSH();
        }
        nrf_delay_ms(1000);
    }
}
```

## 構成Parts
-

## GitHub
