#include "../include/uart_serializer.hpp"
#include "../include/virtual_uart.hpp"

using namespace std;

VirtualUART::VirtualUART():isAvailable(true){}
VirtualUART::~VirtualUART(){}

//getters
bool VirtualUART::getIsAvailable(){
    return isAvailable;
}

uint32_t VirtualUART::getBaudRate(){
    return baudRate;    
}

//setters
void VirtualUART::setIsAvailable(bool status){
    isAvailable=status;
}

void VirtualUART::setBaudRate(uint32_t rate){
    baudRate=rate;

}
      
void VirtualUART::transmitByte(uint8_t& data){
    txBuffer.push(data);
}

uint8_t VirtualUART::receiveByte(){
    uint8_t result = txBuffer.front();
    txBuffer.pop();
    return result;    
}

void VirtualUART::transmit(vector<uint8_t>& data){
    for(int i=0;i<data.size();i++){
        transmitByte(data[i]);
    }
}

vector<uint8_t> VirtualUART::receive(size_t n){
    vector<uint8_t> received;;
    for(int i=0;i<n;i++){
        received.push_back(receiveByte());
    }
    return received;
}

ImuPacket VirtualUART::read(vector<uint8_t>& data){
    return serializer.deserialize(data);
}

vector<uint8_t> VirtualUART::write(ImuPacket& packet){
    return serializer.serialize(packet);
}

size_t VirtualUART::size(){
    return txBuffer.size();
}
