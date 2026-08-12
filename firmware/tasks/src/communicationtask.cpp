#include "../include/communicationtask.hpp"

using namespace std;

void communicationTask(void* parameter){
    (void)parameter;
    while (true){
        cout << "[CommunicationTask] Updating measures ..." << endl;
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}


