# #101 LED Brick

![](../img/led001.jpg)
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

## １．SESを起動

## 2. 必要なファイルをIncludeする

SDKのフィルだに参照元ファイルは存在

|ファイル名|参照先パス|
|:--|:--|
|Board Definition/board.c|nRF5_SDK_14.2.0_17b948a/components/boards/boards.c|
|Device/ses_nRF_Startup.s|nRF5_SDK_14.2.0_17b948a/components/toolchain/ses/ses_nRF_Startup.s|
|Device/ses_nrf52_Vectors.s|nRF5_SDK_14.2.0_17b948a/components/toolchain/ses/ses_nrf52_Vectors.s|
|Device/system_nrf52.s|nRF5_SDK_14.2.0_17b948a/components/toolchain/system_nrf52.c|
|nRF_Libraries/app_error_weak.c|nRF5_SDK_14.2.0_17b948a/components/libraries/util/app_error_weak.c|
|nRF_Libraries/app_error.c|nRF5_SDK_14.2.0_17b948a/components/libraries/util/app_error.c|
|nRF_Libraries/app_util_platform.c|nRF5_SDK_14.2.0_17b948a/components/libraries/util/app_util_platform.c|
|nRF_Libraries/nrf_assert.c|nRF5_SDK_14.2.0_17b948a/components/libraries/util/nrf_assert.c|
|nRF_Libraries/nrf_strerror.c|nRF5_SDK_14.2.0_17b948a/components/libraries/strerror/nrf_strerror.c|
|Segger Startup Files|thumb_crt0.s|/Applications/SEGGER Embedded Studio for ARM 4.10/source/thumb_crt0.s|

## 3 sdk_config.h を用意

nRF5_SDK_14.2.0_17b948a/examples/peripheral/blinky/pca10040/s132/ses
あたりから、sdk_config.hをコピーしてくる。

## main.cの作成

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

## Document
NRF52 ドキュメント
http://infocenter.nordicsemi.com/pdf/nRF52832_PS_v1.4.pdf

## 構成パーツParts
- 5mm LED(各色)
