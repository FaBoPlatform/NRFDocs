# 電力測定の方法

![](/img/PPK/PPK.JPG)
PCA63511

## Overview

Nordic Semiconductor PowerProfilerKit（PPK）を使えば、高価なDC電源や測定器がなくとも、安く、簡単に電力を計ることができる。測定用マイコンは、PPK上にあるNordic Semiconductor NRF52832(Cortex-M4F)です。測定範囲は1μA～70ｍA（最小分解能0.2μA）測定精度は±２０％、最小13μ秒で表示可能です。

## 測定の方法

PPK上にある、nRF52832のADC機能を利用しています。被試験デバイスの電源にシャント抵抗を直列に接続し、抵抗間の電圧降下により電流値がわかります。電流測定範囲により、３つの測定回路があり、自動的に選択されます。


### 電源供給

DKボード、PowerProfilerKit（USB5V外部 Max70mA,電圧調整可能）、外部電源(1.8V~3.6V)からの3種類から選択。同期トリガーIN、OUT搭載。オシロスコープやロジックアナライザーと組み合わせて使うことも可能です。

## スイッチ

![](/img/PPK/PPK_F.JPG)

PPKには、DUT Select,PowerSelect,SEGGER J-Link selectの３つのスイッチがあります。

### DUT select(SW2)

nRF52ボードあるいは、外部のハードウェアを選択する。

DK  nRF52ボード

External　外部ハードウェア

### Power select(SW4)

DUTへ供給する電源の選択。

DK　外部からの電源。

Reg 外部ハードウェア用

Eternal 外部から電源用

### COM(SW3)

PPKのSocと接続するJ-Linkの選択するスイッチ。

DK DKキットのJ-Linkを使用する。（PPKのSocをデバックする場合）

EXT 外部からのJ-Linkを使用する。（DKボードのSocをデバックする場合）

※通常は、DK側にする。

## PCソフトウェアインストール

Pythonを利用した方法もありますが、今回は、ネイティブな方法で測定します。Windowsの場合、Windows版nRFConnectを選択します。

![](/img/PPK/PPK_Download1.PNG)

Windows版をダウンロード、インストールします。

![](/img/PPK/nRFConnect.PNG)

nRFConnectを起動し、Add/remove appsを選び、PowerProfilerをインストールします。

![](/img/PPK/nrfconnect2.PNG)

LanchAppを選択し、PowerProfilerを起動します。ComPortを適切に選択します。

![](/img/PPK/nrfconnect3.PNG)

下記のような、画面が現れ、DKボードのポートを選択し、正常の場合、しばらく経つと波形が現れます。

![](/img/PPK/nRFConnect_PowerMeasurement.PNG)

上側の波形は、長時間の波形

下側の波形は、短時間のトリガーによって表示される波形


平均値がAVGであり、これにより電池寿命おおよその電池寿命がわかる。

ピーク電流がとらわれやすいですが、スリープ電流が少ないと長寿命です。

マンガン電池やアルカリ電池は、自己放電が高く製造からの時間により保有している電池容量や製造時の製品のばらつきにより変わるので注意が必要で、温度や電流の取り出し方法で容量も変化する。電池メーカーのデータシートを参考にしてください。計算の１／２から１／３ぐらいあると安心です。

リチウムコイン電池は自己放電が少なく、大きな電流は流せませんが、温度変化にも強く、電池寿命が計算しやすい。例えば、CR2477は1000mAhであり、平均電流が1mAであれば1000mAh/1mAから1000時間持つことになります。計算の８０％として計算したほうが安心です。

# 接続例

![](/img/PPK/Connect.JPG)

nRF52DK,nRF51Dkあるいは、nRF52840-PDKをベースにPPKを接続します。

マイクロUSBケーブルでDKボードのUSBポートとパソコンのUSBポートに接続

電源コネクタでDUT(被試験デバイス）とPPKを接続します。

スイッチは、SW2をEternal,SW4をReg.にする。COMは、DKに設定します。


## PPKファームウェア更新

Nordic Profiler KitのダウンロードタブからnRF6707-SWをダウンロードします。

![](/img/PPK/Download_Software_PPK.PNG)

PPKのSocファームウェアは、ppk_110.hexです。更新される場合は、nRFgoStudioやflash_ppk.pyのファイル実行で更新できます。

# 参考

http://infocenter.nordicsemi.com/index.jsp?topic=%2Fcom.nordic.infocenter.tools%2Fdita%2Ftools%2Fpower_profiler_kit%2FPPK_user_guide_Intro.html

https://www.nordicsemi.com/eng/Products/Power-Profiler-Kit
