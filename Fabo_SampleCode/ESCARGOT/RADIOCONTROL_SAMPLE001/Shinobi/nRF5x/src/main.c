// GRIDEYE_SENSING for nRF5 SDK 12.2.0
//Version 1.0.0 A
#include <string.h>
#include "bsp.h"
#include "boards.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "app_timer.h"
#include "app_button.h"
#include "nrf_delay.h"
#include "ble_dis.h"
#include "peer_manager.h"

#include "aka_service.h"
#include "advertising.h"
#include "blestack.h"
#include "gaputil.h"
#include "peer.h"
#include "storage.h"
#include "aka_service.h"


#include "app_uart.h"

#include "nrf_drv_twi.h"

/* TWI instance ID. */
#define TWI_INSTANCE_ID     0

//JINK ascii code Service Name
#define SERVICE_NAME_1 0x00
#define SERVICE_NAME_2 0x00
#define SERVICE_NAME_3 0x00
#define SERVICE_NAME_4 0x00

//TWI(I2C)Pin設定
#define TWI0_SCL 27
#define TWI0_SDA 26

#define MANUFACTURER_NAME               "GClue,Inc."

#define APP_ADV_INTERVAL                100

#define APP_TIMER_PRESCALER             0                                           /**< Value of the RTC1 PRESCALER register. */
#define APP_TIMER_OP_QUEUE_SIZE         4                                           /**< Size of timer operation queues. */
#define BUTTON_DETECTION_DELAY APP_TIMER_TICKS(50, APP_TIMER_PRESCALER)
// ADCタイマーの間隔
#define BEACON_TIMER_INTERVAL              80   

// 接続待ち時間
#define CONNECTION_TIME 10000

//DRV8830 i2c deviceAdress
#define DRV8830_ADDR_Motor1	(0x64)
#define DRV8830_ADDR_Motor2	(0x63)

//DRV8830 Registor
#define CONTROL_ADDR    0x00
#define FALUT_ADR       0x01
#define MOTOR_STANBY    0x00  
#define MOTOR_REVERSE   0x01
#define MOTOR_NORMAL    0x02
#define MOTOR_BRAKE     0x03
#define MAX_VOLTAGE     0x3F
#define MIN_VOLTAGE     0x01

// The -40dBm setting is only available on nRF52 series ICs.
static int8_t tx_power[] = {-40, -30, -20, -16, -12, -8, -4, 0, 4};

//Shinobiコネクションモード、ステータスフラグ
static bool connectionMode = false;
static bool connected = false;

//TWI実行終了フラッグ
static volatile bool m_xfer_done = false;

//TWI（I2C） インスタンス
static const nrf_drv_twi_t nrf_drv_twi_DRV8830 = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);

//BEACONペイロード
static uint8_t m_beacon_info[23];

//サービスデータ
static aka_data m_aka_data;

//I2Cバッファデータ
static uint8_t m_sample[32];

//GRIDEYEマトリックスデータ
static volatile uint8_t pixcel[64];

// BEACONタイマー
APP_TIMER_DEF(beacon_timer_id);

// 接続タイマー作成
APP_TIMER_DEF(timer_id);

// Beacon情報
static beacon_info_t beacon_info;

//Prototype
static void connection_enabled(bool enabled);

// エラーハンドラ
__WEAK void app_error_fault_handler(uint32_t id, uint32_t pc, uint32_t info)
{
    switch (id)
    {
        case NRF_FAULT_ID_SDK_ASSERT: {
            NRF_LOG_ERROR("**Assert!**\r\n");
            volatile assert_info_t *assert_info = (assert_info_t*)info;
            NRF_LOG_ERROR("Line:%d\r\n", assert_info->line_num);
            NRF_LOG_ERROR("File:%c\r\n", assert_info->p_file_name[0]);
        } break;
        case NRF_FAULT_ID_SDK_ERROR: {
            NRF_LOG_ERROR("**Error!**\r\n");
            volatile error_info_t *error_info = (error_info_t*)info;
            NRF_LOG_ERROR("Line:%d\r\n", error_info->line_num);
            NRF_LOG_ERROR("File:%s\r\n", nrf_log_push((char*)error_info->p_file_name));
            NRF_LOG_ERROR("Code:%d\r\n", error_info->err_code);
        } break;
    }
    NRF_LOG_FINAL_FLUSH();

    NVIC_SystemReset();
}

