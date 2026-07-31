#include <iostream>
#include "../include/gaussianNoise.hpp"

using namespace std; 

GaussianNoise::GaussianNoise(float mean,float sigma): mean(mean),sigma(sigma),generator(random_device{}()), distribution(mean, sigma){
}

GaussianNoise::GaussianNoise(){}
GaussianNoise::~GaussianNoise(){}

//setters
void GaussianNoise::configure(float mean,float sigma)
{
    this->mean = mean;
    this->sigma = sigma;

    distribution = normal_distribution<float>(mean,sigma);
}

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