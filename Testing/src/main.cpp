#include "log.h"
#include <mbed.h>
#include <rtos.h>
#include <stdio.h>
#include <chrono>
#include "ThisThread.h"

#define FLASH_PERIOD 500ms

// DigitalOut brake_lights(BRAKE_LIGHT_EN);

// AnalogIn fan_tach(FanTach);

/*

Command Documentation for Testing:

digital/analog in/out pin_number
d/a i/o pin_number

*/

enum DigitalInputPins {
    LEFT_TURN = 17,
    RIGHT_TURN = 28,
    HAZARDS = 2,
    BRAKE = 31,
    REGEN = 29,
    FORWARD = 18
};

enum AnalogInputPins {
    THROTTLE = 27,
};

enum DigitalOutputPins {
    BRAKE_LIGHT = 26,
    LEFT_TURN_LIGHT = 8,
    RIGHT_TURN_LIGHT = 9,
    DRO = 25,
    BMS_STROBE = 16
};

Thread signalFlashThread;

DigitalOut brake_lights(BRAKE_LIGHT);
DigitalOut leftTurnSignal(LEFT_TURN_LIGHT);
DigitalOut rightTurnSignal(RIGHT_TURN_LIGHT);

// bool flashHazards, flashLSignal, flashRSignal = false;
DigitalIn flashHazards(HAZARDS);
DigitalIn flashLSignal(LEFT_TURN);
DigitalIn flashRSignal(RIGHT_TURN);

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

void signalFlashHandler() {
    while (true) {
        if (flashHazards || flashLSignal || flashRSignal) {
            if (flashHazards) {
                bool leftTurnSignalState = leftTurnSignal;
                leftTurnSignal = !leftTurnSignalState;
                rightTurnSignal = !leftTurnSignalState;
            } else if (flashLSignal) {
                leftTurnSignal = !leftTurnSignal;
                rightTurnSignal = false;
            } else if (flashRSignal) {
                rightTurnSignal = !rightTurnSignal;
                leftTurnSignal = false;
            } else {
                leftTurnSignal = false;
                rightTurnSignal = false;
            }

            ThisThread::sleep_for(FLASH_PERIOD);
        } else {
            leftTurnSignal = false;
            rightTurnSignal = false;
        }
        ThisThread::flags_wait_all(0x1);
    }
}

int main() {
    // No SPI for now.
    signalFlashThread.start(signalFlashHandler);

    while (true) {
        log_debug("Main thread loop");

        ThisThread::sleep_for(MAIN_LOOP_PERIOD);
    }

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
