#ifndef VIRTUAL_UART_HPP
#define VIRTUAL_UART_HPP

#include <iostream>
#include <vector>
#include <queue>
#include "../include/packet.hpp"
#include "../include/uart_serializer.hpp"

class VirtualUART{//transport bytes
    private :
        //UARTSerializer serializer;
        std::queue<uint8_t> txBuffer;
        uint32_t baudRate;       

    public :
        VirtualUART();
        ~VirtualUART();

        //getters
        uint32_t getBaudRate();

        //setters
        void setBaudRate(uint32_t rate);
        
        void transmitByte(uint8_t data);
        uint8_t receiveByte();

        void transmit(std::vector<uint8_t>& data);
        std::vector<uint8_t> receive(size_t n);
        
        size_t size();
        bool dataAvailable();
};

#endif //VIRTUAL_UART_HPP
