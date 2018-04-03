# #304 USB Serial Brick

![Cube](../img/USBSerial304/USBSerial304.JPG)
<!--COLORME-->

## Overview
FT232RLを使用した、USBシリアル通信ができるBrickです。

mac　screenコマンドで
screen /dev/tty.****** 115200

終了後はscreen -r で復活できる。

screen -lsでもセッションが確認。

終了するのは、

control 押しながら　a ,kと押す。

## Connecting
Serialコネクタへ接続し、MicroUSBコネクタを他のデバイスに接続します。Necleoのi/oは3.3Vで駆動しますのでUSB Brickの電圧スイッチを3.3Vにしてください。

sdk_config.h printfで出力する設定。

![](/img/USB304/UART_OUTPUT.PNG)

## Sample Code

```c

```


## 構成Parts
-

## GitHub
