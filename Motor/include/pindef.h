#ifndef PINDEF_H
#define PINDEF_H

#ifdef TARGET_UVA_SOLAR_CAR

/***************************/
/* pin definitions for CAN */
/***************************/
#define MAIN_CAN_RX       PB_12
#define MAIN_CAN_TX       PB_13

#define MTR_CTRL_CAN_RX   PA_11
#define MTR_CTRL_CAN_TX   PA_12
#define MTR_CTRL_CAN_STBY PA_10

/***************************/
/* pin definitions for USB */
/***************************/
#define USB_RX            PB_7 // Rx for MCU
#define USB_TX            PB_6

/***************************************/
/* pin definitions for Trottle */
/***************************************/
#define SCL_ACCEL         PA_15
#define SDA_ACCEL         PB_9
#define DIR_ACCEL         PC_13

/***************************************/
/* pin definitions for Regen */
/***************************************/
#define SCL_REGEN         PA_9
#define SDA_REGEN         PA_8
#define DIR_REGEN         PB_15

/***************************************/
/* pin definitions for Switching Logic */
/***************************************/
#define MAIN_SWITCH       PA_2
#define PWR_ECO_ON        PA_3
#define FWD_REV_EN        PA_4

/**********************************/
/* pin definitions for Unused I/O */
/**********************************/
#define PULLUP_2          PB_14
#define PULLUP_3          PB_11
#define PULLUP_6          PB_10
#define PULLUP_7          PA_1
#define PULLUP_8          PA_0
#define PULLUP_9          PB_2
#define PULLUP_10         PB_1
#define PULLUP_11         PB_0
#define PULLUP_12         PA_7

#else

/***************************/
/* pin definitions for CAN */
/***************************/
#define MAIN_CAN_RX       NC
#define MAIN_CAN_TX       NC

#define MTR_CTRL_CAN_RX   NC
#define MTR_CTRL_CAN_TX   NC
#define MTR_CTRL_CAN_STBY NC

/***************************/
/* pin definitions for USB */
/***************************/
#define USB_RX            NC // Rx for MCU
#define USB_TX            NC

/***************************************/
/* pin definitions for Trottle */
/***************************************/
#define SCL_ACCEL         NC
#define SDA_ACCEL         NC
#define DIR_ACCEL         NC

/***************************************/
/* pin definitions for Regen */
/***************************************/
#define SCL_REGEN         NC
#define SDA_REGEN         NC
#define DIR_REGEN         NC

/***************************************/
/* pin definitions for Switching Logic */
/***************************************/
#define MAIN_SWITCH       NC
#define PWR_ECO_ON        NC
#define FWD_REV_EN        NC

/**********************************/
/* pin definitions for Unused I/O */
/**********************************/
#define PULLUP_2          NC
#define PULLUP_3          NC
#define PULLUP_6          NC
#define PULLUP_7          NC
#define PULLUP_8          NC
#define PULLUP_9          NC
#define PULLUP_10         NC
#define PULLUP_11         NC
#define PULLUP_12         NC

#endif

#endif // PINDEF_H