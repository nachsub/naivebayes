#include <math.h>
#include <limits>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "digit.h"
#include "NumberImage.h"
using std::string;
using std::ifstream;
using std::vector;
using std::ostream;
using std::cout;
using std::endl;
using std::unordered_map;
using std::numeric_limits;


//entry in row r and column c is the percentage of test images from class r that are classified as class c.

void Model::LoadModel(string s_imagefile, string s_labelfile) {
	ifstream imagefile(s_imagefile), labelfile(s_labelfile);
	string str, label;
	int i = 0;
    NumberImage image;
	while (std::getline(imagefile, str)) {
		if (std::getline(labelfile, label)) 
			labels.insert(labels.end(), std::stoi(label));
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

void Model::calculate_freq(vector<int> labels) {
	//digit_freq = {};
	for(int i = 0; i < labels.size(); i++) {
		digit_freq[(Digit) labels[i]]++;
	}
}

float DigitProb(Digit dig) {
    Model m;
	int sum = 0;
	for (int i = Digit::zero; i <= Digit::nine; i++) {
		sum += m.digit_freq[(Digit) i];
	}
	return (float) m.digit_freq[dig]/sum;
}

void Model::training() {
	for (int i = 0; i < NumberImage::size; i++) {
		for (int j = 0; j < NumberImage::size; j++) {
			//counts the frequency of 0s and 1s given a class
			int count_data[10][2] = {};  
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
	}
	return max_dig;
}

void Model::evaluate() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			confusion[i][j] = (float) confusion[i][j]/ digit_freq[(Digit) i];
		}
	}
}

void Model::classification() {
	int success_count = 0;
	for (int k = 0; k < images.size(); k++) {
		NumberImage image = images[k];
		unordered_map<Digit, float> post_prob = {}; //posterior probabilities
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
		confusion[labels[k]][max_dig]++;
		if (max_dig == labels[k]) 
			success_count++;
	}
	cout << (float) success_count/labels.size() << endl;
}

ostream& operator<<(ostream &stream, NumberImage ni) {
	for (int i = 0; i < ni.size; i++) {
		for (int j = 0; j < ni.size; j++) {
			cout << ni.data[i][j];
            stream << ni.data[i][j];
		}
	cout << std::endl;
	}
    return stream;
}

ostream& operator<<(ostream &stream, float confusion[10][10]) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			string str = std::to_string(confusion[i][j]);
			cout << str.substr(0, 4) << "   ";
		}
		cout <<  endl;
	}
    return stream;
}

/**
int main() {
	Model m;
	m.LoadModel(train_images, train_labels);
	m.calculate_freq(m.labels);
	m.training();
	m.LoadModel(test_images, test_labels);
	m.classification();
	m.calculate_freq(m.labels);
	m.evaluate();
	cout << m.confusion;
}
*/


