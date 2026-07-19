#include <iostream>
#include "../include/gaussianNoise.hpp"
#include "../include/sensorError.hpp"

using namespace std;

SensorError::SensorError(float mean,float sigma,float b){
    GaussianNoise noise(mean,sigma);
    bias=b;
}

SensorError::~SensorError(){}

float SensorError::apply(float rawValue){
    return rawValue+bias+noise.sample();

}