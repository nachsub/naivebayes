#ifndef name
#define name
#include <string>
using std::string;

enum Digit {
	zero, one, two, three, four, five, six, seven, eight, nine
};

struct NumberImage {
public:
	const static int size = 28;
	bool data[size][size];
	void SetData(int i, int j, bool val);
    //initializes data with values from filename
	void LoadImage(string filename, int &start, int &end);
    //returns true if all data values are false
    bool isFalse();
};
std::ostream& operator<<(std::ostream &stream, NumberImage ni);
#endif


