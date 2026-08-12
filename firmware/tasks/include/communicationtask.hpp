#ifndef COMMUNICATIONTASK_HPP
#define COMMUNICATIONTASK_HPP

#include <iostream>
#include "../../../shared/state/include/dronestate.hpp"
#include "../../../external/FreeRTOS/Source/include/FreeRTOS.h"
#include "../../common/include/freertos_objects.hpp"

void communicationTask(void* parameter);

#endif // COMMUNICATIONTASK_HPP