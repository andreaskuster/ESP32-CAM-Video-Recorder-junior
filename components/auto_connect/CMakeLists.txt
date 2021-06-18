idf_component_register(
        SRCS "auto_connect.cpp"
        INCLUDE_DIRS "."
        REQUIRES wifimanager-esp32)

set_property(TARGET ${COMPONENT_LIB} APPEND PROPERTY LINK_INTERFACE_MULTIPLICITY 3)
