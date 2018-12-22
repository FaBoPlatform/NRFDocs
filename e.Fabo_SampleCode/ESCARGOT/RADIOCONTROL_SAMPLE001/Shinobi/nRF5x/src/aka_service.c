#include <string.h>

#include "aka_service.h"
#include "app_error.h"
#include "nrf_log.h"

#define FW_NAME "GRIDEYE_Sensing"
#define FW_VER 1

// Base UUID
// 28B1AC44-0CD3-40BC-B3F3-C92E2752117E
static const ble_uuid128_t service_uuid128 = 
    {{0x7e,0x11,0x52,0x27,0x2e,0xc9,0xf3,0xb3,0xbc,0x40,0xd3,0x0c,0x44,0xac,0xb1,0x28}};
// Service UUID
#define UUID_AKA_SERVICE 0xac44
// Charactaristic UUID
#define UUID_AKA_CHR_CTR 0xb579
#define UUID_AKA_CHR_DAT 0xb708


// Service Handle
static uint16_t service_handle;
// Charastaristic Handle
static ble_gatts_char_handles_t char_ctr_handles;
static ble_gatts_char_handles_t char_dat_handles;

// Data
static aka_data *m_aka_data;
// 認証フラグ
static bool authorized = false;
// 書き込みバッファ
static uint8_t writte_buff[20] = {0};

typedef struct {
    char name[12];
    uint8_t reserved[5];
    uint8_t ver;
    uint8_t max_params;
    uint8_t auth_r    :1;
    uint8_t auth_w    :1;
} aka_info;

// 初期データ設定
void akadata_init(aka_data *data)
{
    memset(data, 0, sizeof(aka_data));
    data->ver = AKA_DATA_VER;
    data->enabled = 1;
    strcpy(data->name, "RADIOCAR_CONTOL");
    strcpy(data->password, "");
    data->auth.read = false;
    data->auth.write = true;
    data->tx_power = 7;
    // 
    data->beacon_info.major = 0;
    data->beacon_info.minor = 0;
    data->beacon_info.interval = 100;
    data->beacon_info.measured_pow = 0x00;
    data->beacon_info.channel_mask.ch_37_off = false;
    data->beacon_info.channel_mask.ch_38_off = false;
    data->beacon_info.channel_mask.ch_39_off = false;
    uint8_t uuid[16] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};	
    memcpy(data->beacon_info.uuid, uuid, 16);
}

// Charactaristic追加
static void add_char(uint16_t uuid, uint16_t len, ble_gatts_char_handles_t *handles, bool isReadable, bool isWriteable)
{
    uint32_t err_code;
    ble_gatts_char_md_t char_md;
    ble_gatts_attr_t attr_char_value;
    ble_uuid_t char_uuid;
    ble_gatts_attr_md_t attr_md;

    memset(handles, 0, sizeof(ble_gatts_char_handles_t));
    memset(&char_md, 0, sizeof(char_md));

    char_md.char_props.read = isReadable;
    char_md.char_props.write = isWriteable;
    char_md.p_char_user_desc = NULL;
    char_md.p_char_pf = NULL;
    char_md.p_user_desc_md = NULL;
    char_md.p_cccd_md = NULL;
    char_md.p_sccd_md = NULL;

    char_uuid.type = BLE_UUID_TYPE_VENDOR_BEGIN;
    char_uuid.uuid = uuid;

    memset(&attr_md, 0, sizeof(attr_md));

    if(isReadable){
        BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&attr_md.read_perm);
    } else {
        BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&attr_md.read_perm);
    }
    if(isWriteable){
        BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&attr_md.write_perm);
    } else {
        BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&attr_md.write_perm);
    }

    attr_md.vloc = BLE_GATTS_VLOC_STACK;
    attr_md.rd_auth = 0;
    attr_md.wr_auth = 1;
    attr_md.vlen = 0;

    memset(&attr_char_value, 0, sizeof(attr_char_value));

    attr_char_value.p_uuid = &char_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len = len;
    attr_char_value.init_offs = 0;
    attr_char_value.max_len = len;

    err_code = sd_ble_gatts_characteristic_add(service_handle,
                                &char_md,
                                &attr_char_value,
                                handles);
    APP_ERROR_CHECK(err_code);
}

// サービス初期化
void aka_service_init(aka_data *data)
{
    uint32_t err_code;
    ble_uuid_t ble_uuid;

    m_aka_data = data;

    // UUID設定
    err_code = sd_ble_uuid_vs_add(&service_uuid128, &ble_uuid.type);
    APP_ERROR_CHECK(err_code);

    // Service追加
    ble_uuid.type = BLE_UUID_TYPE_VENDOR_BEGIN;
    ble_uuid.uuid = UUID_AKA_SERVICE;
    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &ble_uuid, &service_handle);
    APP_ERROR_CHECK(err_code);

    // Charactaristic追加
    add_char(UUID_AKA_CHR_CTR, 20, &char_ctr_handles, false, true);
    add_char(UUID_AKA_CHR_DAT, 20, &char_dat_handles, true, true);
}

