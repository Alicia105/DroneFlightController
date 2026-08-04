#define CATCH_CONFIG_MAIN
#include <iostream>
#include <iomanip>
#include <bitset>
#include <cstdint>
#include "../../../external/include/catch_amalgamated.hpp"
#include "../../sensors/include/imu.hpp"
#include "../../sensors/include/sensorError.hpp"
#include "../../sensors/include/sensorSaturation.hpp"
#include "../../motion/include/motiongenerator.hpp"
#include "../include/packet.hpp"
#include "../include/uart_serializer.hpp"

using Catch::Matchers::WithinAbs;
using namespace std;

TEST_CASE("IMU Data packet", "[Packet]") {
    IMU imu;
    imu.setAx(1);
    imu.setAy(2);
    imu.setAz(5.5);

    imu.setWx(7.8);
    imu.setWy(12);
    imu.setWz(2);

    ImuPacket packet;

    packet.header=0xAA;
    packet.packetID=0x01;
    packet.payloadSize=0x0A01;

    packet.timestamp=0x00111101;
    
    packet.checksum=0x0B02;

    REQUIRE(packet.header == 0xAA);
    REQUIRE(packet.packetID == 0x01);
    REQUIRE(packet.payloadSize == 0x0A01);
    REQUIRE(packet.timestamp == 0x00111101);


    REQUIRE(packet.ax == 1);
    REQUIRE(packet.ay == 2);
    REQUIRE(packet.az == 5.5);

    REQUIRE(packet.wx == 7.8);
    REQUIRE(packet.wy == 12);
    REQUIRE(packet.wz == 2);

    REQUIRE(packet.checksum == 0x0B02);
}

TEST_CASE("Convert packet to bytes", "[UART Serializer]") {
    ImuPacket packet;
    UARTSerializer serializer;

    packet.header=0xAA;
    packet.packetID=0x01;
    packet.payloadSize=0x0A01;

    packet.timestamp=0x00111101;

    packet.ax=1;
    packet.ay=2;
    packet.az=5.5;

    packet.wx=7.8;
    packet.wy=12;
    packet.wz=2;
    
    packet.checksum=0x0B02;

    auto bytes = serializer.serialize(packet);
    
    REQUIRE(original.header == );
    REQUIRE(original.packetID == );
    REQUIRE(original.timestamp == );

    REQUIRE_THAT(,WithinAbs(10 * 2 * M_PI,1e-4))

    REQUIRE_THAT(original.ax,WithinAbs(10 * 2 * M_PI,1e-4));
    REQUIRE_THAT(original.ay,WithinAbs(10 * 2 * M_PI,1e-4));
    REQUIRE_THAT(original.ax,WithinAbs(10 * 2 * M_PI,1e-4));

    REQUIRE_THAT(original.wx,WithinAbs(10 * 2 * M_PI,1e-4));
    REQUIRE_THAT(original.wy,WithinAbs(10 * 2 * M_PI,1e-4));
    REQUIRE_THAT(original.wz,WithinAbs(10 * 2 * M_PI,1e-4));
}

TEST_CASE("Convert bytes to packet", "[UART Serializer]") {
    ImuPacket packet;
    UARTSerializer serializer;

    auto bytes = serializer.serialize(packet);
    auto reconstructed = serializer.deserialize(bytes);

    REQUIRE(original.header == reconstructed.header);
    REQUIRE(original.packetID == reconstructed.packetID);
    REQUIRE(original.timestamp == reconstructed.timestamp);

    REQUIRE(original.ax == Approx(reconstructed.ax));
    REQUIRE(original.ay == Approx(reconstructed.ay));
    REQUIRE(original.ax == Approx(reconstructed.ax));

    REQUIRE(original.ay == Approx(reconstructed.wx));
    REQUIRE(original.ax == Approx(reconstructed.wy));
    REQUIRE(original.ay == Approx(reconstructed.wz));
}

TEST_CASE("Convert packet to bytes and back", "[UART Serializer]") {
    ImuPacket original;
    UARTSerializer serializer;

    original.header=0xAA;
    original.packetID=0x01;
    original.payloadSize=0x0A01;

    original.timestamp=0x00111101;

    original.ax=1;
    original.ay=2;
    original.az=5.5;

    original.wx=7.8;
    original.wy=12;
    original.wz=2;
    
    original.checksum=0x0B02;

    auto bytes = serializer.serialize(original);
    auto reconstructed = serializer.deserialize(bytes);

    REQUIRE(original.header == reconstructed.header);
    REQUIRE(original.packetID == reconstructed.packetID);
    REQUIRE(original.timestamp == reconstructed.timestamp);

    REQUIRE_THAT(original.ax,WithinAbs(reconstructed.ax,1e-6));
    REQUIRE_THAT(original.ay,WithinAbs(reconstructed.ay,1e-6));
    REQUIRE_THAT(original.ax,WithinAbs(reconstructed.az,1e-6));

    REQUIRE_THAT(original.wx,WithinAbs(reconstructed.wx,1e-6));
    REQUIRE_THAT(original.wy,WithinAbs(reconstructed.wy,1e-6));
    REQUIRE_THAT(original.wz,WithinAbs(reconstructed.wz,1e-6));

    REQUIRE_THAT(original.checksum,WithinAbs(reconstructed.checksum,1e-6));
}