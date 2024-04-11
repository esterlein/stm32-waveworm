# **WAVEWORM**

## About
The goal of the project is to visualize electromagnetic fields in three-dimensional space. The prototype is being written for an STM32F4 series board with an Arm Cortex-M4 microcontroller, and the current version includes peripheral drivers and a basic 3D rendering pipeline with static memory allocation optimized for embedded environments. In the future, the rendering engine will be moved to a separate repository for desktop host platforms. The design also includes an IR mesh network as a topology and sensing data collector. There are several approaches to using IR beacons for positioning, which will be explored further.

The project's most challenging problem is the topological interpolation of the electromagnetic field based on sparse sampling. General properties of electromagnetic fields, such as the sampling density to wavelength ratio and the inverse square law, will be utilized. The [field interpolation simulator](https://github.com/esterlein/waveworm-field-caster) created for this project is used for research and development, and the repository readme file includes additional information on this topic.

## Disclaimer
This project is a Work In Progress. Some parts are not implemented or are not working.

## Prerequisites
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
