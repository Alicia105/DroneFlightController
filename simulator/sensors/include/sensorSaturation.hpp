#ifndef SENSOR_SATURATION_HPP
#define SENSOR_SATURATION_HPP

class SensorSaturation{
    private :
        float minValue;
        float maxValue;

    public : 
        
        SensorSaturation(float min,float max);
        ~SensorSaturation();
        float applySaturation(float rawValue);

};
#endif //SENSOR_ERROR_HPP

