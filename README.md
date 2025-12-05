# Nucleo-F767ZI Demo — DroneCAN branch

## Overview

This repository contains a demo project for the STM32 Nucleo‑144 F767ZI board, targeting use with DroneCAN (formerly UAVCAN) — a lightweight protocol for reliable intra-vehicle communication over CAN. It integrates the DroneCAN stack and demonstrates how to run a DroneCAN node on Nucleo-F767ZI.  

The Nucleo-F767ZI board is a versatile, Arduino-compatible development board with a powerful STM32F767 microcontroller, making it a convenient platform for prototyping embedded systems.

## Repository Structure

/ — root project files \
├── App/DroneCAN — application code using DroneCAN \
├── Core/ — core HAL/RTOS (or bare-metal) setup for F767ZI \
├── Drivers/ — MCU drivers, peripheral drivers, HAL wrappers \
├── modules/DroneCAN — DroneCAN library module \
├── Tools/ — build scripts, helper tools \
├── cmake/ — CMake configuration \
├── STM32F767XX_FLASH.ld — linker script for STM32F767xx \
├── startup_stm32f767xx.s — startup assembly for Cortex-M7 \
├── nucleo-f767zi-demo.ioc — configuration file (for STM32CubeIDE or alike) \
├── .gitignore \
└── CMakeLists.txt — top-level CMake build file


## Features & What’s Included

- Integration of DroneCAN protocol stack for CAN-bus communications. 
- Board support for STM32F767ZI including initialization, startup, and linking (startup code + linker script).  
- Modular structure dividing hardware abstraction (drivers), core system code, and application logic.  
- Build system configured with CMake, enabling flexibility in toolchains and IDEs.  
- Example application under `App/DroneCAN` demonstrating a working DroneCAN node on Nucleo.  

## Prerequisites

To build and run this project, you will need:

- A STM32F767ZI-based Nucleo-144 board (If you are using the alternative version, the configuration and included header name may need to be changed respectively)
- A CAN transceiver (if using external CAN bus hardware)  
- A development environment/toolchain supporting STM32 + Cortex-M7 + CMake (e.g. GNU ARM Embedded Toolchain, STM32CubeIDE, or similar)  
- (Optional) ST-LINK/V2-1 for flashing and debugging — Nucleo-F767ZI includes ST-LINK on board.


## Getting Started

1. Clone the repository and checkout the `dronecan` branch:

   ```bash
   git clone https://github.com/JWaik/nucleo-f767zi-demo.git
   cd nucleo-f767zi-demo
   git checkout dronecan
Configure the build (e.g. using CMake):


mkdir build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=path/to/your/arm/toolchain.cmake
make
Flash the compiled firmware to your Nucleo-F767ZI using ST-LINK or your preferred programmer.

Connect the CAN transceiver and a CAN bus network (or peer node).

Run the example DroneCAN node — it should appear on the CAN network and respond appropriately.

Usage & Configuration
Customize MCU and board settings in nucleo-f767zi-demo.ioc (if using STM32Cube-based setup) or equivalent configuration.

Modify DroneCAN settings (node ID, bitrate, message handlers) under App/DroneCAN.

Add or extend drivers under Drivers/ if you need additional peripherals.

Use CMakeLists.txt and cmake/ folder to tailor build flags, optimization level, or integrate an RTOS if required.

N/A WIP
