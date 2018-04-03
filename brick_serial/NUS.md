# #NUS

セントラルとペリフェラル間で接続し、GATTへ書き込むのですがUARTのように使える機能があります。

Nordicの独自のBLEサービスで、BluetoothクラシックRFCOMMプロファイル（UART over BT）の様なUART Serviceが用意されております。

これを使えば、簡単にスマートフォンなどのセントラルから文字を送信できます。

GATTは、４つのRX（書き込み）、２つTX（通知）のデータチャンネルが設定できます。
















# 参照
http://infocenter.nordicsemi.com/index.jsp
