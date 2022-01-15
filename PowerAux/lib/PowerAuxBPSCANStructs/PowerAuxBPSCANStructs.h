#ifndef POWER_AUX_BPS_CAN_STRUCTS_H
#define POWER_AUX_BPS_CAN_STRUCTS_H

#include "CANStruct.h"
#include "CANSerializer.h"

/**
 * General BPS information and errors.
 */
typedef struct PackInformation : public CANStruct
{
    uint16_t pack_voltage;
    uint16_t pack_current;
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
        (internal_logic_fault, 1)
    );

    uint32_t get_message_ID()
    {
        return POWER_AUX_BPS_CAN_PackInformation;
    }
} PackInformation;

/**
 * Extreme (low and high only) cell voltage data.
 */
typedef struct CellVoltage : public CANStruct
{
    uint16_t low_cell_voltage;
    uint8_t low_cell_voltage_id;
    uint16_t high_cell_voltage;
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
 */
typedef struct CellTemperature : public CANStruct
{
    uint8_t low_temperature;
    uint8_t low_thermistor_id;
    uint8_t high_temperature;
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