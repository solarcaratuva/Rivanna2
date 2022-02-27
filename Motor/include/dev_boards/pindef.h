#ifndef PINDEF_H
#define PINDEF_H

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

#endif // PINDEF_H