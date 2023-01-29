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
