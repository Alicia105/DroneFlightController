#ifndef CONTROLLERTASK_HPP
#define CONTROLLERTASK_HPP

#include <iostream>
#include "../../../simulator/sensors/include/imu.hpp"
#include "../../../simulator/sensors/include/sensorSaturation.hpp"
#include "../../../simulator/sensors/include/sensorError.hpp"
#include "../../../simulator/motion/include/motiongenerator.hpp"
#include "../../../shared/state/include/dronestate.hpp"
#include "../../../shared/controller/include/pcontroller.hpp"
#include "../../../shared/controller/include/motorcommand.hpp"
#include "../../../shared/communication/include/packet.hpp"
#include "../../../simulator/communication/uart/include/uart_serializer.hpp"
#include "../../../simulator/communication/uart/include/uart_channel.hpp"
#include "../../../simulator/communication/uart/include/uart_driver.hpp"
#include "../../../simulator/communication/uart/include/packet_builder.hpp"
#include "../../../simulator/communication/uart/include/packet_validator.hpp"

#include "../../../external/FreeRTOS/Source/include/FreeRTOS.h"
#include "../../common/include/freertos_objects.hpp"

void controllerTask(void* parameter);


#endif // CONTROLLERTASK_HPP