#!/usr/bin/env bash
set -euo pipefail

ELF="${1:-build/blink.elf}"

if [[ ! -f "$ELF" ]]; then
    echo "Error: firmware not found at '$ELF'" >&2
    echo "Run: cmake -S . -B build -G Ninja && cmake --build build" >&2
    exit 1
fi

echo "Flashing $ELF ..."

openocd \
    -f interface/stlink.cfg \
    -f target/stm32g0x.cfg \
    -c "program $ELF verify reset exit"
