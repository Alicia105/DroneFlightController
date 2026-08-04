#include "../include/uart_driver.hpp"

using namespace std;

UARTDriver::UARTDriver(){}//interface to write/read packets
UARTDriver::~UARTDriver(){}

ImuPacket UARTDriver::read(std::vector<uint8_t>& data){
    return serializer.deserialize(data);
}

vector<uint8_t> UARTDriver::write(ImuPacket& packet){
    return serializer.serialize(packet);
}

