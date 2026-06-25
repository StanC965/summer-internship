cmake_minimum_required(VERSION 3.20)

project(atmega324pb_blink C)

set(MCU atmega324pb CACHE STRING "AVR MCU")
set(F_CPU 16000000UL CACHE STRING "CPU frequency")
set(TARGET blink)

set(CMAKE_EXECUTABLE_SUFFIX ".elf")

add_executable(${TARGET} main.c)

target_compile_definitions(${TARGET} PRIVATE F_CPU=${F_CPU})
target_compile_options(${TARGET} PRIVATE
    -mmcu=${MCU}
    -Os
    -g3
    -Wall
    -Wextra
    -std=c11
)

target_link_options(${TARGET} PRIVATE
    -mmcu=${MCU}
    -Wl,-Map=${CMAKE_BINARY_DIR}/${TARGET}.map,--cref
)

find_program(AVR_OBJCOPY avr-objcopy REQUIRED)
find_program(AVR_OBJDUMP avr-objdump REQUIRED)
find_program(AVR_SIZE avr-size REQUIRED)
find_program(ATPROGRAM atprogram)

add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/${TARGET}.hex
    COMMAND ${AVR_OBJCOPY} -O ihex -R .eeprom $<TARGET_FILE:${TARGET}> ${CMAKE_BINARY_DIR}/${TARGET}.hex
    DEPENDS ${TARGET}
    VERBATIM
)

add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/${TARGET}.lst
    COMMAND ${AVR_OBJDUMP} -h -S $<TARGET_FILE:${TARGET}> > ${CMAKE_BINARY_DIR}/${TARGET}.lst
    DEPENDS ${TARGET}
    VERBATIM
)

add_custom_target(artifacts ALL
    DEPENDS ${CMAKE_BINARY_DIR}/${TARGET}.hex ${CMAKE_BINARY_DIR}/${TARGET}.lst
)

add_custom_target(size ALL
    COMMAND ${AVR_SIZE} -C --mcu=${MCU} $<TARGET_FILE:${TARGET}>
    DEPENDS ${TARGET}
    VERBATIM
)

if(ATPROGRAM)
    add_custom_target(flash
        COMMAND ${ATPROGRAM} -t edbg -i isp -d ${MCU} program -f ${CMAKE_BINARY_DIR}/${TARGET}.hex
        DEPENDS ${CMAKE_BINARY_DIR}/${TARGET}.hex
        VERBATIM
    )
else()
    message(WARNING "'atprogram' not found. The 'flash' target will be unavailable.")
endif()
