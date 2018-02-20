# #101 LED Brick

![](/img/LED_101/101_led.jpg)
<!--COLORME-->

## Overview
LEDのBrickです。発光色は5色（青・緑・赤・白・黄）あります。Lチカのおともにもどうぞ。

※購入時は色の間違いにご注意ください。

## Connecting
接続例：ShinobiのAnalogに接続。
Shinobi アナログコネクタ

## Schematic
![](/img/led101_schmatic.png)

## Sample Code
Arduino Motor ShieldのA0コネクタにLED Brickを接続し、一定時間(1秒=1000ms)ごとに点灯/消灯（Lチカ）させています。

## １．Keilを起動します。

任意の場所プロジェクトフォルダの中にLED101のフォルダを作成します。
Project → New μ プロジェクト → プロジェクトファイルを保存します。

![](/img/LED_101/_101_ProjectMake.png)

プロジェクトファイルが作成され。

## ２．デバイスの選択

ターゲットとなるマイコンを選択します。Nordic Semiconductorを選択。
![](/img/LED_101/Selection_Soc.png)

nRF52　Series→nRF528232_xxAAを選択します。
![](/img/LED_101/SocVersionSelect.jpg)

## ３．コンポーネントを選択

マイコン起動に必要なコンポーネントを選択します。

CMSIS→CORE
Device→Startup

## 4．コンポーネント、ライブラリを選択

管理しやすいように名前を以下のようにします。

必要な以下のSDKのコンポーネントおよびライブラリから参照します。

## 5．インクルードファイルの設定

以下のコンポーネント等のヘッダーファイルを指定します。

## 6．SDK_confing.hの設定

SDK_confing.hを選択しconfigration_Wizardタブをクリック。

以下をチェックします。

## 7．コンパイラ制御の設定

Option for Targetボタンを押し、C/C++をクリックPreprocessor SymbolsのDefine:に



![](/img/Fabo_LED_101/OptionfoTarget101.png)

nRF52 Shinobiの場合

NRF52832 NRF52 BOARD_CUSTOM  NRF52_PAN_12 NRF52_PAN_15 NRF52_PAN_20 NRF52_PAN_31 NRF52_PAN_36 NRF52_PAN_51 CONFIG_GPIO_AS_PINRESET NRF52_PAN_54 NRF52_PAN_55 NRF52_PAN_58 NRF52_PAN_64 BSP_DEFINES_ONLY SWI_DISABLE0

nRF52 DKボード(BOARD_PCA10040)の場合

NRF52832 NRF52 BOARD_PCA10040  NRF52_PAN_12 NRF52_PAN_15 NRF52_PAN_20 NRF52_PAN_31 NRF52_PAN_36 NRF52_PAN_51 CONFIG_GPIO_AS_PINRESET NRF52_PAN_54 NRF52_PAN_55 NRF52_PAN_58 NRF52_PAN_64 BSP_DEFINES_ONLY SWI_DISABLE0

を追加します。

Langeage / Code Generationの項目
ARMコンパイラの最適化レベルの設定
Optimize Level3(-O3)を選択

Misc　Controls：　--c99を追加します。

### 8. デバッカの設定

次にDebugタグをクリックします。

![](/img/LED_101/OptionsTarget_C.png)

ターゲットのフラッシュメモリ　プログラム開始アドレスが0x0から始まっていることを確認してください。（無線を使用する場合などで、SoftDeviceを前もってDownloadした場合は、その領域の次にアドレス設定をします。他の項で記述）

![](/img/LED_101/OptionsTarget.png)

使用するデバッカを設定します。J-linkの場合は、J-LINK/J-TRACE Cortexを選択。

![](/img/LED_101/J-linkSettings.jpg)

Settingボタンを押します。port:をJTAG(4～5線式)からSW(2線式)に変更いたします。

![](/img/LED_101/build_Settings.jpg)

Flash Downloadタブをクリックし、書き込み方法を設定いたします。
書き込み後すぐ実行させるため、Reset and Runを選択します。

![](/img/LED_101/WriteSettings.jpg)

OKボタンを押して設定は終了です。


## 9．main関数追加

Projectファイルと同一のディレクトリにListings,Object,RTEフォルダが自動的に生成されます。
画面の左フォルダSourceGroup 1を左クリックしAdd New Item to Group'SourceGroup 1'を選択します。C File(.c)を選択します。

![](/img/LED_101/AddNewGroup.png)

一番最初に呼ばれるファイルなのでファイル名はmain.cと名前で保存してください。

![](/img/LED_101/SouceGroupSelection.png)

main.cをクリックして開きます。
次のコードを記述してください。

### 10.直接レジスタ操作によるLED点滅の場合

Arduino PinA0は、NRF52のピン番号はP0.03にとなります。C言語なのでintなどは、マイコンによってバイト数が２バイトである場合と４バイトである場合があり、unsigned char(unsigned int)ではなくuint8_tなどを使ったほうが可読性や移植性の観点から望ましい。

```c
#include "nrf_delay.h"
#include "nrf_gpio.h"

const uint8_t led_pin = 3;  /*P0.03使用　/*P0.03使用　constで修飾する場合は定数はROMに格納されRAM領域の節約になる*/
int main(void)
{
      nrf_gpio_cfg_output(3); /*P0.03の入出力方向は出力に設定*/
    while (true)
    {

          uint32_t gpio_state = NRF_GPIO->OUT;/*GPIOのレジスタを取得*/
          NRF_GPIO->OUTSET = ((1 << led_pin) & ~gpio_state);
          NRF_GPIO->OUTCLR = ((1 << led_pin) & gpio_state);
          nrf_delay_ms(1000);/*１秒停止*/

    }
}
```


### 11.boards.hに頼ったLED点滅の場合

レジスタ操作は開発効率が悪いので、SDKにはあらかじめ、ボードにあわせたピン定義しているファイルboards.hが存在します。

```c
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "boards.h"
#define PinNumberA0 3

const uint8_t led_pin = PinNumberA0;

int main(void)
{
    LEDS_CONFIGURE(1 << PinNumberA0);

    while (true)
    {  
            LEDS_INVERT(1 << led_pin);
            nrf_delay_ms(1000);
    }
}

```


## 12..実行

Buildを実行します。（ショートカットキーF7）

![](/img/LED_101/BuildButtion.jpg)

エラーが表示されなければ、コンパイラはbuildフォルダに******.axfが生成されます。
並びにプログラムサイズも表示されます。
![](/img/LED_101/BuildSuccess.jpg)

古いファームウェアを削除します。
Flash→Erase

ROMに書き込むため、******.hexファイルが生成され、
Downloadボタン（ショートカットF8）でターゲットに書き込みします。

![](/img/LED_101/Programing_Done.jpg)

書き込みが成功すればLEDが点滅します。



## 構成パーツParts
- 5mm LED(各色)
