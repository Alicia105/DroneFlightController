#include <iostream>
#include "../include/motormixer.hpp"

using namespace std;

MotorMixer::MotorMixer(){}

MotorMixer::~MotorMixer(){}

MotorCommand MotorMixer::mix(float thrust, float rollCorrection, float pitchCorrection, float yawCorrection){
    MotorCommand command;
    command.motor1 = thrust+rollCorrection+pitchCorrection+yawCorrection;
    command.motor2 = thrust-rollCorrection+pitchCorrection-yawCorrection;
    command.motor3 = thrust-rollCorrection-pitchCorrection+yawCorrection;
    command.motor4 = thrust+rollCorrection-pitchCorrection-yawCorrection;
    return command;
}