# #101 LED Brick

![](/img/101/led001.jpg)
<!--COLORME-->

## Overview
LEDのBrickです。発光色は5色（青・緑・赤・白・黄）あります。Lチカのおともにもどうぞ。

## Connecting
接続例：J-Linke LiteをShinobi_NRF、USB電源をShinobiBatterry,Fabo1010をShinobiアナログコネクタに接続します。

![](/img/101/led002.jpg)

## Schematic

Fabo 101 LEDの回路図
![](/img/101/led003.png)

Shinobi NRFの回路図
![](/img/101/led004.png)

## Sample Code
Arduino Motor ShieldのA0コネクタにLED Brickを接続し、一定時間(1秒=1000ms)ごとに点灯/消灯（Lチカ）させています。

## １．Keilを起動

任意の場所プロジェクトフォルダの中にLED101のフォルダを作成します。
Project → New μ プロジェクト → プロジェクトファイルを保存します。

![](/img/101/led005.png)

プロジェクトファイルが作成され。

## ２．デバイスの選択

ターゲットとなるマイコンを選択します。Nordic Semiconductorを選択。
![](/img/101/led006.png)

nRF52　Series→nRF528232_xxAAを選択します。
![](/img/101/led007.jpg)

## ３．コンポーネントを選択

MagageRunTimeEnviromentボタンをクリックします。

![](/img/101/led008.png)

マイコン起動に必要なコンポーネントを選択します。

![](/img/101/led009.png)

依存性を解消します。

![](/img/101/led010.png)

## 4．フォルダの構成

管理しやすいように名前を以下のようにします。

![](/img/101/led011.png)

フォルダ名をsrcに変更します。

configフォルダを作成します。

![](/img/101/led013.png)

![](/img/101/led014.png)

## 5. custom_board.h の作成

configフォルダにcustom_board.hを追加します。

![](/img/101/led015.png)

![](/img/101/led016.png)

![](/img/101/led017.png)

config/custom_board.h
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

## 6. sdk_condig.hの取り込み

configフォルダに、[SDK Root]/examples/ble_peripheral/ble_app_template/pca10040/s132/config/sdk_config.hをプロジェクトフォルダにコピーし、Keil上に取り込みます。

![](/img/101/led018.png)

![](/img/101/led019.png)

![](/img/101/led020.png)


コンパイルするモジュールを指定します。

![](/img/Fabo_LED_101/Configration_Wizard101.PNG)

SDK_confing.hを選択し下のconfigration_Wizardタブをクリック。

以下をチェックします。

![](/img/Fabo_LED_101/Configration_anotation101.PNG)

※SDK configuration header file について
https://infocenter.nordicsemi.com/index.jsp?topic=%2Fcom.nordic.infocenter.sdk5.v12.0.0%2Fsdk_config.html


## 7．インクルードファイルの設定

Option for Targetボタンを押し、

![](/img/101/led021.png)

C/C++をクリックします。Include Pathsの右のボタンをクリックします。

![](/img/101/led022.png)

ボタンを押して逐次ヘッダファイルがあるパスを追加します。
選択されると以下のようになります。

![](/img/101/led023.png)

|フォルダ|必要なHeader File|
|:--|:--|
|プロジェクトのRootパス|自分自身へのパス|
|nRF5_SDK_12.3.0_d7731ad/components/drivers_nrf/hal/ |nrf_gpio.h|
|nRF5_SDK_12.3.0_d7731ad/components/libraries/util/ |nrf_assert.h|
|nRF5_SDK_12.3.0_d7731ad/components/drivers_nrf/nrf_soc_nosd/  | nrf_error.h|
|nRF5_SDK_12.3.0_d7731ad/components/drivers_nrf/delay/ |nrf_delay.h|
|nRF5_SDK_12.3.0_d7731ad/components/boards/ |boards.h|

boards.hは、Nordic製の開発ボード使用の際に参照されます。Shinobiの使用時は、さらに、custom_board.hも参照されます。

## 8．コンパイラ制御の設定

Option for Targetボタンを押し、

![](/img/101/led024.png)

Option for Targetボタンを押し、C/C++をクリックPreprocessor SymbolsのDefine:に

![](/img/101/led025.png)

nRF52 Shinobiの場合

> NRF52832 NRF52 BOARD_CUSTOM  NRF52_PAN_12 NRF52_PAN_15 NRF52_PAN_20 NRF52_PAN_31 NRF52_PAN_36 NRF52_PAN_51 CONFIG_GPIO_AS_PINRESET NRF52_PAN_54 NRF52_PAN_55 NRF52_PAN_58 NRF52_PAN_64 BSP_DEFINES_ONLY SWI_DISABLE0

nRF52 DKボード(BOARD_PCA10040)の場合

