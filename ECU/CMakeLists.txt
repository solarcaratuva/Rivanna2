include_directories(include)

add_subdirectory(lib)

add_executable(ECU src/main.cpp)

target_link_libraries(ECU PRIVATE mbed-os-lib Common-lib ECU-lib)

mbed_set_post_build(ECU)
