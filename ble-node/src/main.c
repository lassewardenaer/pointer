#include <stdint.h>
#include <stddef.h>

#include "nrf_sdh.h"
#include "nrf_sdh_ble.h"
#include "nrf_ble_gatt.h"
#include "app_error.h"

#define APP_BLE_CONN_CFG_TAG 1

NRF_BLE_GATT_DEF(m_gatt);

void assert_nrf_callback(uint16_t line_num, const uint8_t *p_file_name)
{
    app_error_handler(0xDEADBEEF, line_num, p_file_name);
}

void ble_evt_handler(ble_evt_t const *p_ble_evt, void *p_context)
{
    // Handle BLE events here
}

int main(void)
{
    ret_code_t err_code;

    err_code = nrf_sdh_enable_request();
    APP_ERROR_CHECK(err_code);

    // Configure the BLE stack using the default settings
    nrf_sdh_ble_default_cfg_set(APP_BLE_CONN_CFG_TAG, &ble_cfg);

    // Enable BLE stack
    err_code = nrf_sdh_ble_enable(&ble_cfg);
    APP_ERROR_CHECK(err_code);

    // Register a handler for BLE events
    NRF_SDH_BLE_OBSERVER(m_ble_observer, APP_BLE_OBSERVER_PRIO, ble_evt_handler, NULL);

    // Initialize the GATT module
    err_code = nrf_ble_gatt_init(&m_gatt, NULL);
    APP_ERROR_CHECK(err_code);

    // Enter the main loop
    while (true)
    {
        // Do nothing, the event handlers will handle everything
    }
}
