#include <unity.h>
#include <unistd.h>
#include <cstring>
#include "Printing.h"

using namespace std;

#define STDOUT_BUFFER_SIZE 1024

int stdout_save;
char stdout_buffer[STDOUT_BUFFER_SIZE];

// extern int dup(int oldfd);
// extern int dup2(int oldfd, int newfd);

void redirect_stdout()
{
    // adapted from https://kaskavalci.com/redirecting-stdout-to-array-and-restoring-it-back-in-c/
    fflush(stdout); //clean everything first
    stdout_save = dup(STDOUT_FILENO); //save the stdout state
    freopen("NUL", "a", stdout); //redirect stdout to null pointer
    setvbuf(stdout, stdout_buffer, _IOFBF, STDOUT_BUFFER_SIZE); //set buffer to stdout
}

void restore_stdout()
{
    // adapted from https://kaskavalci.com/redirecting-stdout-to-array-and-restoring-it-back-in-c/
    freopen("NUL", "a", stdout); //redirect stdout to null again
    dup2(stdout_save, STDOUT_FILENO); //restore the previous state of stdout
    setvbuf(stdout, NULL, _IONBF, 0); //disable buffer to print to screen instantly
}

// Called before every test
void setUp()
{
    redirect_stdout();
}

// Called after every test
void tearDown()
{
    // restore_stdout();    // Don't need because every test function needs to call this before any assertions anyways (to allow fail messages to be printed)
    memset(stdout_buffer, 0, STDOUT_BUFFER_SIZE);   // clear the stdout_buffer with all zeros
}

// Write all tests here
void test_print()
{
    const char* testMessage = "Hello World!";
    PRINT(testMessage);
    restore_stdout();
    TEST_ASSERT_EQUAL_STRING(testMessage, stdout_buffer);
}

void test_print_integer_as_float()
{
    int testNum = 123;
    int testDecimals = 2;
    const char* expectedResult = "1.23";
    printIntegerAsFloat(testNum, testDecimals);
    restore_stdout();
    TEST_ASSERT_EQUAL_STRING(expectedResult, stdout_buffer);
}

void test_print_float()
{
    float testNum = 1.23f;
    int testDecimals = 2;
    const char* expectedResult = "1.23";
    printFloat(testNum, testDecimals);
    restore_stdout();
    TEST_ASSERT_EQUAL_STRING(expectedResult, stdout_buffer);
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_print);
    RUN_TEST(test_print_integer_as_float);
    RUN_TEST(test_print_float);
    UNITY_END();

#ifndef NATIVE
    while(1){}
#endif
}