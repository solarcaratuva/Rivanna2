#ifndef SOLAR_CAN_STRUCTS_H
#define SOLAR_CAN_STRUCTS_H

#include "CANSerializer.h"
#include "CANStruct.h"
#include "Printing.h"

typedef struct SolarCurrent : CANStruct {
    /**
     * 1mA/LSB
     */
    uint16_t total_current;

    SolarCurrent() {}
    SolarCurrent(uint16_t total_current) : total_current(total_current) {}

    SERIALIZATION_METHODS((total_current, 16))

    uint32_t get_message_ID() { return SolarCurrent_MESSAGE_ID; }
    
    void printStruct() {
        PRINT("SolarCurret\n total_currentL %u\n", total_current);
    }

} SolarCurrent;

typedef struct SolarVoltage : CANStruct {
    /**
     * 1mV/LSB
     */
    uint16_t panel1_voltage;
    /**
     * 1mV/LSB
     */
    uint16_t panel2_voltage;
    /**
     * 1mV/LSB
     */
    uint16_t panel3_voltage;
    /**
     * 1mV/LSB
     */
    uint16_t panel4_voltage;

    SolarVoltage() {}
    SolarVoltage(uint16_t panel1_voltage, uint16_t panel2_voltage,
                 uint16_t panel3_voltage, uint16_t panel4_voltage)
        : panel1_voltage(panel1_voltage), panel2_voltage(panel2_voltage),
          panel3_voltage(panel3_voltage), panel4_voltage(panel4_voltage) {}

    SERIALIZATION_METHODS((panel1_voltage, 16), (panel2_voltage, 16),
                          (panel3_voltage, 16), (panel4_voltage, 16))

    uint32_t get_message_ID() { return SolarVoltage_MESSAGE_ID; }
    void printStruct() { 
        PRINT("SolarVoltage\n panel1_voltage: %u\n panel2_voltage: %u\n panel3_voltage: %u\n panel4_voltage: %u\n", panel1_voltage, panel2_voltage, panel3_voltage, panel4_voltage);
    }

} SolarVoltage;

typedef struct SolarTemp : CANStruct {
    /**
     * 1°C/LSB
     */
    uint16_t panel1_temp;
    /**
     * 1°C/LSB
     */
    uint16_t panel2_temp;
    /**
     * 1°C/LSB
     */
    uint16_t panel3_temp;
    /**
     * 1°C/LSB
     */
    uint16_t panel4_temp;

    SolarTemp() {}
    SolarTemp(uint16_t panel1_temp, uint16_t panel2_temp, uint16_t panel3_temp,
              uint16_t panel4_temp)
        : panel1_temp(panel1_temp), panel2_temp(panel2_temp),
          panel3_temp(panel3_temp), panel4_temp(panel4_temp) {}

    SERIALIZATION_METHODS((panel1_temp, 16), (panel2_temp, 16),
                          (panel3_temp, 16), (panel4_temp, 16))

    uint32_t get_message_ID() { return SolarTemp_MESSAGE_ID; }

    void printStruct() { 
        PRINT("SolarTemp\n panel1_temp: %u\n panel2_temp: %u\n panel3_temp: %u\n panel4_temp: %u\n", panel1_temp, panel2_temp, panel3_temp, panel4_temp);
    }
} SolarTemp;

typedef struct SolarPhoto : CANStruct {
    uint16_t panel1_photo;
    uint16_t panel2_photo;
    uint16_t panel3_photo;
    uint16_t panel4_photo;

    SolarPhoto() {}
    SolarPhoto(uint16_t panel1_photo, uint16_t panel2_photo,
               uint16_t panel3_photo, uint16_t panel4_photo)
        : panel1_photo(panel1_photo), panel2_photo(panel2_photo),
          panel3_photo(panel3_photo), panel4_photo(panel4_photo) {}

    SERIALIZATION_METHODS((panel1_photo, 16), (panel2_photo, 16),
                          (panel3_photo, 16), (panel4_photo, 16))

    uint32_t get_message_ID() { return SolarPhoto_MESSAGE_ID; }
    void printStruct() { 
        PRINT("SolarPhoto\n panel1_photo: %u\n panel2_photo: %u\n panel3_photo: %u\n panel4_photo: %u\n", panel1_photo, panel2_photo, panel3_photo, panel4_photo);
    }    
} SolarPhoto;

#endif