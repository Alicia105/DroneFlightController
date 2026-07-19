#ifndef SENSOR_ERROR_HPP
#define SENSOR_ERROR_HPP

#include "gaussianNoise.hpp"

class SensorError{
    private :
        float bias;
        GaussianNoise noise;

    public : 
        
        SensorError(float mean = 0,float sigma=0.05,float bias = 0);
        ~SensorError();
        float apply(float rawValue);

};
#endif //SENSOR_ERROR_HPP

