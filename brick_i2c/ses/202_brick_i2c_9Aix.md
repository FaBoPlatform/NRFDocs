# #202 9Aixs I2C Brick

## Overview



## Connecting

ShinobiとFabo 9Axisを接続。

## User Include Directories
Solution Option -> Preprocessor -> User Include Directoriesに以下を追加する。(../nRF5_SDKの部分は適宜変えてください。)

|User Include Directories|
|:--|
|../nRF5_SDK/components/libraries/atomic|
|../nRF5_SDK/components/libraries/ringbuf|
|../nRF5_SDK/external/fprintf|
|../nRF5_SDK/modules/nrfx/drivers/src/prs|
|../nRF5_SDK/modules/nrfx/drivers/src|
|../nRF5_SDK/components/libraries/balloc|
|../nRF5_SDK/components/libraries/memobj|
|../nRF5_SDK/components/libraries/strerror|
|../nRF5_SDK/components/libraries/experimental_section_vars|
|../nRF5_SDK/components/libraries/log|
|../nRF5_SDK/components/libraries/log/src|
|../nRF5_SDK/components/libraries/delay|
|../nRF5_SDK/modules/nrfx/drivers/include|
|../nRF5_SDK/integration/nrfx/legacy|
|../nRF5_SDK/components/libraries/uart|
|../nRF5_SDK/components/drivers_nrf/nrf_soc_nosd|
|../nRF5_SDK/components/libraries/util|
|../nRF5_SDK/components/toolchain/cmsis/include|
|../nRF5_SDK/modules/nrfx/mdk|
|../nRF5_SDK/integration/nrfx|
|../nRF5_SDK/modules/nrfx|
|../nRF5_SDK/modules/nrfx/hal|
|../nRF5_SDK/components/boards|
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
|app_uart.c|../nRF5_SDK/components/libraries/uart|
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
define block log_dynamic_data_ { section .log_dynamic_data* };
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
#define NRF_LOG_MODULE_NAME FABO_202_9AXIS
#include "app_error.h"
#include "nrf_delay.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "mpu9250.h"

NRF_LOG_MODULE_REGISTER();

int main(void)
{
    const uint8_t               mpu9250_afs = MPU9250_AFS_2G;
    const uint8_t               mpu9250_gfs = MPU9250_GFS_250;
    const uint8_t               ak8963_mode = AK8963_MODE_C100HZ;
    const uint8_t               ak8963_mfs = AK8963_BIT_16;
    mpu9250_measurement_data_t  measurement_data;

    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();

    NRF_LOG_INFO("FABO 202 9AXIS SAMPLE");
    NRF_LOG_FLUSH();

    nrf_delay_ms(1000);

    mpu9250_initialize();
    mpu9250_set_mode(mpu9250_gfs, mpu9250_afs, ak8963_mode, ak8963_mfs);

    while(true)
    {
        nrf_delay_ms(1000);
        mpu9250_measurement(&measurement_data);
        NRF_LOG_INFO("accelerometer x = " NRF_LOG_FLOAT_MARKER, NRF_LOG_FLOAT(measurement_data.accelerometer.x));
        NRF_LOG_INFO("accelerometer y = " NRF_LOG_FLOAT_MARKER, NRF_LOG_FLOAT(measurement_data.accelerometer.y));
        NRF_LOG_INFO("accelerometer z = " NRF_LOG_FLOAT_MARKER, NRF_LOG_FLOAT(measurement_data.accelerometer.z));
        NRF_LOG_INFO("gyrometer x = " NRF_LOG_FLOAT_MARKER, NRF_LOG_FLOAT(measurement_data.gyrometer.x));
        NRF_LOG_INFO("gyrometer y = " NRF_LOG_FLOAT_MARKER, NRF_LOG_FLOAT(measurement_data.gyrometer.y));
        NRF_LOG_INFO("gyrometer z = " NRF_LOG_FLOAT_MARKER, NRF_LOG_FLOAT(measurement_data.gyrometer.z));
        NRF_LOG_INFO("magnetometer x = " NRF_LOG_FLOAT_MARKER, NRF_LOG_FLOAT(measurement_data.magnetometer.x));
        NRF_LOG_INFO("magnetometer y = " NRF_LOG_FLOAT_MARKER, NRF_LOG_FLOAT(measurement_data.magnetometer.y));
        NRF_LOG_INFO("magnetometer z = " NRF_LOG_FLOAT_MARKER, NRF_LOG_FLOAT(measurement_data.magnetometer.z));
        NRF_LOG_FLUSH();
    }
}

