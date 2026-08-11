#define CATCH_CONFIG_MAIN
#include <iostream>
#include <vector>
#include "../../../external/include/catch_amalgamated.hpp"
#include "../../sensors/include/imu.hpp"
#include "../include/packet.hpp"
#include "../include/uart_serializer.hpp"
#include "../include/virtual_uart.hpp"
#include "../include/packet_builder.hpp"
#include "../include/packet_validator.hpp"

using Catch::Matchers::WithinAbs;
using namespace std;

TEST_CASE("Packet Validator implementaion", "[Packet Validator]"){
    PacketBuilder builder;
    IMU imu;
    imu.setAx(1);
    imu.setAy(2);
    imu.setAz(5.5);

    imu.setWx(7.8);
    imu.setWy(12);
    imu.setWz(2);

    ImuPacket packet=builder.createImuPacket(imu);
    PacketValidator validator;

    REQUIRE(validator.checkHeader(packet));
    REQUIRE(validator.checkPacketID(packet));
    REQUIRE(validator.checkPayloadSize(packet));
    REQUIRE(validator.checkChecksum(packet));
    REQUIRE(validator.validate(packet));    
}
