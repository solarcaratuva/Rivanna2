#ifndef CAN_STRUCT_MESSAGE_IDS_H
#define CAN_STRUCT_MESSAGE_IDS_H

#include "bitproto/structs/id_bp.h"

// Motor Controller message IDs
// These cannot be user-configured and are on a CAN extended bus, so they are
// different to the IDs used for these messages on the main bus

#define MotorControllerFrameRequest_AUX_BUS_MESSAGE_ID          0x08F89540
#define MotorControllerPowerStatus_AUX_BUS_MESSAGE_ID           0x08850225
#define MotorControllerDriveStatus_AUX_BUS_MESSAGE_ID           0x08950225
#define MotorControllerError_AUX_BUS_MESSAGE_ID                 0x08A50225

#endif
