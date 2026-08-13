#include "../include/freertos_objects.hpp"

QueueHandle_t imuQueue = nullptr;

QueueHandle_t txQueue = nullptr;

//QueueHandle_t rxQueue = nullptr;

SemaphoreHandle_t droneStateMutex = nullptr;

SemaphoreHandle_t UARTMutex = nullptr;

