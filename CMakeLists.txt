cmake_minimum_required(VERSION 3.27)

set(PICO_SDK_FETCH_FROM_GIT on)
include(pico_sdk_import.cmake)

project(MTShuffler C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})

pico_sdk_init()

add_executable(MTShuffler
    src/main.cpp
    src/include/Servo/Servo.cpp
    src/include/Stepper/Stepper.cpp
    src/include/Control/Control.cpp
)

target_link_libraries(MTShuffler
    pico_stdlib
    hardware_pwm
    hardware_clocks
    hardware_i2c
)

pico_add_extra_outputs(MTShuffler)
pico_enable_stdio_usb(MTShuffler 1)
pico_enable_stdio_uart(MTShuffler 0)
