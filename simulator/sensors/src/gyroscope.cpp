#include <iostream>
#include "../include/gyroscope.hpp"

using namespace std;

Gyroscope::Gyroscope() : wx(0), wy(0), wz(0) {}
Gyroscope::~Gyroscope() {}

//setters-all check
void Gyroscope::setWx(float x) { wx = x; }
void Gyroscope::setWy(float y) { wy = y; }
void Gyroscope::setWz(float z) { wz = z; }

//getters-all check
float Gyroscope::getWx() { return wx; }
float Gyroscope::getWy() { return wy; }
float Gyroscope::getWz() { return wz; }

void Gyroscope::printGyroscopeData(){
    cout<<"Gyroscope : Wx = "<<wx<<" , Wy = "<<wy<<", Wz = "<<wz<<endl;
}
