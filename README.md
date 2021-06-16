##


## Troubleshooting

Problem:
```
[   192][E][WiFiGeneric.cpp:555] wifiLowLevelInit(): esp_wifi_init 4353
[   199][E][WiFiAP.cpp:125] softAP(): enable AP first!
```

Solution:
```
#include <nvs_flash.h>

nvs_flash_init();
```

Reference: 
- https://github.com/loboris/MicroPython_ESP32_psRAM_LoBo/issues/230
- https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/error-codes.html
