# Sample

## 使用できるサンプル

BLEなしのサンプル
```
nRF5_SDK_14.2.0_17b948a/examples/peripheral
```

BLEありのサンプル
```
nRF5_SDK_14.2.0_17b948a/examples/ble_central
```


## Blink

nRF5_SDK_14.2.0_17b948a/examples/peripheral/blinky/pca10040/s132/ses

のプロジェクトを開く。

main.c
```c
#include "nrf_delay.h"
#include "nrf_gpio.h"

const uint8_t led_pin = 18; /*P0.03使用　constで修飾する場合は定数はROMに格納されRAM領域の節約になる*/

int main(void)
{
      nrf_gpio_cfg_output(led_pin);/*ポートを出力に設定*/
    while (true)
    {

          uint32_t gpio_state = NRF_GPIO->OUT;/*ポートレジスタの値を取得*/
          NRF_GPIO->OUTSET = ((1 << led_pin) & ~gpio_state);
          NRF_GPIO->OUTCLR = ((1 << led_pin) & gpio_state);
          nrf_delay_ms(1000);/*１秒無しもしない*/
    }
}
```