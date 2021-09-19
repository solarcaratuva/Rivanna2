#ifndef CAN_SERIALIZER_H
#define CAN_SERIALIZER_H

#include <string>
#include <sstream>
#include <mbed.h>
#include "cereal/archives/binary.hpp"

template<class CANStruct>
void serialize_can_struct(CANMessage *message, CANStruct *data)
{
    std::stringstream stream;

    // Copy struct to stream
    {
        cereal::BinaryOutputArchive output_archive(stream);
        output_archive(*data);
    }

    // Get length (in bytes) of stream
    stream.seekg(0, std::ios::end);
    int len = stream.tellg();
    stream.seekg(0, std::ios::beg);

    // TODO: Remove
    PRINT("length: %d\n", len);

    // Copy stream to message
    stream.read((char *)message->data, len);
    message->len = len;
}

template<class CANStruct>
void deserialize_can_struct(CANStruct *data, CANMessage *message)
{
    std::stringstream stream;

    // Copy message to stream
    stream.write((char *)message->data, message->len);
    
    // Copy stream to struct
    {
        cereal::BinaryInputArchive input_archive(stream);
        input_archive(*data);
    }
}

#endif
