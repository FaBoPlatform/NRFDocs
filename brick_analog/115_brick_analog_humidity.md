# #115 Humidity Brick

<center>![](../img/HUMIDITY115/115.jpg)
<!--COLORME-->

## Overview
湿度センサーモジュールを使用したBrickです。

温度、湿度の情報を取得することができます。

## Connecting

アナログコネクタ(A0〜A5)のいずれかに接続します。

![](/img/100_analog/connect/115_humidity_connect.jpg)


## Parts Specification
| Document |
|:--|
| [DHT11](http://akizukidenshi.com/catalog/g/gM-07003/) |

## Schematic
![](/img/100_analog/schematic/115_humidity.png)

## Sample Code
A0コネクタに接続して、湿度を計測するサンプルになります。

このサンプルコードでは外部ライブラリを使用します。

- [GitHub Library](https://github.com/adafruit/DHT-sensor-library)

![](/img/100_analog/docs/115_humidity_docs_001.png)

![](/img/100_analog/docs/115_humidity_docs_002.png)

  ライブラリ名：「DHT sensor library」

```c

```


## 構成Parts
- 湿温度センサモジュールDHT11

## GitHub
- https://github.com/FaBoPlatform/FaBo/tree/master/115_humidity
