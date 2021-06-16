/*
 *
 */

#include <stdio.h>

#include <nvs_flash.h>

#include "auto_connect.h"

#include <WiFiManager.h>


void init_connect_wifi(void) {

    nvs_flash_init();

    //WiFiManager
    //Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wifiManager;

    //reset settings - for testing
    //wifiManager.resetSettings();



    //start
    IPAddress _ip = IPAddress(10, 0, 1, 78);
    IPAddress _gw = IPAddress(10, 0, 1, 1);
    IPAddress _sn = IPAddress(255, 255, 255, 0);
    //end

    wifiManager.setSTAStaticIPConfig(_ip, _gw, _sn);


    //tries to connect to last known settings
    //if it does not connect it starts an access point with the specified name
    //here  "AutoConnectAP" with password "password"
    //and goes into a blocking loop awaiting configuration
    if (!wifiManager.autoConnect("AutoConnectAP", "password")) {
        Serial.println("failed to connect, we should reset as see if it connects");
        delay(3000);
        ESP.restart();
        delay(5000);
    }

    //if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");


    Serial.println("local ip");
    Serial.println(WiFi.localIP());

}


