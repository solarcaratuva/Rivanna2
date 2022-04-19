#ifndef CAN_STRUCT_MESSAGE_IDS_H
#define CAN_STRUCT_MESSAGE_IDS_H

// This file defines the message IDs used be each CANStruct. IDs used in the
// same CAN bus cannot conflict.

// CAN message ID (11 bits): Node ID stored in bottom 3 bits (bits 0-2),
//                           Priority stored in upper 8 bits (bits 3-10)
#define CAN_MESSAGE_ID(NODE_ID, PRIORITY)                                      \
    ((NODE_ID & 0x07) | ((PRIORITY & 0xFF) << 3))
#define CAN_NODE_ID(CAN_MESSAGE_ID)              (CAN_MESSAGE_ID & 0x07)
#define CAN_PRIORITY(CAN_MESSAGE_ID)             ((CAN_MESSAGE_ID >> 7) & 0xFF)

// Main CAN bus message IDs

#define ECUMotorCommands_MESSAGE_ID              CAN_MESSAGE_ID(1, 1)
#define ECUPowerAuxCommands_MESSAGE_ID           CAN_MESSAGE_ID(1, 2)

#define PowerAuxError_MESSAGE_ID                               CAN_MESSAGE_ID(3, 3)

#define SolarCurrent_MESSAGE_ID                  CAN_MESSAGE_ID(4, 4)
#define SolarVoltage_MESSAGE_ID                  CAN_MESSAGE_ID(4, 5)
#define SolarTemp_MESSAGE_ID                     CAN_MESSAGE_ID(4, 6)
#define SolarPhoto_MESSAGE_ID                    CAN_MESSAGE_ID(4, 7)

// IDs to use the Motor IDs for sending to main bus
#define MotorControllerPowerStatus_MESSAGE_ID                  CAN_MESSAGE_ID(5, 1)
#define MotorControllerDriveStatus_MESSAGE_ID                  CAN_MESSAGE_ID(5, 2)
#define MotorControllerError_MESSAGE_ID                        CAN_MESSAGE_ID(5, 3)

//// IDs to use the PowerAux IDs for sending to main bus
#define BPSPackInformation_Message_ID                          CAN_MESSAGE_ID(6, 1)
#define BPSCellVoltage_Message_ID                              CAN_MESSAGE_ID(6, 2)
#define BPSCellTemperature_Message_ID                          CAN_MESSAGE_ID(6, 3)

// Motor Controller CAN bus message IDs
// These IDs use the CAN extended format

#define MOTOR_CONTROLLER_FrameRequest_MESSAGE_ID 0x08F89540
#define MOTOR_CONTROLLER_MotorControllerPowerStatus_MESSAGE_ID 0x08850225
#define MOTOR_CONTROLLER_MotorControllerDriveStatus_MESSAGE_ID 0x08950225
#define MOTOR_CONTROLLER_MotorControllerError_MESSAGE_ID       0x08A50225

// PowerAux BPS CAN bus message IDs

#define POWER_AUX_BPS_CAN_BPSPackInformation                   0x03
#define POWER_AUX_BPS_CAN_BPSCellVoltage                       0x0B
#define POWER_AUX_BPS_CAN_BPSCellTemperature                   0x13

#endif
