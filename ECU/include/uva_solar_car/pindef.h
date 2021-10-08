#ifndef PINDEF_H
#define PINDEF_H

/***************************/
/* pin definitions for CAN */
/***************************/
#define CAN_RX      PA_11   // Rx for MCU
#define CAN_TX      PA_12
#define CAN_STBY    PB_10   // Digital Output

/*************************************/
/* pin definitions for Analog Inputs */
/*************************************/
#define THROTTLE      PB_13
#define REGEN         PB_14

/***************************************/
/* pin definitions for Digital Inputs */
/***************************************/
#define HAZARDS            PC_13
#define LEFT_TURN_SIG      PA_0
#define RIGHT_TURN_SIG     PA_1
#define HORN               PA_2
#define CRUISE_SPEED_DOWN  PA_3
#define CRUISE_SPEED_UP    PA_4
#define CRUISE_THROTTLE_EN PA_5
#define RUNNING_LIGHTS_EN  PA_6
#define BRAKE_PEDAL        PA_7
#define MOTOR_ON           PB_0
#define REVERSE_EN         PB_1
#define FORWARD_EN         PB_2
#define BATTERY_CONTACT    PB_11
#define IGNITION           PB_12


/**********************************/
/* pin definitions for Unused I/O */
/**********************************/
#define UNUSED_PIN_1    PA_9
#define UNUSED_PIN_2    PA_10
#define UNUSED_PIN_3    PA_8
#define UNUSED_PIN_4    PB_15
#define UNUSED_PIN_5    PB_9
#define UNUSED_PIN_6    PB_5
#define UNUSED_PIN_7    PB_4

#endif // PINDEF_H