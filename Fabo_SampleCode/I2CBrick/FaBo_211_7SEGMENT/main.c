#include <stdio.h>
#include <math.h>
#include "boards.h"
#include "app_util_platform.h"
#include "app_error.h"
#include "nrf_drv_twi.h"
#include "nrf_delay.h"
#define NRF_LOG_MODULE_NAME "FaBo_211_7Segment"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

#define TWI_INSTANCE_ID     0

#define TLC59208_SLAVE_ADDRESS 0x20 ///< Default I2C slave address
#define TLC59208_PWM_VALUE 0x02 ///< PWM output value


#define TLC59208_LED_0 0x77 ///< 0
#define TLC59208_LED_1 0x14 ///< 1
#define TLC59208_LED_2 0xB3 ///< 2
#define TLC59208_LED_3 0xB6 ///< 3
#define TLC59208_LED_4 0xD4 ///< 4
#define TLC59208_LED_5 0xE6 ///< 5
#define TLC59208_LED_6 0xE7 ///< 6
#define TLC59208_LED_7 0x74 ///< 7
#define TLC59208_LED_8 0xF7 ///< 8
#define TLC59208_LED_9 0xF6 ///< 9

#define TLC59208_LED_A 0xB7 ///< A
#define TLC59208_LED_B 0xC7 ///< B
#define TLC59208_LED_C 0x63 ///< C
#define TLC59208_LED_D 0x97 ///< D
#define TLC59208_LED_E 0xE3 ///< E
#define TLC59208_LED_F 0xE1 ///< F
#define TLC59208_LED_H 0xD5 ///< H

#define TLC59208_LED_DP 0x08 ///< Dot
#define TLC59208_LED_OFF 0x00 ///< OFF

#define TLC59208_LED_PWM0 0x01
#define TLC59208_LED_PWM1 0x02
#define TLC59208_LED_PWM2 0x04
#define TLC59208_LED_PWM3 0x08
#define TLC59208_LED_PWM4 0x10
#define TLC59208_LED_PWM5 0x20
#define TLC59208_LED_PWM6 0x40
#define TLC59208_LED_PWM7 0x80

#define TLC59208_LED_PIN_A 0x20
#define TLC59208_LED_PIN_B 0x10
#define TLC59208_LED_PIN_C 0x04
#define TLC59208_LED_PIN_D 0x02
#define TLC59208_LED_PIN_E 0x01
#define TLC59208_LED_PIN_F 0x40
#define TLC59208_LED_PIN_G 0x80
#define TLC59208_LED_PIN_DP 0x08

void FaBo7Seg_TLC59208(uint8_t addr);
//FaBo7Seg_TLC59208(uint8_t addr1, uint8_t addr2);
//FaBo7Seg_TLC59208(uint8_t addr1, uint8_t addr2, uint8_t addr3);
//FaBo7Seg_TLC59208(uint8_t addr1, uint8_t addr2, uint8_t addr3, uint8_t addr4);
bool configure(void);
void showNumber(uint8_t number, uint8_t digit);
void clearNumber(uint8_t digit);
void showNumberFullDigit(uint8_t number);
void showDot(uint8_t digit);
void clearDot(uint8_t digit);
void showPattern(uint8_t data, uint8_t digit);
uint8_t _i2caddr[4];
uint8_t _digits;
void writeI2c(uint8_t address, uint8_t data);


static volatile bool m_xfer_done = false;
static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);

void FaBo7Seg_TLC59208(uint8_t addr) {
  _i2caddr[0] = addr;
  _digits = 1;
}

bool configure(void) {
  uint8_t i;
  uint8_t ret = 1;
	uint32_t err_code;
	for (i=0; i<_digits; i++) {
		uint8_t reg[19] = {0x80,0x81,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0xAA,0xAA,0x92,0x94,0x98,0xD0};
		err_code = nrf_drv_twi_tx(&m_twi, _i2caddr[i], reg, sizeof(reg), false);
		APP_ERROR_CHECK(err_code);
		nrf_delay_ms(40);
		NRF_LOG_INFO("configuring=%d\r\n",err_code);
		NRF_LOG_FLUSH();
	}
  return ret;
}

