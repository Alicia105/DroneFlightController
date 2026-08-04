#include "../include/uart_driver.hpp"

using namespace std;

UARTDriver::UARTDriver(){}//interface to write/read packets
UARTDriver::~UARTDriver(){}

ImuPacket UARTDriver::read(){
    size_t n=channel.size();
    vector<uint8_t> data = channel.receive(n);
    return serializer.deserialize(data);
}

bool UARTDriver::write(ImuPacket& packet){
    vector<uint8_t> data = serializer.serialize(packet);
    channel.transmit(data);

    return channel.dataAvailable();
}

