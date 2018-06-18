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

    for (unsigned int z = 0; z < numberOfImages; z++)
        absolute<float>(laplacian[z]);

    Mat sumMat(sizeY, sizeX, CV_32F);
    sumMatElementsInVec<float>(laplacian, sumMat);
    for (unsigned int i = 0; i < numberOfImages; i++)
        divideMat<float>(laplacian[i], sumMat, laplacian[i]);

    Mat focused(sizeY, sizeX, colors[0].type());

    //For every pixel in the final image, find the index of image, from
    //the series of photos, with the highest laplacian value. Assign pixel from
    //this image to the final image.
    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            float val = -FLT_MAX;
            int index = 0;

            for (unsigned int i = 0; i < numberOfImages; i++) {
                if (laplacian[i].at<float>(y, x) > val) {
                    index = i;
                    val = laplacian[i].at<float>(y, x);
                }
            }
            focused.at<cv::Vec3b>(y, x) = colors[index].at<cv::Vec3b>(y, x);
        }
    }

    cv::imshow("result", focused);
    cv::waitKey(0);

    cv::imwrite("focused.png", focused);

    return 0;
}
