#include <string.h>

#include "fstorage.h"
#include "app_error.h"

// const uint32_t * stored_data;
static void fs_evt_handler(fs_evt_t const * const evt, fs_ret_t result)
{
}

FS_REGISTER_CFG(fs_config_t fs_config) =
{
    .callback  = fs_evt_handler,    // Function for event callbacks.
    .num_pages = 1,                 // Number of physical flash pages required.
    .priority  = 0xFE               // Priority for flash usage.
};

// init
void storage_init()
{	
    fs_ret_t ret = fs_init();
    APP_ERROR_CHECK(ret);
}

// clear
void storage_clear()
{
    fs_ret_t ret = fs_erase(&fs_config, fs_config.p_start_addr, 1, NULL);
    APP_ERROR_CHECK(ret);
}

// save
void storage_save(void *value, int size)
{
    storage_clear();
    fs_ret_t ret = fs_store(&fs_config, fs_config.p_start_addr, value, size/4, NULL);
    APP_ERROR_CHECK(ret);
}

// load
void storage_load(void *value, int size)
{
    memcpy(value, fs_config.p_start_addr, size);
}
