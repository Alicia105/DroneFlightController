#include <iostream>
#include "../include/dronestate.hpp"

using namespace std;

DroneState::DroneState() {
    position = vector<float>(3, 0); // Initialize position to (0, 0, 0)
    velocity = vector<float>(3, 0); //vx,vy,vz
    acceleration = vector<float>(3, 0); //ax,ay,az
    angularVelocity = vector<float>(3, 0); //wx,wy,wz
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

void DroneState::setAngularVelocity(float x, float y, float z) {
    angularVelocity[0]=x;
    angularVelocity[1]=y;
    angularVelocity[2]=z;
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

vector<float> DroneState::getAngularVelocity() {
    return angularVelocity;

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

void DroneState::printAngularVelocity(){
    cout<<"Angular Velocity : Wx = "<<angularVelocity[0]<<" , Wy = "<<angularVelocity[1]<<", Wz = "<<angularVelocity[2]<<endl;
}