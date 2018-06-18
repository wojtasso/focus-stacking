#include "common.hpp"

using cv::Mat;

Mat BGR2Gray(Mat input)
{
    Mat tmp(input.rows, input.cols, CV_8UC1);

    if (input.channels() != 3)
        throw std::invalid_argument("Image is not in BGR format");

    for (int y = 0; y < tmp.rows; y++) {
        for (int x = 0; x < tmp.cols; x++) {
            tmp.at<uchar>(y, x) =
                0.114f*input.at<cv::Vec3b>(y, x)[0] +
                0.587f*input.at<cv::Vec3b>(y, x)[1] +
                0.299f*input.at<cv::Vec3b>(y, x)[2];
        }
    }

    return tmp;
}


