#include <iostream>
# include "../include/dronestate.hpp"
# include "../include/estimation.hpp"


//Compute

//to complete
void computePosition(DroneState& drone, const ImuPacket& imu, float dt){
    float g = 9.81;

    float ax = imu.ax;
    float ay = imu.ay;
    float az = imu.az-drone.getWeight()*g;

    drone.setAcceleration(ax,ay,az);

    float vx = ax * dt;
    float vy = ay * dt;
    float vz = az * dt;

    drone.setVelocity(vx,vy,vz);

    float x = vx * dt;//
    float y = vy * dt;//
    float z = vz * dt;//

    drone.setPosition(x,y,z);

    float wx = imu.wx;
    float wy = imu.wy;
    float wz = imu.wz;

    drone.setAngularVelocity(wx,wy,wz);

    float ox = wx * dt;
    float oy = wy * dt;
    float oz = wz * dt;

    drone.setOrientation(ox,oy,oz);

    float awx = wx/dt;
    float awy = wy/dt;
    float awz = wz/dt;

    drone.setAngularAcceleration(awx,awy,awz);

}

/*void DroneState::applyMotorCommand(MotorCommand& commands){
    //   
}*/

DroneState computeError(DroneState& desiredState,DroneState& estimatedState){
    
    float x = desiredState.getPosition()[0]-estimatedState.getPosition()[0];
    float y = desiredState.getPosition()[1]-estimatedState.getPosition()[1];
    float z = desiredState.getPosition()[2]-estimatedState.getPosition()[2];

    float vx = desiredState.getVelocity()[0]-estimatedState.getVelocity()[0];
    float vy = desiredState.getVelocity()[1]-estimatedState.getVelocity()[1];
    float vz = desiredState.getVelocity()[2]-estimatedState.getVelocity()[2];

    float ax = desiredState.getAcceleration()[0]-estimatedState.getAcceleration()[0];
    float ay = desiredState.getAcceleration()[1]-estimatedState.getAcceleration()[1];
    float az = desiredState.getAcceleration()[2]-estimatedState.getAcceleration()[2];

    float ox = desiredState.getOrientation()[0]-estimatedState.getOrientation()[0];
    float oy = desiredState.getOrientation()[1]-estimatedState.getOrientation()[1];
    float oz = desiredState.getOrientation()[2]-estimatedState.getOrientation()[2];

    float wx = desiredState.getAngularVelocity()[0]-estimatedState.getAngularVelocity()[0];
    float wy = desiredState.getAngularVelocity()[1]-estimatedState.getAngularVelocity()[1];
    float wz = desiredState.getAngularVelocity()[2]-estimatedState.getAngularVelocity()[2];

    float awx = desiredState.getAngularAcceleration()[0]-estimatedState.getAngularAcceleration()[0];
    float awy = desiredState.getAngularAcceleration()[1]-estimatedState.getAngularAcceleration()[1];
    float awz = desiredState.getAngularAcceleration()[2]-estimatedState.getAngularAcceleration()[2];
    
    DroneState drone;

    drone.setPosition(x,y,z);
    drone.setVelocity(vx,vy,vz);
    drone.setAcceleration(ax,ay,az);

    drone.setOrientation(ox,oy,oz);
    drone.setAngularVelocity(wx,wy,wz);
    drone.setAngularAcceleration(awx,awy,awz);

}