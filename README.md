##

![master idf build pipeline status](https://github.com/andreaskuster/ESP32-WebCam/actions/workflows/idf_build.yml/badge.svg?branch=master)

## Troubleshooting

Problem: 
Cyclic dependency problem, ending up in linker error:
```
/home/andreas/.espressif/tools/xtensa-esp32-elf/esp-2020r3-8.4.0/xtensa-esp32-elf/bin/../lib/gcc/xtensa-esp32-elf/8.4.0/../../../../xtensa-esp32-elf/bin/ld: /home/andreas/CLionProjects/ESP32-WebCam/components/wifimanager-esp32/WiFiManager.cpp:735: undefined reference to `WebServer::sendHeader(String const&, String const&, bool)'
/home/andreas/.espressif/tools/xtensa-esp32-elf/esp-2020r3-8.4.0/xtensa-esp32-elf/bin/../lib/gcc/xtensa-esp32-elf/8.4.0/../../../../xtensa-esp32-elf/bin/ld: /home/andreas/CLionProjects/ESP32-WebCam/components/wifimanager-esp32/WiFiManager.cpp:736: undefined reference to `WebServer::sendHeader(String const&, String const&, bool)'
/home/andreas/.espressif/tools/xtensa-esp32-elf/esp-2020r3-8.4.0/xtensa-esp32-elf/bin/../lib/gcc/xtensa-esp32-elf/8.4.0/../../../../xtensa-esp32-elf/bin/ld: /home/andreas/CLionProjects/ESP32-WebCam/components/wifimanager-esp32/WiFiManager.cpp:737: undefined reference to `WebServer::sendHeader(String const&, String const&, bool)'
/home/andreas/.espressif/tools/xtensa-esp32-elf/esp-2020r3-8.4.0/xtensa-esp32-elf/bin/../lib/gcc/xtensa-esp32-elf/8.4.0/../../../../xtensa-esp32-elf/bin/ld: /home/andreas/CLionProjects/ESP32-WebCam/components/wifimanager-esp32/WiFiManager.cpp:738: undefined reference to `WebServer::send(int, char const*, String const&)'
collect2: error: ld returned 1 exit status
make[3]: *** [CMakeFiles/esp32-webcam.elf.dir/build.make:520: esp32-webcam.elf] Error 1
make[2]: *** [CMakeFiles/Makefile2:2500: CMakeFiles/esp32-webcam.elf.dir/all] Error 2
make[1]: *** [CMakeFiles/Makefile2:2507: CMakeFiles/esp32-webcam.elf.dir/rule] Error 2
make: *** [Makefile:365: esp32-webcam.elf] Error 2
```

Solution: 
Add the following snippet to the `CMakeLists.txt` of a component in the cyclic dependency (increase 3 if it still does not work)
```
set_property(TARGET ${COMPONENT_LIB} APPEND PROPERTY LINK_INTERFACE_MULTIPLICITY 3)
```

Reference:
- https://www.esp32.com/viewtopic.php?t=21378


Problem WiFi Error 4353 (0x1101)
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
