# プログラミングツール

マイコンへプログラミングするのに２つの方法があります。

### 実装前後にプログラミングする方法。

マイコン実装前にソケット使用してマイコンにプログラミングする方法。

製造ではこちらで行うケースがあります。ピンを出す必要がないのでコンパクトにできます。

提供している会社はElnec、Hi-Lo Systems

### マイコン実装後にプログラミングする方法(ISP)

アプリケーション開発には通常こちらを使います。

提供している会社は、SEGGER,PEmicro

SEGGER使用でコマンドラインツールがあり、nrfjprogを使えば、バッチ処理でのマイコンへプログラミングできます。

参考URL
http://infocenter.nordicsemi.com/index.jsp?topic=%2Fcom.nordic.infocenter.gs%2Fdita%2Fgs%2Fnordic_tools.html

### ダイレクトテストモード（DTM）
,
送信電力と受信感度,周波数オフセットとドリフト,変調特性,パケットエラー率,相互変調性能などハードをテストするモードがあります。

参考URL ダイレクトテストモード
https://infocenter.nordicsemi.com/index.jsp?topic=%2Fcom.nordic.infocenter.sdk52.v0.9.1%2Fble_sdk_app_dtm_serial.html

### 電力計算

実測ではないのですが、おおよその電力が計算できます。それぞれの実装によりアプリケーション作成後は必ずPowerProfilerKit等で実際の電力を確認してください。

参考URL
https://devzone.nordicsemi.com/power/
