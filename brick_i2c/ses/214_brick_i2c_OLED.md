# #214 OLED I2C Brick

## Overview



## Connecting

ShinobiとFabo 214 OLEDを接続。

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

## ssd1306.h
```c
#ifndef _SSD1306_H
#define _SSD1306_H

#include <stdint.h>

#define SSD1306_DISPLAY_ON  0x01
#define SSD1306_DISPLAY_OFF 0x00
#define SSD1306_DCLK_RESET          0x00
#define SSD1306_OSCLTR_FREQ_RESET   0x80
#define SSD1306_MLTPLX_RATIO_RESET  0x3F
#define SSD1306_DISP_OFS_RESET      0x00
#define SSD1306_DISP_STR_LINE_RESET 0x00
#define SSD1306_CHARGE_PUMP_RESET   0x14
#define SSD1306_SEGMENT_REMAP_RESET 0x00
#define SSD1306_SEGMENT_REMAP       0x01
#define SSD1306_COM_OP_SCAN_DIR_UP      0x00
#define SSD1306_COM_OP_SCAN_DIR_DOWN    0x08
#define SSD1306_COM_PIN_HW_CONF_RESET   0x12
#define SSD1306_CONTRAST_RESET          0xCF
#define SSD1306_PRE_CHARGE_PERIOD_RESET 0xF1
#define SSD1306_VCOMH_DESEL_LVL_RESET   0x40
#define SSD1306_ENTIRE_DISP_ON          0x01
#define SSD1306_ENTIRE_DISP_OFF         0x00
#define SSD1306_NOR_DISPLAY             0x00
#define SSD1306_INV_DISPLAY             0x01

void    ssd1306_init(void);
void    ssd1306_set_display(uint8_t);
void    ssd1306_set_dclk_oscltr_freq(uint8_t);
void    ssd1306_set_multiplex_ratio(uint8_t);
void    ssd1306_set_display_offset(uint8_t);
void    ssd1306_set_display_start_line(uint8_t);
void    ssd1306_set_charge_pump(uint8_t);
void    ssd1306_set_segment_remap(uint8_t);
void    ssd1306_set_com_output_scan_direction(uint8_t);
void    ssd1306_set_com_pin_hardware_control(uint8_t);
void    ssd1306_set_contrast_control(uint8_t);
void    ssd1306_set_pre_charge_period(uint8_t);
void    ssd1306_set_vcomh_deselect_level(uint8_t);
void    ssd1306_set_entire_display(uint8_t);
void    ssd1306_set_normal_inverse_display(uint8_t);
void    ssd1306_clear_display(void);
void    ssd1306_set_page_address(uint8_t);
void    ssd1306_set_column_address(uint8_t);
void    ssd1306_data_write(uint8_t);
```

