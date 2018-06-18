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

template<typename inputType, typename outputType>
void convolution(const Mat& input, const Mat& kernel, Mat& output)
{
    for (int y = 0; y < input.rows; y++) {
        for (int x = 0; x < input.cols; x++) {
            for (int j = 0; j < kernel.rows; j++) {
                for (int i = 0; i < kernel.cols; i++) {
                    //Avoid taking elements outside the matrix
                    if (y + j - 1 < 0 || x + i - 1 < 0 ||
                            y + j - 1 >= input.rows || x + i - 1 >= input.cols)
                        continue;

                    output.at<outputType>(y, x) +=
                        input.at<inputType>(y + j - 1, x + i - 1) * kernel.at<float>(j, i);
                }
            }
        }
    }
}



template void convolution<uchar, uchar>(const Mat& input, const Mat& kernel, Mat& output);
template void convolution<uchar, float>(const Mat& input, const Mat& kernel, Mat& output);

