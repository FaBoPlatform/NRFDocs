#ifndef ADVERTISING_H___
#define ADVERTISING_H___

#include "ble_advdata.h"

void advertising_init(ble_uuid_t *adv_uuids);
void advertising_start(int interval, int timeout);
void advertising_stop();
void advertising_ble_evt(ble_evt_t *p_ble_evt);

#endif // ADVERTISING_H___
