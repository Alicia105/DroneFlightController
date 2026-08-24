#include <iostream>

#include "simulator/sensors/include/imu.hpp"
#include "simulator/sensors/include/sensorSaturation.hpp"
#include "simulator/sensors/include/sensorError.hpp"
#include "simulator/motion/include/motiongenerator.hpp"

#include "shared/state/include/dronestate.hpp"

#include "shared/controller/include/motorcommand.hpp"

#include "simulator/communication/uart/include/uart_serializer.hpp"
#include "simulator/communication/uart/include/uart_channel.hpp"
#include "simulator/communication/uart/include/uart_driver.hpp"
#include "simulator/communication/uart/include/packet_builder.hpp"
#include "simulator/communication/uart/include/packet_validator.hpp"

#include "external/FreeRTOS/Source/include/FreeRTOS.h"
#include "firmware/common/include/freertos_objects.hpp"
#include "firmware/tasks/include/physicstask.hpp"
#include "firmware/tasks/include/controllertask.hpp"
#include "firmware/tasks/include/actuatortask.hpp"
#include "firmware/tasks/include/communicationtask.hpp"


using namespace std;

/*template<typename T>
void printMemory(const T& value)
{
    const uint8_t* bytes = reinterpret_cast<const uint8_t*>(&value);

    cout << "Size : " << sizeof(T) << " bytes" << endl;

    for(size_t i = 0; i < sizeof(T); i++)
    {
        cout << "Byte " << i << " : 0x"
             << hex << setw(2) << setfill('0')
             << static_cast<int>(bytes[i])
             << endl;
    }

    cout << dec << endl;
}

int main(){
    VirtualUART ch;
    VirtualUART& channel=ch;
    UARTDriver driver(channel);
    UARTSerializer serializer;

    ImuPacket packet{};

    packet.header = 0xAA;
    packet.packetID = 0x01;
    packet.payloadSize = 24;

    packet.timestamp = 0x00111101;
    

    packet.ax = 1.0f;
    packet.ay = 2.0f;
    packet.az = 5.5f;

    packet.wx = 7.8f;
    packet.wy = 12.0f;
    packet.wz = 2.0f;

    packet.checksum = 0x0B02;

    vector<uint8_t> buffer = serializer.serialize(packet);
    cout << "Serialized size = " << buffer.size() << endl;

    channel.transmit(buffer);

    cout << "Channel size = " << channel.size() << endl;

    cout << "---------------In read()---------------" << endl;
    ImuPacket reconstructed = driver.read();
    
}*/



int main(){
    float g = 9.81;

    //queue
    imuQueue = xQueueCreate(10, sizeof(ImuPacket));
    txQueue = xQueueCreate(340, sizeof(uint8_t));
    motorCommandQueue = xQueueCreate(100, sizeof(MotorCommand));;
    
    //mutex
    droneStateMutex = xSemaphoreCreateMutex();    
    
    if (imuQueue == nullptr){
        cerr << "Failed to create IMU queue" << endl;
        return 1;
    }
     if (txQueue == nullptr){
        cerr << "Failed to create tx queue" << endl;
        return 1;
    }
    if (motorCommandQueue == nullptr){
        cerr << "Failed to create rx queue" << endl;
        return 1;
    }
    if (droneStateMutex == nullptr){
        cerr << "Failed to create dronestate mutex" << endl;
        return 1;
    }
  
    UARTChannel ch1(txQueue);
    UARTChannel& channel1 = ch1;
    UARTDriver driver1(channel1);

    IMU imu;
    MotionGenerator motionGen;
    
    DroneState droneState;
    DroneState desiredState;

    //sensors implementation
    imu.setAccelSensorSaturation(-2*g,2*g);
    imu.setGyroSensorSaturation(-250,250);
    
    //motiongenerator implementation
    float dt=0.01f;
    motionGen.setDeltaTime(dt);
    
    //set drone start position
    droneState.setPosition(0,0,0);
    //droneState.setVelocity(1,1,1);

    desiredState.setPosition(0,0,19.62);
    desiredState.setOrientation(10,2,3);

    cout << "[Initial] Drone state :" ;
    droneState.printFullDroneStateData();
    cout << "[Initial] Desired state :" ;
    desiredState.printFullDroneStateData();
    
    CommunicationTaskParameters communicationParams{&driver1};
    PhysicsTaskParameters physicsParams{&droneState,&imu,&motionGen};
    ControllerTaskParameters controllerParams{&driver1,&droneState,&desiredState,};
    ActuatorTaskParameters actuatorParams{&droneState};


    xTaskCreate(physicsTask,"PhysicsTask",configMINIMAL_STACK_SIZE,&physicsParams,3,nullptr);
    xTaskCreate(communicationTask,"CommunicationTask",configMINIMAL_STACK_SIZE,&communicationParams,2,nullptr);
    xTaskCreate(controllerTask,"ControllerTask",configMINIMAL_STACK_SIZE,&controllerParams,1,nullptr);
    xTaskCreate(actuatorTask,"ActuatorTask",configMINIMAL_STACK_SIZE,&actuatorParams,1,nullptr);
    
    vTaskStartScheduler();

    cout << "Scheduler stopped!" << endl;

    return 0;
}
