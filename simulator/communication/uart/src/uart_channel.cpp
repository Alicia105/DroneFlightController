#include "../include/uart_serializer.hpp"
#include "../include/uart_channel.hpp"

using namespace std;

UARTChannel::UARTChannel():baudRate(115200){}//transport bytes
UARTChannel::~UARTChannel(){}

//getters
uint32_t UARTChannel::getBaudRate(){
    return baudRate;    
}

//setters
void UARTChannel::setBaudRate(uint32_t rate){
    baudRate=rate;
}
      
void UARTChannel::transmitByte(uint8_t data){
    txBuffer.push(data);
}

uint8_t UARTChannel::receiveByte(){
    if(txBuffer.empty()){
        throw runtime_error("UART RX buffer is empty.");
    }
    uint8_t result = txBuffer.front();
    txBuffer.pop();
    return result;    
}

void UARTChannel::transmit(vector<uint8_t>& data){
    for(int i=0;i<data.size();i++){
        transmitByte(data[i]);
    }
}

vector<uint8_t> UARTChannel::receive(size_t n){
    vector<uint8_t> received;
    for(int i=0;i<n;i++){
        received.push_back(receiveByte());
    }
    return received;
}

size_t UARTChannel::size(){
    return txBuffer.size();
}

bool UARTChannel::dataAvailable(){
    return !txBuffer.empty();
}
