cmake_minimum_required(VERSION 3.16)

# Must be set before project() so CMake uses the cross-compiler
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/arm-none-eabi-toolchain.cmake)

project(blink C ASM)

set(MCU_FLAGS
    -mcpu=cortex-m0plus
    -mthumb
)

set(BOARD_DIR ${CMAKE_SOURCE_DIR}/board/nucleo-g071rb)

add_executable(blink
    ${BOARD_DIR}/startup_stm32g071xx.s
    src/main.c
    src/led_mgr/led_mgr.c
)

target_include_directories(blink PRIVATE
    src/led_mgr   # led_mgr.h
    ${BOARD_DIR}  # board.h
)

target_compile_options(blink PRIVATE
    ${MCU_FLAGS}
    -O2
    -Wall
    -Wextra
    -fdata-sections
    -ffunction-sections
    -ffreestanding
)

target_link_options(blink PRIVATE
    ${MCU_FLAGS}
    -T${BOARD_DIR}/STM32G071RBTX_FLASH.ld
    -Wl,--gc-sections
    -Wl,-Map=${CMAKE_BINARY_DIR}/blink.map
    -specs=nano.specs
    -specs=nosys.specs
    -nostartfiles
)

set_target_properties(blink PROPERTIES SUFFIX ".elf")

find_program(OBJCOPY arm-none-eabi-objcopy REQUIRED)
find_program(SIZE    arm-none-eabi-size    REQUIRED)

add_custom_command(TARGET blink POST_BUILD
    COMMAND ${OBJCOPY} -O ihex   $<TARGET_FILE:blink> ${CMAKE_BINARY_DIR}/blink.hex
    COMMAND ${OBJCOPY} -O binary $<TARGET_FILE:blink> ${CMAKE_BINARY_DIR}/blink.bin
    COMMAND ${SIZE}              $<TARGET_FILE:blink>
    COMMENT "Generating blink.hex / blink.bin"
)
