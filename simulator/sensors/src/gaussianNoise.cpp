#include <iostream>
#include "../include/gaussianNoise.hpp"

using namespace std; 

GaussianNoise::GaussianNoise(float m,float s){
    mean=m;
    sigma=s;
    random_device rd;
    mt19937 generator(rd());

    normal_distribution<float> distribution(mean, sigma);
}

GaussianNoise::GaussianNoise(){}
GaussianNoise::~GaussianNoise(){}

//getters
float GaussianNoise::getMean(){
    return mean;
}

float GaussianNoise::getSigma(){
    return sigma;
}

normal_distribution<float> GaussianNoise::getDistribution(){
    return distribution;
}

float GaussianNoise::sample(){
    return distribution(generator);
}