# SEGGER Embed Stduioの開発環境の構築

SEGGER社が提供するIDEです。他のARMマイコンにも使うことができますが、Nordic社とSEGGER社が契約を結び、
ターゲットがNRF51,NRF52ならばコード無制限、無償で使える大変ありがたいツールとなっています。
ソフトデバイスのアドレス設定や使うべきソフトデバイスも自動でインストールできて大変便利です。
Windows,Mac,Linuxでも使うことができる。

注意すべき点:対応しているSDKバージョンがV1４以降となります。サンプルのプロジェクトフォルダ名は、sesとなります。

参考URL
http://infocenter.nordicsemi.com/index.jsp?topic=%2Fcom.nordic.infocenter.gs%2Fdita%2Fgs%2Fnordic_tools.html

Keilには、nRFConfig.hをチェックボックスで管理できる機能がすでにありますが、Embed Stduioには、別アプリになりますが、CMSIS_Configuration_Wizardがあります。Javaアプリになります。

SDK内にあります。CMSIS_Configuration_Wizard.jarを実行してください。
〜/Downloads/nRF5_SDK_15.0-3.0_a53641a/external_tools/cmsisconfig
