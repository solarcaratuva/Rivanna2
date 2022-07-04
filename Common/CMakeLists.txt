add_library(Common-lib
    src/dbc/structs/bps.c
    src/dbc/structs/motor_controller.c
    src/dbc/structs/rivanna2.c
    src/CANInterface.cpp
    src/log.cpp
    src/MainCANInterface.cpp
    src/Printing.cpp
)

target_include_directories(Common-lib PRIVATE include/dbc/structs)
target_include_directories(Common-lib PUBLIC include)

target_link_libraries(Common-lib mbed-os-lib)
