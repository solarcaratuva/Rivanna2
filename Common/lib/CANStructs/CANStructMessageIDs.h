#ifndef CAN_STRUCT_MESSAGE_IDS_H
#define CAN_STRUCT_MESSAGE_IDS_H

#include "dbc/structs/bps.h"
#include "dbc/structs/motor_controller.h"
#include "dbc/structs/rivanna2.h"

#define ECUMotorCommands_MESSAGE_ID    RIVANNA2_ECU_MOTOR_COMMANDS_FRAME_ID
#define ECUPowerAuxCommands_MESSAGE_ID RIVANNA2_ECU_POWER_AUX_COMMANDS_FRAME_ID
#define PowerAuxError_MESSAGE_ID       RIVANNA2_POWER_AUX_ERROR_FRAME_ID
#define SolarCurrent_MESSAGE_ID        RIVANNA2_SOLAR_CURRENT_FRAME_ID
#define SolarVoltage_MESSAGE_ID        RIVANNA2_SOLAR_VOLTAGE_FRAME_ID
#define SolarTemp_MESSAGE_ID           RIVANNA2_SOLAR_TEMP_FRAME_ID
#define SolarPhoto_MESSAGE_ID          RIVANNA2_SOLAR_PHOTO_FRAME_ID
#define MotorControllerPowerStatus_MESSAGE_ID                                  \
    MOTOR_CONTROLLER_MOTOR_CONTROLLER_POWER_STATUS_FRAME_ID
#define MotorControllerDriveStatus_MESSAGE_ID                                  \
    MOTOR_CONTROLLER_MOTOR_CONTROLLER_DRIVE_STATUS_FRAME_ID
#define MotorControllerError_MESSAGE_ID                                        \
    MOTOR_CONTROLLER_MOTOR_CONTROLLER_ERROR_FRAME_ID
#define BPSPackInformation_MESSAGE_ID                  BPS_BPS_PACK_INFORMATION_FRAME_ID
#define BPSError_MESSAGE_ID                            BPS_BPS_ERROR_FRAME_ID
#define BPSCellVoltage_MESSAGE_ID                      BPS_BPS_CELL_VOLTAGE_FRAME_ID
#define BPSCellTemperature_MESSAGE_ID                  BPS_BPS_CELL_TEMPERATURE_FRAME_ID

// Motor Controller message IDs
// These cannot be user-configured and are on a CAN extended bus, so they are
// different to the IDs used for these messages on the main bus

#define MotorControllerFrameRequest_AUX_BUS_MESSAGE_ID 0x08F89540
#define MotorControllerPowerStatus_AUX_BUS_MESSAGE_ID  0x08850225
#define MotorControllerDriveStatus_AUX_BUS_MESSAGE_ID  0x08950225
#define MotorControllerError_AUX_BUS_MESSAGE_ID        0x08A50225

#endif
