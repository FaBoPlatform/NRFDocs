# 省電力メモ


### スリープ中のモジュール停止について


　sd_app_evt_wait()でスリープ状態になっても、約1.4mA程度の平均電流が常時流れてしまう。Beaconのようなスリープ時にUARTを受信する必要がない場合は、UARTモジュールの電力を０になるように、次の１行をmain関数に加える。
**NRF_UART0->POWER = 0;
**
ただし、宣言するとUARTが停止するので、TeraTermなどのターミナルからログが出なくなりますので注意が必要です。

※開発ボードを使えば接続しているUSBケーブル１本のみでUARTが出力できます。


### 内部発振と外部発振


nRF51822には、32kHz（LFCLK）と16MHz(HFCLK)の発振回路が内臓されている。スリープ時には遅い32KHzが使われ省電力になる。内部の発振回路(RC)は、コンデンサと抵抗で構成され、温度に影響されやすく精度が落ちる。モジュール品は、16MHzor32MHzの外部発振子が装備され、オプションとして32kHzの発振子が設ける事ができる。外部発振子はどちらも精度が高い。それゆえ、部品点数が増えコストは高くなる。


内部発振使用（RC）の場合は、いずれも精度は250ppmとなる。キャリブレーションが行われ外部発振と比べて消費電力がわずかに高くなる。また、温度によるドリフト対策（ズレ)されたものが選べる。温度変化があると補正が行われる。一方、外部発振(XTAL)を使用する場合は、実装されている水晶発振子のデータシートを元に選択する。精度が最大で20ppmとなりますが、非常に精度が高くなりわずかにRCと比べ省電力となる。また、水晶発振子16MHzのみでの実行でき部品が節約できるが（水晶発振子32KHzをカット）非常に消費電力が高くなる（約２から３倍）。


よって**1.4.10SoftDevice**,**1.4.11iBeacon**のコードをボードによって適切な設定をしなくてはいけない。

SOFTDEVICE_HANDLER_INIT(**NRF_CLOCK_LFCLKSRC_RC_250_PPM_8000MS_CALIBRATION**, NULL);


| NRF_CLOCK_LFCLKSRCS | 詳細|
| -- | -- |
| NRF_CLOCK_LFCLKSRC_SYNTH_250_PPM |外部16MHzのみ　周波数精度250ppm
|
|NRF_CLOCK_LFCLKSRC_XTAL_250_PPM| 外部32KHzあり周波数精度250ppm |
| NRF_CLOCK_LFCLKSRC_XTAL_150_PPM |周波数精度150ppm |
| NRF_CLOCK_LFCLKSRC_XTAL_100_PPM |周波数精度100ppm |
| NRF_CLOCK_LFCLKSRC_XTAL_75_PPM | 周波数精度75ppm |
| NRF_CLOCK_LFCLKSRC_XTAL_50_PPM | 周波数精度50ppm |
| NRF_CLOCK_LFCLKSRC_XTAL_30_PPM | 周波数精度30ppm |
| NRF_CLOCK_LFCLKSRC_XTAL_20_PPM | 周波数精度20ppm |
| NRF_CLOCK_LFCLKSRC_RC_250_PPM_250MS_CALIBRATION | 内部発振回路　周波数精度250ppm  |
| NRF_CLOCK_LFCLKSRC_RC_250_PPM_500MS_CALIBRATION | 周波数精度250ppm |
| NRF_CLOCK_LFCLKSRC_RC_250_PPM_1000MS_CALIBRATION | 周波数精度250ppm |
| NRF_CLOCK_LFCLKSRC_RC_250_PPM_2000MS_CALIBRATION | 周波数精度250ppm |
| NRF_CLOCK_LFCLKSRC_RC_250_PPM_4000MS_CALIBRATION | 周波数精度250ppm |
| NRF_CLOCK_LFCLKSRC_RC_250_PPM_4000MS_CALIBRATION | 周波数精度250ppm |
| NRF_CLOCK_LFCLKSRC_RC_250_PPM_8000MS_CALIBRATION | 周波数精度250ppm |
| NRF_CLOCK_LFCLKSRC_RC_250_PPM_TEMP_1000MS_CALIBRATION | 周波数精度250ppm |
| NRF_CLOCK_LFCLKSRC_RC_250_PPM_TEMP_2000MS_CALIBRATION | 周波数精度250ppm |
| NRF_CLOCK_LFCLKSRC_RC_250_PPM_TEMP_4000MS_CALIBRATION | 周波数精度250ppm |
| NRF_CLOCK_LFCLKSRC_RC_250_PPM_TEMP_8000MS_CALIBRATION | 周波数精度250ppm |
| NRF_CLOCK_LFCLKSRC_RC_250_PPM_TEMP_16000MS_CALIBRATION | 周波数精度250ppm |