void showNumber(uint8_t number, uint8_t digit) {
  switch (number) {
    case 0:
      writeI2c(_i2caddr[digit], TLC59208_LED_0);
    break;
    case 1:
      writeI2c(_i2caddr[digit], TLC59208_LED_1);
    break;
    case 2:
      writeI2c(_i2caddr[digit], TLC59208_LED_2);
    break;
    case 3:
      writeI2c(_i2caddr[digit], TLC59208_LED_3);
    break;
    case 4:
      writeI2c(_i2caddr[digit], TLC59208_LED_4);
    break;
    case 5:
      writeI2c(_i2caddr[digit], TLC59208_LED_5);
    break;
    case 6:
      writeI2c(_i2caddr[digit], TLC59208_LED_6);
    break;
    case 7:
      writeI2c(_i2caddr[digit], TLC59208_LED_7);
    break;
    case 8:
      writeI2c(_i2caddr[digit], TLC59208_LED_8);
    break;
    case 9:
      writeI2c(_i2caddr[digit], TLC59208_LED_9);
    break;
    default:
      writeI2c(_i2caddr[digit], TLC59208_LED_OFF);
    break;
  }
}

void clearNumber(uint8_t digit) {
  writeI2c(_i2caddr[digit], TLC59208_LED_OFF);
}
void showNumberFullDigit(uint8_t number) {
  uint8_t i;
  for (i=0; i<_digits; i++) {
    if (number <= 0) {
      clearNumber(i);
    } else {
      showNumber(number % 10, i);
    }
    number /= 10;
  }
}

void showDot(uint8_t digit) {
	uint32_t err_code;
	uint8_t reg[2] = {0x05,TLC59208_PWM_VALUE};
	err_code = nrf_drv_twi_tx(&m_twi, _i2caddr[digit], reg, sizeof(reg), false);
	APP_ERROR_CHECK(err_code);
	nrf_delay_ms(40);
}

void clearDot(uint8_t digit) {
	uint32_t err_code;
	uint8_t reg[2] = {0x05,TLC59208_LED_OFF};
	err_code = nrf_drv_twi_tx(&m_twi, _i2caddr[digit], reg, sizeof(reg), false);
	APP_ERROR_CHECK(err_code);
	nrf_delay_ms(40);
}


void showPattern(uint8_t data, uint8_t digit) {
  writeI2c(_i2caddr[digit], data);
}

void writeI2c(uint8_t addr, uint8_t data)
{	
		uint32_t err_code;
	  uint8_t reg[9] = {0xA2,TLC59208_PWM_VALUE,TLC59208_PWM_VALUE,TLC59208_PWM_VALUE,TLC59208_PWM_VALUE,TLC59208_PWM_VALUE,TLC59208_PWM_VALUE,TLC59208_PWM_VALUE,TLC59208_PWM_VALUE};
		for (int i=1; i<9; i++) {
			if ((data>>(i-1)) & 0x01) {
				reg[i] = TLC59208_PWM_VALUE;
			} else {
				reg[i] = TLC59208_LED_OFF;
			}
		}
    err_code = nrf_drv_twi_tx(&m_twi, addr, reg, sizeof(reg), false);
    APP_ERROR_CHECK(err_code);
		nrf_delay_ms(40);
    while (m_xfer_done == false);
}

void twi_handler(nrf_drv_twi_evt_t const * p_event, void * p_context)
{
    switch (p_event->type)
    {
        case NRF_DRV_TWI_EVT_DONE:
            if (p_event->xfer_desc.type == NRF_DRV_TWI_XFER_RX)
            {
                //data_handler(m_sample);
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

    const nrf_drv_twi_config_t twi_mpl115a2_config = {
       .scl                = ARDUINO_SCL_PIN,
       .sda                = ARDUINO_SDA_PIN,
       .frequency          = NRF_TWI_FREQ_100K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
       .clear_bus_init     = false
    };

    err_code = nrf_drv_twi_init(&m_twi, &twi_mpl115a2_config, twi_handler, NULL);
    APP_ERROR_CHECK(err_code);

    nrf_drv_twi_enable(&m_twi);
}



int main(void)
{
    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_INFO("FaBo_211_7Segement Sample\r\n");
    NRF_LOG_FLUSH();
		FaBo7Seg_TLC59208(TLC59208_SLAVE_ADDRESS);
		nrf_delay_ms(40);
    twi_init();
		NRF_LOG_INFO("RESET\r\n");
		NRF_LOG_FLUSH();
		nrf_delay_ms(10);
		NRF_LOG_INFO("configuring device.\r\n");
		NRF_LOG_FLUSH();
		nrf_delay_ms(10);
	
  if (configure()) {
    NRF_LOG_INFO("configured FaBo 7Seg Brick");
		NRF_LOG_FLUSH();
	} else {
    NRF_LOG_INFO("device error");
    NRF_LOG_FLUSH();
		while(1);
  }
	while(1){
		for (int i = 0; i<10; i++) {
			showNumber(i,0); // show a number
			NRF_LOG_INFO("LED: %d\r\n",i);
			NRF_LOG_FLUSH();
			nrf_delay_ms(1000);
		}
	}
}
