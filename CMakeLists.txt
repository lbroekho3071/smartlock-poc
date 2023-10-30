# Just a recent number
cmake_minimum_required(VERSION 3.18)

# Use AVR GCC toolchain definition in your HOME/Arduino directory
set(ARDUINO_PATH $ENV{HOME}/.arduino)
set(AVR_PORT /dev/tty.usbmodem1101)

# the toolchain to use
set(CMAKE_TOOLCHAIN_FILE ${ARDUINO_PATH}/etc/toolchain-avr.cmake)

# include standard extra targets, like 'upload'
set(CMAKE_PROJECT_INCLUDE ${ARDUINO_PATH}/etc/extratargets-avr.cmake)

# Project name (also the name of the target)
project(RandD)

# Create one target. To generate a list of source files: `find src -name \*.c\*`
add_executable(${PROJECT_NAME} src/main.cpp
        src/hardware/keypad.cpp
        src/hardware/timer.cpp
        src/hardware/lock.cpp
        src/api.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE "${ARDUINO_PATH}/include/arduino")
target_link_directories(${PROJECT_NAME} PRIVATE "${ARDUINO_PATH}/lib")
target_link_libraries(${PROJECT_NAME} core)

# Rename the output to .elf as we will create multiple files
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME}.elf)
