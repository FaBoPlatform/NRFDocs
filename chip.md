# BLEチップ

## BLEチップ種類

| Chip名 | Maker |Co-Proccesor| 送信感度|受信感度<br>|送信時最大電流<br>(0dBm時) | 受信時最大電流|
| -- | -- |
| [DA14580](http://www.dialog-semiconductor.com/products/bluetooth-smart) | [dialog](http://www.dialog-semiconductor.com/) | ARM® Cortex™ M0 |0dBm |-93dBm |3.4mA(DD) |3.7mA(DD)| 
|[DA14680](http://www.dialog-semiconductor.com/docs/site-pdf/dialog-smartbond-da14680-product-brief-japanese.pdf?sfvrsn=2)|[dialog](http://www.dialog-semiconductor.com/) | ARM® Cortex™ M0 | | | | | 
| [NRF51822](http://www.nordicsemi.com/eng/Products/Bluetooth-R-low-energy/nRF51822) | [Nordic Semiconductor](http://www.nordicsemi.com/)  |  ARM® Cortex™ M0 |+4dBm |-93 dBm| 10.5mA<br>8mA (DD)| 13 mA<br>9.7mA(DD)| 
| [NRF51422](http://www.nordicsemi.com/eng/Products/ANT/nRF51422)  | [Nordic Semiconductor](http://www.nordicsemi.com/)|  ARM® Cortex™ M0 |+4dBm |-93 dBm| 10.5mA<br>8mA (DD)| 13 mA<br>9.7mA(DD)| 
| [CSR1010](https://www.csrsupport.com/download/39359/CSR1010%20Data%20Sheet%20CS-231985-DS.pdf) | [CSR](http://www.csr.com/) | 独自MCU(RISC) | +9dBm | -93dBm| |
| [CSR1011](https://www.csrsupport.com/download/40289/CSR1010%20Data%20Sheet%20CS-231986-DS.pdf) | [CSR](http://www.csr.com/)  | 独自MCU(RISC) | +9dBm | -93dBm| ||
| [CSR1012](https://www.csrsupport.com/download/47278/CSR1012%20Data%20Sheet%20CS-238833-DS.pdf) | [CSR](http://www.csr.com/)  | 独自MCU(RISC) | +9dBm | -93dBm| ||
| [CC2540](http://m.tij.co.jp/product/jp/CC2540)| [TI](http://www.tij.co.jp/) |  8051互換 | +6dBm | -96dBm|24mA<br>15.8 mA(DD)<br>*-6dBm|19.6 mA<br>18.6 mA(DD)<br>|
| [CC2541](http://m.tij.co.jp/product/jp/CC2541) | [TI](http://www.tij.co.jp/) |  8051互換 | +6dBm | -96dBm|18.2 mA<br>14.7mA(DD)| 17.9 mA <br>14.7mA(DD)|  
| [BCM20737S](http://www.broadcom.com/collateral/pb/WICED-Sense-PB100.pdf) | [Broadcom](http://ja.broadcom.com/) |  ARM® Cortex™ M3 ||||||
| [BlueNGR](http://www.st.com/web/catalog/sense_power/FM1968/CL1976/SC1898/PF258646?ecmp=pf258646_link_emf_jan2014&sc=bluenrg) | [STMicro](http://www.st-japan.co.jp/web/jp/home.html) | ARM® Cortex™ M0 | +8dBm |-96dBm | 8.2mA| 7.3mA| 
| [CYBL10X6X](http://japan.cypress.com/?rID=99422 ) | [CYPRESS](http://japan.cypress.com/) |ARM® Cortex™ M0| +3dBm |-89dBm|15.6mA| 16.4mA|
|[TZ1000](http://toshiba.semicon-storage.com/jp/product/assp/applite/tz1000.html) |[Toshibaセミコン](http://toshiba.semicon-storage.com/) |ARM® Cortex™ M4F||||||
|[ML1705-002](http://www.lapis-semi.com/jp/semicon/telecom/ble.html)|[LAPIS](http://www.lapis-semi.com)|ARM® Cortex™ M0|||9mA|9mA|

*DDは、DC/DC変換の略

#DA14580のBlock diagram

![](image/da14580.png)

#NRF51822のBlock diagram
![](image/nrf51822.png)

#CYBL10X6XのBlock diagram
![](image/cybl10x6x.png)

#CSR1012のBlock diagram
![](image/csr1012.png)

#CC2541のBlock diagram
![](image/cc2541.png)

#BlueNGRのBlock diagram
![](image/BlueNGR.png)

#TZ1000のBlock diagram
![](image/tz1000.png)

# ML7105のBlock diagram
![](image/ml7105.png)
