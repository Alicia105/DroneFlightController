#ifndef PCONTROLLER_HPP
#define PCONTROLLER_HPP

#include <vector>

class PController {
    // PController class implementation
    private:
        float Kp_throttle;
        float Kp_pitch;
        float Kp_roll;
        float Kp_yaw;

    public:
        PController();
        PController(float t, float r, float p, float y);
        ~PController();

        //getters
        float getThrottle();
        float getRoll();
        float getPitch();
        float getYaw();

        //setters
        void setThrottle(float t);
        void setRoll(float r);
        void setPitch(float p);
        void setYaw(float y);

        float computeThrottle(float error);
        float computeRoll(float error);
        float computePitch(float error);
        float computeYaw(float error);
};


#endif // PCONTROLLER_HPP