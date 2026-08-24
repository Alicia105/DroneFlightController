#ifndef MOTORMIXER_HPP
#define MOTORMIXER_HPP

#include "motorcommand.hpp"

class MotorMixer
{
    private :
    public :
        MotorMixer();
        ~MotorMixer();
        MotorCommand mix(float thrust, float rollCorrection, float pitchCorrection, float yawCorrection);
};


#endif // MOTORMIXER_HPP