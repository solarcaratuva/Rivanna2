// Adapted from Mbed source

#ifndef MBED_CAN_HELPER_H
#define MBED_CAN_HELPER_H

#if DEVICE_CAN

#ifdef __cplusplus
extern "C" {
#endif

/**
 *
 * \enum    CANFormat
 *
 * \brief   Values that represent CAN Format
 **/
enum CANFormat { CANStandard = 0, CANExtended = 1, CANAny = 2 };
typedef enum CANFormat CANFormat;

/**
 *
 * \enum    CANType
 *
 * \brief   Values that represent CAN Type
 **/
enum CANType { CANData = 0, CANRemote = 1 };
typedef enum CANType CANType;

/**
 *
 * \struct  CAN_Message
 *
 * \brief   Holder for single CAN message.
 *
 **/
struct CAN_Message {
    unsigned int id;       // 29 bit identifier
    unsigned char data[8]; // Data field
    unsigned char len;     // Length of data field in bytes
    CANFormat format;      // Format ::CANFormat
    CANType type;          // Type ::CANType
};
typedef struct CAN_Message CAN_Message;

#ifdef __cplusplus
}
#endif

#endif

#endif // MBED_CAN_HELPER_H

/** @}*/