```

mpu9250.h
```c
#ifndef _MPU9250_H
#define _MPU9250_H

#define MPU9250_SLAVE_ADDRESS 0x68 ///< MPU9250 Default I2C slave address
#define AK8963_SLAVE_ADDRESS 0x0C ///< AK8963 I2C slave address

#define MPU9250_SELF_TEST_X_GYRO 0x00
#define MPU9250_SELF_TEST_Y_GYRO 0x01
#define MPU9250_SELF_TEST_Z_GYRO 0x02
#define MPU9250_SELF_TEST_X_ACCEL 0x0D
#define MPU9250_SELF_TEST_Y_ACCEL 0x0E
#define MPU9250_SELF_TEST_Z_ACCEL 0x0F
#define MPU9250_XG_OFFSET_H 0x13
#define MPU9250_XG_OFFSET_L 0x14
#define MPU9250_YG_OFFSET_H 0x15
#define MPU9250_YG_OFFSET_L 0x16
#define MPU9250_ZG_OFFSET_H 0x17
#define MPU9250_ZG_OFFSET_L 0x18
#define MPU9250_SMPLRT_DIV 0x19
#define MPU9250_CONFIG 0x1A
#define MPU9250_GYRO_CONFIG 0x1B
#define MPU9250_ACCEL_CONFIG 0x1C
#define MPU9250_ACCEL_CONFIG_2 0x1D
#define MPU9250_LP_ACCEL_ODR 0x1E
#define MPU9250_WOM_THR 0x1F
#define MPU9250_FIFO_EN 0x23
#define MPU9250_I2C_MST_CTRL 0x24
#define MPU9250_I2C_SLV0_ADDR 0x25
#define MPU9250_I2C_SLV0_REG 0x26
#define MPU9250_I2C_SLV0_CTRL 0x27
#define MPU9250_I2C_SLV1_ADDR 0x28
#define MPU9250_I2C_SLV1_REG 0x29
#define MPU9250_I2C_SLV1_CTRL 0x2A
#define MPU9250_I2C_SLV2_ADDR 0x2B
#define MPU9250_I2C_SLV2_REG 0x2C
#define MPU9250_I2C_SLV2_CTRL 0x2D
#define MPU9250_I2C_SLV3_ADDR 0x2E
#define MPU9250_I2C_SLV3_REG 0x2F
#define MPU9250_I2C_SLV3_CTRL 0x30
#define MPU9250_I2C_SLV4_ADDR 0x31
#define MPU9250_I2C_SLV4_REG 0x32
#define MPU9250_I2C_SLV4_DO 0x33
#define MPU9250_I2C_SLV4_CTRL 0x34
#define MPU9250_I2C_SLV4_DI 0x35
#define MPU9250_I2C_MST_STATUS 0x36
#define MPU9250_INT_PIN_CFG 0x37
#define MPU9250_INT_ENABLE 0x38
#define MPU9250_INT_STATUS 0x3A
#define MPU9250_ACCEL_XOUT_H 0x3B
#define MPU9250_ACCEL_XOUT_L 0x3C
#define MPU9250_ACCEL_YOUT_H 0x3D
#define MPU9250_ACCEL_YOUT_L 0x3E
#define MPU9250_ACCEL_ZOUT_H 0x3F
#define MPU9250_ACCEL_ZOUT_L 0x40
#define MPU9250_TEMP_OUT_H 0x41
#define MPU9250_TEMP_OUT_L 0x42
#define MPU9250_GYRO_XOUT_H 0x43
#define MPU9250_GYRO_XOUT_L 0x44
#define MPU9250_GYRO_YOUT_H 0x45
#define MPU9250_GYRO_YOUT_L 0x46
#define MPU9250_GYRO_ZOUT_H 0x47
#define MPU9250_GYRO_ZOUT_L 0x48
#define MPU9250_EXT_SENS_DATA_00 0x49
#define MPU9250_EXT_SENS_DATA_01 0x4A
#define MPU9250_EXT_SENS_DATA_02 0x4B
#define MPU9250_EXT_SENS_DATA_03 0x4C
#define MPU9250_EXT_SENS_DATA_04 0x4D
#define MPU9250_EXT_SENS_DATA_05 0x4E
#define MPU9250_EXT_SENS_DATA_06 0x4F
#define MPU9250_EXT_SENS_DATA_07 0x50
#define MPU9250_EXT_SENS_DATA_08 0x51
#define MPU9250_EXT_SENS_DATA_09 0x52
#define MPU9250_EXT_SENS_DATA_10 0x53
#define MPU9250_EXT_SENS_DATA_11 0x54
#define MPU9250_EXT_SENS_DATA_12 0x55
#define MPU9250_EXT_SENS_DATA_13 0x56
#define MPU9250_EXT_SENS_DATA_14 0x57
#define MPU9250_EXT_SENS_DATA_15 0x58
#define MPU9250_EXT_SENS_DATA_16 0x59
#define MPU9250_EXT_SENS_DATA_17 0x5A
#define MPU9250_EXT_SENS_DATA_18 0x5B
#define MPU9250_EXT_SENS_DATA_19 0x5C
#define MPU9250_EXT_SENS_DATA_20 0x5D
#define MPU9250_EXT_SENS_DATA_21 0x5E
#define MPU9250_EXT_SENS_DATA_22 0x5F
#define MPU9250_EXT_SENS_DATA_23 0x60
#define MPU9250_I2C_SLV0_DO 0x63
#define MPU9250_I2C_SLV1_DO 0x64
#define MPU9250_I2C_SLV2_DO 0x65
#define MPU9250_I2C_SLV3_DO 0x66
#define MPU9250_I2C_MST_DELAY_CTRL 0x67
#define MPU9250_SIGNAL_PATH_RESET 0x68
#define MPU9250_MOT_DETECT_CTRL 0x69
#define MPU9250_USER_CTRL 0x6A
#define MPU9250_PWR_MGMT_1 0x6B
#define MPU9250_PWR_MGMT_2 0x6C
#define MPU9250_FIFO_COUNTH 0x72
#define MPU9250_FIFO_COUNTL 0x73
#define MPU9250_FIFO_R_W 0x74
#define MPU9250_WHO_AM_I 0x75
#define MPU9250_XA_OFFSET_H 0x77
#define MPU9250_XA_OFFSET_L 0x78
#define MPU9250_YA_OFFSET_H 0x7A
#define MPU9250_YA_OFFSET_L 0x7B
#define MPU9250_ZA_OFFSET_H 0x7D
#define MPU9250_ZA_OFFSET_L 0x7E

