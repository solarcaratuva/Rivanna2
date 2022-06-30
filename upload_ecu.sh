#!/bin/bash
source ./confirm_unique_id.sh
if confirm_unique_id "0x1B002F" "0x32535007" "0x20333657"
then
    st-flash --connect-under-reset --reset write cmake_build/UVA_SOLAR_CAR/develop/GCC_ARM/ECU/ECU.bin 0x8000000
else
    echo "ERROR: This is not the ECU board."
    exit 1
fi
