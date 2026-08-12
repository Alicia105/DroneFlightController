#ifndef UART_DRIVER_HPP
#define UART_DRIVER_HPP

#include <iostream>
#include <vector>
#include "../../../../shared/communication/include/packet.hpp"
#include "uart_serializer.hpp"
#include "virtual_uart.hpp"


class UARTDriver{//interface to write/read packets
    private :
        VirtualUART& channel;
        UARTSerializer serializer;
    
    public :
        UARTDriver(VirtualUART& uart);
        ~UARTDriver();

        UARTSerializer getSerializer();
        ImuPacket read();
        void write(const ImuPacket& packet);
        
};

#endif //UART_DRIVER_HPP