#define MPU9250_GFS_250  0x0 ///< +250dps
#define MPU9250_GFS_500  0x1 ///< +500dps
#define MPU9250_GFS_1000 0x2 ///< +1000dps
#define MPU9250_GFS_2000 0x3 ///< +2000dps

#define MPU9250_AFS_2G  0x0 ///< 2g
#define MPU9250_AFS_4G  0x1 ///< 4g
#define MPU9250_AFS_8G  0x2 ///< 8g
#define MPU9250_AFS_16G 0x3 ///< 16g

#define AK8963_WIA 0x00
#define AK8963_INFO 0x01
#define AK8963_ST1 0x02
#define AK8963_HXL 0x03
#define AK8963_HXH 0x04
#define AK8963_HYL 0x05
#define AK8963_HYH 0x06
#define AK8963_HZL 0x07
#define AK8963_HZH 0x08
#define AK8963_ST2 0x09
#define AK8963_CNTL1 0x0A
#define AK8963_CNTL2 0x0B
#define AK8963_ASTC 0x0C
#define AK8963_TS1 0x0D
#define AK8963_TS2 0x0E
#define AK8963_I2CDIS 0x0F
#define AK8963_ASAX 0x10
#define AK8963_ASAY 0x11
#define AK8963_ASAZ 0x12
#define AK8963_RSV 0x13

#define AK8963_MODE_DOWN 0x00 ///< Power down mode
#define AK8963_MODE_ONE 0x01 ///< One shot data output
#define AK8963_MODE_C8HZ 0x02 ///< Continous data output 8Hz
#define AK8963_MODE_C100HZ 0x06 ///< Continous data output 100Hz
#define AK8963_MODE_TRIG 0x04 ///< External trigger data output
#define AK8963_MODE_TEST 0x08 ///< Self test
#define AK8963_MODE_FUSE 0x0F ///< Fuse ROM access

