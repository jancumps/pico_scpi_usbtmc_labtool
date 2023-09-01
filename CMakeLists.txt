cmake_minimum_required(VERSION 3.13)

# set(PICO_DEOPTIMIZED_DEBUG 1)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(pico_scpi_usbtmc_labtool C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "  Diag: maximum debug info")
    #I've set this to allow breakpoints on any source line
    set(PICO_DEOPTIMIZED_DEBUG=1)
endif ()

pico_sdk_init()

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function 
        -Wno-maybe-uninitialized
        )

add_executable(pico_scpi_usbtmc_labtool
        ${CMAKE_CURRENT_SOURCE_DIR}/source/main.c
        ${CMAKE_CURRENT_SOURCE_DIR}/source/usb/usb_descriptors.c
        ${CMAKE_CURRENT_SOURCE_DIR}/source/usb/usbtmc_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/source/scpi/scpi-def.c
        ${CMAKE_CURRENT_SOURCE_DIR}/source/gpio/gpio_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/source/adc/adc_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/source/adc16/adc16_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/source/pwm/pwm_utils.c
        $ENV{SCPI_LIB_PATH}/src/parser.c
        $ENV{SCPI_LIB_PATH}/src/lexer.c
        $ENV{SCPI_LIB_PATH}/src/error.c
        $ENV{SCPI_LIB_PATH}/src/ieee488.c
        $ENV{SCPI_LIB_PATH}/src/minimal.c
        $ENV{SCPI_LIB_PATH}/src/utils.c
        $ENV{SCPI_LIB_PATH}/src/units.c
        $ENV{SCPI_LIB_PATH}/src/fifo.c
        source/adc16/adc16_utils.c source/adc16/adc16_utils.h)

target_include_directories(pico_scpi_usbtmc_labtool PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/source
        ${CMAKE_CURRENT_LIST_DIR}/source/usb
        ${CMAKE_CURRENT_LIST_DIR}/source/scpi
        ${CMAKE_CURRENT_LIST_DIR}/source/gpio
        ${CMAKE_CURRENT_LIST_DIR}/source/adc
        ${CMAKE_CURRENT_LIST_DIR}/source/adc16
        ${CMAKE_CURRENT_LIST_DIR}/source/pwm
        $ENV{SCPI_LIB_PATH}/inc
)

target_link_libraries(pico_scpi_usbtmc_labtool PUBLIC pico_stdlib tinyusb_device tinyusb_board hardware_gpio hardware_adc hardware_pwm hardware_i2c pico_unique_id)

pico_set_linker_script(pico_scpi_usbtmc_labtool ${CMAKE_SOURCE_DIR}/memmap_custom.ld)

pico_add_extra_outputs(pico_scpi_usbtmc_labtool)

# usb output, uart output
 pico_enable_stdio_usb(pico_scpi_usbtmc_labtool 0)
 pico_enable_stdio_uart(pico_scpi_usbtmc_labtool 0)
