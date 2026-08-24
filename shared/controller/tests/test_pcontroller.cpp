#define CATCH_CONFIG_MAIN
#include <vector>
#include "../../../external/Catch2/include/catch_amalgamated.hpp"
#include "../include/pcontroller.hpp"


using namespace std;

TEST_CASE("PController implementation","[PController]"){
    PController p;

    REQUIRE(p.getThrottle()==0);
    REQUIRE(p.getRoll()==0);
    REQUIRE(p.getPitch()==0);
    REQUIRE(p.getYaw()==0);

    p.setThrottle(1);
    p.setRoll(2);
    p.setPitch(3);
    p.setYaw(4);

    REQUIRE(p.getThrottle()==1);
    REQUIRE(p.getRoll()==2);
    REQUIRE(p.getPitch()==3);
    REQUIRE(p.getYaw()==4);    
}

TEST_CASE("Proportionnal corrector","[PController]"){
    PController p(2,4,5,6);
    
    REQUIRE(p.computeThrottle(10)==20);
    REQUIRE(p.computeRoll(10)==40);
    REQUIRE(p.computePitch(10)==50);
    REQUIRE(p.computeYaw(10)==60);

    REQUIRE(p.computeThrottle(0)==0);
    REQUIRE(p.computeRoll(0)==0);
    REQUIRE(p.computePitch(0)==0);
    REQUIRE(p.computeYaw(0)==0);

}
