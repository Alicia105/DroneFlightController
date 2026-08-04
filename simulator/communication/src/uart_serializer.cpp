#include <iostream>
#include <bitset>
#include "../include/uart_serializer.hpp"

using namespace std;

UARTSerializer::UARTSerializer(){}
UARTSerializer::~UARTSerializer(){}

vector<uint8_t> UARTSerializer::serialize(const ImuPacket& packet){
    vector<uint8_t> buffer;
   
    appendUint8(buffer,packet.header);
    appendUint8(buffer,packet.packetID);

    appendUint16(buffer,packet.payloadSize);

    appendUint32(buffer,packet.timestamp);

    appendFloat(buffer,packet.ax);
    appendFloat(buffer,packet.ay);
    appendFloat(buffer,packet.az);
    appendFloat(buffer,packet.wx);
    appendFloat(buffer,packet.wy);
    appendFloat(buffer,packet.wz);

    appendUint16(buffer,packet.checksum);

    return buffer;
}

ImuPacket UARTSerializer::deserialize(const vector<uint8_t>& data){
    ImuPacket packet;
    size_t i=0;
    size_t& index=i;

    packet.header=readUint8(data,index);
    packet.packetID=readUint8(data,index);

    packet.payloadSize=readUint16(data,index);

    packet.timestamp=readUint32(data,index);


    packet.ax=readFloat(data,index);
    packet.ay=readFloat(data,index);
    packet.az=readFloat(data,index);
    packet.wx=readFloat(data,index);
    packet.wy=readFloat(data,index);
    packet.wz=readFloat(data,index);

    packet.checksum=readUint16(data,index);

    return packet;
}

void UARTSerializer::appendUint8(vector<uint8_t>& buffer,uint8_t data){
    buffer.push_back(data);
}

void UARTSerializer::appendUint16(vector<uint8_t>& buffer,uint16_t data){
    uint8_t b0 = data & 0xFF;
    uint8_t b1 = (data >> 8) & 0xFF;

    buffer.push_back(b0);
    buffer.push_back(b1);
}

void UARTSerializer::appendUint32(vector<uint8_t>& buffer,uint32_t data){
    uint8_t b0 = data & 0xFF;
    uint8_t b1 = (data >> 8) & 0xFF;
    uint8_t b2 = (data >> 16) & 0xFF;
    uint8_t b3 = (data >> 24) & 0xFF;

    buffer.push_back(b0);
    buffer.push_back(b1);
    buffer.push_back(b2);
    buffer.push_back(b3);

}

void UARTSerializer::appendFloat(vector<uint8_t>& buffer,float data){
    uint32_t bits;
    memcpy(&bits, &data, sizeof(float));
    appendUint32(buffer,bits);

}

uint8_t UARTSerializer::readUint8(const vector<uint8_t>& buffer, size_t& index){
    index+=1;
    return buffer[index];
}

uint16_t UARTSerializer::readUint16(const vector<uint8_t>& buffer, size_t& index){
    uint8_t b0 = buffer[index];
    uint8_t b1 = buffer[index+1];
    uint16_t bits = ((uint16_t)b1<<8)|(b0 & 0x00FF);
    index+=2;
    return bits;
}

uint32_t UARTSerializer::readUint32(const vector<uint8_t>& buffer, size_t& index){
    uint8_t b0 = buffer[index];
    uint8_t b1 = buffer[index+1];
    uint8_t b2 = buffer[index+2];
    uint8_t b3 = buffer[index+3];
    index+=4;

    uint32_t bits = (((uint32_t)b3<<24)|((uint32_t)b2<<16)|((uint32_t)b1<<8))|(b0 & 0x00FF);
    return bits;
}

float UARTSerializer::readFloat(const vector<uint8_t>& buffer, size_t& index){
    uint32_t bits = readUint32(buffer,index);
    float data;
    memcpy(&data, &bits, sizeof(float));
    return data;
}