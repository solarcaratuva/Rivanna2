#ifndef STM_UNIQUE_ID_H
#define STM_UNIQUE_ID_H

#include "Printing.h"

#define STM_UNIQUE_ID_BASE_ADDRESS 0x1FFF7590

/**
 * Struct used to store STM unique device IDs.
 * https://www.st.com/resource/en/reference_manual/dm00355726-stm32g4-series-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf
 */
typedef struct STMUniqueID {
    uint32_t part0;
    uint32_t part1;
    uint32_t part2;
} STMUniqueID;

void read_unique_id(STMUniqueID *id) {
    id->part0 = *((volatile uint32_t *)(STM_UNIQUE_ID_BASE_ADDRESS + 0x00));
    id->part1 = *((volatile uint32_t *)(STM_UNIQUE_ID_BASE_ADDRESS + 0x04));
    id->part2 = *((volatile uint32_t *)(STM_UNIQUE_ID_BASE_ADDRESS + 0x08));
}

void print_unique_id(STMUniqueID *id) {
    PRINT("STM unique id:\r\n\tpart0: %X\r\n\tpart1: %X\r\n\tpart2: %X\r\n", id->part0, id->part1, id->part2);
}

void check_ecu_board() {
    STMUniqueID id;
    read_unique_id(&id);
    if (id.part0 != 0x1B002F || id.part1 != 0x32535007 || id.part2 != 0x20333657) {
        PRINT("WARNING: ECU code uploaded to incorrect board\r\n");
    }
}

void check_motor_board() {
    STMUniqueID id;
    read_unique_id(&id);
    if (id.part0 != 0x2D002F || id.part1 != 0x32535007 || id.part2 != 0x20333657) {
        PRINT("WARNING: Motor code uploaded to incorrect board\r\n");
    }
}

void check_power_aux_board() {
    STMUniqueID id;
    read_unique_id(&id);
    if (id.part0 != 0x3C0031 || id.part1 != 0x32535007 || id.part2 != 0x20333657) {
        PRINT("WARNING: PowerAux code uploaded to incorrect board\r\n");
    }
}


void check_solar_board() {
    STMUniqueID id;
    read_unique_id(&id);
    if (id.part0 != 0x500031 || id.part1 != 0x32535007 || id.part2 != 0x20333657) {
        PRINT("WARNING: Solar code uploaded to incorrect board\r\n");
    }
}

#endif
