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
    
    PacketValidator packetValidator;
    auto* params = static_cast<CommunicationTaskParameters*>(parameter);
    UARTDriver& driver = *params->driver;
    int i = 0;

    while (true){
        ImuPacket packet = driver.readFreeRTOS();
        MotorCommand commands{};

        DroneState estimated;
        DroneState desiredState;

        desiredState.setPosition(3,3,3);
        //desiredState.setVelocity(1,2,3);
        //desiredState.setAcceleration(1,2,3);

        desiredState.setOrientation(10,2,3);
        //desiredState.setAngularVelocity(1,2,3);
        //desiredState.setAngularAcceleration(1,2,3);

        bool isPacketValid=packetValidator.validate(packet);

        /*if(isPacketValid){
            cout << "[Controller] IMU received" << endl;

            cout << "[Controller] Before command calculation" << endl;

            commands.motor1 = 10.0f;
            commands.motor2 = 0.5f;
            commands.motor3 = 0.7f;
            commands.motor4 = 3.4f;

            cout << "[Controller] Before xQueueSend" << endl;

            BaseType_t ok = xQueueSend(
                motorCommandQueue,
                &commands,
                pdMS_TO_TICKS(100)
            );

            cout << "[Controller] After xQueueSend : " << ok << endl;
            /*cout<< "[Controller] IMU #"<<i<<": ax=" << packet.ax<< " ay=" << packet.ay<< " az=" << packet.az<< " wx=" << packet.wx<< " wy=" << packet.wy<< " wz=" << packet.wz<<endl;
            commands.motor1 = 10.0f;
            commands.motor2 = 0.5f;
            commands.motor3 = 0.7f;
            commands.motor4 = 3.4f;

            cout << "[ControllerTask] Before xQueueSend" << endl;
            BaseType_t ok = xQueueSend(motorCommandQueue,&commands,pdMS_TO_TICKS(100));
            cout << "[Controller] After send : " << ok << endl;

            //xQueueSend(motorCommandQueue,&commands,portMAX_DELAY);
            //cout << "[ControllerTask] After xQueueSend" << endl;
            cout << "[ControllerTask] Sending commands #"<<i<<" ..." << endl;
            i++;
            vTaskDelay(pdMS_TO_TICKS(20));

        }*/
        
        if (isPacketValid){
            cout << "[Controller] 1" << endl;

            //xSemaphoreTake(droneStateMutex, portMAX_DELAY);
            computePosition(estimated,packet,0.01f);
            DroneState error = computeError(desiredState,estimated);
            //xSemaphoreGive(droneStateMutex);

            MotorCommand commands{};

            cout << "[Controller] 2" << endl;

            commands.motor1 = 10.0f;
            commands.motor2 = 0.5f;
            commands.motor3 = 0.7f;
            commands.motor4 = 3.4f;

            cout << "[Controller] 3" << endl;

            BaseType_t ok = xQueueSend(motorCommandQueue,&commands,pdMS_TO_TICKS(100));

            cout << "[Controller] 4 : " << ok << endl;
        }
        
    }
}
