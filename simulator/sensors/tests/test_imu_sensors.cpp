#define CATCH_CONFIG_MAIN
#include "../../../external/include/catch_amalgamated.hpp"
#include "../include/accelerometer.hpp"
#include "../include/gyroscope.hpp"
#include "../include/imu.hpp"

using namespace std;

TEST_CASE("Accelerometer implementation","[accelerometer]"){
    Accelerometer a;
    a.setAx(1);
    a.setAy(2);
    a.setAz(3);

    REQUIRE(a.getAx()==1);
    REQUIRE(a.getAy()==2);
    REQUIRE(a.getAz()==3);

}

TEST_CASE("Gyroscope implementation","[gyroscope]"){
    Gyroscope g;
    g.setWx(1);
    g.setWy(2);
    g.setWz(3);

    REQUIRE(g.getWx()==1);
    REQUIRE(g.getWy()==2);
    REQUIRE(g.getWz()==3);

}

TEST_CASE("IMU implementation","[IMU]"){
    IMU i;
    i.setAx(1);
    i.setAy(2);
    i.setAz(3);
    
    i.setWx(1);
    i.setWy(2);
    i.setWz(3);

    REQUIRE(i.getAx()==1);
    REQUIRE(i.getAy()==2);
    REQUIRE(i.getAz()==3);
    REQUIRE(i.getWx()==1);
    REQUIRE(i.getWy()==2);
    REQUIRE(i.getWz()==3);

}