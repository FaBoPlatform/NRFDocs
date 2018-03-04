# #120 Button Brick

## Overview
ボタンを使ったBrickです。I/OピンよりボタンのON/OFFの状態を取得することができます。

※ボタンカバー部分の色はランダムで送付するため色のご指定はできません。あらかじめご了承ください。

## Connecting


## Schematic


## Sample Code

ウォッチタイマーのサンプル。
LEDが点灯後２秒経過前に押さないとリセットがかかるサンプルコードです。

Shinobi_NRFの３ピンの設定をボタンに変えます。

PCA10040.hのファイルを

\#define BUTTON_1       3に変更します。

```c

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

#define NRF_LOG_MODULE_NAME "FABO ANGLE"
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

		NRF_LOG_INFO("Fabo Shinobi Sample BUTTON 120\r\n");


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
```

```c
#include "boards.h"
#include "app_uart.h"
#include "bsp.h"
#include "app_timer.h"
#include "nrf_drv_clock.h"

//UARTのバッファサイズを定義
#define UART_TX_BUF_SIZE        256
#define UART_RX_BUF_SIZE        1

#define APP_TIMER_PRESCALER     0
#define APP_TIMER_OP_QUEUE_SIZE 2

#define PinNumberA0 3

const uint8_t led_pin = PinNumberA0;

//LEDを点灯
static void TurnON(void)
{
    printf("TurnON\r\n");
		NRF_GPIO->OUTCLR = (1 << led_pin) & ((1 << led_pin) & led_pin);
    NRF_GPIO->OUTSET = (1 << led_pin) & ((1 << led_pin) & ~led_pin);
}

//LEDを消灯
static void TurnOFF(void)
{
    printf("TurnOFF\r\n");
		NRF_GPIO->OUTSET = (1 << led_pin) & ((1 << led_pin) & led_pin);
    NRF_GPIO->OUTCLR = (1 << led_pin) & ((1 << led_pin) & ~led_pin);
}		
//ボタンが押された場合のハンドラー
static void bsp_evt_handler(bsp_event_t evt)
{
    void (* const SwichState[])(void) =
    {
        TurnON,
        TurnOFF
    };
    uint8_t const SwichState_index_max = (sizeof(SwichState)/sizeof(SwichState[0])) - 1;
    static uint8_t SwichState_index = 0;
		static uint32_t count = 0;

		printf("\n\rcounter=%d\n\r",count);
		count++;

    switch (evt)
    {
        case BSP_EVENT_KEY_0:
            if (SwichState_index > 0)
            {
                --SwichState_index;
								printf("KeyEvent=BSP_EVENT_KEY_0\n\r");
							LEDS_ON(LEDS_MASK);
            }
            else
            {
								printf("KeyEvent=BSP_EVENT_KEY_0\n\r");
                SwichState_index = SwichState_index_max;
            }
            break;

        case BSP_EVENT_KEY_1:
            if (SwichState_index < SwichState_index_max)
            {
                ++SwichState_index;
							printf("KeyEvent=BSP_EVENT_KEY_1\n\r");
            }
            else
            {
								printf("KeyEvent=BSP_EVENT_KEY_1\n\r");
                SwichState_index = 0;
            }
						break;
				case BSP_EVENT_KEY_2:
						printf("KeyEvent=BSP_EVENT_KEY_2\n\r");
						break;
				case BSP_EVENT_KEY_3:
						printf("KeyEvent=BSP_EVENT_KEY_3\n\r");
            break;
        default:
            return;
    }
    SwichState[SwichState_index]();
}

static void init_bsp()
{
    uint32_t err_code;

    err_code = nrf_drv_clock_init();
    APP_ERROR_CHECK(err_code);
    nrf_drv_clock_lfclk_request(NULL);

    APP_TIMER_INIT(APP_TIMER_PRESCALER, APP_TIMER_OP_QUEUE_SIZE, false);
    err_code = bsp_init(BSP_INIT_BUTTONS,
        APP_TIMER_TICKS(100, APP_TIMER_PRESCALER), bsp_evt_handler);
    APP_ERROR_CHECK(err_code);

    err_code = bsp_buttons_enable();
    APP_ERROR_CHECK(err_code);
}


static void uart_event_handler(app_uart_evt_t * p_event)
{
    // This function is required by APP_UART_FIFO_INIT, but we don't need to
    // handle any events here.
}
static void init_uart(void)
{
    uint32_t err_code;

//ボーレートは38400bps　フロー制御なし。

    app_uart_comm_params_t const comm_params =
    {
        .rx_pin_no    = RX_PIN_NUMBER,
        .tx_pin_no    = TX_PIN_NUMBER,
        .rts_pin_no   = RTS_PIN_NUMBER,
        .cts_pin_no   = CTS_PIN_NUMBER,
        .flow_control = APP_UART_FLOW_CONTROL_DISABLED,
        .use_parity   = false,
        .baud_rate    = UART_BAUDRATE_BAUDRATE_Baud38400
    };

    APP_UART_FIFO_INIT(&comm_params,
                       UART_RX_BUF_SIZE,
                       UART_TX_BUF_SIZE,
                       uart_event_handler,
                       APP_IRQ_PRIORITY_LOW,
                       err_code);
    APP_ERROR_CHECK(err_code);
}

int main(void)
{
		LEDS_CONFIGURE(1 << PinNumberA0);

    init_bsp();

    init_uart();

    printf("\r\nFabo#120Button Example.");

    for (;;)
    {
        //イベントを待機する
        __WFE();

        //レジスタのクリア
        __SEV();
        __WFE();
    }
}

```

リセットボタンを押して、ターミナルソフトで確認します。



## 構成Parts
- 12mm角タクトスイッチ

## GitHub
- https://github.com/FaBoPlatform/FaBo/tree/master/103_button
