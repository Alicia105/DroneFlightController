cmake_minimum_required(VERSION 3.10)
project(DroneFlightController)

project(DroneFlightController
    LANGUAGES C CXX
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------------------------------------------------------
# FreeRTOS
# ---------------------------------------------------------

set(FREERTOS_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/external/FreeRTOS/Source"
)

set(FREERTOS_PORT
    "${FREERTOS_DIR}/portable/MSVC-MingW"
)

set(FREERTOS_MEMORY
    "${FREERTOS_DIR}/portable/MemMang"
)

# ---------------------------------------------------------
# FreeRTOS kernel
# ---------------------------------------------------------

set(FREERTOS_SOURCES
    ${FREERTOS_DIR}/tasks.c
    ${FREERTOS_DIR}/queue.c
    ${FREERTOS_DIR}/list.c
    ${FREERTOS_DIR}/timers.c
    ${FREERTOS_DIR}/event_groups.c
    ${FREERTOS_DIR}/croutine.c
    ${FREERTOS_DIR}/stream_buffer.c

    ${FREERTOS_PORT}/port.c

    ${FREERTOS_MEMORY}/heap_4.c
)

# ---------------------------------------------------------
# Application
# ---------------------------------------------------------
set(SIMULATOR_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/simulator"
)

set(COMMUNICATION_DIR
    "${SIMULATOR_DIR}/communication/uart/src"
)

set(MOTION_DIR
    "${SIMULATOR_DIR}/motion/src"
)

set(SENSORS_DIR
    "${SIMULATOR_DIR}/sensors/src"
)

set(FIRMWARE_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/firmware/"
)

set(SHARED_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/shared/"
)

set(COMMUNICATION_SOURCES
    ${COMMUNICATION_DIR}/packet_builder.cpp
    ${COMMUNICATION_DIR}/packet_validator.cpp
    ${COMMUNICATION_DIR}/virtual_uart.cpp
    ${COMMUNICATION_DIR}/uart_serializer.cpp
    ${COMMUNICATION_DIR}/uart_driver.cpp

)

set(MOTION_SOURCES
    ${MOTION_DIR}/motiongenerator.cpp
)

set(SENSORS_SOURCES
    ${SENSORS_DIR}/accelerometer.cpp
    ${SENSORS_DIR}/gyroscope.cpp
    ${SENSORS_DIR}/imu.cpp
    ${SENSORS_DIR}/gaussianNoise.cpp
    ${SENSORS_DIR}/sensorError.cpp
    ${SENSORS_DIR}/sensorSaturation.cpp

)

set(SHARED_SOURCES
    ${SHARED_DIR}/state/src/dronestate.cpp
    ${SHARED_DIR}/communication/src/packet.cpp
)

set(FIRMWARE_SOURCES
    ${FIRMWARE_DIR}/common/src/freertos_objects.cpp
)

# Source files
add_executable(DroneFlightController
   main.cpp
   ${FREERTOS_SOURCES}
   ${SENSORS_SOURCES}
   ${MOTION_SOURCES}
   ${SHARED_SOURCES}
   ${COMMUNICATION_SOURCES}
   ${FIRMWARE_SOURCES}
)


# Include directories
target_include_directories(DroneFlightController PRIVATE
    ${FREERTOS_DIR}/include
    ${FREERTOS_PORT}/portmacro.h
    
    simulator/sensors/include
    simulator/motion/include    
    simulator/communication/include
    shared/state/include
    firmware/common/include          
)

if(WIN32)
    target_link_libraries(DroneFlightController
        winmm
    )
endif()