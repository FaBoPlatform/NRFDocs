#include <string.h>

#include "gaputil.h"
#include "app_util.h"
#include "ble_gap.h"
#include "app_error.h"

#define MIN_CONN_INTERVAL               MSEC_TO_UNITS(500, UNIT_1_25_MS)            /**< Minimum acceptable connection interval (0.1 seconds). */
#define MAX_CONN_INTERVAL               MSEC_TO_UNITS(1000, UNIT_1_25_MS)            /**< Maximum acceptable connection interval (0.2 second). */
#define SLAVE_LATENCY                   0                                           /**< Slave latency. */
#define CONN_SUP_TIMEOUT                MSEC_TO_UNITS(5000, UNIT_10_MS)             /**< Connection supervisory timeout (4 seconds). */

void gap_name_set(const char *name)
{
    uint32_t                err_code;
    ble_gap_conn_sec_mode_t sec_mode;
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&sec_mode);

    err_code = sd_ble_gap_device_name_set(&sec_mode,
                                          (const uint8_t *)name,
                                          strlen(name));
    APP_ERROR_CHECK(err_code);
}

void gap_params_init(void)
{
    uint32_t                err_code;
    ble_gap_conn_params_t   gap_conn_params;
    memset(&gap_conn_params, 0, sizeof(gap_conn_params));

    gap_conn_params.min_conn_interval = MIN_CONN_INTERVAL;
    gap_conn_params.max_conn_interval = MAX_CONN_INTERVAL;
    gap_conn_params.slave_latency     = SLAVE_LATENCY;
    gap_conn_params.conn_sup_timeout  = CONN_SUP_TIMEOUT;

    err_code = sd_ble_gap_ppcp_set(&gap_conn_params);
    APP_ERROR_CHECK(err_code);

#if (NRF_SD_BLE_API_VERSION == 3)
    //ble_gap_privacy_params_t privacy_params = {0};
    //privacy_params.privacy_mode = BLE_GAP_PRIVACY_MODE_DEVICE_PRIVACY;
    //privacy_params.private_addr_type = BLE_GAP_ADDR_TYPE_RANDOM_PRIVATE_RESOLVABLE;
    //sd_ble_gap_privacy_set(&privacy_params);
#else
    //ble_gap_addr_t gap_address;
    //gap_address.addr_type = BLE_GAP_ADDR_TYPE_RANDOM_PRIVATE_RESOLVABLE;
    //err_code = sd_ble_gap_address_set(BLE_GAP_ADDR_CYCLE_MODE_AUTO, &gap_address);
#endif

    //APP_ERROR_CHECK(err_code);

    // ble_opt_t opt = {0};
    // opt.gap_opt.privacy.interval_s = 10;
    // err_code = sd_ble_opt_set(BLE_GAP_OPT_PRIVACY, &opt);
    // APP_ERROR_CHECK(err_code);

}
