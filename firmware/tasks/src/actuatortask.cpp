#include "../include/actuatortask.hpp"

using namespace std;
/*
application des commandes
*/
void actuatorTask(void* parameter){
    (void)parameter;
    while (true){
        cout << "[ActuatorTask] Updating controller ..." << endl;
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}