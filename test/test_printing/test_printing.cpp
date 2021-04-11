#include <unity.h>
#include <unistd.h>
#include <cstring>
#include <stdexcept>
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

// Equivalence Test
void test_print()
{
    const char* test_message = "Hello World!";
    PRINT(test_message);
    restore_stdout();
    TEST_ASSERT_EQUAL_STRING(test_message, stdout_buffer);
}

// Boundary Test
void test_print_empty()
{
    const char* test_message = "";
    PRINT(test_message);
    restore_stdout();
    TEST_ASSERT_EQUAL_STRING(test_message, stdout_buffer);
}

// Boundary Test
void test_print_newline()
{
    const char* test_message = "Hello World!\r\n";
    PRINT(test_message);
    restore_stdout();
    TEST_ASSERT_EQUAL_STRING(test_message, stdout_buffer);
}

// Equivalence Test
void test_print_positive_integer()
{
    const char* test_message = "Test number is: %d";
    int test_num = 123;
    const char* expected_result = "Test number is: 123";
    PRINT(test_message, test_num);
    restore_stdout();
    TEST_ASSERT_EQUAL_STRING(expected_result, stdout_buffer);
}

// Boundary Test
void test_print_negative_integer()
{
    const char* test_message = "Test number is: %d";
    int test_num = -123;
    const char* expected_result = "Test number is: -123";
    PRINT(test_message, test_num);
    restore_stdout();
    TEST_ASSERT_EQUAL_STRING(expected_result, stdout_buffer);
}

// Boundary Test
void test_print_zero_integer()
{
    const char* test_message = "Test number is: %d";
    int test_num = 0;
    const char* expected_result = "Test number is: 0";
    PRINT(test_message, test_num);
    restore_stdout();
    TEST_ASSERT_EQUAL_STRING(expected_result, stdout_buffer);
}

// Equivalence Test
void test_print_integer_as_float()
{
    int test_num = 123;
    int test_decimals = 2;
    const char* expected_result = "1.23";
    printIntegerAsFloat(test_num, test_decimals);
    restore_stdout();
    TEST_ASSERT_EQUAL_STRING(expected_result, stdout_buffer);
}

// Boundary Test
void test_print_integer_as_float_negative()
{
    int test_num = -123;
    int test_decimals = 2;
    const char* expected_result = "-1.23";
    printIntegerAsFloat(test_num, test_decimals);
    restore_stdout();
    TEST_ASSERT_EQUAL_STRING(expected_result, stdout_buffer);
}

// Boundary Test
void test_print_integer_as_float_middle_zeros()
{
    int test_num = 1003;
    int test_decimals = 2;
    const char* expected_result = "10.03";
    printIntegerAsFloat(test_num, test_decimals);
    restore_stdout();
    TEST_ASSERT_EQUAL_STRING(expected_result, stdout_buffer);
}

// Boundary Test
void test_print_integer_as_float_trailing_zero()
{
    int test_num = 120;
    int test_decimals = 2;
    const char* expected_result = "1.20";
    printIntegerAsFloat(test_num, test_decimals);
    restore_stdout();
    TEST_ASSERT_EQUAL_STRING(expected_result, stdout_buffer);
}

// Boundary Test
void test_print_integer_as_float_leading_zero()
{
    int test_num = 123;
    int test_decimals = 3;
    const char* expected_result = "0.123";
    printIntegerAsFloat(test_num, test_decimals);
    restore_stdout();
    TEST_ASSERT_EQUAL_STRING(expected_result, stdout_buffer);
}

// Exception Test
void test_print_integer_as_float_negative_decimals()
{
    int test_num = 123;
    int test_decimals = -1;
    try
    {
        printIntegerAsFloat(test_num, test_decimals);
        restore_stdout();
        TEST_FAIL();
    }
    catch(invalid_argument& e)
    {
        restore_stdout();
        TEST_PASS();
    }
}

// Equivalence Test
void test_print_float()
{
    float test_num = 1.23f;
    int test_decimals = 2;
    const char* expected_result = "1.23";
    printFloat(test_num, test_decimals);
    restore_stdout();
    TEST_ASSERT_EQUAL_STRING(expected_result, stdout_buffer);
}

// Boundary Test
void test_print_float_negative()
{
    float test_num = -1.23f;
    int test_decimals = 2;
    const char* expected_result = "-1.23";
    printFloat(test_num, test_decimals);
    restore_stdout();
    TEST_ASSERT_EQUAL_STRING(expected_result, stdout_buffer);
}

// Boundary Test
void test_print_float_middle_zeros()
{
    float test_num = 10.03f;
    int test_decimals = 2;
    const char* expected_result = "10.03";
    printFloat(test_num, test_decimals);
    restore_stdout();
    TEST_ASSERT_EQUAL_STRING(expected_result, stdout_buffer);
}

// Boundary Test
void test_print_float_trailing_zero()
{
    float test_num = 1.20f;
    int test_decimals = 2;
    const char* expected_result = "1.20";
    printFloat(test_num, test_decimals);
    restore_stdout();
    TEST_ASSERT_EQUAL_STRING(expected_result, stdout_buffer);
}

// Boundary Test
void test_print_float_leading_zero()
{
    float test_num = 0.123f;
    int test_decimals = 3;
    const char* expected_result = "0.123";
    printFloat(test_num, test_decimals);
    restore_stdout();
    TEST_ASSERT_EQUAL_STRING(expected_result, stdout_buffer);
}

// Exception Test
void test_print_float_negative_decimals()
{
    float test_num = 1.23f;
    int test_decimals = -1;
    try
    {
        printFloat(test_num, test_decimals);
        restore_stdout();
        TEST_FAIL();
    }
    catch(invalid_argument& e)
    {
        restore_stdout();
        TEST_PASS();
    }
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_print);
    RUN_TEST(test_print_empty);
    RUN_TEST(test_print_newline);
    RUN_TEST(test_print_positive_integer);
    RUN_TEST(test_print_negative_integer);
    RUN_TEST(test_print_zero_integer);
    RUN_TEST(test_print_integer_as_float);
    RUN_TEST(test_print_integer_as_float_negative);
    RUN_TEST(test_print_integer_as_float_middle_zeros);
    RUN_TEST(test_print_integer_as_float_trailing_zero);
    RUN_TEST(test_print_integer_as_float_leading_zero);
    RUN_TEST(test_print_integer_as_float_negative_decimals);
    RUN_TEST(test_print_float);
    RUN_TEST(test_print_float_negative);
    RUN_TEST(test_print_float_middle_zeros);
    RUN_TEST(test_print_float_trailing_zero);
    RUN_TEST(test_print_float_leading_zero);
    RUN_TEST(test_print_float_negative_decimals);
    UNITY_END();

#ifndef NATIVE
    while(1){}
#endif
}