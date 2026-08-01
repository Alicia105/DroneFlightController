#ifndef MOTIONGENERATOR_HPP
#define MOTIONGENERATOR_HPP
#include "../../../shared/state/include/dronestate.hpp"
#include "../../sensors/include/sensorError.hpp"
#include "../../sensors/include/sensorSaturation.hpp"
class MotionGenerator{
    private :
        float currenTime;
        float dt;
        float simulationDurationTime;     

    public :
        MotionGenerator();
        ~MotionGenerator();

        float getDeltaTime();
        float getSimulationTime();
        float getCurrentTime();

        void setDeltaTime(float deltaTime);
        void setSimulationTime(float simuTime);
        
        void update();

        void hover(DroneState& state,float r, float p, float y);
        void constantRoll(DroneState& drone,float rollRate);
        void constantPitch(DroneState& drone,float pitchRate);
        void constantYaw(DroneState& drone,float yawRate);

        void sinusoidalRoll(DroneState& drone, float amplitude, float frequency);
        void sinusoidalPitch(DroneState& drone, float amplitude, float frequency);
        void RollAndPitch(DroneState& drone,float rollAmplitude,float pitchAmplitude,float frequency);
        void printMotionGeneratorData();
        

        //Takeoff simplifié
        void takeOff(DroneState& drone);

        //landing simplifié
        void landing(DroneState& drone);
};

#endif // MOTIONGENERATOR_HPP