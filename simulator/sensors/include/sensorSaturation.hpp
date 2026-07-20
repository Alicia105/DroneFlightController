#ifndef SENSOR_SATURATION_HPP
#define SENSOR_SATURATION_HPP

class SensorSaturation{
    private :
        float minValue;
        float maxValue;

    public : 
        SensorSaturation();
        SensorSaturation(float min,float max);
        ~SensorSaturation();

        //getters
        float getMinSaturation();
        float getMaxSaturation();

        //setters

        void setMinSaturation(float min);
        void setMaxSaturation(float max);

        float applySaturation(float rawValue);

};
#endif //SENSOR_ERROR_HPP

