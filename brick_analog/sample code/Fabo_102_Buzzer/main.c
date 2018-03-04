#include <stdio.h>
#include <string.h>
#include "nrf_drv_pwm.h"
#include "app_util_platform.h"
#include "app_error.h"
#include "boards.h"
#include "bsp.h"
#include "app_timer.h"
#include "nrf_drv_clock.h"
#include "nrf_delay.h"

#define APP_TIMER_PRESCALER     0
#define APP_TIMER_OP_QUEUE_SIZE 2

static nrf_drv_pwm_t m_pwm0 = NRF_DRV_PWM_INSTANCE(0);

static void sound(int freq)
{
    uint32_t                   err_code;
    nrf_drv_pwm_config_t config0 =
    {
        .output_pins =
        {
            3 | NRF_DRV_PWM_PIN_INVERTED,
        },
        .irq_priority = APP_IRQ_PRIORITY_LOWEST,
        .base_clock   = NRF_PWM_CLK_1MHz,
        .count_mode   = NRF_PWM_MODE_UP,
        .top_value    = freq,
        .load_mode    = NRF_PWM_LOAD_COMMON,
        .step_mode    = NRF_PWM_STEP_AUTO
    };
		
    err_code = nrf_drv_pwm_init(&m_pwm0, &config0, NULL);
    APP_ERROR_CHECK(err_code);
		
    // This array cannot be allocated on stack (hence "static") and it must
    // be in RAM.
    static nrf_pwm_values_common_t seq0_values[2];
    nrf_pwm_sequence_t const       seq0 =
    {
        .values.p_common = seq0_values,
        .length          = NRF_PWM_VALUES_LENGTH(seq0_values),
        .repeats         = 100,
        .end_delay       = 0
    };
        seq0_values[0] = freq / 2;	
			nrf_drv_pwm_simple_playback(&m_pwm0, &seq0, 1,
                                NRF_DRV_PWM_FLAG_LOOP);
}



int main(void)
{  
    while(1){
		sound(3822);
		nrf_delay_ms(200);
    nrf_drv_pwm_uninit(&m_pwm0);
		sound(3405);
		nrf_delay_ms(200);
    nrf_drv_pwm_uninit(&m_pwm0);
		sound(3033);
		nrf_delay_ms(200);
    nrf_drv_pwm_uninit(&m_pwm0);
		sound(2863);
		nrf_delay_ms(200);
    nrf_drv_pwm_uninit(&m_pwm0);
		sound(2551);
		nrf_delay_ms(200);
		nrf_drv_pwm_uninit(&m_pwm0);
		sound(2272);
		nrf_delay_ms(200);
		nrf_drv_pwm_uninit(&m_pwm0);
		sound(2024);
		nrf_delay_ms(200);
		nrf_drv_pwm_uninit(&m_pwm0);
		sound(1911);
		nrf_delay_ms(200);
		nrf_drv_pwm_uninit(&m_pwm0);
		nrf_delay_ms(1000);
	}
		
}
