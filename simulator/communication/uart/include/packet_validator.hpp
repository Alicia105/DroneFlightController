#ifndef PACKET_VALIDATOR_HPP
#define PACKET_VALIDATOR_HPP

#include <iostream>
#include <iomanip>
#include <cstdint>
#include "../../../sensors/include/imu.hpp"
#include "../../../../shared/communication/include/packet.hpp"


class PacketValidator{
    private:
    public:
        PacketValidator();
        ~PacketValidator();

        bool validate(const ImuPacket& packet);

        bool checkHeader(const ImuPacket& packet);

        bool checkPacketID(const ImuPacket& packet);

        bool checkPayloadSize(const ImuPacket& packet);

        bool checkChecksum(const ImuPacket& packet);
};

#endif //PACKET_VALIDATOR_HPP
