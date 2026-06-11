#!/usr/bin/env bash
set -euo pipefail

BUILD_DIR="${1:-build}"
ELF="${BUILD_DIR}/eevee-fw.elf"

if [[ ! -f "$ELF" ]]; then
    echo "Error: eevee-fw not found at '$ELF'" >&2
    echo "Usage: ./flash.sh [build-dir]" >&2
    exit 1
fi

# Select OpenOCD target config from CMakeCache BOARD variable
BOARD=$(grep -m1 "^BOARD:" "${BUILD_DIR}/CMakeCache.txt" 2>/dev/null | cut -d= -f2)
case "$BOARD" in
    stm32f407g-disc1) TARGET_CFG="target/stm32f4x.cfg" ;;
    *)                TARGET_CFG="target/stm32g0x.cfg"  ;;
esac

echo "Flashing $ELF with $TARGET_CFG ..."

openocd \
    -f interface/stlink.cfg \
    -f "$TARGET_CFG" \
    -c "program $ELF verify reset exit"
