#include <math.h>
#include <limits>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "digit.h"
using std::string;
using std::ifstream;
using std::vector;
using std::ostream;
using std::cout;
using std::endl;
using std::unordered_map;
using std::numeric_limits;

vector<NumberImage> images;

unordered_map<Digit, int> digit_freq;

vector<int> labels;

float prob_pixel[NumberImage::size][NumberImage::size][2][10];

//entry in row r and column c is the percentage of test images from class r that are classified as class c.
float confusion[10][10];

const int laplace_k = 1;

const string train_images = "digitdata/trainingimages";

const string train_labels = "digitdata/traininglabels";

const string test_labels = "digitdata/testlabels";

const string test_images = "digitdata/testimages";


void NumberImage::SetData(int i, int j, bool val) {
	data[i][j] = val;
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

void LoadImagesAndLabels(string s_imagefile, string s_labelfile) {
	images = {};
	labels = {};
	if (s_labelfile == train_labels)
		digit_freq = {};
	ifstream imagefile(s_imagefile);
	ifstream labelfile(s_labelfile);
	string str, label;
	int i = 0;
    NumberImage image;
	while (std::getline(imagefile, str)) {
		if (std::getline(labelfile, label)) {
			labels.insert(labels.end(), std::stoi(label));
			if (s_labelfile == train_labels)
				digit_freq[(Digit) std::stoi(label)]++;
		}
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

//calculates the probability of class = digit
float DigitProb(Digit digit) {
	int sum = 0;
	for (int i = Digit::zero; i <= Digit::nine; i++) {
		sum += digit_freq[(Digit) i];
	}
	return (float) digit_freq[digit] / sum;
}

void training() {
	for (int i = 0; i < NumberImage::size; i++) {
		for (int j = 0; j < NumberImage::size; j++) {
			int count_data[10][2] = {};  //counts the frequency of 0s and 1s given class
			for (int k = 0; k < images.size(); k++) {
				int f = images[k].data[i][j]; //f == 0 or 1
				count_data[labels[k]][f]++;
				prob_pixel[i][j][f][labels[k]] = (float) (laplace_k + count_data[labels[k]][f])/(2*laplace_k + digit_freq[(Digit) labels[k]]);
			}
		}
	}
}

Digit MaxDig(unordered_map<Digit, float> post_prob) {
	float max = -numeric_limits<float>::infinity();
	Digit max_dig = Digit::zero;
	for (int dig = Digit::zero; dig <= Digit::nine; dig++) {
		if (post_prob[(Digit) dig] > max) {
			max = post_prob[(Digit) dig];
			max_dig = (Digit) dig;
		}
		//cout << "digit: " << dig << " max_dig: " << max_dig << " max: " << max << endl;
	}
	return max_dig;
}

void classification() {
	int success_count = 0;
	for (int k = 0; k < images.size(); k++) {
		NumberImage image = images[k];
		unordered_map<Digit, float> post_prob; //posterior probabilities
		for (int dig = Digit::zero; dig <= Digit::nine; dig++) {
			post_prob[(Digit) dig] = log(DigitProb((Digit) dig));  //log(P(class))
			for (int i = 0; i < NumberImage::size; i++) {
				for (int j = 0; j < NumberImage::size; j++) {
					int f = image.data[i][j];
					float prob_pix = prob_pixel[i][j][f][dig];
					post_prob[(Digit) dig] += log(prob_pix);
				}
			}
		}
		Digit max_dig = MaxDig(post_prob);
		cout << max_dig << " " << endl;
		confusion[labels[k]][max_dig]++;
		if (max_dig == labels[k]) 
			success_count++;
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			confusion[i][j] = (double) confusion[i][j]/digit_freq[(Digit) i];
		}
	}
	cout << (float) success_count/labels.size() << endl;
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

ostream& operator<<(ostream &stream, float confusion[10][10]) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << confusion[i][j] << " ";
            stream << confusion[i][j];
		}
		cout << std::endl;
	}
    return stream;
}


int main() {
	LoadImagesAndLabels(train_images, train_labels);
	training();
	LoadImagesAndLabels(test_images, test_labels);
	classification();
	cout << confusion;
}


