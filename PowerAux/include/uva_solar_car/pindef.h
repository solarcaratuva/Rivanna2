#ifndef PINDEF_H
#define PINDEF_H

/***************************/
/* pin definitions for CAN */
/***************************/
#define CAN_RX      PA_11   // Rx for MCU
#define CAN_TX      PA_12
#define CAN_STBY    PA_10   // Digital Output

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


//Bottom
#define HORN_EN               PA_5
#define BMS_STROBE_CURRENT    PA_6
#define BMS_STROBE_EN         PA_7
#define BRAKE_LIGHT_CURRENT   PB_0
#define BRAKE_LIGHT_EN        PB_1
#define RIGHT_TURN_CURRENT    PB_2
#define RIGHT_TURN_EN         PB_10

//Top
#define VDD                   VDD_3
#define MAIN_CAN_STBY         PB_9
#define USB_RX                PB_7
#define USB_TX                PB_6
#define BMS_CAN2_STBY         PB_5
#define BMS_CAN2_TX           PB_4
#define SWO                   PB_3
#define JTDI                  PA_15
#define SWCLK                 PA_14
#define SWDIO                 PA_13

#endif // PINDEF_H