# #201 3Aixs I2C Brick

## Overview

## Connecting

ShinobiとFabo 3Axisを接続。

##必要なソフトウェアコンポーネント

```c
#include <stdio.h>
#include "boards.h"
#include "app_util_platform.h"
#include "app_error.h"
#include "nrf_drv_twi.h"
#include "nrf_delay.h"
#define NRF_LOG_MODULE_NAME "FaBo_210_3Aix"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

#define TWI_INSTANCE_ID     0
#define ADXL345_SLAVE_ADDRESS 0x53
#define ADXL345_DEVID_REG 0x00
#define ADXL345_DEVICE 0xe5
#define ADXL345_THRESH_TAP_REG 0x1D
#define ADXL345_DUR_REG 0x21
#define ADXL345_LATENT_REG 0x22
#define ADXL345_WINDOW_REG 0x23
#define ADXL345_INT_MAP_REG 0x2F
#define ADXL345_INT_ENABLE_REG 0x2E
#define ADXL345_POWER_CTL_REG 0x2D
#define ADXL345_TAP_STATUS_REG 0x2B
#define ADXL345_TAP_AXES_REG 0x2A
#define ADXL345_INT_SOURCE_REG 0x30
#define ADXL345_DATA_FORMAT_REG 0x31
#define ADXL345_SELF_TEST_ON 0x80
#define ADXL345_SELF_TEST_OFF 0x00
#define ADXL345_SPI_ON 0x40
#define ADXL345_SPI_OFF 0x00
#define ADXL345_INT_INVERT_ON 0x20
#define ADXL345_INT_INVERT_OFF 0x00
#define ADXL345_FULL_RES_ON 0x08
#define ADXL345_FULL_RES_OFF 0x00
#define ADXL345_JUSTIFY_ON 0x04
#define ADXL345_JUSTIFY_OFF 0x00
#define ADXL345_TAP_AXES_Z_ON 0x01
#define ADXL345_TAP_AXES_Y_ON 0x02
#define ADXL345_TAP_AXES_X_ON 0x04
#define ADXL345_INT_SINGLE_TAP 0x40
#define ADXL345_INT_DOUBLE_TAP 0x20

#define ADXL345_RANGE_2G 0x00
#define ADXL345_RANGE_4G 0x01
#define ADXL345_RANGE_8G 0x02
#define ADXL345_RANGE_16G 0x03

#define ADXL345_AUTO_SLEEP_ON 0x10
#define ADXL345_AUTO_SLEEP_OFF 0x00
#define ADXL345_MEASURE_ON 0x08
#define ADXL345_MEASURE_OFF 0x00
#define ADXL345_SLEEP_ON 0x04
#define ADXL345_SLEEP_OFF 0x00

#define ADXL345_WAKEUP_8HZ 0x00
#define ADXL345_WAKEUP_4HZ 0x01
#define ADXL345_WAKEUP_2HZ 0x02
#define ADXL345_WAKEUP_1HZ 0x03

void writeI2c(uint8_t register_addr, uint8_t value);

static volatile bool m_xfer_done = false;
static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);
static uint8_t m_sample[6];

void read_sensor_data(void);

void configuration(void)
{
	NRF_LOG_INFO("configuration\r\n");
	uint8_t conf = ADXL345_SELF_TEST_OFF;
	conf |= ADXL345_SPI_OFF;
	conf |= ADXL345_INT_INVERT_OFF;
	conf |= ADXL345_FULL_RES_OFF;
	conf |= ADXL345_JUSTIFY_OFF;
	conf |= ADXL345_RANGE_16G;
  writeI2c(ADXL345_DATA_FORMAT_REG, conf);
}

bool searchDevice()
{
	NRF_LOG_INFO("searchDevice\r\n");
  uint8_t device = 0x00;
	writeI2c(ADXL345_DEVID_REG,1);
  //readI2c(ADXL345_DEVID_REG, 1, &device);
  if(device == ADXL345_DEVICE){
    return true;
  } else{
    return false;
  }
}

static void powerOn()
{
	NRF_LOG_INFO("powerOn\r\n");
  uint8_t power = ADXL345_AUTO_SLEEP_OFF;
  power |= ADXL345_MEASURE_ON;
  power |= ADXL345_SLEEP_OFF;
  power |= ADXL345_WAKEUP_8HZ;
  writeI2c(ADXL345_POWER_CTL_REG, power);
}

uint8_t readIntStatus()
{
  uint8_t buff;
  //readI2c(ADXL345_INT_SOURCE_REG, 1, &buff);
  return buff;
}

void enableTap()
{
  writeI2c(ADXL345_THRESH_TAP_REG, 0x32); // 62.5mg/LBS
  writeI2c(ADXL345_DUR_REG, 0x0f); // 1.25ms/LSB
  writeI2c(ADXL345_LATENT_REG, 0x78); // 1.25ms/LSB
  writeI2c(ADXL345_WINDOW_REG, 0xcb); // 1.25ms/LSB
  uint8_t int_tap = ADXL345_INT_SINGLE_TAP | ADXL345_INT_DOUBLE_TAP;
  writeI2c(ADXL345_INT_ENABLE_REG, int_tap);
  writeI2c(ADXL345_TAP_AXES_REG, ADXL345_TAP_AXES_Z_ON);
}

bool isSingleTap(uint8_t value)
{
  if((value & 0x40) == 0x40){
    return true;
  } else {
    return false;
  }
}

bool isDoubleTap(uint8_t value)
{
  if((value & 0x20) == 0x20){
    return true;
  } else {
    return false;
  }
}

__STATIC_INLINE void data_handler(uint8_t *axis_buff)
{
	NRF_LOG_INFO("Device=%x\n\r",axis_buff[0]);
	NRF_LOG_INFO("Device=%x\n\r",axis_buff[1]);
	NRF_LOG_INFO("Device=%x\n\r",axis_buff[2]);
	NRF_LOG_INFO("Device=%x\n\r",axis_buff[3]);
	NRF_LOG_INFO("Device=%x\n\r",axis_buff[4]);
	NRF_LOG_INFO("Device=%x\n\r",axis_buff[5]);

	int16_t x = (((int)axis_buff[0]) << 8) | axis_buff[1];
  int16_t y = (((int)axis_buff[2]) << 8) | axis_buff[3];
	int16_t z = (((int)axis_buff[4]) << 8) | axis_buff[5];

	NRF_LOG_INFO("x= %d y= %d z= %d \r\n",x,y,z);

	 if(axis_buff[0] == ADXL345_DEVICE){
    NRF_LOG_INFO("I am ADXL345\n\r");
  }

}


void twi_handler(nrf_drv_twi_evt_t const * p_event, void * p_context)
{
    switch (p_event->type)
    {
        case NRF_DRV_TWI_EVT_DONE:
            if (p_event->xfer_desc.type == NRF_DRV_TWI_XFER_RX)
            {
                data_handler(m_sample);
            }
            m_xfer_done = true;
            break;
        default:
            break;
    }
}

void twi_init (void)
{
    ret_code_t err_code;

    const nrf_drv_twi_config_t twi_lm75b_config = {
       .scl                = ARDUINO_SCL_PIN,
       .sda                = ARDUINO_SDA_PIN,
       .frequency          = NRF_TWI_FREQ_100K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
       .clear_bus_init     = false
    };

    err_code = nrf_drv_twi_init(&m_twi, &twi_lm75b_config, twi_handler, NULL);
    APP_ERROR_CHECK(err_code);

    nrf_drv_twi_enable(&m_twi);
}

static void read_sensor_data()
{
    m_xfer_done = false;
    ret_code_t err_code = nrf_drv_twi_rx(&m_twi, ADXL345_SLAVE_ADDRESS, m_sample, sizeof(m_sample));
    APP_ERROR_CHECK(err_code);
}

void writeI2c(uint8_t register_addr, uint8_t value)
{
		uint32_t err_code;
    uint8_t reg[2] = {register_addr, value};
    err_code = nrf_drv_twi_tx(&m_twi, ADXL345_SLAVE_ADDRESS, reg, sizeof(reg), false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
}

int main(void)
{
    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_INFO("FaBo_3AiX_201 Sample\r\n");
    NRF_LOG_FLUSH();
    twi_init();
		searchDevice();
		nrf_delay_ms(10);
		read_sensor_data();
		NRF_LOG_INFO("Init.\r\n");
		nrf_delay_ms(10);
		configuration();
		nrf_delay_ms(10);
		powerOn();
		nrf_delay_ms(10);
	while(1){
		uint8_t reg[2] = {0x32,6};
    nrf_drv_twi_tx(&m_twi, ADXL345_SLAVE_ADDRESS, reg, sizeof(reg), false);
		nrf_delay_ms(10);
		read_sensor_data();
		nrf_delay_ms(1000);
		NRF_LOG_FLUSH();
	}
}

```


## 構成Parts
-

## GitHub
