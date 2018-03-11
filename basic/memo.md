# メモ

## 差分 app_timer.h

nRF_libraries: 3.0.1

	APP_TIMER_INIT(PRESCALER, MAX_TIMERS, OP_QUEUES_SIZE, USE_SCHEDULER)		

https://devzone.nordicsemi.com/documentation/nrf51/6.1.0/s110/html/a00682.html#ga9eb4ec72345e8b61aa833ee299a788fe

nRF_libraries: 3.1.0(SDK10)


	APP_TIMER_INIT(PRESCALER,OP_QUEUES_SIZE,SCHEDULER_FUNC);

APP_TIMER_INTマクロのMAX_TIMES変数が廃止。

http://infocenter.nordicsemi.com/index.jsp?topic=%2Fcom.nordic.infocenter.sdk51.v10.0.0%2Fgroup__app__timer.html&anchor=ga63243f2b20523cb832fe0bf3d56c1bc9

## sd_app_evt_wait

sd_app_evt_waitは、#include "nrf_sdm.h"で使えるようになる。

## type

BLE_UUID_TYPE_VENDOR_BEGINは、S110のSDK 8のble_types.hで定義

https://developer.nordicsemi.com/nRF51_SDK/nRF51_SDK_v8.x.x/doc/8.0.0/s110/html/a00864.html

## Service UUID definitions

Service UUID definitions

ble_srv_common.h で定義

http://infocenter.nordicsemi.com/index.jsp?topic=%2Fcom.nordic.infocenter.sdk51.v10.0.0%2Fgroup___u_u_i_d___s_e_r_v_i_c_e_s.html&resultof=%22Service%22%20%22servic%22%20%22UUID%22%20%22uuid%22%20%22definitions%22%20%22definit%22%20
