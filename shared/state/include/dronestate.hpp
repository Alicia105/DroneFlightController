#ifndef DRONESTATE_HPP
#define DRONESTATE_HPP

#include <vector>


class DroneState {
    // DroneState class implementation
    private:
        float weight; //in kg
        std::vector<float> position;
        std::vector<float> velocity;
        std::vector<float> acceleration;

        std::vector<float> orientation;
        std::vector<float> angularVelocity;
        std::vector<float> angularAcceleration;
        

    public:
        DroneState();
        ~DroneState();

        //Setters
        void setPosition(float x, float y, float z);
        void setVelocity(float x, float y, float z);
        void setAcceleration(float x, float y, float z);

        void setOrientation(float x, float y, float z);
        void setAngularVelocity(float x, float y, float z);
        void setAngularAcceleration(float x, float y, float z);

        void setWeight(float w);

        std::vector<float> getPosition();
        std::vector<float> getVelocity();
        std::vector<float> getAcceleration();
        std::vector<float> getOrientation();
        std::vector<float> getAngularVelocity();
        std::vector<float> getAngularAcceleration();
        float getWeight();
        
        void printPosition();
        void printVelocity();
        void printAcceleration();
        void printOrientation();
        void printAngularVelocity();
        void printAngularAcceleration();
        void printFullDroneStateData();

        //void computePosition(const ImuPacket& imu,float dt);
        //void applyMotorCommand(MotorCommand& commands);
        void computeError(const DroneState& desiredState, const DroneState& estimatedState);
        //void applyMotorCommand(MotorCommand& commands);

};


#endif // DRONESTATE_HPP