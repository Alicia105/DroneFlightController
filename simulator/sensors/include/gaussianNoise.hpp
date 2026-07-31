#ifndef GAUSSIAN_NOISE_HPP
#define GAUSSIAN_NOISE_HPP

#include <iostream>
#include <ctime>
#include <random>

class GaussianNoise {

    private:
    float mean;
    float sigma;
    std::mt19937 generator;
    std::normal_distribution<float> distribution;

    public:
    GaussianNoise();
    GaussianNoise(float mean,float sigma);
    ~GaussianNoise();

    void configure(float mean,float sigma);

    //getters
    float getMean();
    float getSigma();

    std::normal_distribution<float> getDistribution();

    float sample();

};
#endif //GAUSSIAN_NOISE_HPP