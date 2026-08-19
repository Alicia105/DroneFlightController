#ifndef IMU_HPP
#define IMU_HPP
#include "gyroscope.hpp"
#include "accelerometer.hpp"
#include "../../../shared/state/include/dronestate.hpp"
#include "sensorSaturation.hpp"
#include "sensorError.hpp"

class IMU : public Gyroscope, public Accelerometer {
    // IMU class implementation
    private:
        SensorError accelSensorErr;
        SensorSaturation accelSensorSat;

        SensorError gyroSensorErr;
        SensorSaturation gyroSensorSat;
    
        float rate; // frequency of measurement (Hz)
       
    public:
        IMU();
        ~IMU();

        //getter
        float getRate();
        SensorError getAccelSensorError();
        SensorSaturation getAccelSensorSaturation();
        SensorError getGyroSensorError();
        SensorSaturation getGyroSensorSaturation();

        //setter
        void setRate(float x);
        void setAccelSensorSaturation(float min,float max);
        void setAccelSensorError(float mean,float sigma,float b);      
        
        void setGyroSensorSaturation(float min,float max);
        void setGyroSensorError(float mean,float sigma,float b);

        void updateMeasures(DroneState& drone);

        
};
#endif // IMU_HPP