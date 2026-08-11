#include "../include/packet_builder.hpp"

PacketBuilder::PacketBuilder(){}
PacketBuilder::~PacketBuilder(){}

ImuPacket PacketBuilder::createImuPacket(IMU& imu){
    ImuPacket packet=setFromIMU(imu);
    packet.header = generateHeader();
    packet.packetID = generatePacketID(PacketID::IMU);
    packet.timestamp = generateTimestamp();
    packet.payloadSize = computePayloadSize(packet);
    packet.checksum = computeChecksum(packet);
    return packet;
}

uint8_t PacketBuilder::generateHeader(){
    return 0xAA;
}

uint8_t PacketBuilder::generatePacketID(PacketID id){
    return static_cast<uint8_t>(id);
}

uint32_t PacketBuilder::generateTimestamp(){
    static uint32_t timestamp = 0;
    timestamp += 10;
    return timestamp;
}

uint16_t PacketBuilder::computePayloadSize(const ImuPacket& packet){
    return sizeof(uint32_t)+ 6*sizeof(float);
}

uint16_t PacketBuilder::computeChecksum(const ImuPacket& packet){
    const uint8_t* bytes = reinterpret_cast<const uint8_t*>(&packet);
    uint16_t checksum = 0;
    for(size_t i = 0; i < offsetof(ImuPacket, checksum); ++i)
    {
        checksum += bytes[i];
    }

    return checksum;
}


        
