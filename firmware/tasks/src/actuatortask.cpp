#include "../include/actuatortask.hpp"

using namespace std;
/*
application des commandes
*/
void actuatorTask(void* parameter){
    (void)parameter;
    while (true){
        //xSemaphoreTake(droneStateMutex, portMAX_DELAY);

        //droneState update via command

       // xSemaphoreGive(droneStateMutex);
        cout << "[ActuatorTask] Updating controller ..." << endl;
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}