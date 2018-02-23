# #3 Shinobi_Solar

![](/img/Shinobi_Power/Shinobi_LipoCharrger.JPG)
<!--COLORME-->

## Overview

太陽電池パネルから発電された電気をLiPoバッテリー（３．７V)に充電します。発電しないときは、BLEへ放電いたします。

※重要　リチウムポリマー電池は、取り扱いに誤ると大変危険です。

リチウムポリマー電池には、軽量なのですが、パッケージは弱く傷や衝撃、圧力を与えないようにしてください。

リチウムポリマー（３．７V)電池専用です。他の電池には絶対に接続しないでください。

### 搭載チップ

MCP73871-2CC

### ステータス表示

シャットダウン

シャットダウン

予備充電

定電流

STAT1とPGが点灯

定電圧

![](/img/Shinobi_Power/LEDS_STAT.jpg)

充電完了（スタンバイ）

温度フォルト

タイマフォルト

バッテリ電圧低下

バッテリーなし

入力電源なし

## Connecting

PHコネクタ SYSには、Shinobi_NRFまたは、Shinobi_ANAを接続します。

Lipoにはリチウムポリマー電池(3.7V)を接続します。

※接続を間違わないようにしてください。

※短時間に接続を繰り返さないでください。

１．３ｍｍDCジャックに太陽電池を接続します。

NTCサーミスタは、温度計でありリチウムポリマー電池の温度を計測し、異常な温度を感知し、停止します。

リチウムポリマー電池に密着するようにテープ止めしてください。

## 設定

１０ｍAで給電するように設定されています。

タイマーモードは無効になっています。

## Parts Specification
| Document |
|:--|
| [microchip MCP73871](http://www.microchip.com/wwwproducts/en/en536670) |

## Schematic

## Sample Code

## 構成Parts
