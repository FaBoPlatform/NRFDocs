# #102 Buzzer Brick

![](/img/BUZZER102/102.jpg)
<!--COLORME-->

## Overview
圧電ブザーを使ったBrickです。

## Connecting

![](/img/BUZZER102/FaBo_102_BUZZER_CONNECT.JPG)

## Schematic

## Sample Code

###PWMによる出力

Buzzer Brickを接続し、ビープ音を鳴らしています。
音の波形は矩形波でPWM出力します。

## 出力するPWMの設定

デューティー比は0.5に設定
ベースクロックは１MHzで出力

設定は構造体でそれぞれ設定しており、各メンバで設定。


## 主な構造体

### nrf_drv_pwm_t

PWM ドライバのインスタンスデータ構造体

| 変数名 | 概要 |
|:--|:--|
| NRF_PWM_Type * p_registers | PWMペリフェラルインスタンスレジスタの指し示す |
| uint8_t drv_inst_idx |ドライバインスタンスインデックス |


###  enum nrf_pwm_mode_t

PWMモード

| 変数名 | 概要 |
|:--|:--|
|NRF_PWM_MODE_UP|アップカウンタ（エッジデューティーサイクル）|
|NRF_PWM_MODE_UP_AND_DOWN|アップ、ダウンカウンタ　（センターデューティーサイクル）|


###  enum nrf_pwm_dec_load_t

PWMデコーダーロードモード
シーケンスデータのRAMから読み出され、コンペアレジスタに格納方法。

| 変数名 | 概要 |
|:--|:--|
|NRF_PWM_LOAD_COMMON | すべてのPWMチャンネル（0〜3）で使用される一番最初のハーフワード（16ビット）|
|NRF_PWM_LOAD_GROUPED |チャンネル0と1で使用される一番最初のハーフワード（16ビット）。チャンネル2と3の2番目のワード。|
|NRF_PWM_LOAD_INDIVIDUAL |チャンネル0で使用される一番最初のハーフワード（16ビット）、チャンネル1では2番目、チャネル2の3番目、チャンネル3の4番目|
|NRF_PWM_LOAD_WAVE_FORM | チャンネル0で使用される一番最初のハーフワード（16ビット）、チャンネル1では2番目、4番目は、パルスジェネレータカウンタの最上位の値 |

###  enum nrf_pwm_clk_t

ベースクロック周波数。

| 変数名 |
|:--|
|NRF_PWM_CLK_16MHz|
|NRF_PWM_CLK_8MHz|	
|NRF_PWM_CLK_4MHz|
|NRF_PWM_CLK_2MHz|	
|NRF_PWM_CLK_1MHz|
|NRF_PWM_CLK_500kHz|	
|NRF_PWM_CLK_250kHz|	
|NRF_PWM_CLK_125kHz|

### enum nrf_pwm_dec_step_t

PWMデコーダーネクストステップモード

アクティブシーケンスからの次の値がいつロードされるかを決定します

| 変数名 | 概要 |
|:--|:--|
|NRF_PWM_STEP_AUTO|Automatically after the current value is played and repeated the requested number of times.自動的に、現在の値がプレイされた後、要求された回数だけ繰り返されます|
|NRF_PWM_STEP_TRIGGERED|When the NRF_PWM_TASK_NEXTSTEP task is triggered. NRF_PWM_TASK_NEXTSTEPタスクがトリガーしたとき|

## 主な関数

###  ret_code_t nrf_drv_pwm_init
> ret_code_t nrf_drv_pwm_init
(nrf_drv_pwm_t const \*const p_instance, nrf_drv_pwm_config_t const \* p_config, nrf_drv_pwm_handler_t handler )

PWMドライバを初期化する関数

| 変数名 | 概要 |
|:--|:--|
|p_instance|ドライバーのインスタンス|
|p_config|初期設定構造体を指し示す。もし、デフォルト設定ならNULLをいれます。|
|handler|ユーザーによって供給されたイベントハンドラー。もし使わないなら、代わりにNULLを入れ、イベントの通知はされず、PWM割り込みは使えません。|

返り値

| 変数名 | 概要 |
|:--|:--|
|NRF_SUCCESS|成功した場合。|
|NRF_ERROR_INVALID_STATE|すでに初期化されている場合。|

### nrf_drv_pwm_uninit
> void nrf_drv_pwm_uninit	(	nrf_drv_pwm_t const \*const 	p_instance	)

PWMドライバを初期化しない関数

プレイ中の場合は、すぐに停止します。

### nrf_drv_pwm_simple_playback
> void nrf_drv_pwm_simple_playback (nrf_drv_pwm_t const \*const p_instance, nrf_pwm_sequence_t const * p_sequence,uint16_tplayback_count,uint32_t flags )

１回のシーケンス再生を行う関数

