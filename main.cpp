#include <iostream>
#include <iomanip>
#include <bitset>
#include <cstdint>
#include <vector>
#include "simulator/sensors/include/accelerometer.hpp"
#include "simulator/sensors/include/gyroscope.hpp"
#include "simulator/sensors/include/imu.hpp"
#include "simulator/sensors/include/sensorSaturation.hpp"
#include "simulator/sensors/include/sensorError.hpp"
#include "simulator/motion/include/motiongenerator.hpp"
#include "shared/state/include/dronestate.hpp"
#include "shared/communication/include/packet.hpp"
#include "simulator/communication/uart/include/uart_serializer.hpp"
#include "simulator/communication/uart/include/virtual_uart.hpp"
#include "simulator/communication/uart/include/uart_driver.hpp"
#include "simulator/communication/uart/include/packet_builder.hpp"
#include "simulator/communication/uart/include/packet_validator.hpp"

#include "external/FreeRTOS/Source/include/FreeRTOS.h"
#include "firmware/common/include/freertos_objects.hpp"


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


/*int main(){

    //declarations
    float g = 9.81;
    IMU imu;
    DroneState droneState;
    DroneState & drone = droneState;
    MotionGenerator motionGen;

    VirtualUART ch;
    VirtualUART& channel=ch;

    UARTDriver driver(channel);
    PacketBuilder packetBuilder;
    PacketValidator packetValidator;

    ImuPacket packet{};

    //sensors implementation
    imu.setAccelSensorSaturation(-2*g,2*g);
    imu.setGyroSensorSaturation(-250,250);
  
    //motiongenerator implementation
    float dt=0.1;
    float simulationTime=1;
    motionGen.setSimulationTime(simulationTime);
    motionGen.setDeltaTime(dt);

    //motiongenerator start
    cout<<"------------------------Start------------------------"<<endl;
    motionGen.printMotionGeneratorData();

    //set drone start position
    drone.setPosition(1,2,3);
    drone.setVelocity(1,1,1);

    while(motionGen.getCurrentTime()<=motionGen.getSimulationTime()){
        //move function
        motionGen.RollAndPitch(drone,3,4,5);
        
        cout<<"--------------------t ="<<motionGen.getCurrentTime()<<" --------------------"<<endl;
        motionGen.printMotionGeneratorData();
        cout<<"-------------------Drone data--------------------"<<endl;
        drone.printFullDroneStateData();

        cout<<"-------------------IMU--------------------"<<endl;
        imu.updateMeasures(drone);
        imu.printAccelerometerData();
        imu.printGyroscopeData();
        motionGen.update();

        //ImuPacket
        /*ImuPacket packet=setFromIMU(imu);
        packet.header = 0xAA;
        packet.packetID = 0x01;
        packet.payloadSize = 24;
        packet.timestamp = 0x00111101;
        packet.checksum = 0x0B02;*/

       /*ImuPacket packet=packetBuilder.createImuPacket(imu);
        bool isPacketAvailable=packetValidator.validate(packet);
        if(isPacketAvailable){
            driver.write(packet);
            ImuPacket pck=driver.read();
            cout<<"-------------------ImuPacket--------------------"<<endl;
            printImuPacket(pck);
        }
    }

    cout<<"--------------------t ="<<motionGen.getCurrentTime()<<" --------------------"<<endl;
    motionGen.printMotionGeneratorData();
    cout<<"-------------------Drone--------------------"<<endl;
    drone.printFullDroneStateData();

    cout<<"-------------------IMU--------------------"<<endl;
    imu.updateMeasures(drone);
    imu.printAccelerometerData();
    imu.printGyroscopeData();


    return 0;
}*/

extern "C" void vApplicationStackOverflowHook(TaskHandle_t xTask,char* pcTaskName){
    (void)xTask;
    (void)pcTaskName;

    cerr << "FreeRTOS: stack overflow detected in task: "<< pcTaskName << endl;
    while (true){
    }
}

extern "C" void vApplicationMallocFailedHook(){
    cerr << "FreeRTOS: malloc failed!" << endl;

    while (true){
    }
}

void testTask(void* parameter){
    while (true)
    {
        cout << "FreeRTOS task is running!" << endl;

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

/*
Cette tâche représente le travail qui serait effectué par le microcontrôleur pour récupérer les données des capteurs.
*/
void sensorTask(void* parameter){
    (void)parameter;
    float g = 9.81;
    IMU imu;
    DroneState droneState;
    DroneState & drone = droneState;
    MotionGenerator motionGen;
    PacketBuilder builder;
    PacketValidator packetValidator;

    //sensors implementation
    imu.setAccelSensorSaturation(-2*g,2*g);
    imu.setGyroSensorSaturation(-250,250);
    
    //motiongenerator implementation
    float dt=1/100;
    motionGen.setDeltaTime(dt);

    //set drone start position
    drone.setPosition(1,2,3);
    drone.setVelocity(1,1,1);

    while (true){
        motionGen.RollAndPitch(drone,3,4,5);
        imu.updateMeasures(drone);
        motionGen.update();

        ImuPacket packet = builder.createImuPacket(imu);
        bool isPacketValid=packetValidator.validate(packet);

        if(isPacketValid){
            xQueueSend(imuQueue,&packet,portMAX_DELAY);
            cout << "[SensorTask] Reading IMU ..." << endl;   
        }
        cout << "[SensorTask] Sending IMU ..." << endl;        
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void communicationTask(void* parameter){
    (void)parameter;
    while (true){
        cout << "[CommunicationTask] Updating measures ..." << endl;
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

/**
 * @brief 
    C'est probablement la tâche la plus importante. Elle reçoit les mesures de l'IMU.
    Elle peut ensuite :
    -désérialiser/interpréter les données ;
    -estimer l'état du drone ;
    -comparer l'état actuel à la consigne ;
    -calculer les erreurs ;
    -appliquer les contrôleurs PID ;
    -produire les commandes moteurs.
 * 
 */

void controllerTask(void* parameter){
    (void)parameter;
    PacketValidator packetValidator;

    while (true){
        ImuPacket packet{};
        
        if (xQueueReceive(imuQueue, &packet, portMAX_DELAY) == pdTRUE){
            bool isPacketValid=packetValidator.validate(packet);
            if(isPacketValid){
                cout<< "[Controller] IMU: "<< "ax=" << packet.ax<< " ay=" << packet.ay<< " az=" << packet.az<< "wx=" << packet.wx<< " wy=" << packet.wy<< " wz=" << packet.wz<<endl;
            }

        }        
        cout << "[ControllerTask] Updating controller ..." << endl;
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}

/*
application des commandes
*/
void actuatorTask(void* parameter){
    (void)parameter;
    while (true){
        cout << "[ActuatorTask] Updating controller ..." << endl;
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}


int main(){
   
    //mutex

    imuQueue = xQueueCreate(10, sizeof(ImuPacket));

    if (imuQueue == nullptr){
        cerr << "Failed to create IMU queue" << endl;
        return 1;
    }

    xTaskCreate(sensorTask,"SensorTask",configMINIMAL_STACK_SIZE,nullptr,2,nullptr);
    xTaskCreate(controllerTask,"ControllerTask",configMINIMAL_STACK_SIZE,nullptr,3,nullptr);
    
    vTaskStartScheduler();

    cout << "Scheduler stopped!" << endl;

    return 0;
}
