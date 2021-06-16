#idf_component_register(SRCS "main.cpp" "device_info.cpp" "auto_connect.cpp" INCLUDE_DIRS "")

set(COMPONENT_REQUIRES )
set(COMPONENT_PRIV_REQUIRES )

set(COMPONENT_SRCS "main.cpp" "device_info.cpp" "auto_connect.cpp")
set(COMPONENT_ADD_INCLUDEDIRS "")

register_component()


# add debug option
option(DEBUG "Enable debug output" OFF)
if (DEBUG)
    message(STATUS "Debug output activated")
    add_compile_definitions(DEBUG)
endif()

# add custom port assignments
set(CONFIG_BLINK_GPIO 33 CACHE STRING "Blink led pin number.") # default: 22
if(DEBUG)
    message(STATUS "CONFIG_BLINK_GPIO value: ${CONFIG_BLINK_GPIO}")
endif()
add_compile_definitions(CONFIG_BLINK_GPIO=${CONFIG_BLINK_GPIO})

#add_subdirectory(WiFiMan)
#add_subdirectory(WiFiMan/src)
