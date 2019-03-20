#ifndef name
#define name
#include <string>
using std::string;
enum Digit {
	one, two, three, four, five, six, seven, eight, nine
};
struct NumberImage {
public:
	const static int size = 28;
	int GetSize();
	bool data[size][size];
	void SetData(int i, int j, bool val);
	void LoadData(string filename, int start, int end);
};
#endif


