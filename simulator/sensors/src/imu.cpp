#include <iostream>
#include "../include/imu.hpp"
#include "../include/dronestate.hpp"

using namespace std;

IMU::IMU():Accelerometer(),Gyroscope(){
    rate = 100; //by default
}

IMU::~IMU() {
    // Destructor implementation
}

//getter
float IMU::getRate(){
    return rate;
}

//setter
void IMU::setRate(float x){
    rate=x;
}

//check
void IMU::updateMeasures(DroneState drone){
    setAx(drone.getAcceleration()[0]);
    setAy(drone.getAcceleration()[1]);
    setAz(drone.getAcceleration()[2]);

    setWx(drone.getAngularVelocity()[0]);
    setWy(drone.getAngularVelocity()[1]);
    setWz(drone.getAngularVelocity()[2]);

}

//write function to send datas via UART

//write function to send datas via I2C