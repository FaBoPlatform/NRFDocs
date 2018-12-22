#ifndef BLESTACK_H___
#define BLESTACK_H___

#include "softdevice_handler.h"

typedef void (*ble_event_handler_t)(ble_evt_t *p_ble_evt);

void ble_stack_init(ble_event_handler_t handler);

#endif // BLESTACK_H___
