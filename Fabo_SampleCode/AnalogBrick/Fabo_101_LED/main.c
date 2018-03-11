#include "nrf.h"
#include "bsp.h"
#include "nrf_delay.h"

#define FaBo_Shinobi_ANALOGPIN 3

static void gpio_init(void)
{
	nrf_gpio_cfg_output(FaBo_Shinobi_ANALOGPIN);
}

int main(void)
{
	gpio_init();
	while(1){
					nrf_gpio_pin_set(FaBo_Shinobi_ANALOGPIN);
					nrf_delay_ms(1000);
					nrf_gpio_pin_clear(FaBo_Shinobi_ANALOGPIN);
					nrf_delay_ms(1000);
    }
}

