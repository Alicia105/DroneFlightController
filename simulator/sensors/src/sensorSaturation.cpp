#include <iostream>
#include "../include/sensorSaturation.hpp"

using namespace std;

SensorSaturation::SensorSaturation(): minValue(0),maxValue(0){
}

SensorSaturation::SensorSaturation(float min,float max){
   minValue=min;
   maxValue=max;
}

SensorSaturation::~SensorSaturation(){}

//getters
float SensorSaturation::getMinSaturation(){
   return minValue;
}

float SensorSaturation::getMaxSaturation(){
    return maxValue;
}

//setters

void SensorSaturation::setMinSaturation(float min){
    minValue = min;
}

void SensorSaturation::setMaxSaturation(float max){
    maxValue = max;
}

float SensorSaturation::applySaturation(float rawValue){
    if(rawValue<minValue){
        return minValue;
    }
    if(rawValue>maxValue){
        return maxValue;
    }
    return rawValue;

}