// GATTS設定
static void set_gatts_data(uint8_t* buff, uint16_t len, uint16_t conn_handle)
{
    uint8_t tmp[20] = {0};
    memcpy(tmp, buff, len);

    ble_gatts_value_t value;
    value.len = 20;
    value.offset = 0;
    value.p_value = tmp;

    uint32_t err_code;
    err_code = sd_ble_gatts_value_set(conn_handle, char_dat_handles.value_handle, &value);
    APP_ERROR_CHECK(err_code);
}

// 書き込みコマンド
static void on_write_command(uint8_t write_index) {
    NRF_LOG_DEBUG("on_write_command:%d\r\n", write_index);

    switch(write_index) {
        case 1: // Name
            memcpy(&m_aka_data->name, writte_buff, 20);
            break;
        case 2: // UUID
            memcpy(&m_aka_data->beacon_info.uuid, writte_buff, 16);
            break;
        case 3: // Major
            memcpy(&m_aka_data->beacon_info.major, writte_buff, 2);
            break;
        case 4: // Minor
            memcpy(&m_aka_data->beacon_info.minor, writte_buff, 2);
            break;
        case 5: // TxPower
            memcpy(&m_aka_data->tx_power, writte_buff, 1);
            break;
        case 6: // Span
            memcpy(&m_aka_data->beacon_info.interval, writte_buff, 2);
            break;
        case 7: // Measured TX power
            memcpy(&m_aka_data->beacon_info.measured_pow, writte_buff, 1);
            break;
        case 8: // Channels
            memcpy(&m_aka_data->beacon_info.channel_mask, writte_buff, 1);
            break;
        case 9: // Enabled
            memcpy(&m_aka_data->enabled, writte_buff, 1);
            break;
        default:
            authorized = false;
            break;
    }
    memcpy(writte_buff, 0, 20);
}

// 読み込みコマンド
static void on_read_command(uint8_t read_index, uint16_t conn_handle) {
    NRF_LOG_DEBUG("on_read_command:%d\r\n", read_index);

    switch(read_index) {
        case 1: // Name
            set_gatts_data((uint8_t*)m_aka_data->name, 20, conn_handle);
            break;
        case 2: // UUID
            set_gatts_data(m_aka_data->beacon_info.uuid, 16, conn_handle);
            break;
        case 3: // Major
            set_gatts_data((uint8_t*)&m_aka_data->beacon_info.major, 2, conn_handle);
            break;
        case 4: // Minor
            set_gatts_data((uint8_t*)&m_aka_data->beacon_info.minor, 2, conn_handle);
            break;
        case 5: // TxPower
            set_gatts_data((uint8_t*)&m_aka_data->tx_power, 1, conn_handle);
            break;
        case 6: // Span
            set_gatts_data((uint8_t*)&m_aka_data->beacon_info.interval, 2, conn_handle);
            break;
        case 7: // Measured TX power
            set_gatts_data((uint8_t*)&m_aka_data->beacon_info.measured_pow, 1, conn_handle);
            break;
        case 8: // Channels
            set_gatts_data((uint8_t*)&m_aka_data->beacon_info.channel_mask, 1, conn_handle);
            break;
        case 9: // Enabled
            set_gatts_data((uint8_t*)&m_aka_data->enabled, 1, conn_handle);
            break;
        default:
            authorized = false;
            break;
    }
}

