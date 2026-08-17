#ifndef FREERTOS_OBJECTS_HPP
#define FREERTOS_OBJECTS_HPP

#include "../../../external/FreeRTOS/Source/include/FreeRTOS.h"
#include "../../../external/FreeRTOS/Source/include/queue.h"
#include "../../../external/FreeRTOS/Source/include/task.h"
#include "../../../external/FreeRTOS/Source/portable/MSVC-MingW/portmacro.h"
#include "../../../external/FreeRTOS/Source/include/event_groups.h"
#include "../../../external/FreeRTOS/Source/include/semphr.h"
#include "../../../shared/state/include/dronestate.hpp"
#include "../../../simulator/motion/include/motiongenerator.hpp"
#include "../../../simulator/sensors/include/imu.hpp"
#include "../../../simulator/communication/uart/include/uart_driver.hpp"
#include "../../../simulator/communication/uart/include/uart_channel.hpp"
#include "../../../simulator/communication/uart/include/uart_serializer.hpp"

//for FreeRTOS
//#include "external/FreeRTOS/Source//include/FreeRTOSConfig.h"
/*#include "external/FreeRTOS/Source/include/FreeRTOS.h"
#include "external/FreeRTOS/Source/include/atomic.h"
#include "external/FreeRTOS/Source/include/croutine.h"
#include "external/FreeRTOS/Source/include/deprecated_definitions.h"
#include "external/FreeRTOS/Source/include/event_groups.h"
#include "external/FreeRTOS/Source/include/list.h"
#include "external/FreeRTOS/Source/include/message_buffer.h"
//#include "external/FreeRTOS/Source/include/mpu_prototypes.h"
#include "external/FreeRTOS/Source/include/mpu_syscall_numbers.h"
#include "external/FreeRTOS/Source/include/mpu_wrappers.h"
//#include "external/FreeRTOS/Source/include/newlib-freertos.h"
//#include "external/FreeRTOS/Source/include/piclib-freeertos.h"
#include "external/FreeRTOS/Source/include/portable.h"
#include "external/FreeRTOS/Source/include/projdefs.h"
#include "external/FreeRTOS/Source/include/semphr.h"
#include "external/FreeRTOS/Source/include/stack_macros.h"
#include "external/FreeRTOS/Source/include/StackMacros.h"
#include "external/FreeRTOS/Source/include/stream_buffer.h"
#include "external/FreeRTOS/Source/include/task.h"
#include "external/FreeRTOS/Source/include/timers.h"
*/

struct CommunicationTaskParameters{
    UARTDriver* driver;
};

struct PhysicsTaskParameters{
    DroneState* droneState;
    IMU* imu;
    MotionGenerator* motionGen;
};
    
struct ControllerTaskParameters{
    UARTDriver* driver;
    DroneState* droneState;
   // MotorCommand* motorCommand;
};

struct ActuatorTaskParameters{
    DroneState* droneState;
    //MotorCommand* motorCommand;
};

extern  QueueHandle_t imuQueue;

extern QueueHandle_t txQueue;

extern QueueHandle_t motorCommandQueue;

extern SemaphoreHandle_t droneStateMutex;

#endif