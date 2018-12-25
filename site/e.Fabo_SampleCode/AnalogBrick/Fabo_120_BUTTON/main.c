#include <stdbool.h>
#include <stdint.h>

#include "nrf.h"
#include "bsp.h"
#include "app_timer.h"
#include "app_error.h"
#include "nrf_drv_wdt.h"
#include "nrf_drv_clock.h"
#include "nrf_delay.h"
#include "app_util_platform.h"

#define NRF_LOG_MODULE_NAME "FaBo_120_BUTTON"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

#define APP_TIMER_PRESCALER     0                          
#define APP_TIMER_OP_QUEUE_SIZE 2                           
#define FEED_BUTTON_ID          0                          

nrf_drv_wdt_channel_id m_channel_id;


void wdt_event_handler(void)
{
    bsp_board_leds_off();
    //NOTE: The max amount of time we can spend in WDT interrupt is two cycles of 32768[Hz] clock - after that, reset occurs
}

void app_error_fault_handler(uint32_t id, uint32_t pc, uint32_t info)
{
    bsp_board_leds_off();
    while (1);
}

/**
 * @brief BSP events callback.
 */
void bsp_event_callback(bsp_event_t event)
{
    switch (event)
    {
        case BSP_EVENT_KEY_0:
            nrf_drv_wdt_channel_feed(m_channel_id);
						NRF_LOG_INFO("Button PUSH!\r\n");
            break;

        default :
            //Do nothing.
            break;
    }
}


int main(void)
{
		uint32_t err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);

		NRF_LOG_INFO("Fabo Shinobi_Sample_BUTTON 120\r\n");
	

    //BSP configuration for button support: button pushing will feed the dog.
    err_code = nrf_drv_clock_init();
    APP_ERROR_CHECK(err_code);
    nrf_drv_clock_lfclk_request(NULL);

    APP_TIMER_INIT(APP_TIMER_PRESCALER, APP_TIMER_OP_QUEUE_SIZE, false);
    err_code = bsp_init(BSP_INIT_BUTTONS, APP_TIMER_TICKS(100, APP_TIMER_PRESCALER), bsp_event_callback);
    APP_ERROR_CHECK(err_code);

    //Configure all LEDs on board.
    bsp_board_leds_init();

    //Configure WDT.
    nrf_drv_wdt_config_t config = NRF_DRV_WDT_DEAFULT_CONFIG;
    err_code = nrf_drv_wdt_init(&config, wdt_event_handler);
    APP_ERROR_CHECK(err_code);
    err_code = nrf_drv_wdt_channel_alloc(&m_channel_id);
    APP_ERROR_CHECK(err_code);
    nrf_drv_wdt_enable();

    //Indicate program start on LEDs.
    for (uint32_t i = 0; i < LEDS_NUMBER; i++)
    {   nrf_delay_ms(200);
        bsp_board_led_on(i);
    }
     err_code = bsp_buttons_enable();
     APP_ERROR_CHECK(err_code);

    while (1)
    {
        __SEV();
        __WFE();
        __WFE();
				NRF_LOG_FLUSH();
    }
}