#define AK8963_BIT_14 0x0 ///< 14bit output
#define AK8963_BIT_16 0x1 ///< 16bit output

#define AK8963_ST1_DRDY 0x01

typedef struct {
    struct {
        float   x;
        float   y;
        float   z;
    } accelerometer;
    struct {
        float   x;
        float   y;
        float   z;
    } gyrometer;
    struct {
        float   x;
        float   y;
        float   z;
    } magnetometer;
} mpu9250_measurement_data_t;

void    mpu9250_initialize(void);
void    mpu9250_set_mode(uint8_t gfs, uint8_t afs, uint8_t mode, uint8_t mfs);
void    mpu9250_measurement(mpu9250_measurement_data_t*);

#endif
```

mpu9250.c
```c
#define NRF_LOG_MODULE_NAME MPU9250
#include "app_error.h"
#include "nrf_drv_twi.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_delay.h"
#include "mpu9250.h"
#include "app_twi.h"

static float ak8963_coef_x                      = 0;
static float ak8963_coef_y                      = 0;
static float ak8963_coef_z                      = 0;
static float ak8963_resolution                  = 0;
static float mpu9250_accelerometer_resolution   = 0;
static float mpu9250_gyrometer_resolution       = 0;
static const float ak8963_offset_x              = (28.74 - 16.15) / 2.0;
static const float ak8963_offset_y              = (25.48 - 19.56) / 2.0;
static const float ak8963_offset_z              = (11.96 - 34.84) / 2.0;
NRF_LOG_MODULE_REGISTER();

void    mpu9250_measurement(
    mpu9250_measurement_data_t* measurement_data
) {
    uint8_t rx_data_mpu9250[14];
    uint8_t rx_data_ak8963[7];
    uint8_t rx_data_ak8963_drdy;
    uint8_t hofl_bit;
    int16_t temp;

    app_twi_rx_func(MPU9250_SLAVE_ADDRESS, MPU9250_ACCEL_XOUT_H, rx_data_mpu9250, sizeof(rx_data_mpu9250));

    temp = ((int16_t)rx_data_mpu9250[0] << 8) | rx_data_mpu9250[1];
    measurement_data->accelerometer.x = (float)temp * mpu9250_accelerometer_resolution;
    temp = ((int16_t)rx_data_mpu9250[2] << 8) | rx_data_mpu9250[3];
    measurement_data->accelerometer.y = (float)temp * mpu9250_accelerometer_resolution;
    temp = ((int16_t)rx_data_mpu9250[4] << 8) | rx_data_mpu9250[5];
    measurement_data->accelerometer.z = (float)temp * mpu9250_accelerometer_resolution;

    temp = ((int16_t)rx_data_mpu9250[8] << 8) | rx_data_mpu9250[9];
    measurement_data->gyrometer.x = (float)temp * mpu9250_gyrometer_resolution;
    temp = ((int16_t)rx_data_mpu9250[10] << 8) | rx_data_mpu9250[11];
    measurement_data->gyrometer.y = (float)temp * mpu9250_gyrometer_resolution;
    temp = ((int16_t)rx_data_mpu9250[12] << 8) | rx_data_mpu9250[13];
    measurement_data->gyrometer.z = (float)temp * mpu9250_gyrometer_resolution;

    while(true) {
        app_twi_rx_func(AK8963_SLAVE_ADDRESS, AK8963_ST1, &rx_data_ak8963_drdy, sizeof(rx_data_ak8963_drdy));
        if((rx_data_ak8963_drdy & AK8963_ST1_DRDY) == AK8963_ST1_DRDY) {
            break;
        }
        nrf_delay_ms(10);
    }

    app_twi_rx_func(AK8963_SLAVE_ADDRESS, AK8963_HXL, rx_data_ak8963, sizeof(rx_data_ak8963));

    hofl_bit = (uint8_t)0x08 & rx_data_ak8963[6];
    if(hofl_bit == 0) {
        temp = ((int16_t)rx_data_ak8963[1] << 8) | rx_data_ak8963[0];
        measurement_data->magnetometer.x = (float)temp * (((ak8963_coef_x - 128.0) * 0.5) / 128.0 + 1.0) * ak8963_resolution - ak8963_offset_x;

        temp = ((int16_t)rx_data_ak8963[3] << 8) | rx_data_ak8963[2];
        measurement_data->magnetometer.y = (float)temp * (((ak8963_coef_y - 128.0) * 0.5) / 128.0 + 1.0) * ak8963_resolution - ak8963_offset_y;

        temp = ((int16_t)rx_data_ak8963[5] << 8) | rx_data_ak8963[4];
        measurement_data->magnetometer.z = (float)temp * (((ak8963_coef_z - 128.0) * 0.5) / 128.0 + 1.0) * ak8963_resolution - ak8963_offset_z;
    } else {
        measurement_data->magnetometer.x = 0;
        measurement_data->magnetometer.y = 0;
        measurement_data->magnetometer.z = 0;
    }

}

