#include <iostream>
#include "../include/accelerometer.hpp"

using namespace std;

Accelerometer::Accelerometer() : ax(0), ay(0), az(0) {}
Accelerometer::~Accelerometer() {}

//setters
void Accelerometer::setAx(float x) { ax = x; }
void Accelerometer::setAy(float y) { ay = y; }
void Accelerometer::setAz(float z) { az = z; }

//getters
float Accelerometer::getAx() { return ax; }
float Accelerometer::getAy()  { return ay; }
float Accelerometer::getAz()  { return az; }

void Accelerometer::printAccelerometerData(){
    cout<<"Accelerometer : Ax = "<<ax<<" , Ay = "<<ay<<", Az = "<<az<<endl;
}

