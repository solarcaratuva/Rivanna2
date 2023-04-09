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

SPI spi(SPI_MOSI, SPI_MISO, SPI_SCK); // mosi, miso, sclk
DigitalOut cs(SPI_CS);

// Based on DriverBoard/DriverBoard.kicad_sch
typedef enum {
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
} ButtonMasks;

typedef struct {

} Response;

int initializeADC() {
    // Sends SPI commands

    return 0;
}

Response queryADC() {
    // Queries for ADC values from IO board

    return Response {};
}

int main() {

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
