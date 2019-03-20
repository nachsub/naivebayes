#include <fstream>
#include <iostream>
#include <string>
#include "digit.h"
using std::string;
using std::ifstream;

void NumberImage::SetData(int i, int j, bool val) {
	NumberImage::data[i][j] = val;
}

int NumberImage::GetSize() {
	return size;
}

void NumberImage::LoadData(string filename, int start, int end) {
	ifstream file(filename);
	string str;
	int i = 0;
	while (std::getline(file, str) && i <= end) {
		if (i >= start) {
			for (int j = 0; j < GetSize(); j++) {
				char ch = str.at(j);
				if (ch == ' ')
					data[i][j] = false;
				if (ch == '#' || ch == '+')
					data[i][j] = true;
			}
		}
		i++;
	}
}

int main() {
	NumberImage ni;
	string file = "digitdata/trainingimages";
	ni.LoadData(file, 0, 28);
	std::cout << ni.data[14][14] << "\n";
    std::cout << ni.data[27][27];
}


