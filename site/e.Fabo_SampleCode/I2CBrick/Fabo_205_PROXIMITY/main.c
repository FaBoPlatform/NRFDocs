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

#define VCNL4010_SLAVE_ADDRESS 0x13 ///< I2C Slave Address
#define VCNL4010_DEVICE_ID 0x21 ///< Product,Revision ID Value

//Register Addresses
#define VCNL4010_REG_CMD 0x80
#define VCNL4010_REG_ID 0x81
#define VCNL4010_REG_PROX_RATE 0x82
#define VCNL4010_REG_LED_CRNT 0x83
#define VCNL4010_REG_AMBI_PARM 0x84
#define VCNL4010_REG_AMBI_DATA_H 0x85
#define VCNL4010_REG_AMBI_DATA_L 0x86
#define VCNL4010_REG_PROX_DATA_H 0x87
#define VCNL4010_REG_PROX_DATA_L 0x88
#define VCNL4010_REG_INT_CTRL 0x89
#define VCNL4010_REG_INT_LOW_H 0x8A
#define VCNL4010_REG_INT_LOW_L 0x8B
#define VCNL4010_REG_INT_HIGH_H 0x8C
#define VCNL4010_REG_INT_HIGH_L 0x8D
#define VCNL4010_REG_INT_STAT 0x8E
#define VCNL4010_REG_PROX_ADJ 0x8F

//Commands
#define VCNL4010_CMD_SELFTIMED_EN 0x01
#define VCNL4010_CMD_PROX_EN 0x02
#define VCNL4010_CMD_ALS_EN 0x04
#define VCNL4010_CMD_PROX_OD 0x08
#define VCNL4010_CMD_ALS_OD 0x10
#define VCNL4010_CMD_PROX_DRDY 0x20
#define VCNL4010_CMD_ALS_DRDY 0x40

//Proximity Measurement Rate
#define VCNL4010_PROX_RATE_1   0x00
#define VCNL4010_PROX_RATE_3   0x01
#define VCNL4010_PROX_RATE_7   0x02
#define VCNL4010_PROX_RATE_16  0x03
#define VCNL4010_PROX_RATE_31  0x04
#define VCNL4010_PROX_RATE_62  0x05
#define VCNL4010_PROX_RATE_125 0x06
#define VCNL4010_PROX_RATE_250 0x07

//Ambient Light Parameter
#define VCNL4010_AMBI_CONT_CONV_MODE 0x80
#define VCNL4010_AMBI_RATE_1  0x00
#define VCNL4010_AMBI_RATE_2  0x10
#define VCNL4010_AMBI_RATE_3  0x20
#define VCNL4010_AMBI_RATE_4  0x30
#define VCNL4010_AMBI_RATE_5  0x40
#define VCNL4010_AMBI_RATE_6  0x50
#define VCNL4010_AMBI_RATE_8  0x60
#define VCNL4010_AMBI_RATE_10 0x70
#define VCNL4010_AMBI_AUTO_OFFSET 0x08
#define VCNL4010_AMBI_AVE_NUM_1   0x00
#define VCNL4010_AMBI_AVE_NUM_2   0x01
#define VCNL4010_AMBI_AVE_NUM_4   0x02
#define VCNL4010_AMBI_AVE_NUM_8   0x03
#define VCNL4010_AMBI_AVE_NUM_16  0x04
#define VCNL4010_AMBI_AVE_NUM_32  0x05
#define VCNL4010_AMBI_AVE_NUM_64  0x06
#define VCNL4010_AMBI_AVE_NUM_128 0x07

bool begin(void);
bool searchDevice(void);
void configuration(void);
void setCommand(uint8_t config);
void setProxRate(uint8_t config);
void setLedCurrent(uint8_t config);
void setAmbiParm(uint8_t config);
bool checkProxReady(void);
bool checkAmbiReady(void);
uint16_t readProx(void);
uint16_t readAmbi(void);
void dumpReg(void);
void writeI2c(uint8_t address, uint8_t data);
void readI2c(uint8_t address,uint8_t * data);
void print_byte(uint8_t val);

static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);


bool begin() {
  if ( searchDevice() ) {
    configuration();
    return true;
  } else {
    return false;
  }
}

bool searchDevice() {
	uint8_t data;
	readI2c(VCNL4010_REG_ID,&data);
  if ( data == VCNL4010_DEVICE_ID ) {
    return true;
  } else {
    return false;
  }
}

