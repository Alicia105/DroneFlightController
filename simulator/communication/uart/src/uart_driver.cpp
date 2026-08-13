#include "../include/uart_driver.hpp"

using namespace std;

UARTDriver::UARTDriver(UARTChannel& uart):channel(uart),serializer(){}//interface to write/read packets
UARTDriver::~UARTDriver(){}

//getters
UARTSerializer UARTDriver::getSerializer(){
    return serializer;
}

ImuPacket UARTDriver::read(){
    //cout << "IMU_PACKET_SIZE = " << IMU_PACKET_SIZE << endl;
    //cout << "channel.size() = " << channel.size() << endl;

    if(channel.size() < IMU_PACKET_SIZE){
        throw runtime_error("Incomplete UART packet.");
    }
    vector<uint8_t> data = channel.receive(IMU_PACKET_SIZE);
    return serializer.deserialize(data);
}


void UARTDriver::write(const ImuPacket& packet){
    vector<uint8_t> data = serializer.serialize(packet);
    channel.transmit(data);
    return;
}

//via FreeRTOS

ImuPacket UARTDriver::readFreeRTOS(){
    vector<uint8_t> data = channel.receiveFreeRTOS();
    return serializer.deserialize(data);
}


void UARTDriver::writeFreeRTOS(const ImuPacket& packet){
    vector<uint8_t> data = serializer.serialize(packet);
    channel.transmitFreeRTOS(data);
    return;
}


/*void UARTDriver::writeFreeRTOS(const ImuPacket& packet){
    cout << "[UARTDriver] Before serialize" << endl;

    vector<uint8_t> data = serializer.serialize(packet);

    cout << "[UARTDriver] After serialize, size = "
         << data.size() << endl;

    channel.transmitFreeRTOS(data);

    cout << "[UARTDriver] After transmitFreeRTOS" << endl;
}*/