#include "../include/actuatortask.hpp"

using namespace std;
/*
application des commandes
*/
void actuatorTask(void* parameter){
    (void)parameter;
    auto* param = static_cast<ActuatorTaskParameters*>(parameter);
    DroneState& drone = *param->droneState;
    int i=0;

    while (true){
        MotorCommand commands{};
        //cout << "[Actuator] Waiting..." << endl;

        BaseType_t ok = xQueueReceive(motorCommandQueue,&commands,portMAX_DELAY);

        cout << "[ActuatorTask] Received " << ok << endl;

        //cout << "[ActuatorTask] Before xQueueReceive" << endl;
        if(ok == pdTRUE){
        //if(xQueueReceive(motorCommandQueue, &commands, portMAX_DELAY) == pdTRUE){
            //cout << "[ActuatorTask] After xQueueReceive" << endl;
            //cout<< "[ActuatorTask] Motor Commands #"<<i<<" : throttle=" << commands.throttle<< " roll=" << commands.roll<< " pitch=" << commands.pitch<< " yaw=" << commands.yaw<<endl;
            cout<< "[ActuatorTask] Motor Commands #"<<i<<" : m1=" << commands.motor1<< " m2=" << commands.motor2<< " m3=" << commands.motor3<< " m4=" << commands.motor4<<endl;
            //xSemaphoreTake(droneStateMutex, portMAX_DELAY);
            //droneState update via command
            //xSemaphoreGive(droneStateMutex);
            
            //cout << "[ActuatorTask] Applying motor commands #"<<i<<" ..." << endl;
            i++;
            vTaskDelay(pdMS_TO_TICKS(20));
        }
        
    }
}