void mpu9250_set_mode(uint8_t gfs, uint8_t afs, uint8_t mode, uint8_t mfs)
{
    uint8_t reg[2];
    uint8_t address;
    uint8_t rb[3];
    uint8_t tx_data;
    uint8_t rx_addr;
    uint8_t rx_data[3];

    switch(gfs) {
        case MPU9250_GFS_250:
            mpu9250_gyrometer_resolution = 250.0 / 32768.0;
            break;
        case MPU9250_GFS_500:
            mpu9250_gyrometer_resolution = 500.0 / 32768.0;
            break;
        case MPU9250_GFS_1000:
            mpu9250_gyrometer_resolution = 1000.0 / 32768.0;
            break;
        case MPU9250_GFS_2000:
            mpu9250_gyrometer_resolution = 2000.0 / 32768.0;
            break;
        default:
            break;
    }

    switch(afs) {
        case MPU9250_AFS_2G:
            mpu9250_accelerometer_resolution = 2.0 / 32768.0;
            break;
        case MPU9250_AFS_4G:
            mpu9250_accelerometer_resolution = 4.0 / 32768.0;
            break;
        case MPU9250_AFS_8G:
            mpu9250_accelerometer_resolution = 8.0 / 32768.0;
            break;
        case MPU9250_AFS_16G:
            mpu9250_accelerometer_resolution = 16.0 / 32768.0;
            break;
        default:
            break;
    }

    tx_data = 0x00;
    app_twi_tx_func(MPU9250_SLAVE_ADDRESS, MPU9250_PWR_MGMT_1, &tx_data, sizeof(tx_data));

    tx_data = 0x01;
    app_twi_tx_func(MPU9250_SLAVE_ADDRESS, MPU9250_PWR_MGMT_1, &tx_data, sizeof(tx_data));

    tx_data = gfs << 3;
    app_twi_tx_func(MPU9250_SLAVE_ADDRESS, MPU9250_GYRO_CONFIG, &tx_data, sizeof(tx_data));

    tx_data = afs << 3;
    app_twi_tx_func(MPU9250_SLAVE_ADDRESS, MPU9250_ACCEL_CONFIG, &tx_data, sizeof(tx_data));

    tx_data = 0x03;
    app_twi_tx_func(MPU9250_SLAVE_ADDRESS, MPU9250_ACCEL_CONFIG_2, &tx_data, sizeof(tx_data));

    tx_data = 0x02;
    app_twi_tx_func(MPU9250_SLAVE_ADDRESS, MPU9250_INT_PIN_CFG, &tx_data, sizeof(tx_data));

    tx_data = 0x01;
    app_twi_tx_func(MPU9250_SLAVE_ADDRESS, MPU9250_PWR_MGMT_1, &tx_data, sizeof(tx_data));

    switch(mfs) {
        case AK8963_BIT_14:
            ak8963_resolution = 4912.0 / 8190.0;
            break;
        case AK8963_BIT_16:
            ak8963_resolution = 4912.0 / 32760.0;
            break;
        default:
            break;
    }

    tx_data = 0x00;
    app_twi_tx_func(AK8963_SLAVE_ADDRESS, AK8963_CNTL1, &tx_data, sizeof(tx_data));

    tx_data = 0x0f;
    app_twi_tx_func(AK8963_SLAVE_ADDRESS, AK8963_CNTL1, &tx_data, sizeof(tx_data));

    app_twi_rx_func(AK8963_SLAVE_ADDRESS, AK8963_ASAX, rx_data, sizeof(rx_data));
    ak8963_coef_x = (float)(rx_data[0] - 128) / 256.0 + 1.0;
    ak8963_coef_y = (float)(rx_data[1] - 128) / 256.0 + 1.0;
    ak8963_coef_z = (float)(rx_data[2] - 128) / 256.0 + 1.0;

    tx_data = (mfs << 4) | mode;
    app_twi_tx_func(AK8963_SLAVE_ADDRESS, AK8963_CNTL1, &tx_data, sizeof(tx_data));
}


