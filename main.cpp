#include <iostream>

#include "simulator/sensors/include/imu.hpp"
#include "simulator/sensors/include/sensorSaturation.hpp"
#include "simulator/sensors/include/sensorError.hpp"
#include "simulator/motion/include/motiongenerator.hpp"

#include "shared/state/include/dronestate.hpp"

#include "shared/controller/include/motorcommand.hpp"
#include "shared/controller/include/motormixer.hpp"

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


/*int main(){
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
}*/


int main(){
    float g = 9.81;

    UARTChannel ch1(txQueue);
    UARTChannel& channel1 = ch1;
    UARTDriver driver1(channel1);

    PacketBuilder builder;
    PacketValidator packetValidator;

    IMU imu;
    MotionGenerator motionGen;
    
    DroneState droneState;
    DroneState desiredState;

    DroneState estimated;
    DroneState error;

    PController pid(2,2,2,2);
    MotorMixer motor;

    //sensors implementation
    imu.setAccelSensorSaturation(-2*g,2*g);
    imu.setGyroSensorSaturation(-250,250);
    
    //motiongenerator implementation
    float dt=0.01f;
    motionGen.setDeltaTime(dt);
    
    //set drone start position
    droneState.setPosition(0,0,18);
    droneState.setOrientation(0,0,60);
   
    desiredState.setPosition(0,0,19.62f);
    desiredState.setOrientation(0,0,40);

    cout << "[Initial] Original Drone state :"<<endl ;
    droneState.printFullDroneStateData();
    cout << "[Initial] Desired state :"<<endl ;
    desiredState.printFullDroneStateData();

    int i=0;

    while(motionGen.getCurrentTime()<=12.78){

        motionGen.takeoffHoverLandingScenario(droneState,30,0,0);
        
        //droneState.setPosition(0,0,18);
        imu.updateMeasures(droneState);
        motionGen.update();

        ImuPacket packet = builder.createImuPacket(imu);
        bool isPacketValid = packetValidator.validate(packet);

        if(isPacketValid){

            estimated.computePosition(packet,dt);
            //error.computeError(desiredState,estimated);
            error.computeError(desiredState,droneState);

            cout<<"[Original state] #"<<i<<" :"<<endl;
            droneState.printFullDroneStateData();

            cout<<"[Estimated state] #"<<i<<" :"<<endl;
            estimated.printFullDroneStateData();

            cout<<"[Error state] #"<<i<<" :"<<endl;
            error.printFullDroneStateData();

            vector<float> errorOrientation = error.getOrientation();
            vector<float> errorPosition = error.getPosition();


            float thrustCorrection = pid.computeThrust(errorPosition[2]);
            float rollCorrection = pid.computeRoll(errorOrientation[0]);
            float pitchCorrection = pid.computePitch(errorOrientation[1]);
            float yawCorrection = pid.computeYaw(errorOrientation[2]);

            MotorCommand commands = motor.mix(thrustCorrection,rollCorrection,pitchCorrection,yawCorrection);

            cout<<"[ControllerTask] Commands #"<<i<<" :"<<endl;
            printMotorCommand(commands);
            i++;
        }
    }
    

    return 0;
}