※指定されたシーケンスのデューティサイクル値を含む配列はRAMになければならず、スタックに配置することはできません。

| 変数名 | 概要 |
|:--|:--|
|p_instance|PWMドライバのインスタンスを指し示す|
|p_sequence|プレイバックするシーケンスを指し示す|
|playback_count|プレイバックする回数(０であってはなりません。).|
|flags|Additional options. Pass any combination of playback flags, or 0 for default settings.オプションを追加します。いくつかのプレイバックフラッグの組み合わせ渡すか、デフォルトセッティングは０となります。|

## 音の周波数

音の周波数は、ラの４４０をベースに２＾（１/12）の公差数列であり周波数Hzは下記になります。

| 変数名 | 概要 |
|:--|:--|
|ド|261.6255653|
|ド＃|277.182631|
|レ|293.6647679|
|レ＃|311.1269837|
|ミ|329.6275569|
|ファ|369.9944227|
|ファ＃|391.995436|
|ソ|415.3046976|
|ラ|440|
|ラ＃|466.1637615|
|シ|493.8833013|
|ド|523.2511306|

波長lengthは、（１０００／周波数）＊１０００になります。
繰り返しは１００回です。

###ビープ音でドレミを演奏。

```c

#include <stdio.h>
#include <string.h>
#include "nrf_drv_pwm.h"
#include "app_util_platform.h"
#include "app_error.h"
#include "boards.h"
#include "bsp.h"
#include "app_timer.h"
#include "nrf_drv_clock.h"
#include "nrf_delay.h"

#define Fabo_Shinobi_AnalogPin 3

static nrf_drv_pwm_t m_pwm0 = NRF_DRV_PWM_INSTANCE(0);

static void sound(int freq)
{
    uint32_t                   err_code;
    nrf_drv_pwm_config_t config0 =
    {
        .output_pins =
        {
            Fabo_Shinobi_AnalogPin | NRF_DRV_PWM_PIN_INVERTED,
        },
        .irq_priority = APP_IRQ_PRIORITY_LOWEST,
        .base_clock   = NRF_PWM_CLK_1MHz,
        .count_mode   = NRF_PWM_MODE_UP,
        .top_value    = freq,
        .load_mode    = NRF_PWM_LOAD_COMMON,
        .step_mode    = NRF_PWM_STEP_AUTO
    };

    err_code = nrf_drv_pwm_init(&m_pwm0, &config0, NULL);
    APP_ERROR_CHECK(err_code);

    // This array cannot be allocated on stack (hence "static") and it must
    // be in RAM.
    static nrf_pwm_values_common_t seq0_values[2];
    nrf_pwm_sequence_t const       seq0 =
    {
        .values.p_common = seq0_values,
        .length          = NRF_PWM_VALUES_LENGTH(seq0_values),
        .repeats         = 100,
        .end_delay       = 0
    };
        seq0_values[0] = freq / 2;
			nrf_drv_pwm_simple_playback(&m_pwm0, &seq0, 1,
                                NRF_DRV_PWM_FLAG_LOOP);
}



int main(void)
{  
    while(1){
		sound(3822);
		nrf_delay_ms(200);
    nrf_drv_pwm_uninit(&m_pwm0);
		sound(3405);
		nrf_delay_ms(200);
    nrf_drv_pwm_uninit(&m_pwm0);
		sound(3033);
		nrf_delay_ms(200);
    nrf_drv_pwm_uninit(&m_pwm0);
		sound(2863);
		nrf_delay_ms(200);
    nrf_drv_pwm_uninit(&m_pwm0);
		sound(2551);
		nrf_delay_ms(200);
		nrf_drv_pwm_uninit(&m_pwm0);
		sound(2272);
		nrf_delay_ms(200);
		nrf_drv_pwm_uninit(&m_pwm0);
		sound(2024);
		nrf_delay_ms(200);
		nrf_drv_pwm_uninit(&m_pwm0);
		sound(1911);
		nrf_delay_ms(200);
		nrf_drv_pwm_uninit(&m_pwm0);
		nrf_delay_ms(1000);
	}

}



```


## 参照　API
* nrf_drv_pwm_config_t Struct Reference
https://infocenter.nordicsemi.com/index.jsp?topic=%2Fcom.nordic.infocenter.sdk5.v11.0.0%2Fstructnrf__drv__pwm__config__t.html
Software Development Kit > nRF5 SDK > nRF5 SDK v12.3.0 > Data Structures > Data Structures

* PWM HAL
Software Development Kit > nRF5 SDK > nRF5 SDK v12.3.0 > API Reference > Peripheral drivers > PWM HAL and driver

* PWM
Software Development Kit > nRF5 SDK > nRF5 SDK v12.3.0 > Hardware Drivers

## 構成Parts
- 圧電ブザー

## GitHub
