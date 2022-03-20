#ifndef POWER_AUX_BPS_CAN_STRUCTS_H
#define POWER_AUX_BPS_CAN_STRUCTS_H

#include "CANStruct.h"
#include "Printing.h"
#include "bitproto/structs/bps_bp.h"

/**
 * General BPS information and errors.
 * NOTE: This struct has not been tested thoroughly, there may be transcription
 * or padding errors.
 */
typedef struct PackInformation : CANStruct, BitprotoPackInformation {
    void serialize(CANMessage *message) {
        EncodeBitprotoPackInformation(this, message->data);
    }

    void deserialize(CANMessage *message) {
        DecodeBitprotoPackInformation(this, message->data);
    }

    uint32_t get_message_ID() { return PackInformation_Message_ID; }

    bool has_error() {
        return internal_communications_fault || internal_conversion_fault ||
               weak_cell_fault || low_cell_voltage_fault || open_wiring_fault ||
               current_sensor_fault || pack_voltage_sensor_fault ||
               weak_pack_fault || voltage_redundancy_fault ||
               fan_monitor_fault || thermistor_fault ||
               CANBUS_communications_fault || always_on_supply_fault ||
               high_voltage_isolation_fault || power_supply_12v_fault ||
               charge_limit_enforcement_fault ||
               discharge_limit_enforcement_fault ||
               charger_safety_relay_fault || internal_memory_fault ||
               internal_thermistor_fault || internal_logic_fault;
    }

    void print() {
        PRINT("PackInformation\n pack_voltage: %u\n pack_current:  %u\n "
              "pack_sock: %u\n internal_communications_fault: %d\n "
              "internal_conversion_fault: %d\n weak_cell_fault: %d\n "
              "low_cell_voltage_fault: %d\n open_wiring_fault: %d\n "
              "current_sensor_fault: %d\n pack_voltage_sensor_fault: %d\n "
              "weak_pack_fault: %d\n voltage_redundancy_fault: %d\n "
              "fan_monitor_fault: %d\n thermistor_fault: %d\n "
              "CANBUS_communications_fault: %d\n always_on_supply_fault: %d\n "
              "high_voltage_isolation_fault: %d\n power_supply_12v_fault: %d\n "
              "charge_limit_enforcement_fault: %d\n "
              "discharge_limit_enforcement_fault:  %d\n "
              "charger_safety_relay_fault:  %d\n internal_memory_fault: %d\n "
              "internal_thermistor_fault: %d/n internal_logic_fault: %d\n "
              "discharge_relay: %d\n charge_relay: %d\n",
              pack_voltage, pack_current, pack_soc,
              internal_communications_fault, internal_conversion_fault,
              weak_cell_fault, low_cell_voltage_fault, open_wiring_fault,
              current_sensor_fault, pack_voltage_sensor_fault, weak_pack_fault,
              voltage_redundancy_fault, fan_monitor_fault, thermistor_fault,
              CANBUS_communications_fault, always_on_supply_fault,
              high_voltage_isolation_fault, power_supply_12v_fault,
              charge_limit_enforcement_fault, discharge_limit_enforcement_fault,
              charger_safety_relay_fault, internal_memory_fault,
              internal_thermistor_fault, internal_logic_fault, discharge_relay,
              charge_relay);
    }
} PackInformation;

/**
 * Extreme (low and high only) cell voltage data.
 * NOTE: This struct has not been tested thoroughly, there may be transcription
 * or padding errors.
 */
typedef struct CellVoltage : CANStruct, BitprotoCellVoltage {
    void serialize(CANMessage *message) {
        EncodeBitprotoCellVoltage(this, message->data);
    }

    void deserialize(CANMessage *message) {
        DecodeBitprotoCellVoltage(this, message->data);
    }

    uint32_t get_message_ID() { return CellVoltage_Message_ID; }

    void print() {
        PRINT("CellVoltage\n low_cell_voltage: %u\n low_cell_voltage_id: %u\n "
              "high_cell_voltage: %u\n high_cell_voltage_id: %u\n",
              low_cell_voltage, low_cell_voltage_id, high_cell_voltage,
              high_cell_voltage_id);
    }
} CellVoltage;

/**
 * Extreme (low and high only) cell temperature data.
 * NOTE: This struct has not been tested thoroughly, there may be transcription
 * or padding errors.
 */
typedef struct CellTemperature : CANStruct, BitprotoCellTemperature {
    void serialize(CANMessage *message) {
        EncodeBitprotoCellTemperature(this, message->data);
    }

    void deserialize(CANMessage *message) {
        DecodeBitprotoCellTemperature(this, message->data);
    }

    uint32_t get_message_ID() { return CellTemperature_Message_ID; }

    void print() {
        PRINT("CellTemperature: \n low_temperature: %u\n low_thermistor_id: "
              "%u\n high_temperature: %u\n high_thermistor_id: %u\n",
              low_temperature, low_thermistor_id, high_temperature,
              high_thermistor_id);
    }
} CellTemperature;

#endif