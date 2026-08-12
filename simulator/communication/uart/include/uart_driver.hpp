#ifndef UART_DRIVER_HPP
#define UART_DRIVER_HPP

#include <iostream>
#include <vector>
#include "../../../../shared/communication/include/packet.hpp"
#include "uart_serializer.hpp"
#include "uart_channel.hpp"


class UARTDriver{//interface to write/read packets
    private :
        UARTChannel& channel;
        UARTSerializer serializer;
    
    public :
        UARTDriver(UARTChannel& uart);
        ~UARTDriver();

        UARTSerializer getSerializer();
        ImuPacket read();
        void write(const ImuPacket& packet);
        
};

#endif //UART_DRIVER_HPP
