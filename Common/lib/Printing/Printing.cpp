#include "Printing.h"
#include <stdlib.h>

using namespace std;

// Used to make printing thread safe
Mutex mutex;
Mutex &printing_mutex = mutex;

void print_thread_safe(const char *s, ...) {
    printing_mutex.lock();
    va_list args;
    va_start(args, s);
    printf(s, args);
    va_end(args);
    printing_mutex.unlock();
}

// Input: an integer representing a float with decimals digits past decimal multiplied by 10^decimals
// Output: print num as a float
void printIntegerAsFloat(int num, int decimals) {
#ifdef PRINTING
    printing_mutex.lock();
    int left = num;
    int right = num;
    int d = decimals;

    if(d < 0)
    {
        PRINT("ERROR: printIntegerAsFloat() argument decimals was negative.");
        printing_mutex.unlock();
        return;
    }

    if(left < 0)
    {
        PRINT("-");
    }
    int mult = 1;
    for(int i = 0; i < d; ++i)
        mult *= 10;
    
    left = abs(left/mult);
    right = abs(right) - left * mult;

    PRINT("%d.", left);

    for(int i = 10; i < mult; i*=10)
    {
        if(right < i)
        {
            PRINT("0");
        }    
    }

    PRINT("%d", right);
    PRINT("\n");
    printing_mutex.unlock();

#endif //PRINTING
}

// Input: a float
// Output: print num as a float
void printFloat(float num, int decimals) {
#ifdef PRINTING
    float n = num;
    int d = decimals;
    
    if(d < 0)
    {
        PRINT("ERROR: printFloat() argument decimals was negative.");
        return;
    }

    int mult = 1;
    for(int i = 0; i < d; ++i)
        mult *= 10;

    printIntegerAsFloat((int)(n*mult), d);

#endif //PRINTING
}
