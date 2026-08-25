#include <iostream>
#include <algorithm>
#include <cmath>
#include "../include/motiongenerator.hpp"

using namespace std;

MotionGenerator::MotionGenerator(){
    currentTime=0;
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
    return currentTime;
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
    currentTime+=dt; 
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
    float roll= amplitude*sin(2*M_PI*frequency*currentTime);
    float rollRate = amplitude*2*M_PI*frequency*cos(2*M_PI*frequency*currentTime);
    float rollAcceleration =-amplitude*pow(2*M_PI*frequency,2)*sin(2*M_PI*frequency*currentTime);
    
    drone.setOrientation(roll,0,0);
    drone.setAngularVelocity(rollRate,0,0);    
    drone.setAngularAcceleration(rollAcceleration,0,0);      
}

//Sinusoidal Pitch
void MotionGenerator::sinusoidalPitch(DroneState& drone, float amplitude, float frequency){
    float pitch= amplitude*sin(2*M_PI*frequency*currentTime);
    float pitchRate = amplitude*2*M_PI*frequency*cos(2*M_PI*frequency*currentTime);
    float pitchAcceleration =-amplitude*pow(2*M_PI*frequency,2)*sin(2*M_PI*frequency*currentTime);
    
    drone.setOrientation(0,pitch,0);
    drone.setAngularVelocity(0,pitchRate,0);    
    drone.setAngularAcceleration(0,pitchAcceleration,0);  
}

//Roll + Pitch
void MotionGenerator::rollAndPitch(DroneState& drone,float rollAmplitude,float pitchAmplitude,float frequency){
    float roll = rollAmplitude*sin(2*M_PI*frequency*currentTime);
    float rollRate = rollAmplitude*2*M_PI*frequency*cos(2*M_PI*frequency*currentTime);
    float rollAcceleration = -rollAmplitude*pow(2*M_PI*frequency,2)*sin(2*M_PI*frequency*currentTime);

    float pitch = pitchAmplitude*sin(2*M_PI*frequency*currentTime);
    float pitchRate = pitchAmplitude*2*M_PI*frequency*cos(2*M_PI*frequency*currentTime);
    float pitchAcceleration = -pitchAmplitude*pow(2*M_PI*frequency,2)*sin(2*M_PI*frequency*currentTime);
    
    drone.setOrientation(roll,pitch,0);
    drone.setAngularVelocity(rollRate,pitchRate,0);    
    drone.setAngularAcceleration(rollAcceleration,pitchAcceleration,0);   
}

//Roll + Yaw
void MotionGenerator::rollAndYaw(DroneState& drone,float rollAmplitude,float yawAmplitude,float frequency){
    float roll = rollAmplitude*sin(2*M_PI*frequency*currentTime);
    float rollRate = rollAmplitude*2*M_PI*frequency*cos(2*M_PI*frequency*currentTime);
    float rollAcceleration = -rollAmplitude*pow(2*M_PI*frequency,2)*sin(2*M_PI*frequency*currentTime);

    float yaw = yawAmplitude*sin(2*M_PI*frequency*currentTime);
    float yawRate = yawAmplitude*2*M_PI*frequency*cos(2*M_PI*frequency*currentTime);
    float yawAcceleration = -yawAmplitude*pow(2*M_PI*frequency,2)*sin(2*M_PI*frequency*currentTime);
    
    drone.setOrientation(roll,0,yaw);
    drone.setAngularVelocity(rollRate,0,yawRate);    
    drone.setAngularAcceleration(rollAcceleration,0,yawAcceleration);   
}

//Roll + Pitch + Constant Yaw
void MotionGenerator::rollAndPitchAndConstantYaw(DroneState& drone,float rollAmplitude,float pitchAmplitude,float yawRate, float frequency){
    float roll = rollAmplitude*sin(2*M_PI*frequency*currentTime);
    float rollRate = rollAmplitude*2*M_PI*frequency*cos(2*M_PI*frequency*currentTime);
    float rollAcceleration = -rollAmplitude*pow(2*M_PI*frequency,2)*sin(2*M_PI*frequency*currentTime);

    float pitch = pitchAmplitude*sin(2*M_PI*frequency*currentTime);
    float pitchRate = pitchAmplitude*2*M_PI*frequency*cos(2*M_PI*frequency*currentTime);
    float pitchAcceleration = -pitchAmplitude*pow(2*M_PI*frequency,2)*sin(2*M_PI*frequency*currentTime);

    float yaw = drone.getOrientation()[2]+yawRate*dt;
    
    drone.setOrientation(roll,pitch,yaw);
    drone.setAngularVelocity(rollRate,pitchRate,yawRate);    
    drone.setAngularAcceleration(rollAcceleration,pitchAcceleration,0);   
}

