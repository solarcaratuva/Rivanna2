

add_executable(Testing src/main.cpp)

target_link_libraries(Testing PRIVATE mbed-os-lib Common-lib)

mbed_set_post_build(Testing)
