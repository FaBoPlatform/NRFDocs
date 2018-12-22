#include <stdio.h>
#include "boards.h"
#include "app_util_platform.h"
#include "app_uart.h"
#include "app_error.h"
#include "nrf_drv_twi.h"
#include "nrf_delay.h"

#define UART_TX_BUF_SIZE 4096
#define UART_RX_BUF_SIZE 1

//i2c deviceAdress
#define GridEye_DeviceAddress_0 (0x68)
#define GridEye_DeviceAddress_1 (0x69)

//grideye registor
#define REG_PCLT	0x00
#define REG_RST		0x01
#define REG_FPSC	0x02
#define REG_INTC	0x03
#define REG_STAT	0x04
#define REG_SCLR	0x05
#define REG_AVE		0x07
#define REG_INTHL	0x08
#define REG_INTHH	0x09
#define REG_INTLL	0x0A
#define REG_INTLH	0x0B
#define REG_INHYSL	0x0C
#define REG_INHYSH	0x0D
#define REG_TOOL	0x0E
#define REG_TOOH	0x0F
#define REG_INT0	0x10
#define REG_INT1	0x11
#define REG_INT2	0x12
#define REG_INT3	0x13
#define REG_INT4	0x14
#define REG_INT5	0x15
#define REG_INT6	0x16
#define REG_INT7	0x17
#define REG_PIXL	0x80

static volatile bool m_xfer_done = true;
static volatile bool m_set_mode_done = false;
static const nrf_drv_twi_t nrf_drv_twi_grideye = NRF_DRV_TWI_INSTANCE(0);

static int i = 0;
static int pix[64];

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
        UART_BAUDRATE_BAUDRATE_Baud115200
    };

    APP_UART_FIFO_INIT(&comm_params,
                       UART_RX_BUF_SIZE,
                       UART_TX_BUF_SIZE,
                       uart_events_handler,
                       APP_IRQ_PRIORITY_LOW,
                       err_code);

    APP_ERROR_CHECK(err_code);
}

void grideye_set_mode(void)
{
	uint8_t reg =0x0E;
	nrf_drv_twi_tx(&nrf_drv_twi_grideye, GridEye_DeviceAddress_0, &reg, sizeof(reg), true);
  while(m_set_mode_done == false);
}



void twi_handler(nrf_drv_twi_evt_t const * p_event, void * p_context)
{   
    ret_code_t err_code;
		static uint8_t Buf[32];
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
								//receive value
								err_code = nrf_drv_twi_rx(&nrf_drv_twi_grideye, GridEye_DeviceAddress_0, (uint8_t*)&Buf, sizeof(Buf));
								uint16_t j;
								int temp;
								
								static uint16_t h = 0;
								
								for(j=0; j<32; j+=2){
									temp = ((Buf[j + 1] & 0xf) << 8) | Buf[j];
									if(temp > 2047){
										temp = temp - 4096;
									}
									pix[h] = temp;
									h++;
								}
								if (h >63){
										h=0;
										for (int e=0;e<64;e++){
											printf("%.2f,",pix[e] * 0.25);
											if ((e+1)%8 == 0){
												printf("\n\r");
											}
										}		
								}						
										printf("\n\r");
								APP_ERROR_CHECK(err_code);
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
    
    const nrf_drv_twi_config_t twi_grideye_config = {
       .scl                = ARDUINO_SCL_PIN,
       .sda                = ARDUINO_SDA_PIN,
       .frequency          = NRF_TWI_FREQ_100K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH
    };
    
    err_code = nrf_drv_twi_init(&nrf_drv_twi_grideye, &twi_grideye_config, twi_handler, NULL);
    APP_ERROR_CHECK(err_code);
    nrf_drv_twi_enable(&nrf_drv_twi_grideye);
}



int main(void)
{
    uart_config();
    twi_init();
    grideye_set_mode();
		printf("\n\rFabo #226 GridEye,#9 Shinobi SampleCode\r\n");
		nrf_delay_ms(500);
    while(true)
    {
        do
        {
            __WFE();
        }while(m_xfer_done == false);
					uint8_t reg = REG_PIXL + (i * 0x20);
					ret_code_t err_code = nrf_drv_twi_tx(&nrf_drv_twi_grideye, GridEye_DeviceAddress_0, &reg, sizeof(reg), true);
						i++;
				if (4 <= i){
					i = 0;
					printf("\n\r");
					nrf_delay_ms(500);
				}
		}
				
}
