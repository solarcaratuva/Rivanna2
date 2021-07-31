#ifndef PRINTING_H
#define PRINTING_H

#define PRINTING    // only defined if using printf functions

#include <mbed.h>

#ifdef PRINTING
#define PRINT(formatstring, ...) print_thread_safe(formatstring, ##__VA_ARGS__)
#else  //PRINTING
#define PRINT(formatstring, ...) do { } while(0)
#endif //PRINTING

void print_thread_safe(const char *s, ...);

// Input: an integer representing a float with decimals digits past decimal multiplied by 10^decimals
// Output: print num as a float
void printIntegerAsFloat(int num, int decimals);

// Input: a float
// Output: print num as a float
void printFloat(float num, int decimals);

#endif // PRINTING_H