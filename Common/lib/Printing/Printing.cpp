#include "Printing.h"
#include <mbed.h>
#include <stdarg.h>
#include <stdlib.h>

// Used to make printing thread safe
Mutex printing_mutex;

void print_thread_safe(const char *s, ...) {
    printing_mutex.lock();
    va_list args;
    va_start(args, s);
    vprintf(s, args);
    va_end(args);
    printing_mutex.unlock();
}

// Input: an integer representing a float with decimals digits past decimal
// multiplied by 10^decimals Output: print num as a float
void printIntegerAsFloat(int num, int decimals) {
    printing_mutex.lock();
    int left = num;
    int right = num;
    int d = decimals;

    if (d < 0) {
        printf("ERROR: printIntegerAsFloat() argument decimals was negative.");
        printing_mutex.unlock();
        return;
    }

    if (left < 0) {
        printf("-");
    }
    int mult = 1;
    for (int i = 0; i < d; ++i)
        mult *= 10;

    left = abs(left / mult);
    right = abs(right) - left * mult;

    printf("%d.", left);

    for (int i = 10; i < mult; i *= 10) {
        if (right < i) {
            printf("0");
        }
    }

    printf("%d", right);
    printing_mutex.unlock();
}

// Input: a float
// Output: print num as a float
void printFloat(float num, int decimals) {
    float n = num;
    int d = decimals;

    if (d < 0) {
        print_thread_safe(
            "ERROR: printFloat() argument decimals was negative.");
        return;
    }

    int mult = 1;
    for (int i = 0; i < d; ++i)
        mult *= 10;

    printIntegerAsFloat((int)(n * mult), d);
}
