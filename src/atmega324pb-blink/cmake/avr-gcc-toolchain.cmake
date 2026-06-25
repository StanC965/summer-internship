set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)

find_program(AVR_GCC avr-gcc REQUIRED)
find_program(AVR_GXX avr-g++ REQUIRED)
find_program(AVR_OBJCOPY avr-objcopy REQUIRED)
find_program(AVR_OBJDUMP avr-objdump REQUIRED)
find_program(AVR_SIZE avr-size REQUIRED)

set(CMAKE_C_COMPILER ${AVR_GCC})
set(CMAKE_CXX_COMPILER ${AVR_GXX})
set(CMAKE_ASM_COMPILER ${AVR_GCC})

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
