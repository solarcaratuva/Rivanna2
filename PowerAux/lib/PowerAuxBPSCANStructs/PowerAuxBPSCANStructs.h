#ifndef POWER_AUX_BPS_CAN_STRUCTS_H
#define POWER_AUX_BPS_CAN_STRUCTS_H

#include "CANStruct.h"
#include "CANSerializer.h"

/**
 * General BPS information and errors.
 * NOTE: This struct has not been tested thoroughly, there may be transcription or padding errors.
 */
typedef struct PackInformation : public CANStruct
{
    /**
     * 0.1V/LSB
     */
    uint16_t pack_voltage;
    /**
     * 0.1A/LSB
     */
    uint16_t pack_current;
    /**
     * 0.5%/LSB
     */
    uint8_t pack_soc;

    bool internal_communications_fault;
    bool internal_conversion_fault;
    bool weak_cell_fault;
    bool low_cell_voltage_fault;
    bool open_wiring_fault;
    bool current_sensor_fault;
    bool pack_voltage_sensor_fault;
    bool weak_pack_fault;
    bool voltage_redundancy_fault;
    bool fan_monitor_fault;
    bool thermistor_fault;
    bool CANBUS_communications_fault;
    bool always_on_supply_fault;
    bool high_voltage_isolation_fault;
    bool power_supply_12v_fault;
    bool charge_limit_enforcement_fault;
    bool discharge_limit_enforcement_fault;
    bool charger_safety_relay_fault;
    bool internal_memory_fault;
    bool internal_thermistor_fault;
    bool internal_logic_fault;
    
    bool discharge_relay;
    bool charge_relay;

    PackInformation() {}

    SERIALIZATION_METHODS(
        (pack_voltage, 16),
        (pack_current, 16),
        (pack_soc, 8),
        (internal_communications_fault, 1),
        (internal_conversion_fault, 1),
        (weak_cell_fault, 1),
        (low_cell_voltage_fault, 1),
        (open_wiring_fault, 1),
        (current_sensor_fault, 1),
        (pack_voltage_sensor_fault, 1),
        (weak_pack_fault, 1),
        (voltage_redundancy_fault, 1),
        (fan_monitor_fault, 1),
        (thermistor_fault, 1),
        (CANBUS_communications_fault, 1),
        (always_on_supply_fault, 1),
        (high_voltage_isolation_fault, 1),
        (power_supply_12v_fault, 1),
        (charge_limit_enforcement_fault, 1),
        (discharge_limit_enforcement_fault, 1),
        (charger_safety_relay_fault, 1),
        (internal_memory_fault, 1),
        (internal_thermistor_fault, 1),
        (internal_logic_fault, 1),
        (discharge_relay, 1),
        (charge_relay, 1)
    );

    uint32_t get_message_ID()
    {
        return POWER_AUX_BPS_CAN_PackInformation;
    }

    bool has_error() {
        return internal_communications_fault  
            || internal_conversion_fault 
            || weak_cell_fault 
            || low_cell_voltage_fault 
            || open_wiring_fault 
            || current_sensor_fault 
            || pack_voltage_sensor_fault 
            || weak_pack_fault 
            || voltage_redundancy_fault 
            || fan_monitor_fault 
            || thermistor_fault 
            || CANBUS_communications_fault 
            || always_on_supply_fault 
            || high_voltage_isolation_fault 
            || power_supply_12v_fault 
            || charge_limit_enforcement_fault 
            || discharge_limit_enforcement_fault
            || charger_safety_relay_fault 
            || internal_memory_fault 
            || internal_thermistor_fault 
            || internal_logic_fault;
    }
} PackInformation;

/**
 * Extreme (low and high only) cell voltage data.
 * NOTE: This struct has not been tested thoroughly, there may be transcription or padding errors.
 */
typedef struct CellVoltage : public CANStruct
{
    /**
     * 0.0001V/LSB
     */
    uint16_t low_cell_voltage;
    /**
     * Id of the cell with the lowest voltage
     */
    uint8_t low_cell_voltage_id;
    /**
     * 0.0001V/LSB
     */
    uint16_t high_cell_voltage;
    /**
     * Id of the cell with the highest voltage
     */
    uint8_t high_cell_voltage_id;

    CellVoltage() {}

    SERIALIZATION_METHODS(
        (low_cell_voltage, 16),
        (low_cell_voltage_id, 8),
        (high_cell_voltage, 16),
        (high_cell_voltage_id, 8)
    );

    uint32_t get_message_ID()
    {
        return POWER_AUX_BPS_CAN_CellVoltage;
    }
} CellVoltage;

/**
 * Extreme (low and high only) cell temperature data.
 * NOTE: This struct has not been tested thoroughly, there may be transcription or padding errors.
 */
typedef struct CellTemperature : public CANStruct
{
    /**
     * 1°C/LSB
     */
    uint8_t low_temperature;
    /**
     * Id of the cell with the lowest temperature
     */
    uint8_t low_thermistor_id;
    /**
     * 1°C/LSB
     */
    uint8_t high_temperature;
    /**
     * Id of the cell with the highest temperature
     */
    uint8_t high_thermistor_id;

    CellTemperature() {}

    SERIALIZATION_METHODS(
        (low_temperature, 8),
        (low_thermistor_id, 8),
        (high_temperature, 8),
        (high_thermistor_id, 8)
    );

    uint32_t get_message_ID()
    {
        return POWER_AUX_BPS_CAN_CellTemperature;
    }
} CellTemperature;

#endif