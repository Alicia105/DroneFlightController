#include "../include/packet_builder.hpp"
#include "../include/packet_validator.hpp"

using namespace std;

PacketValidator::PacketValidator(){}
PacketValidator::~PacketValidator(){}

bool PacketValidator::validate(const ImuPacket& packet){
    return checkHeader(packet)
        && checkPacketID(packet)
        && checkPayloadSize(packet)
        && checkChecksum(packet);
}

bool PacketValidator::checkHeader(const ImuPacket& packet){
    return packet.header == 0xAA;
}

bool PacketValidator::checkPacketID(const ImuPacket& packet){
    switch(static_cast<PacketID>(packet.packetID)){
        case PacketID::IMU:
            return true;
        case PacketID::GPS:
            return true;
        default:
            return false;
    }
}

bool PacketValidator::checkPayloadSize(const ImuPacket& packet){
    return packet.payloadSize == PacketBuilder::computePayloadSize(packet);
}

bool PacketValidator::checkChecksum(const ImuPacket& packet){
    return packet.checksum == PacketBuilder::computeChecksum(packet);
}
