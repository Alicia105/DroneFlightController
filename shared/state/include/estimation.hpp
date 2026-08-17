#ifndef ESTIMATOR_HPP
#define ESTIMATOR_HPP

#include "dronestate.hpp"
#include "../../communication/include/packet.hpp"

void computePosition(DroneState& drone,const ImuPacket& imu,float dt);
//void applyMotorCommand(MotorCommand& commands);
DroneState computeError(DroneState& desiredState,DroneState& estimatedState);
//void applyMotorCommand(MotorCommand& commands);

#endif // ESTIMATOR_HPP