__STATIC_INLINE void data_handler(uint8_t tempSample[32])
{

	}

    void twi_handler(nrf_drv_twi_evt_t const * p_event, void * p_context)
{
    switch (p_event->type)
    {
        case NRF_DRV_TWI_EVT_DONE:
            if (p_event->xfer_desc.type == NRF_DRV_TWI_XFER_RX)
            {
                data_handler(m_sample);
            }
            m_xfer_done = true;
            break;
        default:
            break;
    }
}
void twi_init (void)
{
    ret_code_t err_code;

    const nrf_drv_twi_config_t twi_grideye_config = {
       .scl                = TWI0_SCL,
       .sda                = TWI0_SDA,
       .frequency          = NRF_TWI_FREQ_100K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
       .clear_bus_init     = false
    };

    err_code = nrf_drv_twi_init(&nrf_drv_twi_DRV8830, &twi_grideye_config, twi_handler, NULL);
    APP_ERROR_CHECK(err_code);

    nrf_drv_twi_enable(&nrf_drv_twi_DRV8830);
}



// Timerイベント
static void timeout_handler(void * p_context)
{
    //パケット送信タイマー
    if (p_context == beacon_timer_id) {
        //メインパケット
        static uint16_t main_packetid = 0;
        //サブパケット
        static uint8_t id_pakect_number = 0;

        //NRF_LOG_INFO("DATA SEND >>>>:main_pakect%d\r\n",main_packetid);
        //NRF_LOG_INFO(">>>>:id_pakect_number%d\r\n",id_pakect_number);

     // データダンプ
     /*
    NRF_LOG_DEBUG("-name: %s \r\n", (uint32_t)m_aka_data.name);
    NRF_LOG_DEBUG("-ver: %d \r\n", m_aka_data.ver);
    NRF_LOG_DEBUG("-major: %d \r\n", m_aka_data.beacon_info.major);
    NRF_LOG_DEBUG("-minor: %d \r\n", m_aka_data.beacon_info.minor);
    NRF_LOG_DEBUG("-uuid: \r\n");
    NRF_LOG_HEXDUMP_DEBUG(m_aka_data.beacon_info.uuid, 23);
    */
        //Grid_Eye_Original_Format
        //独自サービスネームセット
        m_beacon_info[0] = SERVICE_NAME_3;
        m_beacon_info[1] = SERVICE_NAME_4;
        //機器番号セット
        m_beacon_info[2] = MSB_16(m_aka_data.beacon_info.major);
        m_beacon_info[3] = LSB_16(m_aka_data.beacon_info.major); 
        //メインパケットナンバーセット
        m_beacon_info[4] = MSB_16(main_packetid);
        m_beacon_info[5] = LSB_16(main_packetid);
        //サブパケットナンバーセット
        m_beacon_info[6] = id_pakect_number;
        //GRIDEYEデータセット
        switch(id_pakect_number){
            case 0:
                for (int ii= 7;ii<23;ii++){
                    m_beacon_info[ii] = pixcel[ii-7];
                }
                break;
            case 1:
                for (int ii= 7;ii<23;ii++){
                    m_beacon_info[ii] = pixcel[ii+9];
                }
                break;
            case 2:
                for (int ii= 7;ii<23;ii++){
                    m_beacon_info[ii] = pixcel[ii+25];
                }
                break;
            case 3:
                for (int ii= 7;ii<23;ii++){
                    m_beacon_info[ii] = pixcel[ii+41];
                }
                break;
            default:
                break;
        }
        //パイロードデバッグ
        //for (int ii= 7;ii<23;ii++){
          //          NRF_LOG_INFO("id=%d [%d]:%d\r\n",id_pakect_number,ii,m_beacon_info[ii]/2);
            //    }
        beacon_stop();
        memcpy(beacon_info.uuid, m_beacon_info, 23);
        beacon_init(beacon_info,SERVICE_NAME_1 + (SERVICE_NAME_2<<8));
        beacon_start();
        main_packetid++;
        id_pakect_number++;
        if (id_pakect_number>=4){
            id_pakect_number = 0;
        }
    }else if (p_context == timer_id && !connected) {
        //接続タイムアウト
        NRF_LOG_INFO("timerd>>\r\n");
        connection_enabled(false);
    }
}

