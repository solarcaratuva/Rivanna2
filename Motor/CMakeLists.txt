include_directories(include)

add_subdirectory(lib)

add_executable(Motor src/main.cpp)

target_link_libraries(Motor PRIVATE mbed-os-lib Common-lib Motor-lib)

mbed_set_post_build(Motor)
