#include <iostream>
#include "../include/gaussianNoise.hpp"
#include "../include/sensorError.hpp"

using namespace std;

SensorError::SensorError(float mean,float sigma,float b): noise(mean,sigma),bias(b){
    
}

SensorError::~SensorError(){}

void SensorError::configure(float mean,float sigma,float bias){
    noise.configure(mean,sigma);
    this->bias = bias;
}

float SensorError::apply(float rawValue){
    return rawValue+bias+noise.sample();
}