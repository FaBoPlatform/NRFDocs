#ifndef AKA_SERVICE_H___
#define AKA_SERVICE_H___

#include "ble.h"
#include "ble_srv_common.h"
#include "beacon.h"

// data version
#define AKA_DATA_VER 3

typedef struct {
    uint8_t read    :1;
    uint8_t write    :1;
} auth_info;

typedef struct {
    char name[20];
    char password[18];
    uint8_t ver;
    uint8_t enabled;
    uint8_t tx_power;
    auth_info auth;
    beacon_info_t beacon_info;
} aka_data;

void akadata_init(aka_data *data);
void aka_service_init(aka_data *data);
void aka_service_ble_evt(ble_evt_t *p_ble_evt);

#endif // AKA_SERVICE_H___
