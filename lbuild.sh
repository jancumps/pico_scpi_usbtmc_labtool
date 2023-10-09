#!/bin/sh

#On MacOS
alias nproc="sysctl -n hw.logicalcpu"
export CMAKE_BUILD_PARALLEL_LEVEL=$(nproc)
export PICO_TOOLCHAIN_PATH=/Applications/ArmGNUToolchain/12.3.rel1/arm-none-eabi/bin/

./build.sh