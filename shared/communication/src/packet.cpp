#include "../include/packet.hpp"

using namespace std;

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

void printFloatBytes(float value){
    uint8_t* bytes = reinterpret_cast<uint8_t*>(&value);

    for(int i = 0; i < sizeof(float); ++i){
        cout << "0x"
                  << hex
                  << uppercase
                  << setw(2)
                  << setfill('0')
                  << static_cast<int>(bytes[i])
                  << " ";
    }

    cout << dec << endl;
}

void printImuPacket(const ImuPacket& packet){
    /*using hex;
    using dec;
    using setw;
    using setfill;*/

    //cout << "========== IMU Packet ==========" << endl;

    cout << "Header : 0x"
         << hex << uppercase
         << setw(2) << setfill('0')
         << static_cast<int>(packet.header)
         << dec << endl;

    cout << "Packet ID : 0x"
         << hex
         << setw(2)
         << static_cast<int>(packet.packetID)
         << dec << endl;

    cout << "PayloadSize : "
         << packet.payloadSize
         << " bytes (0x"
         << hex << setw(4)
         << packet.payloadSize
         << dec << ")" << endl;

    cout << "Timestamp : "
         << packet.timestamp
         << " (0x"
         << hex << setw(8)
         << packet.timestamp
         << dec << ")" << endl;

    cout << "ax : " << packet.ax << endl;
    cout << "ay : " << packet.ay << endl;
    cout << "az : " << packet.az << endl;

    cout << "wx : " << packet.wx << endl;
    cout << "wy : " << packet.wy << endl;
    cout << "wz : " << packet.wz << endl;

    cout << "Checksum : 0x"
         << hex << setw(4)
         << packet.checksum
         << dec << endl;

    //cout << "===============================" << endl;
}

void printImuPacketAsBytes(const ImuPacket& packet){
    /*using hex;
    using dec;
    using setw;
    using setfill;*/

    //cout << "========== IMU Packet ==========" << endl;

    cout << "Header : 0x"
         << hex << uppercase
         << setw(2) << setfill('0')
         << static_cast<int>(packet.header)
         << dec << endl;

    cout << "Packet ID : 0x"
         << hex
         << setw(2)
         << static_cast<int>(packet.packetID)
         << dec << endl;

    cout << "PayloadSize : "
         << packet.payloadSize
         << " bytes (0x"
         << hex << setw(4)
         << packet.payloadSize
         << dec << ")" << endl;

    cout << "Timestamp : "
         << packet.timestamp
         << " (0x"
         << hex << setw(8)
         << packet.timestamp
         << dec << ")" << endl;

    printFloatBytes(packet.ax);
    printFloatBytes(packet.ay);
    printFloatBytes(packet.az);

    printFloatBytes(packet.wx);
    printFloatBytes(packet.wy);
    printFloatBytes(packet.wz);

    cout << "Checksum : 0x"
         << hex << setw(4)
         << packet.checksum
         << dec << endl;

    //cout << "===============================" << endl;
}

