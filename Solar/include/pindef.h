#ifndef PINDEF_H
#define PINDEF_H

#ifdef TARGET_UVA_SOLAR_CAR

/***************************/
/* pin definitions for CAN */
/***************************/
#define CAN_RX    PA_11 // Rx for MCU
#define CAN_TX    PA_12
#define CAN_STBY  PB_10 // Digital Output

/***************************/
/* pin definitions for USB */
/***************************/
#define USB_RX    PB_7 // Rx for MCU
#define USB_TX    PB_6

/**********************************/
/* pin definitions for Unused I/O */
/**********************************/
#define Pullup_1  PA_10
#define Pullup_2  PA_9
#define Pullup_3  PA_8
#define Pullup_4  PB_11
#define Pullup_5  PB_2
#define Pullup_6  PB_1
#define Pullup_7  PA_4
#define Pullup_8  PA_3
#define Pullup_9  PA_2
#define Pullup_10 PA_1
#define Pullup_11 PA_0
#define Pullup_12 PC_13
#define Pullup_13 PB_9
#define Pullup_14 PB_5
#define Pullup_15 PB_4

// External ADC pins
#define ADC2_MOSI PB_15
#define ADC2_MISO PB_14
#define ADC2_CLK  PB_13
#define ADC2_CS   PB_12

#define ADC1_CLK  PA_5
#define ADC1_MISO PA_6
#define ADC1_MOSI PA_7
#define ADC1_CS   PB_0

#else

/***************************/
/* pin definitions for CAN */
/***************************/
#define CAN_RX    NC // Rx for MCU
#define CAN_TX    NC
#define CAN_STBY  NC // Digital Output

/***************************/
/* pin definitions for USB */
/***************************/
#define USB_RX    NC // Rx for MCU
#define USB_TX    NC

/**********************************/
/* pin definitions for Unused I/O */
/**********************************/
#define Pullup_1  NC
#define Pullup_2  NC
#define Pullup_3  NC
#define Pullup_4  NC
#define Pullup_5  NC
#define Pullup_6  NC
#define Pullup_7  NC
#define Pullup_8  NC
#define Pullup_9  NC
#define Pullup_10 NC
#define Pullup_11 NC
#define Pullup_12 NC
#define Pullup_13 NC
#define Pullup_14 NC
#define Pullup_15 NC

// External ADC pins
#define ADC2_MOSI NC
#define ADC2_MISO NC
#define ADC2_CLK  NC
#define ADC2_CS   NC

#define ADC1_CLK  NC
#define ADC1_MISO NC
#define ADC1_MOSI NC
#define ADC1_CS   NC

#endif

#endif // PINDEF_H
