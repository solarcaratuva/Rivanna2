#ifndef PINDEF_H
#define PINDEF_H

#ifdef TARGET_UVA_SOLAR_CAR

// CAN
#define MAIN_CAN_TX         PB_13
#define MAIN_CAN_RX         PB_12
#define MAIN_CAN_STBY       PB_9
#define BMS_CAN1_TX         PA_12
#define BMS_CAN1_RX         PA_11
#define BMS_CAN1_STBY       PA_10
#define BMS_CAN2_RX         PA_8
#define BMS_CAN2_TX         PB_4
#define BMS_CAN2_STBY       PB_5

// Error LEDs
#define BMS_ERROR_LED       PA_4
#define CAN_ERROR_LED       PA_3

// USB
#define USB_RX              PB_7
#define USB_TX              PB_6

// Inputs
#define DCDC_ON             PC_13
#define AUX_PLUS            PA_0
#define DCDC_PLUS           PA_1
#define FanTach             PA_2

// Outputs
#define LEFT_TURN_EN        PA_9
#define LEFT_TURN_CURRENT   PB_15
#define DRL_EN              PB_14
#define DRL_CURRENT         PB_11
#define HORN_EN             PA_5
#define BMS_STROBE_CURRENT  PA_6
#define BMS_STROBE_EN       PA_7
#define BRAKE_LIGHT_CURRENT PB_0
#define BRAKE_LIGHT_EN      PB_1
#define RIGHT_TURN_CURRENT  PB_2
#define RIGHT_TURN_EN       PB_10
#define JTDI                PA_15

#else

// CAN
#define MAIN_CAN_TX         NC
#define MAIN_CAN_RX         NC
#define MAIN_CAN_STBY       NC
#define BMS_CAN1_TX         NC
#define BMS_CAN1_RX         NC
#define BMS_CAN1_STBY       NC
#define BMS_CAN2_RX         NC
#define BMS_CAN2_TX         NC
#define BMS_CAN2_STBY       NC

// Error LEDs
#define BMS_ERROR_LED       NC
#define CAN_ERROR_LED       NC

// USB
#define USB_RX              NC
#define USB_TX              NC

// Inputs
#define DCDC_ON             NC
#define AUX_PLUS            NC
#define DCDC_PLUS           NC
#define FanTach             NC

// Outputs
#define LEFT_TURN_EN        NC
#define LEFT_TURN_CURRENT   NC
#define DRL_EN              NC
#define DRL_CURRENT         NC
#define HORN_EN             NC
#define BMS_STROBE_CURRENT  NC
#define BMS_STROBE_EN       NC
#define BRAKE_LIGHT_CURRENT NC
#define BRAKE_LIGHT_EN      NC
#define RIGHT_TURN_CURRENT  NC
#define RIGHT_TURN_EN       NC
#define JTDI                NC

#endif

#endif // PINDEF_H