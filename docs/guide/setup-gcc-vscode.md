# Setup GCC + VS Code

This guide covers setting up the AVR GCC toolchain with VS Code for the ATmega324PB development.

## Prerequisites

Install the following tools:

1. **AVR-GCC**: The GNU C compiler for AVR microcontrollers
2. **CMake**: Build system used in this project
3. **Ninja**: Build tool for faster compilation
4. **VS Code**: Code editor with C/C++ extensions

## AVR-GCC Installation

Download and install AVR-GCC from [Microchip](https://www.microchip.com/en-us/development-tools/avr-and-sam-downloads-archive) or use a package manager.

## VS Code Extensions

Install the recommended extensions:

- **C/C++** (Microsoft) - For IntelliSense and debugging
- **CMake** (Twxs) - For CMake support
- **CMake Tools** (Microsoft) - For CMake integration

## Project Configuration

The project uses CMake with the AVR-GCC toolchain. Build configurations are defined in:

- `src/atmega324pb-blink/CMakeLists.txt` - Project build definition
- `src/atmega324pb-blink/cmake/avr-gcc-toolchain.cmake` - Toolchain configuration

## Building the Project

Use the configured tasks in VS Code:

1. **CMake Configure** - Configures the build system
2. **Build** - Compiles the project
3. **Flash** - Uploads the binary to the microcontroller

See the [Getting Started](./getting-started.md) guide for step-by-step instructions.
