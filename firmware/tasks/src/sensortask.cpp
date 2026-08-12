#include "../include/sensortask.hpp"

using namespace std;


/*
Cette tâche représente le travail qui serait effectué par le microcontrôleur pour récupérer les données des capteurs.
*/
void sensorTask(void* parameter){
    (void)parameter;
    float g = 9.81;
    IMU imu;
    DroneState droneState;
    DroneState & drone = droneState;
    MotionGenerator motionGen;
    PacketBuilder builder;
    PacketValidator packetValidator;

    //sensors implementation
    imu.setAccelSensorSaturation(-2*g,2*g);
    imu.setGyroSensorSaturation(-250,250);
    
    //motiongenerator implementation
    float dt=1/100;
    motionGen.setDeltaTime(dt);

    //set drone start position
    drone.setPosition(1,2,3);
    drone.setVelocity(1,1,1);

    while (true){
        motionGen.RollAndPitch(drone,3,4,5);
        imu.updateMeasures(drone);
        motionGen.update();

        ImuPacket packet = builder.createImuPacket(imu);
        bool isPacketValid=packetValidator.validate(packet);

        if(isPacketValid){
            xQueueSend(imuQueue,&packet,portMAX_DELAY);
            cout << "[SensorTask] Reading IMU ..." << endl;   
        }
        cout << "[SensorTask] Sending IMU ..." << endl;        
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
