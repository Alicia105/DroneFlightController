#ifndef VIRTUAL_UART_HPP
#define VIRTUAL_UART_HPP

#include <iostream>
#include <vector>
#include <queue>
#include "../include/packet.hpp"
#include "../include/uart_serializer.hpp"

class VirtualUART{
    private :
        UARTSerializer serializer;
        std::queue<uint8_t> txBuffer;
        bool isAvailable;
        uint32_t baudRate;       

    public :
        VirtualUART();
        ~VirtualUART();

        //getters
        bool VirtualUART::getIsAvailable();
        uint32_t VirtualUART::getBaudRate();

        //setters
        void VirtualUART::setIsAvailable(bool status);
        void VirtualUART::setBaudRate(uint32_t rate);
        
        void transmitByte(uint8_t& data);
        uint8_t receiveByte();

        void transmit(std::vector<uint8_t>& data);
        std::vector<uint8_t> receive(size_t n);


        ImuPacket read(std::vector<uint8_t>& data);
        std::vector<uint8_t> write(ImuPacket& packet);
        
        size_t size();

};

#endif //VIRTUAL_UART_HPP
