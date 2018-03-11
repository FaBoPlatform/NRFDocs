#include <stdbool.h>
#include <stdint.h>
#include "nrf.h"
#include "bsp.h"
#include "nrf_delay.h"
#include "app_util_platform.h"

#define NRF_LOG_MODULE_NAME "FaBo_110_TILT"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

#define FaBo_Shinobi_ANALOGPIN 3
#define FaBo_Shinobi_LEDPIN 18

static void gpio_init(void)
{
	nrf_gpio_cfg_sense_input(FaBo_Shinobi_ANALOGPIN, NRF_GPIO_PIN_PULLDOWN, NRF_GPIO_PIN_SENSE_HIGH);
	nrf_gpio_cfg_output(FaBo_Shinobi_LEDPIN);
	nrf_gpio_pin_clear(FaBo_Shinobi_LEDPIN);
}

int main(void)
{
		uint32_t err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);
		gpio_init();
	
    while (true)
    {
				uint32_t TILT_PIN = 0;
				TILT_PIN = nrf_gpio_pin_read(FaBo_Shinobi_ANALOGPIN);
			
				if (TILT_PIN == 1) {
					nrf_gpio_pin_set(FaBo_Shinobi_LEDPIN);
					NRF_LOG_INFO("Detect Slope.\r\n");
					NRF_LOG_FLUSH();
				}
				else {
					nrf_gpio_pin_clear(FaBo_Shinobi_LEDPIN);
				}
    }
		
}

