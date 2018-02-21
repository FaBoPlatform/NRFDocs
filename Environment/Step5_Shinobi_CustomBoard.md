# Shinobiボード定義

マイコンを使うには様々なピン設定や発振回路設定が必要になります。
LEDピン、ボタン、UARTピンの定義
発振器の定義

#Shinobi回路図
shinobiは１８ピンは、LED、外部水晶32kHz搭載
UARTピン
I2C(TWI)ピン

![](/img/abo_LED_101/Shinobi_Schamtic.PNG)

#ボードの定義

以下のファイルをプロジェクトファイルのどこかに配置します。
サンプルご利用では、こちらを参考にしてください。
https://github.com/FaBoPlatform/NRFDocs/blob/master/brick_analog/101_brick_analog_led.md


custom_borad.h

```c

// Shinobi Dev Board

#ifndef CUSTOM_BOARD_H
#define CUSTOM_BOARD_H

#define LEDS_NUMBER    1
#define LED_1          18
#define LEDS_LIST { LED_1 }
#define LEDS_ACTIVE_STATE 1
#define BSP_LED_0      LED_1
#define BUTTONS_NUMBER 1
#define BUTTON_0       16
#define BUTTONS_ACTIVE_STATE 0
#define BSP_BUTTON_0   BUTTON_0
#define BUTTONS_LIST { BUTTON_0 }
#define BUTTON_PULL    NRF_GPIO_PIN_PULLUP

#define LEDS_INV_MASK  0

#define RX_PIN_NUMBER  9
#define TX_PIN_NUMBER  11
#define CTS_PIN_NUMBER 10
#define RTS_PIN_NUMBER 8
#define HWFC           false

#define SPIS_MISO_PIN  20    // SPI MISO signal.
#define SPIS_CSN_PIN   21    // SPI CSN signal.
#define SPIS_MOSI_PIN  22    // SPI MOSI signal.
#define SPIS_SCK_PIN   23    // SPI SCK signal.

#define SPIM0_SCK_PIN       23u     /**< SPI clock GPIO pin number. */
#define SPIM0_MOSI_PIN      20u     /**< SPI Master Out Slave In GPIO pin number. */
#define SPIM0_MISO_PIN      22u     /**< SPI Master In Slave Out GPIO pin number. */
#define SPIM0_SS_PIN        21u     /**< SPI Slave Select GPIO pin number. */

#define SPIM1_SCK_PIN       29u     /**< SPI clock GPIO pin number. */
#define SPIM1_MOSI_PIN      24u     /**< SPI Master Out Slave In GPIO pin number. */
#define SPIM1_MISO_PIN      28u     /**< SPI Master In Slave Out GPIO pin number. */
#define SPIM1_SS_PIN        25u     /**< SPI Slave Select GPIO pin number. */

// serialization APPLICATION board

// UART
// this configuration works with the SPI wires setup
#define SER_APP_RX_PIN              20     // UART RX pin number.
#define SER_APP_TX_PIN              22     // UART TX pin number.
#define SER_APP_CTS_PIN             23     // UART Clear To Send pin number.
#define SER_APP_RTS_PIN             21     // UART Request To Send pin number.

// serialization CONNECTIVITY board

// UART
#if 0
#define SER_CON_RX_PIN              22    // UART RX pin number.
#define SER_CON_TX_PIN              20    // UART TX pin number.
#define SER_CON_CTS_PIN             21    // UART Clear To Send pin number. Not used if HWFC is set to false.
#define SER_CON_RTS_PIN             23    // UART Request To Send pin number. Not used if HWFC is set to false.
#else
// this configuration works with the SPI wires setup
#define SER_CON_RX_PIN              20    // UART RX pin number.
#define SER_CON_TX_PIN              22    // UART TX pin number.
#define SER_CON_CTS_PIN             21    // UART Clear To Send pin number. Not used if HWFC is set to false.
#define SER_CON_RTS_PIN             23    // UART Request To Send pin number. Not used if HWFC is set to false.
#endif

#define SER_CONN_ASSERT_LED_PIN     LED_0

#define NRF_CLOCK_LFCLKSRC      {.source        = NRF_CLOCK_LF_SRC_XTAL,            \
                                 .rc_ctiv       = 0,                                \
                                 .rc_temp_ctiv  = 0,                                \
                                 .xtal_accuracy = NRF_CLOCK_LF_XTAL_ACCURACY_20_PPM}

#endif

```
