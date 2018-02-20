# #101 LED Brick

![](/img/LED_101/101_led.jpg)
<!--COLORME-->

## Overview
LEDのBrickです。発光色は5色（青・緑・赤・白・黄）あります。Lチカのおともにもどうぞ。

## Connecting
接続例：J-Linke LiteをShinobi_NRF、USB電源をShinobiBatterry,Fabo1010をShinobiアナログコネクタに接続します。

![](/img/Fabo_LED_101/Fabo_101_Connect_LI.jpg)

## Schematic
![](/img/led101_schmatic.png)

## Sample Code
Arduino Motor ShieldのA0コネクタにLED Brickを接続し、一定時間(1秒=1000ms)ごとに点灯/消灯（Lチカ）させています。

## １．Keilを起動

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

![](/img/Fabo_LED_101/StartupSelect.PNG)

以下をチェックします。

CMSIS→CORE

Device→Startup

## 4．コンポーネント、ライブラリを選択

管理しやすいように名前を以下のようにします。

![](/img/Fabo_LED_101/makeLibraryFolder.PNG)

必要な以下のSDKのコンポーネントおよびライブラリから参照します。

![](/img/Fabo_LED_101/OptionfoTarget101.PNG)

ボタンをクリックします。

![](/img/Fabo_LED_101/ButtoniconManager.PNG)

以下のコンポーネント等のヘッダーファイルをAdd Filesボタンをクリックして指定します。

![](/img/Fabo_LED_101/ManageProjectItems.PNG)


Application

main.c


Board Definition

boards.c


nRF_Drivers

..\..\..\..\..\..\components\drivers_nrf\clock\nrf_drv_clock.c

..\..\..\..\..\..\components\drivers_nrf\common\nrf_drv_common.c

..\..\..\..\..\..\components\drivers_nrf\uart\nrf_drv_uart.c

..\..\..\..\..\..\components\drivers_nrf\nrf_soc_nosd\nrf_nvic.c

..\..\..\..\..\..\components\drivers_nrf\nrf_soc_nosd\nrf_soc.c

nRF_Libraries

..\..\..\..\..\..\components\libraries\util\app_error.c

..\..\..\..\..\..\components\libraries\util\app_error_weak.c

..\..\..\..\..\..\components\libraries\timer\app_timer.c

..\..\..\..\..\..\components\libraries\util\app_util_platform.c

..\..\..\..\..\..\components\libraries\hardfault\hardfault_implementation.c

..\..\..\..\..\..\components\libraries\util\nrf_assert.c

..\..\..\..\..\..\components\libraries\util\sdk_errors.c

nRF_Log

..\..\..\..\..\..\components\libraries\log\src\nrf_log_backend_serial.c

..\..\..\..\..\..\components\libraries\log\src\nrf_log_frontend.c

nRF_Segger_RTT

..\..\..\..\..\..\external\segger_rtt\RTT_Syscalls_KEIL.c

..\..\..\..\..\..\external\segger_rtt\SEGGER_RTT.c

..\..\..\..\..\..\external\segger_rtt\SEGGER_RTT_printf.c

選択されると、コンポーネントがそれぞれ取り込まれます。

![](/img/Fabo_LED_101/Projet_tree.PNG)


## 5．インクルードファイルの設定

Option for Targetボタンを押し、

![](/img/Fabo_LED_101/Optiontarget.PNG)

C/C++をクリックします。Include Pathsの右のボタンをクリックします。

![](/img/Fabo_LED_101/Includepass.PNG)

ボタンを押して逐次ヘッダファイルがあるパスを追加します。
選択されると以下のようになります。

![](/img/Fabo_LED_101/Includepass101.PNG)

## 6．SDK_confing.hの設定

コンパイルするモジュールを指定します。

![](/img/Fabo_LED_101/Configration_Wizard101.PNG)

SDK_confing.hを選択し下のconfigration_Wizardタブをクリック。

以下をチェックします。

![](/img/Fabo_LED_101/Configration_anotation101.PNG)


## 7．コンパイラ制御の設定

Option for Targetボタンを押し、

![](/img/Fabo_LED_101/Optiontarget.PNG)

Option for Targetボタンを押し、C/C++をクリックPreprocessor SymbolsのDefine:に

![](/img/Fabo_LED_101/OptionfoTarget101.PNG)

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
次のコードをコピーアンドペーストしてください。

### 10. 1秒間隔でFaboBrickを点滅させる。

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


### 11.直接レジスタ操作によるLED点滅の場合

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

const uint8_t led_pin = PINNUMBER;

int main(void)
{
    LEDS_CONFIGURE(1 << PINNUMBER);

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
並びにメモリサイズも表示されます。
![](/img/LED_101/BuildSuccess.jpg)

古いファームウェアを削除します。
Flash→Erase

ROMに書き込むため、******.hexファイルが生成され、
Downloadボタン（ショートカットF8）でターゲットに書き込みします。

![](/img/LED_101/Programing_Done.jpg)

書き込みが成功すればLEDが点滅します。



## 構成パーツParts
- 5mm LED(各色)
