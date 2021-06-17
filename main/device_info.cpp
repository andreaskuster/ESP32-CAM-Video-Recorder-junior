/*
 *
 */


#include <stdio.h>
#include <esp32-hal-cpu.h>
#include <esp32-hal-psram.h>

#include "esp_system.h"
#include "esp_spi_flash.h"

#include "device_info.h"

/**
 * Description
 *
 * @param
 * @return
 */
void report_device_info(void){
    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    psramInit();
    printf("This is %s chip with %d CPU core(s), WiFi%s%s, PSRAM: %s, ",
           CONFIG_IDF_TARGET,
           chip_info.cores,
           (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
           (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "",
           psramFound() ? "yes" : "no"
           );

    printf("silicon revision %d, ", chip_info.revision);

    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
           (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");


    printf("Minimum free heap size: %d bytes\n", esp_get_minimum_free_heap_size());

    printf("Frequency\nCPU: %d MHz, XTAL: %d MHz, APB: %d MHz\n", getCpuFrequencyMhz(), getXtalFrequencyMhz(), getApbFrequency());
    // TODO: set if < 240MHz? bool setCpuFrequencyMhz(uint32_t cpu_freq_mhz);
}
