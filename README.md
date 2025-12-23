# STM32 Nucleo Firmware Project (C++ / CMake / DroneCAN / FreeRTOS / ETC.)

This project is a modular STM32 firmware written in C++, built using CMake, and organized into reusable modules under the App/ directory.

## DroneCAN demo project (WIP, Check out [here](https://github.com/JWaik/nucleo-f767zi-demo/tree/dronecan))
### Features
- C++17 firmware for STM32 Nucleo boards
- CMake-based build system (supports VSCode, CLion, Make, Ninja)
- Modular project structure:
- App/DroneCAN (DroneCAN node implementation)
- libcanard integration
- Pre-generated DSDL support
- Easy-to-extend architecture for additional modules
- Clean separation of executable vs. application libraries

## Example CAN Configuration using CubeMX
- Check out this [docs link!](CAN_Configurations.md) 

## FreeRTOS demo project (N/A)
