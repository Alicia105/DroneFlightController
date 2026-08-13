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
    (void)parameter;
    PacketValidator packetValidator;

    while (true){
        //xSemaphoreTake(UARTMutex, portMAX_DELAY);
        ImuPacket packet = driver1.readFreeRTOS();
        //xSemaphoreGive(UARTMutex);   
        
        bool isPacketValid=packetValidator.validate(packet);
            if(isPacketValid){
                cout<< "[Controller] IMU: "<< "ax=" << packet.ax<< " ay=" << packet.ay<< " az=" << packet.az<< "wx=" << packet.wx<< " wy=" << packet.wy<< " wz=" << packet.wz<<endl;
            }      
        cout << "[ControllerTask] Updating controller ..." << endl;
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}