// ボタンイベントハンドラ
static void button_event_handler(uint8_t pin_no, uint8_t button_action)
{
    if(button_action == APP_BUTTON_PUSH){
        switch(pin_no) {
            case BSP_BUTTON_0:
                NRF_LOG_INFO("BUTTON_0\r\n");
                connection_enabled(true);
                break;
            default:
                APP_ERROR_HANDLER(pin_no);
                break;
        }
    }
}

// ボタン初期化
static bool buttons_init(void)
{
    uint32_t err_code;
    
    static app_button_cfg_t buttons[] = {
        {BSP_BUTTON_0, APP_BUTTON_ACTIVE_LOW, BUTTON_PULL, button_event_handler},
    };
        
    err_code = app_button_init(buttons,  sizeof(buttons) / sizeof(buttons[0]),  BUTTON_DETECTION_DELAY);
    APP_ERROR_CHECK(err_code);
    
    err_code = app_button_enable();
    APP_ERROR_CHECK(err_code);

    return app_button_is_pushed(0);
}
// BLEイベントハンドラ
static void on_ble_evt(ble_evt_t * p_ble_evt)
{
    NRF_LOG_DEBUG("on_ble_evt:%d\r\n", p_ble_evt->header.evt_id);
    uint32_t err_code;

    // Advertising
    advertising_ble_evt(p_ble_evt);
    // PeerManager
    pm_on_ble_evt(p_ble_evt);
    // Shinobi
    aka_service_ble_evt(p_ble_evt);

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_DISCONNECTED:
            connected = false;
            // 名前設定
            gap_name_set(m_aka_data.name);
            // TX設定
            err_code = sd_ble_gap_tx_power_set(tx_power[m_aka_data.tx_power]);
            APP_ERROR_CHECK(err_code);
            // 接続切り替え
            connection_enabled(false);
            // 設定値の保存
            storage_save(&m_aka_data, sizeof(aka_data));
            break; // BLE_GAP_EVT_DISCONNECTED

        case BLE_GAP_EVT_CONNECTED:
            connected = true;
            // LED点灯
            err_code = bsp_indication_set(BSP_INDICATE_CONNECTED);
            APP_ERROR_CHECK(err_code);
            break; // BLE_GAP_EVT_CONNECTED
    }
}



// 接続可能状態の切り替え
static void connection_enabled(bool enabled)
{
    uint32_t err_code;
    if (connectionMode == enabled) return;
    connectionMode = enabled;
    NRF_LOG_INFO("connectionEnabled:%d\r\n", enabled ? 1 : 0);

    if (enabled) {
        //接続状態できる。
        //ADCタイマー停止
        err_code = app_timer_stop(beacon_timer_id);
        APP_ERROR_CHECK(err_code);
        // Beacon停止
        NRF_LOG_INFO("#######Enabled=True.##########\r\n");
        beacon_stop();

        // Advertising開始
        ble_uuid_t adv_uuids[] = 
        {
            {BLE_UUID_DEVICE_INFORMATION_SERVICE, BLE_UUID_TYPE_BLE},
            {BLE_UUID_BATTERY_SERVICE, BLE_UUID_TYPE_BLE}
        };
        advertising_init(adv_uuids);
        advertising_start(APP_ADV_INTERVAL, 0);

        // Timer開始
        err_code = app_timer_start(timer_id, APP_TIMER_TICKS(CONNECTION_TIME, 0), (void*)timer_id);
        APP_ERROR_CHECK(err_code);

        // LED点滅
        err_code = bsp_indication_set(BSP_INDICATE_ADVERTISING);
        APP_ERROR_CHECK(err_code);
    } else {
        //接続できない。
        NRF_LOG_INFO("#######Enabled=Flase.##########\r\n");
        // Advertising停止
        advertising_stop();
        if (m_aka_data.enabled) {
            // Beacon開始
            //beacon_init(m_aka_data.beacon_info);
            //beacon_init(m_aka_data.beacon_info,0x00);
            //beacon_start();
            NRF_LOG_INFO("######m_aka_data.enabled##########\r\n");
            // Timer開始
            err_code = app_timer_start(beacon_timer_id, APP_TIMER_TICKS(BEACON_TIMER_INTERVAL, 0), (void*)beacon_timer_id);
            APP_ERROR_CHECK(err_code);
        }

        // Timer停止
        err_code = app_timer_stop(timer_id);
        APP_ERROR_CHECK(err_code);

        // LED消灯
        err_code = bsp_indication_set(BSP_INDICATE_IDLE);
        APP_ERROR_CHECK(err_code);
    }
}

