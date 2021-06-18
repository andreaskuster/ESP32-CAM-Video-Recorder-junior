# idf component registration
idf_component_register(SRCS "main.cpp"
                       INCLUDE_DIRS ".")

# add debug option
option(DEBUG "Enable debug output" OFF)
if (DEBUG)
    message(STATUS "Debug output activated")
    add_compile_definitions(DEBUG)
endif()

# add spi ram option
option(BOARD_HAS_PSRAM "Activate SPI RAM" ON)
if (BOARD_HAS_PSRAM)
    message(STATUS "SPI RAM activated")
    target_compile_definitions(${COMPONENT_TARGET} PUBLIC "-DBOARD_HAS_PSRAM")
endif()

# add custom port assignments
set(CONFIG_BLINK_GPIO 33 CACHE STRING "Blink led pin number.") # default: 22
if(DEBUG)
    message(STATUS "CONFIG_BLINK_GPIO value: ${CONFIG_BLINK_GPIO}")
endif()
add_compile_definitions(CONFIG_BLINK_GPIO=${CONFIG_BLINK_GPIO})
