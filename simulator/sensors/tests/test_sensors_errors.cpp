#define CATCH_CONFIG_MAIN
#include <iostream>
#include <vector>
#include "../../../external/Catch2/include/catch_amalgamated.hpp"
#include "../include/gaussianNoise.hpp"
#include "../include/sensorSaturation.hpp"
#include "../include/sensorError.hpp"

using namespace std;

TEST_CASE("Gaussian Noise Implementation", "[gaussian noise]") {
    float stddev=0.7;
    float mean=0;
    GaussianNoise noise(mean,stddev);

    REQUIRE(noise.getMean()==mean);
    REQUIRE(noise.getSigma()==stddev);


    /*vector<float> v;
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

    float standardDeviation = sqrt(variance/(v.size()-1));*/

    //REQUIRE(round(m)==mean);//empirical
    //REQUIRE(standardDeviation-stddev<0.001);//empirical

    REQUIRE(noise.getDistribution().mean()==mean);
    REQUIRE(noise.getDistribution().stddev()==stddev);
}

TEST_CASE("Gaussian Noise Reconfiguration", "[gaussian noise]") {
    float stddev=0.7;
    float mean=0;
    GaussianNoise noise(mean,stddev);

    REQUIRE(noise.getMean()==mean);
    REQUIRE(noise.getSigma()==stddev);

    REQUIRE(noise.getDistribution().mean()==mean);
    REQUIRE(noise.getDistribution().stddev()==stddev);

    float stddev2=0.5;
    float mean2=0.2;
    noise.configure(mean2,stddev2);

    REQUIRE(noise.getMean()==mean2);
    REQUIRE(noise.getSigma()==stddev2);

    REQUIRE(noise.getDistribution().mean()==mean2);
    REQUIRE(noise.getDistribution().stddev()==stddev2);
   
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