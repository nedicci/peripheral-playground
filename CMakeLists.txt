cmake_minimum_required(VERSION 3.16)

# Must be set before project() so CMake uses the cross-compiler
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/arm-none-eabi-toolchain.cmake)

project(eevee-fw C ASM)

set(BOARD "" CACHE STRING "Target board (nucleo-g071rb | stm32f407g-disc1)")

set(FREERTOS_DIR ${CMAKE_SOURCE_DIR}/submodules/FreeRTOS)

if(NOT BOARD)
    message(FATAL_ERROR "BOARD is not set. Use: cmake -DBOARD=nucleo-g071rb or -DBOARD=stm32f407g-disc1")
endif()

if(BOARD STREQUAL "nucleo-g071rb")
    set(BOARD_DIR     ${CMAKE_SOURCE_DIR}/board/nucleo-g071rb)
    set(STARTUP_FILE  ${BOARD_DIR}/startup_stm32g071xx.s)
    set(LINKER_SCRIPT ${BOARD_DIR}/STM32G071RBTX_FLASH.ld)
    set(MCU_FLAGS     -mcpu=cortex-m0plus -mthumb)
    set(FREERTOS_PORT GCC/ARM_CM0)
elseif(BOARD STREQUAL "stm32f407g-disc1")
    set(BOARD_DIR     ${CMAKE_SOURCE_DIR}/board/stm32f407g-disc1)
    set(STARTUP_FILE  ${BOARD_DIR}/startup_stm32f407xx.s)
    set(LINKER_SCRIPT ${BOARD_DIR}/STM32F407VGTx_FLASH.ld)
    set(MCU_FLAGS     -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=softfp)
    set(FREERTOS_PORT GCC/ARM_CM4F)
else()
    message(FATAL_ERROR "Unknown BOARD: ${BOARD}")
endif()

add_library(freertos STATIC
    ${FREERTOS_DIR}/tasks.c
    ${FREERTOS_DIR}/queue.c
    ${FREERTOS_DIR}/list.c
    ${FREERTOS_DIR}/timers.c
    ${FREERTOS_DIR}/portable/MemMang/heap_4.c
    ${FREERTOS_DIR}/portable/${FREERTOS_PORT}/port.c
    ${FREERTOS_DIR}/portable/${FREERTOS_PORT}/portasm.c
)

target_include_directories(freertos PUBLIC
    ${FREERTOS_DIR}/include
    ${FREERTOS_DIR}/portable/${FREERTOS_PORT}
    ${CMAKE_SOURCE_DIR}/cfg
)

target_compile_options(freertos PRIVATE ${MCU_FLAGS})

add_executable(eevee-fw
    ${STARTUP_FILE}
    src/main.c
    src/app_hooks.c
    src/led_mgr/led_mgr.c
    src/btn_mgr/btn_mgr.c
    src/uart_mgr/uart_mgr.c
)

target_include_directories(eevee-fw PRIVATE
    src/led_mgr   # led_mgr.h
    src/btn_mgr   # btn_mgr.h
    src/uart_mgr  # uart_mgr.h
    ${BOARD_DIR}  # board.h
    ${FREERTOS_DIR}/include
    ${FREERTOS_DIR}/portable/${FREERTOS_PORT}
)

target_link_libraries(eevee-fw PRIVATE freertos)

target_compile_options(eevee-fw PRIVATE
    ${MCU_FLAGS}
    -O2
    -Wall
    -Wextra
    -fdata-sections
    -ffunction-sections
    -ffreestanding
)

target_link_options(eevee-fw PRIVATE
    ${MCU_FLAGS}
    -T${LINKER_SCRIPT}
    -Wl,--gc-sections
    -Wl,-Map=${CMAKE_BINARY_DIR}/eevee-fw.map
    -specs=nano.specs
    -specs=nosys.specs
    -nostartfiles
)

set_target_properties(eevee-fw PROPERTIES SUFFIX ".elf")

find_program(OBJCOPY arm-none-eabi-objcopy REQUIRED)
find_program(SIZE    arm-none-eabi-size    REQUIRED)

add_custom_command(TARGET eevee-fw POST_BUILD
    COMMAND ${OBJCOPY} -O ihex   $<TARGET_FILE:eevee-fw> ${CMAKE_BINARY_DIR}/eevee-fw.hex
    COMMAND ${OBJCOPY} -O binary $<TARGET_FILE:eevee-fw> ${CMAKE_BINARY_DIR}/eevee-fw.bin
    COMMAND ${SIZE}              $<TARGET_FILE:eevee-fw>
    COMMENT "Generating eevee-fw.hex / eevee-fw.bin"
)
