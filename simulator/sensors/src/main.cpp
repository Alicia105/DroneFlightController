#include <iostream>
#include "../include/accelerometer.hpp"
#include "../include/gyroscope.hpp"
#include "../include/imu.hpp"
#include "../../../shared/state/include/dronestate.hpp"
#include "../include/sensorSaturation.hpp"
#include "../include/sensorError.hpp"
#include "../../motion/include/motiongenerator.hpp"

using namespace std;

int main(){
    float g = 9.81;
    IMU imu;
    DroneState droneState;
    DroneState & drone = droneState;
    MotionGenerator motionGen;
    /*GaussianNoise noise(0.2,0.7);
    cout <<"Gaussian noise = "<<noise.sample()<<endl;

    cout <<"Mean = "<<noise.getMean()<<endl;
    cout<<"Sigma = "<<noise.getSigma()<<endl;
    cout<<"Distribution Mean = "<<noise.getDistribution().mean()<<endl;
    cout<<"Distribution Sigma = "<<noise.getDistribution().stddev()<<endl;

    SensorError s(0.0f,0.05f,0);
    SensorSaturation gyroSat(-250,250);
    SensorSaturation acceleroSat(-2*g,2*g);*/

    /*cout<<"-------------------Initialisation--------------------"<<endl;
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

    cout<<"-------------------Noisy Value--------------------"<<endl;*/

    /*cout<<"-------------------Noisy Value--------------------"<<endl;
    
    droneState.setPosition(1,2,3);
    droneState.setVelocity(1,1,1);*/

    /*cout<<"-------------------Initialisation--------------------"<<endl;
    imu.setAccelSensorSaturation(-2*g,2*g);
    imu.setGyroSensorSaturation(-250,250);
  
    float dt=0.1;
    float simulationTime=1;
    motionGen.setSimulationTime(simulationTime);
    motionGen.setDeltaTime(dt);

    cout<<"--------------------t ="<<motionGen.getSimulationTime()<<" --------------------"<<endl;
    motionGen.printMotionGeneratorData();

    drone.setPosition(1,2,3);
    drone.setVelocity(1,1,1);
    motionGen.update();

    while(motionGen.getCurrentTime()<=motionGen.getSimulationTime()){
        motionGen.constantPitch(drone,3);
        
        cout<<"--------------------t ="<<motionGen.getCurrentTime()<<" --------------------"<<endl;
        motionGen.printMotionGeneratorData();
        cout<<"-------------------Drone--------------------"<<endl;
        drone.printFullDroneStateData();

        cout<<"-------------------IMU--------------------"<<endl;
        imu.updateMeasures(drone);
        imu.printAccelerometerData();
        imu.printGyroscopeData();

        motionGen.update();
        
    }

    cout<<"--------------------t ="<<motionGen.getCurrentTime()<<" --------------------"<<endl;
    motionGen.printMotionGeneratorData();
    cout<<"-------------------Drone--------------------"<<endl;
    drone.printFullDroneStateData();

    cout<<"-------------------IMU--------------------"<<endl;
    imu.updateMeasures(drone);
    imu.printAccelerometerData();
    imu.printGyroscopeData();*/

    return 0;
}