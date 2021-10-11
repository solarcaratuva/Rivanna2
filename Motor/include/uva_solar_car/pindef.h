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

// pin definition for acceleration direction
#define DIR_ACCEL   PC_13

// pin definition for MAIN_SWITCH
#define MAIN_SWITCH PA_2

// pin definition for PWR_ECO
#define PWR_ECO PA_3

// pin definition for FWD_REV
#define FWD_REV PA_4

// pin definition for SDA_ACCEL
#define SDA_ACCEL   PB_9

// pin definition for SWD
#define SWO    PB_3

// pin definiiton SCL_ACCEL
#define SCL_ACCEL   PA_15

// pin definition SWCLK
#define SWCLK   PA_14

// pin defintion SWD10
#define SWDIO   PA_13

// pin definition for EXTRA_4
#define EXTRA_4    PB_5

// pin definition for EXTRA_3
#define EXTRA_3    PB_4

// pin definiiton SCL_ACCEL
#define SCL_ACCEL   PA_15

#endif // PINDEF_H