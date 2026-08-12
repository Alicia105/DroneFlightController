#define CATCH_CONFIG_MAIN
#include <iostream>
#include <vector>
#include "../../../../external/Catch2/include/catch_amalgamated.hpp"
#include "../../../sensors/include/imu.hpp"
#include "../../../../shared/communication/include/packet.hpp"
#include "../include/uart_serializer.hpp"
#include "../include/virtual_uart.hpp"
#include "../include/uart_driver.hpp"

using Catch::Matchers::WithinAbs;
using namespace std;

TEST_CASE("Transmission via UART Driver", "[UART Driver]"){
    VirtualUART ch;
    VirtualUART& channel=ch;
    UARTDriver driver(channel);

    ImuPacket packet{};

    packet.header = 0xAA;
    packet.packetID = 0x01;
    packet.payloadSize = 24;

    packet.timestamp = 0x00111101;

    packet.ax = 1.0f;
    packet.ay = 2.0f;
    packet.az = 5.5f;

    packet.wx = 7.8f;
    packet.wy = 12.0f;
    packet.wz = 2.0f;

    packet.checksum = 0x0B02;

    driver.write(packet);
    REQUIRE(channel.size()==IMU_PACKET_SIZE);
  
}

TEST_CASE("Reading via UART Driver", "[UART Driver]"){
    VirtualUART ch;
    VirtualUART& channel=ch;
    UARTDriver driver(channel);
    UARTSerializer serializer;

    ImuPacket packet{};

    packet.header = 0xAA;
    packet.packetID = 0x01;
    packet.payloadSize = 24;

    packet.timestamp = 0x00111101;

    packet.ax = 1.0f;
    packet.ay = 2.0f;
    packet.az = 5.5f;

    packet.wx = 7.8f;
    packet.wy = 12.0f;
    packet.wz = 2.0f;

    packet.checksum = 0x0B02;

    vector<uint8_t> buffer = serializer.serialize(packet);
    channel.transmit(buffer);
    ImuPacket pck = driver.read();

    REQUIRE(channel.size()==0);

}

TEST_CASE("Transmission and Reading back via UART Driver", "[UART Driver]"){
    VirtualUART ch;
    VirtualUART& channel=ch;
    UARTDriver driver(channel);

    ImuPacket packet{};

    packet.header = 0xAA;
    packet.packetID = 0x01;
    packet.payloadSize = 24;

    packet.timestamp = 0x00111101;

    packet.ax = 1.0f;
    packet.ay = 2.0f;
    packet.az = 5.5f;

    packet.wx = 7.8f;
    packet.wy = 12.0f;
    packet.wz = 2.0f;

    packet.checksum = 0x0B02;

    driver.write(packet);
    REQUIRE(channel.size()==IMU_PACKET_SIZE);
    ImuPacket pck = driver.read();

    REQUIRE(packet.header == pck.header);
    REQUIRE(packet.packetID == pck.packetID);
    REQUIRE(packet.payloadSize == pck.payloadSize);
    REQUIRE(packet.timestamp == pck.timestamp);

    REQUIRE_THAT(packet.ax, WithinAbs(pck.ax,1e-6));
    REQUIRE_THAT(packet.ay, WithinAbs(pck.ay,1e-6));
    REQUIRE_THAT(packet.az, WithinAbs(pck.az,1e-6));

    REQUIRE_THAT(packet.wx, WithinAbs(pck.wx,1e-6));
    REQUIRE_THAT(packet.wy, WithinAbs(pck.wy,1e-6));
    REQUIRE_THAT(packet.wz, WithinAbs(pck.wz,1e-6));

    REQUIRE(packet.checksum == pck.checksum);

}