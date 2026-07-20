#define CATCH_CONFIG_MAIN
#include "../../../external/include/catch_amalgamated.hpp"
#include <iostream>
#include <vector>
#include "../include/gaussianNoise.hpp"
#include "../include/sensorSaturation.hpp"
#include "../include/sensorError.hpp"

using namespace std;

TEST_CASE("Gaussian Noise Implementation", "[gaussian noise]") {
    GaussianNoise noise(0,0.05);

    REQUIRE(noise.getMean()==0);
    REQUIRE(noise.getSigma()==0.05);


    vector<float> v;
    float sum = 0;

    for(int i=0;i<100000;i++){
        float f = noise.sample();
        v.push_back(f);
        sum +=f;
    }

    float m = sum/v.size();
    float variance = 0;

    for (int i = 0; i < v.size(); ++i) {
        variance += pow(v[i] - m, 2);
    }

    float standardDeviation = sqrt(variance/v.size());

    REQUIRE(round(m)==0);
    REQUIRE(standardDeviation-0.05<0.05);//failed

    /*noise.getDistribution().mean();
    noise.getDistribution().stddev();//problem*/
}

TEST_CASE("Saturation implementation", "[saturation]") {
    SensorSaturation sat;
    REQUIRE(sat.getMinSaturation()==0);
    REQUIRE(sat.getMaxSaturation()==0);

    sat.setMinSaturation(-10);
    sat.setMaxSaturation(10);

    REQUIRE(sat.getMinSaturation()==-10);
    REQUIRE(sat.getMaxSaturation()==10);
    
}

TEST_CASE("Saturation clamping", "[saturation]") {
    SensorSaturation sat(-10,10);    
    REQUIRE(sat.applySaturation(-20)==-10);
    REQUIRE(sat.applySaturation(20)==10);
    REQUIRE(sat.applySaturation(2)==2);
}

TEST_CASE("Sensor error calculation", "[sensor error]") {
    SensorError s(0.0f,0.05f,0);
    float f = 10;
    REQUIRE_FALSE(s.apply(10)==10);
}