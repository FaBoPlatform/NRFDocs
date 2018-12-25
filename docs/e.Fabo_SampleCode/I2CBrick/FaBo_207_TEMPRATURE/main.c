#include <stdio.h>
#include "boards.h"
#include "app_util_platform.h"
#include "app_error.h"
#include "nrf_drv_twi.h"
#include "nrf_delay.h"

#define NRF_LOG_MODULE_NAME "Fabo_207_temprature"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

#define TWI_INSTANCE_ID     0

#define ADT7410_SLAVE_ADDRESS 0x48 ///< Default I2C Slave Address

//Register Addresses
#define ADT7410_TEMP_MSB_REG 0x00
#define ADT7410_TEMP_LSB_REG 0x01
#define ADT7410_STATUS_REG 0x02
#define ADT7410_CONFIGURATION_REG 0x03
#define ADT7410_WHO_AM_I_REG 0x0B

//Config Parameter
#define ADT7410_13BIT_RESOLUTION 0x00
#define ADT7410_16BIT_RESOLUTION 0x80
#define ADT7410_OP_MODE_CONTINUOUS 0x00
#define ADT7410_OP_MODE_ONESHOT 0x20
#define ADT7410_OP_MODE_SPS 0x40
#define ADT7410_OP_MODE_SHUTDOWN 0x60
#define ADT7410_INTERRUPT_MODE  0x00
#define ADT7410_COMPARATOR_MODE 0x10
#define ADT7410_INT_LOW  0x00
#define ADT7410_INT_HIGH 0x08
#define ADT7410_CT_LOW  0x00
#define ADT7410_CT_HIGH 0x04
#define ADT7410_16BIT_OP_MODE_1FAULT 0x00
#define ADT7410_16BIT_OP_MODE_2FAULT 0x01
#define ADT7410_16BIT_OP_MODE_3FAULT 0x02
#define ADT7410_16BIT_OP_MODE_4FAULT 0x03

void begin(void);
void configure(uint8_t config);
bool checkDataReady(void);
float readTemperature(void);
void writeI2c(uint8_t address, uint8_t data);
void readI2c(uint8_t address,uint8_t * data);

/* TWI instance. */
static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);

void begin() {
  uint8_t config;
//   config  = ADT7410_13BIT_RESOLUTION;
  config  = ADT7410_16BIT_RESOLUTION;
  config |= ADT7410_16BIT_OP_MODE_1FAULT;
  config |= ADT7410_CT_LOW;
  config |= ADT7410_INT_LOW;
  config |= ADT7410_INTERRUPT_MODE;
  config |= ADT7410_OP_MODE_CONTINUOUS;
  configure(config);
}

void configure(uint8_t config) {
  writeI2c(ADT7410_CONFIGURATION_REG, config);
}
bool checkDataReady() {
  uint8_t status;
  readI2c(ADT7410_STATUS_REG, &status);
  if ( (status & 0x80) ) {
    return false;
  } else {
    return true;
  }
}

float readTemperature() {
  uint8_t buffer[2];
  uint16_t adc;
  float temp;
  int16_t val;
  uint8_t config;
	
  if ( checkDataReady() ) {
		nrf_delay_ms(10);
    readI2c(ADT7410_CONFIGURATION_REG,&config);
		nrf_delay_ms(40);
    readI2c(ADT7410_TEMP_MSB_REG,buffer);
		nrf_delay_ms(10);
    adc = (uint16_t)buffer[0] << 8;
    adc |= buffer[1];
    val = (long)adc;
    if ( (config & 0x80) ) {
      // 13bit resolution
      adc >>= 3;
      if(adc & 0x1000) {
        val = val - 8192;
      }
      temp = (float)val / 16.0F;
    } else {
      // 16bit resolution
      if(adc & 0x8000) {
        val = val - 65536;
      }
      temp = (float)val / 128.0F;
    }
    return temp;
  } else {
    return 0.0;
  }
}

void writeI2c(uint8_t address, uint8_t data) {
	uint32_t err_code;
	uint8_t reg[2] = {address,data};
  err_code = nrf_drv_twi_tx(&m_twi, ADT7410_SLAVE_ADDRESS, reg, sizeof(reg), false);
  APP_ERROR_CHECK(err_code);
	nrf_delay_ms(40);
}

void readI2c(uint8_t address,uint8_t * data) {
	nrf_delay_ms(10);
	uint32_t err_code;
	uint8_t reg = address;
  err_code = nrf_drv_twi_tx(&m_twi, ADT7410_SLAVE_ADDRESS, &reg, sizeof(reg), false);
  APP_ERROR_CHECK(err_code);
	nrf_delay_ms(100);
  err_code = nrf_drv_twi_rx(&m_twi, ADT7410_SLAVE_ADDRESS, data, sizeof(data));
  APP_ERROR_CHECK(err_code);
}

void twi_handler(nrf_drv_twi_evt_t const * p_event, void * p_context)
{
    switch (p_event->type)
    {
        case NRF_DRV_TWI_EVT_DONE:
            if (p_event->xfer_desc.type == NRF_DRV_TWI_XFER_RX)
            {
            }
            break;
        default:
            break;
    }
}

void twi_init (void)
{
    ret_code_t err_code;

    const nrf_drv_twi_config_t twi_Temprature_config = {
       .scl                = ARDUINO_SCL_PIN,
       .sda                = ARDUINO_SDA_PIN,
       .frequency          = NRF_TWI_FREQ_100K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
       .clear_bus_init     = false
    };

    err_code = nrf_drv_twi_init(&m_twi, &twi_Temprature_config, twi_handler, NULL);
    APP_ERROR_CHECK(err_code);

    nrf_drv_twi_enable(&m_twi);
}

int main(void)
{
    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));

    NRF_LOG_INFO("\r\nFabo_207_Temprature_Brick Sample\r\n");
    NRF_LOG_FLUSH();
    twi_init();
		NRF_LOG_INFO("RESET\r\n");
    NRF_LOG_FLUSH();
		begin();
    while (true)
    {
			float a = readTemperature();
			NRF_LOG_INFO("Temperarue" NRF_LOG_FLOAT_MARKER "\r\n",a);
			NRF_LOG_FLUSH();
			nrf_delay_ms(1000);
    }
}
