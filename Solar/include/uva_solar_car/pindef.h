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
//counting pullups as unused pins
#define Pullup_1        PA_10
#define Pullup_2        PA_9
#define Pullup_3        PA_8
#define Pullup_4        PB_11
#define Pullup_5        PB_2
#define Pullup_6        PB_1
#define Pullup_7 PA_4
#define Pullup_8 PA_3
#define Pullup_9 PA_2
#define Pullup_10 PA_1
#define Pullup_11 PA_0
#define Pullup_12   PC_13
#define Pullup_13 PB_9
#define Pullup_14 PB_5
#define Pullup_15 PB_4

//VDD is not defined
  //VBAT Port
  //VDD_3 Port
//VSS is not defined

/**********************************/
/* pin definitions for Unused I/O */
/**********************************/
#define SWCLK PA_14
#define LSE_CLK PC_14-OSC32_IN
#define HSE_CLK PF0-OSC_IN


#define BOOT0 PB_8-BOOT0
#define SWO PB_3
#define JTDI PA_15
#define SWDIO PA_13
#define NRST  PG_10-NRST







#define ADC2_MOSI       PB_15
#define ADC2_MISO       PB_14
#define ADC2_CLK        PB_13
#define ADC2_CS         PB_12


#define ADC1_CLK        PA_5
#define ADC1_MISO       PA_6
#define ADC1_MOSI       PA_7
#define ADC1_CS         PB_0

#define VSSA            VSSA
#define VREF            VREF+
#define VDDA            VDDA



#endif // PINDEF_H
