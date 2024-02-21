cmake_minimum_required(VERSION 3.27)

set(PICO_SDK_FETCH_FROM_GIT on)
include(pico_sdk_import.cmake)

project(BMP280 C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})

pico_sdk_init()

add_executable(BMP280
    src/main.cpp
    src/BMP280/BMP280.cpp
)

target_link_libraries(BMP280
    pico_stdlib
    hardware_clocks
    hardware_i2c
)

pico_add_extra_outputs(BMP280)
pico_enable_stdio_usb(BMP280 1)
pico_enable_stdio_uart(BMP280 0)
