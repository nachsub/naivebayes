#define CATCH_CONFIG_MAIN 
#include "catch.hpp"
#include "digit.h"
#include "NumberImage.h"
using std::string;

TEST_CASE("Model.cpp") {
    const int laplace_k = 1;
    Model m;
    m.LoadModel(train_images, train_labels);
    m.calculate_freq(m.labels);

    SECTION("test calculate_freq") {
        int sum = 0;
        for (int i = Digit::zero; i <= Digit::nine; i++) {
            sum += m.digit_freq[(Digit) i];
        }
        REQUIRE(sum == 5000);
    }

    SECTION("test digit_freq") {
        REQUIRE((int) m.digit_freq[Digit::one] == 563);
    }

    SECTION("test DigitProb") {
        m.set_model(m);
        float prob = m.DigitProb(Digit::one);
        REQUIRE(prob == 0.1126f);
    }

    SECTION("test classification") {
        m.training();
	    m.LoadModel(test_images, test_labels);
	    float success = m.classification();
        REQUIRE(success == 0.72467f);
    }

    SECTION("test evaluate") {
        
    }

}