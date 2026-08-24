#include <iostream>
#include <algorithm>
#include <cmath>
#include "../include/motiongenerator.hpp"

using namespace std;

MotionGenerator::MotionGenerator(){
    currenTime=0;
    simulationDurationTime=0;
    dt=0;
}

MotionGenerator::~MotionGenerator(){

}

//getters

float MotionGenerator::getDeltaTime(){
    return dt;
}

float MotionGenerator::getSimulationTime(){
    return simulationDurationTime;
}

float MotionGenerator::getCurrentTime(){
    return currenTime;
}

//setters
void MotionGenerator::setDeltaTime(float deltaTime){
    dt=deltaTime;
}

void MotionGenerator::setSimulationTime(float simuTime){
    simulationDurationTime=simuTime;
}

//update
void MotionGenerator::update(){
    currenTime+=dt; 
}

//scenarios

//hover (stationery)
void MotionGenerator::hover(DroneState& drone,float r, float p, float y){
    drone.setVelocity(0,0,0);
    drone.setAcceleration(0,0,0);
    drone.setOrientation(r,p,y);
    drone.setAngularVelocity(0,0,0);
    drone.setAngularAcceleration(0,0,0);
}

//Constant Roll
void MotionGenerator::constantRoll(DroneState& drone,float rollRate){
    float roll = drone.getOrientation()[0]+rollRate*dt;
    drone.setOrientation(roll,0,0);
    drone.setAngularVelocity(rollRate,0,0);
    drone.setAngularAcceleration(0,0,0);
}

//Constant Pitch
void MotionGenerator::constantPitch(DroneState& drone,float pitchRate){
    float pitch = drone.getOrientation()[1]+pitchRate*dt;
    drone.setOrientation(0,pitch,0);
    drone.setAngularVelocity(0,pitchRate,0);
    drone.setAngularAcceleration(0,0,0);
}

//Constant yaw
void MotionGenerator::constantYaw(DroneState& drone,float yawRate){
    float yaw = drone.getOrientation()[2]+yawRate*dt;
    drone.setOrientation(0,0,yaw);
    drone.setAngularVelocity(0,0,yawRate);
    drone.setAngularAcceleration(0,0,0);
}

//Sinusoidal Roll
void MotionGenerator::sinusoidalRoll(DroneState& drone, float amplitude, float frequency){
    float roll= amplitude*sin(2*M_PI*frequency*currenTime);
    float rollRate = amplitude*2*M_PI*frequency*cos(2*M_PI*frequency*currenTime);
    float rollAcceleration =-amplitude*pow(2*M_PI*frequency,2)*sin(2*M_PI*frequency*currenTime);
    
    drone.setOrientation(roll,0,0);
    drone.setAngularVelocity(rollRate,0,0);    
    drone.setAngularAcceleration(rollAcceleration,0,0);      
}

//Sinusoidal Pitch
void MotionGenerator::sinusoidalPitch(DroneState& drone, float amplitude, float frequency){
    float pitch= amplitude*sin(2*M_PI*frequency*currenTime);
    float pitchRate = amplitude*2*M_PI*frequency*cos(2*M_PI*frequency*currenTime);
    float pitchAcceleration =-amplitude*pow(2*M_PI*frequency,2)*sin(2*M_PI*frequency*currenTime);
    
    drone.setOrientation(0,pitch,0);
    drone.setAngularVelocity(0,pitchRate,0);    
    drone.setAngularAcceleration(0,pitchAcceleration,0);  
}

//Roll + Pitch
void MotionGenerator::RollAndPitch(DroneState& drone,float rollAmplitude,float pitchAmplitude,float frequency){
    float roll = rollAmplitude*sin(2*M_PI*frequency*currenTime);
    float rollRate = rollAmplitude*2*M_PI*frequency*cos(2*M_PI*frequency*currenTime);
    float rollAcceleration = -rollAmplitude*pow(2*M_PI*frequency,2)*sin(2*M_PI*frequency*currenTime);

    float pitch = pitchAmplitude*sin(2*M_PI*frequency*currenTime);
    float pitchRate = pitchAmplitude*2*M_PI*frequency*cos(2*M_PI*frequency*currenTime);
    float pitchAcceleration = -pitchAmplitude*pow(2*M_PI*frequency,2)*sin(2*M_PI*frequency*currenTime);
    
    drone.setOrientation(roll,pitch,0);
    drone.setAngularVelocity(rollRate,pitchRate,0);    
    drone.setAngularAcceleration(rollAcceleration,pitchAcceleration,0);   
}

//Takeoff simplifié
void MotionGenerator::takeOff(DroneState& drone){
    float g=-9.81;
    if(currenTime<=2){
        float az = -g;
        float vz = drone.getVelocity()[2] + az*dt;
        float z = drone.getPosition()[2] + drone.getVelocity()[2]*dt+0.5f*az*dt*dt;

        drone.setAcceleration(0,0,az);
        drone.setVelocity(0,0,vz);
        drone.setPosition(0,0,z);
        return;
    }
    else{
        float az = 0;
        float vz = drone.getVelocity()[2] + az*dt;
        float z = drone.getPosition()[2] + drone.getVelocity()[2]*dt+0.5f*az*dt*dt;

        drone.setAcceleration(0,0,az);
        drone.setVelocity(0,0,vz);
        drone.setPosition(0,0,z);
        return;
    }
    
}

//landing simplifié
void MotionGenerator::landing(DroneState& drone){
    if(currenTime>=2){
        float az = -1;
        float vz = drone.getVelocity()[2] + az*dt;
        float z = drone.getPosition()[2] + vz*dt;

        drone.setAcceleration(0,0,az);
        drone.setVelocity(0,0,vz);
        drone.setPosition(0,0,z);
        return;
    }
    else{
        float az = 0;
        float vz = drone.getVelocity()[2] + az*dt;
        float z = drone.getPosition()[2] + vz*dt;

        if(z<0){
            z=0;
        }

        drone.setAcceleration(0,0,az);
        drone.setVelocity(0,0,vz);
        drone.setPosition(0,0,z);
        return;
    }
    
}


void MotionGenerator::printMotionGeneratorData(){
    cout<<"simulation time : "<<simulationDurationTime<<" s"<<endl;
    cout<<"dt : "<<dt<<" s"<<endl;
    cout<<"current time : "<<currenTime<<" s"<<endl;
}
