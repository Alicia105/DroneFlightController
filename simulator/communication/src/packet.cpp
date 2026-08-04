#include "../include/packet.hpp"
#include "../../sensors/include/imu.hpp"

ImuPacket setFromIMU(IMU& imu){
    ImuPacket packet;
    packet.ax=imu.getAx();
    packet.ay=imu.getAy();
    packet.az=imu.getAz();

    packet.wx=imu.getWx();
    packet.wy=imu.getWy();
    packet.wz=imu.getWz();

    return packet;
}