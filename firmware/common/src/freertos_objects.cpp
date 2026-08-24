#include "../include/freertos_objects.hpp"

using namespace std;

QueueHandle_t imuQueue = nullptr;

QueueHandle_t txQueue = nullptr;

QueueHandle_t motorCommandQueue = nullptr;

SemaphoreHandle_t droneStateMutex = nullptr;



extern "C" void vApplicationStackOverflowHook(TaskHandle_t xTask,char* pcTaskName){
    (void)xTask;
    (void)pcTaskName;

    cerr << "FreeRTOS: stack overflow detected in task: "<< pcTaskName << endl;
    while (true){
    }
}

extern "C" void vApplicationMallocFailedHook(){
    cerr << "FreeRTOS: malloc failed!" << endl;

    while (true){
    }
}