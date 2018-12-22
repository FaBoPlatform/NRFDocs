#include <stdio.h>
#include "boards.h"
#include "app_util_platform.h"
#include "app_error.h"
#include "nrf_drv_twi.h"
#include "nrf_delay.h"

#define NRF_LOG_MODULE_NAME "FaBo_LCDMini"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

#define TWI_INSTANCE_ID     0
#define AQM0802A_ADDRESS 0x3E
#define CONTRAST 0x25

/* TWI instance. */
static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);

void command(uint8_t c)
{
	ret_code_t err_code;
  uint8_t reg[2] = {0x00, c};
  err_code = nrf_drv_twi_tx(&m_twi, AQM0802A_ADDRESS, reg, sizeof(reg), false);
  APP_ERROR_CHECK(err_code);
	nrf_delay_ms(30);
}

void send(uint8_t	d)
{
	ret_code_t err_code;
  uint8_t reg[2] = {0x40, d};
  err_code = nrf_drv_twi_tx(&m_twi, AQM0802A_ADDRESS, reg, sizeof(reg), false);
  APP_ERROR_CHECK(err_code);
	nrf_delay_ms(30);
}

void lcdprint(char* c)
{
  while(*c != 0){
		send(*c++);
	}		
}


void set_cursor(uint8_t column,uint8_t row){
	switch(row){
		case 0:
			command(column+0x80);
		break;
		case 1:
			command(column+0xc0);
		break;
		default:
		break;
		}
}

void lcd_begin(void)
{
  nrf_delay_ms(30);
	command(0x38);
  command(0x39);
  command(0x14); 
  command(0x70);
  command(0x56);
  command(0x6B); 
	nrf_delay_ms(30);
  command(0x39);
  command(0x0C);
  command(0x01);
	nrf_delay_ms(30);
}

void twi_handler(nrf_drv_twi_evt_t const * p_event, void * p_context)
{
}

void twi_init (void)
{
    ret_code_t err_code;
    const nrf_drv_twi_config_t twi_LCD_Mini_config = {
       .scl                = 27,
       .sda                = 26,
       .frequency          = NRF_TWI_FREQ_100K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
       .clear_bus_init     = false
    };
    err_code = nrf_drv_twi_init(&m_twi, &twi_LCD_Mini_config, twi_handler, NULL);
    APP_ERROR_CHECK(err_code);
    nrf_drv_twi_enable(&m_twi);
}

int main(void)
{
    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_INFO("\r\nFabo LCDMini_213\r\n");
    NRF_LOG_FLUSH();
    twi_init();
		lcd_begin();
		set_cursor(0,0);
		lcdprint("Fabo");
		set_cursor(0,1);
		lcdprint("Shinobi");
    nrf_delay_ms(500);
    while (true)
    {
        NRF_LOG_FLUSH();
    }
}

