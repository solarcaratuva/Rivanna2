#ifndef PINDEF_H
#define PINDEF_H

/***************************/
/* pin definitions for CAN */
/***************************/
#define CAN_RX      NC   // Rx for MCU
#define CAN_TX      NC
#define CAN_STBY    NC   // Digital Output

/***************************/
/* pin definitions for USB */
/***************************/
#define USB_RX  NC    // Rx for MCU
#define USB_TX  NC

/**********************************/
/* pin definitions for Unused I/O */
/**********************************/
#define Pullup_1        NC
#define Pullup_2        NC
#define Pullup_3        NC
#define Pullup_4        NC
#define Pullup_5        NC
#define Pullup_6        NC
#define Pullup_7        NC
#define Pullup_8        NC
#define Pullup_9        NC
#define Pullup_10       NC
#define Pullup_11       NC
#define Pullup_12       NC
#define Pullup_13       NC
#define Pullup_14       NC
#define Pullup_15       NC

// External ADC pins
#define ADC2_MOSI       NC
#define ADC2_MISO       NC
#define ADC2_CLK        NC
#define ADC2_CS         NC

#define ADC1_CLK        NC
#define ADC1_MISO       NC
#define ADC1_MOSI       NC
#define ADC1_CS         NC

#endif // PINDEF_H
