#ifndef BEACON_H__
#define BEACON_H__

#include "ble_advdata.h"

typedef struct
{
    uint8_t ch_37_off : 1;
    uint8_t ch_38_off : 1;
    uint8_t ch_39_off : 1;
} beacon_channel_mask_t;

typedef struct
{
    uint16_t major;
    uint16_t minor;
    uint16_t interval;
    uint8_t measured_pow;
    beacon_channel_mask_t channel_mask;
    uint8_t uuid[23];
    uint16_t dummy;
} beacon_info_t;

//void beacon_init(beacon_info_t info);
//GridEye Functions
void beacon_init(beacon_info_t info,uint16_t company);
void beacon_start(void);
void beacon_stop(void);

#endif // BEACON_H__
