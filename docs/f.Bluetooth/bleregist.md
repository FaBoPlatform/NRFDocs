# Bluetooth認証

## Bluetooth SIGについて
自社製品およびサービスに Bluetooth 技術を使用、自社商品とサービスの提供に Bluetooth ブランドを活用、または
Bluetooth 技術を使用する製品を再ブランド化または再販売する企業は、Bluetooth SIGへ加入しなければならない。<br>

Bluetooth SIG のアダプターメンバーとして、直ちに以下を獲得できる

* Bluetooth 無線技術を使って製品を開発する許可
* Bluetooth ワードマークと Bluetooth Smart および Bluetooth Smart Ready ロゴを認証されて登録された製品で使用する許可
* 多種多様な業界の何千社もの Bluetooth SIG メンバーと交流し協力する機会
* プロファイルチューニングスイート供与(試験ツールやテスト仕様)

## Bluetooth認証

Bluetooth搭載のハードウェアを製品化した場合、認証登録(デザイン登録、プロダクト登録)が必要。
売り上げ1億円以上だと8000ドル、設立2年以内で売り上げ1億円以下だと、2500ドルで手続きできる。
Bluetooth関連製品を開発をする場合、BT SIG のメンバーシップになる必要があるが、個人では登録きないので、法人もしくは団体で登録する。

> Bluetooth認証プログラムによって、認証された製品が市場の期待を満たしているという大きな信頼をメンバーならびに消費者に与えることができます。Bluetooth認証プログラムを取得しないでBluetooth対応製品を製造したり、ライセンスを取得しないでBluetoothトレードマークを使用する企業や個人に対しては法的な手段をとる場合があります。<br><br>
トレードマークの使用(Bluetooth SIG) https://www.bluetooth.org/docman/handlers/DownloadDoc.ashx?doc_id=67617

* [認証および登録プロセス](https://www.bluetooth.org/ja-jp/test-qualification/qualification-overview)<br>
* [認証および登録料金](https://www.bluetooth.org/ja-jp/test-qualification/qualification-overview/fees)

一般的に、Bluetooth搭載のハードウェアを製品化し、それが開発者向けではない場合、認証に$8000がかかる。売上1億円以下で設立2年以内の会社には、$2500で、2回まで認証が受けられる特例が設けられている。


# 各社モジュールのQDID(デザイン登録ID)
| Chip名 | QDID |
| -- | -- |
| nRF51822,nRF51422 | [66456](https://www.bluetooth.org/tpg/QLI_viewQDL.cfm?qid=25689),[66455](https://www.bluetooth.org/tpg/QLI_viewQDL.cfm?qid=25690),[66453](https://www.bluetooth.org/tpg/QLI_viewQDL.cfm?qid=25691) |
| BLE113 |[46266](https://www.bluetooth.org/tpg/QLI_viewQDL.cfm?qid=21015)|
| BLE112 |[35451](https://www.bluetooth.org/tpg/QLI_viewQDL.cfm?qid=18943) |
| BLE121 | [57409](https://www.bluetooth.org/tpg/QLI_viewQDL.cfm?qid=25691)|
|DA14580|[56907](https://www.bluetooth.org/tpg/QLI_viewQDL.cfm?qid=22759), [52690](https://www.bluetooth.org/tpg/QLI_viewQDL.cfm?qid=22409), [52696](https://www.bluetooth.org/tpg/QLI_viewQDL.cfm?qid=22410)|
|CSR1010|[65475](https://www.bluetooth.org/tpg/QLI_viewQDL.cfm?qid=25607)|
|CSR1011,CSR1012|[31021](https://www.bluetooth.org/tpg/QLI_viewQDL.cfm?qid=17702)|
|CC2541,CC2540|[35040](https://www.bluetooth.org/tpg/QLI_viewQDL.cfm?qid=19095),[23454](https://www.bluetooth.org/tpg/QLI_viewQDL.cfm?qid=16552)

モジュールそのものを用いる場合は、仕様するモジュールのQDIDを用いて、プロダクト認証をおこなう。

## FAQ 

### iBeaconを開発した場合はどうなるか？

はじめて登録する場合は、デザイン登録、プロダクト登録が必要となる。Declaration Feeは発生する。

### BLEモジュールを使ったハードウェアで、ケースを変えた場合はどうなるか？

* デザイン認証が異なるモジュールを使う場合は、Declaration Feeは発生
* デザイン認証が同じでも、新たにBT SIG標準プロファイルを追加した派生モデルをプロドダクト登録する場合は、Declaration Feeは発生
* デザイン認証が同じで、新たに独自のカスタマイズプロファイルを追加する場合は、派生モデルとして、Declaration Feeは発生しない
* デザイン認証が同じで、プロファイルを追加する場合、派生モデルとして、Declaration Feeは発生しない

### 一度、認証登録したハードのFirmwareをUpdateした場合はどうなるか？

Update内容に、新たにBT SIG標準プロファイルの追加がない場合は、問題ない。

### Bluetoothモジュールを使っている場合は、どのような場合、認証登録が必要になるか？

Bluetoothモジュールを使っている場合でも、新しいハードウェアを開発する場合は、デザイン登録、プロダクト登録が必要となる。

# 用語集
| 用語 | 意味 |
| -- | -- |
| BTQF | BT認証をおこなっているBT SIG認定の機関。 |
|BQB | Bluetooth Qualification Bodyの略。Bluetoothのロゴ認証システムの公認判定者。ロゴの取得を申請してきたメーカに対して，その合否を判定する役割を果たす。|
|デザイン認証 | 「チップ＋スタック＋PCB／アンテナ」あるいは、「（それらを含んだ）モジュール」の認証|
|プロダクト認証 | 認証されたデザインを利用した最終製品としての認証。BT SIGの標準プロファイルを利用する場合は、そのプロファイルを「プロファイル・サブシステム」として、認証する（これは、BT SIGより無料でダウンロードできるPTS:Profiule Tunning Suiteを使って自分でテストして、ログを提出する。　独自プロファイルは（GATTベースプロファイル）認証は不要。|
|QDID|各モジュールのデザイン認証番号（プロダクト登録に必要）|
| PTS| Profile Tuning Suiteの略。標準のプロファイル試験パッケージ|




# 国内のBTQF認定機関

* [UL](http://site.ul.com/)
* [テュフ ラインランド ジャパン](http://www.tuv.com/jp/japan/home.jsp)
* [アリオン株式会社](http://www.allion.co.jp/about.html)
* [太陽誘電](http://www.yuden.co.jp/jp/)
* [Paltek](http://www.paltek.co.jp/)
* 
# 参考になる情報
* [Understanding Bluetooth® Special Interest Group (SIG) Fees](http://na.industrial.panasonic.com/blog/understanding-bluetooth%C2%AE-special-interest-group-sig-fees)(Panasonic)
* [Bluetooth Qualification Program”と日本の型式認定制度](https://www.toshiba.co.jp/tech/review/2001/04/56_04pdf/a10.pdf)

