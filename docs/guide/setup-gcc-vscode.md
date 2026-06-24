# Setup GCC + VS Code for ATmega324PB Xplained Pro

This guide migrates your workflow from IAR Embedded Workbench to a free toolchain based on AVR-GCC and Visual Studio Code.

## 1) Install required tools (Windows)

Install these components:

1. AVR 8-bit GNU Toolchain (contains `avr-gcc`, `avr-gdb`, `avr-objdump`, `avr-size`)
2. Microchip Studio (for `atprogram` utility and USB drivers for onboard mEDBG)
3. CMake
4. `avarice` via MSYS2 (GDB server that bridges avr-gdb to the onboard mEDBG over debugWIRE)
5. VS Code extensions:
   - C/C++ (Microsoft)
   - CMake Tools (Microsoft)

After install, verify these commands work from a terminal:

```powershell
avr-gcc --version
avr-gdb --version
atprogram --version
cmake --version
avarice --version
```

## 2) Connect and verify board visibility

Plug in the ATmega324PB Xplained Pro board over USB.

Check that the onboard debugger (mEDBG) is detected:

```powershell
atprogram list
```

Expected: at least one `edbg` tool in the output.

## 3) Build the blink project

This repository already includes a sample project:

- `src/atmega324pb-blink/main.c`
- `src/atmega324pb-blink/CMakeLists.txt`
- `src/atmega324pb-blink/cmake/avr-gcc-toolchain.cmake`
- `.vscode/tasks.json`
- `.vscode/launch.json`

Build from terminal:

```powershell
cmake -S src/atmega324pb-blink -B src/atmega324pb-blink/build -G Ninja -DCMAKE_TOOLCHAIN_FILE=src/atmega324pb-blink/cmake/avr-gcc-toolchain.cmake
cmake --build src/atmega324pb-blink/build --target artifacts
```

Outputs are generated in `src/atmega324pb-blink/build`:

- `blink.elf`
- `blink.hex`
- `blink.lst`
- `blink.map`

## 4) Flash the board

Flash using onboard mEDBG through ISP:

```powershell
cmake --build src/atmega324pb-blink/build --target flash
```

Equivalent command:

```powershell
atprogram -t edbg -i isp -d atmega324pb program -f build/blink.hex
```

## 5) Debug step-by-step in VS Code (real hardware)

`avarice` acts as a GDB server that bridges `avr-gdb` to the onboard mEDBG debugger over the debugWIRE protocol, giving you real chip state directly in VS Code.

**Install avarice on Windows (via MSYS2):**

```powershell
# Inside an MSYS2 MINGW64 shell:
pacman -S mingw-w64-x86_64-avarice
```

**Start the GDB server** once before launching VS Code debug (board must be plugged in):

```powershell
avarice --edbg --debugwire --port 4242
```

**Start debugging in VS Code:**

1. Open Run and Debug.
2. Select `AVR-GDB: hardware mEDBG (ATmega324PB)`.
3. Press Start Debugging.
4. Use breakpoints, Step Over, Step Into as usual.

**What you can inspect:**

| View | How to open in VS Code |
|---|---|
| CPU registers (r0–r31, SREG, SP, PC) | Run and Debug → **Registers** panel |
| SRAM / peripheral memory | Command Palette → **Debug: Open Memory View** |
| Variables / Watch | Standard **Variables** and **Watch** debug panes |
| Disassembly | Right-click source line → **Open Disassembly View** |

**Hardware debug notes:**

- The ATmega324PB has **2 hardware breakpoints** maximum. VS Code will warn if you add more.
- You see **real peripheral register values** (PORTB, TIMSK, USART, etc.) directly from the chip.
- After a debug session, disable debugWIRE to restore normal ISP programming: run `monitor debugwire disable` in the avr-gdb console before detaching.

## 6) Open and read the map file

Linker map is generated automatically:

- `src/atmega324pb-blink/build/blink.map`

Use it to inspect:

- section sizes (`.text`, `.data`, `.bss`)
- symbol addresses
- memory placement

## 7) If onboard LED does not blink

The default blink pin is `PB0`. If your board LED is on another pin, edit these macros in `src/atmega324pb-blink/main.c`:

- `LED_PORT`
- `LED_DDR`
- `LED_PIN`

Then rebuild and flash.
