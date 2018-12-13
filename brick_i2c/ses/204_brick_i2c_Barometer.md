# #204 Barometer I2C Brick

## Overview



## Connecting

ShinobiとFabo Barometerを接続。

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
#define NRF_LOG_MODULE_NAME FABO_204_BAROMETER
#include "app_error.h"
#include "nrf_delay.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "mpl115a2.h"

NRF_LOG_MODULE_REGISTER();

void main(void) {
    float   hpa = 0;
    float   temp = 0;

    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();

    NRF_LOG_INFO("FABO 204 BAROMETER SAMPLE");

    mpl115a2_initialize();
    while(1) {
        mpl115a2_measurement(200.0, &hpa, &temp);
        NRF_LOG_INFO("hpa  :" NRF_LOG_FLOAT_MARKER, NRF_LOG_FLOAT(hpa));
        NRF_LOG_INFO("temp :" NRF_LOG_FLOAT_MARKER, NRF_LOG_FLOAT(temp));
        NRF_LOG_FLUSH();
        nrf_delay_ms(1000);
    }
}
```

mpl115a2.h
```c
#ifndef _MPL115A2_H
#define _MPL115A2_H

#define MPL115A2_SLAVE_ADDRESS  0x60

#define MPL115A2_PADC_MSB       0x00
#define MPL115A2_PADC_LSB       0x01
#define MPL115A2_TADC_MSB       0x02
#define MPL115A2_TACD_LSB       0x03
#define MPL115A2_A0_MSB         0x04
#define MPL115A2_A0_LSB         0x05
#define MPL115A2_B1_MSB         0x06
#define MPL115A2_B1_LSB         0x07
#define MPL115A2_B2_MSB         0x08
#define MPL115A2_B2_LSB         0x09
#define MPL115A2_C12_MSB        0x0A
#define MPL115A2_C12_LSB        0x0B
#define MPL115A2_CONVERT        0x12

void    mpl115a2_initialize(void);
void    mpl115a2_measurement(float, float*, float*);

#endif
```

mpl115a2.c
```c
#define NRF_LOG_MODULE_NAME MPL115A2
#include "app_error.h"
#include "nrf_delay.h"
#include "nrf_log.h"
#include "mpl115a2.h"
#include "app_twi.h"

static float            mpl115a2_coef_a0;
static float            mpl115a2_coef_b1;
static float            mpl115a2_coef_b2;
static float            mpl115a2_coef_c12;
NRF_LOG_MODULE_REGISTER();

void    mpl115a2_measurement_internal(float* hpa, float* temp) {
    uint8_t     reg[2] = { MPL115A2_CONVERT, 0x00 };
    uint8_t     address = MPL115A2_PADC_MSB;
    uint8_t     measurement_data[4];
    uint16_t    padc, tadc;
    float       pcomp;

    uint8_t tx_buff = 0x00;
    uint8_t rx_buff[4];

    app_twi_tx_func(MPL115A2_SLAVE_ADDRESS, MPL115A2_CONVERT, &tx_buff, sizeof(tx_buff));

    nrf_delay_ms(3);

    app_twi_rx_func(MPL115A2_SLAVE_ADDRESS, MPL115A2_PADC_MSB, rx_buff, sizeof(rx_buff));

    padc = (((uint16_t)rx_buff[0] << 8) | rx_buff[1]) >> 6;
    tadc = (((uint16_t)rx_buff[2] << 8) | rx_buff[3]) >> 6;

    pcomp = (mpl115a2_coef_a0 + ((mpl115a2_coef_b1 + (mpl115a2_coef_c12 * tadc)) * padc)) + (mpl115a2_coef_b2 * tadc);

    *hpa  = pcomp * ((115.0-50.0)/1023.0) + 50.0;
    *temp = 25.0 - ((float)tadc - 512.0 ) / 5.35;     
}

void    mpl115a2_measurement(float altitude, float* a_hpa, float* a_temp) {
    float   hpa, temp;
    mpl115a2_measurement_internal(&hpa, &temp);
    *a_hpa = hpa / pow(1.0 - (altitude/44330.0), 5.255) * 10;
    *a_temp = temp;
}

void    read_coef(void) {
    uint8_t rx_buff[8];
    uint8_t address = MPL115A2_A0_MSB;
    uint8_t read_coef_data[8];
    int16_t coef_data, coef_num_part, coef_dec_part;
    uint16_t sign_bit;

    app_twi_rx_func(MPL115A2_SLAVE_ADDRESS, MPL115A2_A0_MSB, rx_buff, sizeof(rx_buff));

    coef_data = ((uint16_t)rx_buff[0] << 8) | rx_buff[1];
    sign_bit = coef_data & 0x8000;
    coef_num_part = (coef_data & 0x7ff8) >> 3;
    coef_dec_part = (coef_data & 0x0007) | sign_bit;
    mpl115a2_coef_a0 = (float)coef_dec_part / (float)((long)1 << 3) + (float)coef_num_part;

    coef_data = ((uint16_t)rx_buff[2] << 8) | rx_buff[3];
    sign_bit = coef_data & 0x8000;
    coef_num_part = (coef_data & 0x6000) >> 13;
    coef_dec_part = (coef_data & 0x1fff) | sign_bit;
    mpl115a2_coef_b1 = (float)coef_dec_part / (float)((long)1 << 13) + (float)coef_num_part;

    coef_data = ((uint16_t)rx_buff[4] << 8) | rx_buff[5];
    sign_bit = coef_data & 0x8000;
    coef_num_part = (coef_data & 0x4000) >> 14;
    coef_dec_part = (coef_data & 0x3fff) | sign_bit;
    mpl115a2_coef_b2 = (float)coef_dec_part / (float)((long)1 << 14) + (float)coef_num_part;

    coef_data = ((uint16_t)rx_buff[6] << 8) | rx_buff[7];
    sign_bit = coef_data & 0x8000;
    coef_num_part = 0;
    coef_dec_part = ((coef_data & 0x7ffc) >> 2) | sign_bit;
    mpl115a2_coef_c12 = (float)coef_dec_part / (float)((long)1 << 22) + (float)coef_num_part;

    NRF_LOG_HEXDUMP_DEBUG(read_coef_data, sizeof(read_coef_data));
    NRF_LOG_DEBUG("mpl115a2_coef_a0  :" NRF_LOG_FLOAT_MARKER, NRF_LOG_FLOAT(mpl115a2_coef_a0));
    NRF_LOG_DEBUG("mpl115a2_coef_b1  :" NRF_LOG_FLOAT_MARKER, NRF_LOG_FLOAT(mpl115a2_coef_b1));
    NRF_LOG_DEBUG("mpl115a2_coef_b2  :" NRF_LOG_FLOAT_MARKER, NRF_LOG_FLOAT(mpl115a2_coef_b2));
    NRF_LOG_DEBUG("mpl115a2_coef_c12 :" NRF_LOG_FLOAT_MARKER, NRF_LOG_FLOAT(mpl115a2_coef_c12));
}

void    mpl115a2_initialize(void) {
    app_twi_init();

    read_coef();
}
```

app_twi.c/app_twi.hは省略(202を参照)

## 構成Parts
-

## GitHub
