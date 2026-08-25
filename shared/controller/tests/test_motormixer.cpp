#define CATCH_CONFIG_MAIN
#include <vector>
#include "../../../external/Catch2/include/catch_amalgamated.hpp"
#include "../include/motormixer.hpp"
#include "../include/motorcommand.hpp"

using namespace std;

TEST_CASE("MotorMixer implementation","[MotorMixer]"){
    MotorMixer p;
    MotorCommand command = p.mix(2,5,7,9);

    REQUIRE(command.motor1==2+5+7+9);
    REQUIRE(command.motor2==2-5+7-9);
    REQUIRE(command.motor3==2-5-7+9);
    REQUIRE(command.motor4==2+5-7-9);
    
}