// サービス設定
static void services_init() {
    uint32_t err_code;

    // DeviceInformationサービス
    ble_dis_init_t dis_init;
    memset(&dis_init, 0, sizeof(dis_init));
    ble_srv_ascii_to_utf8(&dis_init.manufact_name_str, (char *)MANUFACTURER_NAME);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&dis_init.dis_attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&dis_init.dis_attr_md.write_perm);
    err_code = ble_dis_init(&dis_init);
    APP_ERROR_CHECK(err_code);

    NRF_LOG_INFO("**DeviceInformation**\r\n");

    // AkaBeacon設定サービス
    aka_service_init(&m_aka_data);
    NRF_LOG_INFO("**aka_service_init**\r\n");

}


int main()
{
    uint32_t err_code;

    // ログ初期化
    err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);
    NRF_LOG_INFO("**GRIDEYE_SENSING**\r\n");

    // Timer初期化
    APP_TIMER_INIT(APP_TIMER_PRESCALER, APP_TIMER_OP_QUEUE_SIZE, false);
    err_code = app_timer_create(&beacon_timer_id, APP_TIMER_MODE_REPEATED, timeout_handler);
    APP_ERROR_CHECK(err_code);

    //Timer初期化
    err_code = app_timer_create(&timer_id, APP_TIMER_MODE_SINGLE_SHOT, timeout_handler);
    APP_ERROR_CHECK(err_code);

    // BLEStack初期化
    ble_stack_init(on_ble_evt);

    // DCDCを有効化
//#if (NRF_SD_BLE_API_VERSION == 3)
    //NRF_POWER->DCDCEN = 1;
    //sd_power_dcdc_mode_set(NRF_POWER_DCDC_ENABLE);
