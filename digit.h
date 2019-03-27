#ifndef digit
#define digit
#include <unordered_map>

enum Digit {
	zero, one, two, three, four, five, six, seven, eight, nine
};

std::unordered_map<Digit, int> digit_freq;

//calculates the probability of dig
float DigitProb(Digit dig);

#endif


