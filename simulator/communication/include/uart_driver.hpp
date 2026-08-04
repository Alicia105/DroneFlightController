#ifndef UART_DRIVER_HPP
#define UART_DRIVER_HPP

#include <iostream>
#include <vector>
#include "../include/packet.hpp"
#include "../include/uart_serializer.hpp"
#include "../include/virtual_uart.hpp"


class UARTDriver{//interface to write/read packets
    private :
        VirtualUART channel;
        UARTSerializer serializer;
    
    public :
        UARTDriver();
        ~UARTDriver();

        ImuPacket read(std::vector<uint8_t>& data);
        std::vector<uint8_t> write(ImuPacket& packet);
        
};

#endif //UART_DRIVER_HPP
