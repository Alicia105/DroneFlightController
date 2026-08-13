#include "../include/communicationtask.hpp"

using namespace std;


void communicationTask(void* parameter){
    (void)parameter;
    PacketValidator packetValidator;
    
    while (true){
        ImuPacket packet{};
        
        if (xQueueReceive(imuQueue, &packet, portMAX_DELAY) == pdTRUE){
            bool isPacketValid=packetValidator.validate(packet);
            if(isPacketValid){
                cout<< "[CommunicationTask]  Received IMU: "<< "ax=" << packet.ax<< " ay=" << packet.ay<< " az=" << packet.az<< "wx=" << packet.wx<< " wy=" << packet.wy<< " wz=" << packet.wz<<endl;            
                //xSemaphoreTake(UARTMutex, portMAX_DELAY);
                driver1.writeFreeRTOS(packet);
                //xSemaphoreGive(UARTMutex);                   
            }
        }        
        cout << "[CommunicationTask] Sending data to UART ..." << endl;
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}
