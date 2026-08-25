#include "../include/controllertask.hpp"


using namespace std;

/**
 * @brief 
    C'est probablement la tâche la plus importante. Elle reçoit les mesures de l'IMU.
    Elle peut ensuite :
    -désérialiser/interpréter les données ;
    -estimer l'état du drone ;
    -comparer l'état actuel à la consigne ;
    -calculer les erreurs ;
    -appliquer les contrôleurs PID ;
    -produire les commandes moteurs.
 * 
 */

void controllerTask(void* parameter){
    auto* params = static_cast<ControllerTaskParameters*>(parameter);

    PacketValidator packetValidator;
    
    UARTDriver& driver = *params->driver;
    DroneState& desiredState = *params->desired;
    DroneState& originalState = *params->original;

    PController pid(3,3,3,3);
    MotorMixer motor;
    
    int i = 0;

    while (true){

        ImuPacket packet = driver.readFreeRTOS();
       
        DroneState estimated;
        DroneState error;

        bool isPacketValid=packetValidator.validate(packet);

        if (isPacketValid){

            estimated.computePosition(packet,0.01f);
            error.computeError(desiredState,estimated);

            vector<float> errorOrientation = error.getOrientation();

            float thrustCorrection = pid.computeThrust(10.0f);
            float rollCorrection = pid.computeRoll(errorOrientation[0]);
            float pitchCorrection = pid.computePitch(errorOrientation[1]);
            float yawCorrection = pid.computeYaw(errorOrientation[2]);
            MotorCommand commands = motor.mix(thrustCorrection,rollCorrection,pitchCorrection,yawCorrection);

            cout<<"[ControllerTask] Commands #"<<i<<" :"<<endl;
            printMotorCommand(commands);

            BaseType_t ok = xQueueSend(motorCommandQueue,&commands,pdMS_TO_TICKS(100));
            i++;

        }
        
    }
}
