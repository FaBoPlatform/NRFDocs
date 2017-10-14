# #5 Shinobi Motor

## Overview
DRV8830を2個搭載したモータードライバーです。

DCモーターをI2Cで制御します。Nordic NRF51,NRF5152ではI2CをTWI（Two Wire Interface）という名称になります。

## Connecting
Shibobi NRF #1 とShinobi Motor #5 をFabo 4Pinケーブルを使用しI2Cコネクタへ接続します。
DCモーターは電源に合わせてご使用ください。状況を見たい場合は、Fabo #304 USBシリアルをShnibi #1 NRFのSerial端子に4Pinケーブルを用いて接続してください。

## Sample Code
ファームウェア実行後、２つのモーターが前進、バックします。
ソフトデバイス不要
必要なソフトウェアコンポーネントを以下チェックおよび選択してください。
Board Support--> bsp
CMSIS --> CORE
Device --> Startup
nRF Drivers --> app_uart Fifoを選択
nRF Drivers --> nrf_delay
nRF Drivers --> nrf_drv_common
nRF Drivers --> nrf_drv_twi
nRF Drivers --> nrf_drv_uart
nRF Drivers --> nrf_error No SoftwareDivceを選択
nRF Drivers --> nrf_gpio
nRF Drivers --> nrf_twi
nRF Drivers --> nrf_uart
nRF Drivers --> nrf_uarte
nRF Library --> app_error
nRF Library --> app_fifo
nRF Library --> app_util
nRF Library --> nordic_common
nRF Library --> nrf_assert
nRF Library --> retarget


```c
#include <stdio.h>
#include "boards.h"
#include "app_uart.h"
#include "app_error.h"
#include "nrf_drv_twi.h"
#include "nrf_delay.h"

#define ARDUINO_I2C_SCL_PIN 27
#define ARDUINO_I2C_SDA_PIN 26
#define UART_TX_BUF_SIZE 256
#define UART_RX_BUF_SIZE 1
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

/* TWI instance. */
static const nrf_drv_twi_t m_twi_DRV8830 = NRF_DRV_TWI_INSTANCE(0);

static void uart_events_handler(app_uart_evt_t * p_event)
{
    switch (p_event->evt_type)
    {
        case APP_UART_COMMUNICATION_ERROR:
            APP_ERROR_HANDLER(p_event->data.error_communication);
            break;

        case APP_UART_FIFO_ERROR:
            APP_ERROR_HANDLER(p_event->data.error_code);
            break;

        default:
            break;
    }
}

static void uart_config(void)
{
    uint32_t                     err_code;
    const app_uart_comm_params_t comm_params =
    {
        RX_PIN_NUMBER,
        TX_PIN_NUMBER,
        RTS_PIN_NUMBER,
        CTS_PIN_NUMBER,
        APP_UART_FLOW_CONTROL_DISABLED,
        false,
        UART_BAUDRATE_BAUDRATE_Baud38400
    };

    APP_UART_FIFO_INIT(&comm_params,
                       UART_RX_BUF_SIZE,
                       UART_TX_BUF_SIZE,
                       uart_events_handler,
                       APP_IRQ_PRIORITY_LOW,
                       err_code);

    APP_ERROR_CHECK(err_code);
}

void twi_handler(nrf_drv_twi_evt_t const * p_event, void * p_context)
{   

}

void twi_init (void)
{
    ret_code_t err_code;

    const nrf_drv_twi_config_t twi_DRV8830_config = {
       .scl                = ARDUINO_SCL_PIN,
       .sda                = ARDUINO_SDA_PIN,
       .frequency          = NRF_TWI_FREQ_100K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH
    };
    err_code = nrf_drv_twi_init(&m_twi_DRV8830, &twi_DRV8830_config, twi_handler, NULL);
		APP_ERROR_CHECK(err_code);

    nrf_drv_twi_enable(&m_twi_DRV8830);
}


int main(void)
{
    uart_config();
    twi_init();
		printf("\n\r****************************************\r\n");
		printf("*Fabo Shinobi Motor beta Firmware      *\r\n");
		printf("*Fabo 2017                             *\r\n");
		printf("*Version 0.0.0                         *\r\n");
		printf("****************************************\r\n");

		nrf_delay_ms(300);

    //DVR8830　初期設定
		uint8_t reg[2] = {CONTROL_ADDR,0x00+(0x09<<2)};
    nrf_drv_twi_tx(&m_twi_DRV8830, DRV8830_ADDR_Motor1, reg, sizeof(reg), false);
		nrf_delay_ms(1);
    nrf_drv_twi_tx(&m_twi_DRV8830, DRV8830_ADDR_Motor2, reg, sizeof(reg), false);
		nrf_delay_ms(1000);

		printf("\n\rForward Speed up\r\n");

    //前進
		for (uint8_t i = MIN_VOLTAGE; i <= MAX_VOLTAGE; i++) {
			reg[1] = 0x02+(i<<2);
			nrf_drv_twi_tx(&m_twi_DRV8830, DRV8830_ADDR_Motor1, reg, sizeof(reg), false);
			nrf_delay_ms(1);
			nrf_drv_twi_tx(&m_twi_DRV8830, DRV8830_ADDR_Motor2, reg, sizeof(reg), false);
			printf("Speed=%d\n\r",i);
			nrf_delay_ms(200);
		}

		printf("MAX Speed\n\r");
		nrf_delay_ms(5000);
		printf("\n\rForward Speed down\r\n");

    //後進
		for (uint8_t i = MAX_VOLTAGE; i >= MIN_VOLTAGE; i--) {
			reg[1] = 0x02+(i<<2);
			nrf_drv_twi_tx(&m_twi_DRV8830, DRV8830_ADDR_Motor1, reg, sizeof(reg), false);
			nrf_delay_ms(1);
			nrf_drv_twi_tx(&m_twi_DRV8830, DRV8830_ADDR_Motor2, reg, sizeof(reg), false);
			printf("Speed=%d\n\r",i);
    nrf_delay_ms(200);
		}
		printf("END.\n\r");
		for(;;){

		}
}



```

## 構成Parts


## GitHub
