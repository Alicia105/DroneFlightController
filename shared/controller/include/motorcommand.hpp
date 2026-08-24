#ifndef MOTORCOMMAND_HPP
#define MOTORCOMMAND_HPP

typedef struct MotorCommand
{
    float motor1;
    float motor2;
    float motor3;
    float motor4;
}MotorCommand;

void printMotorCommand(const  MotorCommand& command);

#endif // MOTORCOMMAND_HPP