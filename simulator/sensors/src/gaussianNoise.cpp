#include <iostream>
#include "../include/gaussianNoise.hpp"

using namespace std; 

GaussianNoise::GaussianNoise(float mean,float sigma){
    random_device rd;
    mt19937 generator(rd());
    normal_distribution<float> distribution(mean, sigma);
}

GaussianNoise::~GaussianNoise(){}

float GaussianNoise::sample(){
    return distribution(generator);
}