cmake_minimum_required(VERSION 3.17)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmodules-ts -fcommon -fno-rtti -fno-exceptions")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PICO_DEOPTIMIZED_DEBUG 1)

# path to PICO utilities (if needed)
if (NOT DEFINED ENV{PIOASM_DIR})
        message("PIOASM: set PIOASM_DIR env variable if you use PIO")
else()
        message("PIOASM: PIOASM_DIR env variable is set to '$ENV{PIOASM_DIR}'")
        set(pioasm_DIR $ENV{PIOASM_DIR})
endif()
if (NOT DEFINED ENV{PICOTOOL_DIR})
        message("PICOTOOL: set PICOTOOL_DIR env variable if you create uf2 output with pico_add_extra_outputs()")
else()
        message("PICOTOOL: PICOTOOL_DIR env variable is set to '$ENV{PICOTOOL_DIR}'")
        set(picotool_DIR $ENV{PICOTOOL_DIR})
endif()

if (DEFINED ENV{PICO_PLATFORM})
        message("PICO_PLATFORM: PICO_PLATFORM env variable is set to '$ENV{PICO_PLATFORM}'")
        set(PICO_PLATFORM $ENV{PICO_PLATFORM} CACHE STRING "Pico Platform")
else()
        message("PICO_PLATFORM: PICO_PLATFORM env variable is not set. Using default")
endif()

if (DEFINED ENV{PICO_BOARD})
        message("PICO_BOARD: PICO_BOARD env variable is set to '$ENV{PICO_BOARD}'")
        set(PICO_BOARD $ENV{PICO_BOARD} CACHE STRING "Board type")
else()
        message("PICO_BOARD: PICO_BOARD env variable is not set. Using default")
endif()

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(pico_scpi_usbtmc_labtool C CXX ASM)


if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "  Diag: maximum debug info")
    #I've set this to allow breakpoints on any source line
    set(PICO_DEOPTIMIZED_DEBUG=1)
endif ()


pico_sdk_init()

# include(FetchContent)
# FetchContent_Declare(
#         pico_scpi_usbtmc_lablib
#         GIT_REPOSITORY https://github.com/jancumps/pico_scpi_usbtmc_lablib.git
#         GIT_TAG master
#         GIT_SUBMODULES_RECURSE FALSE
# )
# message("Downloading PICO SCPI USBTMC Lab Lib")
# FetchContent_Populate(pico_scpi_usbtmc_lablib)

pico_add_subdirectory(pico_scpi_usbtmc_lablib)

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function 
        -Wno-maybe-uninitialized
        )



add_executable(${CMAKE_PROJECT_NAME}
        ${CMAKE_CURRENT_SOURCE_DIR}/source/main.c
        ${CMAKE_CURRENT_SOURCE_DIR}/source/usb/usb_descriptors.c
        ${CMAKE_CURRENT_SOURCE_DIR}/source/scpi/scpi-def.c
        ${CMAKE_CURRENT_SOURCE_DIR}/source/scpi/registers/registers.c
        ${CMAKE_CURRENT_SOURCE_DIR}/source/gpio/gpio_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/source/adc/adc_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/source/i2c/i2c_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/source/adc16/adc16_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/source/pwm/pwm_utils.c
        source/adc16/adc16_utils.c source/adc16/adc16_utils.h)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/source
        ${CMAKE_CURRENT_LIST_DIR}/source/usb
        ${CMAKE_CURRENT_LIST_DIR}/source/scpi
        ${CMAKE_CURRENT_LIST_DIR}/source/gpio
        ${CMAKE_CURRENT_LIST_DIR}/source/adc
        ${CMAKE_CURRENT_LIST_DIR}/source/i2c
        ${CMAKE_CURRENT_LIST_DIR}/source/adc16
        ${CMAKE_CURRENT_LIST_DIR}/source/pwm
)

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC pico_stdlib 
        tinyusb_device tinyusb_board hardware_gpio hardware_adc 
        hardware_pwm hardware_i2c pico_unique_id
        pico_scpi_usbtmc_lablib)

# TODO: custom script doesn't work with RP2350 (risc) and picotool - find a way to reserve 4K for persistent data
# pico_set_linker_script(${CMAKE_PROJECT_NAME} ${CMAKE_SOURCE_DIR}/memmap_custom.ld)

pico_add_extra_outputs(${CMAKE_PROJECT_NAME})

# enable use of scpi_user_config.h, to support custom device specific registers 
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE SCPI_USER_CONFIG=1)

# usb output, uart output
 pico_enable_stdio_usb(${CMAKE_PROJECT_NAME} 0)
 pico_enable_stdio_uart(${CMAKE_PROJECT_NAME} 0)
