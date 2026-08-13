#ifndef UART_CHANNEL_HPP
#define UART_CHANNEL_HPP

#include <iostream>
#include <vector>
#include <queue>
#include "../../../../shared/communication/include/packet.hpp"
#include "../../../external/FreeRTOS/Source/include/FreeRTOS.h"
#include "../../../external/FreeRTOS/Source/include/semphr.h"
#include "uart_serializer.hpp"


class UARTChannel{//transport bytes
    private :
        //UARTSerializer serializer;
        std::queue<uint8_t> txBuffer;
        QueueHandle_t txQueue;
        uint32_t baudRate;       

    public :
        UARTChannel();
        UARTChannel(QueueHandle_t& queue);
        ~UARTChannel();

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

        //via FreeRTOS

        void transmitByteFreeRTOS(uint8_t data);

        uint8_t receiveByteFreeRTOS();

        void transmitFreeRTOS(std::vector<uint8_t>& data);

        std::vector<uint8_t> receiveFreeRTOS();

};

#endif //UART_CHANNEL_HPP
