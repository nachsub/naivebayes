#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "digit.h"
using std::string;
using std::ifstream;
using std::vector;
using std::ostream;

vector<NumberImage> images;

const string trainingfile = "digitdata/trainingimages";

void NumberImage::SetData(int i, int j, bool val) {
	data[i][j] = val;
}

void NumberImage::LoadImage(string filename, int &start, int &end) {
    std::cout << "niggg " << images.size() << " " << start << " " << end << std::endl;   
	ifstream file(filename);
	string str;
	int i = 0;
	while (std::getline(file, str) && i < end) {
        //no more lines to read, so fills data with false
        if (str.length() == 0) {
            std::fill(data[0], data[0] + size*size, false);
            std::cout << "done" << std::endl;
            return;            
        } 

		if (i >= start) {
            std::cout << str << i << std::endl;
			for (int j = 0; j < str.length(); j++) {
				char ch = str.at(j);
				if (ch == ' ')
					data[i][j] = false;
				else if (ch == '#' || ch == '+')
                    data[i][j] = true;
			}
		}
		i++;
	}
}

//returns true if all data values are false
bool NumberImage::isFalse() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (data[i][j] == true)
                return false;
        }
    }
    std::cout << "done" << std::endl;
    return true;
}

ostream& operator<<(ostream &stream, vector<NumberImage> vect) {
	for (int i = 0; i < 10; i++) {
        std::cout << vect[i] << std::endl;
    }
}

void LoadImages(string filename) {
	ifstream file(filename);
	string str;
	int i = 0;
    NumberImage image;
	while (std::getline(file, str)) {
        if (i == image.size) {
            i = 0;
            images.insert(images.end(), image);
            NumberImage image;
        }
		for (int j = 0; j < image.size; j++) {
		    char ch = str.at(j);
		    if (ch == ' ')
			    image.data[i][j] = false;
		    else if (ch == '#' || ch == '+')
                image.data[i][j] = true;
		}
		i++;
	}
}

ostream& operator<<(ostream &stream, NumberImage ni) {
	for (int i = 0; i < ni.size; i++) {
		for (int j = 0; j < ni.size; j++) {
			std::cout << ni.data[i][j];
            stream << ni.data[i][j];
		}
		std::cout << std::endl;
	}
    return stream;
}


int main() {
	NumberImage ni;
    LoadImages(trainingfile);
	std::cout << images;
}


