#ifndef DRONESTATE_HPP
#define DRONESTATE_HPP

#include <vector>

class DroneState {
    // DroneState class implementation
    private:
        std::vector<float> position;
        std::vector<float> velocity;
        std::vector<float> acceleration;
        std::vector<float> angularVelocity;

    public:
        DroneState();
        ~DroneState();

        //Setters
        void setPosition(float x, float y, float z);
        void setVelocity(float x, float y, float z);
        void setAcceleration(float x, float y, float z);
        void setAngularVelocity(float x, float y, float z);

        std::vector<float> getPosition();
        std::vector<float> getVelocity();
        std::vector<float> getAcceleration();
        std::vector<float> getAngularVelocity();      
        
        void printPosition();
        void printVelocity();
        void printAcceleration();
        void printAngularVelocity();

};


#endif // DRONESTATE_HPP