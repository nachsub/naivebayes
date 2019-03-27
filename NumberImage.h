#ifndef numberimage
#define numberimage
#include <ostream>
#include <vector>
#include <string>
#include <unordered_map>

//number of digits
const int digit_count = 10;
//number of features
const int feature_count = 2;

const int laplace_k = 1;

const std::string train_images = "digitdata/trainingimages";
const std::string train_labels = "digitdata/traininglabels"; 
const std::string test_labels = "digitdata/testlabels";
const std::string test_images = "digitdata/testimages";

struct NumberImage {
public:
	const static int size = 28;
	bool data[size][size];
};

struct Model{ 
public:
    std::unordered_map<Digit, int> digit_freq;
    void set_model(Model m);
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
