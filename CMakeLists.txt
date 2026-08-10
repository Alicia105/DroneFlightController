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
    "${CMAKE_CURRENT_SOURCE_DIR}/FreeRTOS/Source"
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

# Source files
add_executable(DroneFlightController
   main.cpp
    ${FREERTOS_SOURCES}
)


# Include directories
target_include_directories(DroneFlightController PRIVATE
    ${FREERTOS_DIR}/include

    ${FREERTOS_PORT}/portmacro.h
    
    simulator/sensors/include
    simulator/motion/include    
    simulator/communication/include
    shared/state/include          
)

if(WIN32)
    target_link_libraries(DroneFlightController
        winmm
    )
endif()