#include <stdio.h>
#include "boards.h"
#include "app_util_platform.h"
#include "app_error.h"
#include "nrf_drv_twi.h"
#include "nrf_delay.h"

#define NRF_LOG_MODULE_NAME "GridEye"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

/* TWI instance ID. */
#define TWI_INSTANCE_ID     0

/* Common addresses definition for temperature sensor. */
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


/* Indicates if operation on TWI has ended. */
static volatile bool m_xfer_done = false;

/* TWI instance. */
static const nrf_drv_twi_t nrf_drv_twi_grideye = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);

/* Buffer for samples read from temperature sensor. */
static uint8_t m_sample[32];

static uint8_t packet_id = 0;

void GridEye_Set(void)
{
		NRF_LOG_INFO("\r\nSetmode\r\n");
		
    ret_code_t err_code;		
		uint8_t reg_fps[2] = {REG_FPSC,0x01};
		err_code = nrf_drv_twi_tx(&nrf_drv_twi_grideye, GridEye_DeviceAddress_0, reg_fps, sizeof(reg_fps), true);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
}

void GridEye_Command(uint8_t pix)
{
		int pix_num[4] = {0,1,2,3};
		NRF_LOG_INFO("\r\nGridEye_Command:%d\r\n",pix);
    ret_code_t err_code;
    m_xfer_done = false;
		uint8_t reg_pixl = REG_PIXL + (pix_num[pix] * 0x20);
		err_code = nrf_drv_twi_tx(&nrf_drv_twi_grideye, GridEye_DeviceAddress_0, &reg_pixl, sizeof(reg_pixl), true);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
}


void tempConvert(uint8_t sample[32]){
	
		static int16_t temp;
		static uint8_t tempc;
		static uint8_t pixcel_index;
		static uint8_t pixcel[64];
	
	for(int j=0; j<32; j+=2){
				temp = (int8_t)((sample[j + 1] & 0xf) << 8) | sample[j];
					pixcel[pixcel_index] = temp;
					NRF_LOG_INFO("pixcel_index=%d\r\n",pixcel_index);
					pixcel_index++;
					if (pixcel_index > 63){
						pixcel_index = 0;
					}
				
				}
				for(int i = 0;i<64;i++){
					NRF_LOG_INFO("%d=%d\r\n", i,pixcel[i]);
				}
}


/**
 * @brief Function for handling data from temperature sensor.
 *
 * @param[in] temp          Temperature in Celsius degrees read from sensor.
 */
__STATIC_INLINE void data_handler(uint8_t tempSample[32])
{
		static uint32_t receive_count;
		tempConvert(tempSample);
		receive_count++;
	}

/**
 * @brief TWI events handler.
 */
void twi_handler(nrf_drv_twi_evt_t const * p_event, void * p_context)
{
    switch (p_event->type)
    {
        case NRF_DRV_TWI_EVT_DONE:
            if (p_event->xfer_desc.type == NRF_DRV_TWI_XFER_RX)
            {
                data_handler(m_sample);
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

    const nrf_drv_twi_config_t twi_grideye_config = {
       .scl                = ARDUINO_SCL_PIN,
       .sda                = ARDUINO_SDA_PIN,
       .frequency          = NRF_TWI_FREQ_100K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
       .clear_bus_init     = false
    };

    err_code = nrf_drv_twi_init(&nrf_drv_twi_grideye, &twi_grideye_config, twi_handler, NULL);
    APP_ERROR_CHECK(err_code);

    nrf_drv_twi_enable(&nrf_drv_twi_grideye);
}

/**
 * @brief Function for reading data from temperature sensor.
 */
static void read_sensor_data()
{
    m_xfer_done = false;
    ret_code_t err_code = nrf_drv_twi_rx(&nrf_drv_twi_grideye, GridEye_DeviceAddress_0, (uint8_t*)&m_sample, sizeof(m_sample));
		NRF_LOG_INFO("\r\nCensor READ:%d\r\n",packet_id);
		APP_ERROR_CHECK(err_code);
}

/**
 * @brief Function for main application entry.
 */
int main(void)
{
    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));

    NRF_LOG_INFO("\r\nTWI sensor example\r\n");
    NRF_LOG_FLUSH();
    twi_init();
    GridEye_Set();
	
    while (true)
    {
        GridEye_Command(packet_id);
				packet_id++;
				if (3 < packet_id){
					packet_id = 0;
				}
				GridEye_Command(packet_id);

        do
        {
            __WFE();
        }while (m_xfer_done == false);
        read_sensor_data();
        NRF_LOG_FLUSH();
				nrf_delay_ms(200);
    }
}

/** @} */
