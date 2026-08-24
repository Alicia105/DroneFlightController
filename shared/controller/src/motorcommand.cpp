#include <iostream>
#include "../include/motorcommand.hpp"

using namespace std;

void printMotorCommand(const  MotorCommand& command){

    cout << "Motor 1 : " << command.motor1 << endl;
    cout << "Motor 2 : " << command.motor2 << endl;
    cout << "Motor 3 : " << command.motor3 << endl;
    cout << "Motor 4 : " << command.motor4 << endl;

}
