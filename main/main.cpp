/*
 *
 */
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#include "device_info.h"
#include "auto_connect.h"

// catch compile time variables
#define BLINK_GPIO ((gpio_num_t)CONFIG_BLINK_GPIO)

void blink_task(void *pvParameter);


// add C linkage definition
extern "C" {
    void app_main(void);
}

//#include <WiFi.h>
//#include <nvs_flash.h>
//
//const char* ssid = "ESP32-Access-Point";
//const char* password = "123456789";

void app_main(void) {
    printf("Hello world!\n");

//    Serial.begin(115200);
//    nvs_flash_init();

//    WiFi.softAP(ssid, password);
//
//    Serial.println();
//    Serial.print("IP address: ");
//    Serial.println(WiFi.softAPIP());


    report_device_info();

    init_connect_wifi();

    printf("Starting blink task\n");
    xTaskCreate(&blink_task, "blink_task", CONFIG_ESP32_PTHREAD_TASK_STACK_SIZE_DEFAULT, NULL, 5, NULL);

    for (int i = 100; i >= 0; i--) {
        printf("Restarting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    printf("Restarting now.\n");
    fflush(stdout);
    esp_restart();
}

void blink_task(void *pvParameter) {
    /* Configure the IOMUX register for pad BLINK_GPIO (some pads are
     * muxed to GPIO on reset already, but some default to other
     * functions and need to be switched to GPIO. Consult the
     * Technical Reference for a list of pads and their default
     * functions.)
     */
    gpio_pad_select_gpio(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
    while (1) {
        /* Blink off (output low) */
        printf("Turning off the LED\n");
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        /* Blink on (output high) */
        printf("Turning on the LED\n");
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}