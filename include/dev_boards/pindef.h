#ifndef PINDEF_H
#define PINDEF_H

/***************************/
/* pin definitions for CAN */
/***************************/
#define INT_CAN_RX      PD_0   // Rx for MCU
#define INT_CAN_TX      PD_1
#define INT_CAN_STBY    PA_10   // Digital Output
#define EXT_CAN_RX      PB_5   // Rx for MCU
#define EXT_CAN_TX      PB_6
#define EXT_CAN_STBY    PB_11   // Digital Output

#define PACK_VOLTAGE    PA_0
#define PACK_CURRENT    PA_1

#define FAN_CTRL                    PB_4
#define FAN_PWM                     PB_5
#define CHARGE_CONTACTOR_CTRL       PB_9
#define DISCHARGE_CONTACTOR_CTRL    PB_10
#define UNUSED_PIN_0    PA_2
#endif // PINDEF_H