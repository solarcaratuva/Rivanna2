#include "Printing.h"
#include <stdlib.h>

// Input: an integer representing a float with decimals digits past decimal multiplied by 10^decimals
// Output: print num as a float
void printIntegerAsFloat(int num, int decimals) {
#ifdef PRINTING
    int left = num;
    int right = num;
    int d = decimals;

    if(left < 0)
        PRINT("-");
    
    int mult = 1;
    for(int i = 0; i < d; ++i)
        mult *= 10;
    
    left = abs(left/mult);
    right = abs(right) - left * mult;

    PRINT("%d.", left);

    for(int i = 10; i < mult; i*=10)
    {
        if(right < i)
            PRINT("0");
    }

    PRINT("%d", right);
#endif //PRINTING
}

// Input: a float
// Output: print num as a float
void printFloat(float num, int decimals) {
#ifdef PRINTING
    float n = num;
    int d = decimals;

    int mult = 1;
    for(int i = 0; i < d; ++i)
        mult *= 10;

    printIntegerAsFloat((int)(n*mult), d);
#endif //PRINTING
}