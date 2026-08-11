#define CATCH_CONFIG_MAIN
#include <iostream>
#include <vector>
#include "../../../external/include/catch_amalgamated.hpp"
#include "../../sensors/include/imu.hpp"
#include "../include/packet.hpp"
#include "../include/uart_serializer.hpp"
#include "../include/virtual_uart.hpp"

using Catch::Matchers::WithinAbs;
using namespace std;

TEST_CASE("UART Channel implementaion", "[UART Channel]"){
    VirtualUART channel;
    REQUIRE(channel.size()==0);
    REQUIRE(channel.getBaudRate()==115200);
    channel.setBaudRate(1152);
    REQUIRE(channel.getBaudRate()==1152);    
}

TEST_CASE("1 byte transmission via UART Channel", "[UART Channel]"){
    VirtualUART channel;
    channel.transmitByte(0xAA);
    REQUIRE(channel.receiveByte()==0xAA);
}

TEST_CASE("Several bytes transmission via UART Channel", "[UART Channel]"){
    VirtualUART channel;

    vector<uint8_t> buffer = {0x78,0x56,0x34,0x12};
    size_t index = 4;
    size_t ind = 2;

    channel.transmit(buffer);
    vector<uint8_t> b=channel.receive(index);

    REQUIRE(b.size()==index);
    REQUIRE(buffer[0]==b[0]);
    REQUIRE(buffer[1]==b[1]);
    REQUIRE(buffer[2]==b[2]);
    REQUIRE(buffer[3]==b[3]);

    channel.transmit(buffer);
    vector<uint8_t> a=channel.receive(ind);

    REQUIRE(a.size()==ind);
    REQUIRE(buffer[0]==a[0]);
    REQUIRE(buffer[1]==a[1]);
        
}

TEST_CASE("UART Channel size", "[UART Channel]"){
    VirtualUART channel;
    REQUIRE(channel.size()==0);
    channel.transmitByte(0xAA);
    REQUIRE(channel.size()==1);    
   
}

TEST_CASE("UART Channel available for transmission", "[UART Channel]"){
    VirtualUART channel;
    REQUIRE(channel.dataAvailable()==false);
    channel.transmitByte(0xAA);
    REQUIRE(channel.dataAvailable()==true);    
}