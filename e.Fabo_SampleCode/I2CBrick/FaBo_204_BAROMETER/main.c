#include <stdio.h>
#include <math.h>
#include "boards.h"
#include "app_util_platform.h"
#include "app_error.h"
#include "nrf_drv_twi.h"
#include "nrf_delay.h"
#define NRF_LOG_MODULE_NAME "FaBo_204_Barometor"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

#define TWI_INSTANCE_ID     0

#define MPL115A2_SLAVE_ADDRESS 0x60 ///< MPL115A2 I2C slave address

#define MPL115A2_PADC_MSB 0x00
#define MPL115A2_PADC_LSB 0x01
#define MPL115A2_TADC_MSB 0x02
#define MPL115A2_TACD_LSB 0x03
#define MPL115A2_A0_MSB 0x04
#define MPL115A2_A0_LSB 0x05
#define MPL115A2_B1_MSB 0x06
#define MPL115A2_B1_LSB 0x07
#define MPL115A2_B2_MSB 0x08
#define MPL115A2_B2_LSB 0x09
#define MPL115A2_C12_MSB 0x0A
#define MPL115A2_C12_LSB 0x0B
#define MPL115A2_CONVERT 0x12

void begin(void);
void readCoef(void);
void readData(float * hpa, float * temp);
float readHpa(float altitude);
float readTemp(void);
float _a0, _b1, _b2, _c12;
void writeI2c(uint8_t address, uint8_t data);
void readI2c(uint8_t address, uint8_t num,uint8_t *data);

static volatile bool m_xfer_done = false;
static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);
void read_sensor_data(void);

void begin() {
  readCoef();
}

void readCoef() {
  uint8_t data[8];
  readI2c(MPL115A2_A0_MSB, 8, data);
	nrf_delay_ms(1000);
  _a0  = ((float) ((data[2] << 8) + data[1]) / ((long)1 << 3));
  _b1  = ((float) ((data[2] << 8) + data[3]) / ((long)1 << 13));
  _b2  = ((float) ((data[4] << 8) + data[5]) / ((long)1 << 14));
  _c12 = ((float) ((data[6] << 8) + data[7]) / ((long)1 << 24));
}

float readHpa(float altitude) {
  float hpa,temp;
  readData(&hpa,&temp);
  return hpa / pow(1.0F - (altitude/44330.0F), 5.255F);
}


float readTemp() {
  float hpa,temp;
  readData(&hpa,&temp);
  return temp;
}

void readData(float * hpa, float * temp) {
  uint8_t data[4];
  uint16_t padc,tadc;
  float pcomp;
  writeI2c(MPL115A2_CONVERT, 0x01);
  nrf_delay_ms(3);
  readI2c(MPL115A2_PADC_MSB, 4,data);
	nrf_delay_ms(10);
  padc = (((uint16_t)data[0] << 8) | data[1]) >> 6;
  tadc = (((uint16_t)data[2] << 8) | data[3]) >> 6;
  pcomp = _a0 + ( _b1 + _c12 * tadc ) * padc + _b2 * tadc;
  *hpa  = pcomp * ( (1150.0F-500.0F)/1023.0F ) + 500.0F;
  *temp = 25.0F - ((float)tadc - 512.0F ) / 5.35F;
}

void twi_handler(nrf_drv_twi_evt_t const * p_event, void * p_context)
{
    switch (p_event->type)
    {
        case NRF_DRV_TWI_EVT_DONE:
            if (p_event->xfer_desc.type == NRF_DRV_TWI_XFER_RX)
            {
                //data_handler(m_sample);
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

    const nrf_drv_twi_config_t twi_mpl115a2_config = {
       .scl                = ARDUINO_SCL_PIN,
       .sda                = ARDUINO_SDA_PIN,
       .frequency          = NRF_TWI_FREQ_100K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
       .clear_bus_init     = false
    };

    err_code = nrf_drv_twi_init(&m_twi, &twi_mpl115a2_config, twi_handler, NULL);
    APP_ERROR_CHECK(err_code);

    nrf_drv_twi_enable(&m_twi);
}

void writeI2c(uint8_t register_addr, uint8_t value)
{	
		uint32_t err_code;
    uint8_t reg[2] = {register_addr, value};
    err_code = nrf_drv_twi_tx(&m_twi, MPL115A2_SLAVE_ADDRESS, reg, sizeof(reg), false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
}

void readI2c(uint8_t address, uint8_t num,uint8_t *data) {
	uint32_t err_code;
  uint8_t reg[2] = {address, num};
  err_code = nrf_drv_twi_tx(&m_twi, MPL115A2_SLAVE_ADDRESS, reg, sizeof(reg), false);
  APP_ERROR_CHECK(err_code);
  while (m_xfer_done == false);
	nrf_delay_ms(10);
	m_xfer_done = false;
  err_code = nrf_drv_twi_rx(&m_twi, MPL115A2_SLAVE_ADDRESS, data, sizeof(data));
  APP_ERROR_CHECK(err_code);
}

int main(void)
{
    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_INFO("FaBo_Barometor_204 Sample\r\n");
    NRF_LOG_FLUSH();
    twi_init();
		NRF_LOG_INFO("RESET\r\n");
		NRF_LOG_FLUSH();
		nrf_delay_ms(10);
		begin();
		nrf_delay_ms(10);
		NRF_LOG_INFO("Init.\r\n");
		nrf_delay_ms(10);
	while(1){
		float a = readTemp();
		NRF_LOG_INFO("Temp:ÅÅ " NRF_LOG_FLOAT_MARKER "\r\n", NRF_LOG_FLOAT(a));
		nrf_delay_ms(100);
		float b = readHpa(212.0F);
		NRF_LOG_INFO("hPa: " NRF_LOG_FLOAT_MARKER "\r\n", NRF_LOG_FLOAT(b));
		nrf_delay_ms(1000);
		NRF_LOG_FLUSH();
	}
}
