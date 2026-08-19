#include <iostream>
#include <cmath>
#include "../include/dronestate.hpp"

using namespace std;

DroneState::DroneState():weight(0) {
    position = vector<float>(3, 0); // Initialize position to (0, 0, 0)
    velocity = vector<float>(3, 0); //vx,vy,vz
    acceleration = vector<float>(3, 0); //ax,ay,az

    orientation = vector<float>(3, 0); //ox,oy,oz
    angularVelocity = vector<float>(3, 0); //wx,wy,wz
    angularAcceleration = vector<float>(3, 0); //awx,awy,awz
}

DroneState::~DroneState() {

}

//Setters-all check
void DroneState::setPosition(float x, float y, float z) {
    position[0]=x;
    position[1]=y;
    position[2]=z;
}

void DroneState::setVelocity(float x, float y, float z) {
    velocity[0]=x;
    velocity[1]=y;
    velocity[2]=z;
}

void DroneState::setAcceleration(float x, float y, float z) {
    acceleration[0]=x;
    acceleration[1]=y;
    acceleration[2]=z;
}

void DroneState::setOrientation(float x, float y, float z) {
    orientation[0]=x;
    orientation[1]=y;
    orientation[2]=z;
}

void DroneState::setAngularVelocity(float x, float y, float z) {
    angularVelocity[0]=x;
    angularVelocity[1]=y;
    angularVelocity[2]=z;
}

void DroneState::setAngularAcceleration(float x, float y, float z) {
    angularAcceleration[0]=x;
    angularAcceleration[1]=y;
    angularAcceleration[2]=z;
}

void DroneState::setWeight(float w) {
    weight=w;
}


//Getters-all check
vector<float> DroneState::getPosition() {
    return position;

}

vector<float> DroneState::getVelocity() {
    return velocity;

}

vector<float> DroneState::getAcceleration() {
    return acceleration;

}

vector<float> DroneState::getOrientation() {
    return orientation;

}

vector<float> DroneState::getAngularVelocity() {
    return angularVelocity;

}

vector<float> DroneState::getAngularAcceleration() {
    return angularAcceleration;

}

float DroneState::getWeight() {
    return weight;
}

//Print-all check
void DroneState::printPosition(){
    cout<<"Position : X = "<<position[0]<<" , Y = "<<position[1]<<", Z = "<<position[2]<<endl;
}

void DroneState::printVelocity(){
    cout<<"Velocity : Vx = "<<velocity[0]<<" , Vy = "<<velocity[1]<<", Vz = "<<velocity[2]<<endl;
}

void DroneState::printAcceleration(){
    cout<<"Acceleration : Ax = "<<acceleration[0]<<" , Ay = "<<acceleration[1]<<", Az = "<<acceleration[2]<<endl;
}

void DroneState::printOrientation(){
    cout<<"Orientation : roll(Ox) = "<<orientation[0]<<" , pitch(Oy) = "<<orientation[1]<<", yaw(Oz) = "<<orientation[2]<<endl;
}

void DroneState::printAngularVelocity(){
    cout<<"Angular Velocity : Wx = "<<angularVelocity[0]<<" , Wy = "<<angularVelocity[1]<<", Wz = "<<angularVelocity[2]<<endl;
}

void DroneState::printAngularAcceleration(){
    cout<<"Angular Acceleration : awx = "<<angularAcceleration[0]<<" , awy = "<<angularAcceleration[1]<<", awz = "<<angularAcceleration[2]<<endl;
}

void DroneState::printFullDroneStateData(){
    cout<<"Position : X = "<<position[0]<<" , Y = "<<position[1]<<", Z = "<<position[2]<<endl;
    cout<<"Velocity : Vx = "<<velocity[0]<<" , Vy = "<<velocity[1]<<", Vz = "<<velocity[2]<<endl;
    cout<<"Acceleration : Ax = "<<acceleration[0]<<" , Ay = "<<acceleration[1]<<", Az = "<<acceleration[2]<<endl;
    cout<<"Orientation : roll(Ox) = "<<orientation[0]<<" , pitch(Oy) = "<<orientation[1]<<", yaw(Oz) = "<<orientation[2]<<endl;
    cout<<"Angular Velocity : Wx = "<<angularVelocity[0]<<" , Wy = "<<angularVelocity[1]<<", Wz = "<<angularVelocity[2]<<endl;
    cout<<"Angular Acceleration : awx = "<<angularAcceleration[0]<<" , awy = "<<angularAcceleration[1]<<", awz = "<<angularAcceleration[2]<<endl;
}


float DroneState::normalizeAngle(float angle){
    angle = fmod(angle + 180.0f, 360.0f);

    if (angle < 0)
        angle += 360.0f;

    return angle - 180.0f;
}

void DroneState::computePosition(const ImuPacket& imu, float dt){

    vector<float> oldPosition = getPosition();
    vector<float> oldVelocity = getVelocity();
    vector<float> oldOrientation = getOrientation();
    vector<float> oldAngularVelocity = getAngularVelocity();

    float ax = imu.ax;
    float ay = imu.ay;
    float az = imu.az;

    setAcceleration(ax,ay,az);
    
    float vx = oldVelocity[0]+ax * dt;
    float vy = oldVelocity[1]+ay * dt;
    float vz = oldVelocity[2]+az * dt;

    setVelocity(vx,vy,vz);

    float x = oldPosition[0]+oldVelocity[0]*dt+0.5f*ax*dt*dt;
    float y = oldPosition[1]+oldVelocity[1]*dt+0.5f*ay*dt*dt;
    float z = oldPosition[2]+oldVelocity[2]*dt+0.5f*az*dt*dt;

    setPosition(x,y,z);

    float wx = imu.wx;
    float wy = imu.wy;
    float wz = imu.wz;

    setAngularVelocity(wx,wy,wz);

    float ox = oldOrientation[0]+wx * dt;
    float oy = oldOrientation[1]+wy * dt;
    float oz = oldOrientation[2]+wz * dt;

    setOrientation(normalizeAngle(ox),normalizeAngle(oy),normalizeAngle(oz));

    float awx = (wx-oldAngularVelocity[0])/dt;
    float awy = (wy-oldAngularVelocity[1])/dt;
    float awz = (wz-oldAngularVelocity[2])/dt;

    setAngularAcceleration(awx,awy,awz);

}

void DroneState::computeError(DroneState& desiredState,DroneState& estimatedState){
    
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

    setPosition(x,y,z);
    setVelocity(vx,vy,vz);
    setAcceleration(ax,ay,az);

    //setOrientation(ox,oy,oz);
    setOrientation(normalizeAngle(ox),normalizeAngle(oy),normalizeAngle(oz));
    setAngularVelocity(wx,wy,wz);
    setAngularAcceleration(awx,awy,awz);

}


/*void DroneState::applyMotorCommand(MotorCommand& commands){
    //   
}*/