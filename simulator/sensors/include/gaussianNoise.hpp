#ifndef GAUSSIAN_NOISE_HPP
#define GAUSSIAN_NOISE_HPP

#include <iostream>
#include <ctime>
#include <random>

class GaussianNoise {

    private:

    std::mt19937 generator;
    std::normal_distribution<float> distribution;

    public:
    GaussianNoise();
    GaussianNoise(float mean,float sigma);
    ~GaussianNoise();
    float sample();

};
#endif //GAUSSIAN_NOISE_HPP