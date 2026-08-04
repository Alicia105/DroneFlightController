#ifndef VIRTUAL_UART_HPP
#define VIRTUAL_UART_HPP

#include <iostream>
#include <vector>
#include "../include/packet.hpp"

class VirtualUART{
    private :

    public :
        VirtualUART();
        ~VirtualUART();
        bool send(std::vector<uint8_t>& data);
        bool receive(std::vector<uint8_t>& data);

};

#endif //VIRTUAL_UART_HPP