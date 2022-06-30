add_library(Solar-lib
    src/mcp3008.cpp
    src/SolarInputReader.cpp
)

target_include_directories(Solar-lib PUBLIC include)

target_link_libraries(Solar-lib mbed-os-lib Common-lib)
