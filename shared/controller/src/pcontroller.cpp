#include <iostream>
#include "../include/pcontroller.hpp"

PController::PController(){
    Kp_throttle = 0;
    Kp_roll = 0;
    Kp_pitch = 0;
    Kp_yaw = 0;
}

PController::PController(float t, float r, float p, float y){
    Kp_throttle = t;
    Kp_roll = r;
    Kp_pitch = p;
    Kp_yaw = y;
}

PController::~PController(){}

//getters
float PController::getThrottle(){
    return Kp_throttle;
}

float PController::getRoll(){
    return Kp_roll;
}

float PController::getPitch(){
    return Kp_pitch;
}

float PController::getYaw(){
    return Kp_yaw;
}

//setters
void PController::setThrottle(float t){
    Kp_throttle = t;
}

void PController::setRoll(float r){
    Kp_roll = r;
}

void PController::setPitch(float p){
    Kp_pitch = p;
}

void PController::setYaw(float y){
    Kp_yaw = y;
}


float PController::computeThrottle(float error){
    return Kp_throttle * error;
}

float PController::computeRoll(float error){
    return Kp_roll * error;
}

float PController::computePitch(float error){
    return Kp_pitch * error;
}

float PController::computeYaw(float error){
    return Kp_yaw * error;
}