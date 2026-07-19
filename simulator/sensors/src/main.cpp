#include <iostream>
#include "../include/accelerometer.hpp"
#include "../include/gyroscope.hpp"
#include "../include/imu.hpp"
#include "../include/dronestate.hpp"
#include "../include/sensorSaturation.hpp"
#include "../include/sensorError.hpp"

using namespace std;

int main() {
    float g = 9.81;
    IMU imu;
    DroneState droneState;
    GaussianNoise noise(0.0,0.05);
    cout <<"Gaussian noise = "<<noise.sample()<<endl;
    SensorError s(0.0f,0.05f,0);
    SensorSaturation gyroSat(-250,250);
    SensorSaturation acceleroSat(-2*g,2*g);

    cout<<"-------------------Initialisation--------------------"<<endl;
    droneState.printPosition();
    droneState.printVelocity();
    droneState.printAcceleration();
    droneState.printAngularVelocity();
    imu.printAccelerometerData();
    imu.printGyroscopeData();

    cout<<"-------------------Update--------------------"<<endl;
    
    droneState.setPosition(1,2,3);
    droneState.setVelocity(1,1,1);
    droneState.setAcceleration(-30,2,30);
    droneState.setAngularVelocity(-300,2,300);
    
    droneState.printPosition();
    droneState.printVelocity();
    droneState.printAcceleration();
    droneState.printAngularVelocity();

    cout<<"-------------------Noisy Value--------------------"<<endl;

    droneState.setPosition(1,2,3);
    droneState.setVelocity(1,1,1);
    droneState.setAcceleration(acceleroSat.applySaturation(s.apply(-30)),acceleroSat.applySaturation(s.apply(2)),acceleroSat.applySaturation(s.apply(30)));
    droneState.setAngularVelocity(gyroSat.applySaturation(s.apply(-300)),gyroSat.applySaturation(s.apply(2)),gyroSat.applySaturation(s.apply(300)));
    droneState.printPosition();
    droneState.printVelocity();
    droneState.printAcceleration();
    droneState.printAngularVelocity();   

    cout<<"-------------------IMU--------------------"<<endl;
    
    imu.updateMeasures(droneState);
    imu.printAccelerometerData();
    imu.printGyroscopeData();

    return 0;
}