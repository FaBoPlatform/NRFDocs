# 電力測定の方法

![](/img/PPK/PPK.JPG)
<!--COLORME-->

## Overview

Nordic Semiconductor PowerProfilerKit（PPK）を使えば、高価な測定器がなくとも、安く、簡単に電力を計ることができる。測定用マイコンは、PPK上にあるNordic Semiconductor NRF52832(Cortex-M4F)です。測定範囲は1μA～70ｍA（最小分解能0.2μA）測定精度は±２０％、最小13μ秒で表示可能です。

PCA63511

## 測定の方法

PPK上にある、nRF52832のADC機能を利用しています。被試験デバイスの電源にシャント抵抗を直列に接続し、抵抗間の電圧降下により電流値がわかります。電流測定範囲により、３つの測定回路があり、自動的に選択されます。


### 電源供給

DKボード、PowerProfilerKit（USB5V外部 Max70mA,電圧調整可能）、外部電源(1.8V~3.6V)からの3種類から選択。同期トリガーIN、OUT搭載。オシロスコープやロジックアナライザーと組み合わせて使うことも可能です。

## PCソフトウェアインストール

Windowsの場合、Windows版nRFConnectを選択します。

![](/img/PPK/nRFConnect.PNG)

Windows版をダウンロード、インストールします。

![](/img/PPK/PPK_Download1.PNG)

nRFConnectを起動し、Add/remove appsを選び、PowerProfilerをインストールします。

![](/img/PPK/nRFConnect.PNG)

PowerProfilerを起動します。

![](/img/PPK/nrfconnect3.PNG)

下記のような、画面が現れ、DKボードのポートを選択し、正常の場合、しばらく経つと波形が現れます。

![](/img/PPK/nRFConnect_PowerMeasurement.PNG)


# 設定

![](/img/PPK/PPK_F.JPG)

## スイッチ

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

## 接続方法

nRF52DK,nRF51Dkあるいは、nRF52840-PDKをベースにPPKを接続します。

マイクロUSBケーブルでDKボードとパソコンに接続

DUT(被試験デバイス）とPPKを接続します。


## 電池の特徴


# 参考

http://infocenter.nordicsemi.com/index.jsp?topic=%2Fcom.nordic.infocenter.tools%2Fdita%2Ftools%2Fpower_profiler_kit%2FPPK_user_guide_Intro.html

https://www.nordicsemi.com/eng/Products/Power-Profiler-Kit
