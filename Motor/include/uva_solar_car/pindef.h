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

/**********************************/
/* pin definitions for Direction Acceleration */
/**********************************/
#define DIR_ACCEL   PC13

// pin definition for NRST
#define NRST    PG10-NRST

// pin definition for MAIN_SWITCH
#define MAIN_SWITCH PA2

// pin definition for PWR_ECO
#define PWR_ECO PA3

// pin definition for FWD_REV
#define FWD_REV PA4

// pin definition for VDD
#define VDD    VDD_3

// pin definition for SDA_ACCEL
#define SDA_ACCEL   PB9

// pin definition for SWD
#define SWD    PB3

// pin definiiton SCL_ACCEL
#define SCL_ACCEL   PA15

// pin definition SWCLK
#define SWCLK   PA14

// pin defintion SWD10
#define SWD10   PA13

// pin definition for EXTRA_4
#define EXTRA_4    PB5

// pin definition for EXTRA_3
#define EXTRA_3    PB4

// pin definition for SWD
#define SWD    PB3

// pin definiiton SCL_ACCEL
#define SCL_ACCEL   PA15

// pin definition SWCLK
#define SWCLK   PA14

// pin defintion SWD10
#define SWD10   PA13

#endif // PINDEF_H