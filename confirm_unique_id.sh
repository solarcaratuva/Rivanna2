#!/bin/bash
# Script used to ensure that each upload*.sh script only can upload to the correct board.
# Each STM32 chip has a unique ID, which we read here.
# This script takes three arguments, the three parts of that ID in hex with no leading zeroes.
# It returns 0 if the connected board has the same unique ID as the provided arguments; it returns 1 otherwise.
# e.g. ./confirm_unique_id.sh 0x500031 0x32535007 0x20333657

function confirm_unique_id {
    PART_0_EXPECTED=$1
    PART_1_EXPECTED=$2
    PART_2_EXPECTED=$3

    STM_UNIQUE_ID_BASE_ADDRESS="0x1FFF7590"

    st-flash --connect-under-reset read /tmp/rivanna2-stm-unique-id.bin $STM_UNIQUE_ID_BASE_ADDRESS 0x0B

    HEXDUMP_OUTPUT=`hexdump /tmp/rivanna2-stm-unique-id.bin --format '3/4 "0x%X "'`

    PART_0_ACTUAL=`echo $HEXDUMP_OUTPUT | cut -d ' ' -f 1`
    PART_1_ACTUAL=`echo $HEXDUMP_OUTPUT | cut -d ' ' -f 2`
    PART_2_ACTUAL=`echo $HEXDUMP_OUTPUT | cut -d ' ' -f 3`

    if [ "$PART_0_EXPECTED" == "$PART_0_ACTUAL" ] && [ "$PART_1_EXPECTED" == "$PART_1_ACTUAL" ] && [ "$PART_2_EXPECTED" == "$PART_2_ACTUAL" ]
    then
        return 0
    else
        return 1
    fi
}
