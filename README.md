# **STM32-WAVEWORM**

## About
The project is aimed to visualize multichannel analog input in 3D space.
It is being written for the STM32F4 series board with an Arm Cortex-M4 processor.
Some parts of the code for graphics primitives is a modified version of a modified version of Adafruit code.
This code will be replaced **very soon**.

## Prerequisites
Currently developing on MacOS but should compile on Linux with minor path adjustments.
* [Arm GNU Toolchain](https://developer.arm.com/Tools%20and%20Software/GNU%20Toolchain)
* [GNU Make](https://www.gnu.org/software/make/)
* ST-Link/V2
* [libopencm3](https://github.com/libopencm3/libopencm3) library
* [OpenOCD](https://openocd.org/) as a GDB server

## Build & Flash
```
git clone git@github.com:esterlein/stm32-waveworm.git
cd stm32-waveworm
git submodule init
git submodule update
cd libopencm3
make
cd ..
make all
make flash
```
