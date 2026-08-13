#ifndef PACKET_HPP
#define PACKET_HPP

#include <iostream>
#include <iomanip>
#include <cstdint>
#include "../../../simulator/sensors/include/imu.hpp"

constexpr size_t IMU_PACKET_SIZE = 34;

typedef struct ImuPacket{

    uint8_t header;      // 0xAA
    uint8_t packetID;    // 0x01 = IMU
    uint16_t payloadSize;

    uint32_t timestamp;

    float ax;
    float ay;
    float az;

    float wx;
    float wy;
    float wz;
    
    uint16_t checksum;
    
}ImuPacket;

ImuPacket setFromIMU(IMU& imu);

void printFloatBytes(float value);
void printImuPacket(const ImuPacket& packet);
void printImuPacketAsBytes(const ImuPacket& packet);

#endif //PACKET_HPP
