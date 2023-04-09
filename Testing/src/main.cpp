#include "DigitalOut.h"
#include "log.h"
#include <mbed.h>
#include <rtos.h>
#include <stdio.h>

// DigitalOut brake_lights(BRAKE_LIGHT_EN);

// AnalogIn fan_tach(FanTach);

/*

Command Documentation for Testing:

digital/analog in/out pin_number
d/a i/o pin_number

*/

const PinName SPI_CS = D0;
const PinName SPI_MOSI = D0;
const PinName SPI_MISO = D0;
const PinName SPI_SCK = D0;
const PinName SPI_RESET = D0;
const PinName SPI_RDY = D0;

mbed::SPI spi(SPI_MOSI, SPI_MISO, SPI_SCK); // mosi, miso, sclk
DigitalOut cs(SPI_CS);
DigitalOut rdy(SPI_RDY);

// Define AD4696 configuration parameters
const uint8_t OSR = 0x03;    // Oversampling ratio = 64
const uint8_t PGA = 0x00;    // Gain = 1
const uint8_t BW = 0x00;     // Bandwidth = 2.4576 MHz

// Based on DriverBoard/DriverBoard.kicad_sch
enum ADCMasks {
    MotorEn               = 1 << 0,
    CruiseControlNeutral  = 1 << 1,
    CruiseControlPositive = 1 << 2,
    CruiseControlNegative = 1 << 3,
    DriverKillSwitch      = 1 << 4,
    RadioToggle           = 1 << 5,
    BrakeLightCurrent     = 1 << 6,
    BMSStrobeCurrent      = 1 << 7,
    LeftTurnCurrent       = 1 << 8,
    RightTurnCurrent      = 1 << 9,
    DRLCurrent            = 1 << 10,
};

int initializeADC() {
    // Sends SPI commands

    return 0;
}

int readADC() {

    return 0;
}

enum ButtonMasks {
    THROTTLE = 1 << 0,
    BRAKE_PEDAL = 1 << 1,
    REGEN_PEDAL = 1 << 2,
    LEFT_TURN_SIGNAL = 1 << 3,
    RIGHT_TURN_SIGNAL = 1 << 4,
    RUNNING_LIGHTS = 1 << 5,
    HORN = 1 << 6,
    HAZARDS = 1 << 7,
    REVERSE = 1 << 8,
    FORWARD = 1 << 9,
    REGEN_ENABLED = 1 << 10,
    IGNITION = 1 << 11,
    DRL = 1 << 12,
    BRAKE_LIGHT = 1 << 13,
    BMS_STROBE = 1 << 14
};

int handle_button_state(int buttonState) {
    if (buttonState & THROTTLE) {
        // handle throttle
    }
    if (buttonState & BRAKE_PEDAL) {
        // handle brake pedal
    }
    if (buttonState & REGEN_PEDAL) {
        // handle regen pedal
    }
    if (buttonState & LEFT_TURN_SIGNAL) {
        // handle left turn signal
    }
    if (buttonState & RIGHT_TURN_SIGNAL) {
        // handle right turn signal
    }
    if (buttonState & RUNNING_LIGHTS) {
        // handle running lights
    }
    if (buttonState & HORN) {
        // handle horn
    }
    if (buttonState & HAZARDS) {
        // handle hazards
    }
    if (buttonState & REVERSE) {
        // handle reverse
    }
    if (buttonState & FORWARD) {
        // handle forward
    }
    if (buttonState & REGEN_ENABLED) {
        // handle regen enabled
    }
    if (buttonState & IGNITION) {
        // handle ignition
    }
    if (buttonState & DRL) {
        // handle DRL
    }
    if (buttonState & BRAKE_LIGHT) {
        // handle brake light
    }
    if (buttonState & BMS_STROBE) {
        // handle BMS strobe
    }
    
    return 0;
}

int main() {
    // Configure SPI parameters
    spi.format(16, 3);       // 16-bit data, mode 3
    spi.frequency(1000000);  // 1 MHz clock speed

    // Initialize AD4696
    cs = 1;
    rdy = 1;
    wait_us(10);

    // Send configuration commands to AD4696
    cs = 0;
    spi.write(0x8000 | (OSR << 8) | (PGA << 4) | BW);  // Write to configuration register
    cs = 1;

    return 0;
}

/* // Old pin testing code
int main() {
    char pintype, direction;
    int pin, value;

    printf("Rivanna2 Testing Suite v0.1\n");
    printf("This enables you to read or write values to digital and analog pins.\n");
    printf("Usage: d/a i/o pin\n");
    printf("d/a: Digital/Analog\ni/o: Input/Output\npin: Pin number\n");

    while (true) {
        // read command
        printf("d/a i/o pin_number: ");
        scanf("%c %c %d", &pintype, &direction, &pin);
        printf("%c %c %d\n", pintype, direction, pin);
        if (direction == 'i') {
            // Reading code
            printf("Reading value from pin %d with mode %c\n", pin, pintype);
        } else if (direction == 'o') {
            // Writing code
            printf("Value to write: ");
            scanf("%d", &value);
            printf("Writing value %d to pin %d with mode %c\n", value, pin, pintype);
        }
        scanf("%c", &direction);
    }
}
*/
