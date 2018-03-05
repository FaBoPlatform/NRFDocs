# #4 Shinobi_Motor

![](..\img\Shinobi_Motor\Shinobi_Motor.JPG)
<!--COLORME-->

## Overview
DRV8830を2個搭載したモータードライバーです。

DCモーターをI2Cで制御します。Nordic NRF51,NRF5152ではI2CをTWI（Two Wire Interface）という名称になります。

## Connecting
Shibobi NRF #1 とShinobi Motor #5 をFabo 4Pinケーブルを使用しI2Cコネクタへ接続します。
DCモーターは電源に合わせてご使用ください。状況を見たい場合は、Fabo #304 USBシリアルをShnibi #1 NRFのSerial端子に4Pinケーブルを用いて接続してください。

## Sample Code

ファームウェア実行後、２つのモーターが回転します。
ソフトデバイス不要
必要なソフトウェアコンポーネントを以下チェックおよび選択してください。

```c
#include <stdio.h>
#include "boards.h"
#include "app_util_platform.h"
#include "app_error.h"
#include "nrf_drv_twi.h"
#include "nrf_delay.h"

#define NRF_LOG_MODULE_NAME "Shinobi_Motor"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

#define TWI_INSTANCE_ID     0

#define DRV8830_ADDR_Motor1	0x64
#define DRV8830_ADDR_Motor2	0x63
#define CONTROL_ADDR   0x00
#define FALUT_ADR		   0x01
#define MOTOR_STANBY  0x00  
#define MOTOR_REVERSE 0x01
#define MOTOR_NORMAL  0x02
#define MOTOR_BRAKE   0x03
#define MAX_VOLTAGE 0x3F
#define MIN_VOLTAGE 0x01

static const nrf_drv_twi_t m_twi_DRV8830 = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);

void twi_handler(nrf_drv_twi_evt_t const * p_event, void * p_context)
{
    switch (p_event->type)
    {
        case NRF_DRV_TWI_EVT_DONE:
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

    err_code = nrf_drv_twi_init(&m_twi_DRV8830, &twi_lm75b_config, twi_handler, NULL);
    APP_ERROR_CHECK(err_code);

    nrf_drv_twi_enable(&m_twi_DRV8830);
}

int main(void)
{
    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));

    NRF_LOG_INFO("\r\nShinobi_Motor_5 Sample\r\n");
    NRF_LOG_FLUSH();
    twi_init();

		uint8_t reg[2] = {CONTROL_ADDR,0x00+(0x09<<2)};
    nrf_drv_twi_tx(&m_twi_DRV8830, DRV8830_ADDR_Motor1, reg, sizeof(reg), false);
		nrf_delay_ms(5);
    nrf_drv_twi_tx(&m_twi_DRV8830, DRV8830_ADDR_Motor2, reg, sizeof(reg), false);
		nrf_delay_ms(1000);

		for (uint8_t i = MIN_VOLTAGE; i <= MAX_VOLTAGE; i++) {
			reg[1] = 0x02+(i<<2);
			nrf_drv_twi_tx(&m_twi_DRV8830, DRV8830_ADDR_Motor1, reg, sizeof(reg), false);
			nrf_delay_ms(10);
			nrf_drv_twi_tx(&	m_twi_DRV8830, DRV8830_ADDR_Motor2, reg, sizeof(reg), false);
			nrf_delay_ms(200);
		}

		for (uint8_t i = MAX_VOLTAGE; i >= MIN_VOLTAGE; i--) {
			reg[1] = 0x02+(i<<2);
			nrf_drv_twi_tx(&m_twi_DRV8830, DRV8830_ADDR_Motor1, reg, sizeof(reg), false);
			nrf_delay_ms(10);
			nrf_drv_twi_tx(&m_twi_DRV8830, DRV8830_ADDR_Motor2, reg, sizeof(reg), false);
			nrf_delay_ms(200);
		}

		NRF_LOG_INFO("\r\nEND.\r\n");
		NRF_LOG_FLUSH();

    while (true)
    {

    }
}

```
