# `CANSerializer.h`

## Usage

`CANSerializer.h` defines the `SERIALIZATION_METHODS(...)` macro, which automatically generates `serialize` and `deserialize` methods for a CAN struct. 

The macro takes in a variable number of (`field_name`, `field_size_in_bits`) pairs, each describing one field of the CAN struct, as shown below.

```
struct can_struct {
    std::uint8_t a;
    bool b;
    bool c;
    std::int32_t d;
    SERIALIZATION_METHODS((a, 8), (b, 1), (c, 1), (d, 32))
};
```

The generated `serialize` and `deserialize` methods will have the signatures shown below.
```
void serialize(unsigned char *data, unsigned char *len)
void deserialize(const unsigned char *data, const unsigned char len)
```

`serialize` will read the fields of the struct, serialize them into `data`, and set `len` to the number of bytes required by the serialization.

`deserialize` will deserialize `data` and set each field of the struct accordingly.

The behavior of `serialize` and `deserialize` is shown below, relying on `can_struct` defined above.

```
// Initialize a
struct can_struct a = { -7, true, false, 38 };

unsigned char data[8];
unsigned char len;

// Serialize a into data and set len
a.serialize(data, &len);

// Build b from the contents of data
struct can_struct b;
b.deserialize(data, len);

// Here, b.a == -7, b.b == true, b.c == false, and b.d == 38
```

## Limitations

`mbed::CANMessage` can only hold messages of 8 bytes or fewer. The same limit applies to `CANSerializer`.

## Implementation

On the serialization side, a 64-bit unsigned integer (`serialized`) represents the serialized version of the CAN struct. It is initialized to 0. The `field_start_bit` variable is used to keep track of the next bit to be used for serialization.

Then, the Boost Preprocessor library macro `BOOST_PP_SEQ_FOR_EACH` is used to apply the `SERIALIZE_FIELD` macro to each field pair passed to `SERIALIZATION_METHODS(...)`. This will set bits in `serialized` based on the value of each field using bit manipulation.

Finally, the `len` variable will be set and the `serialized` variable is copied to `data`. 

This process is repeated in reverse to generate the `deserialize` method.
