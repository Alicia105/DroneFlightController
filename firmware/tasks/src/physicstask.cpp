#include "../include/physicstask.hpp"

using namespace std;


/*
Cette tâche représente le travail qui serait effectué par le microcontrôleur pour récupérer les données des capteurs.
*/
void physicsTask(void* parameter){
    (void)parameter;
    float g = 9.81;
    IMU imu;
    MotionGenerator motionGen;
    PacketBuilder builder;
    PacketValidator packetValidator;

    //sensors implementation
    imu.setAccelSensorSaturation(-2*g,2*g);
    imu.setGyroSensorSaturation(-250,250);
    
    //motiongenerator implementation
    float dt=1/100;
    motionGen.setDeltaTime(dt);
    
    while (true){
        xSemaphoreTake(droneStateMutex, portMAX_DELAY);
        motionGen.RollAndPitch(drone,3,4,5);
        imu.updateMeasures(drone);
        xSemaphoreGive(droneStateMutex);

        motionGen.update();

        ImuPacket packet = builder.createImuPacket(imu);
        bool isPacketValid=packetValidator.validate(packet);

        if(isPacketValid){
            xQueueSend(imuQueue,&packet,portMAX_DELAY);
            cout << "[PhysicsTask] Reading IMU ..." << endl;   
        }
        cout << "[PhysicsTask] Sending IMU ..." << endl;        
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
