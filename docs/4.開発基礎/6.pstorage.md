# Persistent Storage Interface


```c
#include <stdbool.h>
#include "nrf_delay.h"
#include "app_trace.h"
#include "app_error.h"
#include "storage.h"
#include "ble_conn_params.h"
#include "nrf_sdm.h"
#include "softdevice_handler.h"
#include "pstorage.h"

static uint8_t pstorage_wait_flag = 0;
static pstorage_block_t pstorage_wait_handle = 0;

/**
 * @brief エラーハンドラ.APP_ERROR_CHECKでエラーが発生している場合は、呼ばれる.
 */
void app_error_handler	(	uint32_t 	error_code,
		uint32_t 	line_num,
		const uint8_t * 	p_file_name 
)	{
	app_trace_log("error_code: %d\r\n", error_code);
	app_trace_log("line_num:  %d\r\n", line_num);
	app_trace_log("p_file_name: %s\r\n", p_file_name);
}

/**
 * @brief 関連するModule群にシステムイベントを送出する関数.
 *
 * @details システムイベントが発生したあとに、システムイベント割り込みハンドラから呼び出される.
 *
 * @param[in]  sys_evt システムスタックイベント
 */
static void sys_evt_dispatch(uint32_t sys_evt)
{
        pstorage_sys_event_handler(sys_evt);

}

/**
 * @brief BLEスタックイベントに関連するすべてのModule群にBLEスタックイベントを送出するための関数.
 *
 * @details BLEスタックイベントを受信したあと、メインループの中のスケジューラーから呼び出される.
 *          
 * @param[in]   p_ble_evt   Bluetoothスタックイベント.
 */
static void ble_evt_dispatch(ble_evt_t * p_ble_evt)
{
  
}

/**
 * @brief PStorage関連のハンドラ.各処理の成功失敗の結果が取れる.
 */
static void example_cb_handler(pstorage_handle_t  * handle,
								uint8_t              op_code,
                               uint32_t             result,
                               uint8_t            * p_data,
                               uint32_t             data_len)
{
		if(handle->block_id == pstorage_wait_handle) { pstorage_wait_flag = 0; }  //If we are waiting for this callback, clear the wait flag.
	
		switch(op_code)
		{
			case PSTORAGE_LOAD_OP_CODE:
				 if (result == NRF_SUCCESS)
				 {
					 app_trace_log("PSTORAGE_LOAD_OP_CODE: SUCCESS\r\n");				 
				 }
				 else
				 {
						app_trace_log("PSTORAGE_LOAD_OP_CODE: FAULT\r\n");				 
				 }
				 break;
			case PSTORAGE_STORE_OP_CODE:
				 if (result == NRF_SUCCESS)
				 {
						app_trace_log("PSTORAGE_STORE_OP_CODE: SUCCESS\r\n");				 
				 }
				 else
				 {
						app_trace_log("PSTORAGE_STORE_OP_CODE: FAULT\r\n");				 
				 }
				 break;				 
			case PSTORAGE_UPDATE_OP_CODE:
				 if (result == NRF_SUCCESS)
				 {
					app_trace_log("PSTORAGE_UPDATE_OP_CODE: SUCCESS\r\n");				 
				 }
				 else
				 {
					 	app_trace_log("PSTORAGE_ERROR_LED_PIN_NO: FAULT\r\n");				 
				 }
				 break;
			case PSTORAGE_CLEAR_OP_CODE:
				 if (result == NRF_SUCCESS)
				 {
					 app_trace_log("PSTORAGE_ERROR_LED_PIN_NO: SUCCESS\r\n");				 
				 }
				 else
				 {
					 app_trace_log("PSTORAGE_ERROR_LED_PIN_NO: FAULT\r\n");				 
				 }
				 break;			
		}			
}

/**
 * @brief パワーマネージャーの関数.
 */
static void power_manage(void)
{
    uint32_t err_code = sd_app_evt_wait();
    APP_ERROR_CHECK(err_code);
}

/**
 * @brief Main処理.
 */
int main(void)
{
	// Debug Loggerの初期化.
	app_trace_init();
	
	// SoftDeviceの初期化.
	uint32_t err_code;	
	SOFTDEVICE_HANDLER_INIT(NRF_CLOCK_LFCLKSRC_RC_250_PPM_4000MS_CALIBRATION, false);

	// BLEスタックを有効にする. 
    ble_enable_params_t ble_enable_params;
    memset(&ble_enable_params, 0, sizeof(ble_enable_params));
    //ble_enable_params.gatts_enable_params.service_changed = IS_SRVC_CHANGED_CHARACT_PRESENT;
    err_code = sd_ble_enable(&ble_enable_params);
    APP_ERROR_CHECK(err_code);
	
    // BLEイベントを登録する.
    err_code = softdevice_ble_evt_handler_set(ble_evt_dispatch);
    APP_ERROR_CHECK(err_code);

    // BLEイベント群のためのSoftDeviceハンドラモジュールを登録.
    err_code = softdevice_sys_evt_handler_set(sys_evt_dispatch);
    APP_ERROR_CHECK(err_code);
	
	pstorage_handle_t       			handle;
	pstorage_handle_t				block_0_handle;
	pstorage_handle_t				block_1_handle;
	
	pstorage_module_param_t param;
	
	// Param of write
	uint8_t                 write_data_0[16] = {0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50};
	uint8_t                 write_data_1[16] = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x4d, 0x3e, 0x3f, 0x40};
	
	// Param of read
	uint8_t                 read_data_0[16];
	uint8_t                 read_data_1[16];
	
	// Persistent Storageの初期化.
	err_code = pstorage_init();
	if(err_code != NRF_SUCCESS)
	{
		app_trace_log("fail of intialize pstorage.");
	}
	     
	param.block_size  = 16;                   //Select block size of 16 bytes
	param.block_count = 10;                   //Select 10 blocks, total of 160 bytes
	param.cb          = example_cb_handler;   //Set the pstorage callback handler
			
	// Persistent Storageの登録.
	err_code = pstorage_register(&param, &handle);
	if (err_code  != NRF_SUCCESS)
	{
		app_trace_log(" fail of register pstorage.");
	}
		
	// ブロック識別しを取得.
	pstorage_block_identifier_get(&handle, 0, &block_0_handle);
	pstorage_block_identifier_get(&handle, 1, &block_1_handle);
		
	// 32 bytesのデータクリア( 16 bytes x 2 block )
	pstorage_clear(&block_0_handle, 32);                     
		
	// データをストア
	pstorage_wait_handle = block_1_handle.block_id;            //Specify which pstorage handle to wait for
	pstorage_wait_flag = 1;                                    //Set the wait flag. Cleared in the example_cb_handler
	pstorage_store(&block_0_handle, write_data_0, 16, 0);     //Write to flash, only one block is allowed for each pstorage_store command
	pstorage_store(&block_1_handle, write_data_1, 16, 0);     //Write to flash, only one block is allowed for each pstorage_store command		
	while(pstorage_wait_flag) { power_manage(); }              //Sleep until store operation is finished.
		
	// エータをロード
	pstorage_wait_handle = block_0_handle.block_id;            //Specify which pstorage handle to wait for
	pstorage_wait_flag = 1;                                    //Set the wait flag. Cleared in the example_cb_handler
	pstorage_load(read_data_0, &block_0_handle, 16, 0);				 //Read from flash, only one block is allowed for each pstorage_load command
	pstorage_load(read_data_1, &block_1_handle, 16, 0);				 //Read from flash
	
	// 結果を表示	
	app_trace_log("First value of read_data_0: %c\r\n", read_data_0[0]);
	app_trace_log("First value of read_data_1: %c\r\n", read_data_1[0]);

   while (true)
    {
        power_manage();
    }
}
```