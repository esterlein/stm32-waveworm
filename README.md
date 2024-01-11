STM32-WAVEWORM
Work In Progress

The project is aimed to visualize multichannel analog input in 3D space.
It is being written for the STM32F4 series board with an Arm Cortex-M4 chip.
Some parts of the code for graphics primitives is a modified version of a modified version of AdaFruit code. This code will be replaced very soon.

Prerequisites

Arm GNU Toolchain
GNU Make
ST-Link/V2
libopencm3 library
OpenOCD as a GDB server

Currently developing on MacOS but should compile on Linux with minor path adjustments.

Build & Flash

git clone git@github.com:esterlein/stm32-waveworm.git
cd stm32-waveworm
git submodule init
git submodule update
cd libopencm3
make
cd ../main
make all
make flash