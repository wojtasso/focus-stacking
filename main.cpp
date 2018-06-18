#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using std::vector;
using cv::Mat;

int main(int argc, char *argv[])
{
    vector<cv::String> imageList;
    vector<Mat> colors, gray;
    vector<Mat> gaussian;
    vector<Mat> laplacian;

    glob("images/*.png", imageList, false);
    unsigned int numberOfImages = imageList.size();

    for (unsigned int i = 0; i < numberOfImages; i++) {
        Mat image = imread(imageList[i] , cv::IMREAD_UNCHANGED);
        colors.push_back(image);
    }

    int sizeX = colors[0].cols;
    int sizeY = colors[0].rows;


    return 0;
}
