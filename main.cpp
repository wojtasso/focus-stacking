#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include "common.hpp"

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

    for (unsigned int i = 0; i < numberOfImages; i++)
        gray.push_back(BGR2Gray(colors[i]));

    for (unsigned int i = 0; i < numberOfImages; i++) {
        Mat tmp(sizeY, sizeX, gray[0].type());
        gaussianBlur(gray[i], tmp);
        gaussian.push_back(tmp);
    }

    for (unsigned int i = 0; i < numberOfImages; i++) {
        Mat tmp(sizeY, sizeX, CV_32F);
        calcLaplacian(gaussian[i], tmp);
        laplacian.push_back(tmp);
    }

    return 0;
}