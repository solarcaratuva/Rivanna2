add_library(mbed-uva-solar-car INTERFACE)

target_sources(mbed-uva-solar-car
    INTERFACE
        PeripheralPins.c
        system_clock.c
)

target_include_directories(mbed-uva-solar-car
    INTERFACE
        .
)

target_link_libraries(mbed-uva-solar-car INTERFACE mbed-stm32g473xe)