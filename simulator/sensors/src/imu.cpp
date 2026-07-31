#include <iostream>
#include "../include/imu.hpp"



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

SensorError IMU::getAccelSensorError(){ 
    return accelSensorErr;
}

SensorSaturation IMU::getAccelSensorSaturation(){
    return accelSensorSat;
}

SensorError IMU::getGyroSensorError(){ 
    return gyroSensorErr;
}

SensorSaturation IMU::getGyroSensorSaturation(){
    return gyroSensorSat;
}

//setter
void IMU::setRate(float x){
    rate=x;
}

void IMU::setAccelSensorError(float mean,float sigma,float b){ 
    accelSensorErr.configure(mean,sigma,b);
    
}

void IMU::setAccelSensorSaturation(float min,float max){
    accelSensorSat.setMinSaturation(min);
    accelSensorSat.setMaxSaturation(max);
   
}

void IMU::setGyroSensorError(float mean,float sigma,float b){ 
    gyroSensorErr.configure(mean,sigma,b);
    
}

void IMU::setGyroSensorSaturation(float min,float max){
    gyroSensorSat.setMinSaturation(min);
    gyroSensorSat.setMaxSaturation(max);
}

//check
void IMU::updateMeasures(DroneState& drone){
    
    setAx(accelSensorSat.applySaturation(accelSensorErr.apply(drone.getAcceleration()[0])));
    setAy(accelSensorSat.applySaturation(accelSensorErr.apply(drone.getAcceleration()[1])));
    setAz(accelSensorSat.applySaturation(accelSensorErr.apply(drone.getAcceleration()[2])));

    setWx(gyroSensorSat.applySaturation(gyroSensorErr.apply(drone.getAngularVelocity()[0])));
    setWy(gyroSensorSat.applySaturation(gyroSensorErr.apply(drone.getAngularVelocity()[1])));
    setWz(gyroSensorSat.applySaturation(gyroSensorErr.apply(drone.getAngularVelocity()[2])));

}



//write function to send datas via UART

//write function to send datas via I2C