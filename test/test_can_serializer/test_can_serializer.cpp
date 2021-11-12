#include <unity.h>
#include <mbed.h>
#include "CANSerializer.h"

#define SERIALIZE_AND_DESERIALIZE \
    CANMessage message; \
    a.serialize(&message); \
    struct test b; \
    b.deserialize(&message); \

void single_int_test()
{
    struct test {
        std::int32_t a;
        SERIALIZATION_METHODS((a, 32))
    };
    struct test a = { 1 };

    SERIALIZE_AND_DESERIALIZE

    TEST_ASSERT_TRUE(message.len == 4);
    TEST_ASSERT_TRUE(a.a == b.a);
}

void multiple_types_test()
{
    struct test {
        bool a;
        std::int32_t b;
        bool c;
        bool d;
        std::uint8_t e;
        bool f;
        SERIALIZATION_METHODS(
            (a, 1),
            (b, 32),
            (c, 1),
            (d, 1),
            (e, 8),
            (f, 1)
        )
    };
    struct test a = { true, -37, false, true, 5, true };

    SERIALIZE_AND_DESERIALIZE

    TEST_ASSERT_TRUE(message.len == 6);
    TEST_ASSERT_TRUE(a.a == b.a);
    TEST_ASSERT_TRUE(a.b == b.b);
    TEST_ASSERT_TRUE(a.c == b.c);
    TEST_ASSERT_TRUE(a.d == b.d);
    TEST_ASSERT_TRUE(a.e == b.e);
    TEST_ASSERT_TRUE(a.f == b.f);
}

// This tests for serializing only the low 7 bits of an
// 8-bit unsigned integer. This should work, but only for
// values that fit in 7 bits. In this case, the serialized
// struct should only require 1 byte.
void seven_bit_unsigned_int_test()
{
    struct test {
        bool a;
        std::uint8_t b;
        SERIALIZATION_METHODS((a, 1), (b, 7))
    };
    struct test a = { false, 14 };

    SERIALIZE_AND_DESERIALIZE

    TEST_ASSERT_TRUE(message.len == 1);
    TEST_ASSERT_TRUE(a.a == b.a);
    TEST_ASSERT_TRUE(a.b == b.b);
}


void unserialized_fields_test()
{
    struct test {
        std::uint8_t a;
        std::uint32_t b;
        SERIALIZATION_METHODS((a, 8))
    };
    struct test a = { 8, 14 };

    SERIALIZE_AND_DESERIALIZE

    TEST_ASSERT_TRUE(message.len == 1);
    TEST_ASSERT_TRUE(a.a == b.a);
}

void unsigned_long_long_test()
{
    struct test {
        std::uint64_t a;
        SERIALIZATION_METHODS((a, 64))
    };
    struct test a = { 18446744073709551615ull };

    SERIALIZE_AND_DESERIALIZE

    TEST_ASSERT_TRUE(message.len == 8);
    TEST_ASSERT_TRUE(a.a == b.a);
}

void max_values_test()
{
    struct test {
        std::uint32_t a;
        std::int16_t b;
        std::uint8_t c;
        SERIALIZATION_METHODS((a, 32), (b, 16), (c, 8))
    };
    struct test a = { 4294967295, -32768, 255 };

    SERIALIZE_AND_DESERIALIZE

    TEST_ASSERT_TRUE(message.len == 7);
    TEST_ASSERT_TRUE(a.a == b.a);
    TEST_ASSERT_TRUE(a.b == b.b);
    TEST_ASSERT_TRUE(a.c == b.c);
}

