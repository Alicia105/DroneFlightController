#define CATCH_CONFIG_MAIN
#include <iostream>
#include <vector>
#include "../../../../external/Catch2/include/catch_amalgamated.hpp"
#include "../../../../shared/communication/include/packet.hpp"
#include "../../../sensors/include/imu.hpp"
#include "../include/uart_serializer.hpp"
#include "../include/virtual_uart.hpp"
#include "../include/packet_builder.hpp"

using Catch::Matchers::WithinAbs;
using namespace std;

TEST_CASE("Packet Builder implementaion", "[Packet Builder]"){
    PacketBuilder builder;
    IMU imu;
    imu.setAx(1);
    imu.setAy(2);
    imu.setAz(5.5);

    imu.setWx(7.8);
    imu.setWy(12);
    imu.setWz(2);

    ImuPacket packet=builder.createImuPacket(imu);

    REQUIRE(packet.header == 0xAA);
    REQUIRE(packet.packetID == 0x01);
    REQUIRE(packet.payloadSize == PacketBuilder::computePayloadSize(packet));

    REQUIRE_THAT(packet.ax, WithinAbs(1,1e-6));
    REQUIRE_THAT(packet.ay, WithinAbs(2,1e-6));
    REQUIRE_THAT(packet.az, WithinAbs(5.5,1e-6));

    REQUIRE_THAT(packet.wx, WithinAbs(7.8,1e-6));
    REQUIRE_THAT(packet.wy, WithinAbs(12,1e-6));
    REQUIRE_THAT(packet.wz, WithinAbs(2,1e-6));

    REQUIRE(packet.checksum == PacketBuilder::computeChecksum(packet));
    
}
