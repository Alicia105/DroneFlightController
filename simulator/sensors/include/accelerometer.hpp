#ifndef ACCELEROMETER_HPP
#define ACCELEROMETER_HPP

class Accelerometer {
    private:
        float ax, ay, az; // Accelerometer readings in x, y, z axes
    public :
        Accelerometer();
        ~Accelerometer();

        // Setters
        void setAx(float x);
        void setAy(float y);
        void setAz(float z);

        // Getters
        float getAx();
        float getAy();
        float getAz();

        void printAccelerometerData();
};

#endif // ACCELEROMETER_HPP