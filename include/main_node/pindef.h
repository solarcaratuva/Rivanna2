#ifndef PINDEF_H
#define PINDEF_H

/***************************/
/* pin definitions for CAN */
/***************************/
#define INT_CAN_RX      PA_11   // Rx for MCU
#define INT_CAN_TX      PA_12
#define INT_CAN_STBY    PA_10   // Digital Output
#define EXT_CAN_RX      PB_12   // Rx for MCU
#define EXT_CAN_TX      PB_13
#define EXT_CAN_STBY    PB_11   // Digital Output

/***************************/
/* pin definitions for USB */
/***************************/
#define USB_RX  PB_7    // Rx for MCU
#define USB_TX  PB_6

/*************************************/
/* pin definitions for Analog Inputs */
/*************************************/
#define PACK_VOLTAGE    PA_0
#define PACK_CURRENT    PA_1

/***************************************/
/* pin definitions for Digital Outputs */
/***************************************/
#define FAN_CTRL                    PB_4
#define FAN_PWM                     PB_5
#define CHARGE_CONTACTOR_CTRL       PB_9
#define DISCHARGE_CONTACTOR_CTRL    PB_10

/**********************************/
/* pin definitions for Unused I/O */
/**********************************/
#define UNUSED_PIN_0    PA_2
#define UNUSED_PIN_1    PA_3
#define UNUSED_PIN_2    PA_5
#define UNUSED_PIN_3    PA_6
#define UNUSED_PIN_4    PA_7
#define UNUSED_PIN_5    PB_0
#define UNUSED_PIN_6    PB_1
#define UNUSED_PIN_7    PB_2
#define UNUSED_PIN_8    PB_14
#define UNUSED_PIN_9    PB_15
#define UNUSED_PIN_10   PA_8
#define UNUSED_PIN_11   PA_9
#define UNUSED_PIN_12   PA_4
#define UNUSED_PIN_13   PC_13

#endif // PINDEF_H