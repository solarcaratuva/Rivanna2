#ifndef PINDEF_H
#define PINDEF_H

/***************************/
/* pin definitions for CAN */
/***************************/
#define CAN_RX      PA_11   // Rx for MCU
#define CAN_TX      PA_12
#define CAN_STBY    PA_10   // Digital Output
#define CAN2_RX     PB_12   // Rx for MCU
#define CAN2_TX     PB_13
#define CAN2_STBY   PB_9    // Digital Output

/***************************/
/* pin definitions for USB */
/***************************/
#define USB_RX  PB_7    // Rx for MCU
#define USB_TX  PB_6

/*************************************/
/* pin definitions for Analog Inputs */
/*************************************/
#define ANALOG_INPUT_1      PA_0

/***************************************/
/* pin definitions for Digital Inputs */
/***************************************/
#define DIGITAL_INPUT_1     PB_4

/***************************************/
/* pin definitions for Digital Outputs */
/***************************************/
#define DIGITAL_OUTPUT_1    PB_5

/**********************************/
/* pin definitions for Unused I/O */
/**********************************/
#define UNUSED_PIN_0    PA_2

#endif // PINDEF_H