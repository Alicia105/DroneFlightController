#define CATCH_CONFIG_MAIN
#include "../../../external/Catch2/include/catch_amalgamated.hpp"
#include "../../../simulator/sensors/include/accelerometer.hpp"
#include "../include/dronestate.hpp"


using namespace std;

TEST_CASE("Weight implementation","[Drone state]"){
    DroneState d;

    REQUIRE(d.getWeight()==0);
    d.setWeight(3);
    REQUIRE(d.getWeight()==3);  
}

TEST_CASE("Position vector implementation","[Drone state]"){
    DroneState d;

    REQUIRE(d.getPosition().size()==3);
    REQUIRE(d.getPosition()[0]==0);
    REQUIRE(d.getPosition()[1]==0);
    REQUIRE(d.getPosition()[2]==0);
    
    d.setPosition(1,2,3);
    REQUIRE(d.getPosition()[0]==1);
    REQUIRE(d.getPosition()[1]==2);
    REQUIRE(d.getPosition()[2]==3);

}


TEST_CASE("Velocity vector implementation","[Drone state]"){
    DroneState d;

    REQUIRE(d.getVelocity().size()==3);
    REQUIRE(d.getVelocity()[0]==0);
    REQUIRE(d.getVelocity()[1]==0);
    REQUIRE(d.getVelocity()[2]==0);
    
    d.setVelocity(1,2,3);
    REQUIRE(d.getVelocity()[0]==1);
    REQUIRE(d.getVelocity()[1]==2);
    REQUIRE(d.getVelocity()[2]==3);

}


TEST_CASE("Acceleration vector implementation","[Drone state]"){
    DroneState d;

    REQUIRE(d.getAcceleration().size()==3);
    REQUIRE(d.getAcceleration()[0]==0);
    REQUIRE(d.getAcceleration()[1]==0);
    REQUIRE(d.getAcceleration()[2]==0);
    
    d.setAcceleration(1,2,3);
    REQUIRE(d.getAcceleration()[0]==1);
    REQUIRE(d.getAcceleration()[1]==2);
    REQUIRE(d.getAcceleration()[2]==3);

}


TEST_CASE("Orientation vector implementation","[Drone state]"){
    DroneState d;

    REQUIRE(d.getOrientation().size()==3);
    REQUIRE(d.getOrientation()[0]==0);
    REQUIRE(d.getOrientation()[1]==0);
    REQUIRE(d.getOrientation()[2]==0);
    
    d.setOrientation(1,2,3);
    REQUIRE(d.getOrientation()[0]==1);
    REQUIRE(d.getOrientation()[1]==2);
    REQUIRE(d.getOrientation()[2]==3);

}


TEST_CASE("Angular Velocity vector implementation","[Drone state]"){
    DroneState d;

    REQUIRE(d.getAngularVelocity().size()==3);
    REQUIRE(d.getAngularVelocity()[0]==0);
    REQUIRE(d.getAngularVelocity()[1]==0);
    REQUIRE(d.getAngularVelocity()[2]==0);
    
    d.setAngularVelocity(1,2,3);
    REQUIRE(d.getAngularVelocity()[0]==1);
    REQUIRE(d.getAngularVelocity()[1]==2);
    REQUIRE(d.getAngularVelocity()[2]==3);

}


TEST_CASE("Angular Acceleration vector implementation","[Drone state]"){
    DroneState d;

    REQUIRE(d.getAngularAcceleration().size()==3);
    REQUIRE(d.getAngularAcceleration()[0]==0);
    REQUIRE(d.getAngularAcceleration()[1]==0);
    REQUIRE(d.getAngularAcceleration()[2]==0);
    
    d.setAngularAcceleration(1,2,3);
    REQUIRE(d.getAngularAcceleration()[0]==1);
    REQUIRE(d.getAngularAcceleration()[1]==2);
    REQUIRE(d.getAngularAcceleration()[2]==3);

}
