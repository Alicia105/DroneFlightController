#define CATCH_CONFIG_MAIN
#include <iostream>
#include <vector>
#include "../../../external/include/catch_amalgamated.hpp"
#include "../../sensors/include/imu.hpp"
#include "../include/packet.hpp"
#include "../include/uart_serializer.hpp"

using Catch::Matchers::WithinAbs;
using namespace std;


TEST_CASE("IMU Data fields", "[Packet]") {
    IMU i;
    IMU& imu=i;

    imu.setAx(1);
    imu.setAy(2);
    imu.setAz(5.5);

    imu.setWx(7.8);
    imu.setWy(12);
    imu.setWz(2);

    ImuPacket packet=setFromIMU(imu);

    packet.header=0xAA;
    packet.packetID=0x01;
    packet.payloadSize=28;

    packet.timestamp=0x00111101;
    
    packet.checksum=0x0B02;


    REQUIRE(packet.header == 0xAA);
    REQUIRE(packet.packetID == 0x01);
    REQUIRE(packet.payloadSize == 28);
    REQUIRE(packet.timestamp == 0x00111101);


    REQUIRE_THAT(packet.ax, WithinAbs(1.0f,1e-6));
    REQUIRE_THAT(packet.ay, WithinAbs(2.0f,1e-6));
    REQUIRE_THAT(packet.az, WithinAbs(5.5f,1e-6));

    REQUIRE_THAT(packet.wx, WithinAbs(7.8f,1e-6));
    REQUIRE_THAT(packet.wy, WithinAbs(12.0f,1e-6));
    REQUIRE_THAT(packet.wz, WithinAbs(2.0f,1e-6));

    REQUIRE(packet.checksum == 0x0B02);
}

TEST_CASE("appendUint32()", "[UART Serializer]")
{
    UARTSerializer serializer;

    vector<uint8_t> buffer;

    serializer.appendUint32(buffer,0x12345678);

    REQUIRE(buffer.size()==4);

    REQUIRE(buffer[0]==0x78);
    REQUIRE(buffer[1]==0x56);
    REQUIRE(buffer[2]==0x34);
    REQUIRE(buffer[3]==0x12);
}

TEST_CASE("readUint32()", "[UART Serializer]")
{
    UARTSerializer serializer;

    vector<uint8_t> buffer = {0x78,0x56,0x34,0x12};

    size_t index = 0;

    uint32_t value = serializer.readUint32(buffer,index);

    REQUIRE(value == 0x12345678);
    REQUIRE(index == 4);
}

TEST_CASE("Serialize packet", "[UART Serializer]")
{
    UARTSerializer serializer;

    ImuPacket packet{};

    packet.header = 0xAA;
    packet.packetID = 0x01;
    packet.payloadSize = 28;

    packet.timestamp = 0x00111101;

    packet.ax = 1.0f;
    packet.ay = 2.0f;
    packet.az = 5.5f;

    packet.wx = 7.8f;
    packet.wy = 12.0f;
    packet.wz = 2.0f;

    packet.checksum = 0x0B02;

    auto bytes = serializer.serialize(packet);

    REQUIRE(bytes.size() == 34);

    REQUIRE(bytes[0] == 0xAA);
    REQUIRE(bytes[1] == 0x01);

    REQUIRE(bytes[2] == 28);
    REQUIRE(bytes[3] == 0x00);

    REQUIRE(bytes[4] == 0x01);
    REQUIRE(bytes[5] == 0x11);
    REQUIRE(bytes[6] == 0x11);
    REQUIRE(bytes[7] == 0x00);
}

TEST_CASE("Deserialize packet", "[UART Serializer]")
{
    UARTSerializer serializer;

    ImuPacket original{};

    original.header = 0xAA;
    original.packetID = 0x01;
    original.payloadSize = 28;

    original.timestamp = 0x00111101;

    original.ax = 1.0f;
    original.ay = 2.0f;
    original.az = 5.5f;

    original.wx = 7.8f;
    original.wy = 12.0f;
    original.wz = 2.0f;

    original.checksum = 0x0B02;

    auto bytes = serializer.serialize(original);

    ImuPacket reconstructed = serializer.deserialize(bytes);

    REQUIRE(original.header == reconstructed.header);
    REQUIRE(original.packetID == reconstructed.packetID);
    REQUIRE(original.payloadSize == reconstructed.payloadSize);
    REQUIRE(original.timestamp == reconstructed.timestamp);

    REQUIRE_THAT(original.ax, WithinAbs(reconstructed.ax,1e-6));
    REQUIRE_THAT(original.ay, WithinAbs(reconstructed.ay,1e-6));
    REQUIRE_THAT(original.az, WithinAbs(reconstructed.az,1e-6));

    REQUIRE_THAT(original.wx, WithinAbs(reconstructed.wx,1e-6));
    REQUIRE_THAT(original.wy, WithinAbs(reconstructed.wy,1e-6));
    REQUIRE_THAT(original.wz, WithinAbs(reconstructed.wz,1e-6));

    REQUIRE(original.checksum == reconstructed.checksum);
}

TEST_CASE("Serialize then Deserialize", "[UART Serializer]")
{
    UARTSerializer serializer;

    ImuPacket original{};

    original.header = 0xAA;
    original.packetID = 0x01;
    original.payloadSize = 28;

    original.timestamp = 0x00111101;

    original.ax = 1.0f;
    original.ay = 2.0f;
    original.az = 5.5f;

    original.wx = 7.8f;
    original.wy = 12.0f;
    original.wz = 2.0f;

    original.checksum = 0x0B02;

    auto bytes = serializer.serialize(original);

    auto reconstructed = serializer.deserialize(bytes);

    REQUIRE(original.header == reconstructed.header);
    REQUIRE(original.packetID == reconstructed.packetID);
    REQUIRE(original.payloadSize == reconstructed.payloadSize);
    REQUIRE(original.timestamp == reconstructed.timestamp);

    REQUIRE_THAT(original.ax, WithinAbs(reconstructed.ax,1e-6));
    REQUIRE_THAT(original.ay, WithinAbs(reconstructed.ay,1e-6));
    REQUIRE_THAT(original.az, WithinAbs(reconstructed.az,1e-6));

    REQUIRE_THAT(original.wx, WithinAbs(reconstructed.wx,1e-6));
    REQUIRE_THAT(original.wy, WithinAbs(reconstructed.wy,1e-6));
    REQUIRE_THAT(original.wz, WithinAbs(reconstructed.wz,1e-6));

    REQUIRE(original.checksum == reconstructed.checksum);
}