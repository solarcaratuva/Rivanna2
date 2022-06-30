cmake_minimum_required(VERSION 3.19.0)

set(MBED_PATH ${CMAKE_CURRENT_SOURCE_DIR}/mbed-os CACHE INTERNAL "")
set(MBED_CONFIG_PATH ${CMAKE_CURRENT_BINARY_DIR} CACHE INTERNAL "")
set(APP_TARGET Rivanna2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

include(${MBED_PATH}/tools/cmake/app.cmake)

project(${APP_TARGET})

add_subdirectory(TARGET_UVA_SOLAR_CAR)
add_subdirectory(${MBED_PATH})

mbed_create_distro(mbed-os-lib mbed-os mbed-events mbed-rtos)

add_subdirectory(Common)

add_subdirectory(ECU)
add_subdirectory(Motor)
add_subdirectory(PowerAux)
add_subdirectory(Solar)

option(VERBOSE_BUILD "Have a verbose build process")
if(VERBOSE_BUILD)
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif()