void sixty_four_booleans_test()
{
    struct test {
        bool a0;
        bool a1;
        bool a2;
        bool a3;
        bool a4;
        bool a5;
        bool a6;
        bool a7;
        bool a8;
        bool a9;
        bool a10;
        bool a11;
        bool a12;
        bool a13;
        bool a14;
        bool a15;
        bool a16;
        bool a17;
        bool a18;
        bool a19;
        bool a20;
        bool a21;
        bool a22;
        bool a23;
        bool a24;
        bool a25;
        bool a26;
        bool a27;
        bool a28;
        bool a29;
        bool a30;
        bool a31;
        bool a32;
        bool a33;
        bool a34;
        bool a35;
        bool a36;
        bool a37;
        bool a38;
        bool a39;
        bool a40;
        bool a41;
        bool a42;
        bool a43;
        bool a44;
        bool a45;
        bool a46;
        bool a47;
        bool a48;
        bool a49;
        bool a50;
        bool a51;
        bool a52;
        bool a53;
        bool a54;
        bool a55;
        bool a56;
        bool a57;
        bool a58;
        bool a59;
        bool a60;
        bool a61;
        bool a62;
        bool a63;
        SERIALIZATION_METHODS(
            (a0, 1),
            (a1, 1),
            (a2, 1),
            (a3, 1),
            (a4, 1),
            (a5, 1),
            (a6, 1),
            (a7, 1),
            (a8, 1),
            (a9, 1),
            (a10, 1),
            (a11, 1),
            (a12, 1),
            (a13, 1),
            (a14, 1),
            (a15, 1),
            (a16, 1),
            (a17, 1),
            (a18, 1),
            (a19, 1),
            (a20, 1),
            (a21, 1),
            (a22, 1),
            (a23, 1),
            (a24, 1),
            (a25, 1),
            (a26, 1),
            (a27, 1),
            (a28, 1),
            (a29, 1),
            (a30, 1),
            (a31, 1),
            (a32, 1),
            (a33, 1),
            (a34, 1),
            (a35, 1),
            (a36, 1),
            (a37, 1),
            (a38, 1),
            (a39, 1),
            (a40, 1),
            (a41, 1),
            (a42, 1),
            (a43, 1),
            (a44, 1),
            (a45, 1),
            (a46, 1),
            (a47, 1),
            (a48, 1),
            (a49, 1),
            (a50, 1),
            (a51, 1),
            (a52, 1),
            (a53, 1),
            (a54, 1),
            (a55, 1),
            (a56, 1),
            (a57, 1),
            (a58, 1),
            (a59, 1),
            (a60, 1),
            (a61, 1),
            (a62, 1),
            (a63, 1)
        )
    };
    struct test a = { 
        true, true, true, true, true, true, true, true,
        true, true, true, true, true, true, true, true, 
        true, true, true, true, true, true, true, true, 
        true, true, true, true, true, true, true, true, 
        true, true, true, true, true, true, true, true, 
        true, true, true, true, true, true, true, true, 
        true, true, true, true, true, true, true, true, 
        true, true, true, true, true, true, true, true
    };

    SERIALIZE_AND_DESERIALIZE

    TEST_ASSERT_TRUE(message.len == 8);
    TEST_ASSERT_TRUE(a.a0 == b.a0);
    TEST_ASSERT_TRUE(a.a1 == b.a1);
    TEST_ASSERT_TRUE(a.a2 == b.a2);
    TEST_ASSERT_TRUE(a.a3 == b.a3);
    TEST_ASSERT_TRUE(a.a4 == b.a4);
    TEST_ASSERT_TRUE(a.a5 == b.a5);
    TEST_ASSERT_TRUE(a.a6 == b.a6);
    TEST_ASSERT_TRUE(a.a7 == b.a7);
    TEST_ASSERT_TRUE(a.a8 == b.a8);
    TEST_ASSERT_TRUE(a.a9 == b.a9);
    TEST_ASSERT_TRUE(a.a10 == b.a10);
    TEST_ASSERT_TRUE(a.a11 == b.a11);
    TEST_ASSERT_TRUE(a.a12 == b.a12);
    TEST_ASSERT_TRUE(a.a13 == b.a13);
    TEST_ASSERT_TRUE(a.a14 == b.a14);
    TEST_ASSERT_TRUE(a.a15 == b.a15);
    TEST_ASSERT_TRUE(a.a16 == b.a16);
    TEST_ASSERT_TRUE(a.a17 == b.a17);
    TEST_ASSERT_TRUE(a.a18 == b.a18);
    TEST_ASSERT_TRUE(a.a19 == b.a19);
    TEST_ASSERT_TRUE(a.a20 == b.a20);
    TEST_ASSERT_TRUE(a.a21 == b.a21);
    TEST_ASSERT_TRUE(a.a22 == b.a22);
    TEST_ASSERT_TRUE(a.a23 == b.a23);
    TEST_ASSERT_TRUE(a.a24 == b.a24);
    TEST_ASSERT_TRUE(a.a25 == b.a25);
    TEST_ASSERT_TRUE(a.a26 == b.a26);
    TEST_ASSERT_TRUE(a.a27 == b.a27);
    TEST_ASSERT_TRUE(a.a28 == b.a28);
    TEST_ASSERT_TRUE(a.a29 == b.a29);
    TEST_ASSERT_TRUE(a.a30 == b.a30);
    TEST_ASSERT_TRUE(a.a31 == b.a31);
    TEST_ASSERT_TRUE(a.a32 == b.a32);
    TEST_ASSERT_TRUE(a.a33 == b.a33);
    TEST_ASSERT_TRUE(a.a34 == b.a34);
    TEST_ASSERT_TRUE(a.a35 == b.a35);
    TEST_ASSERT_TRUE(a.a36 == b.a36);
    TEST_ASSERT_TRUE(a.a37 == b.a37);
    TEST_ASSERT_TRUE(a.a38 == b.a38);
    TEST_ASSERT_TRUE(a.a39 == b.a39);
    TEST_ASSERT_TRUE(a.a40 == b.a40);
    TEST_ASSERT_TRUE(a.a41 == b.a41);
    TEST_ASSERT_TRUE(a.a42 == b.a42);
    TEST_ASSERT_TRUE(a.a43 == b.a43);
    TEST_ASSERT_TRUE(a.a44 == b.a44);
    TEST_ASSERT_TRUE(a.a45 == b.a45);
    TEST_ASSERT_TRUE(a.a46 == b.a46);
    TEST_ASSERT_TRUE(a.a47 == b.a47);
    TEST_ASSERT_TRUE(a.a48 == b.a48);
    TEST_ASSERT_TRUE(a.a49 == b.a49);
    TEST_ASSERT_TRUE(a.a50 == b.a50);
    TEST_ASSERT_TRUE(a.a51 == b.a51);
    TEST_ASSERT_TRUE(a.a52 == b.a52);
    TEST_ASSERT_TRUE(a.a53 == b.a53);
    TEST_ASSERT_TRUE(a.a54 == b.a54);
    TEST_ASSERT_TRUE(a.a55 == b.a55);
    TEST_ASSERT_TRUE(a.a56 == b.a56);
    TEST_ASSERT_TRUE(a.a57 == b.a57);
    TEST_ASSERT_TRUE(a.a58 == b.a58);
    TEST_ASSERT_TRUE(a.a59 == b.a59);
    TEST_ASSERT_TRUE(a.a60 == b.a60);
    TEST_ASSERT_TRUE(a.a61 == b.a61);
    TEST_ASSERT_TRUE(a.a62 == b.a62);
    TEST_ASSERT_TRUE(a.a63 == b.a63);
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(single_int_test);
    RUN_TEST(multiple_types_test);
    RUN_TEST(seven_bit_unsigned_int_test);
    RUN_TEST(unserialized_fields_test);
    RUN_TEST(unsigned_long_long_test);
    RUN_TEST(max_values_test);
    RUN_TEST(sixty_four_booleans_test);
    UNITY_END();

#ifndef NATIVE
    while(1){}
#endif
}