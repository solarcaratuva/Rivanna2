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
        bps_bps_pack_information_pack(message->data, this,
                                      BPS_BPS_PACK_INFORMATION_LENGTH);
        message->len = BPS_BPS_PACK_INFORMATION_LENGTH;
    }

    void deserialize(CANMessage *message) {
        bps_bps_pack_information_unpack(this, message->data,
                                        BPS_BPS_PACK_INFORMATION_LENGTH);
    }

    uint32_t get_message_ID() { return BPSPackInformation_MESSAGE_ID; }

    void log(int level) {
        log_at_level(
            level,
            "BPSPackInformation: pack_voltage %u, pack_current %u, pack_soc "
            "%u, discharge_relay_status %u, charge_relay_status %u, "
            "charger_safety_status %u, dtc_status %u, "
            "multipurpose_input_signal_status %u, always_on_signal_status %u, "
            "is_ready_signal_status %u, is_charging_signal_status %u",
            pack_voltage, pack_current, pack_soc, discharge_relay_status,
            charge_relay_status, charger_safety_status, dtc_status,
            multipurpose_input_signal_status, always_on_signal_status,
            is_ready_signal_status, is_charging_signal_status);
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
            "BPSError: internal_communications_fault %u, "
            "internal_conversion_fault %u, weak_cell_fault %u, "
            "low_cell_voltage_fault %u, open_wiring_fault %u, "
            "current_sensor_fault %u, pack_voltage_sensor_fault %u, "
            "weak_pack_fault %u, voltage_redundancy_fault %u, "
            "fan_monitor_fault %u, thermistor_fault %u, "
            "CANBUS_communications_fault %u, always_on_supply_fault %u, "
            "high_voltage_isolation_fault %u, power_supply_12v_fault %u, "
            "charge_limit_enforcement_fault %u, "
            "discharge_limit_enforcement_fault %u, charger_safety_relay_fault "
            "%u, internal_memory_fault %u, internal_thermistor_fault %u, "
            "internal_logic_fault %u",
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
        bps_bps_cell_voltage_pack(message->data, this,
                                  BPS_BPS_CELL_VOLTAGE_LENGTH);
        message->len = BPS_BPS_CELL_VOLTAGE_LENGTH;
    }

    void deserialize(CANMessage *message) {
        bps_bps_cell_voltage_unpack(this, message->data,
                                    BPS_BPS_CELL_VOLTAGE_LENGTH);
    }

    uint32_t get_message_ID() { return BPSCellVoltage_MESSAGE_ID; }

    void log(int level) {
        log_at_level(level,
                     "BPSCellVoltage: low_cell_voltage %u, low_cell_voltage_id "
                     "%u, high_cell_voltage %u, high_cell_voltage_id %u",
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
        bps_bps_cell_temperature_pack(message->data, this,
                                      BPS_BPS_CELL_TEMPERATURE_LENGTH);
        message->len = BPS_BPS_CELL_TEMPERATURE_LENGTH;
    }

    void deserialize(CANMessage *message) {
        bps_bps_cell_temperature_unpack(this, message->data,
                                        BPS_BPS_CELL_TEMPERATURE_LENGTH);
    }

    uint32_t get_message_ID() { return BPSCellTemperature_MESSAGE_ID; }

    void log(int level) {
        log_at_level(
            level,
            "BPSCellTemperature: low_temperature %u, low_thermistor_id %u, "
            "high_temperature %u, high_thermistor_id %u",
            low_temperature, low_thermistor_id, high_temperature,
            high_thermistor_id);
    }
} BPSCellTemperature;

#endif