// 書き込み時
static void on_write(ble_gatts_evt_write_t *p_evt_write, uint16_t conn_handle)
{
    uint32_t err_code;
    ble_gatts_rw_authorize_reply_params_t auth_reply;
    memset(&auth_reply, 0, sizeof(ble_gatts_rw_authorize_reply_params_t));

    NRF_LOG_DEBUG("*on_write*\r\n");
    NRF_LOG_DEBUG("handle:%d\r\n", p_evt_write->handle);
    NRF_LOG_DEBUG("auth:%d\r\n", p_evt_write->uuid.uuid);
    NRF_LOG_DEBUG("op:%d\r\n", p_evt_write->op);
    NRF_LOG_DEBUG("auth:%d\r\n", p_evt_write->auth_required);
    NRF_LOG_DEBUG("len:%d\r\n", p_evt_write->len);
    NRF_LOG_DEBUG("offs:%d\r\n", p_evt_write->offset);
    NRF_LOG_HEXDUMP_DEBUG(p_evt_write->data, p_evt_write->len);

    // コントロール
    if(p_evt_write->handle == char_ctr_handles.value_handle) {
        uint8_t command = p_evt_write->data[0];

        switch(command) {
            case 1: { // 情報取得コマンド
                NRF_LOG_DEBUG("1:Info\r\n");
                aka_info info;
                strcpy(info.name, FW_NAME);
                info.ver = FW_VER;
                info.max_params = 9;
                info.auth_r = m_aka_data->auth.read;
                info.auth_w = m_aka_data->auth.write;
                set_gatts_data((uint8_t*)&info, 20, conn_handle);
                authorized = false;
            } break;
            case 2: { // 認証コマンド
                NRF_LOG_DEBUG("2:Auth\r\n");
                char buff[19] = {0};
                memcpy(buff, &p_evt_write->data[1], p_evt_write->len -1);
                NRF_LOG_HEXDUMP_DEBUG(m_aka_data->password, 18);
                NRF_LOG_HEXDUMP_DEBUG(buff, 18);
                if(memcmp(buff, m_aka_data->password, sizeof(char)*18) == 0){
                    NRF_LOG_DEBUG("Auth OK!\r\n");
                    authorized = true;
                } else {
                    NRF_LOG_DEBUG("Auth NG!\r\n");
                    authorized = false;
                    auth_reply.params.write.gatt_status = BLE_GATT_STATUS_ATTERR_WRITE_NOT_PERMITTED;
                }
            } break;
            case 3: { // 読み込みコマンド
                NRF_LOG_DEBUG("3:Read\r\n");
                if (m_aka_data->auth.read && !authorized) {
                    auth_reply.params.write.gatt_status = BLE_GATT_STATUS_ATTERR_WRITE_NOT_PERMITTED;
                } else {
                    on_read_command(p_evt_write->data[1], conn_handle);
                }
            } break;
            case 4: { // 書き込みコマンド
                NRF_LOG_DEBUG("4:Write\r\n");
                if (m_aka_data->auth.write && !authorized) {
                    auth_reply.params.write.gatt_status = BLE_GATT_STATUS_ATTERR_WRITE_NOT_PERMITTED;
                } else {
                    on_write_command(p_evt_write->data[1]);
                }
            } break;
            case 5: { // パスワード変更コマンド
                NRF_LOG_DEBUG("5:PassChange\r\n");
                if (authorized) {
                    // mode
                    memcpy(&m_aka_data->auth, &p_evt_write->data[1], 1);
                    // pass
                    memset(m_aka_data->password, 0, 18);
                    memcpy(m_aka_data->password, &p_evt_write->data[2], p_evt_write->len -2);
                    authorized = false;
                } else {
                    auth_reply.params.write.gatt_status = BLE_GATT_STATUS_ATTERR_WRITE_NOT_PERMITTED;
                }
            } break;
            default: // エラー
                NRF_LOG_DEBUG("%d:Invalid command!\r\n", command);
                char buff[20] = {0};
                set_gatts_data((uint8_t*)buff, 20, conn_handle);
                auth_reply.params.write.gatt_status = BLE_GATT_STATUS_ATTERR_INVALID;
                break;
        }
    }

    // データ
	if (p_evt_write->handle == char_dat_handles.value_handle) {
        memcpy(writte_buff, &p_evt_write->data, p_evt_write->len);
    }

    // reply
    if (p_evt_write->auth_required) {
        auth_reply.type = BLE_GATTS_AUTHORIZE_TYPE_WRITE;
        auth_reply.params.write.update = 1;
        err_code = sd_ble_gatts_rw_authorize_reply(conn_handle, &auth_reply);
        APP_ERROR_CHECK(err_code);
    }
}

// イベントハンドラ
void aka_service_ble_evt(ble_evt_t *p_ble_evt)
{
    switch(p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            NRF_LOG_DEBUG("*BLE_GAP_EVT_CONNECTED.\r\n");
            authorized = false;
            break; // BLE_GAP_EVT_DISCONNECTED
        case BLE_GATTS_EVT_WRITE: {
            NRF_LOG_DEBUG("*BLE_GATTS_EVT_WRITE.\r\n");
            uint16_t conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
            on_write(&p_ble_evt->evt.gatts_evt.params.write, conn_handle);
        } break;
        case BLE_GATTS_EVT_RW_AUTHORIZE_REQUEST:
        {
            NRF_LOG_DEBUG("*BLE_GATTS_EVT_RW_AUTHORIZE_REQUEST.\r\n");
            ble_gatts_evt_rw_authorize_request_t  *req;
            req = &p_ble_evt->evt.gatts_evt.params.authorize_request;
            if (req->type != BLE_GATTS_AUTHORIZE_TYPE_INVALID)
            {
                if (req->request.write.op == BLE_GATTS_OP_WRITE_REQ)
                {
                    uint16_t conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
                    on_write(&req->request.write, conn_handle);
                }
            }
        } break;
    }
}
