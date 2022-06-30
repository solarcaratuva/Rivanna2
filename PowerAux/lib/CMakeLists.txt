add_library(PowerAux-lib
    src/BPSCANInterface.cpp
    src/BPSRelayController.cpp
)

target_include_directories(PowerAux-lib PUBLIC include)

target_link_libraries(PowerAux-lib mbed-os-lib Common-lib)