void configuration() {
  setCommand(
  VCNL4010_CMD_SELFTIMED_EN |
  VCNL4010_CMD_PROX_EN |
  VCNL4010_CMD_ALS_EN );
  setProxRate(VCNL4010_PROX_RATE_250);
  setLedCurrent(20);
  setAmbiParm(
  VCNL4010_AMBI_RATE_10 |
  VCNL4010_AMBI_AUTO_OFFSET |
  VCNL4010_AMBI_AVE_NUM_128 );
}

void setCommand(uint8_t config) {
  writeI2c(VCNL4010_REG_CMD, config);
}

void setProxRate(uint8_t config) {
  writeI2c(VCNL4010_REG_PROX_RATE, config);
}

void setLedCurrent(uint8_t config) {
  writeI2c(VCNL4010_REG_LED_CRNT, config);
}

void setAmbiParm(uint8_t config) {
  writeI2c(VCNL4010_REG_AMBI_PARM, config);
}

bool checkProxReady() {
	uint8_t data;
	NRF_LOG_FLUSH();
	readI2c(VCNL4010_REG_CMD,&data);
  if ( data & VCNL4010_CMD_PROX_DRDY ) {
    return true;
  }
  return false;
}

bool checkAmbiReady() {
	uint8_t data;
	readI2c(VCNL4010_REG_CMD,&data);
  if ( data & VCNL4010_CMD_ALS_DRDY ) {
    return true;
  }
  return false;
}

uint16_t readProx() {
	uint8_t data_h,data_l;
	readI2c(VCNL4010_REG_PROX_DATA_H,&data_h);
	readI2c(VCNL4010_REG_PROX_DATA_L,&data_l);
  uint16_t value;
  value = data_h;
  value <<= 8;
  value |= data_l;
  return value;
}

uint16_t readAmbi() {
	uint8_t ambi_h,ambi_l;
  uint16_t value;
	readI2c(VCNL4010_REG_AMBI_DATA_H,&ambi_h);
	readI2c(VCNL4010_REG_AMBI_DATA_L,&ambi_l);
  value = ambi_h;
  value <<= 8;
  value |= ambi_l;
  return value;
}

void dumpReg() {
  uint8_t data;
  int i;
  for (i=0x80;i<=0x90;i++){
		readI2c(i,&data);
		NRF_LOG_INFO("0x%x:%b\n\r",i,data);
		NRF_LOG_FLUSH();
    print_byte(data);
  }
}

void print_byte(uint8_t val) {
  int i;
	NRF_LOG_INFO("B");
	NRF_LOG_FLUSH();
  for(i=7; i>=0; i--){
		NRF_LOG_INFO("%b",val >> i & 1);
		NRF_LOG_FLUSH();
  }
}

void writeI2c(uint8_t address, uint8_t data) {
	uint32_t err_code;
	uint8_t reg[2] = {address,data};
  err_code = nrf_drv_twi_tx(&m_twi, VCNL4010_SLAVE_ADDRESS, reg, sizeof(reg), false);
  APP_ERROR_CHECK(err_code);
	nrf_delay_ms(40);
}

void readI2c(uint8_t address,uint8_t * data) {
	nrf_delay_ms(10);
	uint32_t err_code;
	uint8_t reg = address;
  err_code = nrf_drv_twi_tx(&m_twi, VCNL4010_SLAVE_ADDRESS, &reg, sizeof(reg), false);
  APP_ERROR_CHECK(err_code);
	nrf_delay_ms(100);
  err_code = nrf_drv_twi_rx(&m_twi, VCNL4010_SLAVE_ADDRESS, data, sizeof(data));
  APP_ERROR_CHECK(err_code);
	nrf_delay_ms(40);
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

int main(void)
{
    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_INFO("FaBo_Proximity\r\n");
    NRF_LOG_FLUSH();
    twi_init();
		begin();
		NRF_LOG_INFO("Init...\r\n");
		NRF_LOG_FLUSH();
	while(1){
		if(checkProxReady()){
			NRF_LOG_INFO("Prox:%d\r\n",readProx());
			NRF_LOG_FLUSH();
  }
		nrf_delay_ms(10);
  if(checkAmbiReady()){
		NRF_LOG_INFO("Ambi:%d\r\n",readAmbi());
		NRF_LOG_FLUSH();
  }
		nrf_delay_ms(1000);
	}
}
