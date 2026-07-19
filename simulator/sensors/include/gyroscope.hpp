#ifndef GYROSCOPE_HPP
#define GYROSCOPE_HPP

class Gyroscope {
    private:
        float wx, wy, wz; // Gyroscope readings in x, y, z axes
    public :
        Gyroscope();
        ~Gyroscope();

        // Setters
        void setWx(float x);
        void setWy(float y);
        void setWz(float z);

        // Getters
        float getWx();
        float getWy();
        float getWz();

        void printGyroscopeData();

       
};

#endif // GYROSCOPE_HPP