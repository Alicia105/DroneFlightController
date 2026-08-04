#ifndef UART_SERIALIZER_HPP
#define UART_SERIALIZER_HPP

#include <vector>
#include "packet.hpp"

class UARTSerializer{
    
    public:
    UARTSerializer();
    ~UARTSerializer();

    std::vector<uint8_t> serialize(const ImuPacket& packet);
    ImuPacket deserialize(const std::vector<uint8_t>& data);

    void appendUint8(std::vector<uint8_t>& buffer,uint8_t data);
    void appendUint16(std::vector<uint8_t>& buffer,uint16_t data);
    void appendUint32(std::vector<uint8_t>& buffer,uint32_t data);
    void appendFloat(std::vector<uint8_t>& buffer,float data);

    uint8_t  readUint8(const std::vector<uint8_t>& serializedBuffer, size_t& index);
    uint16_t readUint16(const std::vector<uint8_t>& serializedBuffer, size_t& index);
    uint32_t readUint32(const std::vector<uint8_t>& serializedBuffer, size_t& index);
    float readFloat(const std::vector<uint8_t>& serializedBuffer, size_t& index);

};

#endif //UART_SERIALIZER_HPP