//Roll + Pitch + Yaw
void MotionGenerator::rollAndPitchAndYaw(DroneState& drone,float rollAmplitude,float pitchAmplitude,float yawAmplitude, float frequency){
    float roll = rollAmplitude*sin(2*M_PI*frequency*currentTime);
    float rollRate = rollAmplitude*2*M_PI*frequency*cos(2*M_PI*frequency*currentTime);
    float rollAcceleration = -rollAmplitude*pow(2*M_PI*frequency,2)*sin(2*M_PI*frequency*currentTime);

    float pitch = pitchAmplitude*sin(2*M_PI*frequency*currentTime);
    float pitchRate = pitchAmplitude*2*M_PI*frequency*cos(2*M_PI*frequency*currentTime);
    float pitchAcceleration = -pitchAmplitude*pow(2*M_PI*frequency,2)*sin(2*M_PI*frequency*currentTime);

    float yaw = yawAmplitude*sin(2*M_PI*frequency*currentTime);
    float yawRate = yawAmplitude*2*M_PI*frequency*cos(2*M_PI*frequency*currentTime);
    float yawAcceleration = -yawAmplitude*pow(2*M_PI*frequency,2)*sin(2*M_PI*frequency*currentTime);
    
    drone.setOrientation(roll,pitch,yaw);
    drone.setAngularVelocity(rollRate,pitchRate,yawRate);    
    drone.setAngularAcceleration(rollAcceleration,pitchAcceleration,yawAcceleration);   
}

//Takeoff simplifié
void MotionGenerator::takeOff(DroneState& drone){
    float g=-9.81;
    
    float az = -g;
    float vz = drone.getVelocity()[2] + az*dt;
    float z = drone.getPosition()[2] + drone.getVelocity()[2]*dt+0.5f*az*dt*dt;

    drone.setAcceleration(0,0,az);
    drone.setVelocity(0,0,vz);
    drone.setPosition(0,0,z);
    return;    
}

//landing simplifié
void MotionGenerator::landing(DroneState& drone){
    float g=-9.81;

    float az = g;
    float vz = drone.getVelocity()[2] + az*dt;
    float z = drone.getPosition()[2] + drone.getVelocity()[2]*dt+0.5*az*dt*dt;

    if(z<=0){
        z=0;
        vz=0;
        az=0;
    }

    drone.setAcceleration(0,0,az);
    drone.setVelocity(0,0,vz);
    drone.setPosition(0,0,z);
    return;
  
}

//print
void MotionGenerator::printMotionGeneratorData(){
    cout<<"simulation time : "<<simulationDurationTime<<" s"<<endl;
    cout<<"dt : "<<dt<<" s"<<endl;
    cout<<"current time : "<<currentTime<<" s"<<endl;
}


//scenario

//lands after 12.77s
void MotionGenerator::takeoffHoverLandingScenario(DroneState& drone,float r, float p, float y){
    if(currentTime<=2){
        takeOff(drone);
    }
    if(currentTime>2 && currentTime<10){
        hover(drone,r,p,y);
    }
    if(currentTime>=10){
        landing(drone);
    }
    if(drone.getPosition()[2]==0 && currentTime>=10){
        return;
    }
}

void MotionGenerator::linearMovementScenario(DroneState& drone,float r, float p, float y){
    if(currentTime<=2){
        takeOff(drone);
    }
    if(currentTime>2 && currentTime<=6){
        hover(drone,r,p,y);
    }
    if(currentTime>6 && currentTime<=10){
        vector<float> orientation = drone.getOrientation();
        orientation[1] = orientation[1]-30;
        drone.setOrientation(0,orientation[1],0);
    }
    if(currentTime>10 && currentTime<=15){
        vector<float> position = drone.getPosition();
        vector<float> velocity = drone.getVelocity();
        float vx = 5;
        float x = 5*dt;
        position[0] = position[0] + x;
        velocity[0] = velocity[0]+ vx;
        
        drone.setPosition(position[0],position[1],position[2]);
        drone.setVelocity(velocity[0],0,0);
    }
    if(currentTime>15 && currentTime<=19){
        vector<float> orientation = drone.getOrientation();
        orientation[1] = orientation[1]-30;
        drone.setOrientation(0,orientation[1],0);
    }
    if(currentTime>19 && currentTime<=23){
        hover(drone,r,p,y);
    }
    if(currentTime>23){
        landing(drone);
    }
    if(drone.getPosition()[2]==0 && currentTime>23){
        return;
    }
}

