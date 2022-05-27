#ifndef BPS_CAN_STRUCTS_H
#define BPS_CAN_STRUCTS_H

#include "CANStruct.h"
#include "dbc/structs/bps.h"
#include "log.h"

/**
 * General BPS information.
 * NOTE: This struct has not been tested thoroughly, there may be transcription
 * or padding errors.
 */
typedef struct BPSPackInformation : CANStruct, bps_bps_pack_information_t {
    void serialize(CANMessage *message) {
        bps_bps_pack_information_pack(message->data, this, BPS_BPS_PACK_INFORMATION_LENGTH);
        message->len = BPS_BPS_PACK_INFORMATION_LENGTH;
    }

    void deserialize(CANMessage *message) {
        bps_bps_pack_information_unpack(this, message->data, BPS_BPS_PACK_INFORMATION_LENGTH);
    }

    uint32_t get_message_ID() { return BPSPackInformation_MESSAGE_ID; }

    void log(int level) {
        log_at_level(
            level,
            "BPSPackInformation\n pack_voltage: %u\n pack_current:  %u\n "
            "pack_soc: %u\n"
            "discharge_relay: %d\n charge_relay: %d",
            pack_voltage, pack_current, pack_soc, discharge_relay,
            charge_relay);
    }
} BPSPackInformation;

/**
 * BPS errors.
 * NOTE: This struct has not been tested thoroughly, there may be transcription
 * or padding errors.
 */
typedef struct BPSError : CANStruct, bps_bps_error_t {
    void serialize(CANMessage *message) {
        bps_bps_error_pack(message->data, this, BPS_BPS_ERROR_LENGTH);
        message->len = BPS_BPS_ERROR_LENGTH;
    }

    void deserialize(CANMessage *message) {
        bps_bps_error_unpack(this, message->data, BPS_BPS_ERROR_LENGTH);
    }

    uint32_t get_message_ID() { return BPSError_MESSAGE_ID; }

    bool has_error() {
        return internal_communications_fault || internal_conversion_fault ||
               weak_cell_fault || low_cell_voltage_fault || open_wiring_fault ||
               current_sensor_fault || pack_voltage_sensor_fault ||
               weak_pack_fault || voltage_redundancy_fault ||
               fan_monitor_fault || thermistor_fault ||
               canbus_communications_fault || always_on_supply_fault ||
               high_voltage_isolation_fault || power_supply_12v_fault ||
               charge_limit_enforcement_fault ||
               discharge_limit_enforcement_fault ||
               charger_safety_relay_fault || internal_memory_fault ||
               internal_thermistor_fault || internal_logic_fault;
    }

    void log(int level) {
        log_at_level(
            level,
            "BPSError\n internal_communications_fault: %d\n "
            "internal_conversion_fault: %d\n weak_cell_fault: %d\n "
            "low_cell_voltage_fault: %d\n open_wiring_fault: %d\n "
            "current_sensor_fault: %d\n pack_voltage_sensor_fault: %d\n "
            "weak_pack_fault: %d\n voltage_redundancy_fault: %d\n "
            "fan_monitor_fault: %d\n thermistor_fault: %d\n "
            "canbus_communications_fault: %d\n always_on_supply_fault: %d\n "
            "high_voltage_isolation_fault: %d\n power_supply_12v_fault: %d\n "
            "charge_limit_enforcement_fault: %d\n "
            "discharge_limit_enforcement_fault:  %d\n "
            "charger_safety_relay_fault:  %d\n internal_memory_fault: %d\n "
            "internal_thermistor_fault: %d/n internal_logic_fault: %d",
            internal_communications_fault, internal_conversion_fault,
            weak_cell_fault, low_cell_voltage_fault, open_wiring_fault,
            current_sensor_fault, pack_voltage_sensor_fault, weak_pack_fault,
            voltage_redundancy_fault, fan_monitor_fault, thermistor_fault,
            canbus_communications_fault, always_on_supply_fault,
            high_voltage_isolation_fault, power_supply_12v_fault,
            charge_limit_enforcement_fault, discharge_limit_enforcement_fault,
            charger_safety_relay_fault, internal_memory_fault,
            internal_thermistor_fault, internal_logic_fault);
    }
} BPSError;

/**
 * Extreme (low and high only) cell voltage data.
 * NOTE: This struct has not been tested thoroughly, there may be transcription
 * or padding errors.
 */
typedef struct BPSCellVoltage : CANStruct, bps_bps_cell_voltage_t {
    void serialize(CANMessage *message) {
        bps_bps_cell_voltage_pack(message->data, this, BPS_BPS_CELL_VOLTAGE_LENGTH);
        message->len = BPS_BPS_CELL_VOLTAGE_LENGTH;
    }

    void deserialize(CANMessage *message) {
        bps_bps_cell_voltage_unpack(this, message->data, BPS_BPS_CELL_VOLTAGE_LENGTH);
    }

    uint32_t get_message_ID() { return BPSCellVoltage_MESSAGE_ID; }

    void log(int level) {
        log_at_level(
            level,
            "BPSCellVoltage\n low_cell_voltage: %u\n low_cell_voltage_id: %u\n "
            "high_cell_voltage: %u\n high_cell_voltage_id: %u",
            low_cell_voltage, low_cell_voltage_id, high_cell_voltage,
            high_cell_voltage_id);
    }
} BPSCellVoltage;

/**
 * Extreme (low and high only) cell temperature data.
 * NOTE: This struct has not been tested thoroughly, there may be transcription
 * or padding errors.
 */
typedef struct BPSCellTemperature : CANStruct, bps_bps_cell_temperature_t {
    void serialize(CANMessage *message) {
        bps_bps_cell_temperature_pack(message->data, this, BPS_BPS_CELL_TEMPERATURE_LENGTH);
        message->len = BPS_BPS_CELL_TEMPERATURE_LENGTH;
    }

    void deserialize(CANMessage *message) {
        bps_bps_cell_temperature_unpack(this, message->data, BPS_BPS_CELL_TEMPERATURE_LENGTH);
    }

    uint32_t get_message_ID() { return BPSCellTemperature_MESSAGE_ID; }

    void log(int level) {
        log_at_level(
            level,
            "BPSCellTemperature: \n low_temperature: %u\n low_thermistor_id: "
            "%u\n high_temperature: %u\n high_thermistor_id: %u\n",
            low_temperature, low_thermistor_id, high_temperature,
            high_thermistor_id);
    }
} BPSCellTemperature;

#endif