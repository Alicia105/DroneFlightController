#ifndef PACKET_HPP
#define PACKET_HPP

#include <iostream>
#include <cstdint>
#include "../../sensors/include/imu.hpp"

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

#endif //PACKET_HPP
