#include "../include/physicstask.hpp"

using namespace std;


/*
Cette tâche représente le travail qui serait effectué par le microcontrôleur pour récupérer les données des capteurs.
*/
void physicsTask(void* parameter){
    
    auto* param =static_cast<PhysicsTaskParameters*>(parameter);

    IMU& imu = *param->imu;
    MotionGenerator& motionGen = *param->motionGen;
    DroneState& drone = *param->droneState;

    PacketBuilder builder;
    PacketValidator packetValidator;
    int i = 0;

    while (true){
        xSemaphoreTake(droneStateMutex, portMAX_DELAY);
        motionGen.hover(drone,30,0,0);
        imu.updateMeasures(drone);
        //cout << "[PhysicsTask] Drone state :";
        //drone.printFullDroneStateData();
        xSemaphoreGive(droneStateMutex);

        motionGen.update();

        ImuPacket packet = builder.createImuPacket(imu);
        bool isPacketValid = packetValidator.validate(packet);

        if(isPacketValid){
            xQueueSend(imuQueue,&packet,portMAX_DELAY);
            //cout << "[PhysicsTask] IMU measures #"<<i<<" generated..." <<endl;   
        }
        //cout << "[PhysicsTask] Sending IMU #"<<i<<" generated..."<<endl;       
        i++; 
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}