add_library(ECU-lib
    src/ECUInputReader.cpp
)

target_include_directories(ECU-lib PUBLIC include)

target_link_libraries(ECU-lib mbed-os-lib Common-lib)
