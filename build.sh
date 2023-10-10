
#!/bin/sh

#export CMAKE_BUILD_TYPE=Release
export CMAKE_BUILD_TYPE=Debug

if [ -d "build" ]; then
  rm -rf build
fi

mkdir build

#if ! [ -f ~/.ssh/known_hosts ]; then
#  ssh-keyscan github.com > ~/.ssh/known_hosts
#fi


if [ ! -d "pico-sdk" ]; then
    git clone https://github.com/raspberrypi/pico-sdk.git
fi
cd pico-sdk
git submodule update --init
cd ..

CURRENT_DIR=$(pwd)

export PICO_SDK_PATH=$CURRENT_DIR/pico-sdk

cd $PICO_SDK_PATH/lib/tinyusb/src/class
git apply $CURRENT_DIR/usbtmc_device.patch
cd $CURRENT_DIR

if [ ! -d "scpi-parser" ]; then
    git clone https://github.com/j123b567/scpi-parser.git
fi
cd scpi-parser
git submodule update --init
cd ..

export SCPI_LIB_PATH="./scpi-parser/libscpi"

cmake -B build -S .
make -C build