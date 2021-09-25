#ifndef CAN_SERIALIZER_H
#define CAN_SERIALIZER_H

#include <inttypes.h>
#include <stdio.h>
#include <cstring>
#include <boost/preprocessor.hpp>

#define BITS_PER_BYTE 8

// Bit mask for lower bit_count bits
#define BITMASK(bit_count) \
    (bit_count >= sizeof(std::uint64_t) * BITS_PER_BYTE ? -1ULL : (1ULL << bit_count) - 1ULL)

// Add value of field_name to serialized variable
// Increment field_start bit by field_size
#define SERIALIZE_FIELD(field_name, field_size) \
    serialized |= ((field_name & BITMASK(field_size)) << field_start_bit); \
    field_start_bit += field_size; \

// Set field_name to value based on serialized variable
// Increment field_start bit by field_size
#define DESERIALIZE_FIELD(field_name, field_size) \
    field_name = (serialized >> field_start_bit) & BITMASK(field_size); \
    field_start_bit += field_size; \

// Macro to be applied for each arg in __VA_ARGS__
// r is used by Boost internally
// data is unused
// elem is a tuple of the form (field_name, field_size)
#define SERIALIZE_FIELD_MACRO(r, data, elem) \
    SERIALIZE_FIELD(BOOST_PP_TUPLE_ELEM(0, elem), BOOST_PP_TUPLE_ELEM(1, elem))

#define DESERIALIZE_FIELD_MACRO(r, data, elem) \
    DESERIALIZE_FIELD(BOOST_PP_TUPLE_ELEM(0, elem), BOOST_PP_TUPLE_ELEM(1, elem))

// Macro to generate serialize and deserialize methods
// Input is of the form (field1_name, field1_size), (field2_name, field2_size), ...
#define SERIALIZATION_METHODS(...) \
    void serialize(unsigned char *data, unsigned char *len) \
    { \
        std::uint64_t serialized = 0; \
        std::uint8_t field_start_bit = 0; \
        BOOST_PP_SEQ_FOR_EACH(SERIALIZE_FIELD_MACRO, (), BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)) \
        *len = (field_start_bit + BITS_PER_BYTE - 1) / BITS_PER_BYTE; \
        memcpy(data, &serialized, *len); \
    } \
    void deserialize(const unsigned char *data, const unsigned char len) \
    { \
        std::uint64_t serialized = 0; \
        memcpy(&serialized, data, len); \
        std::uint8_t field_start_bit = 0; \
        BOOST_PP_SEQ_FOR_EACH(DESERIALIZE_FIELD_MACRO, (), BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)) \
    } \

#endif