#ifndef numberimage
#define numberimage
#include <ostream>
#include <vector>
#include <string>

//number of digits
const int digit_count = 10;
//number of features
const int feature_count = 2;

struct NumberImage {
public:
	const static int size = 28;
	bool data[size][size];
};
std::ostream& operator<<(std::ostream &stream, NumberImage image);

struct Model{ 
public:
    std::vector<NumberImage> images;
    std::vector<int> labels;
    float confusion[10][10];
    float prob_pixel[NumberImage::size][NumberImage::size][feature_count][digit_count];
    //calculates digit frequencies and stores them in map digit_freq
    void calculate_freq(std::vector<int> labels);
    //loads images from imagefile and labels from labelfile
    void LoadModel(std::string s_imagefile, std::string s_labelfile);
    void training();
    void evaluate();
    void classification();
};

#endif