void mpu9250_initialize(void)
{
    app_twi_init();
}
```

app_twi.h
```c
#ifndef _APP_TWI_H
#define _APP_TWI_H

void    app_twi_init(void);
int8_t  app_twi_tx_func(uint8_t dev_addr, uint8_t reg_addr, uint8_t* tx_buff_addr, uint16_t tx_data_size);
int8_t  app_twi_rx_func(uint8_t dev_addr, uint8_t reg_addr, uint8_t* rx_buff_addr, uint16_t rx_data_size);

#endif
```

app_twi.c
```c
#define NRF_LOG_MODULE_NAME APP_TWI
#include "app_error.h"
#include "nrf_drv_twi.h"
#include "nrf_log.h"
#include "app_twi.h"

#define ARDUINO_SCL_PIN 27
#define ARDUINO_SDA_PIN 26

static nrf_drv_twi_t    app_twi_instance    =   NRF_DRV_TWI_INSTANCE(0);
static volatile bool    app_twi_xfer_done   =   false;
NRF_LOG_MODULE_REGISTER();

void    app_twi_event_handler(nrf_drv_twi_evt_t const* a_event, void* a_context) {
    NRF_LOG_DEBUG("app_twi_event_handler() ### START ###");
    NRF_LOG_DEBUG("a_event->type = %d", a_event->type);
    switch(a_event->type) {
        case NRF_DRV_TWI_EVT_DONE:
            NRF_LOG_DEBUG("app_twi_xfer_done = %d", app_twi_xfer_done);
            if(app_twi_xfer_done == false) {
                app_twi_xfer_done = true;
            }
            break;
        default:
            break;
    }

    NRF_LOG_DEBUG("app_twi_event_handler() ### END ###");
}

void    app_twi_init(void) {
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

int8_t  app_twi_tx_func(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len) {
    uint8_t tx_buf[len + 1];

    NRF_LOG_DEBUG("app_twi_tx_func() ### START ###");
    NRF_LOG_DEBUG("dev_id   : %02X", dev_id);
    NRF_LOG_DEBUG("reg_addr : %02X", reg_addr);
    NRF_LOG_DEBUG("data     : %08X", data);
    NRF_LOG_DEBUG("len      : %d", len);

    memset(tx_buf, 0, len + 1);

    tx_buf[0] = reg_addr;
    if(len) {
        memcpy(&tx_buf[1], data, len);
    }

    NRF_LOG_HEXDUMP_DEBUG(tx_buf, len + 1);

    app_twi_xfer_done = false;
    APP_ERROR_CHECK(nrf_drv_twi_tx(&app_twi_instance, dev_id, tx_buf, len + 1, false));
    while(app_twi_xfer_done == false);

    NRF_LOG_DEBUG("app_twi_tx_func() ### END ###");

    return 0;
}

int8_t  app_twi_rx_func(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len) {

    NRF_LOG_DEBUG("app_twi_rx_func() ### START ###");
    NRF_LOG_DEBUG("dev_id   : %02X", dev_id);
    NRF_LOG_DEBUG("reg_addr : %02X", reg_addr);
    NRF_LOG_DEBUG("data     : %08X", data);
    NRF_LOG_DEBUG("len      : %d", len);

    memset(data, 0x00, len);

    app_twi_tx_func(dev_id, reg_addr, NULL, 0);

    app_twi_xfer_done = false;
    APP_ERROR_CHECK(nrf_drv_twi_rx(&app_twi_instance, dev_id, data, len));
    while(app_twi_xfer_done == false);

    NRF_LOG_HEXDUMP_DEBUG(data, len);

    NRF_LOG_DEBUG("app_twi_rx_func() ### END ###");

    return 0;
}
```

## 構成Parts
-

## GitHub
