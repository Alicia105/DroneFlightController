#include <iostream>
#include "../include/sensorSaturation.hpp"

using namespace std;

SensorSaturation::SensorSaturation(float min,float max){
   minValue=min;
   maxValue=max;
}

SensorSaturation::~SensorSaturation(){}

float SensorSaturation::applySaturation(float rawValue){
    if(rawValue<minValue){
        return minValue;
    }
    if(rawValue>maxValue){
        return maxValue;
    }
    return rawValue;

}