# #3 Shinobi_Solar

![](/img/Shinobi_Power/Shinobi_LipoCharrger.JPG)
<!--COLORME-->

## Overview

太陽電池パネルから発電された電気をLiPoバッテリー（３．７V)に充電、Shinobi_NRF,ANA6へ放電３．３Vいたします。

３．３Vレギュレーター搭載。

NTCサーミスタによる充電禁止機能

※重要　リチウムポリマー電池は、取り扱いに誤ると大変危険です。

リチウムポリマー電池には、軽量なのですが、パッケージは弱く傷や衝撃、圧力を与えないようにしてください。

リチウムポリマー（３．７V)電池専用です。他の電池には絶対に接続しないでください。

##　接続

接続するリチウムポリマー電池は400mAhをご使用ください。

### 搭載チップ

Microchip
MCP73871-2CC

TI
LP2985-33DBVR

Murata
NXFT15XH103FA2B050



### ステータス表示

電圧比例充電制御VPCCと電流制限制御ICLCで充電、放電を制御いたします。

LBO(バッテリー電圧低下検知出力)は３．１Vとなります。


予備充電、定電流充電、定電圧充電

STAT1（青）とPG（赤）が点灯

![](/img/Solar/LEDS_STAT.jpg)

充電完了（スタンバイ）

STAT2（緑）とPG（赤）が点灯

温度フォルト、タイマフォルトで停止

全点灯

バッテリ電圧低下

STAT1（青）のみ点灯

バッテリーなし（バッテリーが未接続）または、
シャットダウン（電源電圧VDDと入力電圧INが同じとき）

PG（赤）が点灯

入力電源なし（バッテリーが放電しBLEへ供給）
または、シャットダウン（電源電圧VDDとバッテリー電圧が同じとき）

全消灯

※正常に接続し、十分な日光が太陽電池に照射されているにもかかわらず、充電しても何もLEDが光らないときは、異常ですのでただちに使用を中止してください。

## 充電電圧

4.20V

## 入力電圧

最大　６V

最低　0.3V

## 出力電圧

3.3V(降圧レギュレーターによる)


## Connecting

PHコネクタ SYSには、Shinobi_NRFまたは、Shinobi_ANAを接続します。

Lipoにはリチウムポリマー電池(3.7V)を接続します。

※接続を間違わないようにしてください。

※短時間に接続を繰り返さないでください。

※リチウムポリマー電池が膨らんだものや、膨らんだものは使用しないでください。

※バッテリーメーカーの仕様、推奨に従ってください。

１．３ｍｍDCジャックに太陽電池を接続します。

NTCサーミスタは、温度計でありリチウムポリマー電池の温度を計測し、異常な温度を感知し、停止します。

リチウムポリマー電池に密着するようにテープ止めしてください。

## 設定

１０ｍAで充電するように設定されています。（設定は変更しないでください。）

安全タイマー６時間

温度監視を有効

## 温度範囲

0℃～４０℃

## Parts Specification

| Document |
|:--|
| [microchip MCP73871](http://www.microchip.com/wwwproducts/en/en536670) |

| Document |
|:--|
| [mirata NXFT15XH103FA2B050](https://www.murata.com/~/media/webrenewal/support/library/catalog/products/thermistor/ntc/r44e.ashx) |

| Document |
|:--|
| [TI LP2985-33DBVR](http://www.ti.com/lit/ds/symlink/lp2985.pdf
) |


## Schematic

## Sample Code

## 構成Parts
