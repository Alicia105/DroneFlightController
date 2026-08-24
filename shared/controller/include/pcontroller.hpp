#ifndef PCONTROLLER_HPP
#define PCONTROLLER_HPP

#include <vector>

class PController {
    // PController class implementation
    private:
        float Kp_thrust;
        float Kp_pitch;
        float Kp_roll;
        float Kp_yaw;

    public:
        PController();
        PController(float t, float r, float p, float y);
        ~PController();

        //getters
        float getThrust();
        float getRoll();
        float getPitch();
        float getYaw();

        //setters
        void setThrust(float t);
        void setRoll(float r);
        void setPitch(float p);
        void setYaw(float y);

        float computeThrust(float error);
        float computeRoll(float error);
        float computePitch(float error);
        float computeYaw(float error);
};


#endif // PCONTROLLER_HPP