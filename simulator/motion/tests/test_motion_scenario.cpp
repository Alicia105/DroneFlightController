#define CATCH_CONFIG_MAIN
#include <algorithm>
#include <cmath>
#include "../../../external/include/catch_amalgamated.hpp"
#include "../../../shared/state/include/dronestate.hpp"
#include "../include/motiongenerator.hpp"

using Catch::Matchers::WithinAbs;
using namespace std;

TEST_CASE("MotionGenerator initialization", "[Motion Generator]")
{
    MotionGenerator motion;

    REQUIRE(motion.getCurrentTime()==0);
    REQUIRE(motion.getDeltaTime()==0);
    REQUIRE(motion.getSimulationTime()==0);
}

TEST_CASE("MotionGenerator setters", "[Motion Generator]")
{
    MotionGenerator motion;

    motion.setDeltaTime(0.01);
    motion.setSimulationTime(10);

    REQUIRE_THAT(motion.getDeltaTime(),WithinAbs(0.01,1e-6));
    REQUIRE(motion.getSimulationTime()==10);
}

TEST_CASE("Simulation time update", "[Motion Generator]")
{
    MotionGenerator motion;

    motion.setDeltaTime(0.1);

    int n=0;
    while(n<3){
        motion.update();
        n++;
    }

    REQUIRE_THAT(motion.getCurrentTime(),WithinAbs(0.3,1e-6));
}

TEST_CASE("Hover scenario", "[Motion Generator]")
{
    MotionGenerator motion;
    DroneState d;
    DroneState & drone=d;

    motion.hover(drone,10,20,30);

    REQUIRE(drone.getVelocity()[0] == 0);
    REQUIRE(drone.getVelocity()[1] == 0);
    REQUIRE(drone.getVelocity()[2] == 0);

    REQUIRE(drone.getAcceleration()[0] == 0);
    REQUIRE(drone.getAcceleration()[1] == 0);
    REQUIRE(drone.getAcceleration()[2] == 0);

    REQUIRE(drone.getOrientation()[0] == 10);
    REQUIRE(drone.getOrientation()[1] == 20);
    REQUIRE(drone.getOrientation()[2] == 30);

    REQUIRE(drone.getAngularVelocity()[0] == 0);
    REQUIRE(drone.getAngularVelocity()[1] == 0);
    REQUIRE(drone.getAngularVelocity()[2] == 0);
}

TEST_CASE("Constant roll", "[Motion Generator]")
{
    MotionGenerator motion;
    DroneState d;
    DroneState & drone=d;

    motion.setDeltaTime(0.1);
    motion.constantRoll(drone,5.0);

    REQUIRE(drone.getOrientation()[0] == 0.5);
    REQUIRE(drone.getAngularVelocity()[0] == 5);
    REQUIRE(drone.getAngularAcceleration()[0] == 0);
}

TEST_CASE("Constant pitch", "[Motion Generator]")
{
    MotionGenerator motion;
    DroneState d;
    DroneState & drone=d;

    motion.setDeltaTime(0.2);
    motion.constantPitch(drone,2);

    REQUIRE_THAT(drone.getOrientation()[1],WithinAbs(0.4,1e-6));
    REQUIRE(drone.getAngularVelocity()[1] == 2);
    REQUIRE(drone.getAngularAcceleration()[1] == 0.0);
}

TEST_CASE("Constant yaw", "[Motion Generator]")
{
    MotionGenerator motion;
    DroneState d;
    DroneState & drone=d;

    motion.setDeltaTime(0.5);

    motion.constantYaw(drone,4);

    REQUIRE(drone.getOrientation()[2] == 2);
    REQUIRE(drone.getAngularVelocity()[2] == 4);
    REQUIRE(drone.getAngularAcceleration()[2] == 0);
}

TEST_CASE("Sinusoidal roll at t = 0", "[Motion Generator]")
{
    MotionGenerator motion;
    DroneState d;
    DroneState & drone=d;

    motion.sinusoidalRoll(drone,10,1);

    REQUIRE(drone.getOrientation()[0] == 0);
    REQUIRE_THAT(drone.getAngularVelocity()[0],WithinAbs(10 * 2 * M_PI,1e-4));
    REQUIRE(drone.getAngularAcceleration()[0] == 0);
}

TEST_CASE("Sinusoidal pitch at t = 0", "[Motion Generator]")
{
    MotionGenerator motion;
    DroneState d;
    DroneState & drone=d;

    motion.sinusoidalPitch(drone,5,2);

    REQUIRE(drone.getOrientation()[1] == 0);
    REQUIRE_THAT(drone.getAngularVelocity()[1],WithinAbs(10 * 2 * M_PI,1e-4));
    REQUIRE(drone.getAngularAcceleration()[1] == 0);
}

TEST_CASE("Takeoff", "[Motion Generator]")
{
    MotionGenerator motion;
    DroneState d;
    DroneState & drone=d;

    motion.setDeltaTime(0.1);

    motion.takeOff(drone);

    REQUIRE(drone.getAcceleration()[2] == 1);
    REQUIRE(drone.getVelocity()[2] > 0);
    REQUIRE(drone.getPosition()[2] > 0);
}

TEST_CASE("Landing from altitude", "[Motion Generator]")
{
    MotionGenerator motion;
    DroneState d;
    DroneState & drone=d;

    motion.setDeltaTime(0.1f);

    drone.setPosition(0,0,10);
    drone.setVelocity(0,0,-1);

    while(motion.getCurrentTime()<2.1){
        motion.update();
    }

    motion.landing(drone);

    REQUIRE(drone.getAcceleration()[2] == -1);
}