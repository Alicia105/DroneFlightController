#ifndef ACTUATORTASK_HPP
#define ACTUATORTASK_HPP

#include <iostream>
#include "../../../shared/state/include/dronestate.hpp"
#include "../../../shared/state/include/motorcommand.hpp"
#include "../../../external/FreeRTOS/Source/include/FreeRTOS.h"
#include "../../common/include/freertos_objects.hpp"

void actuatorTask(void* parameter);

#endif // ACTUATORTASK_HPP