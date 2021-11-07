#ifndef PINDEF_H
#define PINDEF_H

/***************************/
/* pin definitions for CAN */
/***************************/
#define CAN_RX      PA_11   // Rx for MCU
#define CAN_TX      PA_12
#define CAN_STBY    PA_10   // Digital Output
#define MTR_CTL_MCU_CAN_TX PA_12
#define MTR_CTL_MCU_CAN_RX PA_11
#define MTR_CTL_MCU_CAN_STBY PA_10

/***************************/
/* pin definitions for USB */
/***************************/
#define USB_RX  PB_7    // Rx for MCU
#define USB_TX  PB_6

/***************************************/
/* pin definitions for Trottle */
/***************************************/
#define SCL_ACCEL PA_15
#define SDA_ACCEL PB_9
#define DIR_ACCEL PC_13


/***************************************/
/* pin definitions for Regen */
/***************************************/
#define SCL_REGEN PA_9
#define SDA_REGEN PA_8
#define DIR_REGEN PB_15

/***************************************/
/* pin definitions for Switching Logic */
/***************************************/
#define MAIN_SWITCH PA_2
#define PWR_ECO_ON PA_3
#define FWD_REV_EN PA_4

/**********************************/
/* pin definitions for Unused I/O */
/**********************************/
#define PULLUP_2 PB_14
#define PULLUP_3 PB_11
#define PULLUP_6 PB_10
#define PULLUP_7 PA_1
#define PULLUP_8 PA_0
#define PULLUP_9 PB_2
#define PULLUP_10 PB_1
#define PULLUP_11 PB_0
#define PULLUP_12 PA_7

#endif // PINDEF_H