//#endif
    sd_power_dcdc_mode_set(NRF_POWER_DCDC_ENABLE);

    // BSP初期化
    err_code = bsp_init(BSP_INIT_LED, APP_TIMER_TICKS(100, APP_TIMER_PRESCALER), NULL);
    APP_ERROR_CHECK(err_code);
   
    // Storage初期化
    storage_init();

    // ボタン設定
    if (buttons_init()) {
        NRF_LOG_INFO("*clear data\r\n");
        // 起動時にボタンが押されていたらFlash初期化
        storage_clear();
        // 初期データ設定
        akadata_init(&m_aka_data);
        // PeerManager設定（初期化）
        peer_manager_init(true);
    } else {
        NRF_LOG_INFO("*load data\r\n");
        // データ読み込み
        storage_load(&m_aka_data, sizeof(aka_data));
        // データが不正な場合は初期データ設定
        if (m_aka_data.ver != AKA_DATA_VER) {
            akadata_init(&m_aka_data);
        }
        // PeerManager設定
        peer_manager_init(false);
    }
    
    // GAP設定
    gap_name_set(m_aka_data.name);
    gap_params_init();
     NRF_LOG_INFO("*gap_params_init\r\n");

    // サービス設定
    services_init();
    NRF_LOG_INFO("*services_init()\r\n");
    
    // TX設定
    err_code = sd_ble_gap_tx_power_set(tx_power[m_aka_data.tx_power]);
    NRF_LOG_INFO("sd_ble_gap_tx_power_set\r\n");
    APP_ERROR_CHECK(err_code);

    // LED点滅
    err_code = bsp_indication_set(BSP_INDICATE_ADVERTISING);
    NRF_LOG_INFO("bsp_indication_set\r\n");
    APP_ERROR_CHECK(err_code);

    // Beacon情報初期化
    beacon_info.major = 0x0000;
    beacon_info.minor = 0x0000;
    beacon_info.interval = 200;
    beacon_info.measured_pow = 0x00;
    beacon_info.channel_mask.ch_37_off = false;
    beacon_info.channel_mask.ch_38_off = false;
    beacon_info.channel_mask.ch_39_off = false;
    memcpy(beacon_info.uuid, m_beacon_info, 23);
    
    //接続可能状態にする。
    connection_enabled(true);
    NRF_LOG_INFO("connection_enabled\r\n");

    twi_init();

    //DVR8830　初期設定
		    uint8_t reg[2] = {CONTROL_ADDR,0x00+(0x09<<2)};
            nrf_drv_twi_tx(&nrf_drv_twi_DRV8830, DRV8830_ADDR_Motor1, reg, sizeof(reg), false);
		    nrf_delay_ms(1);
            nrf_drv_twi_tx(&nrf_drv_twi_DRV8830, DRV8830_ADDR_Motor2, reg, sizeof(reg), false);
		    nrf_delay_ms(1000);


  while (true)
    {
            do
            {
                __WFE();
            }while (m_xfer_done == false);

		    NRF_LOG_INFO("\n\r Major=%d\r\n",LSB_16(m_aka_data.beacon_info.major));
            NRF_LOG_FLUSH();
            switch(LSB_16(m_aka_data.beacon_info.major)){
                case 0:
                    NRF_LOG_INFO("\n\rRight Rotation\r\n");
                    NRF_LOG_FLUSH();
                    reg[1] = MOTOR_NORMAL+(20<<2);
                    nrf_drv_twi_tx(&nrf_drv_twi_DRV8830, DRV8830_ADDR_Motor1, reg, sizeof(reg), false);
                    nrf_delay_ms(1);
                    nrf_drv_twi_tx(&nrf_drv_twi_DRV8830, DRV8830_ADDR_Motor2, reg, sizeof(reg), false);
                    nrf_delay_ms(10);
                    break;
                case 1:
                    NRF_LOG_INFO("\n\rLEFT Rotation\r\n");
                    NRF_LOG_FLUSH();
                    reg[1] = MOTOR_REVERSE+(20<<2);
                    nrf_drv_twi_tx(&nrf_drv_twi_DRV8830, DRV8830_ADDR_Motor1, reg, sizeof(reg), false);
                    nrf_delay_ms(1);
                    nrf_drv_twi_tx(&nrf_drv_twi_DRV8830, DRV8830_ADDR_Motor2, reg, sizeof(reg), false);
                    nrf_delay_ms(10);
                    break;
                case 2:
                    NRF_LOG_INFO("\n\rADVANCE\r\n");
                    NRF_LOG_FLUSH();
                    reg[1] = MOTOR_NORMAL+(20<<2);
                    nrf_drv_twi_tx(&nrf_drv_twi_DRV8830, DRV8830_ADDR_Motor1, reg, sizeof(reg), false);
                    nrf_delay_ms(1);
                    reg[1] = MOTOR_REVERSE+(20<<2);
                    nrf_drv_twi_tx(&nrf_drv_twi_DRV8830, DRV8830_ADDR_Motor2, reg, sizeof(reg), false);
                    nrf_delay_ms(10);
                    break;
                case 3:
                    NRF_LOG_INFO("\n\rBACKFORWARD\r\n");
                    NRF_LOG_FLUSH();
                    reg[1] = MOTOR_REVERSE+(20<<2);
                    nrf_drv_twi_tx(&nrf_drv_twi_DRV8830, DRV8830_ADDR_Motor1, reg, sizeof(reg), false);
                    nrf_delay_ms(1);
                    reg[1] = MOTOR_NORMAL+(20<<2);
                    nrf_drv_twi_tx(&nrf_drv_twi_DRV8830, DRV8830_ADDR_Motor2, reg, sizeof(reg), false);
                    nrf_delay_ms(10);
                    break;
                default:
                    break;
            }
    }
    return 0;
}
