#define CATCH_CONFIG_MAIN 
#include "catch.hpp"
#include "digit.h"
#include "NumberImage.h"
using std::string;

TEST_CASE("Model.cpp") {
    const int laplace_k = 1;
    Model m;
    m.LoadModel(train_images, train_labels);

    SECTION("test calculate_freq") {
        m.calculate_freq(m.labels);
        int sum = 0;
        for (int i = Digit::zero; i <= Digit::nine; i++) {
            sum += m.digit_freq[(Digit) i];
        }
    }

    SECTION("test digit_freq") {
        m.calculate_freq(m.labels);
        REQUIRE((int) m.digit_freq[Digit::one] == 563);
    }

    SECTION("test DigitProb") {
        //float prob = DigitProb(Digit::one);
    }

}