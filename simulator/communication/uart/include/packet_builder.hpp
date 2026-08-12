#ifndef PACKET_BUILDER_HPP
#define PACKET_BUILDER_HPP

#include <iostream>
#include <iomanip>
#include <cstdint>
#include <cstddef>
#include "../../../sensors/include/imu.hpp"
#include "../../../../shared/communication/include/packet.hpp"

enum class PacketID : uint8_t
{
    IMU = 0x01,
    GPS = 0x02
};

class PacketBuilder{
    private:
    public :
        PacketBuilder();
        ~PacketBuilder();

        ImuPacket createImuPacket(IMU& imu);

        uint8_t generateHeader();

        uint8_t generatePacketID(PacketID id);

        uint32_t generateTimestamp();

        static uint16_t computePayloadSize(const ImuPacket& packet);

        static uint16_t computeChecksum(const ImuPacket& packet);

};

#endif //PACKET_BUILDER_HPP
