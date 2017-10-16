# #202 9Aixs I2C Brick

## Overview



## Connecting

ShinobiとFabo 9Axisを接続。

##必要なソフトウェアコンポーネント

以下のソフトウェアコンポーネントをチェックおよび選択します。

Board Support --> bsp Defineに設定
CMSIS --> CORE
Devie --> Startup
nRF_Drivers --> app_uart FIFOに設定
nRF_Drivers --> nrf_delay
nRF Drivers --> nrf_drv_commmon
nRF Drivers --> nrf_drv_uart
nRF Drivers --> nrf_error No_softdeviceを選択
nRF Drivers --> nrf_gpio
nRF Drivers --> nrf_twi
nRF Drivers --> nrf_uart
nRF Drivers --> nrf_uarte

nRF_Libraries --> app_error
nRF_Libraries --> app_fifp
nRF_Libraries --> app_util No_softdeviceを選択
nRF_Libraries --> nordic_common
nRF_Libraries --> nrf_assert
nRF_Libraries --> retarget


```c
#include <stdio.h>
#include "boards.h"
#include "app_util_platform.h"
#include "app_uart.h"
#include "app_error.h"
#include "nrf_drv_twi.h"
#include "nrf_delay.h"

#define UART_TX_BUF_SIZE 256
#define UART_RX_BUF_SIZE 1

#define    DEVICEADDRESS_MPU9250			0x68
#define    DEVICEADDRESS_MAG 					0x0C

#define    GYRO_FULL_SCALE_250_DPS    0x00  
#define    GYRO_FULL_SCALE_500_DPS    0x08
#define    GYRO_FULL_SCALE_1000_DPS   0x10
#define    GYRO_FULL_SCALE_2000_DPS   0x18

#define    ACC_FULL_SCALE_2_G        0x00  
#define    ACC_FULL_SCALE_4_G        0x08
#define    ACC_FULL_SCALE_8_G        0x10
#define    ACC_FULL_SCALE_16_G       0x18

/* Indicates if reading operation from accelerometer has ended. */
static volatile bool m_xfer_done = true;
/* Indicates if setting mode operation has ended. */
static volatile bool m_set_mode_done = false;
/* TWI instance. */
static const nrf_drv_twi_t m_twi_mpu_9250 = NRF_DRV_TWI_INSTANCE(0);

static volatile uint8_t twi_number = 0;

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

void MPU9250_set_mode(void)
{
    ret_code_t err_code;
    uint8_t reg[2] = {GYRO_FULL_SCALE_2000_DPS,27};
    err_code = nrf_drv_twi_tx(&m_twi_mpu_9250, DEVICEADDRESS_MPU9250, reg, sizeof(reg), false);  
    APP_ERROR_CHECK(err_code);
		nrf_delay_ms(10);
		uint8_t reg2[2] = {ACC_FULL_SCALE_16_G,28};
    err_code = nrf_drv_twi_tx(&m_twi_mpu_9250, DEVICEADDRESS_MPU9250, reg2, sizeof(reg2), false);
		nrf_delay_ms(10);
		uint8_t reg3[2] = {0x37,0x02};
    err_code = nrf_drv_twi_tx(&m_twi_mpu_9250, DEVICEADDRESS_MPU9250, reg3, sizeof(reg3), false);
    nrf_delay_ms(10);

    while(m_set_mode_done == false);
}

void twi_handler(nrf_drv_twi_evt_t const * p_event, void * p_context)
{   
    ret_code_t err_code;
		static uint8_t Buf[14];
		static uint8_t Mag[6];

    switch(p_event->type)
    {
        case NRF_DRV_TWI_EVT_DONE:
            if ((p_event->type == NRF_DRV_TWI_EVT_DONE) &&
                (p_event->xfer_desc.type == NRF_DRV_TWI_XFER_TX))
            {
                if(m_set_mode_done != true)
                {
                    m_set_mode_done  = true;
                    return;
                }
                m_xfer_done = false;
									err_code = nrf_drv_twi_rx(&m_twi_mpu_9250, DEVICEADDRESS_MPU9250, (uint8_t*)&Buf, sizeof(Buf));
									//err_code = nrf_drv_twi_rx(&m_twi_mpu_9250, DEVICEADDRESS_MAG, (uint8_t*)&Mag, sizeof(Mag));
								APP_ERROR_CHECK(err_code);
								// Accelerometer
								int16_t ax=-(Buf[0]<<8 | Buf[1]);
								int16_t ay=-(Buf[2]<<8 | Buf[3]);
								int16_t az=Buf[4]<<8 | Buf[5];

								// Gyroscope
								int16_t gx=-(Buf[8]<<8 | Buf[9]);
								int16_t gy=-(Buf[10]<<8 | Buf[11]);
								int16_t gz=Buf[12]<<8 | Buf[13];

								printf("Accelerometer\n\r");
								printf("ax=%d \t ay=%d \t az=%d\n\r",ax,ay,az);
								printf("Gyroscope\n\r");
								printf("gx=%d \t gy=%d \t gz=%d\n\r",gx,gy,gz);

								// Magnetometer
								int16_t mx=-(Mag[3]<<8 | Mag[2]);
								int16_t my=-(Mag[1]<<8 | Mag[0]);
								int16_t mz=-(Mag[5]<<8 | Mag[4]);

								printf("Magnetometer\n\r");
								printf("mx=%d \t my=%d \t mz=%d\n\r",mx,my,mz);
            }
            else
            {

                m_xfer_done = true;
            }
            break;
        default:
            break;        
    }   
}

void twi_init (void)
{
    ret_code_t err_code;

    const nrf_drv_twi_config_t twi_mpu_9250_config = {
       .scl                = ARDUINO_SCL_PIN,
       .sda                = ARDUINO_SDA_PIN,
       .frequency          = NRF_TWI_FREQ_100K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH
    };

    err_code = nrf_drv_twi_init(&m_twi_mpu_9250, &twi_mpu_9250_config, twi_handler, NULL);
    APP_ERROR_CHECK(err_code);

    nrf_drv_twi_enable(&m_twi_mpu_9250);
}

int main(void)
{
    uart_config();
    printf("\n\rFabo #202 9Aix Sample Beta\r\n");
    twi_init();
    MPU9250_set_mode();

    ret_code_t err_code;

    while(true)
    {
        nrf_delay_ms(1000);
        do
        {
            __WFE();
        }while(m_xfer_done == false);

				uint8_t reg9 =0x3B;
				err_code = nrf_drv_twi_tx(&m_twi_mpu_9250, DEVICEADDRESS_MPU9250, &reg9, sizeof(reg9), true);
				//nrf_delay_ms(100);
				//uint8_t reg7[2] ={0x0A,0x01};
				//err_code = nrf_drv_twi_tx(&m_twi_mpu_9250, DEVICEADDRESS_MAG, reg7, sizeof(reg7), true);
				//nrf_delay_ms(100);
				//uint8_t reg5 = 0x03;
				//err_code = nrf_drv_twi_tx(&m_twi_mpu_9250, DEVICEADDRESS_MAG, &reg5, sizeof(reg5), true);
        m_xfer_done = false;
    }
}


```


## 構成Parts
-

## GitHub
