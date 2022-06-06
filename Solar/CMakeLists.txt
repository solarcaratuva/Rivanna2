include_directories(include)

add_subdirectory(lib)

add_executable(Solar src/main.cpp)

target_link_libraries(Solar PRIVATE mbed-os-lib Common-lib Solar-lib)

mbed_set_post_build(Solar)
