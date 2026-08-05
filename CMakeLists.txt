cmake_minimum_required(VERSION 3.10)
project(DroneFlightController)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Source files
add_executable(DroneFlightController 
    main.cpp 
    simulator/sensors/src/accelerometer.cpp
    simulator/sensors/src/gyroscope.cpp
    simulator/sensors/src/imu.cpp
    simulator/sensors/src/gaussianNoise.cpp
    simulator/sensors/src/sensorError.cpp 
    simulator/sensors/src/sensorSaturation.cpp
    simulator/motion/src/motiongenerator.cpp
    simulator/communication/src/packet.cpp  
    simulator/communication/src/uart_serializer.cpp
    simulator/communication/src/virtual_uart.cpp  
    simulator/communication/src/uart_driver.cpp    
    shared/state/src/dronestate.cpp
    
)

# Include directories
target_include_directories(DroneFlightController PRIVATE
   simulator/sensors/include
   simulator/motion/include    
   simulator/communication/include
   shared/state/include          
)

