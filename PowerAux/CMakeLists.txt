include_directories(include)

add_subdirectory(lib)

add_executable(PowerAux src/main.cpp)

target_link_libraries(PowerAux PRIVATE mbed-os-lib Common-lib PowerAux-lib)

mbed_set_post_build(PowerAux)
