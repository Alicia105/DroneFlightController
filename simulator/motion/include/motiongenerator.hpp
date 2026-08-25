#ifndef MOTIONGENERATOR_HPP
#define MOTIONGENERATOR_HPP
#include "../../../shared/state/include/dronestate.hpp"
#include "../../sensors/include/sensorError.hpp"
#include "../../sensors/include/sensorSaturation.hpp"
class MotionGenerator{
    private :
        float currentTime;
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

        void sinusoidalRoll(DroneState& drone, float amplitude, float frequency); //sinusoidal Pitch
        void sinusoidalPitch(DroneState& drone, float amplitude, float frequency); //sinusoidal Roll 
        void rollAndPitch(DroneState& drone,float rollAmplitude,float pitchAmplitude,float frequency); //sinusoidal Roll + sinusoidal Pitch
        void rollAndYaw(DroneState& drone,float rollAmplitude,float yawAmplitude,float frequency); //sinusoidal Roll + sinusoidal Yaw
        void rollAndPitchAndConstantYaw(DroneState& drone,float rollAmplitude,float pitchAmplitude,float yawRate, float frequency); //sinusoidal Roll + sinusoidalRoll Pitch + constant Yaw
        void rollAndPitchAndYaw(DroneState& drone,float rollAmplitude,float pitchAmplitude,float yawAmplitude, float frequency); //sinusoidal Roll + sinusoidal Pitch + sinusoidal Yaw
       
        void printMotionGeneratorData();
        

        //Takeoff simplifié
        void takeOff(DroneState& drone);

        //landing simplifié
        void landing(DroneState& drone);

        
    void takeoffHoverLandingScenario(DroneState& drone,float r, float p, float y);
    void linearMovementScenario(DroneState& drone,float r, float p, float y);
    void sinusoidalRollScenario(DroneState& drone,float amplitude, float frequency);
    void sinusoidalPitchScenario(DroneState& drone,float amplitude, float frequency);
    void rollAndPitchAndYawScenario(DroneState& drone,float rollAmplitude,float pitchAmplitude,float yawAmplitude, float frequency);
    void constantYawScenario(DroneState& drone,float yawRate);
    void squareScenario(DroneState& drone);

};

#endif // MOTIONGENERATOR_HPP