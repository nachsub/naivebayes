#include <catch.hpp>
#include <digit.h>

TEST_CASE("NumberImages.cpp") {
    const int laplace_k = 1;
    const string train_images = "digitdata/trainingimages";
    const string train_labels = "digitdata/traininglabels"; 
    const string test_labels = "digitdata/testlabels";
    const string test_images = "digitdata/testimages";

    SECTION("test DigitProb") {
        float prob = DigitProb(Digit::one);
        REQUIRE(prob == 0.112);
    }

}