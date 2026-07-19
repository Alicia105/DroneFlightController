#include <iostream>
#include "../include/accelerometer.hpp"
#include "../include/gyroscope.hpp"
#include "../include/imu.hpp"
#include "../include/dronestate.hpp"

using namespace std;

int main() {
    IMU imu;
    DroneState droneState;
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
    droneState.setAcceleration(3,2,1);
    droneState.setAngularVelocity(2,2,2);
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