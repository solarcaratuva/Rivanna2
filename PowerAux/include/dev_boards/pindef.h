#ifndef PINDEF_H
#define PINDEF_H

/***************************/
/* pin definitions for CAN */
/***************************/
#define CAN_RX      PD_0    // Rx for MCU
#define CAN_TX      PD_1
#define CAN_STBY    PG_1    // Digital Output
#define CAN2_RX     PB_5    // Rx for MCU
#define CAN2_TX     PB_6
#define CAN2_STBY   PD_7    // Digital Output

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