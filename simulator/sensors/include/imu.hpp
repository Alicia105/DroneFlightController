#ifndef IMU_HPP
#define IMU_HPP
#include "gyroscope.hpp"
#include "accelerometer.hpp"
#include "dronestate.hpp"

class IMU : public Gyroscope, public Accelerometer {
    // IMU class implementation
    private:
    
    float rate; // frequency of measurement (Hz)
       
    public:
        IMU();
        ~IMU();

        //getter
        float getRate();

        //setter
        void setRate(float x);

        void updateMeasures(DroneState drone);
};
#endif // IMU_HPP