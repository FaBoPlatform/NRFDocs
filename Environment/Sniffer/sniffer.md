#[BGScript] パケットスニファの設定

## 必要なハード

* CC2540 USB Evaluation Module Kit
<br>
http://www.ti.com/tool/cc2540emk-usb


## 必要なソフト
* SmartRF Protocol Packet Sniffer
<br>
http://www.tij.co.jp/tool/jp/packet-sniffer


## 手順

1. 以下のURLより、SmartRF Protocol Packet Snifferをダウンロード
<br>
http://www.tij.co.jp/tool/jp/packet-sniffer

2. ダウンロードしたファイルを展開し、「Setup_SmartRF_Packet_Sniffer_2.18.1.exe」を実行

3. 規約に同意し、デフォルトの設定でインストール

4. インストール完了後、Packet Snifferを起動

5. select Protocol and chip typeから「Bluetooth Low Energy」を選択
<br>
![](bgs_sniffer001.jpg)

6. CC2540 USB Evaluation Module KitをPCのUSBポートに接続

7. 画面下部にデバイス名が表示されることを確認し、画面上部の「▶︎」ボタンを押下
<br>
![](bgs_sniffer002.jpg)

7. 画面上にパケットの情報が表示
<br>
![](bgs_sniffer003.jpg)