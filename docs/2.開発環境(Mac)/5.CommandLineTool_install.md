# CommandLineTool Install

コマンドラインツールを使えば、ターミナルからJ-Linkの設定なしでファームウェアを簡単に焼くことができます。

## J-Linkのソフトウェアインストール

https://www.segger.com/downloads/jlink

J-Link Software and Documentation packをダウンロード。

J-Link Software and Documentation pack for macOSをインストールします。

## コマンドラインツールインストール

https://www.nordicsemi.com/eng/nordic/Products/nRF52840/nRF5x-Command-Line-Tools-OSX/58855

## PCの設定

export PATH=~/ダウンロード/nrfjprog:$PATH

あるいは、パッケージ管理ソフトBrewを入れてその後以下を実行（サイトからダウンロードなしで以下のパッケージを実行）

brew cask install nrf5x-command-line-tools

## ターミナルから以下実行

アプリケーションがソフトデバイスに依存しているものは、前もって以下をインストール

nrfjprog --program s132_nrf52_3.0.0_softdevice.hex -f nrf52 --chiperase

### アプリケーションインストール

### ソフトデバイスなしの場合

nrfjprog --program ファイル名.hex -f nrf52 --chiperase

### ソフトデバイスありの場合

nrfjprog --program ファイル名.hex -f nrf52 --sectorerase

### 最後にリセット命令

nrfjprog --reset -f nrf52

###　書き込めないときは

nrfjprog --rbp ALL -f nrf52
