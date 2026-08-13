#ifndef COMMUNICATIONTASK_HPP
#define COMMUNICATIONTASK_HPP

#include <iostream>
#include "../../../shared/state/include/dronestate.hpp"
#include "../../../external/FreeRTOS/Source/include/FreeRTOS.h"
#include "../../common/include/freertos_objects.hpp"
#include "../../../shared/communication/include/packet.hpp"
#include "../../../simulator/communication/uart/include/uart_serializer.hpp"
#include "../../../simulator/communication/uart/include/uart_channel.hpp"
#include "../../../simulator/communication/uart/include/uart_driver.hpp"
#include "../../../simulator/communication/uart/include/packet_builder.hpp"
#include "../../../simulator/communication/uart/include/packet_validator.hpp"


#include "../../../external/FreeRTOS/Source/include/FreeRTOS.h"
#include "../../common/include/freertos_objects.hpp"

void communicationTask(void* parameter);

#endif // COMMUNICATIONTASK_HPP