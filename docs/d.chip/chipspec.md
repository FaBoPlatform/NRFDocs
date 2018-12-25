# BLEチップの感度比較


## 4.2対応BLEチップ

| Chip名 | 送信感度 | 0dBm時<br>送信時電流 | 受信感度 | 受信時電流 |
| -- | -- | -- | -- |
|[DA14680](http://www.dialog-semiconductor.com/docs/site-pdf/dialog-smartbond-da14680-product-brief-japanese.pdf?sfvrsn=2)| 0dBm |4.2mA | -93dBm | 4.3mA | 
| [BGM111](http://www.silabs.com/products/wireless/bluetooth/Pages/bluegecko-bluetooth-smart-module-intro.aspx) |+8 dBm | 8.2 mA |  -93dBm |7.5 mA |
| [NRF52832](https://www.nordicsemi.com/Products/Bluetooth-Smart-Bluetooth-low-energy/nRF52832) | +4dBm |9.6mA<br>5.4mA(DD*)| -96dBm | 10.9mA<br>6.1mA(DD*) |

* DDは、DC/DCコンバーターの略
* 
## 4.1対応BLEチップ

| Chip名 | 送信感度 | 0dBm時<br>送信時電流 | 受信感度 | 受信時電流 |
| -- | -- | --- |
| [DA14580](http://www.dialog-semiconductor.com/products/bluetooth-smart) | 0dBm | 3.4mA(DD*) | -93dBm| 3.7mA(DD*) |
| [NRF51822](http://www.nordicsemi.com/eng/Products/Bluetooth-R-low-energy/nRF51822) | +4dBm |10.5mA<br>8mA (DD*) |-93dBm|  13mA<br>9.7mA(DD*)| 
| [NRF51422](http://www.nordicsemi.com/eng/Products/ANT/nRF51422) | +4dBm |10.5mA<br>8mA (DD*) |-93dBm|  13mA<br>9.7mA(DD*)| 
| [BCM20737S](http://www.broadcom.com/collateral/pb/WICED-Sense-PB100.pdf) | +8dBm | 8.2mA| -96dBm | 7.3mA| 
| [CYBL10X6X](http://japan.cypress.com/?rID=99422 ) |+3dBm |15.6mA |-89dBm| 16.4mA|
| [CC2640](http://www.tij.co.jp/product/jp/cc2640)|+5dBm|+5dBm時 9.1mA<br>0dBm時 6.1 mA|–97dBm|5.9mA|

* DDは、DC/DCコンバーターの略　

## BLE4.0

| Chip名 | 送信感度 | 0dBm時<br>送信時電流 | 受信感度 | 受信時電流 |
| -- | -- | --- |
| [CSR1010](https://www.csrsupport.com/download/39359/CSR1010%20Data%20Sheet%20CS-231985-DS.pdf) | +9dBm | | -93dBm| |
| [CSR1011](https://www.csrsupport.com/download/40289/CSR1010%20Data%20Sheet%20CS-231986-DS.pdf)  | +9dBm | | -93dBm| |
| [CSR1012](https://www.csrsupport.com/download/47278/CSR1012%20Data%20Sheet%20CS-238833-DS.pdf)  | +9dBm | | -93dBm| |
| [BlueNGR](http://www.st.com/web/catalog/sense_power/FM1968/CL1976/SC1898/PF258646?ecmp=pf258646_link_emf_jan2014&sc=bluenrg) | +8dBm | 8.2mA| -96dBm |7.3mA|
| [QN902X](http://www.nxp.com/documents/data_sheet/QN902X.pdf) |+4dBm|9.9mA(DD*) |-95dBm<br>-93dBm(DD*) | 9.25mA(DD*)
| [CC2540](http://m.tij.co.jp/product/jp/CC2540)| +6dBm | 24mA<br>15.8 mA(DD)<br> | -96dBm| 19.6 mA<br>18.6 mA(DD)<br>|
| [CC2541](http://m.tij.co.jp/product/jp/CC2541) | +6dBm | 18.2 mA<br>14.7mA(DD)| -96dBm| 17.9 mA <br>14.7mA(DD)| 
|[TZ1000](http://toshiba.semicon-storage.com/jp/product/assp/applite/tz1000.html) ||-4dBm時<br>6.3mA | | |
|[ML1705-002](http://www.lapis-semi.com/jp/semicon/telecom/ble.html)| |9mA||9mA|
| [CC2564](http://www.ti.com/product/cc2564) |+12dBm|||||

* DDは、DC/DCコンバーターの略