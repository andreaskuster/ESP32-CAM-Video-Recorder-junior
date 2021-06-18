/*
 * Device Initialization and Reporting
 */

#include <Esp.h>
#include <esp_system.h>
#include <nvs_flash.h>
#include <esp32-hal-cpu.h>
#include <esp32-hal-psram.h>

#include "device.h"

/**
 * Description: Initialize hardware components
 *
 * @param
 * @return
 */
void init_device(void) {
#ifdef BOARD_HAS_PSRAM
    // initialize PSRAM
    psramInit();
#endif
    // init non-volatile storage (used for WiFi storage)
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
}

/**
 * Description: Print detailed chip hardware information
 *
 * @param
 * @return
 */
void report_device_info(void) {

    // fetch general chip info
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);

    // report info
    printf("ESP32 Chip Info\n");
    printf("Target: %s\n", CONFIG_IDF_TARGET);
    printf("Model: %s, Revision: %d\n",
           ESP.getChipModel(),
           ESP.getChipRevision());
    printf("Core Count: %d\n",
           ESP.getChipCores());
    printf("Frequencies: CPU: %d MHz, XTAL: %d MHz, APB: %d MHz %s\n",
           getCpuFrequencyMhz(),
           getXtalFrequencyMhz(),
           getApbFrequency() / (1000 * 1000),
           (getCpuFrequencyMhz() < 240) ? "Warning: Not running at maximum frequency!" : "");
    printf("Features: WiFi%s%s\n",
           (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
           (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");
    printf("Minimum Free Heap Size: %dKB\n", ESP.getMinFreeHeap() / 1024);
    const char *mode;
    switch (ESP.getFlashChipMode()) {
        case FM_QIO:
            mode = "FM_QIO";
            break;
        case FM_QOUT:
            mode = "FM_QOUT";
            break;
        case FM_DIO:
            mode = "FM_DIO";
            break;
        case FM_DOUT:
            mode = "FM_DOUT";
            break;
        case FM_FAST_READ:
            mode = "FM_FAST_READ";
            break;
        case FM_SLOW_READ:
            mode = "FM_SLOW_READ";
            break;
        case FM_UNKNOWN:
        default:
            mode = "FM_UNKNOWN";
            break;
    }
    printf("Flash: Size: %dMB, Speed: %dMHz,  Mode: %s\n",
           ESP.getFlashChipSize() / (1024 * 1024),
           ESP.getFlashChipSpeed() / (1000 * 1000),
           mode);
    if (psramFound()) {
        printf("PSRAM: Size: %dMB, Minimum Free: %dMB",
               (ESP.getPsramSize() / (1024 * 1024)),
               (ESP.getMinFreePsram() / (1024 * 1024)));
    }
}