ssd1306.c
```c
#define NRF_LOG_MODULE_NAME SSD1306
#ifndef APP_LOG_ENABLED
#define NRF_LOG_LEVEL   1
#else
#define NRF_LOG_LEVEL   4
#endif
#include <stdint.h>
#include "nrf_log.h"
#include "nrf_delay.h"
#include "ssd1306.h"
#include "app_log.h"
#include "app_twi.h"

NRF_LOG_MODULE_REGISTER();

#define SSD1306_SLAVE_ADDRESS   0x3C

#define SSD1306_CONT_BIT    0x80
#define SSD1306_DATA_BIT    0x40

#define SSD1306_CMD_SET_DISPLAY             0xAE
#define SSD1306_CMD_SET_DCLK_OSCLTR_FREQ    0xD5
#define SSD1306_CMD_SET_MLTPLX_RATIO        0xA8
#define SSD1306_CMD_SET_DISPLAY_OFFSET      0xD3
#define SSD1306_CMD_SET_DISP_START_LINE     0x40
#define SSD1306_CMD_SET_CHARGE_PUMP         0x8D
#define SSD1306_CMD_SET_SEGMENT_REMAP       0xA0
#define SSD1306_CMD_SET_COM_OP_SCAN_DIR     0xC0
#define SSD1306_CMD_SET_COM_PIN_HW_CONF     0xDA
#define SSD1306_CMD_SET_CONTRAST_CTL        0x81
#define SSD1306_CMD_SET_PRE_CHARGE_PERIOD   0xD9
#define SSD1306_CMD_SET_VCOMH_DESELECT_LVL  0xDB
#define SSD1306_CMD_SET_ENTIRE_DISPLAY      0xA4
#define SSD1306_CMD_SET_NOR_INV_DISPLAY     0xA6
#define SSD1306_CMD_SET_PAGE_ADDRESS        0x22
#define SSD1306_CMD_SET_COLUMN_ADDRESS      0x21

#define SSD1306_PAGE_ADDRESS_MAX    7
#define SSD1306_COLUMN_ADDRESS_MAX  127    

void    ssd1306_init(
    void
) {
    app_log_func_start();

    ssd1306_set_display(SSD1306_DISPLAY_OFF);
    ssd1306_set_dclk_oscltr_freq(SSD1306_DCLK_RESET | SSD1306_OSCLTR_FREQ_RESET);
    ssd1306_set_multiplex_ratio(SSD1306_MLTPLX_RATIO_RESET);
    ssd1306_set_display_offset(SSD1306_DISP_OFS_RESET);
    ssd1306_set_display_start_line(SSD1306_DISP_STR_LINE_RESET);
    ssd1306_set_charge_pump(SSD1306_CHARGE_PUMP_RESET);
    ssd1306_set_segment_remap(SSD1306_SEGMENT_REMAP);
    ssd1306_set_com_output_scan_direction(SSD1306_COM_OP_SCAN_DIR_DOWN);
    ssd1306_set_com_pin_hardware_control(SSD1306_COM_PIN_HW_CONF_RESET);
    ssd1306_set_contrast_control(SSD1306_CONTRAST_RESET);
    ssd1306_set_pre_charge_period(SSD1306_PRE_CHARGE_PERIOD_RESET);
    ssd1306_set_vcomh_deselect_level(SSD1306_VCOMH_DESEL_LVL_RESET);
    ssd1306_set_entire_display(SSD1306_ENTIRE_DISP_OFF);
    ssd1306_set_normal_inverse_display(SSD1306_NOR_DISPLAY);
    ssd1306_clear_display();
    ssd1306_set_display(SSD1306_DISPLAY_ON);

    nrf_delay_ms(100);

    app_log_func_end();
}

void    ssd1306_data_write(
    uint8_t data
) {
    uint8_t tx_data[2];

    app_log_func_start();

    tx_data[0] = SSD1306_DATA_BIT;
    tx_data[1] = data;

    app_twi_tx(SSD1306_SLAVE_ADDRESS, 0, tx_data, sizeof(tx_data), false);

    app_log_func_end();
}

void    ssd1306_set_column_address(
    uint8_t data
) {
    uint8_t tx_data[4];

    app_log_func_start();

    tx_data[0] = SSD1306_CONT_BIT;
    tx_data[1] = SSD1306_CMD_SET_COLUMN_ADDRESS;
    tx_data[2] = 0;
    tx_data[3] = data;

    app_twi_tx(SSD1306_SLAVE_ADDRESS, 0, tx_data, sizeof(tx_data), false);

    app_log_func_end();
}

void    ssd1306_set_page_address(
    uint8_t data
) {
    uint8_t tx_data[4];

    app_log_func_start();

    tx_data[0] = SSD1306_CONT_BIT;
    tx_data[1] = SSD1306_CMD_SET_PAGE_ADDRESS;
    tx_data[2] = 0;
    tx_data[3] = data;

    app_twi_tx(SSD1306_SLAVE_ADDRESS, 0, tx_data, sizeof(tx_data), false);

    app_log_func_end();
}

void    ssd1306_clear_display(
    void
) {
    app_log_func_start();

    for(uint32_t i = 0; i <= SSD1306_PAGE_ADDRESS_MAX; i++) {
        ssd1306_set_page_address(i);
        ssd1306_set_column_address(0);
        for(uint32_t j = 0; j <= SSD1306_COLUMN_ADDRESS_MAX; j++) {
            ssd1306_data_write(0);
        }
    }

    app_log_func_end();
}

void    ssd1306_set_normal_inverse_display(
    uint8_t data
) {    
    uint8_t tx_data[2];

    app_log_func_start();

    tx_data[0] = 0;
    tx_data[1] = SSD1306_CMD_SET_NOR_INV_DISPLAY | data;

    app_twi_tx(SSD1306_SLAVE_ADDRESS, 0, tx_data, sizeof(tx_data), false);

    nrf_delay_ms(100);

    app_log_func_end();
}

void    ssd1306_set_entire_display(
    uint8_t data
) {    
    uint8_t tx_data[2];

    app_log_func_start();

    tx_data[0] = 0;
    tx_data[1] = SSD1306_CMD_SET_ENTIRE_DISPLAY | data;

    app_twi_tx(SSD1306_SLAVE_ADDRESS, 0, tx_data, sizeof(tx_data), false);

    nrf_delay_ms(100);

    app_log_func_end();
}

void    ssd1306_set_vcomh_deselect_level(
    uint8_t data
) {    
    uint8_t tx_data[4];

    app_log_func_start();

    tx_data[0] = SSD1306_CONT_BIT;
    tx_data[1] = SSD1306_CMD_SET_VCOMH_DESELECT_LVL;
    tx_data[2] = 0;
    tx_data[3] = data;

    app_twi_tx(SSD1306_SLAVE_ADDRESS, 0, tx_data, sizeof(tx_data), false);

    nrf_delay_ms(100);

    app_log_func_end();
}

void    ssd1306_set_pre_charge_period(
    uint8_t data
) {    
    uint8_t tx_data[4];

    app_log_func_start();

    tx_data[0] = SSD1306_CONT_BIT;
    tx_data[1] = SSD1306_CMD_SET_PRE_CHARGE_PERIOD;
    tx_data[2] = 0;
    tx_data[3] = data;

    app_twi_tx(SSD1306_SLAVE_ADDRESS, 0, tx_data, sizeof(tx_data), false);

    nrf_delay_ms(100);

    app_log_func_end();
}

void    ssd1306_set_contrast_control(
    uint8_t data
) {    
    uint8_t tx_data[4];

    app_log_func_start();

    tx_data[0] = SSD1306_CONT_BIT;
    tx_data[1] = SSD1306_CMD_SET_CONTRAST_CTL;
    tx_data[2] = 0;
    tx_data[3] = data;

    app_twi_tx(SSD1306_SLAVE_ADDRESS, 0, tx_data, sizeof(tx_data), false);

    nrf_delay_ms(100);

    app_log_func_end();
}

void    ssd1306_set_com_pin_hardware_control(
    uint8_t data
) {    
    uint8_t tx_data[4];

    app_log_func_start();

    tx_data[0] = SSD1306_CONT_BIT;
    tx_data[1] = SSD1306_CMD_SET_COM_PIN_HW_CONF;
    tx_data[2] = 0;
    tx_data[3] = data;

    app_twi_tx(SSD1306_SLAVE_ADDRESS, 0, tx_data, sizeof(tx_data), false);

    nrf_delay_ms(100);

    app_log_func_end();
}

void    ssd1306_set_com_output_scan_direction(
    uint8_t data
) {    
    uint8_t tx_data[2];

    app_log_func_start();

    tx_data[0] = 0;
    tx_data[1] = SSD1306_CMD_SET_COM_OP_SCAN_DIR | data;

    app_twi_tx(SSD1306_SLAVE_ADDRESS, 0, tx_data, sizeof(tx_data), false);

    nrf_delay_ms(100);

    app_log_func_end();
}

void    ssd1306_set_segment_remap(
    uint8_t data
) {    
    uint8_t tx_data[2];

    app_log_func_start();

    tx_data[0] = 0;
    tx_data[1] = SSD1306_CMD_SET_SEGMENT_REMAP | data;

    app_twi_tx(SSD1306_SLAVE_ADDRESS, 0, tx_data, sizeof(tx_data), false);

    nrf_delay_ms(100);

    app_log_func_end();
}

void    ssd1306_set_charge_pump(
    uint8_t data
) {    
    uint8_t tx_data[4];

    app_log_func_start();

    tx_data[0] = SSD1306_CONT_BIT;
    tx_data[1] = SSD1306_CMD_SET_CHARGE_PUMP;
    tx_data[2] = 0;
    tx_data[3] = data;

    app_twi_tx(SSD1306_SLAVE_ADDRESS, 0, tx_data, sizeof(tx_data), false);

    nrf_delay_ms(100);

    app_log_func_end();
}

void    ssd1306_set_display_start_line(
    uint8_t data
) {    
    uint8_t tx_data[2];

    app_log_func_start();

    tx_data[0] = 0;
    tx_data[1] = SSD1306_CMD_SET_DISP_START_LINE | data;

    app_twi_tx(SSD1306_SLAVE_ADDRESS, 0, tx_data, sizeof(tx_data), false);

    nrf_delay_ms(100);

    app_log_func_end();
}

void    ssd1306_set_display_offset(
    uint8_t data
) {    
    uint8_t tx_data[4];

    app_log_func_start();

    tx_data[0] = SSD1306_CONT_BIT;
    tx_data[1] = SSD1306_CMD_SET_DISPLAY_OFFSET;
    tx_data[2] = 0;
    tx_data[3] = data;

    app_twi_tx(SSD1306_SLAVE_ADDRESS, 0, tx_data, sizeof(tx_data), false);

    nrf_delay_ms(100);

    app_log_func_end();
}

void    ssd1306_set_multiplex_ratio(
    uint8_t data
) {
    uint8_t tx_data[4];

    app_log_func_start();

    tx_data[0] = SSD1306_CONT_BIT;
    tx_data[1] = SSD1306_CMD_SET_MLTPLX_RATIO;
    tx_data[2] = 0;
    tx_data[3] = data;

    app_twi_tx(SSD1306_SLAVE_ADDRESS, 0, tx_data, sizeof(tx_data), false);

    nrf_delay_ms(100);

    app_log_func_end();
}

void    ssd1306_set_dclk_oscltr_freq(
    uint8_t data
) {
    uint8_t tx_data[4];

    app_log_func_start();

    tx_data[0] = SSD1306_CONT_BIT;
    tx_data[1] = SSD1306_CMD_SET_DCLK_OSCLTR_FREQ;
    tx_data[2] = 0;
    tx_data[3] = data;

    app_twi_tx(SSD1306_SLAVE_ADDRESS, 0, tx_data, sizeof(tx_data), false);

    nrf_delay_ms(100);

    app_log_func_end();
}

void    ssd1306_set_display(
    uint8_t io_ctrl
) {
    uint8_t tx_data[2];

    app_log_func_start();

    if(io_ctrl != SSD1306_DISPLAY_OFF && io_ctrl != SSD1306_DISPLAY_ON) {
        NRF_LOG_ERROR("ssd1306_set_display() NG. ctrl = 0x%02X", io_ctrl);
        return;
    }

    memset(tx_data, 0x00, sizeof(tx_data));

    tx_data[1] = SSD1306_CMD_SET_DISPLAY | io_ctrl;

    app_twi_tx(SSD1306_SLAVE_ADDRESS, 0, tx_data, sizeof(tx_data), false);

    nrf_delay_ms(100);

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

#include "app_twi.h"
#include "app_log.h"
#include "ssd1306.h"

NRF_LOG_MODULE_REGISTER();

void    main(
    void
) {
    uint8_t buffer[16];

    app_log_init();

    app_twi_init();

    NRF_LOG_INFO("214 OLED");

    nrf_delay_ms(1000);

    ssd1306_init();

    NRF_LOG_INFO("ssd1306_init() end");

    APP_ERROR_CHECK(nrf_pwr_mgmt_init());

    while(true) {
        if(NRF_LOG_PROCESS() == false) {
            nrf_pwr_mgmt_run();
        } else {
            NRF_LOG_FLUSH();
        }
    }
}
```

## 構成Parts
-

## GitHub
