#ifndef PINDEF_H
#define PINDEF_H

#define DCDC_ON_ToSTM     PC_13
#define NRST              PG_10
#define AUX_PLUS_ToSTM    PA_0
#define DCDC_PLUS_ToSTM   PA_1
#define FanTach_ToSTM     PA_2
#define CAN_ERROR_LED     PA_3
#define BMS_ERROR_LED     PA_4

#define BMS_CAN1_TX       PA_12
#define BMS_CAN1_RX       PA_11
#define BMS_CAN1_STBY     PA_10
#define LEFT_TURN_EN      PA_9
#define BMS_CAN2_RX       PA_8
#define LEFT_TURN_CURRENT PB_15
#define DRL_EN            PB_14
#define MAIN_CAN_TX       PB_13
#define MAIN_CAN_RX       PB_12
#define DRL_CURRENT       PB_11

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