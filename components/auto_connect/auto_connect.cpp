/*
 * Auto Connect - Simplified and non-static wifi client setup (if the device cannot connect to a known WiFi, it spawns
 * a hotspot with Captive Portal that allows to scan and setup the network)
 */

#include <WiFiManager.h>

#include "auto_connect.h"

void init_connect_wifi(void) {

    // local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wifiManager;

    // tries to connect to last known settings and goes into a blocking loop awaiting configuration
    WiFi.enableAP(true);
    if (!wifiManager.autoConnect("AutoConnectAP", "password")) {
        printf("WifiManager: Failed to connect. Restart device.\n");
        ESP.restart();
    }

    // Report information about the Connection
    printf("Connected to %s, IP: %s, MAC: %s, channel: %d, RSSI: %d\n",
           WiFi.SSID().c_str(),
           WiFi.localIP().toString().c_str(),
           WiFi.macAddress().c_str(),
           WiFi.channel(),
           WiFi.RSSI());

}