void MotionGenerator::sinusoidalRollScenario(DroneState& drone,float amplitude, float frequency){
    if(currentTime<=2){
        takeOff(drone);
    }
    if(currentTime>2 && currentTime<10){
        sinusoidalRoll(drone,amplitude,frequency);
    }
    if(currentTime>=10){
        landing(drone);
    }
    if(drone.getPosition()[2]==0 && currentTime>=10){
        return;
    }
}

void MotionGenerator::sinusoidalPitchScenario(DroneState& drone,float amplitude, float frequency){
    if(currentTime<=2){
        takeOff(drone);
    }
    if(currentTime>2 && currentTime<10){
        sinusoidalPitch(drone,amplitude,frequency);
    }
    if(currentTime>=10){
        landing(drone);
    }
    if(drone.getPosition()[2]==0 && currentTime>=10){
        return;
    }
}

void MotionGenerator::rollAndPitchAndYawScenario(DroneState& drone,float rollAmplitude,float pitchAmplitude,float yawAmplitude, float frequency){
    if(currentTime<=2){
        takeOff(drone);
    }
    if(currentTime>2 && currentTime<10){
        rollAndPitchAndYaw(drone,rollAmplitude,pitchAmplitude,yawAmplitude,frequency);        
    }
    if(currentTime>=10){
        landing(drone);
    }
    if(drone.getPosition()[2]==0 && currentTime>=10){
        return;
    }
}

void MotionGenerator::constantYawScenario(DroneState& drone,float yawRate){
    if(currentTime<=2){
        takeOff(drone);
    }
    if(currentTime>2 && currentTime<10){
        constantYaw(drone,yawRate);
    }
    if(currentTime>=10){
        landing(drone);
    }
    if(drone.getPosition()[2]==0 && currentTime>=10){
        return;
    }
}

void MotionGenerator::squareScenario(DroneState& drone){
    if(currentTime<=2){
        takeOff(drone);
    }
    if(currentTime>2 && currentTime<=7){
        vector<float> position = drone.getPosition();
        vector<float> velocity = drone.getVelocity();
        vector<float> orientation = drone.getOrientation();
        float vx = 5;
        float x = 5*dt;
        position[0] = position[0] + x;
        velocity[0] = velocity[0]+ vx;
        orientation[2] = orientation[2]-45;

        drone.setOrientation(0,0,orientation[2]);
        drone.setPosition(position[0],position[1],position[2]);
        drone.setVelocity(velocity[0],0,0);
    }
    if(currentTime>7 && currentTime<=12){
        vector<float> position = drone.getPosition();
        vector<float> velocity = drone.getVelocity();
        vector<float> orientation = drone.getOrientation();
        float vy = 5;
        float y = 5*dt;

        position[1] = position[1] + y;
        velocity[1] = velocity[1] + vy; 
        orientation[2] = orientation[2]-45;
        
        drone.setOrientation(0,0,orientation[2]);
        drone.setPosition(position[0],position[1],position[2]);
        drone.setVelocity(0,velocity[1],0);
        
    }
    if(currentTime>12 && currentTime<=17){
        vector<float> position = drone.getPosition();
        vector<float> velocity = drone.getVelocity();
        vector<float> orientation = drone.getOrientation();
        float vx = 5;
        float x = -5*dt;
        position[0] = position[0] + x;
        velocity[0] = velocity[0]+ vx;
        orientation[2] = orientation[2]-45;
        
        drone.setOrientation(0,0,orientation[2]);
        drone.setPosition(position[0],position[1],position[2]);
        drone.setVelocity(velocity[0],0,0);
    }
    if(currentTime>17 && currentTime<=22){
        vector<float> position = drone.getPosition();
        vector<float> velocity = drone.getVelocity();
        vector<float> orientation = drone.getOrientation();
        float vy = 5;
        float y = -5*dt;

        position[1] = position[1] + y;
        velocity[1] = velocity[1] + vy; 
        orientation[2] = orientation[2]-45;
        
        drone.setOrientation(0,0,orientation[2]);
        drone.setPosition(position[0],position[1],position[2]);
        drone.setVelocity(0,velocity[1],0);
    }
    if(currentTime>22){
        landing(drone);
    }
    if(drone.getPosition()[2]==0 && currentTime>22){
        return;
    }
}
