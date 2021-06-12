#include "Printing.h"
#include <stdlib.h>

using namespace std;

// Input: an integer representing a float with decimals digits past decimal multiplied by 10^decimals
// Output: print num as a float
void printIntegerAsFloat(int num, int decimals) {
#ifdef PRINTING
    int left = num;
    int right = num;
    int d = decimals;

    if(d < 0)
    {
        printing_mutex.lock();
        PRINT("ERROR: printIntegerAsFloat() argument decimals was negative.");
        printing_mutex.unlock();
        return;
    }

    if(left < 0)
    {
        printing_mutex.lock();
        PRINT("-");
        printing_mutex.unlock();
    }
    int mult = 1;
    for(int i = 0; i < d; ++i)
        mult *= 10;
    
    left = abs(left/mult);
    right = abs(right) - left * mult;

    printing_mutex.lock();
    PRINT("%d.", left);
    printing_mutex.unlock();

    for(int i = 10; i < mult; i*=10)
    {
        if(right < i)
        {
            printing_mutex.lock();
            PRINT("0");
            printing_mutex.unlock();
        }    
    }

    printing_mutex.lock();
    PRINT("%d", right);
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
        printing_mutex.lock();
        PRINT("ERROR: printFloat() argument decimals was negative.");
        printing_mutex.unlock();
        return;
    }

    int mult = 1;
    for(int i = 0; i < d; ++i)
        mult *= 10;

    printIntegerAsFloat((int)(n*mult), d);

#endif //PRINTING
}