> NRF52832 NRF52 BOARD_PCA10040  NRF52_PAN_12 NRF52_PAN_15 NRF52_PAN_20 NRF52_PAN_31 NRF52_PAN_36 NRF52_PAN_51 CONFIG_GPIO_AS_PINRESET NRF52_PAN_54 NRF52_PAN_55 NRF52_PAN_58 NRF52_PAN_64 BSP_DEFINES_ONLY SWI_DISABLE0

を追加します。

Langeage / Code Generationの項目
ARMコンパイラの最適化レベルの設定
Optimize Level3(-O3)を選択

Misc　Controls：　--c99を追加します。

### 9. デバッカの設定

次にDebugタグをクリックします。

ターゲットのフラッシュメモリ　プログラム開始アドレスが0x0から始まっていることを確認してください。（無線を使用する場合などで、SoftDeviceを前もってDownloadした場合は、その領域の次にアドレス設定をします。他の項で記述）

![](/img/101/led026.png)

使用するデバッカを設定します。J-linkの場合は、J-LINK/J-TRACE Cortexを選択。

![](/img/101/led027.png)

Settingボタンを押します。port:をJTAG(4～5線式)からSW(2線式)に変更いたします。

![](/img/101/led028.png)

Flash Downloadタブをクリックし、書き込み方法を設定いたします。
書き込み後すぐ実行させるため、Reset and Runを選択します。

![](/img/101/led029.png)

OKボタンを押して設定は終了です。


## 10．main関数追加

Projectファイルと同一のディレクトリにListings,Object,RTEフォルダが自動的に生成されます。
画面の左フォルダSourceGroup 1を左クリックしAdd New Item to Group'SourceGroup 1'を選択します。C File(.c)を選択します。

![](/img/101/100.png)

一番最初に呼ばれるファイルなのでファイル名はmain.cと名前で保存してください。

![](/img/101/101.png)

main.cをクリックして開きます。
次のコードをコピーアンドペーストしてください。

### 11. 1秒間隔でFaboBrickを点滅させる。

```c

#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "boards.h"

#define PIN_NUMBER 3
#define INTERVAL 1000

int main(void)
{
		nrf_gpio_cfg_output(PIN_NUMBER);

    while (true)
    {
			nrf_gpio_pin_toggle(PIN_NUMBER);
			nrf_delay_ms(INTERVAL);			
    }
}

```

### 12.直接レジスタ操作によるLED点滅の場合

Arduino PinA0は、NRF52のピン番号はP0.03にとなります。C言語なのでintなどは、マイコンによってバイト数が２バイトである場合と４バイトである場合があり、unsigned char(unsigned int)ではなくuint8_tなどを使ったほうが可読性や移植性の観点から望ましい。



```c

#include "nrf_delay.h"
#include "nrf_gpio.h"

const uint8_t led_pin = 3; /*P0.03使用　constで修飾する場合は定数はROMに格納されRAM領域の節約になる*/

int main(void)
{
      nrf_gpio_cfg_output(led_pin);/*ポートを出力に設定*/
    while (true)
    {

          uint32_t gpio_state = NRF_GPIO->OUT;/*ポートレジスタの値を取得*/
          NRF_GPIO->OUTSET = ((1 << led_pin) & ~gpio_state);
          NRF_GPIO->OUTCLR = ((1 << led_pin) & gpio_state);
          nrf_delay_ms(1000);/*１秒無しもしない*/

    }
}

```

### 11.boards.hを利用したLED点滅の場合

レジスタ操作は開発効率が悪いので、SDKにはあらかじめ、ボードにあわせたピン定義しているファイルboards.hが存在します。

```c

#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "boards.h"
#define PINNUMBER 3

int main(void)
{
    LEDS_CONFIGURE(1 << PINNUMBER);

    while (true)
    {  
            LEDS_INVERT(1 << PINNUMBER);
            nrf_delay_ms(1000);
    }
}


```


## 13.実行

Buildを実行します。（ショートカットキーF7）

![](/img/LED_101/BuildButtion.jpg)

エラーが表示されなければ、コンパイラはbuildフォルダに******.axfが生成されます。
並びにメモリサイズも表示されます。
![](/img/LED_101/BuildSuccess.jpg)

古いファームウェアを削除します。

![](/img/Fabo_LED_101/flash_erase.png)

Flash→Erase

ROMに書き込むため、******.hexファイルが生成され、
Downloadボタン（ショートカットF8）でターゲットに書き込みします。

![](/img/LED_101/Programing_Done.jpg)

書き込みが成功すればLEDが点滅します。


## Document
NRF52 ドキュメント
http://infocenter.nordicsemi.com/pdf/nRF52832_PS_v1.4.pdf

## 構成パーツParts
- 5mm LED(各色)
